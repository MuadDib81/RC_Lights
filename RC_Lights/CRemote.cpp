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

void CRemote::setHighTimePercentage()
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
		highTimePercentage=0;
	}
	else
	{
		highTimePercentage=(unsigned int)(100*diffStartMid/(diffStartMid+diffMidStop));
	}
}

void CRemote::setStartTime(unsigned int TimeInMs)
{
	startTime=TimeInMs;
}

void CRemote::setMidTime(unsigned int TimeInMs)
{
	midTime=TimeInMs;
}

void CRemote::setStopTime(unsigned int TimeInMs)
{
	stopTime=TimeInMs;
	highTimePercentage=getHighTimePercentage();
	setStartTime(TimeInMs);
}