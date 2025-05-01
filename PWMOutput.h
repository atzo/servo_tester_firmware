#ifndef PWM_OUTPUT_H
#define PWM_OUTPUT_H

#include "OutputHandler.h"
#include <Servo.h>

class PWMOutput : public OutputHandler {
public:
    PWMOutput(uint8_t maxServos = 4);
    ~PWMOutput();

    void begin() override;
    void moveServo(uint8_t servoId, uint8_t angle) override;
    void feedback() override;
    const char* name() const override;

private:
    Servo* servos;
    uint8_t numServos;
    uint8_t* servoAngles;

    static const uint8_t defaultServoPins[];
};

#endif // PWM_OUTPUT_H
