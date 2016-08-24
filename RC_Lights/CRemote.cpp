#include <avr/io.h>
#include "CRemote.h"
#include "RC_Const.h"

CRemote::CRemote(volatile uint8_t* port, uint8_t pin)
{
	isHigh=false;
	startTime=0;
	midTime=0;
	stopTime=0;

	m_port = port;
	m_ddr_port = port - 1;
	*m_ddr_port |= (1<<pin);
	m_pin = pin;
}

unsigned int CRemote::getHighTimePercentage()
{
	unsigned int diffStartMid;
	unsigned int diffMidStop;
		
	if (midTime > startTime)
	{
		diffStartMid=midTime-startTime;
	}
	else
	{
		diffStartMid=fullTime-startTime+midTime;
	}
		
	if (stopTime > midTime)
	{
		diffMidStop=stopTime-midTime;
	}
	else
	{
		diffMidStop=fullTime-midTime+stopTime;
	}
	
	if (diffMidStop==diffStartMid)
	{
		return 0;
	}
	else
	{
		return (unsigned int)(100*diffStartMid/(diffStartMid+diffMidStop));
	}
}

void CRemote::setStartTime(unsigned int TimeInMs)
{
	
}

void CRemote::setMidTime(unsigned int TimeInMs)
{
	
}

void CRemote::setStopTime(unsigned int TimeInMs)
{
	
}