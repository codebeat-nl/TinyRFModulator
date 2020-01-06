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
    it won't function!  
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



// ----------------------------------------------------------------------------

#ifdef __AVR_ATtiny85__
  // Use TinyWireM, smaller and don't freeze when RF-modulator is 
  // disconnected.
 #include <TinyWireM.h>   
 #define  Wire TinyWireM
#else
  // Warning: Using wire when device is not connected or cannot be 
  // found, can freeze the Arduino. This is a known problem of the
  // default wire library.  
 #include <Wire.h>
#endif

#include "TinyRFModulator.h"

 // Constructor
MBS74T1AEFDevice::MBS74T1AEFDevice()
{
  end();  
}

 // Getters
uint8_t MBS74T1AEFDevice::getChannel( uint8_t iChannel /* = TRFM_CHANNEL_CURRENT */ )
{
   int8_t iCh = iChannel == TRFM_CHANNEL_CURRENT?channel:
                iChannel == TRFM_CHANNEL_NEXT   ?channel+1:
                iChannel == TRFM_CHANNEL_PREV   ?channel-1:
                iChannel;  
  
  if( iCh > TRFM_CHANNEL_MAX )
   { iCh = TRFM_CHANNEL_MIN; }
  else if( iCh < TRFM_CHANNEL_MIN )
        { iCh = TRFM_CHANNEL_MAX; }
  
  return iCh;       
}

uint8_t MBS74T1AEFDevice::getSoundCarrierId( int8_t  iSoundCarrierId /* = TRFM_SOUND_CARRIER_CURRENT */ )
{
  int8_t iCar = iSoundCarrierId == TRFM_SOUND_CARRIER_CURRENT?soundCarrierId:
                iSoundCarrierId == TRFM_SOUND_CARRIER_NEXT   ?soundCarrierId+1:
                iSoundCarrierId == TRFM_SOUND_CARRIER_PREV   ?soundCarrierId-1:
                iSoundCarrierId;  
  
  if( iCar > TRFM_SOUND_CARRIER_MAX  )
   { iCar = TRFM_SOUND_CARRIER_MIN; }
  else if( iCar < TRFM_SOUND_CARRIER_MIN )
        { iCar = TRFM_SOUND_CARRIER_MAX; }
  
  return iCar;       
}


int8_t  MBS74T1AEFDevice::getStatus() /* not working! */
{
  if (!enabled) 
   return TRFM_STATUS_OFF;
  
  int  c = Wire.requestFrom( (int)addr, (int)1 );
  uint8_t s = (c == 1)?Wire.read():1;
  
  return (s & 0x01)?TRFM_STATUS_ERROR:TRFM_STATUS_ON; 
}

uint16_t MBS74T1AEFDevice::getChannelFrequencyBits( uint8_t iChannel /* = TRFM_CHANNEL_CURRENT */ )
{
   // Avoid multiply operator: 
   // Code optimalization: This code consumes less program space, 4 bytes exactly
   // Replaces this line : return (uint16_t)(32 * (uint16_t)getChannel( iChannel )) + 1213;
  
   uint16_t iResult = getChannel( iChannel );
   uint8_t  i = 6;
   while( --i )
    { iResult+=iResult; }
   
   return iResult+1213;
}

uint32_t MBS74T1AEFDevice::getChannelFrequency( uint8_t iChannel /* = TRFM_CHANNEL_CURRENT */ ) // In kHz
{
   // Avoid multiply operator: 
   // Code optimalization: This code consumes less program space, saves 214 bytes!
   // Replaces this line : return (uint32_t)getChannelFrequencyBits( iChannel )*250 /*kHz*/ ;
   
   uint32_t iResult = 0;
   uint8_t  i = 251;
   while( --i )
    { iResult+=(uint32_t)getChannelFrequencyBits( iChannel );  }
   
   return iResult; 
}

uint8_t MBS74T1AEFDevice::getFreqBytes(uint8_t &fm, 
                                       uint8_t &fl, 
                                       uint8_t iChannel /* = TRFM_CHANNEL_CURRENT */, 
                                       bool    testMode /* = false */
                                      ) 
{
  iChannel = getChannel( iChannel );
  uint16_t freqBits = getChannelFrequencyBits( iChannel );
  
  fm = freqBits >> 6;
  
  if( testMode ) 
   { fm |= 0x40; }
  
  fl = (freqBits & 0x3F) << 2;
  
  return iChannel;
}

 // Setters
void MBS74T1AEFDevice::setI2CAddress( uint8_t iAddr ) 
{
  if( iAddr > 0 )
   { addr = iAddr; }
}

void MBS74T1AEFDevice::setChannel(uint8_t iChannel, bool testMode /* = false */ ) 
{
  uint8_t fm, fl;

  channel = getFreqBytes( fm, fl, iChannel, testMode );
  setWord( fm, fl );
}

void MBS74T1AEFDevice::setNextChannel( bool testMode /* = false */ ) 
{
  setChannel( TRFM_CHANNEL_NEXT, testMode );
}

void MBS74T1AEFDevice::setPrevChannel( bool testMode /* = false */ ) 
{
  setChannel( TRFM_CHANNEL_PREV, testMode );
}

void MBS74T1AEFDevice::setTestMode( bool testMode /* = true */)
{
  setChannel( TRFM_CHANNEL_CURRENT, testMode );
}


void MBS74T1AEFDevice::setSoundCarrierId(uint8_t iSoundCarrierId /* = TRFM_SOUND_CARRIER_6_5MHZ */ ) 
{
  soundCarrierId = getSoundCarrierId( iSoundCarrierId ); 
  setWord( // Set defaults (as in datasheet B10001000)
           0x88,
           // Set oscillator ON and set soundCarrier
           0x40 | (uint8_t)(soundCarrierId * TRFM_SOUND_CARRIER_MULTIPLIER ) 
          );
}

void MBS74T1AEFDevice::setNextSoundCarrierId()
{
  setSoundCarrierId( TRFM_SOUND_CARRIER_NEXT );
}

void MBS74T1AEFDevice::setPrevSoundCarrierId()
{
  setSoundCarrierId( TRFM_SOUND_CARRIER_PREV );
}

void MBS74T1AEFDevice::setWord( uint8_t v1, uint8_t v2 )
{
  //beginTransmission();
  //Wire.write(v1);
  //Wire.write(v2);
  //endTransmission();
}

void MBS74T1AEFDevice::beginTransmission()
{ //Wire.beginTransmission( addr ); 
}

void MBS74T1AEFDevice::endTransmission()
{ //Wire.endTransmission(); 
} 

void  MBS74T1AEFDevice::begin( uint8_t iChannel /* = TRFM_CHANNEL_CURRENT */, 
                               int8_t  iSoundCarrierId /* = TRFM_SOUND_CARRIER_CURRENT */ , 
                               bool bTestMode /* = false */ 
                             ) 
{
  setChannel( iChannel, bTestMode );
  setSoundCarrierId( iSoundCarrierId );
  enabled = true;
}

void  MBS74T1AEFDevice::reset( bool bTestMode /* = false */ )
{
  begin( TRFM_CHANNEL_MIN, TRFM_SOUND_CARRIER_MAX, bTestMode ); 
}

void  MBS74T1AEFDevice::end() 
{
  enabled = false;
  setWord( 0xA8, 0x20 );
}


MBS74T1AEFDevice rfmod;

// ----------------------------------------------------------------------------
