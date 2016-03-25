/*
 *  This example requires Adafruit's library for the TCS34725
 *  
 *  It shows how to calibrate and get calibrated readings using ColorMath library
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
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_4X);


void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  }
  else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  
  //You have 2 seconds to place the sensor over white
  delay(2000);

  /*
   * To get the values from Red, Green, Blue and Clear filter you use getRawData.
   * You need to use variables of the type uint16_t always!
   */
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  /*
   *  To use the ColorMath library you need to use arrays. So we need to store r, g, b and c in a array
   * that I named RGBC.
   *  You use ColorMath_Calibrate to set the values for the color white.
   */
  unsigned long RGBC[4] = { r, g, b, c};
  ColorMath_Calibrate(RGBC);
 
}

void loop(void) {

  /*
   *  Like it was done to calibrate, the TCS32745 library requires uint16_t variables 
   * but the ColorMath requires an array
   *  Instead of using values read in the beggining, you can set them yourself
   */
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  unsigned long RGBC[4] = { r, g, b, c};
  /*
   *  This function converts the values in the array "M", which contains raw values, 
   * to a calibrate scale (default 0-1024)
   */
  ColorMath_ConvertRGB(RGBC, 0);

  /*
   * Use this to see which value is set for the white color and the raw values being read
   */
  /*Serial.println("Original:");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" "); Serial.print("cal: "); Serial.print(RGBC[0], DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" "); Serial.print("cal: "); Serial.print(RGBC[1], DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" "); Serial.print("cal: "); Serial.print(RGBC[2], DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" "); Serial.print("cal: "); Serial.print(RGBC[3], DEC); Serial.print(" ");
    Serial.println(" ");*/


  /*
   *    This will print the values Red, Green, Blue and Clear already calibrated.
   *    It also prints how "far" the color read is from being neutral. The bigger the value, the "less neutral the color is" 
   * (neutral colors are white, gray and black). See "What_color_is_it.ino" to see how to use this.
   */
  Serial.println("Calibrated:");
  Serial.print("R: "); Serial.print(RGBC[0], DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(RGBC[1], DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(RGBC[2], DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(RGBC[3], DEC); Serial.print(" ");
  Serial.print("Neutral: "); Serial.print(ColorMath_GetNeutralRadius(RGBC)); Serial.print(" ");
  Serial.println(" ");
  //Serial.println(" ");


  delay(500);
}
