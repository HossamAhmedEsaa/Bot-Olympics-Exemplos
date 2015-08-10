/* 

  This is just a generic example to read analog values and print them on the
  serial monitor
  
*/

#define Analog_Sensor_Pin A0

int Analog_Sensor_Value=0;

void setup() {
  
  /* Configure Fire_Sensor_Pin as a INPUT */ 
  pinMode(Analog_Sensor_Pin,INPUT);
  
  /* Initialize Serial with 9600bps  */ 
  Serial.begin(9600);
}

void loop() {
  
  /* Read the sensor analog value and store in variable */
  Analog_Sensor_Value = analogRead(Analog_Sensor_Pin);
  
  /* Print out the sensor value so we can see it in the serial monitor */
  Serial.print("Analog Sensor Value = ");
  Serial.println(Analog_Sensor_Value); /* See here that it's println instead of just print?*/
  

}
