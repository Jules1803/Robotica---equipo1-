const int ENA = 9;    
const int IN1 = 8;    
const int IN2 = 7;    

const int botonPin = 2;       // Botón sentido normal
const int botonInversoPin = 5; // Nuevo botón para sentido inverso
const int ledVerde = 3;
const int ledRojo = 4;

bool motorActivo = false;
bool sentidoInverso = false;  // Nuevo flag para dirección
int velocidad = 200;  

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(botonPin, INPUT_PULLUP);
  pinMode(botonInversoPin, INPUT_PULLUP); // nuevo botón
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Iniciado Motor DC con L293N");
  
  detenerMotor();
}

void loop() {
  // Botón de avance
  if (digitalRead(botonPin) == LOW) {
    delay(50);  
    if (digitalRead(botonPin) == LOW) {
      toggleMotor(false); // false → sentido normal
      while(digitalRead(botonPin) == LOW);   
    }
  }

  // Botón de retroceso
  if (digitalRead(botonInversoPin) == LOW) {
    delay(50);  
    if (digitalRead(botonInversoPin) == LOW) {
      toggleMotor(true); // true → sentido inverso
      while(digitalRead(botonInversoPin) == LOW);
    }
  }
}

void toggleMotor(bool invertir) {
  if (motorActivo && sentidoInverso == invertir) {
    detenerMotor();
  } else {
    if (invertir) {
      activarMotorInverso();
    } else {
      activarMotor();
    }
  }
}

void activarMotor() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidad);  
  
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledRojo, LOW);
  
  Serial.println("🟢 ACTIVADO (Sentido Normal)");
  Serial.print("Velocidad PWM: ");
  Serial.println(velocidad);
  
  motorActivo = true;
  sentidoInverso = false;
}

void activarMotorInverso() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velocidad);
  
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledRojo, LOW);
  
  Serial.println("🟠 ACTIVADO (Sentido Inverso)");
  Serial.print("Velocidad PWM: ");
  Serial.println(velocidad);
  
  motorActivo = true;
  sentidoInverso = true;
}

void detenerMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledRojo, HIGH);
  
  Serial.println("🔴 DETENIDO");
  
  motorActivo = false;
}