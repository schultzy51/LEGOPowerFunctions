/*
LEGO Power Functions protocol for the arduino.
20-04-2009
Version 1.1 

Changelist:
 - Changed the timing in oscillationWrite from 13us to 9us.
 - Forgot to set the ir-pin to OUTPUT
 - added support for SingleOutput the "Clear - Set - Toggle"

This code is based on the code of Bob Kojima 01-19-2008

I have modified it to work on the Arduino.

Roland Wiersma
*/

#include "legopowerfunctions.h"

int _IR_Pin;
int toggle[4] = {0, 0, 0, 0};
int delay_code1, delay_code2, messagecount = 0;

LEGOPowerFunctions::LEGOPowerFunctions(int IR_Pin) {
    _IR_Pin = IR_Pin;
    pinMode(IR_Pin, OUTPUT);
}

void LEGOPowerFunctions::SingleOutput(int mode, int step, int output, int channel) {
    int nib1, nib2, nib3, nib4;

    //set nibs
    nib1 = toggle[channel] | channel;
    nib2 = 0x4 | mode | output;
    nib3 = step;
    nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

    message_pause(channel, messagecount);
    pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4);

    if (toggle[channel] == 0)
        toggle[channel] = 8;
    else
        toggle[channel] = 0;
}

void LEGOPowerFunctions::SinglePin(int mode, int function, int pin, int output, int channel) {
    int nib1, nib2, nib3, nib4;

    //set nibs
    nib1 = toggle[channel] | channel;
    nib2 = 0x00 | mode;
    nib3 = output << 4 | pin << 3 | function;
    nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

    message_pause(channel, messagecount);
    pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4);

    if (toggle[channel] == 0)
        toggle[channel] = 8;
    else
        toggle[channel] = 0;
}

void LEGOPowerFunctions::ComboMode(int blue_speed, int red_speed, int channel) {
    int nib1, nib2, nib3, nib4;

    //set nibs
    nib1 = channel;
    nib2 = 0x01;
    nib3 = blue_speed | red_speed;
    nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

    message_pause(channel, messagecount);
    pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4);
}

void LEGOPowerFunctions::ComboPWM(int blue_pwm, int red_pwm, int channel) {
    int nib1, nib2, nib3, nib4;

    //set nibs
    nib1 = 0x4 | channel;
    nib2 = blue_pwm;
    nib3 = red_pwm;
    nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

    message_pause(channel, messagecount);
    pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4);
}

void LEGOPowerFunctions::pf_send(int code1, int code2) {

    if (code1 == delay_code1 && code2 == delay_code2) 
    {
        if (messagecount < 4)
            messagecount++;
    } else 
    {
        delay_code1 = code1;
        delay_code2 = code2;
        messagecount = 0;
    }
	
    cli(); // make it uninterruptable
    start_stop_bit();

    int x = 128;
    while (x) {
        oscillationWrite(_IR_Pin, 156);

        if (code1 & x) //high bit
            delayMicroseconds(546);
        else //low bit
            delayMicroseconds(260);

        x >>= 1; //next bit
    }

    x = 128;
    while (x) {
        oscillationWrite(_IR_Pin, 156);

        if (code2 & x) // high bit
            delayMicroseconds(546);
        else //low bit
            delayMicroseconds(260);

        x >>= 1; //next bit
    }
    start_stop_bit();
    sei();

}

void LEGOPowerFunctions::start_stop_bit() {
    oscillationWrite(_IR_Pin, 156);
    delayMicroseconds(1014);
}

/*
The IR signal is 38Khz
1 pulse is 26 microseconds (1/1.000.000)
So the delay should be 13us, but because of internal delay 9us is more close.
I have timed it with a scope. 13us delay equals about 28khz.
10us is about 35khz. I have not timed 9us but i think its close.
*/
void LEGOPowerFunctions::oscillationWrite(int pin, int time) {
    for (int i = 0; i <= time / 26; i++) {
        digitalWrite(pin, HIGH);
        delayMicroseconds(9);
        digitalWrite(pin, LOW);
        delayMicroseconds(9);
    }
}

void LEGOPowerFunctions::message_pause(int channel, int count) {
    unsigned char a = 0;

    if (count == 0)
        a = 4 - channel;
    else if (count == 1 || count == 2)
        a = 5;
    else if (count == 3 || count == 4)
        a = (6 + 2 * channel);

    delay(a * 16);
}