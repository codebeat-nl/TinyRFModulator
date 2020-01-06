/*
  DIY TINY RF MODULATOR
  ---------------------
  This project is an adjustable RF Modulator to convert composite audio (mono) and video to an aerial 
  RF signal. A RF signal (RF = Radio Frequency) is used on older TV-sets (or other RF equipment) and most 
  of these devices  doesn't have a composite input. It uses a tiny Attiny85 (Digispark) to control the 
  RF Modulator (and display) via I2C. The code can be compiled and uploaded using the Arduino IDE.


  -------------------------------------------------------------------------------------------------------


  IDE INFO & COMPILER SETTINGS
  ----------------------------
  Editor used: Arduino IDE 1.8.9
  Board      : Digispark (Default 16.5Mhz)/Digispark (8Mhz - No USB)
  Programmer : AVRISP MKII  
  Bytecode   : 5652 bytes (94%) 180 bytes dynamic memory used
  Notice     : Code supports other AVR's and ESP models

  
  VERSION HISTORY:
  ---------------
  - Date    : 11-sep-2019 (v1.00, first release)
    updated : - 
  
  Copylight (c) codebeat (c) 2019
  Love this software? Consider a donation (in future),
  grateful for any kind of support.

  codebeat channels (maybe work in progress):
  - http://www.codebeat.nl             ; Main website
  - http://blog.codebeat.nl            ; Blog website (projects and more)
  - http://youtube.codebeat.nl         ; YouTube channel (shortcut)
  - http://patreon.codebeat.nl         ; Patreon support channel (shortcut)   
  - http://github.codebeat.nl          ; Github (projects)

  
  JUST A WARNING:
  ---------------
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


  -------------------------------------------------------------------------------------------------------

  
  WHY? RECYCLE! LEARNING! CHEAP!
  ------------------------------
  There are commercial units around that can do the same, converting composite to RF aerial, however why
  buy one if you can make your own? Parts are everywhere, for example salvaged RF Modulator from an old 
  Sattelite receiver (Strong STR-605), RCA connectors from scart adapters (etc). With a $1 microcontroller,
  some salvaged parts and some perfboard is ridiculous cheap to make, learn something too. 
  Made it easier for you to do the same ;-).
  
  
  APPLICATION
  -----------
  o Using any composite video device on an older TV-set, recorder, boombox etc;
  o Using RF-devices in Arduino projects, repurpose and revive life of older technologies; 
  o Using older TV-sets as marquee (for example with Arduino TVOut), (security) video monitor, 
    serial terminal etc;
  o Or anything else ;-).
  
  
  MAIN FEATURES:
  --------------
  o Converts composite video and audio to one RF (aerial) signal;
  o Works on USB power or other 5V adapter;
  o Easy to use, intuitive operation - one button control to set broadcast 
    channel/frequency, test-mode or reset;
  o Low cost MCU/Board and parts;
  o Whopping 512 bytes EEPROM to store settings made by user ;-D;
  o Display current settings on a tiny OLED SSD1306 128x32 pixels display (optional);
  o Can work with or without OLED display (reboot required);
  o 48 channels selectable between 471 and 855 Mhz (UHF);
  o Flash LED to visualize user activity;
  o Test-mode, broadcast test signal (audio/video) to be able to find the channel;
  o Environment friendly: DIY, open source, well documented, reusing old tech and saves 
    the planet from old 'scrap';
  o Customizable: Firmware updates/changes can be made by you.   

       
  SCHEMATIC:            
  ---------- 
  TINY RF MODULATOR
  Author: codebeat                                          SSD1306 OLED DISPLAY
  Date  : 2019-11-09                                        I2C Address 0x3C
  KEYB ASCIICAD ;-)                                         __________________________
                                                            |                        |
      _____________________                           |---- o SDA                    |
      |IN  ___     ___ OUT|                           |  |- o CLK                    |
      |__ /   \__ /   \___|                           |  |  o 5V o-------------------|--------------------------- |
  ____|  | (@) | |  o  |  |                    |------|--|- o GND                    |                            |
  ^   |   \___/   \___/   |                    |      |  |  |________________________|                            |
  PINS|___________________|                    |      |  |                                                        |
                                               |      |  |                                                        |
      I2C RF-Modulator, I2C address 0x65       |      |  |                                                        |
      Shenzhen Tena TNF0170U722*,              |      |  |  Digispark                                             |
      Samsung RMUP74055AD (or equavalent)      |      |  |  Attiny85 (internal LED on P1 removed!)                |
      with MBS74T1AEF IC                       |      |  |  _____________     _______________________             |
      ____________________ *                   |      |  |  |            |    |                     |             |
      |     _      _      | (shield = GND)     |      |  |_ o P0 SDA     |    |       LED           |             |
   ___|____| |____| |_____| (pins are on       |      |  |  o P1 ________|____|_______|>|+----|     |             |
  |   | G  + V   + S S   G|  other side!       |      |---- o P2 SCL     |                    |     o |           |
  |___| N  5 B V 5 D C   N|  Drawed this       |      |  |  o P3  _______|_________-[ 1K ]-___|       --| Push    |
      | D  V S A V A L   D|  way because       |      |  |  o P4  |      |          resistor          --| Button  |
      --|--|-|-|-|-|-|----|  of schematic) GND |      |  |  o P5  5V GND |                          o |           |
        |  | | | | | |   |_____________________|      |  |  |_____o___o__|                          |             |
        |  o o o o o o                                |  |        |   |                             |             |
        |  | | | | | |                                |  |        |   |                             |             |
        |  | | | | | |                                |  |        |   |                             |             |
        |  | | | | | |                                |  | Pullup |   |                             |             |
     GND|  | | | | | |_______ SCL ____________________|----[4K7 ]-|   |                             |             |
        |  | | | | |_________ SDA _______________________|-[4K7 ]-|   |_____________________________|             |
        |  | | | |___________ B+  ________________________________|   |                                           |
        |  | | |_____________ VAUDIO-[VAR 10K]--*] AUDIO-IN RCA   |   |                                           |
        |  | |_______________ VBS----[VAR 10K]---] VIDEO-IN RCA   |   |                                           |
        |  __________________ 5V _________________________________|___|___________________________________________|
        |                          |+                                 |
        |                         === 1000uF                          |
        |__________________________|__________________________________|

  RCA CONNECTORS:              
                    FEMALE IN        MALE OUT (SOURCE)
                     _______                _________ 
      GND  ---------|   ____|         _____|   |<------------- GND
      DATA ------------(____         (_____|   |     <-------- DATA
                    |_______|              |___|_____
  
  RF CONNECTORS (COAX):              
                    MALE OUT         FEMALE IN (CABLE TO TARGET)
                     _______         ______          
      GND  ---------|   ____         _____ |------------------ GND
      DATA ------------|____)        _____)------------------- DATA
                    |_______         ______|     
  
  
  NOTICE: 
  -------
  o (!) Be aware that competitor Samsung RMUP74055AD have another order pinout comparing to 
        the Shenzhen Tena Tena TNF0170U722. Take a look at the datasheet in the doc folder;
  o (!) The Digispark onboard LED is removed to be able to use pin P1 as input pin;  
  o On pin P1 at Digispark an internal pull-up resistor is used, see code below at setup().
    The onboard LED is replaced with an external one and connected in reversed order (polarity); 
  o The LED and 1K resistor on pin P1 is optional;
  o [VAR 10K] is an adjustment potentiometer, trimpot for input. These pots needs to set first 
    (calibration) to be able to get decent quality video and audio. However, the audio trimpot 
    is optional (didn't notice any distortion); 
  o Pin P3 and P4 on Digispark cannot be used when connected to USB;
  o On Digispark clones Pin P5 cannot be used for input because it is fused to act as device
    reset. To change this behaviour and free this pin for input, you need to change the
    fuses with a high voltage programmer. This project doesn't use this pin so this is
    optional;  
  
  
  USAGE:
  ------
  o Connect coax cable to RF out (male connector on RF-Modulator) and the other end
    of the cable to TV-set (female connector);
  o Connect RCA cable to connectors (yellow=video,red/white=audio);
  o Turn unit on, apply power;
  o Adjust broadcast channel/frequency by pressing push button (LED will light up)
    default is channel 21, 471.2 Mhz; 
  o To change to test mode (= test signal with two vertical stripes on a black background
    and a 976 Hz audio signal), hold down push button for 3 seconds (LED flash fast after 
    release). To switch to input mode again, repeat the same step;
  o To reset the device and settings (set defaults), hold push button for 5 seconds
    (or wait until "RESET!" appear on display);
  o LED flashes twice when new settings are saved to EEPROM;  

  
  REMARKS:
  --------
  o Setting Sound Carrier mode isn't enabled in this firmware revision assuming
    user always wants the best audio (and picture) quality possible. If 
    you don't agree with this, take a look at the TinyRFModulator.config.h file
    to be able to enable it.
         
 
  POWER CONSUMPTION
  -----------------
  o The whole system requires at peak around 70mA.
  o When producing static (no input signal): approx 70mA
  o When producing static (no input signal) and MCU sleep mode: approx 50mA
  o When processing video: approx 50mA 
  o When processing video (MCU sleep mode): approx 40-45mA 

  
  BOM LIST (FULLY FEATURED)
  ------------------------
  - 1x Perfboard (any size that fits all components)
  - 1x I2C RF-Modulator (From satellite receiver, VCR etc)
  - 1x ATTINY85 Digispark (clone)
  - 1x Tactile push button
  - 1x 6v/10v 1000uF capacitor
  - 2x 10K trim pot (or at least 2K)
  - 2x Female RCA connectors (yellow and other color) 
  - 1x LED
  - 1x 1K resistor (for LED)
  - 2x 47K resistor (for I2C, pullup)
  - 1x I2C SSD1306 based OLED screen
  - 1x 4 pins female header (for OLED screen) 
*/

// -- FINALLY, BELOW THE CODE ;-) --------------------------------------------------------

// -- INCLUDES ---------------------------------------------------------------------------

// TinyRFModulator.config.h
// ------------------------
// This file contain all includes and configuration settings. If you want to change 
// settings, behaviour, first take a look at this file.
#include "TinyRFModulator.config.h"

#ifndef TRFM_LIBRARY_TINYOLED_ENABLED
   // * Place your custom display library here *
#endif


// -- VARIABLES --------------------------------------------------------------------------

 // Test mode enabled/disabled flag
static bool bTestMode = TRFM_TESTMODE_DEFAULT; 

 // Change flag, is set to true when user change settings
static bool bChanged = false; 

 // 'Timer', when 0 and bChanged==true new settings will be stored in EEPROM
static uint16_t iEepromSaveTimeout = 0;     

#if defined TRFM_SCREENSAVER_TIMEOUT && TRFM_SCREENSAVER_TIMEOUT > 0
 // 'Timer', screen saver timeout, when it reaches zero it will turn off the screen.
 // Pressing the push button will enable the screen again. If you don't
 // want a screensaver, see also TinyRFModulator.config.h
static uint16_t iScreenSaveTimeout = TRFM_SCREENSAVER_TIMEOUT;    
#endif

// -- FUNCTIONS --------------------------------------------------------------------------

 // Defining own delay saves about 8 bytes of program space
void delay( int mseconds )
{
 while ( mseconds-- )
 {
   delayMicroseconds( 1000 );
 }
}

#if defined TRFM_LIBRARY_TINYOLED_ENABLED || defined TRFM_USE_SERIAL_NO_DISPLAY
void updateDisplay() 
{
  char buff[10];
  
  #ifdef TRFM_USE_SERIAL_NO_DISPLAY 
   displayClear();
  #endif
  displaySetCursor(0, 0);
  displayPrint( TRFM_GUI_LABEL_CHANNEL );
  displayPrint( ": " );
  displayPrint( (int)rfmod.getChannel() );

   // When settings are changed and not saved, show * on display
  displayPrint( bChanged?" *":"  " );
  
   // Low cost method to show frequency, avoid devide
  displaySetCursor(64, 0);
  memset(buff, 0, sizeof(buff));
  ultoa( (uint32_t)rfmod.getChannelFrequency(), &buff[0], 10 );
  displayPrint( buff[0] );
  displayPrint( buff[1] );
  displayPrint( buff[2] );
  displayPrint( "." );
  displayPrint( buff[3] ); 
  displayPrint( buff[4] ); 
  displayPrint( " " );
  displayPrint( TRFM_GUI_LABEL_MHZ );
  displayPrint( " " );

   
  displaySetCursor(0, 3);
  // Low cost method to show sound carrier frequency, avoid switch-case, multiply or devide
  uint8_t i=rfmod.getSoundCarrierId();
  displayPrint( TRFM_GUI_LABEL_SOUND_CARRIER );
  displayPrint( ": " );
  displayPrint( (int)min(i+4,6) );
  displayPrint( "." );
  displayPrint( i==TRFM_SOUND_CARRIER_6_0MHZ?"0":"5" );
  displayPrint( " " );
  displayPrint( TRFM_GUI_LABEL_MHZ );
  displayPrint( i == TRFM_SOUND_CARRIER_MAX?" HQ":"   " );

  displaySetCursor(94, 3);
  displayPrint( bTestMode?TRFM_GUI_LABEL_TESTMODE:TRFM_GUI_LABEL_INPUT );
  displayPrint( " " );
}
#else
 // Custom display routines, see also TinyRFModulator.config.h file
void displayBegin()
{
  // * Place your custom code here *
}

void displaySetCursor( uint8_t x, uint8_t y )
{
  // * Place your custom code here *
}

void displayClear()
{
  // * Place your custom code here *
}

void displayPrint( char* s )
{
  // * Place your custom code here *
}
void displayPrint( int i )
{
  // * Place your custom code here *
}

void displayEnable()
{
  // * Place your custom code here *
}
void displayDisable()
{
  // * Place your custom code here *
}
void updateDisplay() 
{
  // * Place your custom code here *
}   
#endif


#ifdef TRFM_EXTERNAL_LED_ENABLED
void ledOn()
{
  pinMode( TRFM_PIN_LED, OUTPUT );
   
  #ifdef __AVR_ATtiny85__
   digitalWrite( TRFM_PIN_LED, LOW ); // Make LED glow
  #else
   digitalWrite( TRFM_PIN_LED, HIGH );
  #endif
}

void ledOff()
{
  #ifdef __AVR_ATtiny85__
   pinMode( TRFM_PIN_LED, INPUT_PULLUP ); 
  #else
   digitalWrite( TRFM_PIN_LED, LOW ); 
  #endif
} 

void blinkLED( uint8_t i = 8, uint8_t iDelay = 200 )
{
  while( i-- ) 
  { 
    ledOn();
    delay(iDelay);
    ledOff();
    delay(iDelay);
  }
}
#else
  #define ledOn()
  #define ledOff()
  #define blinkLED(...)
#endif

#ifdef TRFM_LIBRARY_EEPROM_ENABLED 
bool readSettingsHeader()
{
  return ( EEPROMRead( TRFM_EECFG_HDMAGIC1 ) == TRFM_EEVAL_HDMAGIC1 
           && EEPROMRead( TRFM_EECFG_HDMAGIC2 ) == TRFM_EEVAL_HDMAGIC2 );
}

void saveSettings()
{
  if( !readSettingsHeader() )
  {
    EEPROMUpdate( TRFM_EECFG_HDMAGIC1, TRFM_EEVAL_HDMAGIC1 );
    EEPROMUpdate( TRFM_EECFG_HDMAGIC2, TRFM_EEVAL_HDMAGIC2 );
  }
  
  EEPROMUpdate( TRFM_EECFG_SOUNDCARRIER, rfmod.getSoundCarrierId() );
  EEPROMUpdate( TRFM_EECFG_CHANNEL     , rfmod.getChannel() );
  EEPROMUpdate( TRFM_EECFG_TESTMODE    , bTestMode );
  
  EEPROMEndWrite();
  
  iEepromSaveTimeout = 0;
  bChanged = false;
  #ifdef TRFM_USE_SERIAL_NO_DISPLAY
   displayPrint( "\n\n" );
   displayPrint( TRFM_GUI_LABEL_SERIAL_SETTINGS_SAVED );
  #endif 
  blinkLED( 2, 100 );
}

void restoreSettings()
{
  if( readSettingsHeader() )
  {
    rfmod.setChannel( EEPROMRead( TRFM_EECFG_CHANNEL ) );
    rfmod.setTestMode( bTestMode = (bool)EEPROMRead( TRFM_EECFG_TESTMODE ) );
    rfmod.setSoundCarrierId( EEPROMRead( TRFM_EECFG_SOUNDCARRIER ) );
  }
}

void setSettingsChanged()
{
   // Config changed, set save timeout
  iEepromSaveTimeout = TRFM_EEPROM_SAVE_TIMEOUT;
  bChanged = true;
}
#else
  // Custom
 void setSettingsChanged()
 {
    // * Place your custom code here * 
 }
#endif

void waitNoButtonPressed()
{
  pinMode( TRFM_PIN_BUTTON, INPUT_PULLUP ); 
  while( digitalRead( TRFM_PIN_BUTTON ) == LOW ) 
   { delay(50); } 
}

void toggleTestMode()
{
  rfmod.setTestMode( bTestMode=!bTestMode ); 
  updateDisplay();
  blinkLED(10,50);
}

void updateSaveSequence()
{
   if( bChanged )
   {
     if( iEepromSaveTimeout > 0 )
     {
       --iEepromSaveTimeout;
       if( iEepromSaveTimeout == 0 )
       {
         #ifdef TRFM_LIBRARY_EEPROM_ENABLED  
          saveSettings();
         #endif
         
         #if defined TRFM_SCREENSAVER_TIMEOUT && TRFM_SCREENSAVER_TIMEOUT > 0 
          if( iScreenSaveTimeout > 0 )
           { updateDisplay(); } 
         #else 
          updateDisplay();
         #endif 
       }
     }
   }
}

#ifdef TRFM_SCREENSAVER_DEEP_SLEEP 
 #ifdef __AVR_ATtiny85__
 void sleep() 
 {
   GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
   PCMSK |= _BV(PCINT1);                   // Use PB1 as interrupt pin
   ADCSRA &= ~_BV(ADEN);                   // ADC off
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement

   sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
   sei();                                  // Enable interrupts
   sleep_cpu();                            // sleep

   cli();                                  // Disable interrupts
   PCMSK &= ~_BV(PCINT1);                  // Turn off PB1 as interrupt pin
   sleep_disable();                        // Clear SE bit
   ADCSRA |= _BV(ADEN);                    // ADC on

   sei();                                  // Enable interrupts

   blinkLED( 2,100 );                      // Show user device woke up
 } 

 ISR(PCINT0_vect) 
 {
    // This is called when the wake-up interrupt occurs
   Wire.begin();
 }
 #else
  // Custom
  void sleep()
  {
    // * Place your custom code here *
  }
  #endif
#endif

#if defined(TRFM_SCREENSAVER_TIMEOUT) && TRFM_SCREENSAVER_TIMEOUT > 0 
void updateIdleSequence()
{
  if( iScreenSaveTimeout > 0 )
  {
    --iScreenSaveTimeout;
    
    if( iScreenSaveTimeout == 0 )
     { 
       displayClear(); 
       displayDisable();
       #ifdef TRFM_SCREENSAVER_DEEP_SLEEP 
        sleep();
       #endif
     }
  }  
}  
#endif

#if defined TRFM_USE_SERIAL_NO_DISPLAY && defined TRFM_CMD_SERIAL_UI_ENABLED
void updateChange()
{
   rfmod.setTestMode( bTestMode );
   // Changed: set save timeout
   setSettingsChanged();
   updateDisplay(); 
}

void displayHelp()
{
  displayClear();
  displaySetCursor(0,0);
  displayPrint( TRFM_GUI_LABEL_SERIAL_COMMAND );
  displayPrint("\n--------\n");
  uint8_t i = 0;
  
  #define __displayHelp(c,s) displaySetCursor(0,++i); \
                             displayPrint(c); \
                             displaySetCursor(TRFM_CMD_SERIAL_LEN_MAX+2-strlen(c),i); \
                             displayPrint(s); delay(1)
 
  __displayHelp( TRFM_CMD_SERIAL_HELP              , TRFM_GUI_LABEL_SERIAL_HELP );
  __displayHelp( TRFM_CMD_SERIAL_LONG_PRESS        , TRFM_GUI_LABEL_SERIAL_LONG_PRESS );
  __displayHelp( TRFM_CMD_SERIAL_SHORT_PRESS       , TRFM_GUI_LABEL_SERIAL_SHORT_PRESS );
  __displayHelp( TRFM_CMD_SERIAL_NEXT_CHANNEL      , TRFM_GUI_LABEL_SERIAL_NEXT_CHANNEL );
  __displayHelp( TRFM_CMD_SERIAL_PREV_CHANNEL      , TRFM_GUI_LABEL_SERIAL_PREV_CHANNEL );
  __displayHelp( TRFM_CMD_SERIAL_NEXT_SOUND_CARRIER, TRFM_GUI_LABEL_SERIAL_NEXT_SOUND_CARRIER );
  __displayHelp( TRFM_CMD_SERIAL_PREV_SOUND_CARRIER, TRFM_GUI_LABEL_SERIAL_PREV_SOUND_CARRIER );
  __displayHelp( TRFM_CMD_SERIAL_TOGGLE_TESTMODE   , TRFM_GUI_LABEL_SERIAL_TESTMODE );
  __displayHelp( TRFM_CMD_SERIAL_RESET             , TRFM_GUI_LABEL_SERIAL_RESET );

  #undef __displayHelp
}

uint8_t getSerialCmdPressed()
{ 
  if( Serial.available() )
   {
     char    s[ TRFM_CMD_SERIAL_LEN_MAX+1 ] = {0};
     uint8_t i = 0;
     
     while( Serial.available() > 0 && i < TRFM_CMD_SERIAL_LEN_MAX )
      { s[i] = (char)Serial.read(); 
        delay(10); // Needs some delay on Windows 
        if( s[i] >= 97 )
         { s[i]-=32; }
        ++i; 
      }
     
     while( Serial.available() > 0 )
      { Serial.read(); delay(1); }
     
     if( i > 0 )
     {
       Serial.println( (char*)&s[0] ); 
       
       if( strcmp( s, TRFM_CMD_SERIAL_HELP ) == 0 )
        { 
          displayHelp();
          return 0; 
       }
       
       if( strcmp( s, TRFM_CMD_SERIAL_NEXT_CHANNEL ) == 0 )
        { return 1; }
       
       if( strcmp( s, TRFM_CMD_SERIAL_PREV_CHANNEL ) == 0 )
        { 
           rfmod.setPrevChannel(); 
           updateChange();
           return 0; 
        }
       
       if( strcmp( s, TRFM_CMD_SERIAL_LONG_PRESS ) == 0 )
        { 
          return TRFM_BTN_THRESHOLD_TESTMODE-1;
        }
       
       if( strcmp( s, TRFM_CMD_SERIAL_SHORT_PRESS ) == 0 )
        { 
          return 0x01;
        }

       if( strcmp( s, TRFM_CMD_SERIAL_NEXT_SOUND_CARRIER ) == 0 )
        { 
           rfmod.setNextSoundCarrierId(); 
           updateChange();
           return 0; 
        }
       
       if( strcmp( s, TRFM_CMD_SERIAL_PREV_SOUND_CARRIER ) == 0 )
        { 
           rfmod.setPrevSoundCarrierId(); 
           updateChange();
           return 0; 
        }
       
       if( strcmp( s, TRFM_CMD_SERIAL_TOGGLE_TESTMODE ) == 0 )
        { 
          return TRFM_BTN_THRESHOLD_TESTMODE;
        }
       
       if( strcmp( s, TRFM_CMD_SERIAL_RESET ) == 0 )
        { 
          return TRFM_BTN_THRESHOLD_RESET;
        }
        
        Serial.print( "\n" );
        Serial.print( TRFM_GUI_LABEL_SERIAL_UNKNOWN_CMD );
        Serial.print( " - \"");
        Serial.print(s); 
        Serial.println("\"");
     }
   }
   
   return 0; 
}
#endif

uint8_t getButtonHoldCountPressed() 
{
  uint8_t iHold = 0;
  
  #if defined TRFM_USE_SERIAL_NO_DISPLAY && defined TRFM_CMD_SERIAL_UI_ENABLED
   iHold = getSerialCmdPressed();
   if( iHold > 0 )
    { return iHold; }
  #endif
  
  pinMode( TRFM_PIN_BUTTON, INPUT_PULLUP ); 

    
   // When pin TRFM_PIN_BUTTON is low, button is pushed
  while( digitalRead( TRFM_PIN_BUTTON ) == LOW && iHold < TRFM_BTN_THRESHOLD_HOLD_MAX ) 
  {
     delay( TRFM_BTN_DEBOUNCE_DELAY );
     ++iHold;
  }
  
  #ifndef TRFM_USE_SERIAL_NO_DISPLAY
   #if defined TRFM_SCREENSAVER_TIMEOUT && TRFM_SCREENSAVER_TIMEOUT > 0
    if( iHold > 0 || (iHold == 0 && iScreenSaveTimeout == 0) )
    {
     if( iScreenSaveTimeout == 0 )
     { 
       iScreenSaveTimeout = TRFM_SCREENSAVER_TIMEOUT;
       displayEnable();
       updateDisplay();
       waitNoButtonPressed();
       return 0; 
     }  
     iScreenSaveTimeout = TRFM_SCREENSAVER_TIMEOUT;   
    } 
   #endif
  #endif 
  //waitNoButtonPressed();
  return iHold;
}

void startBroadcast( bool bAskSoundCarrierQuestion = false )
{
   #if defined TRFM_GUI_ASK_SOUND_CARRIER_SETTING && !defined TRFM_GUI_NEXT_CARRIER_ENABLED
     uint8_t i = 8;
    #ifdef TRFM_GUI_ASK_SOUND_CARRIER_TIMEOUT
     uint8_t iTimeOut = min( 10, TRFM_GUI_ASK_SOUND_CARRIER_TIMEOUT );
    #else
     uint8_t iTimeOut = 10;
    #endif     
    
    if( bAskSoundCarrierQuestion && iTimeOut > 0 )
    {
      uint16_t imSec = 1;  
      displayClear();
      displayPrint( TRFM_GUI_LABEL_SC_QESTION ); 
      displayPrint( "?" );
      displaySetCursor(0,2);
      
      #if defined TRFM_USE_SERIAL_NO_DISPLAY && defined TRFM_CMD_SERIAL_UI_ENABLED
       displayPrint( TRFM_CMD_SERIAL_LONG_PRESS );
       displayPrint( ") " );
      #endif
      
      displayPrint( TRFM_GUI_LABEL_ANALOG );
      displayPrint( "* (" );  
      displayPrint( TRFM_GUI_LABEL_LONG_PRESS );
      displayPrint( ")" );
      
      displaySetCursor(0,3);
      
      #if defined TRFM_USE_SERIAL_NO_DISPLAY && defined TRFM_CMD_SERIAL_UI_ENABLED
       displayPrint( TRFM_CMD_SERIAL_SHORT_PRESS );
       displayPrint( ") " );
      #endif
      
      displayPrint( TRFM_GUI_LABEL_DIGITAL );
      displayPrint( " (" );  
      displayPrint( TRFM_GUI_LABEL_SHORT_PRESS );
      displayPrint( ")" );
      waitNoButtonPressed();
   
      while( (iTimeOut > 0 ) && (i = getButtonHoldCountPressed()) == 0 ) 
      {
        --imSec;
        if( imSec == 0 )
        {
          imSec = 1000;
          displaySetCursor(110,0);
          displayPrint( (int)--iTimeOut );
        }
        delay(1);
      }
      
      if( i > 0 )
      {
        displayClear();
        displayPrint(  TRFM_GUI_LABEL_OKAY );
        displaySetCursor(0,1);
        displayPrint( TRFM_GUI_LABEL_SC_QESTION );
        displayPrint( ":" );
        displaySetCursor(0,3);
        displayPrint( (iTimeOut == 0 || i>=5)?TRFM_GUI_LABEL_ANALOG:TRFM_GUI_LABEL_DIGITAL );
        displayPrint( " " );
        displayPrint( TRFM_GUI_LABEL_TUNER );
        delay( 4000 );
      }  
    }
    
    rfmod.begin( TRFM_CHANNEL_DEFAULT,
                 (iTimeOut == 0 || i>=5)?TRFM_SOUND_CARRIER_DEFAULT:TRFM_SOUND_CARRIER_DIGITAL,
                 bTestMode 
                ); 
    waitNoButtonPressed();
    displayClear();
  #else
    rfmod.begin( TRFM_CHANNEL_DEFAULT,
                 TRFM_SOUND_CARRIER_DEFAULT,
                 bTestMode 
               ); 
  #endif
}

void reset()
{
  displayClear();
  displayPrint( TRFM_GUI_LABEL_RESET );
  displayPrint( "!" );
  
  #ifndef TRFM_RESET_KEEP_CURRENT_MODE
   bTestMode = TRFM_TESTMODE_DEFAULT;
  #endif
  
  #ifdef TRFM_EXTERNAL_LED_ENABLED
   blinkLED();
  #else
   delay(3000);
  #endif 
  
  startBroadcast(true);
}

// -- PROGRAM ----------------------------------------------------------------------------


void setup() 
{
  Wire.begin();
  displayBegin();
  rfmod.setI2CAddress( TRFM_I2CADDR_RFMODULATOR ); 
  
  #ifdef TRFM_LIBRARY_EEPROM_ENABLED 
   EEPROMBegin();
   startBroadcast( !readSettingsHeader() );
   restoreSettings();
  #else
   startBroadcast(true);
  #endif 
  updateDisplay();
}

void loop() /* main */
{
 // while(1)
 {  
   // Slow down a bit, do not remove this!
   delay(1); 
   
    // Button press/hold counter
   uint8_t iBtCount = getButtonHoldCountPressed(); 
   
    // Button pressed?
   if( iBtCount > 0 )
   {
     if( iBtCount >= TRFM_BTN_THRESHOLD_RESET )
     { 
         // Reset device and settings
        reset(); 
     }
     else  
     if( iBtCount >= TRFM_BTN_THRESHOLD_TESTMODE )
     {
        toggleTestMode();
     }
     else {  
            #ifdef TRFM_GUI_NEXT_SOUND_CARRIER_ENABLED 
             // If you want this feature, you must enable it at the TinyRFModulator.config.h file
             if( iBtCount >= TRFM_BTN_THRESHOLD_NEXT_SOUND_CARRIER )
             { 
               rfmod.setNextSoundCarrierId();
             }
             else 
            #endif 
                 {
                   // Short press, goto next channel
                   rfmod.setNextChannel(); 
                 }
            
            rfmod.setTestMode( bTestMode );
          }
     
   
      // Changed: set save timeout
     setSettingsChanged();
     updateDisplay();
     
     // Wait until no button is pressed
     waitNoButtonPressed();
   }

    // Screensaver and sleep functionality is disabled when serial output
    // is configurated. 
   #ifndef TRFM_USE_SERIAL_NO_DISPLAY
    #if defined TRFM_SCREENSAVER_TIMEOUT && TRFM_SCREENSAVER_TIMEOUT > 0 
     else {
            updateIdleSequence();
          }
    #endif
   #endif
      
   if( bTestMode )
   {
     // Make LED glow on loop sequence
     ledOn(); 
   }
   
   updateSaveSequence();
 }
}
