#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Sensor HC-SR04
const int trigPin = 9;
const int echoPin = 10;

// Calibración del tanque (sensor arriba del tanque)
const float distancia_lleno = 30.0;  // distancia cuando el tanque está lleno
const float distancia_vacia = 310.0; // distancia cuando está vacío

// Variables
float distancia_cm = 0.0;
float nivel_pct = 0.0;

// LCD I2C con dirección 0x20
LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.backlight();
}

long readMicrosecondsHC() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

float readDistance_cm() {
  long duration = readMicrosecondsHC();
  float distance = (duration * 0.0343) / 2.0;
  if (distance < distancia_lleno) distance = distancia_lleno;
  if (distance > distancia_vacia) distance = distancia_vacia;
  return distance;
}

void loop() {
  distancia_cm = readDistance_cm();

  // Cálculo de nivel invertido correctamente
  nivel_pct = ((distancia_vacia - distancia_cm) / (distancia_vacia - distancia_lleno)) * 100.0;
  if (nivel_pct < 0) nivel_pct = 0;
  if (nivel_pct > 100) nivel_pct = 100;

  // Estimación de litros (si el tanque tiene 100 L máximo)
  float litros = (nivel_pct / 100.0) * 100.0;

  // Mostrar en Serial
  Serial.print("Distancia: "); Serial.print(distancia_cm); Serial.print(" cm, ");
  Serial.print("Nivel: "); Serial.print(nivel_pct, 1); Serial.print(" %, ");
  Serial.print("Litros: "); Serial.print(litros, 1); Serial.println(" L");

  // Mostrar en LCD
  lcd.setCursor(0, 0);
  lcd.print("Nivel: ");
  lcd.print((int)nivel_pct);
  lcd.print("%    ");

  lcd.setCursor(0, 1);
  lcd.print("Litros: ");
  lcd.print((int)litros);
  lcd.print("L     ");

  delay(1000);
}
