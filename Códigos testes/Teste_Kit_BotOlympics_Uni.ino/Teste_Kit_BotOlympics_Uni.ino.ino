/* 
  Selecionem o que querem testar atravez das macros "DEBUG_XXX". Comentem com // os testes que não querem que corram.

  Para iniciar carreguem uma vez no botão verde.
  Depois disso, para testar motores/ventoinha mantenham o botão verde premido durante algum tempo.

*/

#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);




/* ================== Controls ================================ */
#define DEBUG_SONARS
#define DEBUG_COLOR
#define DEBUG_MOTORS //including the fan
#define DEBUG_FLAME
/* ============================================================ */

#define FLAME_PIN A0

#define BUTTON_PIN 8
int button_pressed = 0;

#define FANPIN 10

#define NUMBER_OF_SONARS 3
const int TRIGPIN_Table[] = { 11, 2, 0};
const int   ECHOPIN_Table[] = { 12, 4, 1};
/*
  Conectar:
  Arduino UNO - DRV8833
      5(AIN1) -   AIN1
      3(AIN2) -   AIN2
      9(BIN1) -   BIN1
     6(BIN2) -   BIN2
*/
#define AIN1 5
#define AIN2 3
#define BIN1 9
#define BIN2 6

void Motors_Init();
void MotorEsqSpeed(int Speed);
void MotorDirSpeed(int Speed);
void MotorsSpeed(int Vel_Esq, int Vel_Dir);

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  while(digitalRead(BUTTON_PIN) == 0);
  
  Serial.begin(9600);

  #ifdef DEBUG_MOTORS
    Fan_Init();
    Motors_Init();

  #endif

  #ifdef DEBUG_SONARS
    Sonar_Init(NUMBER_OF_SONARS);
  #endif

  #ifdef DEBUG_COLOR
  tcs.begin();
  #endif
}

void loop() {
  
  // put your main code here, to run repeatedly:
  #ifdef DEBUG_COLOR
    uint16_t RGBC[4];
    Get_Colors(RGBC);
    Serial.print("R: "); Serial.print(RGBC[0], DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(RGBC[1], DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(RGBC[2], DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(RGBC[3], DEC); Serial.print(" ");
    Serial.println("");
  #endif
  
  #ifdef DEBUG_SONARS
    int distance[NUMBER_OF_SONARS];
    Get_Sonars(distance, NUMBER_OF_SONARS);
    for(int i = 0; i <  NUMBER_OF_SONARS; i++){
      Serial.print("Distance ");
      Serial.print(i);
      Serial.print(" = ");
      Serial.print(distance[i]);
      Serial.println("cm");
      Serial.println("");
    }
  #endif

  #ifdef DEBUG_MOTORS
    if(digitalRead(BUTTON_PIN) == 1){

      Serial.println("A iniciar teste de motores");
      Serial.println("Agora o motor da esquerda irá para a frente a 100");
      delay(2000);
      MotorsSpeed(100, 0);
      delay(2000);
      MotorsSpeed(0, 0);
      Serial.println("Agora o motor da esquerda irá para trás a -100");
      delay(2000);
      MotorsSpeed(-100, 0);
      delay(2000);
      MotorsSpeed(0, 0);
      Serial.println("Agora o motor da direita irá para a frente a 100");
      delay(2000);
      MotorsSpeed(0, 100);
      delay(2000);
      MotorsSpeed(0, 0);
      Serial.println("Agora o motor da direita irá para trás a -100");
      delay(2000);
      MotorsSpeed(0, -100);
      delay(2000);
      MotorsSpeed(0, 0);
      Serial.println("Agora a ventoinha irá ligar");
      delay(2000);
      digitalWrite(FANPIN, 0);
      delay(2000);
      digitalWrite(FANPIN,  1);
      Serial.println("Teste de motores acabou");
      delay(2000);
    }
  #endif

  #ifdef DEBUG_FLAME
    Serial.println("Flame sensor:");
    Serial.println(analogRead(FLAME_PIN));
  #endif
  Serial.println("----------------------------------------------------------\n");
  delay(100);
}


void Fan_Init(){

 pinMode(FANPIN, OUTPUT);
 digitalWrite(FANPIN,HIGH);
}


void Get_Colors(uint16_t RGBC[]){
  //uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRawData(&RGBC[0], &RGBC[1], &RGBC[2], &RGBC[3]);
 
  //colorTemp = tcs.calculateColorTemperature(r, g, b);
  //lux = tcs.calculateLux(r, g, b);
  
  /*Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");*/
}

void Sonar_Init(int n){

  for(int i = 0; i < n; i++){
    pinMode(ECHOPIN_Table[i], INPUT); 
    pinMode(TRIGPIN_Table[i], OUTPUT);
  }
 

}

void Get_Sonars(int data[], int n){ 
  for(int i = 0; i < n; i++){
      digitalWrite(TRIGPIN_Table[i], LOW);                   // Set the trigger pin to low for 2uS
      delayMicroseconds(2);
      digitalWrite(TRIGPIN_Table[i], HIGH);                  // Send a 10uS high to trigger ranging
      delayMicroseconds(10);
      digitalWrite(TRIGPIN_Table[i], LOW);                   // Send pin low again
      volatile int distance = pulseIn(ECHOPIN_Table[i], HIGH);        // Read in times pulse
      //Serial.print(TRIGPIN_Table[i]); Serial.print(" "); Serial.println(ECHOPIN_Table[i]);
      data[i]= distance/58;                        // Calculate distance from time of pulse
      delay(50);    
  }

 // Serial.println(distance);                     
                                 // Wait 50mS before next ranging
}

/*
  Chamem isto para configurar os pins.
*/
#define SENTIDO_MOTOR1 -1
#define SENTIDO_MOTOR2 -1
/*
  Chamem isto para configurar os pins.
*/
void Motors_Init() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}
/*
  Muda a velocidade de só do motor da esquerda
*/
void MotorDirSpeed(int Speed) {
  if (Speed == 0) {
    digitalWrite(AIN1, 1);
    digitalWrite(AIN2, 1);
  }
  bool forwards = 1;

  if (Speed < 0) {
    Speed = Speed * (-1);
    forwards = 0;
  }
  if (Speed > 255)
    Speed = 255;

  Speed = 255 - Speed;

  if (forwards) {
    digitalWrite(AIN1, HIGH);
    analogWrite(AIN2, Speed);
  }
  else {
    analogWrite(AIN1, Speed);
    digitalWrite(AIN2, HIGH);
  }
}

/*
  Muda a velocidade de só do motor da direita
*/
void MotorEsqSpeed(int Speed) {
  if (Speed == 0) {
    digitalWrite(BIN1, 1);
    digitalWrite(BIN2, 1);
  }
  bool forwards = 1;

  if (Speed < 0) {
    Speed = Speed * (-1);
    forwards = 0;
  }
  if (Speed > 255)
    Speed = 255;

  Speed = 255 - Speed;
  if (forwards) {
    digitalWrite(BIN1, HIGH);
    analogWrite(BIN2, Speed);
  }
  else {
    analogWrite(BIN1, Speed);
    digitalWrite(BIN2, HIGH);
  }
}

/*
  Muda a velocidade de ambos os motores
*/
void MotorsSpeed(int Vel_Esq, int Vel_Dir) {
  MotorEsqSpeed(SENTIDO_MOTOR1*Vel_Esq);
  MotorDirSpeed(SENTIDO_MOTOR2*Vel_Dir);
}
