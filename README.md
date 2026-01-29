## 🧠 System Architecture: Finite State Machine (FSM)
This project moves away from standard 'If/Else' scripting to a robust FSM architecture:
- **NAVIGATING:** Default state; moves forward while polling ultrasonic data.
- **EVADING:** Triggered at <25cm; halts actuation to recalculate safe vectors.
- **DATA_LOGGING:** Asynchronous state for transmitting DHT22 climate metrics.

### 🛠️ Hardware Requirements
- Arduino / ATmega328P
- HC-SR04 Ultrasonic Sensor
- DHT22 Temperature/Humidity Sensor
- L298N Motor Driver

