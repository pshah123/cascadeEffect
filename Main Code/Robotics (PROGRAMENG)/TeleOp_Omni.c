#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     SMUX,           sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     backLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     a,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     b,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     emptyMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     liftRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     liftLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     backRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     frontRight,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "hitechnic-gyro.h"
#include "AdvancedSensors.c"
#include "hitechnic-sensormux.h"
#include "functionsOmni.c"
//#include "accelerometer.h"



task main()
{
	initializeRobot();
	StartTask(getHeading);
	StartTask(FPSDrive);
	waitForStart();
	while(true)
	{
		getJoystickSettings(joystick);
		StartTask(motorFunctions);
		StartTask(driverSweep);
		StartTask(liftFunction);
		if (joy2Btn(3))
		{
		//	servo[scoreLeft] = 200;
		//	servo[scoreRight] = 255-200;
		}

		if (joy2Btn(4))//score position
		{
			slideBtn ++;
			if(slideBtn % 2 == 1)
			{
		//		servo[scoreLeft] = 255;
		//		servo[scoreRight] = 0;
			}
			else //resting position
			{
			//	servoChangeRate[scoreLeft] = 3;
			//	servoChangeRate[scoreRight] = 3;
			//	servo[scoreLeft] = 35;
			//	servo[scoreRight] = 255-35;
				//servoChangeRate[scoreLeft] = 10;
				//servoChangeRate[scoreRight] = 10;
			}
			wait1Msec(500);
		}
		if (joy2Btn(2) == 1)//resting position
		{
	//		servo[scoreLeft] = 35;
		//	servo[scoreRight] = 255-35;
		}

		if (joy1Btn(3) == 1)//changed 5 to 3
		{
			rollingBtnSide++;
			if(rollingBtnSide % 2 == 1)
			{
			//	servo[rollingSide] = 200; //release rolling goal on side of robot
			}
			else
			{
			//	servo[rollingSide] = 50;//clamp rolling goal
			}
			//	servo[rollingSide] = 250;
			wait1Msec(500);
		}

		if (joy1Btn(4) == 1)
		{
			rollingBtnBack++;
			if(rollingBtnBack%2 == 1)
			{
			//	servo[rollingBack1] = 150; //release rolling goal
			//	servo[rollingBack2] = 150;
			}
			else
			{
				//servo[rollingBack1] = 0; //clamp rolling goal
			//	servo[rollingBack2] = 0;
			}
			wait1Msec(500);
		}

		if(joy1Btn(10))
		{
			autoArmBtn ++;
		}
		//	servoChangeRate[autonomousArm] = 5;
		/*
			if(autoArmBtn%2 == 1) servo[autonomousArm] = 195; //Resting position
			else servo[autonomousArm] = 100; //Scoring Position
			wait1Msec(500);
		}
		*/

		if(joy1Btn(3) && joy1Btn(1))
		{
			PlaySound(soundFastUpwardTones);
			//initializeRobot(); //Bad idea
			calibrate = 360 - currHeading;
		}


	} //DO NOT MOVE ANYTHING BELOW THIS
	/*
	DO	 NOT	 MOVE	 ANYTHING 	BELOW 	THIS
	*/
	while (true)
	{
		wait1Msec(2000); //REQUIRED, DO NOT MOVE
	}
}
