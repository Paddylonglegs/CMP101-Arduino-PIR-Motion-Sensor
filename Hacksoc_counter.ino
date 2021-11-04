/*
Author: Patrick Collins
©️license MIT
https://github.com/Paddylonglegs/
*/

//Includes
#include <Servo.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

//OLED screen setup
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 OLED(OLED_RESET);

//Pir Sensor setup variables
int pirPin = D7; //Pin that the sensor is using
int val; //Used for sensor, sensing detection.
int Mcounter=0; //Counter for detections.

//Servo Variables
Servo servo;
int angle = 10; //angle at which servo will be as default state.

//Servo Functions

void servoSetup()
{
  servo.attach(D8); //Pin servo is using.
  servo.write(angle);
}

void servoLoop() //spinning the servo
{  
  
  //Turning the servo 180 degrees
  for(angle = 10; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(5);                   
  } 
  
  // Turning the servo back to it's original state
  for(angle = 180; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(5);       
  } 
}

////LED Variables
int LED = D6;
 
//LED functions

void ledSetup()
{
  pinMode(LED, OUTPUT); // Make LED pin D6 an output pin
}

void ledOn() //Function to turn LED on
{
  
  digitalWrite(LED, HIGH); // LED on
  delay(500); // Wait 0.5 second
}

void ledOff() //Function to turn LED off
{
  digitalWrite(LED, LOW); // LED off
  delay(500); // Wait 0.5 seconds
}
 
void setup()
{
  Serial.begin(9600);
  
  //OLED screen setup
  OLED.begin();
  //OLED.clearDisplay();
  //Add stuff into the 'display buffer'
  OLED.setTextWrap(false);
  OLED.setTextSize(1); //Font size.
  OLED.setTextColor(WHITE); //Colour of the text displayed on OLED screen.
  OLED.setCursor(0,0);
  OLED.println("Hacksoc Members: "); //This message is displayed constantly, allowing others to see the purpose of the counter.
  OLED.display(); //output 'display buffer' to screen   

  //Servo setup
  servoSetup(); //Calling servo setup funciton.

  //LED setup
  ledSetup(); //calling LED setup function.
  
}
 
void loop()
{
 val = digitalRead(pirPin);
//low = no motion, high = motion

if (val == LOW)
{
  Serial.println("Hacker not present"); //simply for the serial monitor in tools, is not displayed on the OLED screen
}
else
{
  Serial.println("Member +1");
  Mcounter= Mcounter +1; //This is how members are counted. Every time the sensor is activated the members increase. 
  Serial.println(Mcounter); //Simply for serial monitor in tools, is not displayed on OLED screen at this point.
  //OLED display
  OLED.begin();
  OLED.clearDisplay();   
  //Add stuff into the 'display buffer'
  OLED.setTextWrap(false);
  OLED.setTextSize(1); //Same font size to match previous OLED state.
  OLED.setTextColor(WHITE); //Colour of the text displayed on OLED screen, same to make a seemless transition.
  OLED.setCursor(0,0);
  OLED.println("Hacksoc Members: "); //This message is displayed again, allowing a seemless transition between the OLED screens.
  OLED.print(Mcounter); //Displaying how many people have walked past the sensor.
  OLED.display(); //output 'display buffer' to screen  
  
  //Servo action
  servoLoop(); //calling servo loop function

  //LED action
  ledOn(); //Turning LED on for 0.5 seconds.
  ledOff(); //Then turning off for 0.5 seconds.
}
delay(1000);
}
