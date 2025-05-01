#include "PWMOutput.h"
#include <Arduino.h>

// Default servo pins if not specified otherwise
const uint8_t PWMOutput::defaultServoPins[] = {11, 10, 9, 6};

PWMOutput::PWMOutput(uint8_t maxServos)
    : numServos(maxServos)
{
    servos = new Servo[numServos];
    servoAngles = new uint8_t[numServos];

    // Initialize angles to 90 (neutral position)
    for (uint8_t i = 0; i < numServos; i++) {
        servoAngles[i] = 90;
    }
}

PWMOutput::~PWMOutput() {
    delete[] servos;
    delete[] servoAngles;
}

void PWMOutput::begin() {
    for (uint8_t i = 0; i < numServos; i++) {
        if (i < sizeof(defaultServoPins)) {
            servos[i].attach(defaultServoPins[i]);
        } else {
            // No pin assigned, skip
        }
    }
}

void PWMOutput::moveServo(uint8_t servoId, uint8_t angle) {
    if (servoId == 0 || servoId > numServos) {
        Serial.println("Invalid servo ID for PWM output.");
        return;
    }

    uint8_t index = servoId - 1; // IDs start from 1
    servos[index].write(angle);
    servoAngles[index] = angle;
}

void PWMOutput::feedback() {
    Serial.println("PWM Output Feedback:");
    for (uint8_t i = 0; i < numServos; i++) {
        Serial.print("Servo ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(servoAngles[i]);
        Serial.println(" degrees");
    }
}

const char* PWMOutput::name() const {
    return "PWM";
}
