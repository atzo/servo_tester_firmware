#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include <stdint.h>

// Abstract Base Class for Output Handlers
class OutputHandler {
public:
    virtual ~OutputHandler() {}

    // Initialize the output
    virtual void begin() = 0;

    // Move a specific servo
    virtual void moveServo(uint8_t servoId, uint8_t angle) = 0;

    // Provide feedback (optional)
    virtual void feedback() = 0;

    // Return friendly name for output selection
    virtual const char* name() const = 0;
};

#endif // OUTPUT_HANDLER_H
