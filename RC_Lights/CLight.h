#ifndef CLIGHT_H_
#define CLIGHT_H_

class CLight
{
	public:
	CLight(volatile uint8_t* port, uint8_t pin, unsigned int blinkTime=0, bool initiallyOn=true);
	
	bool GetLightOn();
	void SetLightOnOff(bool state);
	void SetBlinkStartTime(unsigned int timeInMs);
	void SetLightStrength(unsigned int timeInMs, int8_t strengthInPercent);
	void Blink(unsigned int timeInMs);
	bool ToggleState(); // returns the new state
	
	private:
	bool m_lightOn;
	bool m_blinkSet;
	unsigned int m_blinkTime;
	unsigned int m_blinkStartTime;
	unsigned int m_lightStrengthStartTime;
	int8_t m_lightStrength;
	bool m_lightOnStrength;
	int arg1;
	int arg2;
	
	volatile uint8_t *m_port;
	volatile uint8_t *m_ddr_port;
	uint8_t m_pin;
};

#endif /* CLIGHT_H_ */