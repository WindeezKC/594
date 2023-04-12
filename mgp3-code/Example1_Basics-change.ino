/****************************************************************
 * Example1_Basics.ino
 * ICM 20948 Arduino Library Demo
 * Use the default configuration to stream 9-axis IMU data
 * Owen Lyke @ SparkFun Electronics
 * Original Creation Date: April 17 2019
 *
 * Please see License.md for the license information.
 *
 * Distributed as-is; no warranty is given.
 ***************************************************************/
#include "ICM_20948.h" // Click here to get the library: http://librarymanager/All#SparkFun_ICM_20948_IMU

//#define USE_SPI       // Uncomment this to use SPI

#define SERIAL_PORT Serial

#define SPI_PORT SPI // Your desired SPI port.       Used only when "USE_SPI" is defined
#define CS_PIN 2     // Which pin you connect CS to. Used only when "USE_SPI" is defined

#define WIRE_PORT Wire // Your desired Wire port.      Used when "USE_SPI" is not defined
// The value of the last bit of the I2C address.
// On the SparkFun 9DoF IMU breakout the default is 1, and when the ADR jumper is closed the value becomes 0
#define AD0_VAL 1

#ifdef USE_SPI
ICM_20948_SPI myICM; // If using SPI create an ICM_20948_SPI object
#else
ICM_20948_I2C myICM; // Otherwise create an ICM_20948_I2C object
#endif
float prevGyrX = 0.0;
float prevGyrY = 0.0;
float prevGyrZ = 0.0;
const int buttonPin1 = 2;  // the number of the pushbutton pin
const int buttonPin2 = 5;  // the number of the pushbutton pin
int buttonState1 = 0;  // variable for reading the pushbutton status
int buttonState2 = 0;  // variable for reading the pushbutton status

// Define a threshold for detecting movements
float moveThreshold = 10.0;

// Define variables to hold the current and previous movement states
bool isMoving = false;
bool prevMoving = false;

// Define a counter for the number of movements detected
int moveCount = 0;

void setup()
{ 
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  SERIAL_PORT.begin(115200);
  while (!SERIAL_PORT)
  {
  };

#ifdef USE_SPI
  SPI_PORT.begin();
#else
  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);
#endif

  //myICM.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  bool initialized = false;
  while (!initialized)
  {

#ifdef USE_SPI
    myICM.begin(CS_PIN, SPI_PORT);
#else
    myICM.begin(WIRE_PORT, AD0_VAL);
#endif

    SERIAL_PORT.print(F("Initialization of the sensor returned: "));
    SERIAL_PORT.println(myICM.statusString());
    if (myICM.status != ICM_20948_Stat_Ok)
    {
      SERIAL_PORT.println("Trying again...");
      delay(500);
    }
    else
    {
      initialized = true;
    }
  }
}

void loop()
{
  
  if (myICM.dataReady())
  {
    myICM.getAGMT();         // The values are only updated when you call 'getAGMT'
                               //printRawAGMT( myICM.agmt );     // Uncomment this to see the raw values, taken directly from the agmt structure
    //printScaledAGMT(&myICM); // This function takes into account the scale settings from when the measurement was made to calculate the values with units
    delay(30);
  }
  else
  {
    SERIAL_PORT.println("Waiting for data");
    delay(500);
  }

 if (myICM.dataReady())
  {// read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    // turn LED on:
    Serial.println("L");
    //delay(500);
  } else {
    // turn LED off:
    
    //delay(500);
  }
  if (buttonState2 == HIGH) {
    // turn LED on:
    Serial.println("R");
    //delay(500);
  } else {
    // turn LED off:
    
    //delay(500);
  }
    myICM.getAGMT();
    float gyrX = myICM.gyrX();
    float gyrY = myICM.gyrY();
    float gyrZ = myICM.gyrZ();

    // Calculate the change in orientation from the previous reading
    float deltaGyrX = gyrX - prevGyrX;
    float deltaGyrY = gyrY - prevGyrY;
    float deltaGyrZ = gyrZ - prevGyrZ;

    // Check if the movement exceeds the threshold
    if (abs(deltaGyrX) > moveThreshold || abs(deltaGyrY) > moveThreshold || abs(deltaGyrZ) > moveThreshold)
    {
      // Update the movement state and increment the movement counter
      isMoving = true;
      moveCount++;
    }
    else
    {
      // Update the movement state
      isMoving = false;
    }  
    SERIAL_PORT.print(gyrX);
    SERIAL_PORT.print(", ");
    SERIAL_PORT.print(gyrY);
    SERIAL_PORT.print(", ");
    SERIAL_PORT.print(gyrZ);


   
    SERIAL_PORT.println("");

    // Save the current orientation data as the previous reading
    prevGyrX = gyrX;
    prevGyrY = gyrY;
    prevGyrZ = gyrZ;

    delay(100);
  }
  else
  {
    SERIAL_PORT.println("Waiting for data");
    delay(500);
  }
}






    

// Below here are some helper functions to print the data nicely!

void printPaddedInt16b(int16_t val)
{
  if (val > 0)
  {
    SERIAL_PORT.print(" ");
    if (val < 10000)
    {
      SERIAL_PORT.print("0");
    }
    if (val < 1000)
    {
      SERIAL_PORT.print("0");
    }
    if (val < 100)
    {
      SERIAL_PORT.print("0");
    }
    if (val < 10)
    {
      SERIAL_PORT.print("0");
    }
  }
  else
  {
    SERIAL_PORT.print("-");
    if (abs(val) < 10000)
    {
      SERIAL_PORT.print("0");
    }
    if (abs(val) < 1000)
    {
      SERIAL_PORT.print("0");
    }
    if (abs(val) < 100)
    {
      SERIAL_PORT.print("0");
    }
    if (abs(val) < 10)
    {
      SERIAL_PORT.print("0");
    }
  }
  SERIAL_PORT.print(abs(val));
}


void printFormattedFloat(float val, uint8_t leading, uint8_t decimals)
{
  float aval = abs(val);
  if (val < 0)
  {
    SERIAL_PORT.print("-");
  }
  else
  {
    SERIAL_PORT.print(" ");
  }
  for (uint8_t indi = 0; indi < leading; indi++)
  {
    uint32_t tenpow = 0;
    if (indi < (leading - 1))
    {
      tenpow = 1;
    }
    for (uint8_t c = 0; c < (leading - 1 - indi); c++)
    {
      tenpow *= 10;
    }
    if (aval < tenpow)
    {
      SERIAL_PORT.print("0");
    }
    else
    {
      break;
    }
  }
  if (val < 0)
  {
    SERIAL_PORT.print(-val, decimals);
  }
  else
  {
    SERIAL_PORT.print(val, decimals);
  }
}

#ifdef USE_SPI
void printScaledAGMT(ICM_20948_SPI *sensor)
{
#else
void printScaledAGMT(ICM_20948_I2C *sensor)
{
#endif
/*
   printFormattedFloat(sensor->gyrX(), 5, 0);
  SERIAL_PORT.print(",");
   printFormattedFloat(sensor->gyrY(), 5, 0);
  SERIAL_PORT.print(",");
  printFormattedFloat(sensor->gyrZ(), 5, 0);
   SERIAL_PORT.println();
  */
}
