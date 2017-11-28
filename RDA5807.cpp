/* Arduino RDA5800m library 
 * Автор Абушинов Александр Александрович
 * Github https://github.com/3eFiR4ik
 * Email abushinov97@gmail.com
 *
 * За основу была взята библиотека https://github.com/csdexter/RDA5807M
*/

#include "RDA5807.h"

#include "Wire.h"

void RDA5807::begin(void){
  Wire.begin();        
  setRegister(0x02, RDA5807M_FLG_DHIZ | RDA5807M_FLG_DMUTE | 
                RDA5807M_FLG_BASS | RDA5807M_FLG_SEEKUP | RDA5807M_FLG_RDS | 
                RDA5807M_FLG_NEW | RDA5807M_FLG_ENABLE);
};

bool RDA5807::setFrequency(int frequency)  // Функция загрузки частоты настройки в модуль EM5807M.
{
 
  //Serial.print("start ferquency = ");
  //Serial.println(frequency);

  if (frequency < 870 || frequency > 1080){
    //Serial.print("bad ferquency");
    return false;
    }
  frequency = ((frequency*10) - 8700) / 10;

  setRegister(0x03,(frequency << 6) | RDA5807M_FLG_TUNE);
  return true;
  
};

float RDA5807::getFrequency(void){
  int freq = (((getRegister(0x0A) & RDA5800_CHAN_MASK) * 10)+8700)/10;
  int low = freq / 10; 
  int high = freq % 10;
  return low + 0.1 * high;
  };



word RDA5807::updateRegister(word reg, word value) {
  return setRegister(reg,getRegister(reg) & ~value);
};

word RDA5807::setRegister(word reg,const word value) {
  Wire.beginTransmission(0x11);
  Wire.write(reg);
  Wire.write(highByte(value));
  Wire.write(lowByte(value));
  Wire.endTransmission(true);
  return value;
};


word RDA5807::getRegister(word reg) {
   word result;

    Wire.beginTransmission(0x11);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(0x11, 2, true);
    result = (word)Wire.read() << 8;
    result |= Wire.read();
    //Serial.println(result);
    
  return result;
};

int RDA5807::volumeUp(void){
   const byte volume = getRegister(0x05) & RDA5800_VOLUME_MASK;
   if(volume == 15){
    //Serial.println("max volume");
    return volume;
    }

   if (volume == 0){
     unmute();
    }
   //volume++;
   setRegister(0x05,getRegister(0x05) & ~RDA5800_VOLUME_MASK | volume + 1);
   return volume;
  };

int RDA5807::volumeDown(void){
const byte volume = getRegister(0x05) & RDA5800_VOLUME_MASK;
   
   if(volume == 0){
    //Serial.println("min volume");
    mute();
    return volume;
    }
   // Serial.println(volume);
   setRegister(0x05,getRegister(0x05) & ~RDA5800_VOLUME_MASK | volume - 1);
   return volume;
  };

void RDA5807::mute(void){
	updateRegister(0x02,RDA5807M_FLG_DMUTE | RDA5807M_FLG_SEEK);
};

void RDA5807::unmute(void){
	setRegister(0x02,(getRegister(0x02) | RDA5807M_FLG_DMUTE) & ~RDA5807M_FLG_SEEK);
};

void RDA5807::seekUp(void){
	setRegister(0x02,RDA5807M_FLG_DHIZ | RDA5807M_FLG_DMUTE |
                             RDA5807M_FLG_SEEK | RDA5807M_FLG_SEEKUP |
                             RDA5807M_FLG_RDS  | RDA5807M_FLG_NEW | RDA5807M_FLG_ENABLE);
};

void RDA5807::seekDown(void){
	setRegister(0x02,getRegister(0x02) & ~RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK);
};

void RDA5807::off(void){
	 updateRegister(0x02,RDA5807M_FLG_ENABLE);
};

void RDA5807::bassboostOn(void){
  setRegister(0x02,getRegister(0x02) | RDA5800_BASSBOOST_MASK);
};

void RDA5807::bassboostOff(void){
  setRegister(0x02,getRegister(0x02) & ~RDA5800_BASSBOOST_MASK);
};