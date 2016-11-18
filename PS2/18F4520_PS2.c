/*
 * Dosya    : 18F4520_PS2.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : PS2 Klavye uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : 18F4520
 * Kristal  : 20Mhz (MCU FOSC 48Mhz)
 * Kit      : EX8
 * Açýklama : PS2 Klavye giriþinden okunan bilgiyi LCD ekranda gösterir.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanicilari;
 *            -SWDIP6 (SW5-6) RX TX ON
 *            olmalidir.
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

#include <EXLCD.C>

//D0 - Clock
//D1 - Data


// Clock must be the interrupt pin
#define CLOCK PIN_B0
#define DATA  PIN_E2
#define KEYCLK PIN_B0
#define KEYDATA  PIN_E2
unsigned char bData[16];
unsigned char idx=0;
unsigned char tmp=0;

unsigned char readByte();
unsigned char processByte();
unsigned char waitKey();
byte keyhit();
unsigned char translate(unsigned char scancode);




volatile byte shiftSet = 0;

byte kbBuffer[16];
byte kbPos = 0;
byte kbSize = 0;
byte capsSet = 0;
volatile byte extFlag = 0;
volatile byte relFlag = 0;
volatile byte key=0;

void sendByte(byte b)
{
    byte a=0;
    byte p = 0;
    boolean t = 0;

  //  return;         // THIS IS NOT FULLY WORKING ON ALL KEYBOARDS
                    // SO IT IS COMMENTED OUT
                    // Some kind of timing issue or something. Whatever, they're just LEDs

    disable_interrupts(GLOBAL);
    output_low(KEYCLK);
    delay_us(80);
  //  input(KEYCLK);
    output_low(KEYDATA);
    output_high(KEYCLK);
    input(KEYCLK);

    for(a=0; a<8; a++)
    {
        while(input(KEYCLK) == 1); //wait for 0
        t = bit_test(b,a);
        output_bit(KEYDATA, t);
        if(t)
            p++;
        while(input(KEYCLK) == 0); //wait for 1
    }

    while(input(KEYCLK) == 1); //wait for 0
    t = bit_test(p,0);
        t = ~t;
    while(input(KEYCLK) == 0); //wait for 1
     output_bit(KEYDATA, t);   // input(KEYDATA);
    while(input(KEYCLK) == 1); //wait for 0
  ///  while(input(KEYCLK) == 0); //wait for 1
     output_float(KEYDATA);
    enable_interrupts(GLOBAL);
} 

main()
{
    int i=0;
    unsigned char k=0;
    lcd_init();
    delay_ms(100);
 //   printf(lcd_putc,"READY >");

    output_b(0x00);
    input(CLOCK);

    delay_ms(100);

    ext_int_edge(H_to_L);
    enable_interrupts(INT_EXT);
    enable_interrupts(GLOBAL);

    while(TRUE)
    {
       k = waitKey();
        printf(lcd_putc,"%c", k);

      while(keyhit())
        {
           k = waitKey();
           // lcd_gotoxy(1,1);
           printf(lcd_putc,"%c", k);
        }
        
        
    }
}

byte keyhit()
{
    return kbSize != 0;
}

unsigned char waitKey()
{
    unsigned char k = 0;
    while(kbSize == 0);
    k = kbBuffer[(kbPos - kbSize)&0x0F];
    kbSize--;
    return k;
}

#int_ext
void kbInterrupt()
{
    volatile byte k=0;
    disable_interrupts(GLOBAL);
    k = processByte();
    //lcd_gotoxy(1,1);
    printf(lcd_putc,"Byte: %x",k);

    if(k != 0)
    {
        kbBuffer[kbPos] = k;
        kbPos = ++kbPos & 0x0F;
        kbSize++;
    }
    enable_interrupts(GLOBAL);
    return;
}

unsigned char readByte()
{
    int i=0, t=0;
    idx=0;
    tmp=0;

    i=0;
    goto dataread;
   // while(INPUT(CLOCK) != 0);   // Wait for a keypress
            t=0;
       while(INPUT(CLOCK) != 0 && t<255)   // Wait for clock, time out if needed
       {
           delay_us(1);
           t++;
       }
    for(i=0; i<11; i++)
    {
        t=0;
        while(INPUT(CLOCK) != 0 && t<255)   // Wait for clock, time out if needed
        {
            delay_us(1);
            t++;
        }
        dataread:

        bData[idx]=INPUT(DATA);
        idx++;
        if(idx==9)
        {
            for(idx=1; idx<9; idx++)
                if(bData[idx]!=0)
                    tmp|=(1<<(idx-1));

            return tmp;
            idx=0;
            tmp=0;
        }
     //   while(INPUT(CLOCK) == 0);
        t=0;
        while(INPUT(CLOCK) == 0 && t<255)   // Wait for clock, time out if needed
        {
            delay_us(1);
            t++;
        }

    }
}

static const unsigned char scantableAZ[]={
0x1C, 0x32, 0x21, 0x23, 0x24, 0x2B, 0x34, 0x33, 0x43, 0x3B, 0x42, 0x4B, 0x3A, // A-Z
0x31, 0x44, 0x4D, 0x15, 0x2D, 0x1B, 0x2C, 0x3C, 0x2A, 0x1D, 0x22, 0x35, 0x1A};


// Normal numeric scancodes, starting with ',' .
static const unsigned char scantable09n[]=
{
0x41, 0x4E, 0x49, 0x4A, // , - . /
0x45, 0x16, 0x1E, 0x26, 0x25, 0x2E, 0x36, 0x3D, 0x3E, 0x46,     //Digits 0-9
0x00, 0x4C, 0x00, 0x55 // 0 ; 0 =
};

// Shift scancodes, starting at '!'
static const unsigned char scantable09s[]=
{
    0x16, 0x52, 0x26, 0x25, 0x2E, 0x3D, 0x00, 0x46, 0x45, 0x3E, 0x55
};

// Normal misc. scancode map. Scancode, ASCII value
static const unsigned char scanmapn[]=
{0x54, '[', 0x5B, ']', 0x0E, '`', 0x5D, '\\', 0x52, '\''};

// Shifted misc. scancode map. Scancode, ASCII value
static const unsigned char scanmaps[]=
{0x1E, '@', 0x36, '^', 0x4E, '_', 0x54, '{', 0x5B, '}', 0x5D, '|',
0x4C, ':', 0x41, '<', 0x49, '>', 0x4A, '?', 0x0E, '~'};


// Scancode map independent of Shift
static const unsigned char scanmapx[]=
{0x29, ' ', 0x5A, '\r', 0x0D, '\t', 0x76, 27, 0x66, 0x08};

// Extended scancode map
static const unsigned char scanmape[]=
{
0x71, 0x7F
};

unsigned char translate(unsigned char scancode)
{
    int i=0;

    if(extFlag == 0)
    {
        for(i=0; i<10; i+=2)
            if(scanmapx[i] == scancode)
                return scanmapx[i+1];

        for(i=0; i<26; i++)
            if(scantableAZ[i] == scancode)
                if(shiftSet ^ capsSet)
                    return i+65;
                else
                    return i+65 + 32;

        if(shiftSet)
        {
            for(i=0; i<11; i++)
                if(scantable09s[i] == scancode)
                    return i+'!';

            for(i=0; i<22; i+=2)
                if(scanmaps[i] == scancode)
                    return scanmaps[i+1];
        } else
        {
            for(i=0; i<18; i++)
                if(scantable09n[i] == scancode)
                    return i+',';

            for(i=0; i<10; i+=2)
                if(scanmapn[i] == scancode)
                    return scanmapn[i+1];
        }
    } else      // Extended keys
    {
        for(i=0; i<2; i+=2)
            if(scanmape[i] == scancode)
                return scanmape[i+1];
    }
    return '?';
}

unsigned char processByte()
{
    unsigned char i, j;
    i = readByte();

    if(i == 0xF0)       //A key is being released
    {
        relFlag = 1;
        return 0;
    }

    if(i == 0xE0)       // Extended key operation
    {
        extFlag = 1;
        relFlag = 0;    //0xE0 always first in sequence, OK to clear this
        return 0;
    }

    if(relFlag == 0)    // Pressing a key
    {
        if(extFlag == 0)    // Non-extended key pressed
        {
            if(i == 0x12 || i == 0x59)
            {
                shiftSet = 1;
                return 0;
            }

            if(i == 0x58)
            {
                sendByte(0xED);
                if(capsSet == 0)
                {
                    capsSet = 1;
                    sendByte(0x04);
                } else
                {
                    capsSet = 0;
                    sendByte(0x00);
                }
                return 0;
            }


        }
        j = translate(i);
        extFlag = 0;
        return j;
    }

    if(relFlag == 1)    //Releasing a key
    {
        relFlag = 0;    //If a flag was set but not handled, we wouldn't have gotten here
        extFlag = 0;    //OK to clear this here

        if(extFlag == 0)   // Releasing a nonextended key
        {
            if(i == 0x12 || i == 0x59)
            {
                shiftSet = 0;
                return 0;
            }

        }
//        } else              // Releasing an extended key
//        {
//            return 0;
//        }

//        return 0;
    }
    return 0;
} 
