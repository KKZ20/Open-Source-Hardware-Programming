#include <Arduino.h>

// int s0, s1, s2, s3;
// int out;
// int flag;
// byte counter;
// byte countR, countG, countB;

// int red, green, blue;

void colorsensor_set_pins(int a, int b, int c, int d, int e);

void colorsensor_read_color(int *a, int *b, int *c);

void TCS(void);

void ISR_INTO(void);

void timer0_init(void);

ISR(TIMER2_OVF_vect);