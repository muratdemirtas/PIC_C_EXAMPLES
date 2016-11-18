/*
 * Dosya    : 18F4520_7Seg-1.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : 7 Segment LED - 9999 Sayac
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç 7 Segment LED göstergede 9999 a kadar saydýrmaktýr.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            SWDIP9 ve SWDIP üzerindeki 7S-1,7S-2,7S-3,7S-4 anahtarlarý
 *            ON konumunda olmalýdýr.
 */
#include <18F4520.h>

#device adc=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz FOR PCM/PCH) (>10mhz for PCD)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOPBADEN                 //PORTB pins are configured as digital I/O on RESET
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used FOR I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=20000000)

#include <math.h>
#include "EXLCD.C"

#define SEG0COM PIN_A2
#define SEG1COM PIN_A3
#define SEG2COM PIN_A4
#define SEG3COM PIN_A5
#define SEG_DOT PIN_D7

int16 i,tens,ones, hundreds, thousands;
int8 step=0;

byte const LED_MAP[10] = {0x3F,0x06,0x5B,0x4F,0X66,0X6D,0X7D,0X07,0X7F,0X67};

void basla()
{
   for (i = 0; i <= 9999; ++i)
   {
      ones = (i % 10);
      tens = (i / 10) % (10);
      hundreds = (i / 100) % 10;
      thousands = (i / 1000) % 10;

      ones = LED_MAP[ones]; 
      tens = LED_MAP[tens];
      hundreds = LED_MAP[hundreds];
      thousands = LED_MAP[thousands];
      
      if (step<25) ones |= 0x80;
      else
       ones &= 0x7F;
      if (step>25 && step<50) tens |= 0x80;
      else
       tens &= 0x7F;
      if (step>50 && step<75) hundreds |= 0x80;
      else
       hundreds &= 0x7F;
      if (step>75 && step<100) thousands |= 0x80;
      else
       thousands &= 0x7F; 
      
      step++;
      
      if (step>99) step = 0;
      
      output_high (SEG0COM); output_d (ones); delay_ms (5); output_low (SEG0COM);
      output_high (SEG1COM); output_d (tens); delay_ms (5); output_low (SEG1COM);
      output_high (SEG2COM); output_d (hundreds); delay_ms (5); output_low (SEG2COM);
      output_high (SEG3COM); output_d (thousands);delay_ms (5); output_low (SEG3COM);
      delay_us (50);

   }
}

void main()
{
   setup_adc_ports (NO_ANALOGS) ;
   
   WHILE (TRUE)
   {
      basla();
   }
}

