#include "I2COutput.h"
#include <Arduino.h>

I2COutput::I2COutput(uint8_t address, uint8_t maxServos)
    : pwmDriver(address), i2cAddress(address), numServos(maxServos)
{
    servoAngles = new uint8_t[numServos];

    // Initialize all servos to 90 degrees
    for (uint8_t i = 0; i < numServos; i++) {
        servoAngles[i] = 90;
    }
}

I2COutput::~I2COutput() {
    delete[] servoAngles;
}

void I2COutput::begin() {
    Wire.begin();
    pwmDriver.begin();
    pwmDriver.setPWMFreq(50); // Set frequency to 50Hz for servos
}

void I2COutput::moveServo(uint8_t servoId, uint8_t angle) {
    if (servoId == 0 || servoId > numServos) {
        Serial.println("Invalid servo ID for I2C output.");
        return;
    }

    uint8_t index = servoId - 1;
    uint16_t pulse = angleToPulse(angle);
    pwmDriver.setPWM(index, 0, pulse);
    servoAngles[index] = angle;
}

void I2COutput::feedback() {
    Serial.println("I2C Output Feedback:");
    for (uint8_t i = 0; i < numServos; i++) {
        Serial.print("Servo ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(servoAngles[i]);
        Serial.println(" degrees");
    }
}

const char* I2COutput::name() const {
    return "I2C";
}

uint16_t I2COutput::angleToPulse(uint8_t angle) {
    // Map 0-180 degrees to 150-600 pulse length (depends on tuning)
    return map(angle, 0, 180, 150, 600);
}
