#include "Ledtreiber.h"
#include <msp430.h>
#include <string.h>


union                                      //array Matrix Definieren
{
    char cDaten[X_SIZE*Y_SIZE*3];
    struct
    {
        char cGreen;

        char cRed;

        char cBlue;
    }sFarbpunkt[X_SIZE][Y_SIZE];
}uLedMatrix;


//Lauflicht mit Farbeein FArbeaus und Die Helligkeit
void pingpong(unsigned char ucFarbeEin, unsigned char ucFarbeAus, unsigned char ucAlpha)
{
      int iA=0;
      int iB=0;
      //const int TIME = 20;

      for(iA=0;iA!= PIXELS;iA++)                            //Ausschalt senden f�r PingPong
      {
          for(iB=0;iB!=iA;iB++)
          {
              sendColor(ucFarbeAus, ucAlpha);
          }
          sendColor(ucFarbeEin, ucAlpha);
          show();
          __delay_cycles((unsigned long)TIME * 100);
      }

      for(iA=PIXELS-2;iA!= 0;iA--)                            //Einschalt senden f�r PingPong
            {
                for(iB=0;iB!=iA;iB++)
                {
                    sendColor(ucFarbeAus, ucAlpha);
                }
                sendColor(ucFarbeEin, ucAlpha);

                for(iB=0;iB!=iA+1;iB++)                      //Ausschalt senden f�r PingPong
                {
                    sendColor(ucFarbeAus, ucAlpha);
                }

                show();
                __delay_cycles((unsigned long)TIME * 100);
            }
      sendColorAll (ucFarbeAus, ucAlpha);
      __delay_cycles((unsigned long)TIME * 100);
}


//Leds an Beschtimten Ort setzten mit Farbein Farbe aus und Helligkeit
void setLed(int iPosition, int iAnzahl, unsigned char ucFarbeEin, unsigned char ucFarbeAus, unsigned char ucAlpha)
{
    int x=0;
    for(x=0; (iPosition-1) != x; x++)
    {
        sendColor(ucFarbeAus,ucAlpha);
    }
    for(x=0; (iAnzahl) != x; x++)
    {
        sendColor(ucFarbeEin,ucAlpha);
    }

    for(x=0;  (PIXELS-(iPosition-iAnzahl)) != x; x++)
    {
        sendColor(ucFarbeAus,ucAlpha);
    }

    show();
    __delay_cycles(600000);
}

void sendArrayRechteck(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue)
{
    unsigned char a = 0;
    unsigned char b = 0;
    for(a=x1; a<=x2; a++)
    {
        for(b=y1; b<=y2; b++)
        {
            uLedMatrix.sFarbpunkt[b][a].cRed = ucRed;
            uLedMatrix.sFarbpunkt[b][a].cGreen = ucGreen;
            uLedMatrix.sFarbpunkt[b][a].cBlue = ucBlue;
        }
    }
}



void initClock()
{
    BCSCTL1 = CALBC1_16MHZ;                   // load calibrated data
    DCOCTL = CALDCO_16MHZ;
}

void initSPI()
{
    P1SEL = BIT1 + BIT2 + BIT4;
    P1SEL2 = BIT1 + BIT2 + BIT4;
    UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
    UCA0CTL1 |= UCSSEL_2;                         // SMCLK
    UCA0BR0 |= SPIDIV;                            // clock divider (/2)
    UCA0BR1 = 0;                                  //
    UCA0MCTL = 0;                                 // No modulation
    UCA0CTL1 &= ~UCSWRST;                         // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                              // Enable USCI0 RX interrupt
}

// Sends one byte to the LED strip by SPI.
void sendByte (unsigned char b)
{
    unsigned char bit;
    for (bit = 0; bit < 8; bit++){
      if (b & 0x80)                 // is high-order bit set?
          UCA0TXBUF = SPILONG;     // long on bit (~700 ns) defined for each clock speed
      else
          UCA0TXBUF = SPISHORT;    // short on bit (~350 ns) defined for each clock speed
      b <<= 1;                      // shift next bit into high-order position
    }
}




// Send a single pixel worth of information.  Turn interrupts off while using.
void sendPixel (unsigned char r, unsigned char g, unsigned char b)
{
    sendByte (g);        // NeoPixel wants colors in green-then-red-then-blue order
    sendByte (r);
    sendByte (b);
}

void sendColor (unsigned char ucColor, unsigned char ucAlpha)
{
    if(ucColor == RED){sendByte(0x00); sendByte(ucAlpha); sendByte(0x00);}

    if(ucColor == GREEN){sendByte(ucAlpha); sendByte(0x00); sendByte(0x00);}

    if(ucColor == BLUE){sendByte(0x00); sendByte(0x00); sendByte(ucAlpha);}

    if(ucColor == WHITE){sendByte(ucAlpha); sendByte(ucAlpha); sendByte(ucAlpha);}

    if(ucColor == YELLOW){sendByte(ucAlpha); sendByte(ucAlpha); sendByte(0x00);}

    if(ucColor == VIOLETT){sendByte(0x00); sendByte(ucAlpha); sendByte(ucAlpha);}

    if(ucColor == ORANGE){sendByte((ucAlpha)/2); sendByte(ucAlpha); sendByte(0x00);}

    if(ucColor == BLACK){sendByte(0x00); sendByte(0x00); sendByte(0x00);}
}

void sendColorAll (unsigned char ucColor, unsigned char ucAlpha)
{
    if(ucColor == RED){showColor(PIXELS, ucAlpha, 0x00, 0x00);}

    if(ucColor == GREEN){showColor(PIXELS, 0x00, ucAlpha, 0x00);}

    if(ucColor == BLUE){showColor(PIXELS, 0x00, 0x00, ucAlpha);}

    if(ucColor == WHITE){showColor(PIXELS, ucAlpha, ucAlpha, ucAlpha);}

    if(ucColor == YELLOW){showColor(PIXELS, ucAlpha, ucAlpha, 0x00);}

    if(ucColor == VIOLETT){showColor(PIXELS, ucAlpha, 0x00, ucAlpha);}

    if(ucColor == ORANGE){showColor(PIXELS, ucAlpha, (ucAlpha)/2, 0x00);}

    if(ucColor == BLACK){showColor(PIXELS, 0x00, 0x00, 0x00);}
}





// Display a single color on the whole string.  Turn interrupts off while using.
void showColor (unsigned int count, unsigned char r , unsigned char g , unsigned char b)
{
    unsigned int pixel;
    for (pixel = 0; pixel < count; pixel++){
        sendPixel (r, g, b);
    }
    show();
}

// latch the colors
void show()
{
    __delay_cycles(72);            // 9 micro seconds
}

void initWS2812()
{
    show ();                       // in case MOSI went high, latch in whatever-we-sent
    sendPixel (0, 0, 0);           // now change back to black
    show ();                       // and latch that
}

void initArray()                    //Array Initialiesieren
{
    memset(uLedMatrix.cDaten,
           0x00,
           sizeof(uLedMatrix));
}

void sendArray()                    //Array Senden
{
    unsigned char i = 0;
    for(i=0; i<(sizeof(uLedMatrix));i++)
        {
            sendByte(uLedMatrix.cDaten[i]);
        }
}
