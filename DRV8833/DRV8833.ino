/*
    Exemplo para usar o driver DRV8833 para controla 2 motores DC que sejam usados para mover uma plataforma.
    Os pins "A" do driver dizem respeita ao motor esquerdo enquanto que os "B" são do motor da direita.
    
    Apenas se pode usar os pins 3, 5, 6, 9, 10, and 11 (é preciso poderem dar PWM).
    
    A função "MotorsSpeed" muda a velocidade de ambos os motores - 1º parametro para o motor da esquerda e
    2º parametro é para o motor da direita. Os valores podem ir de -255 a 255.
    Valores negativos é para o motor girar para trás.
*/

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

/*
  Chamem isto para configurar os pins.
*/
  Motors_Init();
  
 

  /* Põe os dois motores a velocidade 50 de 255 */
  MotorsSpeed(60,60);
}

void loop() {
  
  /* Loop aqui */
  
  
  
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

