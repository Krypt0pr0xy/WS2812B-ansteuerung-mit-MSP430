/*
 * Ledtreiber.h
 *
 *  Created on: 30.01.2019
 *      Author: wyler
 */



#ifndef LEDTREIBER_H_
#define LEDTREIBER_H_

#define SPIDIV     0x02                         // 16 MHz/2 gives ~125 ns for each on bit in byte
#define SPILONG    0b11111100                   // 750 ns (acceptable "on" range 550 to 850 ns)
#define SPISHORT   0b11100000                   // 375 ns (acceptable "on" range 200 to 500 ns)

#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4
#define YELLOW 5
#define VIOLETT 6
#define ORANGE 7
#define BLACK 10

#define PIXELS 42
#define TIME 12000

#define X_SIZE 7
#define Y_SIZE 7

void initClock();
void initSPI();
void initWS2812();
void initArray();
void sendByte (unsigned char b);
void sendPixel (unsigned char r, unsigned char g, unsigned char b);
void showColor (unsigned int count, unsigned char r , unsigned char g , unsigned char b);
void pingpong(unsigned char ucFarbeEin, unsigned char ucFarbeAus, unsigned char ucAlpha);
void sendArray();
void show();

void setLed(int iPosition, int iAnzahl, unsigned char ucFarbeEin, unsigned char ucFarbeAus, unsigned char ucAlpha);
void sendColor (unsigned char ucColor, unsigned char ucAlpha);
void sendColorAll (unsigned char ucColor, unsigned char ucAlpha);
void sendArrayRechteck(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue);


#endif /* LEDTREIBER_H_ */
