#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S3,     HTSPB,          sensorI2CCustom9V)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     frontRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backRight,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorLift1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     backLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     collector2,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    rollingGoalLeft,      tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    rollingGoalRight,     tServoStandard)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Robotics (PROGRAMENG)/hitechnic-superpro.h"

int balls = 0;
int binaryPort = 0;

void writeTo(ubyte mask){
	HTSPBwriteIO(HTSPB,mask);
}

void powerPorts(int ports)
{
	switch(ports){
	case 0: writeTo(0x00); break;
	case 1: writeTo(0x02); break;
	case 2: writeTo(0x06); break;
	case 3: writeTo(0x0e); break;
	case 4: writeTo(0x1e); break;
	case 5: writeTo(0x3e); break;
	}
}


task limitSwitch()
{
	HTSPBsetupIO(HTSPB,0x00); //b1 out, 00000000
	while(true)
	{

		if(HTSPBreadIO(HTSPB,0x01) >= 1) //b4, 00010000
		{
			writeDebugStreamLine("0x01");
	  }

		else if(HTSPBreadIO(HTSPB,0x02) >= 1) //b0
		{
			writeDebugStreamLine("0x02");
		}

	}
}
