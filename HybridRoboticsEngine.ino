/**
 * Project: Autonomous Environmental Waste-Management System 
 * Framework: Finite State Machine (FSM) for Real-Time Logic
 */

#include <NewPing.h>
#include <DHT.h>

// --- Hardware Abstraction Layer (HAL) ---
#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DIST 200
#define MOTOR_R_F 5
#define MOTOR_R_B 6
#define DHT_PIN 2
#define DHT_TYPE DHT22

// --- System Objects ---
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);
DHT dht(DHT_PIN, DHT_TYPE);

// --- State Definitions ---
enum RobotState { IDLE, NAVIGATING, EVADING, DATA_LOGGING };
RobotState currentState = IDLE;

void setup() {
    Serial.begin(115200); // High-speed baud for low-latency debugging
    dht.begin();
    pinMode(MOTOR_R_F, OUTPUT);
    // Add other motor pins here
    currentState = NAVIGATING;
    Serial.println(">>> SYSTEM_BOOT: Autonomous Navigation Logic Loaded.");
}

void loop() {
    // 1. Perception: Sensor Fusion
    int dist = sonar.ping_cm();
    float temp = dht.readTemperature();

    // 2. Decision: State Machine Logic
    switch (currentState) {
        case NAVIGATING:
            if (dist > 0 && dist < 25) currentState = EVADING;
            else moveForward();
            break;

        case EVADING:
            performEvasiveManeuver();
            if (dist > 30 || dist == 0) currentState = NAVIGATING;
            break;
            
        case DATA_LOGGING:
            transmitTelemetry(temp);
            currentState = NAVIGATING;
            break;
    }

    // 3. Asynchronous Data Pipeline: Log every 10 seconds
    static unsigned long lastLog = 0;
    if (millis() - lastLog > 10000) {
        currentState = DATA_LOGGING;
        lastLog = millis();
    }
}

// --- Actuation Functions ---
void moveForward() {
    digitalWrite(MOTOR_R_F, HIGH);
    Serial.println("[NAV] Path Clear: Driving.");
}

void performEvasiveManeuver() {
    digitalWrite(MOTOR_R_F, LOW);
    Serial.println("[WARN] Obstacle: Re-calculating Vector.");
}

void transmitTelemetry(float t) {
    Serial.print("[DATA] Telemetry Uplink: Temp=");
    Serial.println(t);
}
