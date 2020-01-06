/*
 * SSD1306Device - Driver for SSD1306 controlled dot matrix OLED/PLED displays
 *
 * @created: 2014-08-12
 * @author: Neven Boyanov
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 * @updated    : 2019-11-09
 * @modified by: codebeat
 * @changelog  : Some optimalization, name changes, scope changes,
 *               bug fixing and support for 32 pixels displays
 *               added.
 * @notice     : Quality not approved, class works OK however needs a better 
 *               implementation at several areas.
 *               For now it is suitable for this project however don't
 *               use this class for other purposes.
 */

// ----------------------------------------------------------------------------

#ifdef __AVR_ATtiny85__
 #include <TinyWireM.h>   // Use TinyWireM, smaller and don't freeze when display is disconnected
 #define  Wire TinyWireM
#else
 #include <Wire.h>
#endif

#ifdef __AVR__
 #include <avr/pgmspace.h>
#endif


#include "TinyOLED.h"
#include "fonts/font6x8.h"

#define _nofont_8x16  // Important, we don't need big fonts in this project,
                      // saves us 1662 bytes program space

#ifndef _nofont_8x16	// Optional, removal to save code space
#include "fonts/font8x16.h"
#endif


// ----------------------------------------------------------------------------

// Some code based on "IIC_wtihout_ACK" by http://www.14blog.com/archives/1358

const uint8_t __SSD1306_INIT[] PROGMEM = {	// Initialization Sequence
	TOL_DISPLAY_OFF,			        // Display OFF (sleep mode)
	TOL_MEMORY_ADDR_MODE,         // Set Memory Addressing Mode
	    0B00,		                  // --- 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
					                      // --- 10=Page Addressing Mode (RESET); 11=Invalid
	TOL_SET_PAGE_START_ADDRESS,		// Set Page Start Address for Page Addressing Mode, 0-7
	TOL_COM_SCAN_DIR_DEC,			    // Set COM Output Scan Direction
	    0x00,                     // --- set low column address
	    0x10,			                // --- set high column address
	    0x40,                     // --- set start line address
	TOL_SET_CONTRAST_CONTROL,     // Set contrast control register
	    0x3F,                     
	0xA1,			                    // Set Segment Re-map. A0=address mapped; A1=address 127 mapped. 
	0xA6,			                    // Set display mode. A6=Normal; A7=Inverse
	TOL_SET_MULTPLEX_RATIO,       // Set multiplex ratio(1 to 64)
	    0x3F,		
	0xA4,			                    // Output RAM to Display
					                      // 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
	TOL_SET_DISPLAY_OFFSET,       // Set display offset. 00 = no offset
	    0x00,		                  // --- set no offset
	    0xD5,			                // --- set display clock divide ratio/oscillator frequency
	    0xF0,			                // --- set divide ratio
	0xD9, 0x22,		                // Set pre-charge period
	TOL_SET_COM_PINS,             // Set com pins hardware configuration
	    0x12,                     		
	0xDB,			                    // --set vcomhset
	TOL_MEMORY_ADDR_MODE,			    // 0x20,0.77xVcc
	TOL_CHARGE_PUMP,              // Set DC-DC enable <-- ????? 
	    0x14,		
	TOL_DISPLAY_ON			          // Display ON in normal mode
};


SSD1306Device::SSD1306Device(){}

void SSD1306Device::begin( uint8_t iAddr /* = TOL_DEF_DISPLAY_ADDR */,
                           uint8_t iWidth /* = TOL_MAX_DISPLAY_WIDTH */, 
                           uint8_t iHeight /* = TOL_MAX_DISPLAY_HEIGHT */ 
                         )
{
	//Wire.begin();
  addr   = iAddr;
  width  = iWidth;
  height = iHeight; 
  
	for (uint8_t i = 0; i < sizeof (__SSD1306_INIT); i++) {
		cmd(pgm_read_byte(&__SSD1306_INIT[i]));
	}
  
  //set( TOL_SET_MULTIPLEX_RATIO, height-1 );
  //set( TOL_SET_COM_PINS       , ( height > 32 )?0x12:0x02 );
  cmd( TOL_SET_MULTIPLEX_RATIO ); cmd( height-1 );
  cmd( TOL_SET_COM_PINS );        cmd( height > 32 ?0x12:0x02 );
  
	clear();
}


void SSD1306Device::setFont(uint8_t font)
{
	oledFont = font;
}

void SSD1306Device::sendStartCmd(void) 
{
	Wire.beginTransmission( addr );
	Wire.write( TOL_COMMAND );	// write command
}

void SSD1306Device::sendDataStartCmd(void)
{
  Wire.beginTransmission( addr );
  Wire.write( TOL_DATA_CONTINUE ); //write data
}

void SSD1306Device::sendDataByte(uint8_t iData)
{
	//#ifndef __TOL_TINYWIRE_USED
	//if(Wire.writeAvailable())
	//{
		sendStopCmd();
		sendDataStartCmd();
	//}
  //#endif
	Wire.write(iData);
	
}

void SSD1306Device::sendPgmFontChar(uint8_t* pFont, uint16_t iIndex )
{
  sendDataByte(pgm_read_byte(pFont+iIndex));
}

void SSD1306Device::sendStopCmd()
{
  Wire.endTransmission();
}


void SSD1306Device::cmd( uint8_t iCmd )
{
	sendStartCmd();
	Wire.write( iCmd );
	sendStopCmd();
}

void SSD1306Device::set( uint8_t iCmd, uint8_t iValue1, uint8_t iValue2 )
{
  cmd( iCmd );
  cmd( iValue1 );
  cmd( iValue2 );
}

void SSD1306Device::set( uint8_t iCmd, uint8_t iValue )
{
  cmd( iCmd );
  cmd( iValue );
}

void SSD1306Device::set( uint8_t iCmd )
{
  cmd( iCmd );
}

void SSD1306Device::setCursor(uint8_t x, uint8_t y)
{
	sendStartCmd();
  Wire.write(0xb0 + y);
  Wire.write(((x & 0xf0) >> 4) | 0x10); // | 0x10
  Wire.write((x & 0x0f) | 0x01); // | 0x01
	sendStopCmd();
	oledX = x;
	oledY = y;
}



void  SSD1306Device::show( bool bVisible /* default = true */ )
{ cmd( bVisible?TOL_DISPLAY_ON:TOL_DISPLAY_OFF ); }

void  SSD1306Device::hide()
{ show( false ); }

void SSD1306Device::clear()
{ fill(); }

void SSD1306Device::fill(uint8_t fill /* = 0x00 */ )
{
	uint8_t m,n;
	
	if( fill == 0x00 ) 
   { hide(); }
   
	for (m = 0; m < 8; m++)
	{
		cmd(0xb0 + m);	// page0 - page1
		cmd(0x00);		// low column start address
		cmd(0x10);		// high column start address
		sendDataStartCmd();
		for (n = 0; n < width; n++)
		{
			sendDataByte(fill);
		}
		sendStopCmd();
	}
	
	setCursor(0, 0);
  
  if( fill == 0x00 ) 
   show();
}

size_t SSD1306Device::write(uint8_t c) 
{
	uint8_t i = 0;
	uint8_t ci = c - 32;
	
	if(c == '\r')
		{ return 1; }
	
	if(c == '\n')
	{
		if(oledFont == FONT6X8) 
		 {	oledY++; }
		else {
			     oledY+=2;	// Large Font up by two
			     if( oledY > 6) 				     
			      { oledY = 6; }
			   }
		    
		setCursor(0, oledY );
		return 1;
	}

  if(oledFont == FONT6X8)
	{
 		if (oledX > 122)
		{
			oledX = 0;
			oledY++;
			if ( oledY > 7) 
				oledY = 7;
			setCursor(oledX, oledY);
		}

    //setChar(c, oledX, oledY ); 
    
		sendDataStartCmd();
		for (i= 0; i < 6; i++)
		{
			//sendDataByte(pgm_read_byte(&ssd1306xled_font6x8[ci * 6 + i]));
		  sendPgmFontChar((uint8_t*)&ssd1306xled_font6x8, ci * 6 + i);
		}
		sendStopCmd();
		
    
		//oledX+=6;
		setCursor(oledX+6, oledY);
	}

  #ifndef _nofont_8x16
	else {
		     if (oledX > 120)
		     {
			     oledX = 0;
			     oledY+=2;	// Large Font up by two
           //	oledY++;	
			    if ( oledY > 6) // tBUG
				   oledY = 6;
			    setCursor(oledX, oledY);
		     }
		     
		     
		     sendDataStartCmd();
		     for (i = 0; i < 8; i++)
		      {  //Wire.write(pgm_read_byte(&ssd1306xled_font8x16[ci * 16 + i])); 
		         sendPgmFontChar((uint8_t*)&ssd1306xled_font8x16, ci * 16 + i);

		      }
		     sendStopCmd();
		     setCursor(oledX, oledY + 1);
		     sendDataStartCmd();
		     for (i = 0; i < 8; i++)
		      { 
		        //Wire.write(pgm_read_byte(&ssd1306xled_font8x16[ci * 16 + i + 8])); 
		        sendPgmFontChar((uint8_t*)&ssd1306xled_font8x16,ci * 16 + i + 8);
		      }
		     sendStopCmd();
		     setCursor(oledX + 8, oledY - 1);
	     }
  #endif
	
	return 1;
}

void SSD1306Device::bitmap(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[])
{
	uint16_t j = 0;
	uint8_t y, x;
	// if (y1 % 8 == 0) y = y1 / 8; 	// else y = y1 / 8 + 1;		// tBUG :: this does nothing as y is initialized below
	//	THIS PARAM rule on y makes any adjustment here WRONG   //usage oled.bitmap(START X IN PIXELS, START Y IN ROWS OF 8 PIXELS, END X IN PIXELS, END Y IN ROWS OF 8 PIXELS, IMAGE ARRAY);
 	for (y = y0; y < y1; y++)
	{
		setCursor(x0,y);
		sendDataStartCmd();
		for (x = x0; x < x1; x++)
		{
			sendDataByte(pgm_read_byte(&bitmap[j++]));
		}
		sendStopCmd();
	}
	setCursor(0, 0);
}


SSD1306Device oled;

// ----------------------------------------------------------------------------
