/*
  Driver for I2C MBS74T1AEF controlled RF-Modulator

  Easy to use and very straight forward class to control RF-modulator modules 
  via I2C with build-in MBS74T1AEF controller, such as:
  - Shenzhen Tena TNF0170U722
  - Samsung RMUP74055AD 
  
  CopyLight (c) 2019 codebeat, Erwin Haantjes, http://codebeat.nl

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copylight notice, this
     list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  ATTENTION:
  ---------
  THIS SOFTWARE IS PROVIDED BY THE COPYLIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  VERSION history:
  - Date    : 04-sep-2019 (v1.00)
    updated : 18-sep-2018 
              - Optimize some code to make it compile smaller

  
  FEATURES:
  ---------
  o Converts composite video and audio to a RF (aerial) signal;
  o Configurable I2C address;
  o Set channel/frequency (48 Channels - 471 to 855 Mhz UHF)
  o Set sound carrier (5.5 to 6.5 Mhz);
  o Set test-mode (test signal with black background and two white
    stripes and 1Khz test-tone); 
  o begin() (turn on) and end() (turn off) function; 
  o Easy next and previous set functions with rollover protection;
  o Get status (not working).
   
  
  USAGE EXAMPLE:
  --------------
   rfmod.begin();
   rfmod.setChannel(72);
   rfmod.end();

  
  PINOUT:
  -------
  I2C RF-Modulator, I2C address 0x65
  Shenzhen Tena TNF0170U722:
  LEFT SIDE VIEW                              FRONT VIEW
  ____________________                         ____________________
  |     _      _      |____                   |IN  ___     ___ OUT|
  |____| |____| |_____|    |                  |__ /   \__ /   \___|
  |                   |    |        PINS ON   |  | (@) | |  o  |  |
  |  _______________  |____|        THIS SIDE |   \___/   \___/   |
  | |  o o o o o o  | |              ---------|___________________|
  -----|-|-|-|-|-|----|                       |___________________|
       | | | | | |
       | | | | | |_______ +5V      
       | | | | |_________ VIDEO-IN -------[TRIMPOT 10K]--| VIDEO-IN 
       | | | |___________ AUDIO-IN -------[TRIMPOT 10K]--| AUDIO-IN
       | | |_____________ B+ 5V           |-----------------------|
       | |_______________ SDA ____________|_o SDA    ANY ARDUINO  |
       |__________________SCL ______________o SCL                 |
                                          |_______________________| 
  
  NOTICE: 
  o Be aware that competitor Samsung RMUP74055AD (or equavalent) have another order 
    pinout comparing to the Shenzhen Tena TNF0170U722. Refer to datasheet for
    more details;
  o Pull-up resistor on both I2C lines   ----[ 4K7 ]---- +5V required. Without these 
    it will not function!  
  o [TRIMPOT 10K] is an adjustment potentiometer, trimpot for input. These pots needs 
    to set first (calibration) to be able to get decent quality video and audio. 
    However, the audio trimpot is optional (didn't notice any distortion); 
  o Older TV equipment (analog tuning) can handle only one of the lower frequencies 
    (5.5 or lower). Using a non supported frequency will result in poor picture quality
    and audio quality (noise or no audio);
  o TV equipment with a digital tuner (and auto-scan) can handle almost all frequencies 
    (highest = best quality). However, once the channel is discovered by TV equipment, 
    changing the sound carrier will result in poor picture quality and sound quality. 
    In order to change the sound carrier, you need to set the sound carrier first on 
    the device and after this perform an auto-scan on TV equipment.
  o At default the sound carrier is set to 5.5Mhz to cover most TV equipment and
    to provide maximum compatibility. 
  
 
  SUPPORT
  -------
  Love this software? Consider a donation (in future),
  grateful for any kind of support.

  codebeat channels (maybe work in progress):
  - http://www.codebeat.nl             ; Main website
  - http://blog.codebeat.nl            ; Blog website (projects and more)
  - http://youtube.codebeat.nl         ; YouTube channel (shortcut)
  - http://patreon.codebeat.nl         ; Patreon support channel (shortcut)   
  - http://github.codebeat.nl          ; Github (projects)
*/

#ifndef TINYRFMODULATORLIB_H
#define TINYRFMODULATORLIB_H


#define TRFM_DEF_I2C_ADDRESS          0x65 // Default slave address

 // Sound Carrier Ids for setSoundCarrierId() function
#define TRFM_SOUND_CARRIER_MIN        0x00
#define TRFM_SOUND_CARRIER_4_5MHZ     0x00
#define TRFM_SOUND_CARRIER_5_5MHZ     0x01
#define TRFM_SOUND_CARRIER_6_0MHZ     0x02
#define TRFM_SOUND_CARRIER_6_5MHZ     0x03
#define TRFM_SOUND_CARRIER_MAX        0x03
#define TRFM_SOUND_CARRIER_MULTIPLIER 0x08
#define TRFM_SOUND_CARRIER_CURRENT    0x40
#define TRFM_SOUND_CARRIER_NEXT       0x41
#define TRFM_SOUND_CARRIER_PREV       0x42

#define TRFM_STATUS_OFF               0x00
#define TRFM_STATUS_ON                0x01
#define TRFM_STATUS_ERROR             -0x01

#define TRFM_CHANNEL_MIN              21  
#define TRFM_CHANNEL_MAX              69
#define TRFM_CHANNEL_CURRENT          0x80
#define TRFM_CHANNEL_NEXT             0x81
#define TRFM_CHANNEL_PREV             0x82

// ----------------------------------------------------------------------------

class MBS74T1AEFDevice 
{

   private:
		uint8_t addr           = TRFM_DEF_I2C_ADDRESS;
		uint8_t channel        = TRFM_CHANNEL_MIN;
    uint8_t soundCarrierId = TRFM_SOUND_CARRIER_5_5MHZ;		
		bool    enabled        = false;

    uint8_t getFreqBytes( uint8_t &fm, 
                          uint8_t &fl, 
                          uint8_t iChannel = TRFM_CHANNEL_CURRENT, 
                          bool    testMode = false
                         ); 

   public:
		MBS74T1AEFDevice();

     // getters (with self explaining function names)
    uint8_t  getChannel( uint8_t iChannel = TRFM_CHANNEL_CURRENT );
    uint8_t  getSoundCarrierId( int8_t  iSoundCarrierId = TRFM_SOUND_CARRIER_CURRENT );
    int8_t   getStatus(); // <- Not working
    uint16_t getChannelFrequencyBits( uint8_t iChannel = TRFM_CHANNEL_CURRENT );
    uint32_t getChannelFrequency( uint8_t iChannel = TRFM_CHANNEL_CURRENT ); // In kHz
    
 
     // setters (with self explaining function names)
    void setI2CAddress( uint8_t iAddr ); 
    void setChannel(uint8_t iChannel, bool testMode = false ); 
    void setNextChannel( bool testMode = false ); 
    void setPrevChannel( bool testMode = false ); 
    void setSoundCarrierId(uint8_t iSoundCarrierId = TRFM_SOUND_CARRIER_6_5MHZ ); 
    void setNextSoundCarrierId();
    void setPrevSoundCarrierId();
    void setTestMode( bool testMode = true );
    void setWord( uint8_t v1, uint8_t v2 ); 
     
    void beginTransmission();
    void endTransmission();
     
     // default functions
    void begin( uint8_t iChannel = TRFM_CHANNEL_CURRENT, 
                int8_t  iSoundCarrierId = TRFM_SOUND_CARRIER_CURRENT, 
                bool    bTestMode = false 
              );
    void reset( bool bTestMode = false );
    void end();           
};


extern MBS74T1AEFDevice rfmod;

// ----------------------------------------------------------------------------

#endif
