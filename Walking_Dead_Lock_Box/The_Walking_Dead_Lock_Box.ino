#include "LIB_GT511C3.h"
#include "SoftwareSerial.h"
#include <Servo.h>
#define SERVO_PIN 9    // sets servo to pin 9
int count = 0; // current display count
int pos = 0;    // variable to store the servo position
int nonactiveLED = 13;
int readingLED = 12;
int idLED = 11;
int deniedLED = 10;

// Hardware setup - FPS connected to:
//	  digital pin 4(arduino rx, fps tx)
//	  digital pin 5(arduino tx - 560ohm resistor - fps tx - 1000ohm resistor - ground)
//		this voltage divider brings the 5v tx line down to about 3.2v so we dont fry our fps

FPS_GT511C3 fps(4, 5);


Servo myservo;  // create servo object to control the lock


void setup()
{
	Serial.begin(9600);
	delay(100);
	fps.Open();
	fps.SetLED(true);
       // myservo.attach(SERVO_PIN);  // attaches the servo to pin 9
        pinMode(nonactiveLED, OUTPUT);
        pinMode(readingLED, OUTPUT);
        pinMode(idLED, OUTPUT);
        pinMode(deniedLED, OUTPUT);
        //zero();
}

void loop()
{
        digitalWrite(nonactiveLED, HIGH);
	// Identify fingerprint test
	if (fps.IsPressFinger())
{
        count++;
        
}


	{
	  delay(50);
          switch (count) {
            case 0:
              openDoor();
              Serial.print("Door Is Open");
              break;
            case 1:
              closeDoor();
              Serial.print("Door Is Closed");
              break;
            case 2:
              openDoor();
              Serial.print("Door Is Open");
              break;
            case 3:
              closeDoor();
              Serial.print("Door Is Closed");
              break;
            case 4:
              openDoor();
              Serial.print("Door Is Open");
              count = 0; 
              break;
            
            
            
            
          }
	}
	//delay(100);
}


void openDoor()
{ 
        fps.CaptureFinger(false);
        int id = fps.Identify1_N();
        if (id <200)
		{      
                        myservo.attach(SERVO_PIN);  // attaches the servo to pin 9
                        digitalWrite(nonactiveLED, LOW);
                        delay(50);
                        digitalWrite(readingLED, HIGH);
                        delay(50);
                        digitalWrite(readingLED, LOW);
			Serial.print("Verified ID:");
			Serial.println(id);
                        myservo.write(180);              // tell servo to go to 0 degrees
                        digitalWrite(idLED, HIGH);
                        delay(2000);
                        digitalWrite(idLED, LOW);
                        digitalWrite(nonactiveLED, HIGH);
                        myservo.detach();  // attaches the servo to pin 9
		}
		else
		{
			Serial.println("Finger not found");
                        digitalWrite(deniedLED, HIGH);
                        delay(2000);
                        digitalWrite(deniedLED, LOW);
		}    
           // delay(100);
	}


  


void closeDoor()
{
        fps.CaptureFinger(false);
        int id = fps.Identify1_N();
        if (id <200)
		{
                        myservo.attach(SERVO_PIN);  // attaches the servo to pin 9
			digitalWrite(nonactiveLED, LOW);
                        delay(50);
                        digitalWrite(readingLED, HIGH);
                        delay(50);
                        digitalWrite(readingLED, LOW);
			Serial.print("Verified ID:");
			Serial.println(id);
                        myservo.write(130);              // tell servo to go to 90 degrees
                        digitalWrite(idLED, HIGH);
                        delay(2000);
                        digitalWrite(idLED, LOW);
                        digitalWrite(nonactiveLED, HIGH);
                        myservo.detach();  // attaches the servo to pin 9
		}
		else
		{
			Serial.println("Finger not found");
                        digitalWrite(deniedLED, HIGH);
                        delay(2000);
                        digitalWrite(deniedLED, LOW);
		}  
              //  delay(100);
	}

