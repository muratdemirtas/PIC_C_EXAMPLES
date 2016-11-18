/*
 * Dosya    : 18F4520_Blink.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : LED Test Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : A0 ledini yakýp söndürür.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 için;
 *			  -SWDIP8 üzerindeki PORTA-E anahtarý ON konumunda olmalýdýr.
 */
#include <18F4520.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#FUSES HS   // High speed crystal

#use delay(clock=20000000)

#define LED PIN_A0
#define DELAY 500

void main()
{
   //Example blinking LED program
   while(true)
   {
      output_low(LED);
      delay_ms(DELAY);
      output_high(LED);
      delay_ms(DELAY);
   }

}
