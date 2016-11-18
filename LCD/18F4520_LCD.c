/*
 * Dosya    : 18F4520_LCD.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : 16x2 Karakter LCD Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : 16x2 LCD sürülerek ekranda animasyon ile bilgi gösterilir.
 *
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *			  SWDIP10 üzerindeki SW5 LCD_LED ON konumunda olmalýdýr.
 *			  
 */
#include <18F4520.h>
#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=20000000)

#include <EXLCD.C> // Mutlaka yukarýdaki tanýmlamalardan sonra eklenmelidir.

static char *msg={"16x2 Karakter LCD Demo                  "};
   
void main()
{
   int dir=0;
   char *pstr=&msg+1;
   
   lcd_init();
   delay_ms(100);
   
   printf(lcd_putc,"www.expkits.com");

   while(TRUE)
   {
      lcd_gotoxy(1,2);
      printf(lcd_putc,pstr);
      
      if (dir==0)
         pstr++;
      else
         pstr--;

      if (pstr-&msg>=16)
         dir=1;
   
      if (pstr-&msg<1)
      {
         pstr=&msg+1;
         dir=0;
      }
      delay_ms(500);      
   }

}
