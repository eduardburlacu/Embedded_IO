#include "mbed.h"
#include <cstdio>

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
InterruptIn button(USER_BUTTON);


void select_led(int l){
        if (l==0) {
                led1 = false;
                led2 = false;
                led3 = false;
        }
        else if (l==1) {
                led1 = true;
                led2 = false;
                led3 = false;
        }
        else if (l==2) {
                led1 = false;
                led2 = true;
                led3 = false;
        }
        else if (l==3) {
                led1 = false;
                led2 = false;
                led3 = true;
        }
    }

int j=0; //start led
int q=0; //current input order
int N=7; //length of sequence                                //change here the number to allow for a bigger/smaller sequence
int led_cycle[7]; //container for sequence                   //change here the number to allow for a bigger/smaller sequence
int current=0; //counter after the sequence is given
Timeout event_timeout;
float timeout_interval=0.25;                                 //change here the interrupt sensitivity
float T=1.0;                                                 //change here blinking rate
void TIMEOUT_CALLBACK(void);
void ON_BUTTON_PRESS(void){
    led_cycle[q]=j;
    button.rise(NULL);
    event_timeout.attach(TIMEOUT_CALLBACK, timeout_interval);
    }
void TIMEOUT_CALLBACK(void){
    q++;
    if (q<N){button.rise(ON_BUTTON_PRESS);}
    }
Ticker io_ticker;
void TICKER_CALLBACK(void)
    {
    if(q<N){
        j=(j%3)+1;
        select_led(j);
        }
    else if (q==N){
        select_led(led_cycle[current]);
        current = (current+1)%N;
        }
    }

int main() {
    button.rise(ON_BUTTON_PRESS);
    io_ticker.attach(TICKER_CALLBACK,T);
    return 0;
}