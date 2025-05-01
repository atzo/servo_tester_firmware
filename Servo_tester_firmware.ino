#include "OutputHandler.h"
#include "outputs/PWMOutput.h"
#include "outputs/I2COutput.h"

enum class InputMode {
    IMSERIAL,
    IMANALOG
};

// Globals
String currentCommand = "";
OutputHandler* currentOutput = nullptr;
InputMode currentInputMode = InputMode::IMANALOG;

PWMOutput pwmOutput;          // PWM output instance (default 4 servos)
I2COutput i2cOutput(0x40, 16); // I2C output instance for PCA9685 (address 0x40)

const uint8_t potPins[] = {A0, A1, A2, A3};

void setup() {
    Serial.begin(115200);
    // Start with PWM as default output
    currentOutput = &pwmOutput;
    currentOutput->begin();
    Serial.println("System Initialized. Default Output: PWM");
}

void loop() {
    if (currentInputMode == InputMode::IMANALOG) {
         readAnalogAndMoveServos();
    }
    updateInputs();
    updateOutputs();
}

void serialEvent() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        if (inChar == '\n') {
            currentCommand.trim();
            handleSerialCommand(currentCommand);
            currentCommand = "";
        } else {
            currentCommand += inChar;
        }
    }
}

void handleSerialCommand(const String& command) {
    if (command.startsWith("switch")) {
        handleSwitchCommand(command);
    } else if (command.startsWith("get")) {
        handleGetCommand(command);
    } else if (command.indexOf(',') > 0) {
        handleMoveServoCommand(command);
    } else {
        Serial.println("Unknown command");
    }
}

void handleSwitchCommand(const String& command) {
    if (command.indexOf("output") > 0) {
        if (command.indexOf("pwm") > 0) {
            currentOutput = &pwmOutput;
            currentOutput->begin();
            Serial.println("Switched output to PWM");
        } else if (command.indexOf("i2c") > 0) {
            currentOutput = &i2cOutput;
            currentOutput->begin();
            Serial.println("Switched output to I2C");
        } else {
            Serial.println("Unknown output type");
        }
    } else if (command.indexOf("input") > 0) {
        if (command.indexOf("serial") > 0) {
            currentInputMode = InputMode::IMSERIAL;
            Serial.println("Switched input to Serial");
        } else if (command.indexOf("analog") > 0) {
            currentInputMode = InputMode::IMANALOG;
            Serial.println("Switched input to Analog (Potentiometers)");
        } else {
            Serial.println("Unknown input type");
        }
    } else {
        Serial.println("Unknown switch command");
    }
}

void handleGetCommand(const String& command) {
    if (currentOutput) {
        currentOutput->feedback();
    }
}

void handleMoveServoCommand(const String& command) {
    int separatorIndex = command.indexOf(',');
    if (separatorIndex < 0) return;

    uint8_t servoId = command.substring(0, separatorIndex).toInt();
    uint8_t angle = command.substring(separatorIndex + 1).toInt();

    if (currentOutput) {
        currentOutput->moveServo(servoId, angle);
    }
}

void readAnalogAndMoveServos() {
    for (uint8_t i = 0; i < 4; i++) { // assuming 4 pots/servos
        int potValue = analogRead(potPins[i]);
        uint8_t angle = map(potValue, 0, 1023, 0, 180);
        if (currentOutput) {
            currentOutput->moveServo(i + 1, angle);
        }
    }
}

void updateInputs() {
    // (reserved for future input updates like analog reading if needed)
}

void updateOutputs() {
    // (reserved for future output updates if needed)
}
