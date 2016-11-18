///////////////////////////////////////////////////////////////////////////
////                             LCDD.C                                ////
////                 Driver for common LCD modules                     ////
////                                                                   ////
////  lcd_init()   Must be called before any other function.           ////
////                                                                   ////
////  lcd_putc(c)  Will display c on the next position of the LCD.     ////
////                     The following have special meaning:           ////
////                      \f  Clear display                            ////
////                      \n  Go to start of second line               ////
////                      \b  Move back one position                   ////
////                                                                   ////
////  lcd_gotoxy(x,y) Set write position on LCD (upper left is 1,1)    ////
////                                                                   ////
////  lcd_getc(x,y)   Returns character at position x,y on LCD         ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2003 Custom Computer Services           ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////

// As defined in the following structure the pin connection is as follows:
//     D0  enable
//     D1  rs
//     D2  rw
//     D4  D4
//     D5  D5
//     D6  D6
//     D7  D7
//
//   LCD pins D0-D3 are not used and PIC D3 is not used.

// Un-comment the following define to use port B
// #define use_portb_lcd TRUE


/*struct lcd_pin_map {                 // This structure is overlayed
           BOOLEAN enable;           // on to an I/O port to gain
           BOOLEAN rs;               // access to the LCD pins.
           BOOLEAN rw;               // The bits are allocated from
           BOOLEAN unused;           // low order up.  ENABLE will
           int     data : 4;         // be pin B0.
        } lcd;*/

struct lcd_pin_map {                 // This structure is overlayed
   int    data    : 4;         // be pin B0.
   int    rs       : 1;
   int    enable      : 1;
   int    rw      : 1;
   int    en   : 1;      
} lcd;

#define use_portb_lcd

#if defined use_portb_lcd
   #locate lcd = getenv("sfr:PORTB")    // This puts the entire structure over the port
   #define set_tris_lcd(x) set_tris_b(x)
#else
   #locate lcd = getenv("sfr:PORTD")    // This puts the entire structure over the port
   #define set_tris_lcd(x) set_tris_d(x)
#endif


#define lcd_type 2           // 0=5x7, 1=5x10, 2=2 lines
#define lcd_line_two 0x40    // LCD RAM address for the second line


BYTE const LCD_INIT_STRING[4] = {0x20 | (lcd_type << 2), 0xc, 1, 6};
                             // These bytes need to be sent to the LCD
                             // to start it up.


                             // The following are used for setting
                             // the I/O port direction register.

struct lcd_pin_map const LCD_WRITE = {0,0,0,0,0}; // For write mode all pins are out
struct lcd_pin_map const LCD_READ = {0,0,0,0,15}; // For read mode data pins are in



BYTE lcd_read_byte() {
      BYTE low,high;
      set_tris_lcd(LCD_READ);
      lcd.rw = 1;
      delay_cycles(1);
      lcd.enable = 1;
      delay_cycles(1);
      high = lcd.data;
      lcd.enable = 0;
      delay_cycles(1);
      lcd.enable = 1;
      delay_us(1);
      low = lcd.data;
      lcd.enable = 0;
      set_tris_lcd(LCD_WRITE);
      return( (high<<4) | low);
}


void lcd_send_nibble( BYTE n ) {
      lcd.data = n;
      delay_cycles(1);
      lcd.enable = 1;
      delay_us(2);
      lcd.enable = 0;
}


void lcd_send_byte( BYTE address, BYTE n ) {

      lcd.rs = 0;
      //while(bit_test(lcd_read_byte(),7));
     delay_cycles(200);
     delay_cycles(200);
      lcd.rs = address;
      delay_cycles(1);
      lcd.rw = 0;
      delay_cycles(1);
      lcd.enable = 0;
      lcd_send_nibble(n >> 4);
      lcd_send_nibble(n & 0xf);
}


void lcd_init() {
    BYTE i;
    set_tris_lcd(LCD_WRITE);
    lcd.rs = 0;
    lcd.rw = 0;
    lcd.enable = 0;
    delay_ms(15);
    for(i=1;i<=3;++i) {
       lcd_send_nibble(3);
       delay_ms(5);
    }
    lcd_send_nibble(2);
    for(i=0;i<=3;++i)
       lcd_send_byte(0,LCD_INIT_STRING[i]);
}


void lcd_gotoxy( BYTE x, BYTE y) {
   BYTE address;

   if(y!=1)
     address=lcd_line_two;
   else
     address=0;
   address+=x-1;
   lcd_send_byte(0,0x80|address);
}

void lcd_putc( char c) {
   switch (c) {
     case '\f'   : lcd_send_byte(0,1);
                   delay_ms(2);
                                           break;
     case '\n'   : lcd_gotoxy(1,2);        break;
     case '\b'   : lcd_send_byte(0,0x10);  break;
     default     : lcd_send_byte(1,c);     break;
   }
}

char lcd_getc( BYTE x, BYTE y) {
   char value;

    lcd_gotoxy(x,y);
    while ( bit_test(lcd_read_byte(),7) ); // wait until busy flag is low
    lcd.rs=1;
    value = lcd_read_byte();
    lcd.rs=0;
    return(value);
}
