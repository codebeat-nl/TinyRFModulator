/*
  Configuartion file for TinyRFModulator project.

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

// -- CONFIG STUFF --------------------------------------------------------------------------

// PIN CONFIGURATION
// -----------------
// There are two definitions, one for an AtTiny MCU and one for another MCU. It is recommended
// to use this firmware with a Digispark (AtTiny85) however it is possible to use another
// kind of MCU/Arduino board. When using another MCU/Arduino board with this software, be sure 
// to use/configurate digital capable pins only.

#ifdef __AVR_ATtiny85__
  // On Digispark, button and LED are on the same PIN. To be able to use P1 as digital input pin,
  // you need to REMOVE THE ONBOARD LED and replace it with a LED in reversed (polarity) order,
  // see also schematic in sketch. Peel it off carefully with use of your fingernail or 
  // desolder it if you wish.  
 #define TRFM_PIN_LED         1
 #define TRFM_PIN_BUTTON      1
#else
   // Other MCU, verified MCU's: Other Atmel/Microchip AVR's and Espressif ESP variants
   // Please check configuration below before use.
  #ifdef LED_BUILTIN
   #define TRFM_PIN_LED        LED_BUILTIN
  #else
   #define TRFM_PIN_LED        13
  #endif
  #define TRFM_PIN_BUTTON      10
#endif



// TRFM_LIBRARY_TINYOLED_ENABLED
// -----------------------------
// To be able to use the firmware code with other display technologies (or to completely switch
// it off), you are able to write your own display routines (or do nothing to switch it off 
// completely). Simply comment the option below by placing // before the define.
// Notice: If your goal is to use this device headless (with serial monitor), take a look at 
//         the option TRFM_USE_SERIAL_NO_DISPLAY below.
#define TRFM_LIBRARY_TINYOLED_ENABLED


// TRFM_LIBRARY_EEPROM_ENABLED
// ----------------------------
// If you don't want to use the EEPROM to store settings (for example to save some bytecode), you 
// can simply comment the option below by placing // before it to turn this feature off. Be 
// aware settings will not be saved and every time the device is powered on it starts with the 
// defaults.
#define TRFM_LIBRARY_EEPROM_ENABLED


#ifndef __AVR_ATtiny85__
// TRFM_USE_SERIAL_NO_DISPLAY
// --------------------------
// If you don't want to use a display and use serial for output instead (this is called headless), 
// enable this option.
// Notice: Enabling serial without an (onboard) UART, such as Digispark with AtTiny85,
//         no serial output is possible!  
#define TRFM_USE_SERIAL_NO_DISPLAY
#define TRFM_USE_SERIAL_BAUDRATE 9600


 #ifdef TRFM_USE_SERIAL_NO_DISPLAY
  // TRFM_CMD_SERIAL_UI_ENABLED
  // --------------------------
  // If you want a serial user interface, you can enable this option. The device can
  // be controlled via serial monitor by typing simple commands. When the device
  // is turned on, the first thing this device will do is showing an overview of 
  // available commands.
  #define TRFM_CMD_SERIAL_UI_ENABLED
  #define TRFM_CMD_SERIAL_LEN_MAX            2
  // Commands:
  #define TRFM_CMD_SERIAL_HELP               "H" 
  #define TRFM_CMD_SERIAL_LONG_PRESS         "L"
  #define TRFM_CMD_SERIAL_SHORT_PRESS        "S"
  #define TRFM_CMD_SERIAL_NEXT_CHANNEL       "NC"
  #define TRFM_CMD_SERIAL_PREV_CHANNEL       "PC"
  #define TRFM_CMD_SERIAL_NEXT_SOUND_CARRIER "NS"
  #define TRFM_CMD_SERIAL_PREV_SOUND_CARRIER "PS"
  #define TRFM_CMD_SERIAL_TOGGLE_TESTMODE    "T"
  #define TRFM_CMD_SERIAL_RESET              "R"
 #endif
#endif


// TRFM_I2CADDR_RFMODULATOR
// ------------------------
// I2C address of RF-modulator
#define TRFM_I2CADDR_RFMODULATOR 0x65



// TRFM_I2CADDR_TINYOLED
// ----------------------
// I2C address of display
#define TRFM_I2CADDR_TINYOLED 0x3C



// TRFM_DISPLAY_TINYOLED_WIDTH
// ---------------------------
// Width of display in pixels
#define TRFM_DISPLAY_TINYOLED_WIDTH 128



// TRFM_DISPLAY_TINYOLED_HEIGHT
// ----------------------------
// Height of display in pixels
#define TRFM_DISPLAY_TINYOLED_HEIGHT 32



// EEPROM HEADER AND INDEXES
// -------------------------
// EEPROM header and storage locations. A structure header is used to be able to detect
// EEPROM data is present and valid. Only 'mess' with these settings if you know what 
// you are doing.
#define TRFM_EEVAL_HDMAGIC1        0x52 // 'R' --|
#define TRFM_EEVAL_HDMAGIC2        0x4D // 'M' --|--- Structure header identification  
#define TRFM_EECFG_HDMAGIC1        0x00 // Location of header in EEPROM (1)
#define TRFM_EECFG_HDMAGIC2        0x01 // Location of header in EEPROM (2)
#define TRFM_EECFG_SOUNDCARRIER    0x02 // Location of Sound Carrier setting in EEPROM
#define TRFM_EECFG_CHANNEL         0x03 // Location of Channel setting in EEPROM
#define TRFM_EECFG_TESTMODE        0x04 // Location of Testmode setting in EEPROM



// TRFM_GUI_LANGUAGE
// -----------------
// Language of the user interface, select just one.
// (default is TRFM_GUI_LANGUAGE_EN) If you want to create your own translation, 
// take a look at the TinyRFModulator.lang.h file.
// Notice: It is possible translations are not that accurate because of missing
//         font characters or in depth knowledge about a (not natively known) 
//         language. Feel free to rectify possible errors in grammar. 
#define TRFM_GUI_LANGUAGE_EN // English (default) 
//#define TRFM_GUI_LANGUAGE_NL // Dutch
//#define TRFM_GUI_LANGUAGE_DE // German
//#define TRFM_GUI_LANGUAGE_FR // French
//#define TRFM_GUI_LANGUAGE_IT // Italian



// TRFM_CHANNEL_DEFAULT
// --------------------
// When starting the device for the first time, no EEPROM storage is used/available 
// or user performs a reset, this channel default is applied. If you want to change
// the default channel, use a value between 21 and 69. 
// Notice: 
// o For an overview of channels and corresponding frequency, take a look at 
//   "uhf-channel-frequency-bands.png" in the "doc" directory of this project.
// o Setting the option with out of bound values, will default to min or max value,
//   for example:
//   - Greater than 69 will default to 21
//   - Less than 21 will default to 69   
#define TRFM_CHANNEL_DEFAULT 21


// TRFM_SOUND_CARRIER_DEFAULT | TRFM_SOUND_CARRIER_DIGITAL
// -------------------------------------------------------
// When starting the device for the first time, no EEPROM storage is used/available or
// user performs a reset, this sound carrier default is applied. If you want to change
// this, use a value of:
// - TRFM_SOUND_CARRIER_MIN        (which is actually 4.5Mhz)
// - TRFM_SOUND_CARRIER_4_5MHZ     
// - TRFM_SOUND_CARRIER_5_5MHZ     
// - TRFM_SOUND_CARRIER_6_0MHZ     
// - TRFM_SOUND_CARRIER_6_5MHZ     
// - TRFM_SOUND_CARRIER_MAX        (which is actually 6.5Mhz)
// Notice: 
// o Older TV equipment (analog tuning) can handle only one of the lower frequencies 
//   (5.5 or lower). Using a non supported frequency will result in poor picture quality
//   and audio quality (noise or no audio);
// o TV equipment with a digital tuner (and auto-scan) can handle almost all frequencies 
//   (highest = best quality). However, once the channel is discovered by TV equipment, 
//   changing the sound carrier will result in poor picture quality and sound quality. 
//   In order to change the sound carrier, you need to set the sound carrier first on 
//   the device and after this perform an auto-scan on TV equipment.
// o At default the sound carrier is set to 5.5Mhz to cover most TV equipment and
//   to provide maximum compatibility. 
// o When option TRFM_GUI_NEXT_CARRIER_ENABLED is disabled, the device will ask the 
//   user what kind of tuner is connected, Analog (manual dial, older technology) 
//   or Digital (auto tune, newer technology). When user select digital, the option
//   TRFM_SOUND_CARRIER_DIGITAL will be used instead of TRFM_SOUND_CARRIER_DEFAULT.        
#define TRFM_SOUND_CARRIER_DEFAULT TRFM_SOUND_CARRIER_5_5MHZ
#define TRFM_SOUND_CARRIER_DIGITAL TRFM_SOUND_CARRIER_MAX



// TRFM_TESTMODE_DEFAULT
// ---------------------
// Normally, test-mode is not applied when starting the device for the first time or
// user performs a reset. If you want to change this default to test-mode, change false
// into true. 
#define TRFM_TESTMODE_DEFAULT false



// TRFM_EXTERNAL_LED_ENABLED
// -------------------------
// The device uses an external LED for status or action notification to its user. If you 
// don't like a blinky LED (or for some other reason), you can turn this feature off by 
// comment this option (add // before #define).
#define TRFM_EXTERNAL_LED_ENABLED



// TRFM_GUI_NEXT_SOUND_CARRIER_ENABLED
// -----------------------------------
// At default the "set next sound carrier" function is disabled because it can be 
// a little confusing to use. This is replaced by a question at the first boot, 
// or at boot when EEPROM is disabled or at performing a reset. See also option
// TRFM_GUI_ASK_SOUND_CARRIER_SETTING below. However, if you want full control you
// can enable it again by uncomment the option below:
//#define TRFM_GUI_NEXT_SOUND_CARRIER_ENABLED


#ifndef TRFM_GUI_NEXT_SOUND_CARRIER_ENABLED
 
 // TRFM_GUI_ASK_SOUND_CARRIER_SETTING
 // ----------------------------------
 // Like explained already at the TRFM_GUI_NEXT_CARRIER_ENABLED option, device 
 // asks a question to set the sound carrier properly. Question is:
 // "Connected tuner:" and user can select between "ANALOG" (default) or "DIGITAL".
 // When selecting digital, the option TRFM_SOUND_CARRIER_DIGITAL is applied.
 // When selecting analog (or do nothing), the option TRFM_SOUND_CARRIER_DEFAULT
 // will be applied.  
 // If you don't want this question, comment option below by placing // before it.
 // Notice: By disabling this option, default TRFM_SOUND_CARRIER_DEFAULT will be 
 //         applied.
 #define TRFM_GUI_ASK_SOUND_CARRIER_SETTING
 
 
 // TRFM_GUI_ASK_SOUND_CARRIER_TIMEOUT
 // ----------------------------------
 // Question timeout in seconds before apply default selection. This can be a value
 // between 1 to 10. Feel free to change it, use a value between 1 and 20. 
 #define TRFM_GUI_ASK_SOUND_CARRIER_TIMEOUT 10

#endif // /TRFM_GUI_NEXT_CARRIER_ENABLED


// TRFM_RESET_KEEP_CURRENT_MODE
// -----------------------------
// Normally, when user performs a reset, mode change back to default when in testmode.
// If you don't want this behaviour and keep the current mode, uncomment this option
// by removing // before it.
//#define TRFM_RESET_KEEP_CURRENT_MODE



// TRFM_EEPROM_SAVE_TIMEOUT
// ------------------------
// In milliseconds. Approx. 10 Seconds save timeout to minimize EEPROM cell wear when settings 
// changes rapidly (by user) within 10 seconds, for example when changing channel several
// times. Globally a button press extends this timeout until 10 seconds of inactivity. 
// Change this value if you think 10 seconds is too low or too high.
// Notice: Removing power (or power loss) during the delay period will leave settings unchanged.
//         When power is connected again, device will start with last stored settings.           
#define TRFM_EEPROM_SAVE_TIMEOUT    10000UL 



// TRFM_SCREENSAVER_TIMEOUT
// ------------------------
// In milliseconds, turn off screen after 1 minute of inactivity. To wake up the screen again, 
// user have to push the button once. Set define to zero (0) (or comment it) if you don't want 
// this behaviour. Increase this value for a longer timeout.
// Important notice: 
// - Disabling this, effects also the TRFM_SCREENSAVER_DEEP_SLEEP option (see below this option);
// - This feature is disabled when device runs headless (TRFM_USE_SERIAL_NO_DISPLAY) 
#define TRFM_SCREENSAVER_TIMEOUT  60000UL  



// TRFM_SCREENSAVER_DEEP_SLEEP
// ---------------------------
// To take the savings a bit advanced, at least 20mA of power consumption can be saved at 
// user inactivity. Notice that RF-modulator will not be turned off, only the MCU (GUI)
// goes to sleep. To wake up the GUI again, user have to push the button once.
// Important notice: 
//  1. Works only on an AtTiny MCU (however you are able to write your own sleep method);
//  2. When the option TRFM_SCREENSAVER_TIMEOUT is disabled, this behaviour is also disabled!     
//  3. Effects the behaviour of the external LED when in test-mode because the loop() function
//     is no longer executed in sleep mode.
//  4. This feature is disabled when device runs headless (TRFM_USE_SERIAL_NO_DISPLAY) 
// If you don't want this behaviour, comment option below by placing // before it.
#define TRFM_SCREENSAVER_DEEP_SLEEP  



// TRFM_BTN_DEBOUNCE_DELAY
// -----------------------
// In milliseconds. Debounce delay, rate-limiting or throttling the frequency of registering
// a single button press. If you have problems accurate access the device it's functions, you 
// can change this value. 
// Notice: Changing this value also effects the duration of triggering threshold to access
//         the device it's functions.    
#define TRFM_BTN_DEBOUNCE_DELAY 200



// TRFM_BTN_THRESHOLD_RESET
// ------------------------
// Number of times a button needs to be hold to access the reset functionality. The duration
// of hold relies on the value of TRFM_BTN_DEBOUNCE_DELAY, in this case 
// (default) 20*TRFM_BTN_THRESHOLD_RESET = approx. 4000ms = 4 seconds. In practice this is 
// about 5 seconds. 
#define TRFM_BTN_THRESHOLD_RESET 20



// TRFM_BTN_THRESHOLD_TESTMODE
// ---------------------------
// Number of times a button needs to be hold to access the testmode functionality. The duration
// of hold relies on the value of TRFM_BTN_DEBOUNCE_DELAY, in this case 
// (default) 10*TRFM_BTN_THRESHOLD_RESET = approx. 2000ms = 2 seconds. In practice this is 
// about 3 seconds. 
#define TRFM_BTN_THRESHOLD_TESTMODE 10



// TRFM_BTN_THRESHOLD_NEXT_SOUND_CARRIER
// -------------------------------------
// Number of times a button needs to be hold to access the next sound carrier functionality. 
// The duration of hold relies on the value of TRFM_BTN_DEBOUNCE_DELAY, in this case 
// (default) 5*TRFM_BTN_THRESHOLD_RESET = approx. 1000ms = 1 second. In practice this is 
// about 2 seconds.
// Notice: At default this functionality is disabled, see also option 
//         TRFM_GUI_NEXT_CARRIER_ENABLED  
#define TRFM_BTN_THRESHOLD_NEXT_SOUND_CARRIER 5



// TRFM_BTN_THRESHOLD_HOLD_MAX
// ---------------------------
// Maximum number of times a button can be hold to register it as one press cycle. The duration
// of hold relies on the value of TRFM_BTN_DEBOUNCE_DELAY. This value needs to be equal or 
// higher than the longest press assigned to access a functionality. This option cannot exceed
// 254, maximum value is 254. After this cutoff event, the user needs to release the button first 
// to reactivate the button press/hold detection cyclus and to be able to use the button again to 
// access functions.
#define TRFM_BTN_THRESHOLD_HOLD_MAX (uint8_t)TRFM_BTN_THRESHOLD_RESET



// -- LIBRARY STUFF -------------------------------------------------------------------------

#ifdef TRFM_USE_SERIAL_NO_DISPLAY
 void displaySetCursor(uint8_t x, uint8_t y)
 {
   static int8_t lastX = -1;
   static int8_t lastY = -1;
   if( y != lastY )
    { 
      lastY = y;
      lastX = 0;
      Serial.println("");
    }  
   
   y=0;
   while( lastX < x )
   {
      if( y < 10 )
       { Serial.print( " " ); ++y; }
      ++lastX;
   }
 }
 
 #ifdef TRFM_CMD_SERIAL_UI_ENABLED
  #define displayBegin()       while(!Serial){} Serial.begin(TRFM_USE_SERIAL_BAUDRATE); displayHelp()
 #else
  #define displayBegin()       while(!Serial){} Serial.begin(TRFM_USE_SERIAL_BAUDRATE)
 #endif
 
 #define displayClear()        Serial.println("\n-------------")
 //#define displaySetCursor(x,y) Serial.println("")
 #define displayPrint(s)       Serial.print(s)
 #define displayEnable()       Serial.println("DISPLAY ENABLED/AWAKE")  
 #define displayDisable()      Serial.println("DISPLAY DISABLED/SLEEP")  
#elif defined TRFM_LIBRARY_TINYOLED_ENABLED
 #include "TinyOLED.h"

 #define displayBegin() oled.begin( TRFM_I2CADDR_TINYOLED, \
                                    TRFM_DISPLAY_TINYOLED_WIDTH, \
                                    TRFM_DISPLAY_TINYOLED_HEIGHT \
                                  )
 #define displayClear()        oled.clear()
 #define displaySetCursor(x,y) oled.setCursor(x,y)
 #define displayPrint(s)       oled.print(s)
 #define displayEnable()       oled.show()  
 #define displayDisable()      oled.hide()  
#endif

#include "TinyRFModulator.h"
#include "TinyRFModulator.lang.h"

#ifdef __AVR_ATtiny85__
 
  // Use TinyWireM, smaller and don't freeze when display is disconnected
  // If you don't have it installed yet, take a look in the lib folder.
 #include <TinyWireM.h>        
 #define  Wire TinyWireM      
 
 #ifdef TRFM_LIBRARY_EEPROM_ENABLED 
   // Fix some problems with EEPROM, something has changed in IDE.
   // That is why EEPROM.h is included in the source code package.
   #include "lib/EEPROM.h"       
   
   #define EEPROMBegin()     EEPROM.begin()
   #define EEPROMRead(n)     EEPROM.read(n)
   #define EEPROMUpdate(n,u) EEPROM.update(n,u)
   #define EEPROMEndWrite()  
 #endif
 
 #ifdef TRFM_SCREENSAVER_DEEP_SLEEP
  #include <avr/sleep.h>
 #endif

#else
  // Other MCU 
 #include <Wire.h>
 
 #ifdef TRFM_LIBRARY_EEPROM_ENABLED 
  // if compiling breaks here and you using a Nordic chipset,
  // take a look at: https://github.com/d00616/arduino-NVM
  // or uncomment define TRFM_LIBRARY_EEPROM_ENABLED at the
  // top of this file to disable EEPROM functionality.
  #include <EEPROM.h>

  #if defined(ESP8266) || defined(ESP8285) || defined(ESP32)
   //#include <pgmspace.h>
   #define EEPROMBegin()     EEPROM.begin(16)
   #define EEPROMRead(n)     EEPROM.read(n)
   #define EEPROMUpdate(n,u) if( EEPROM.read(n) != u) EEPROM.write(n,u)
   #define EEPROMEndWrite()  EEPROM.commit() 
  #else
   #define EEPROMBegin()     EEPROM.begin()
   #define EEPROMRead(n)     EEPROM.read(n)
   #define EEPROMUpdate(n,u) EEPROM.update(n,u)
   #define EEPROMEndWrite()  
  #endif // /ESP
 #endif // /TRFM_LIBRARY_EEPROM_ENABLED
#endif // /__AVR_ATtiny85__
  
