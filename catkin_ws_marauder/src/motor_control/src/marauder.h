#ifndef MARAUDER_H_INCLUDE
#define MARAUDER_H_INCLUDE

#include <iostream>
#include <softPwm.h>
#include <wiringPi.h>

#define AVANCER_1 1
#define RECULER_1 0

#define AVANCER_2 0
#define RECULER_2 1

// pca9685
#define PIN_BASE 300
#define MAX_PWM 4096
#define FREQUENCE 50

// Servo - Brancher sur pca9685
#define PIN_AVG PIN_BASE
#define PIN_AVD PIN_BASE + 1
#define PIN_ARG PIN_BASE + 2
#define PIN_ARD PIN_BASE + 3

// Moteur ARD
#define SRM_ARD_1 0  // Port 11
#define SRM_ARD_2 2  // Port 13
#define VRM_ARD 3    // Port 15

// Moteur AVD
#define SRM_AVD_1 21  // Port 29
#define SRM_AVD_2 22  // Port 31
#define VRM_AVD 26    // Port 32

// Moteur AVG
#define SRM_AVG_1 23  // Port 33
#define SRM_AVG_2 24  // Port 35
#define VRM_AVG 25    // Port 37

// Moteur ARG
#define SRM_ARG_1 27  // Port 36
#define SRM_ARG_2 28  // Port 38
#define VRM_ARG 29    // Port 40

int calcTicks(float impulseMs, int hertz);
float map(float angle);
void init_motor();
void set_servo_motor(int angle);
void set_motor(int vitesse, char sens);
void stop_servo_motor();
void stop_motor();

#endif
