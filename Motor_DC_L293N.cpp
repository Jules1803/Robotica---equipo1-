//Motor DC con L293N
int ENA = 5;   // PWM velocidad
int IN1 = 7;   // dirección 1
int IN2 = 8;   // dirección 2

int botonIzq = 2; 
int botonDer = 3;

int ledIzq = 10;
int ledDer = 11;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(botonIzq, INPUT_PULLUP);
  pinMode(botonDer, INPUT_PULLUP);

  pinMode(ledIzq, OUTPUT);
  pinMode(ledDer, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Velocidad segura (motor 3~6V con batería 9V)
  int vel = 150;

  if (digitalRead(botonIzq) == LOW) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, vel);
    digitalWrite(ledIzq, HIGH);
    digitalWrite(ledDer, LOW);
    Serial.println("Motor izquierda");
  }
  else if (digitalRead(botonDer) == LOW) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, vel);
    digitalWrite(ledIzq, LOW);
    digitalWrite(ledDer, HIGH);
    Serial.println("Motor derecha");
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    digitalWrite(ledIzq, LOW);
    digitalWrite(ledDer, LOW);
    Serial.println("Motor OFF");
  }

  delay(60);
}