#include "mbed.h"

DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
Serial pc( USBTX, USBRX );
AnalogIn Ain(A0);
AnalogOut Aout(DAC0_OUT);

int sample = 500;
int i;
float j;
int number= 0;
float ADCdata[500];
int a;

int main(){


    for (i = 0; i < sample; i++){
        ADCdata[i] = Ain;   
        wait(1./sample);
    }
    
    for (i = 0; i < sample; i++){
        pc.printf("%1.3f\r\n", ADCdata[i]);
        wait(0.01);
    }

    for (i = 1; i < sample - 1; i++){
        if (ADCdata[i - 1] < ADCdata[i] && ADCdata[i] > ADCdata[i + 1]) 
            number++;
    }

    while(1){

        if( Switch == 1 ){
            greenLED = 0;
            redLED = 1;
            for( j=0; j<2; j+=0.04 ){
                Aout = 0.5 + 0.5*sin(j*3.14159);
                wait(1./number/50);
            }
        }
        else{
            redLED = 0;
            greenLED = 1;

            
            a = number/100;
            display = table[a];
            wait(1);
            
            a = number%100/10;
            display = table[a];
            wait(1);
            
            a = number%10;
            display = (table[a]|0X80);
            wait(1);

            display = 0X00;
        }
    }

}
