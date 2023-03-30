#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#define SensorLDR A0 // Sensor de Luminosidad
#define DHTPIN D4
#define DHTTYPE DHT11
#define echoPin D6
#define triggerPin D7

DHT dht(DHTPIN, DHTTYPE);

int sensorValue = 0;

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200bps
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dht.begin();
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

  sensorValue = analogRead(SensorLDR);
  Serial.print("Luminosidad: ");
  Serial.println(sensorValue);
  delay(2000);
}