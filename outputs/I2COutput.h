#ifndef I2C_OUTPUT_H
#define I2C_OUTPUT_H

#include "../OutputHandler.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class I2COutput : public OutputHandler {
public:
    I2COutput(uint8_t address = 0x40, uint8_t maxServos = 16);
    ~I2COutput();

    void begin() override;
    void moveServo(uint8_t servoId, uint8_t angle) override;
    void feedback() override;
    const char* name() const override;

private:
    Adafruit_PWMServoDriver pwmDriver;
    uint8_t i2cAddress;
    uint8_t numServos;
    uint8_t* servoAngles;

    uint16_t angleToPulse(uint8_t angle);
};

#endif // I2C_OUTPUT_H
