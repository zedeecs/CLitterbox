/*
    程序主干
    作为整个控制系统的逻辑主干
*/

#include <AccelStepper.h>
// Mike McCauley 编写的 AccelStepper 库是一个非常棒的库，
// 可用于您的项目。优点之一是它支持加速和减速，但它也有很多其他不错的功能。

// 电机引脚定义
#define motorPin1 8
#define motorPin2 9
#define motorPin3 10
#define motorPin4 11

//定义AccelStepper接口类型；半步模式下的 4 线电机：
#define MotorInterfaceType 8

int button = 4;
boolean button_state;
unsigned long time_now = 0;

AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{
    pinMode(button, INPUT);
    stepper.setMaxSpeed(1000);
    time_now = millis();
    Serial.begin(9600);
    button_state = LOW;
}

void loop()
{
    button_state = digitalRead(button);
    while (button_state == LOW)
    {
        stepper.disableOutputs();
        button_state = digitalRead(button);
        while (millis() > time_now + 500)
        {
            Serial.println(button_state);
            time_now = millis();
        }
    }
    stepper.setSpeed(600);
    stepper.runSpeed();

    while (millis() > time_now + 500)
    {
        Serial.println(button_state);
        time_now = millis();
    }
}
