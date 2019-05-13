#include <msp430.h>
#include <string.h>
#include "Ledtreiber.h"

extern union
{
    char cDaten[X_SIZE*Y_SIZE*3];
    struct
    {
        char cGreen;

        char cRed;

        char cBlue;
    }sFarbpunkt[X_SIZE][Y_SIZE];
}uLedMatrix;


int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                     // Stop watchdog timer

  initClock();
  initSPI();
  initWS2812();
  initArray();

  showColor(PIXELS, 0x00, 0x00, 0x00);

  __delay_cycles(600000);

  while(1)
  {
      /***************************************************/
      //Einzelne Pixel nacheinander senden
      //sendPixel(0xBB, 0x00, 0x00);           // red
      //sendPixel(0x00, 0xBB, 0x00);           //
      //sendPixel(0x00, 0xBB, 0x00);           // green
      //sendPixel(0x00, 0x00, 0xBB);           // blue
      //sendPixel(0xBB, 0xBB, 0xBB);           // white
      //sendPixel(0xBB, 0x22, 0x22);           // pinkish
      //sendPixel(0x22, 0xBB, 0x22);           // light green
      //sendPixel(0x22, 0x22, 0xBB);           // purplish blue
      //sendPixel(0x00, 0x00, 0x00);           // pixel off
      //show();



      //Pingpong
      //pingpong(WHITE, BLUE,0x1F);


      //Ganzes Recheck Array senden
      //      sendArrayRechteck(0, 0, 1, 1, 0x1B, 0x00, 0x00);
      //      sendArrayRechteck(5, 0, 6, 1, 0x1B, 0x00, 0x00);
      //      sendArrayRechteck(0, 4, 1, 5, 0x1B, 0x00, 0x00);
      //      sendArrayRechteck(5, 4, 6, 5, 0x1B, 0x00, 0x00);
      //
      //      sendArrayRechteck(2, 0, 4, 5, 0x1B, 0x1B, 0x1B);
      //      sendArrayRechteck(0, 2, 6, 3, 0x1B, 0x1B, 0x1B);
      //      sendArray();

      //int x = 3;
      //int y = 3;
      //uLedMatrix.sFarbpunkt[x][y].cRed = 200;
      //sendArray();

      //sendColorAll(VIOLETT,0xBB);
      //show();
      //__delay_cycles(8000000);
      //sendColorAll(BLUE, 0x1B);

      //sendColorAll(VIOLETT,0xBB);
      //show();
      //showColor(PIXELS, 0x00, 0x00, 0x1B);
      //__delay_cycles(8000000);
      //uLedMatrix.sFarbpunkt[0][0].cRed = 200;
      //uLedMatrix.sFarbpunkt[1][0].cRed = 200;
      //uLedMatrix.sFarbpunkt[2][0].cRed = 200;
      //uLedMatrix.sFarbpunkt[3][0].cRed = 200;
      //uLedMatrix.sFarbpunkt[4][0].cRed = 200;
      //uLedMatrix.sFarbpunkt[5][0].cRed = 200;
      //sendArray();
  }
}