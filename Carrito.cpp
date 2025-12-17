#include <Servo.h>

// ----------------------
// Pines del puente H (2 motores)
// ----------------------
int IN1 = 9;   // Motor A
int IN2 = 8;
int IN3 = 10;  // Motor B
int IN4 = 11;

// ----------------------
// Botones
// ----------------------
int btnAdelante  = 2;
int btnAtras     = 3;
int btnDerecha   = 4;
int btnIzquierda = 5;

// ----------------------
// Sensor ultrasónico HC-SR04
// ----------------------
int trigPin = 6;
int echoPin = 7;

// ----------------------
// Servo
// ----------------------
Servo servoSensor;
int servoPin = 12;

// ------------------------------------------------------

void setup() {
  // Motores
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  // Botones
  pinMode(btnAdelante, INPUT_PULLUP);
  pinMode(btnAtras, INPUT_PULLUP);
  pinMode(btnDerecha, INPUT_PULLUP);
  pinMode(btnIzquierda, INPUT_PULLUP);

  // Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Servo
  servoSensor.attach(servoPin);
  servoSensor.write(90); // frente

  Serial.begin(9600);

  detenerMotores();
}

// ---------------- FUNCIONES DE MOTORES ----------------

void motoresAdelante() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void motoresReversa() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void motoresDerecha() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);
}

void motoresIzquierda() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void detenerMotores() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// ---------------- FUNCIONES SENSOR ----------------

long medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH);
  if (duracion == 0) return 200;

  long distancia = duracion * 0.034 / 2;
  return distancia;
}

long medirDistanciaAngulo(int angulo) {
  servoSensor.write(angulo);
  delay(300);
  return medirDistancia();
}

// ---------------- MODO AUTOMÁTICO ----------------

void modoAutomatico() {

  long distFrente = medirDistanciaAngulo(90);
  Serial.print("Frente: ");
  Serial.println(distFrente);

  if (distFrente < 30) {

    // Detener
    detenerMotores();
    delay(200);

    // Retroceder
    motoresReversa();
    delay(400);
    detenerMotores();
    delay(200);

    // Medir lados
    long distIzq = medirDistanciaAngulo(150);
    long distDer = medirDistanciaAngulo(30);

    Serial.print("Izq: ");
    Serial.print(distIzq);
    Serial.print(" | Der: ");
    Serial.println(distDer);

    // Elegir dirección con más espacio
    if (distIzq > distDer) {
      motoresIzquierda();
      delay(500);
    } else {
      motoresDerecha();
      delay(500);
    }
  }
  else {
    motoresAdelante();
  }
}

// ------------------------------------------------------

void loop() {

  // MODO MANUAL
  if (digitalRead(btnAdelante) == LOW) {
    motoresAdelante();
  }
  else if (digitalRead(btnAtras) == LOW) {
    motoresReversa();
  }
  else if (digitalRead(btnDerecha) == LOW) {
    motoresDerecha();
  }
  else if (digitalRead(btnIzquierda) == LOW) {
    motoresIzquierda();
  }
  else {
    // MODO AUTOMÁTICO
    modoAutomatico();
  }
}