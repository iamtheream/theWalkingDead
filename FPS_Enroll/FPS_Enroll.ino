#include "LIB_GT511C3.h"
#include "SoftwareSerial.h"

// Hardware setup - FPS connected to:
//	  digital pin 4(arduino rx, fps tx)
//	  digital pin 5(arduino tx - 560ohm resistor - fps tx - 1000ohm resistor - ground)
//		this voltage divider brings the 5v tx line down to about 3.2v so we dont fry our fps

FPS_GT511C3 fps(4, 5);

void setup()
{
	Serial.begin(9600);
	delay(100);
	fps.Open();
	fps.SetLED(true);

	Enroll();
}


void Enroll()
{
	// Enroll test

	// find open enroll id
	int enrollid = 6;
	bool okid = false;
	while (okid == false)
	{
		okid = fps.CheckEnrolled(enrollid);
		if (okid==false) okid++;
	}
	fps.EnrollStart(enrollid);

	// enroll
	Serial.print("Press finger to Enroll #");
	Serial.println(enrollid);
	while(fps.IsPressFinger() == false) delay(100);
	bool bret = fps.CaptureFinger(true);
	int iret = 0;
	if (bret != false)
	{
		Serial.println("Remove finger");
		fps.Enroll1(); 
		while(fps.IsPressFinger() == true) delay(100);
		Serial.println("Press same finger again");
		while(fps.IsPressFinger() == false) delay(100);
		bret = fps.CaptureFinger(true);
		if (bret != false)
		{
			Serial.println("Remove finger");
			fps.Enroll2();
			while(fps.IsPressFinger() == true) delay(100);
			Serial.println("Press same finger yet again");
			while(fps.IsPressFinger() == false) delay(100);
			bret = fps.CaptureFinger(true);
			if (bret != false)
			{
				Serial.println("Remove finger");
				iret = fps.Enroll3();
				if (iret == 0)
				{
					Serial.println("Enrolling Successfull");
				}
				else
				{
					Serial.print("Enrolling Failed with error code:");
					Serial.println(iret);
				}
			}
			else Serial.println("Failed to capture third finger");
		}
		else Serial.println("Failed to capture second finger");
	}
	else Serial.println("Failed to capture first finger");
}


void loop()
{
	delay(100000);
}
