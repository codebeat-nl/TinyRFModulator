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


#ifndef TINYOLEDLIB_H
#define TINYOLEDLIB_H

// #define _nofont_8x16		
#ifndef _nofont_8x16	
 #define FONT8X16		1
#endif
 #define FONT6X8		0

// ----------------------------------------------------------------------------

#define TOL_DEF_DISPLAY_ADDR        0x3C // Slave address
#define TOL_MAX_DISPLAY_WIDTH       128
//#define TOL_MAX_DISPLAY_HEIGHT    64
#define TOL_MAX_DISPLAY_HEIGHT      32


#define TOL_COMMAND                 0x00
#define TOL_DATA                    0xC0
#define TOL_DATA_CONTINUE           0x40
#define TOL_SET_CURSOR_Y            0xB0
#define TOL_SET_CURSOR_X            0xF0


#define TOL_USE_DEFAULT             0

// *** SSD1306 commands ***

 //next byte is a command only
#define TED_COMMAND_ONLY            TOL_COMMAND       
 //next byte is data
#define TED_DATA_ONLY               TOL_DATA_CONTINUE  

// Fundamental Commands
#define TOL_SET_CONTRAST_CONTROL                  0x81
#define TOL_DISPLAY_ALL_ON_RESUME                 0xA4
#define TOL_DISPLAY_ALL_ON                        0xA5
#define TOL_NORMAL_DISPLAY                        0xA6
#define TOL_INVERT_DISPLAY                        0xA7
#define TOL_SET_MULTPLEX_RATIO                    0xA8
#define TOL_DISPLAY_OFF                           0xAE
#define TOL_DISPLAY_ON                            0xAF
#define TOL_NOP_CMD                               0xE3

// Scrolling Commands
#define TOL_HORIZONTAL_SCROLL_RIGHT               0x26
#define TOL_HORIZONTAL_SCROLL_LEFT                0x27
#define TOL_HORIZONTAL_SCROLL_VERTICAL_AND_RIGHT  0x29
#define TOL_HORIZONTAL_SCROLL_VERTICAL_AND_LEFT   0x2A
#define TOL_DEACTIVATE_SCROLL                     0x2E
#define TOL_ACTIVATE_SCROLL                       0x2F
#define TOL_SET_VERTICAL_SCROLL_AREA              0xA3

// Addressing Setting Commands
#define TOL_SET_PAGE_START_ADDRESS                0xB0
#define TOL_SET_LOWER_COLUMN                      0x00
#define TOL_SET_HIGHER_COLUMN                     0x10
#define TOL_MEMORY_ADDR_MODE                      0x20
#define TOL_SET_COLUMN_ADDR                       0x21
#define TOL_SET_PAGE_ADDR                         0x22

// Hardware Configuration Commands
#define TOL_SET_START_LINE                        0x40
#define TOL_SET_SEGMENT_REMAP                     0xA0
#define TOL_SET_MULTIPLEX_RATIO                   0xA8
#define TOL_COM_SCAN_DIR_INC                      0xC0
#define TOL_COM_SCAN_DIR_DEC                      0xC8
#define TOL_SET_DISPLAY_OFFSET                    0xD3
#define TOL_SET_COM_PINS                          0xDA
#define TOL_CHARGE_PUMP                           0x8D

// Timing & Driving Scheme Setting Commands
#define TOL_SET_DISPLAY_CLOCK_DIV_RATIO           0xD5
#define TOL_SET_PRECHARGE_PERIOD                  0xD9
#define TOL_SET_VCOM_DETECT                       0xDB


// ----------------------------------------------------------------------------

class SSD1306Device: public Print {

    public:
		SSD1306Device();

    uint8_t addr     = TOL_DEF_DISPLAY_ADDR;
    uint8_t oledFont = FONT6X8;
    uint8_t oledX    = 0;
    uint8_t oledY    = 0;
    uint8_t width    = TOL_MAX_DISPLAY_WIDTH;  // default width (128px)
    uint8_t height   = TOL_MAX_DISPLAY_HEIGHT; // default height (32px)
    
		void setFont(uint8_t font);

    void sendStartCmd();
    void sendDataStartCmd();
    void sendDataByte( uint8_t iData );
    void sendPgmFontChar( uint8_t* pFont, uint16_t iIndex );
    void sendStopCmd();
		
		void cmd( uint8_t iCmd );
    void set( uint8_t iCmd, uint8_t iValue1, uint8_t iValue2 );
    void set( uint8_t iCmd, uint8_t iValue );
    void set( uint8_t iCmd );
		
		void setCursor(uint8_t x, uint8_t y);

    void show( bool bVisible = true );
    void hide();
		
		void fill( uint8_t fill = 0x00 );
		void clear();
		void bitmap(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[]);
		
		virtual size_t write(uint8_t c); using Print::write;

    void begin( uint8_t iAddr   = TOL_DEF_DISPLAY_ADDR,
                uint8_t iWidth  = TOL_MAX_DISPLAY_WIDTH, 
                uint8_t iHeight = TOL_MAX_DISPLAY_HEIGHT
              );
};


extern SSD1306Device oled;

// ----------------------------------------------------------------------------

#endif
