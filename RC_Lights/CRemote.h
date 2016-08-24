#ifndef CREMOTE_H_
#define CREMOTE_H_

class CRemote
{
	public:
	CRemote(volatile uint8_t* port, uint8_t pin);
	unsigned int getHighTimePercentage();
	void setStartTime(unsigned int TimeInMs);
	void setMidTime(unsigned int TimeInMs);
	void setStopTime(unsigned int TimeInMs);
	
	private:
	bool isHigh;
	unsigned int startTime; // first rise
	unsigned int midTime; // fall
	unsigned int stopTime; // next rise
	
	volatile uint8_t *m_port;
	volatile uint8_t *m_ddr_port;
	uint8_t m_pin;
};

#endif /* CREMOTE_H_ */