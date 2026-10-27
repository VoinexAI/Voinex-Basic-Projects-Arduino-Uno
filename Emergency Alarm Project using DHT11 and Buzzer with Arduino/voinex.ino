#include <DHT.h>

#define DHT_PIN A1
#define DHT_TYPE DHT11
#define BUZZER_PIN 10

const float HEAT_LIMIT = 30.0;

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();
  noTone(BUZZER_PIN);

  Serial.println("DHT11 heat monitor started");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 Reading: ERROR");
    noTone(BUZZER_PIN);
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | Heat Alert: ");

  if (temperature >= HEAT_LIMIT) {
    tone(BUZZER_PIN, 2000);
    Serial.println("YES");
  } else {
    noTone(BUZZER_PIN);
    Serial.println("NO");
  }

  // DHT11 should not be read more often than about once every 2 seconds
  delay(2000);
}
