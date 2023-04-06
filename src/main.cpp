#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include <liquidcrystal.h>

#define SensorLDR A0 // Sensor de Luminosidad
#define DHTPIN D4
#define DHTTYPE DHT11
#define echoPin D6
#define triggerPin D7
#define RED_LED D1
#define GREEN_LED D2
#define BLUE_LED D3

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

DHT dht(DHTPIN, DHTTYPE);

int sensorValue = 0;

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200bps
  pinMode(triggerPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(RED_LED, OUTPUT); // Sets the echoPin as an Input
  pinMode(GREEN_LED, OUTPUT); // Sets the echoPin as an Input
  pinMode(BLUE_LED, OUTPUT); // Sets the echoPin as an Input
  lcd.begin(16, 2); // Inicializa el LCD
  dht.begin(); // Inicializa el sensor DHT11

  lcd.setCursor(0, 0); // lcd column, lcd row for
  lcd.print("Temperature: ");
  lcd.setCursor(0, 1); // lcd column, lcd row for
  lcd.print("Humidity: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  lcd.setCursor(12, 0); // lcd column, lcd row for
  lcd.print(t);
  lcd.setCursor(11, 1); // lcd column, lcd row for
  lcd.print(h);

  float duration, distance;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // if else statement to control the LED
  if (distance < 10) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  } else if (distance < 20) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }

  sensorValue = analogRead(SensorLDR);
  Serial.print("Luminosidad: ");
  Serial.println(sensorValue);
  delay(2000);
}