
/* ================== Controls ================================ */
#define DEBUG_SONARS
#define DEBUG_LINE
#define DEBUG_MOTORS 
/* ============================================================ */

const int LINEPIN_Table[] = {A0, A1, A2};

#define BUTTON_PIN 8
int button_pressed = 0;

#define NUMBER_OF_SONARS 3
const int TRIGPIN_Table[] = { 11, 2, 7};
const int   ECHOPIN_Table[] = { 12, 4, 10};
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
  Serial.begin(9600);

  #ifdef DEBUG_MOTORS
    Motors_Init();
    pinMode(BUTTON_PIN, INPUT);
  #endif

  #ifdef DEBUG_SONARS
    Sonar_Init(NUMBER_OF_SONARS);
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
      Serial.println("Teste de motores acabou");
      delay(2000);
    }
  #endif

  #ifdef DEBUG_LINE
    int data[3];
    Get_Line(data);
    Serial.println("\n Line sensor ");
    for(int i = 0; i < 3; i++){
      Serial.println(data[i]);
    }
    
  #endif
  Serial.println("----------------------------------------------------------\n");
  delay(1000);
}


void Get_Line(int data[]){
  for(int i = 0; i < 3; i++){
    data[i] = analogRead(LINEPIN_Table[i]);
  }
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
      int distance = pulseIn(ECHOPIN_Table[i], HIGH);        // Read in times pulse
      data[i]= distance/58;                        // Calculate distance from time of pulse
      delay(50);    
  }

 // Serial.println(distance);                     
                                 // Wait 50mS before next ranging
}

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
  if(Speed > 255)
    Speed = 255;
    
  Speed = 255-Speed;

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
  if(Speed > 255)
    Speed = 255;
    
Speed = 255-Speed;
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
  MotorEsqSpeed(Vel_Esq);
  MotorDirSpeed(Vel_Dir);
}

