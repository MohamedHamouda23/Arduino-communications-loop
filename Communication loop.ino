#define STX 0x70  // Start of Text
#define ETX 0x71  // End of Text

char txButton, txTilt, txPot, txA, txB, txC, txD;  // Transmit variables
char txBuffer[8] = {0,0,0,0,0,0,0,ETX};  // Transmit buffer initialized with ETX
char rxBuffer[7];  // Receive buffer
char rxButton, rxTilt, rxPot, rxA, rxB, rxC, rxD;  // Receive variables
int  rx_index;  // Index for receive buffer

#include <LiquidCrystal.h>

// LCD configuration pins
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Sensor and actuator pins
const int trigger = 8;  // Pin connected to the trigger pin of the ultrasonic sensor
const int echo = 9;     // Pin connected to the echo pin of the ultrasonic sensor
const int X_axis = A0;  // Analog pin connected to the X-axis of the joystick
const int motor = 10;   // Pin connected to the motor control


// Function to read inputs from sensors
void readInputs()
{
  long duration;           // Variable to store the duration of the ultrasonic pulse
  int objectDistance;      // Variable to store the calculated distance of an object

  // Trigger the ultrasonic sensor
  digitalWrite(trigger, LOW);         // Ensure the trigger pin is low
  delayMicroseconds(2);               // Wait for 2 microseconds
  digitalWrite(trigger, HIGH);        // Set the trigger pin high to send a pulse
  delayMicroseconds(10);              // Wait for 10 microseconds
  digitalWrite(trigger, LOW);         // Set the trigger pin low again

  // Measure the echo duration (time for the pulse to return)
  duration = pulseIn(echo, HIGH);

  // Calculate the distance in centimeters
  // The formula is based on the speed of sound (343 m/s or 0.034 cm/µs)
  // Dividing by 2 accounts for the round trip of the sound wave
  objectDistance = duration * 0.034 / 2;

  txA = objectDistance;  // Store the calculated distance in the variable `txA`

  // Read the X-axis position of the joystick
  int joystick = analogRead(X_axis);  // Read the analog value from the joystick's X-axis
  int motorVelocity = 0;             // Variable to store the mapped motor velocity

  // Map joystick values to motor velocity
  if (joystick >= 512) { 
    // If the joystick is moved forward, map values from [512, 1023] to [0, 127]
    motorVelocity = map(joystick, 512, 1023, 0, 127); 
  } else { 
    // If the joystick is moved backward, map values from [511, 0] to [0, 127]
    motorVelocity = map(joystick, 511, 0, 0, 127);    
  }
  txB = motorVelocity;  // Store the calculated motor velocity in the variable `txB`
}


// Function to write outputs to the motor and LCD
void writeOutputs()
{
  lcd.setCursor(0, 0);  // Set LCD cursor to the first row
  lcd.print("Distance: "); // Display the text "Distance" on the LCD screen
  lcd.print((int)rxA);  // Display received distance
  lcd.print(" cm   ");   // Display the text "cm" on the LCD screen
  analogWrite(motor, (int)rxB);  // Set motor speed based on received data
}

int ledState = LOW;   // ledState used to set the LED

// Encrypt data (dummy function as no real encryption is applied)
char encrypt(char in_char)
{
  char out_char;
  out_char = in_char;  // No transformation
  return out_char;
}

// Decrypt data (dummy function as no real decryption is applied)
char decrypt(char in_char)
{
  char out_char;
  out_char = in_char;  // No transformation
  return out_char;
}

// Setup function for initialization
void setup()
{
  lcd.begin(16, 2);  // Initialize LCD
  lcd.print("Distance"); // Display the text "Distance" on the LCD screen

  pinMode(trigger, OUTPUT);  // Set trigger pin as output
  pinMode(echo, INPUT);      // Set echo pin as input

  delay(1000);  // Wait for 1 second to allow the system to stabilize
  lcd.clear(); // Clear the LCD display
  pinMode(motor, OUTPUT);    // Set motor pin as output

  Serial.begin(9600);  // Initialize serial communication
}

// Transmit interval and states
const long txInterval = 200;        // interval at which to tx bit          
int tx_state = 0;
char chr;
unsigned long previousTxMillis = 0;   // will store last time LED was updated     

#define TX_START_OF_TEXT  -1
int tx_string_state = TX_START_OF_TEXT;

// Function to get the next character to transmit
char getTxChar()
{
  char chr;
 
  switch (tx_string_state)
  {
    case TX_START_OF_TEXT:
    tx_string_state = 0;
    txBuffer[0] = txButton;
    txBuffer[1] = txTilt;
    txBuffer[2] = txPot;
    txBuffer[3] = txA;
    txBuffer[4] = txB;
    txBuffer[5] = txC;
    txBuffer[6] = txD;
    return STX;  // Return start of text
    break;
   
    default:
    chr = txBuffer[tx_string_state];
    tx_string_state++;
    if (chr == ETX)  
    {
      tx_string_state = TX_START_OF_TEXT;  
      return ETX;  // Return end of text
    }
    else
    {
      return chr;  // Send a character in the string
    }
    break;
  }
}

// Function to handle character transmission
void txChar()
{
  unsigned long currentTxMillis = millis();

  if (currentTxMillis - previousTxMillis >= txInterval)
  {
    previousTxMillis = previousTxMillis + txInterval;  

    switch (tx_state)
    {
      case 0:
        chr = encrypt(getTxChar());  // Encrypt the character
        digitalWrite(12, HIGH);  // Transmit Start bit 
        tx_state++;
        break;

      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
        if ((chr & 0x40) != 0)   /* Transmit each bit in turn */
        {
          digitalWrite(12, HIGH);
        }
        else
        {
          digitalWrite(12, LOW);
        }
        chr = chr << 1;  //  Shift left to present the next bit 
        tx_state++;
        break;

      case 8:
        digitalWrite(12, HIGH);  // Stop bit
        tx_state++;
        break;

      default:
        digitalWrite(12, LOW);  
        tx_state++;
        if (tx_state > 20) tx_state = 0;  /* Start resending the character */
        break;
    }
  }
}

// Receive interval and states
const long rxInterval = 20;             
int rx_state = 0;
char rx_char;
unsigned long previousRxMillis = 0;      
int rx_bits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Function to handle character reception
void rxChar()
{
  unsigned long currentRxMillis = millis();
  int sensorValue;
  int i;

  if (currentRxMillis - previousRxMillis >= rxInterval)
  {
    previousRxMillis = previousRxMillis + rxInterval;  
    sensorValue = analogRead(A1);  // Simulate receiving signal

    switch (rx_state)
    {
      case 0:
        if (sensorValue >= 990)  // Check for start condition
        {
          rx_bits[0]++;
          rx_state++;
        }
        break;

      case 100:
        if ((rx_bits[0] >= 6) && (rx_bits[8] >= 6))  // Validate start and stop bits
        {
          rx_char = 0;

          for (i = 1; i < 8; i++)  // Decode data bits
          {
            rx_char = rx_char << 1;
            if (rx_bits[i] >= 6) rx_char = rx_char | 0x01;
          }
          rx_char = decrypt(rx_char);  // Decrypt received character

          Serial.println(rx_char + 0);  // Debug print

          switch (rx_char)
          {
            case STX:
            rx_index = 0;  // Reset index for new message
            break;
           
            case ETX:
            // Assign received data to variables
            rxButton = rxBuffer[0];
            rxTilt = rxBuffer[1];
            rxPot = rxBuffer[2];
            rxA = rxBuffer[3];
            rxB = rxBuffer[4];
            rxC = rxBuffer[5];
            rxD = rxBuffer[6];
            rx_index = 0;  // Reset index
            break;
           
            default:
            rxBuffer[rx_index] = rx_char;  // Store received character
            rx_index++;
            break;
          }
        }
        else
        {
          Serial.println("Rx error");  // Debug print for errors
        }

        for (i = 0; i < 10; i++)  // Reset bits array
        {
          rx_bits[i] = 0;
        }
        rx_state = 0;  // Reset state
        break;

      default:
        if (sensorValue >= 990)  
        {
          rx_bits[rx_state / 10]++;
        }
        rx_state++;
        break;
    }
  }
}

// Main loop function
void loop()
{
  readInputs();  // Read sensor inputs
  txChar();      // Transmit data
  rxChar();      // Receive data
  writeOutputs();  // Write outputs to actuators and LCD
}
