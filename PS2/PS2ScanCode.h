/*
************************************************************************************************************
*                        Embedded Systems Building Blocks
*                        PS/2 Keyboard 101/104 keys driver
*
*               Original obtained from www.picant.com, C2C complier web site
*                  by Julio Cesar Silva Briano, modified by John Leung
*
* Filenmae       : ps2ScanCode.h
* Programmer    : John Leung, www.TechToys.com.hk under Downloads Section.
* Version      : Version 1.1 - 17th June 2004
* Remarks      : Consult www.beyong.org for PS/2 keyboard protocol
*            
************************************************************************************************************
*                                 DESCRIPTION
* Three lookup tables PS2KeyUnshifted[], PS2KeyShifted[], and PS2KeyNumPad[] map PS2Key_Code to ASCII chars
* If it is going to be the Numpad ONLY, PS2KeyUnshifted[] and PS2KeyShifted[] can be undefined to save ROM
* PS2KeyNumPad[] provided for ASCII character map for Num pad, should choose % #define PS2_NUM_PAD_SCH1/2
* Application must declare PS2ScanCode.h if ASCII should be returned
************************************************************************************************************
*/


/*
************************************************************************************************************
                                 SCAN CODE TABLE
************************************************************************************************************
*/

/*
*****************************************************
*                                          *
*   No-Shift - Lookup Table when Shift not hold     *
*                                          *
*****************************************************
*/

//Uncomment the following #define if a full 104 keyboard ASCII map is included
//#define PS2_FULL_104KEY

#ifdef PS2_FULL_104KEY

const INT8U PS2KeyUnshifted[]={

0x00,   //00
0x00,   //01  F9
0x00,   //02
0x00,   //03  F5
0x00,   //04  F3
0x00,   //05  F1
0x00,   //06  F2   
0x00,   //07  F12
0x00,   //08
0x00,   //09  F10
0x00,   //0A  F8
0x00,   //0B  F6
0x00,   //0C  F4
0x09,   //0D  TAB
'`',   //0E  ` or ~
0x00,   //0F

0x00,   //10
0x00,   //11  Left ALT
0x00,   //12  Left SHIFT
0x00,   //13
0x00,   //14  Left Ctrl
'q',   //15  Q
'1',   //16  1 or !
0x00,   //17
0x00,   //18
0x00,   //19
'z',   //1A  Z
's',   //1B  S
'a',   //1C  A
'w',   //1D  W
'2',   //1E  2 or @
0x00,   //1F

0x00,   //20
'c',   //21  C
'x',   //22  X
'd',   //23  D
'e',   //24  E
'4',   //25  4 or $
'3',   //26  3 or #
0x00,   //27
0x00,   //28
' ',   //29  Space
'v',   //2A  V
'f',   //2B  F
't',   //2C  T
'r',   //2D  R
'5',   //2E  5 or %
0x00,   //2F

0x00,   //30
'n',   //31  N
'b',   //32  B
'h',   //33  H
'g',   //34  G
'y',   //35  Y
'6',   //36  6 or ^
0x00,   //37
0x00,   //38
0x00,   //39
'm',   //3A  M
'j',   //3B  J
'u',   //3C  U
'7',   //3D  7 or &
'8',   //3E  8 or *
0x00,   //3F

0x00,   //40
',',   //41  , or <
'k',   //42  K
'i',   //43  I
'o',   //44  O
'0',   //45  0 or )
'9',   //46  9 or (
0x00,   //47
0x00,   //48
'.',   //49  . or >
'/',   //4A  / or ?
'l',   //4B  L
';',   //4C  ; or :
'p',   //4D  P
'-',   //4E  - or _
0x00,   //4F

0x00,   //50
0x00,   //51
0x27,   //52  ' or "
0x00,   //53
'[',   //54  [ or {
'=',   //55  = or +
0x00,   //56
0x00,   //57
0x00,   //58  Caps Lock
0x00,   //59  Right Shift
0x0D,   //5A  Enter
']',   //5B  ] or }
0x00,   //5C
'\'',   //5D  \ or |
0x00,   //5E
0x00,   //5F

0x00,   //60
0x00,   //61
0x00,   //62
0x00,   //63
0x00,   //64
0x00,   //65
0x08,   //66  Backspace
0x00,   //67
0x00,   //68
'1',   //69  NUM - 1 or END
0x00,   //6A
'4',   //6B  NUM - 4 or LEFT
'7',   //6C  NUM - 7 or HOME
0x00,   //6D
0x00,   //6E
0x00,   //6F

'0',   //70  NUM - 0 or INS
'.',   //71  NUM - . or DEL
'2',   //72  NUM - 2 or DOWN
'5',   //73  NUM - 5
'6',   //74  NUM - 6 or RIGHT
'8',   //75  NUM - 8 or UP
0x1B,   //76  ESC
0x00,   //77  NUM LOCK
0x00,   //78  F11
'+',   //79  NUM - + (Plus)
'3',   //7A  NUM 3 or PAGE DOWN
'-',   //7B  NUM - - (Minus)
'*',   //7C  NUM - *
'9',   //7D  NUM - 9 or PAGE UP
0x00,   //7E  SCROLL LOCK
0x00,   //7F

0x00,   //80
0x00,   //81
0x00,   //82
0x00,   //83  F7
};

/*
*****************************************************
*                                                   *
*   Shift - Lookup Table Used when Shift Hold       *
*                                                   *
*****************************************************
*/

const INT8U PS2KeyShifted[]={
     0x00   //00
     0x00   //01  F9
     0x00   //02
     0x00   //03  F5
     0x00   //04  F3
     0x00   //05  F1
     0x00   //06  F2
     0x00   //07  F12
     0x00   //08
     0x00   //09  F10
     0x00   //0A  F8
     0x00   //0B  F6
     0x00   //0C  F4
     0x09   //0D  TAB
     '~'   //0E  ` or ~
     0x0   //0F

     0x00   //10
     0x00   //11  Left ALT
     0x00   //12  Left SHIFT
     0x00   //13
     0x00   //14  Left Ctrl
     'Q'   //15  Q
     '!'   //16  1 or !
     0x00   //17
     0x00   //18
     0x00   //19
     'Z'   //1A  Z
     'S'   //1B  S
     'A'   //1C  A
     'W'   //1D  W
     '@'   //1E  2 or @
     0x00   //1F

     0x00   //20
     'C'   //21  C
     'X'   //22  X
     'D'   //23  D
     'E'   //24  E
     '$'   //25  4 or $
     '#'   //26  3 or #
     0x00   //27
     0x00   //28
     ' '   //29  Space
     'V'   //2A  V
     'F'   //2B  F
     'T'   //2C  T
     'R'   //2D  R
     '%'   //2E  5 or %
     0x00   //2F

     0x00   //30
     'N'   //31  N
     'B'   //32  B
     'H'   //33  H
     'G'   //34  G
     'Y'   //35  Y
     '^'   //36  6 or ^
     0x00   //37
     0x00   //38
     0x00   //39
     'M'   //3A  M
     'J'   //3B  J
     'U'   //3C  U
     '&'   //3D  7 or &
     '*'   //3E  8 or *
     0x00   //3F

     0x0   //40
     '<'   //41  , or <
     'K'   //42  K
     'I'   //43  I
     'O'   //44  O
     ')'   //45  0 or )
     '('   //46  9 or (
     0x00   //47
     0x00   //48
     '>'   //49  > or .
     '?'   //4A  / or ?
     'L'   //4B  L
     ':'   //4C  ; or :
     'P'   //4D  P
     '_'   //4E  - or _
     0x00   //4F

     0x00   //50
     0x00   //51
     0x22   //52  ' or "
     0x00   //53
     '{'   //54  [ or {
     '+'   //55  = OR +
     0x00   //56
     0x00   //57
     0x00   //58  Caps Lock
     0x00   //59  Right Shift
     0x0D   //5A  Enter
     '}'   //5B  ] or }
     0x00   //5C
     '|'   //5D  \ or |
     0x00   //5E
     0x00   //5F

     0x00   //60
     0x00   //61
     0x00   //62
     0x00   //63
     0x00   //64
     0x00   //65
     0x08   //66  Backspace
     0x00   //67
     0x00   //68
     '1'   //69  NUM - 1 or END
     0x00   //6A
     '4'   //6B  NUM - 4 or LEFT
     '7'   //6C  NUM - 7 or HOME
     0x00   //6D
     0x00   //6E
     0x00   //6F

     '0'   //70  NUM - 0 or INS
     '.'   //71  NUM - . or DEL
     '2'   //72  NUM - 2 or DOWN
     '5'   //73  NUM - 5
     '6'   //74  NUM - 6 or RIGHT
     '8'   //75  NUM - 8 or UP
     0x1B   //76  ESC
     0x00   //77  NUM LOCK
     0x00   //78  F11
     '+'   //79  NUM - + (Plus)
     '3'   //7A  NUM 3 or PAGE DOWN
     '-'   //7B  NUM - - (Minus)
     '*'   //7C  NUM - *
     '9'   //7D  NUM - 9 or PAGE UP
     0x00   //7E  SCROLL LOCK
     0x00   //7F

     0x00   //80
     0x00   //81
     0x00   //82
     0x00   //83  F7
};

#endif


/*
*****************************************************
*                                                   *
*   Numeric KeyPad only - Lookup Table             *
*                                                   *
*****************************************************
*/

//Uncomment the following #define if NumPad is used
//Should use a Decode() sub-routine to decode the array index.
//This method for Flash Rom space saving

//#define PS2_NUM_PAD_SCH1

#ifdef PS2_NUM_PAD_SCH1

const INT8U PS2KeyNumPad[17] ={0x70, 0x69, 0x72, 0x7A, 0x6B, 0x73, 0x74, 0x6C,\
                        0x75, 0x7D, 0x79, 0x7B, 0x7C, 0x4A, 0x71, 0x5A, 0x77};
 
/*
   Array index
       0   //70           NUM - 0 or INS   
      1   //69           NUM - 1 or END
        2   //72           NUM - 2 or DOWN
        3   //7A           NUM - 3 or PAGE DOWN
        4   //6B           NUM - 4 or LEFT   
        5   //73           NUM - 5
        6   //74           NUM - 6 or RIGHT
        7   //6C           NUM - 7 or HOME
        8   //75           NUM - 8 or UP
        9   //7D           NUM - 9 or PAGE UP
        10   //79           NUM - + (Plus)
      11   //7B           NUM - - (Minus)
      12   //7C           NUM - *
      13  //4A or E04A     NUM - /(division), extended code ignore here
      14   //71           NUM - . or DEL
      15  //5A or E05A    NUM - ENT, extended code ignore here
        16   //77           NUM LOCK
*/
#endif


/*
******************************************************
*                                                      *
*   Numeric KeyPad only - Lookup Table to ASCII      *
*   Remarks: NumLock is mapped to 0x77 in this table *
******************************************************
*/

//Uncomment the following #define if NumPad is used
//Should choose between PS2_NUM_PAD_SCH1 or SCH2
//Should shift by 0x4A to map the ASCII character

#define PS2_NUM_PAD_SCH2
#ifdef    PS2_NUM_PAD_SCH2
#define OFFSET_SCH2      0x4A
const INT8U PS2KeyNumPad[] = {
'/',   //4A  / or ?
'l',   //4B  L
';',   //4C  ; or :
'p',   //4D  P
'-',   //4E  - or _
0x00,   //4F

0x00,   //50
0x00,   //51
0x27,   //52  ' or "
0x00,   //53
'[',   //54  [ or {
'=',   //55  = or +
0x00,   //56
0x00,   //57
0x00,   //58  Caps Lock
0x00,   //59  Right Shift
0x0D,   //5A  Enter
']',   //5B  ] or }
0x00,   //5C
'\'',   //5D  \ or |
0x00,   //5E
0x00,   //5F

0x00,   //60
0x00,   //61
0x00,   //62
0x00,   //63
0x00,   //64
0x00,   //65
0x08,   //66  Backspace
0x00,   //67
0x00,   //68
'1',   //69  NUM - 1 or END
0x00,   //6A
'4',   //6B  NUM - 4 or LEFT
'7',   //6C  NUM - 7 or HOME
0x00,   //6D
0x00,   //6E
0x00,   //6F

'0',   //70  NUM - 0 or INS
'.',   //71  NUM - . or DEL
'2',   //72  NUM - 2 or DOWN
'5',   //73  NUM - 5
'6',   //74  NUM - 6 or RIGHT
'8',   //75  NUM - 8 or UP
0x1B,   //76  ESC
0x77,   //77  NUM LOCK
0x00,   //78  F11
'+',   //79  NUM - + (Plus)
'3',   //7A  NUM 3 or PAGE DOWN
'-',   //7B  NUM - - (Minus)
'*',   //7C  NUM - *
'9',   //7D  NUM - 9 or PAGE UP
};
#endif

