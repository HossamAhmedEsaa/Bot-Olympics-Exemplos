/*
 * ColorMath.h
 *
 *  Created on: 01/06/2015
 *      Author: Luís Afonso
 */

#ifndef COLORMATH_H_
#define COLORMATH_H_

#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include <math.h>

void ColorMath_Calibrate(unsigned long M[4]);
void ColorMath_ConvertRGB(unsigned long M[4],unsigned long _invert);
bool ColorMath_IsNeutral(unsigned long M[4]);
unsigned long ColorMath_GetNeutralRadius(unsigned long M[4]);
void ColorMath_SetNeutralLimit(unsigned long _value);
unsigned long ColorMath_GetNeutralLimit();


#endif /* COLORMATH_H_ */
