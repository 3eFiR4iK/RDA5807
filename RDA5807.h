/* Arduino RDA5800m library 
 * Автор Абушинов Александр Александрович
 * Github https://github.com/3eFiR4ik
 * Email abushinov97@gmail.com
 *
 * За основу была взята библиотека https://github.com/csdexter/RDA5807M
*/

#ifndef RDA5807_H
#define RDA5807_H


#if defined(ARDUINO) && ARDUINO >= 100
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

#define RDA5807M_FLG_DHIZ 0x8000
#define RDA5807M_FLG_DMUTE 0x4000
#define RDA5807M_FLG_MONO 0x2000
#define RDA5807M_FLG_BASS 0x1000
#define RDA5807M_FLG_RCLKNOCAL 0x0800
#define RDA5807M_FLG_RCLKDIRECT 0x0400
#define RDA5807M_FLG_SEEKUP 0x0200
#define RDA5807M_FLG_SEEK 0x0100
#define RDA5807M_FLG_SKMODE word(0x0080)
#define RDA5807M_FLG_RDS word(0x0008)
#define RDA5807M_FLG_NEW word(0x0004)
#define RDA5807M_FLG_RESET word(0x0002)
#define RDA5807M_FLG_ENABLE word(0x0001)
#define RDA5807M_FLG_DIRECT word(0x0020)
#define RDA5807M_FLG_TUNE word(0x10)
#define RDA5807M_FLG_DE 0x0800
#define RDA5807M_FLG_SOFTMUTE 0x0200
#define RDA5807M_FLG_AFCD 0x0100
#define RDA5807P_FLG_INTMODE 0x8000
#define RDA5807M_FLG_EASTBAND65M 0x0200
#define RDA5807M_FLG_SOFTBLEND word(0x0002)
#define RDA5807M_FLG_FREQMODE word(0x0001)
#define RDA5807M_FLG_FMTRUE 0x0100
#define RDA5807M_FLG_FMREADY word(0x0080)
#define RDA5807M_FLG_BLOCKE word(0x0010)
#define RDA5807P_FLG_STCIEN 0x4000
#define RDA5807P_FLG_I2S word(0x0040)
#define RDA5807P_FLG_I2SSLAVE 0x1000
#define RDA5807P_FLG_SWLR 0x0800
#define RDA5807P_FLG_SCLKINVERT_I 0x0400
#define RDA5807P_FLG_SIGNED 0x0200
#define RDA5807P_FLG_WSINVERT_I 0x0100
#define RDA5807P_FLG_WSINVERT_O word(0x0008)
#define RDA5807P_FLG_SCLKINVERT_O word(0x0004)
#define RDA5807P_FLG_DELAY_L word(0x0002)
#define RDA5807P_FLG_DELAY_R word(0x0001)
#define RDA5800_FLG_SPACE_200K word(0x0001)
#define RDA5800_FLG_SPACE_50K word(0x0004)
#define RDA5800_FLG_BAND_JAPAN word(0x0002)

#define RDA5800_CHAN_MASK word(0x3FF)
#define RDA5800_VOLUME_MASK word(0x0F)
#define RDA5800_BASSBOOST_MASK word(0x800)

class RDA5807 {

public:

	RDA5807(void) {};

	void begin(void);

	word setRegister(word reg, const word value);

	word getRegister(word reg);

	word updateRegister(word reg, word value);

	bool setFrequency(int frequency);

	float getFrequency(void);

	int volumeUp(void);

	int volumeDown(void);

	void mute(void);

	void unmute(void);

	void bassboostOn(void);

	void bassboostOff(void);

	//void getBassboost(void);

	void seekUp(void);

	void seekDown(void);

	void off(void);


};

#endif

