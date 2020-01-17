#include "marauder.h"

// https://github.com/Reinbert/pca9685/blob/master/examples/servo.c
int calcTicks(float angle)
{
    float cycleMs = 1000.0f / FREQUENCE;
    return (int)(MAX_PWM * map(angle) / cycleMs + 0.5f);
}

/**
 * input is [0..180]
 * output is [0.65..2.05]
 * T_ANGLE_45 1.0f
 * T_ANGLE_90 1.35f
 * T_ANGLE_135 1.7f
 */
float map(float angle) {
  return angle * (2.05 - 0.65) / 180 + 0.65;
}

void init_motor()
{
    // void pinMode (int pin, int mode)
    pinMode(SRM_AVD_1, OUTPUT);
    pinMode(SRM_AVG_1, OUTPUT);
    pinMode(SRM_ARD_1, OUTPUT);
    pinMode(SRM_ARG_1, OUTPUT);

    pinMode(SRM_AVD_2, OUTPUT);
    pinMode(SRM_AVG_2, OUTPUT);
    pinMode(SRM_ARD_2, OUTPUT);
    pinMode(SRM_ARG_2, OUTPUT);

    pinMode(VRM_AVD, OUTPUT);
    pinMode(VRM_AVG, OUTPUT);
    pinMode(VRM_ARD, OUTPUT);
    pinMode(VRM_ARG, OUTPUT);

    // int softPwmCreate (int pin, int initialValue, int pwmRange)
    softPwmCreate(VRM_AVD, 0, 200);
    softPwmCreate(VRM_AVG, 0, 200);
    softPwmCreate(VRM_ARD, 0, 200);
    softPwmCreate(VRM_ARG, 0, 200);
}

void set_servo_motor(int angle)
{
    // Angle servo
    int angleTicksAvant = calcTicks(90 - angle);
    int angleTicksArriere = calcTicks(90 + angle);

    // void pwmWrite (int pin, int value)
    pwmWrite(PIN_AVD, angleTicksAvant);
    pwmWrite(PIN_AVG, angleTicksAvant);
    pwmWrite(PIN_ARD, angleTicksArriere);
    pwmWrite(PIN_ARG, angleTicksArriere);
}

void set_motor(int vitesse, char sens)
{
    // void digitalWrite (int pin, int value)
    switch (sens)
    {
    case 'a': // Avancer
        digitalWrite(SRM_AVD_1, AVANCER_1);
        digitalWrite(SRM_AVD_2, AVANCER_2);

        digitalWrite(SRM_AVG_1, AVANCER_1);
        digitalWrite(SRM_AVG_2, AVANCER_2);

        digitalWrite(SRM_ARD_1, AVANCER_1);
        digitalWrite(SRM_ARD_2, AVANCER_2);

        digitalWrite(SRM_ARG_1, AVANCER_1);
        digitalWrite(SRM_ARG_2, AVANCER_2);
        break;
    case 'r': // Reculer
        digitalWrite(SRM_AVD_1, RECULER_1);
        digitalWrite(SRM_AVD_2, RECULER_2);

        digitalWrite(SRM_AVG_1, RECULER_1);
        digitalWrite(SRM_AVG_2, RECULER_2);

        digitalWrite(SRM_ARD_1, RECULER_1);
        digitalWrite(SRM_ARD_2, RECULER_2);

        digitalWrite(SRM_ARG_1, RECULER_1);
        digitalWrite(SRM_ARG_2, RECULER_2);
        break;
    case 'q': // Gauche
        digitalWrite(SRM_AVD_1, RECULER_1);
        digitalWrite(SRM_AVD_2, RECULER_2);

        digitalWrite(SRM_AVG_1, AVANCER_1);
        digitalWrite(SRM_AVG_2, AVANCER_2);

        digitalWrite(SRM_ARD_1, RECULER_1);
        digitalWrite(SRM_ARD_2, RECULER_2);

        digitalWrite(SRM_ARG_1, AVANCER_1);
        digitalWrite(SRM_ARG_2, AVANCER_2);
        break;
    case 'd': // Droite
        digitalWrite(SRM_AVD_1, AVANCER_1);
        digitalWrite(SRM_AVD_2, AVANCER_2);

        digitalWrite(SRM_AVG_1, RECULER_1);
        digitalWrite(SRM_AVG_2, RECULER_2);

        digitalWrite(SRM_ARD_1, AVANCER_1);
        digitalWrite(SRM_ARD_2, AVANCER_2);

        digitalWrite(SRM_ARG_1, RECULER_1);
        digitalWrite(SRM_ARG_2, RECULER_2);
        break;
    }

    // On utilie les vitesse entre 100 et 200 pour utiliser une puissance de plus de 50%
    for(int i=1; i<vitesse+100; i+=20)
    {
        // void softPwmWrite (int pin, int value)
        softPwmWrite(VRM_AVD, i);
        softPwmWrite(VRM_AVG, i);
        softPwmWrite(VRM_ARD, i);
        softPwmWrite(VRM_ARG, i);

        delay(50);
    }
}

void stop_servo_motor()
{
    pwmWrite(PIN_AVD, 0);
    pwmWrite(PIN_AVG, 0);
    pwmWrite(PIN_ARD, 0);
    pwmWrite(PIN_ARG, 0);
}

void stop_motor()
{
    softPwmStop(VRM_AVD);
    softPwmStop(VRM_AVG);
    softPwmStop(VRM_ARD);
    softPwmStop(VRM_ARG);
}
