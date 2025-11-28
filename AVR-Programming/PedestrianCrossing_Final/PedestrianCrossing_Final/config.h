#ifndef CONFIG_H_
#define CONFIG_H_

//Clock Frequency
#define F_CPU 16000000UL

//LED lights
#define RED 0
#define YLW 1
#define GRN 2

//Switch + Motor
#define SWITCH 0
#define MTR_P1 1
#define MTR_P2 2

//Delays
#define DLY_RED 5
#define DLY_YLW 3
#define DLY_GRN 5
#define DLY_MTR 5
#define DLY_WAIT 10

//74HC595 Pins
#define SDI 5
#define SCLK 4
#define LOAD 3

#endif /* CONFIG_H_ */