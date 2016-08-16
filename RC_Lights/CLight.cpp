#include <avr/io.h>
#include "CLight.h"

CLight::CLight(volatile uint8_t* port, uint8_t pin, unsigned int blinkTime, bool initiallyOn)
{
	m_port = port;
	*m_ddr_port = _BV(pin);
	m_pin = pin;
	
	m_blinkTime = blinkTime;
	
	SetLightOnOff(initiallyOn);
	SetBlinkStartTime((unsigned int)0);
}

void CLight::SetLightOnOff(bool state)
{
	m_lightOn = state;
	
	if (m_lightOn)
	{
		*m_port |= _BV(m_pin);
		m_lightOnStrength=true;
	}
	else
	{
		*m_port &= _BV(m_pin);
	}
}

void CLight::SetLightStrength(unsigned int timeInMs, int8_t strengthInPercent)
{
	m_lightStrengthStartTime=timeInMs;
	m_lightStrength=strengthInPercent;
	if (m_lightStrengthStartTime < m_lightStrengthStartTime-50)
	{
		m_lightStrengthStartTime+=50;
	}
}

void CLight::Blink(unsigned int timeInMs)
{
	if (!(m_blinkTime < 5))
	{
		volatile unsigned int tempTime=0;
	/*
		Get all times inside 1 minute.
		Set tempTime for the calculation when to toggle
	*/
		if (timeInMs < m_blinkStartTime)
		{
			tempTime=timeInMs-m_blinkStartTime+60000;
		}
		else if (timeInMs == m_blinkStartTime)
		{
			tempTime=m_blinkStartTime;
		}
		else
		{
			tempTime=timeInMs-m_blinkStartTime;
		}
		
	//	Toggle LED if the triggered
		if (!((tempTime)%(m_blinkTime/2)))
		{
			if (!m_blinkSet)
			{
				ToggleState();
				m_blinkSet=true; // has to be true if more than one time in 1 milisecond
				m_blinkStartTime=timeInMs;
			}
		}
		else
		{
			if (m_blinkSet)
			{
				m_blinkSet=false; // and set back for the next toggle
			}
		}
	}
	// PWM part - for LED strength
	if (m_lightOn)
	{
		if ((50-((m_lightStrengthStartTime-timeInMs)%50)) < ((uint8_t)(50*m_lightStrength/100)))
		{
			if (m_lightOnStrength == false)
			{
				*m_port |= _BV(m_pin);
			}
			m_lightOnStrength=true;
		}
		else
		{
			if (m_lightOnStrength == true)
			{
				*m_port &= _BV(m_pin);
			}
			m_lightOnStrength=false;
		}
	}
}

bool CLight::ToggleState()
{
	SetLightOnOff(!m_lightOn);
	return m_lightOn;
}