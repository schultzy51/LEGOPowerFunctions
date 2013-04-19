LEGO Power Functions IR Library
===============================


History
-------

Based on code of Bob Kojima 01-19-2008 further modified by Roland Wiersma

Original link is dead: http://www.rjw.speedxs.nl/arduino/LEGOPowerFunctions.rar
Mirror: http://basbase.com/robocam/LEGOPowerFunctions.zip

I was planning on creating my own library to control LEGO Power Functions using
an IR LED attached to an arduino and/or Raspberry pi but I found this as a
starting point.  The library seems to have been written prior to V1.0 of the
Arduino software since it references WProgram.h.  Other than this single zip
file I have found only a few references of this library and it's original
author.


Library Documentation
---------------------

    //SinglePin & SingleOutput modes
    #define CONTINUOUS 0x2
    #define TIMEOUT 0x3
    #define PWM 0x0
    #define CST 0x2 //Clear - Set - Toggle

    //ComboPWM & SingleOutput pwm steps
    #define PWM_FLT 0x0
    #define PWM_FWD1 0x1
    #define PWM_FWD2 0x2
    #define PWM_FWD3 0x3
    #define PWM_FWD4 0x4
    #define PWM_FWD5 0x5
    #define PWM_FWD6 0x6
    #define PWM_FWD7 0x7
    #define PWM_BRK 0x8
    #define PWM_REV7 0x9
    #define PWM_REV6 0xA
    #define PWM_REV5 0xB
    #define PWM_REV4 0xC
    #define PWM_REV3 0xD
    #define PWM_REV2 0xE
    #define PWM_REV1 0xf

    //SingleOutput Clear - Set - Toggle steps
    #define CL_C1_CL_C2 0x0
    #define ST_C1_CL_C2 0x1
    #define CL_C1_ST_C2 0x2
    #define ST_C1_ST_C2 0x3
    #define INC_PWM 0x4
    #define DEC_PWM 0x5
    #define FULL_FWD 0x6
    #define FULL_REV 0x7
    #define TOG_FWD_REV 0x8

    //ComboMode steps
    #define RED_FLT 0x0
    #define RED_FWD 0x1
    #define RED_REV 0x2
    #define RED_BRK 0x3
    #define BLUE_FLT 0x0
    #define BLUE_FWD 0x4
    #define BLUE_REV 0x8
    #define BLUE_BRK 0xC

    //channels
    #define CH1 0x0
    #define CH2 0x1
    #define CH3 0x2
    #define CH4 0x3

    //SinglePin & SingleOutput output
    #define RED 0x0
    #define BLUE 0x1

    //SinglePin functions
    #define NO_CHANGE 0x0
    #define CLEAR 0x1
    #define SET 0x2
    #define TOGGLE 0x3

    //SinglePin pin
    #define PIN_C1 0x0
    #define PIN_C2 0x1

    PowerFunctions(int IR_Pin);
    void SingleOutput(int mode, int step, int output, int channel);
    void SinglePin(int mode, int function, int pin, int output, int channel);
    void ComboMode(int blue_speed, int red_speed, int channel);
    void ComboPWM(int blue_pwm, int red_pwm, int channel);
