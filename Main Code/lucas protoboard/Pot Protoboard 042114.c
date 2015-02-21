#pragma config(Sensor, S1,     proto,          sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "C:\Program Files\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-superpro.h"

task main()
{
	double x = 0;
	while(true){
		x = HTSPBreadADC(proto,1,8);
		x = x * 1.415;
		nxtDisplayString(3,"%d",x);
		wait10Msec(2);
    eraseDisplay();

    string dir = "east";
    if (x < 90)
    	dir = "north";
   else if ( x < 180 && x >= 90)
     dir = "east";
   else if ( x > 180 && x <= 270)
     dir = "south";
   else
     dir = "west";

     nxtDisplayString(4,"%s",dir);


	}


}
