/*
 * Dosya    : 18F4520_RF433_RX_TX.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : RF433 UART Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : RF433 RX ve TX modüller kullanýlarak veri aktarýmýnýn saðlanmasýdýr.
 *            D7 butonuna basýldýðý zaman TX modül üzerinden sinyal gönderilir.
 *            Gönderilen sinyal RX modül tarafýndan alýnarak UART RX interruptý tetiklenir.
 *            Okunan veride 'X' yani 0x58 deðerine rastlanmýþ ise D0 Ledi o anki durumuna
 *            göre açýlýr yada kapanýr. D1 ledi RX modülü sinyal aldýðý sürece iletiþimin sürdüðünü
 *            gösterecek þekilde 1sn aralýklarla yanýp sönen bir ikaz ýþýðý durumundadýr.
 *            Haberleþme kesilirse sönecektir.
 *
 * Uyarýlar : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanýcýlarý;
 *            - SWDIP7 üzerindeki RX ve TX (SW1-2) anahtarlarýný ON konumuna almalýdýr.
 *            - SWDIP8 üzerinde sadece PORTD anahtarý (SW4) ON konumunda olmalýdýr.
 *            - Bu kod RXN3-B Rev1.0 ve TXC1 Rev.01 modülleri ile test edilmiþtir.
 *            - Her iki modülde EX8 üzerine takýlacaktýr.
 *            - Bu kod ile ayný anda TX ve RX modüler test edilmektedir.
 *            - Modüller arasý fiziksel bir sinyal baðlantýsý yoktur.
 *            - Modüller beslemeyi ortak kaynaktan alýr ancak veri iletimi havadan gerçekleþir.
 */

#include <18F4520.h>
#device adc=16
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz FOR PCM/PCH) (>10mhz for PCD)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used FOR I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#use delay(clock=20000000)
#use rs232(baud=2000, rcv=PIN_C7, xmit=PIN_C6)
#include "EXLCD.C"

#int_rda
void serial_isr(){
   output_toggle(PIN_D1);
   if (getc()=='X')
   {
    output_toggle(PIN_D0);
   }
} 

void main()
{
   lcd_init () ;
   delay_ms (100) ;
   lcd_gotoxy(1, 1);
   printf(lcd_putc, "www.expkits.com  ");
   delay_ms(3000);
   WHILE (TRUE)
   {
        if (input(PIN_D7)==1) {
            lcd_gotoxy(1, 1);
            printf(lcd_putc, "Veri Gonderildi   ");
            putc(0x55);
            putc(0x55);
            putc(0x55);
            putc('X');
        } else {
            lcd_gotoxy(1, 1);
            printf(lcd_putc,"Bosta bekliyor.  ");
            putc(0x99);
            putc(0x99);
            putc(0x99);
        };
        delay_ms(500);
   }
}

