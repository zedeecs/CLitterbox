/*
    程序主干
    作为整个控制系统的逻辑主干
*/

#include <Stepper.h>

const int stepsPerRevolution = 2048;

Stepper stepper_28BYJs = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup()
{
    // Set the speed to 5 rpm;
    stepper_28BYJs.setSpeed(15);

    Serial.begin(9600);
}

void loop()
{
    // Step one revolution in one direction;
    Serial.println("clockwise");
    stepper_28BYJs.step(stepsPerRevolution);
    // delay(500);

    // Serial.println("counterclockwise");
    // stepper_28BYJs.step(stepsPerRevolution);
    // delay(500);
}