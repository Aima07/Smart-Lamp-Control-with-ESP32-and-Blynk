#define BLYNK_TEMPLATE_ID "TMPL6Mfb7IEmQ"
#define BLYNK_TEMPLATE_NAME "Smart Lamp"
#define BLYNK_AUTH_TOKEN "GexKEaiwDQyptqenm7azTV1qLeF3CZbl"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define VIRTUAL_PIN_GAUGE V1
#define VIRTUAL_PIN_THRESHOLD V3
#define VIRTUAL_PIN_SWITCH V0
#define VIRTUAL_PIN_MODE V2

const int ledPin = 15;
const int ldrPin = 35;

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

int threshold = 2500;
bool manualMode = false;
bool manualState = false;

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sendLightIntensity);
}

void sendLightIntensity() {
  int lightIntensity = analogRead(ldrPin);
  int gaugeValue = map(lightIntensity, 0, 4095, 0, 100);
  Blynk.virtualWrite(VIRTUAL_PIN_GAUGE, gaugeValue);

  if (!manualMode) {
    // Mode otomatis
    if (lightIntensity < threshold) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  } else {
    // Mode manual
    digitalWrite(ledPin, manualState ? HIGH : LOW);
  }

  // Output Serial yang lebih rapi
  Serial.println("=== STATUS LAMPU ===");
  Serial.print("Mode         : "); Serial.println(manualMode ? "Manual" : "Otomatis");
  Serial.print("LDR Value    : "); Serial.println(lightIntensity);
  Serial.print("Gauge Value  : "); Serial.println(gaugeValue);
  Serial.print("Lampu        : "); Serial.println(digitalRead(ledPin) ? "Menyala" : "Mati");
  Serial.println("====================\n");
}

// Slider ambang batas cahaya
BLYNK_WRITE(VIRTUAL_PIN_THRESHOLD) {
  threshold = param.asInt();
  Serial.print("Ambang batas cahaya diubah: ");
  Serial.println(threshold);
}

// Switch lampu manual (V0)
BLYNK_WRITE(VIRTUAL_PIN_SWITCH) {
  manualState = param.asInt() == 1;
  Serial.print("Status manual diubah: ");
  Serial.println(manualState ? "ON" : "OFF");

  if (manualMode) {
    digitalWrite(ledPin, manualState ? HIGH : LOW);
  }
}

// Switch mode otomatis/manual (V2)
BLYNK_WRITE(VIRTUAL_PIN_MODE) {
  manualMode = param.asInt() == 1;
  Serial.print("Mode diubah: ");
  Serial.println(manualMode ? "Manual" : "Otomatis");

  if (manualMode) {
    digitalWrite(ledPin, manualState ? HIGH : LOW);
  }
}

void loop() {
  Blynk.run();
  timer.run();
}
