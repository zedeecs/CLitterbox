/*
    程序主干
    作为整个控制系统的逻辑主干

    2022.11.2
    实现了3个功能按键，分别是旋转，清洁，home限位
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

int button = 12;
int homeBtn = 5;
int homePot = 6; // 定义近端点
int endPot = 7;  // 定义远端点，目前是测试作用
int button_state = LOW;
int homePot_state = LOW;
int endPot_state = LOW;

unsigned long time_now = 0;

AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{
    pinMode(button, INPUT);
    pinMode(homePot, INPUT);
    pinMode(endPot, INPUT);
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
    time_now = millis();
    Serial.begin(9600);
    // home();
}

void loop()
{
    button_state = digitalRead(button);
    endPot_state = digitalRead(endPot);
    homePot_state = digitalRead(homePot);

    while (button_state == HIGH)
    {
        stepper.setSpeed(850);
        stepper.runSpeed();
        button_state = digitalRead(button);
        // 当按钮电平低时，电机不动
        while (millis() > time_now + 2000)
        {
            Serial.print("button PUSH");
            Serial.print(endPot_state);
            Serial.println(homePot_state);
            Serial.println(stepper.currentPosition());
            time_now = millis();
        }
    }

    // 跳出循环后，电机动作
    stepper.disableOutputs();

    while (millis() > time_now + 2000)
    {
        Serial.println("button PULL");
        Serial.println(stepper.currentPosition());
        time_now = millis();
    }

    if (endPot_state == HIGH)
    {
        // stepper.setSpeed(850);
        // stepper.runToNewPosition(2000);
        // stepper.runToNewPosition(1000);
        // stepper.runToNewPosition(0);
        clearMovement();
    }
}

void home()
{
    stepper.setSpeed(300);
    homePot_state = digitalRead(homePot);

    Serial.println(homePot_state);
    Serial.println(digitalRead(homePot));

    while (homePot_state == LOW)
    {
        // 识别限位触发
        homePot_state = digitalRead(homePot);
        stepper.runSpeed();
        Serial.println(stepper.currentPosition());

        // 超时
        /* while (millis() > time_now + overtime)
        {
            break;
        } */
        // Serial.println("run" + millis());
    }
    stepper.setCurrentPosition(0);
}

void clearMovement()
{
    // home();
    stepper.setSpeed(850);
    stepper.runToNewPosition(8000);

    for (int i = 0; i < 3; i++)
    {
        stepper.runToNewPosition(5000);
        stepper.runToNewPosition(8000);
    }

    stepper.runToNewPosition(9000);
    stepper.runToNewPosition(5);
}