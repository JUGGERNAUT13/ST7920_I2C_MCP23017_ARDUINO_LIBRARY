#ifndef ST7920_I2C_MCP23017_GLCD_H
	#define ST7920_I2C_MCP23017_GLCD_H
	
	#if defined(ARDUINO) && ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include <WProgram.h>
	#endif

	#include <Wire.h>
	
	#define IODIRA   			0x00   	// IO direction  (0 = output, 1 = input (Default))
	#define IODIRB   			0x01
	#define GPIOA    			0x12   	// Port value. Write to change, read to obtain value
	#define GPIOB    			0x13
	#define delay_time    		80   	// default settling time in uS after a command is sent
	#define SWAP(x,y) do { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); } while(0)
		
	class ST7920_I2C_MCP23017_GLCD {
		public:
			GLCD();
			void init_display(const byte port = 0x20, const byte i2cAddress = 0);
			void set_inverse(boolean inv);
			void set_rotate_180(boolean rot);
			void goto_x_y(uint8_t x, uint8_t y);
			void draw_pixel(uint8_t x, uint8_t y);
			void clear_pixel(uint8_t x, uint8_t y);
			void write_number_x_y(uint8_t x, uint8_t y, uint8_t number);
			void write_lnumber_x_y(uint8_t x, uint8_t y, uint16_t number);
			void write_char(int x, int y, uint8_t num_0, uint8_t num_1, uint8_t num_2, uint8_t num_3);
			void write_char_x_y(uint8_t x, uint8_t y, uint8_t number);
			void write_gnumber_x_y(uint8_t x, uint8_t y, uint16_t number);
			void clear_screen(void);
			void set_cursour(int symb, int str);
			void write_string(char * s);
			void draw_line(int x1, int y1, int x2, int y2);
			void draw_frame(int x, int y, int width, int height);
			void draw_box(int x, int y, int width, int height);
			void draw_circle(int x0, int y0, int r);
			void draw_filled_circle(int x0, int y0, int radius);
			void draw_ellipse(int xc, int yc, int w, int h);
			void draw_filled_ellipse(int x0, int y0, int el_width, int el_height);
			void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2);
			void draw_filled_triangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
			void draw_rounded_frame(int x, int y, int w, int h, int r);
			void draw_filled_rounded_box(int x, int y, int w, int h, int r);
			void draw_bitmap(const uint16_t bitmap[], int w, int h);
		private:
			uint16_t reverse_bits(uint16_t value);
			uint16_t read_word(uint8_t type);
			uint8_t read_GPIO(uint8_t b);
			uint8_t i2c_read(void);
			void write_data(uint8_t data);
			void write_word(int x, int y, uint16_t data);
			void glcd_enable(void);
			void set_en_low(void);
			void set_en_high(void);
			void set_rs_low(void);
			void set_rs_high(void);
			void set_rw_low(void);
			void set_rw_high(void);
			void toggle_e(void);
			void cdisplay_clear(void);
			void set_cgram_address(uint8_t x, uint8_t y);
			void clcd_init(void);
			void glcd_fill(int x_l, int x_h, int y_l, int y_h, uint16_t value);
			void write_wdata(uint16_t data);
			void i2c_write(int data);
			void start_send(void);
			void do_send(const byte what);
			void end_send(void);
			void expander_write(const byte reg, const byte data);
			void draw_letter(byte c, int str, int symb);
			void draw_horizontal_line(uint8_t x1, uint8_t x2, uint8_t y);
			void draw_vertical_line(uint8_t x, uint8_t y1, uint8_t y2);
			void draw_circle_by_quartes(int x0, int y0, int r, int q);
			void draw_filled_circle_by_semicircles(int x0, int y0, int rad, int q);
			//global variables
			uint16_t packed_number[4];
			byte _port;
			byte i2caddr;
			int symbol_pos = 0;
			int char_numb = 0;
			int string_numb = 0;
			int state = 0x1C;		//or (state = 0x14) for 8-bit mode/4-bit mode (state = 0x18 or (state = 0x10) for SPI mode)
			int old_string_numb;
			bool rs_high = false;
			bool rw_high = false;
			bool en_high = false;
			bool inversed = false;
			bool rotated = false;
			bool forced_str_position = false;
	};
#endif