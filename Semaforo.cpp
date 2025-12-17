
// Definición de pines
const int LED1 = 12;
const int LED2 = 11
const int LED3 = 10;
const int LED4 = 8;

const int TIEMPO = 5000;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  digitalWrite(LED1, HIGH);
  delay(TIEMPO);
  digitalWrite(LED1, LOW);

  digitalWrite(LED2, HIGH);
  delay(TIEMPO);
  digitalWrite(LED2, LOW);

  digitalWrite(LED3, HIGH);
  delay(TIEMPO);
  digitalWrite(LED3, LOW);

  digitalWrite(LED4, HIGH);
  delay(TIEMPO);
  digitalWrite(LED4, LOW);
}
