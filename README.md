# Smart Lamp Control with ESP32 and Blynk

This project is a simple IoT-based lighting system using an ESP32 microcontroller and Blynk platform. It allows automatic and manual control of a lamp based on real-time light intensity from an LDR sensor.

## 🔧 Features

- **Automatic Mode**: Lamp turns ON/OFF based on LDR light intensity and a user-defined threshold.
- **Manual Mode**: Users can directly control the lamp from the Blynk app.
- **Real-time Monitoring**: Light intensity is displayed on a gauge widget.
- **Custom Threshold**: Users can adjust the sensitivity threshold via a slider on Blynk.

## 🧠 How It Works

- ESP32 reads analog value from the LDR sensor.
- If the system is in **automatic mode**, it compares the sensor value to the threshold to decide whether to turn the lamp ON or OFF.
- If in **manual mode**, lamp status is controlled by a switch on the Blynk app.
- Light intensity is mapped to a percentage and sent to Blynk via virtual pin.

## 📱 Blynk Virtual Pins

| Widget        | Pin | Description                 |
|---------------|-----|-----------------------------|
| Switch        | V0  | Manual lamp ON/OFF          |
| Mode Toggle   | V2  | Auto / Manual mode switch   |
| Threshold     | V3  | Light intensity threshold   |
| Gauge         | V1  | Display current LDR reading |

## 🔩 Hardware Used

- ESP32 Dev Board
- LDR Sensor
- Resistor 10KΩ
- LED
- Jumper Wires
- (Simulated on Wokwi)

## 🚀 Getting Started

1. Clone this repo.
2. Open the `.ino` file in Arduino IDE.
3. Install necessary libraries:
   - Blynk
   - WiFi
4. Replace the BLYNK_AUTH_TOKEN with your own from Blynk.
5. Upload to your ESP32 and monitor via Serial.

## 💡 Note

This project was developed and tested using the [Wokwi](https://wokwi.com/) simulation platform. No physical hardware is required to run the simulation.


## 📄 License

This project is open-source and free to use for educational purposes.
