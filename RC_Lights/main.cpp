/*
 * RC_Lights.cpp
 *
 * Created: 15.08.2016 23:32:55
 * Author : Bostjan.Bele
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "CLight.h"
#include "CRemote.h"
#include "RC_Const.h"

int main(void)
{
	// Configure timer0
#if !defined(DEBUG)
	TCCR0A |= (1<<WGM01); // CTC mode
	TCCR0B |= (1<<CS01)|(1<<CS00); // Prescaler 64
	OCR0A = 125-1; // (())
	//	TIMSK |= (1<<OCIE0A);
	sei();
#endif
	CLight frontL(&PORTA, PA0, 0);
	CLight frontR(&PORTA, PA1, 0);
	CLight rearL(&PORTA, PA2, 0);
	CLight rearR(&PORTA, PA3, 0);
	CLight blinkL(&PORTA, PA4, 1000);
	CLight blinkR(&PORTA, PA5, 1000);
	CLight rotatL(&PORTA, PA6, 5, true);
	rotatL.SetLightStrength(milisec, (int8_t)20);
	CLight rotatR(&PORTA, PA7, 5, false);
	rotatR.SetLightStrength(milisec, (int8_t)95);
/*		
#if defined(DEBUG)
	blinkL.SetBlinkStartTime((unsigned int)5000);
	blinkR.SetBlinkStartTime((unsigned int)55000);
	rearL.SetBlinkStartTime((unsigned int)55000);
#endif
*/
	while (1) 
    {

#if defined(DEBUG)
		milisec++;
#endif

/*		frontL.Blink(milisec);
		frontR.Blink(milisec);
		rearL.Blink(milisec);
		rearR.Blink(milisec);
		blinkL.Blink(milisec);
		blinkR.Blink(milisec);
*/		rotatL.Blink(milisec);
		rotatR.Blink(milisec);

#if defined(DEBUG)
		if (milisec > fullTime-1)
		{
			milisec-=fullTime;
		}
#endif
    }
}

#if !defined(DEBUG)
ISR (TIMER0_COMPA_vect)
{
	milisec++;
	// unsigned int has max 65536; limiting to 1 min
	if (milisec > fullTime-1)
	{
		milisec-=fullTime;
	}

}
#endif