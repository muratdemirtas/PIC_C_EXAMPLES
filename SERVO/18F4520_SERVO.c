/*
 * Dosya    : 18F4520_SERVO.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : Servo motor kullaným Uygulamasi
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz (MCU FOSC 20Mhz)
 * Kit      : EX8
 * Açýklama : J21 headerýna takýlan servo motorun sürülmesini gösterir. D0, D1 ve
 *            D2 butonlarý ile motor sað, sol ve orta pozisyonlara alýnýr.
 *           
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanicilari;
 *            - SWDIP7 üzerindeki DS18-SR (SW8) ON konumunda olmalýdýr.
 *            - SWDIP8 üzerindeki PORTD (SW4) ON konumunda olmalýdýr.
 */
#include <18F4520.h>
#device adc=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=20000000)

#include "EXLCD.C"

#define SERVO_PIN  PIN_A5


//==========================================
void main()
{
    setup_adc_ports (NO_ANALOGS);
    setup_adc (ADC_OFF);
    lcd_init();
    delay_ms (100);
    printf(lcd_putc,"\fD2 <  D1  >D0");
    while (1)
    {
        if (input (PIN_D1) == 1)
        {
            lcd_gotoxy(1,2);
            printf(lcd_putc, "Ortada Sabit");
            output_high (SERVO_PIN);
            delay_us (1500);
            output_low (SERVO_PIN);
            delay_us (18500);
        }

        if (input (PIN_D0) == 1)
        {
            lcd_gotoxy(1,2);        
            printf(lcd_putc, "Saga hareket");
            output_high (SERVO_PIN);
            delay_us (1000);
            output_low (SERVO_PIN);
            delay_us (19000);
        }

        if (input (PIN_D2) == 1)
        {
            lcd_gotoxy(1,2);        
            printf(lcd_putc, "Sola hareket");
            output_high (SERVO_PIN);
            delay_us (2000);
            output_low (SERVO_PIN);
            delay_us (18000);
        }
    }
}

