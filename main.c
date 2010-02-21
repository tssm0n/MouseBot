#include "init.h"	// included by C-Wiz
#include <pic.h>
#include "delay.h"
#include "adc.h"

// Left wheel: A0 - EN, A1 - Forward, A2 - Backward
// Right wheel: C5 - EN, C7 - Forward, C6 - Backward
// Right = ADC 11 (B5)
// LEFT = ADC 10 (B4)

// Bump Sensor - B7 (note: use a pull up resistor (10k ohm))			

void followLight(void);
unsigned char isBumped(void);
void allStop(void);
void leftStop(void);
void rightStop(void);
void rightForward(void);
void leftForward(void);
void rightBack(void);
void leftBack(void);
void allBack(void);
void turnRight(void);
void turnLeft(void);


const int turnDuration = 25;
const int straightDuration = 10;

void delayOneSec(void)
{
	DelayMs(200);
	DelayMs(200);
	DelayMs(200);
	DelayMs(200);
	DelayMs(200);	
}

void main(void)
{
	init();	// Function call inserted by C-Wiz
	TRISA = 0;  // Set all A to output
	TRISB = 0b11110000; // Set all B to input 
	TRISC = 0x00;  // Set all C to output 
	ANSELH = 0b00001100; // Set AN11 and AN10 to analog
	
	OPTION &= 0b01111111; // Don't disable internal pull ups
	WPUB |= 0b10000000; // Enable internal pull up on B7
	
	unsigned int iterations = 0;
	
	for(;;){
		if(isBumped() || iterations == 250){
			allBack();
			DelayMs(200);
			DelayMs(200);
			DelayMs(200);
			iterations = 0;
			allStop();
		} else {
			if(iterations % 75 == 0){
				allStop();
				leftForward();
				rightForward();
				DelayMs(200);
			} else {
				followLight();
			}
			iterations++;
		}
	}
}

void followLight(void){
	unsigned int left = 0;
	unsigned int right = 0;

	InitialiseADC();
	left = ReadADC(10);
	DelayMs(10);
	InitialiseADC();
	right = ReadADC(11);

	if(left == right){
		rightForward();
		leftForward();
	}
	if(left > right){
		allStop();
		turnLeft();
	}
	if(right > left){
		allStop();
		turnRight();
	}
}

unsigned char isBumped(){
	return PORTB & 0b10000000;
}

void allBack(){
	leftBack();
	rightBack();
}

void allStop(){
	leftStop();
	rightStop();}

void leftStop(){
	PORTC &= 0b00011111;
}

void rightStop(){
	PORTA &= 0b11111000;
}

void rightBack(){
	rightStop();
	PORTA |= 0b00000011;
}

void leftForward(){
	leftStop();
	PORTC |= 0b01100000;
}

void rightForward(){
	rightStop();
	PORTA |= 0b00000101;
}

void leftBack(){
	leftStop();
	PORTC |= 0b10100000; 
}

void turnRight(){
	leftForward();
	DelayMs(turnDuration);
	rightForward();
	DelayMs(straightDuration);
}

void turnLeft(){
	rightForward();
	DelayMs(turnDuration);
	leftForward();
	DelayMs(straightDuration);
}
