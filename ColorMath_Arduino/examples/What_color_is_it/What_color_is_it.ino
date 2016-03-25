/*
 *  This example requires Adafruit's library for the TCS34725
 *  
 *  It shows a easy method to distinguish primary colors and black and white
 *  
 *  
 *  Made by: Luís Afonso
 * 
 */

#include <ColorMath_Arduino.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */


/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_16X);





void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  //You have 2 seconds to place the sensor over white
  delay(2000);

  /*
   *    This set's how "far" a reading can be from a neutral color before it's considered "not neutral"
   * you can see how far the color is from neutral by using ColorMath_GetNeutralRadius.
   *    ColorMath_IsNeutral will return 1 or 0 if a reading is considered a neutral color
   */
  ColorMath_SetNeutralLimit(15);
  
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  unsigned long RGBC[4] = { r, g, b, c};
  ColorMath_Calibrate(RGBC);

}

void loop(void) {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  unsigned long M[4] = { r, g, b, c};
  ColorMath_ConvertRGB(M, 0);

  int margem = 50;
  if (ColorMath_IsNeutral(M)){
    if (M[3] < 400)
      Serial.println("Preto");
    else
      Serial.println("Branco");
  }
  else if (M[0] > (M[1] + margem) && M[0] > (M[2] + margem) )
    Serial.println("Vermelho");
  else if (M[1] > (M[0] + margem) && M[1] > (M[2] + margem) )
    Serial.println("Verde");
  else if (M[2] > (M[0] + margem) && M[2] > (M[1] + margem) )
    Serial.println("Azul");
  else
    Serial.println("Desconhecida");
  delay(500);
}
