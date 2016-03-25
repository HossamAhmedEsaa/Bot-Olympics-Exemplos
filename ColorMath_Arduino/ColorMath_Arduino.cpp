/*
 * ColorMath.c
 *
 *  Created on: 31/05/2015
 *      Author: Luís Afonso
 */


#include "ColorMath_Arduino.h"

unsigned long WhiteBase[4];
unsigned long RGBW[4];
unsigned long NeutralLimit=10;
unsigned long Scale_Max = 1024;

void ColorMath_Calibrate(unsigned long M[4]){
	int i;
	for(i=0; i<4; i++){
		WhiteBase[i]=M[i];
	}
}

void ColorMath_ConvertRGB(unsigned long M[4],unsigned long _invert){

	if(_invert){
		int i;
		for(i=0;i<4;i++){
			M[i] = Scale_Max*WhiteBase[i]/M[i];
			if(M[i] > Scale_Max)
				M[i]=Scale_Max;
		}
	}
	else{
		int i;
		for(i=0;i<4;i++){
			M[i] = Scale_Max*M[i]/WhiteBase[i];
			if(M[i] > Scale_Max)
				M[i]=Scale_Max;
		}
	}
}

bool ColorMath_IsNeutral(unsigned long M[4]){
	unsigned long vR = (Scale_Max*M[2]) - (Scale_Max*M[1]);
	unsigned long vG = (Scale_Max*M[0]) - (Scale_Max*M[2]);
	unsigned long vB = (Scale_Max*M[1]) - (Scale_Max*M[0]);
	vR *=vR; vG*=vG; vB*=vB;
	unsigned long radius_temp = (vR +vG+vB)/ ( (Scale_Max*Scale_Max)*3 );
	unsigned long Neutralradius = sqrt(radius_temp);

	if(Neutralradius <= NeutralLimit)
		return 1;
	else
		return 0;


}

unsigned long ColorMath_GetNeutralRadius(unsigned long M[4]){
	unsigned long vR = (Scale_Max*M[2]) - (Scale_Max*M[1]);
	unsigned long vG = (Scale_Max*M[0]) - (Scale_Max*M[2]);
	unsigned long vB = (Scale_Max*M[1]) - (Scale_Max*M[0]);
	vR *=vR; vG*=vG; vB*=vB;
	unsigned long radius_temp = (vR +vG+vB)/ ( (Scale_Max*Scale_Max)*3 );
	unsigned long Neutralradius = sqrt(radius_temp);
	return Neutralradius;
}
void ColorMath_SetNeutralLimit(unsigned long _value){
	NeutralLimit=_value;
}
unsigned long ColorMath_GetNeutralLimit(){
	return NeutralLimit;
}
