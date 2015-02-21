#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Gyro,           sensorI2CMuxController)
#pragma config(Sensor, S3,     Sonar,          sensorSONAR)
#pragma config(Sensor, S4,     Accel,          sensorI2CHiTechnicAccel)
#pragma config(Motor,  mtr_S1_C1_1,     backright,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     backleft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     emptymotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     frontright,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     frontleft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     liftRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     liftLeft,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    scoreA,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    scoreB,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    rollingBack,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    rollingSide,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "hitechnic-gyro.h"

float initial; 	//initial gyro reading
float heading; 	//robots current yaw
float radheading;   //heading in radians
int lastTime = 0;	//last time header was updated, used to find average change in rotation
float FLset; //front-left set, refers to Front-Left and Back-Right
float FRset; //front-right set, refers to Front-Right and Back-Left motor
float joyAngle; // angle of the first joystick
float currHeading;
float sonarValue;
float delTime = 0;//calibration
float prevHeading = 0;
float curRate = 0;
int deadZone = 15;

void motorTrigger(tMotor motorCall,int x,int y,int z)
{
	motor[motorCall]= (y+x+z);
}

void initializeRobot()
{
	for(int i = 0; i < 100; i++){//Sensor
		initial += SensorValue[S4];
		wait10Msec(1);
		initial = initial / 100;//Sensor

		servo[scoreA]=0;
		servo[scoreB]=0;
		servo[rollingBack] = 180;
		servo[rollingSide] = 180; //rolling goal clamps are open
		return;
	}
}


task FPSDrive()
{
	while(true)
	{
		int accelValue = SensorValue(Accel); //set accelerometer value to accelValue
		int gyroValue = SensorValue(Gyro); //set gyroscope value to gyroValue

		nxtDisplayCenteredBigTextLine(5,"%d",gyroValue); //display gyroValue to NXT
		nxtDisplayCenteredBigTextLine(5,"%d",accelValue); //display accelValue to NXT

		getJoystickSettings(joystick);

		int y= joystick.joy1_y1;
		int x= joystick.joy1_x1;
		int z= joystick.joy1_x2;

		int trueX = (cosDegrees(currHeading)*x)-(sinDegrees(currHeading)*y); //sets trueX to rotated x value
		int trueY = (sinDegrees(currHeading)*x)+(cosDegrees(currHeading)*y); //sets trueY to rotated y value

		x = trueX;
		y = trueY;

		if ( (abs(joystick.joy1_x1) < deadZone) && (abs(joystick.joy1_y1) < deadZone) && (abs(joystick.joy1_x2) < deadZone)) //drive only if joystick out of dead zones
		{
			x = 0;
			y = 0;
			z = 0;
		}

		motorTrigger(frontright,x,-y,-z);
		motorTrigger(backright,-x,-y,-z);
		motorTrigger(frontleft,x,y,-z);
		motorTrigger(backleft,-x,y,-z);
	}
}

task getHeading() {
	HTGYROstartCal(Gyro);
	PlaySound(soundBeepBeep);
	while (true) {
		time1[T1] = 0;
		curRate = HTGYROreadRot(Gyro);
		if (abs(curRate) > 3) //sets deadzones for gyroscope
		{
			prevHeading = currHeading;
			currHeading = prevHeading + curRate * delTime; //changes current heading based on the rate of change and time elapsed
			if (currHeading > 360) currHeading -= 360; //keeps current heading between 0 and 360
			else if (currHeading < 0) currHeading += 360; // keeps curent heading between 0 and 360
		}
		wait1Msec(5);
		delTime = ((float)time1[T1]) / 1000;
	}
}
/*
task display()
{
while (true){
eraseDisplay();
nxtDisplayCenteredTextLine(0, "Heading: %d", currHeading);
nxtDisplayCenteredTextLine(1, "joyAngle: %d", joyAngle);
nxtDisplayCenteredTextLine(2, "Sonar: %d", sonarValue);
wait1Msec(20);
}
}


task getSonar()
{
while(true){
sonarValue = SensorValue(Sonar);}
}
*/

/*
task calibrateDrive()//needs work, doing some wack stuff
{
while(true)
{
if(joy1Btn(1)&&joy1Btn(3))
{
PlaySound(soundUpwardTones);
wait1Msec(500);
}
}
}
*/
task liftFunction()
{
	int triggerValue;
	while(true)
	{
		if (abs(joystick.joy2_y2) < deadZone) //drive only if joystick out of dead zones
		{
			triggerValue = 0
		}
		triggerValue = joystick.joy2_y2;
		motor[liftRight] = -triggerValue;
		motor[liftLeft] = triggerValue;
	}
	wait1Msec(20);
}

task motorFunctions()
{
	int sweeperTrigger;
	while(true)//
	{
		if(abs(joystick.joy2_y1) < deadZone)
		{
			sweeperTrigger = 0;
		}
		sweeperTrigger =  joystick.joy2_y1;
		motor[collector] = sweeperTrigger;
		wait1Msec(20);
	}
}

task functions()
{
	while(true)
	{
		if (joy2Btn(1))//ready position
		{
			servo[scoreA] = 75;
			servo[scoreB] = 255-75;
			wait1Msec(500);
		}
		if (joy2Btn(2))//score position
		{
			servo[scoreA] = 240;
			servo[scoreB] = 10;
			wait1Msec(500);
		}
		if (joy2Btn(3))//resting position
		{
			servo[scoreA] = 10;
			servo[scoreB] = 240;
			wait1Msec(500);
		}
		if (joy1Btn(500))
		{
			servo[rollingBack] = 50; //clamp onto rolling goal in back of robot
			wait1Msec(500);
		}
		if (joy1Btn(7))
		{
			servo[rollingBack] = 0; //release rolling goal
			wait1Msec(500);
		}

		if (joy1Btn(6))
		{
			servo[rollingSide] = 50; //clamp onto rolling goal on side of robot
			wait1Msec(500);
		}
		if (joy1Btn(8))
		{
			PlaySound(soundUpwardTones);
			servo[rollingSide] = 0; //release rolling goal
			wait1Msec(500);
		}
	}
}


task main()
{
	initializeRobot();
	waitForStart();
	getJoystickSettings(joystick);
	//StartTask(display);
	StartTask(getHeading);
	StartTask(FPSDrive);
	//StartTask(getSonar);
	//StartTask(calibrateDrive);
	StartTask(functions);
	StartTask(motorFunctions);
	StartTask(liftFunction);

	while (true){
		if(joy1Btn(1))
		{
			PlaySound(soundBeepBeep);
			servoTarget[rollingSide] = 80;
			wait1Msec(1000);
		}
	}

}
