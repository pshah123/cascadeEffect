#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     Compass,        sensorI2CHiTechnicCompass)
#pragma config(Sensor, S4,     Accel,          sensorI2CHiTechnicAccel)
#pragma config(Motor,  mtr_S1_C1_1,     frontright,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     backright,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     frontleft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     backleft,      tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "hitechnic-gyro.h"

//global vars
float initial; 	//initial gyro reading
float heading; 	//robots current yaw
float radheading;   //heading in radians
int lastTime = 0;	//last time header was updated, used to find average change in rotation
float FLset; //front-left set, refers to Front-Left and Back-Right
float FRset; //front-right set, refers to Front-Right and Back-Left motor
float joyAngle; // angle of the first joystick
float temp;

void initializeRobot() {
	for(int i = 0; i < 100; i++){
		initial += SensorValue[S4];
		wait10Msec(1);
	}
	initial = initial / 100;
	return;
}

task fesDrive()
{
 int deadZone = 15;
	while(true)
	{
		int accelValue = SensorValue(Accel);
		int gyroValue = SensorValue(Gyro);

	nxtDisplayCenteredBigTextLine(5,"%d",gyroValue);

		getJoystickSettings(joystick);

		int y= joystick.joy1_y1;
		int x= joystick.joy1_x1;
		int z= joystick.joy1_x2;

	if ( (abs(joystick.joy1_x1) < deadZone) && (abs(joystick.joy1_y1) < deadZone) && (abs(joystick.joy1_x2) < deadZone)) {
			x = 0;
			y = 0;
			z = 0;
		}

		motor[frontright]= (-y+x+z);
		motor[backright]= (-y-x+z);
		motor[frontleft]= (y+x+z);
		motor[backleft]= (y-x+z);
	}
}

task getHeading() {
	float delTime = 0;
	float prevHeading = 0;
	float curRate = 0;

  HTGYROstartCal(GYRO);
  PlaySound(soundBeepBeep);
  while (true) {
    time1[T1] = 0;
    curRate = HTGYROreadRot(GYRO);
    if (abs(curRate) > 3) {
      prevHeading = currHeading;
      currHeading = prevHeading + curRate * delTime;
      if (currHeading > 360) currHeading -= 360;
      else if (currHeading < 0) currHeading += 360;
    }
    wait1Msec(5);
    delTime = ((float)time1[T1]) / 1000;
    //delTime /= 1000;
  }
}



task display()
{
	while (true){
		eraseDisplay();
		nxtDisplayCenteredTextLine(0, "Heading: %d", heading);
		nxtDisplayCenteredTextLine(1, "joyAngle: %d", joyAngle);
		wait1Msec(20);
	}
}


task main()
{
	initializeRobot();


	StartTask(display);

	StartTask(getHeading);

	StartTask(fesDrive);

  while (true){
		wait1Msec(10000);
	}
}
