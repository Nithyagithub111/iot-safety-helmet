// IoT-Enabled Worker Safety Monitoring Helmet
// ESP32 + MQ-2 (gas) + DHT22 (temperature) + Potentiometer (simulates vibration)

#include "DHT.h"

#define GAS_PIN   34   // MQ-2 AOUT
#define DHT_PIN   4    // DHT22 SDA
#define VIB_PIN   35   // Potentiometer wiper (stands in for vibration sensor)
#define DHT_TYPE  DHT22

DHT dht(DHT_PIN, DHT_TYPE);

const int GAS_THRESHOLD = 300;     // MQ-2 analog, 0-4095
const float TEMP_THRESHOLD = 40.0; // °C, heat-stress risk point
const int VIB_THRESHOLD = 2500;    // pot analog, 0-4095

const int CONFIRM_COUNT = 3; // require 3 consecutive high readings before alerting
int gasAboveCount = 0;
int vibAboveCount = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("=== Worker Safety Helmet: monitoring started ===");
}

void loop() {
  unsigned long timestamp = millis();

  int gasValue = analogRead(GAS_PIN);
  int vibValue = analogRead(VIB_PIN);
  float tempValue = dht.readTemperature();

  Serial.print("[t="); Serial.print(timestamp / 1000.0, 1); Serial.print("s] ");
  Serial.print("Gas: "); Serial.print(gasValue);
  Serial.print(" | Temp: "); Serial.print(isnan(tempValue) ? -1 : tempValue, 1);
  Serial.print(" | Vibration: "); Serial.println(vibValue);

  // Gas check
  if (gasValue > GAS_THRESHOLD) {
    gasAboveCount++;
    if (gasAboveCount == CONFIRM_COUNT) {
      Serial.print("!!! ALERT [t="); Serial.print(timestamp / 1000.0, 1);
      Serial.print("s] Unsafe gas level: "); Serial.println(gasValue);
    }
  } else {
    gasAboveCount = 0;
  }

  // Temperature check
  if (!isnan(tempValue) && tempValue > TEMP_THRESHOLD) {
    Serial.print("!!! ALERT [t="); Serial.print(timestamp / 1000.0, 1);
    Serial.print("s] Unsafe temperature: "); Serial.print(tempValue, 1); Serial.println(" C");
  }

  // Vibration check
  if (vibValue > VIB_THRESHOLD) {
    vibAboveCount++;
    if (vibAboveCount == CONFIRM_COUNT) {
      Serial.print("!!! ALERT [t="); Serial.print(timestamp / 1000.0, 1);
      Serial.print("s] Abnormal vibration: "); Serial.println(vibValue);
    }
  } else {
    vibAboveCount = 0;
  }

  delay(500);
}