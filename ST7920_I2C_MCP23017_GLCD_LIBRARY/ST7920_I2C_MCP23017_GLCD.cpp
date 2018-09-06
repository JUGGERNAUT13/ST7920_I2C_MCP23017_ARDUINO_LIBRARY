#include "Arduino.h"
#include <ST7920_I2C_MCP23017_GLCD.h>
#include <fonts.h>

ST7920_I2C_MCP23017_GLCD::GLCD() {}
	
void ST7920_I2C_MCP23017_GLCD::init_display(const byte port, const byte i2cAddress) {
	_port = port;   				// remember port
	i2caddr = i2cAddress;			// remember device address
	Wire.begin(i2caddr);
	Wire.setClock(195000);			//works for ATMEGA 2560
	expander_write(IODIRA, 0);
	expander_write(GPIOA, 0);
	expander_write(IODIRB, 0);
	expander_write(GPIOB, 0);
	clcd_init();					// initialize as character display
	cdisplay_clear();   
	glcd_enable();
	clear_screen();
}

uint8_t ST7920_I2C_MCP23017_GLCD::i2c_read() {
	#if defined(ARDUINO) && ARDUINO >= 100
		if(inversed == true) {
			return (Wire.read() ^ 0xFF);
		} else {
			return Wire.read();
		}
	#else
		if(inversed == true) {
			return (Wire.receive() ^ 0xFF);
		} else {
			return Wire.receive();
		}
	#endif
}

void ST7920_I2C_MCP23017_GLCD::i2c_write(int data) {
	#if defined(ARDUINO) && ARDUINO >= 100
		Wire.write(data);
	#else
		Wire.send(data);
	#endif
}

void ST7920_I2C_MCP23017_GLCD::start_send() {
	Wire.beginTransmission(_port); 
} 

void ST7920_I2C_MCP23017_GLCD::do_send(const byte what) {
	i2c_write(what);
} 

void ST7920_I2C_MCP23017_GLCD::end_send() {
	Wire.endTransmission();		
}

void ST7920_I2C_MCP23017_GLCD::expander_write(const byte reg, const byte data) {
	start_send();
	do_send(reg);
	do_send(data);
	end_send();
}

uint8_t ST7920_I2C_MCP23017_GLCD::read_GPIO(uint8_t b) {
	Wire.beginTransmission(_port | i2caddr);	// read the current GPIO output latches
	if(b == 0) {
		i2c_write(GPIOA);
	} else {
		i2c_write(GPIOB);
	}
	Wire.endTransmission();
	Wire.requestFrom(_port | i2caddr, 1);
	return i2c_read();
} 

void ST7920_I2C_MCP23017_GLCD::set_inverse(boolean inv) {
	inversed = inv;
}

void ST7920_I2C_MCP23017_GLCD::set_rotate_180(boolean rot) {
	rotated = rot;
}

void ST7920_I2C_MCP23017_GLCD::set_rs_high() {
	if(rs_high == false) {
		state = state + 0x20;
		expander_write(GPIOA, state);
		rs_high = true;
		_delay_us(delay_time);
	}
}

uint16_t ST7920_I2C_MCP23017_GLCD::read_word(uint8_t type) {
	uint8_t i, j = 0;
	uint16_t temp;
	expander_write(IODIRB, 0xFF);   // set data port for input
	expander_write(GPIOB, 0x00);
	set_en_low();
	if(type == 0) {
		set_rs_low();
	} else {
		set_rs_high();
	}
	set_rw_high();
	set_en_high();            		// toggle byte in  	
	i = read_GPIO(1);		// need I read this twice?
	set_en_low();
	set_en_high();
	i = read_GPIO(1);
	set_en_low();
	_delay_ms(1);
	set_en_high();
	j = read_GPIO(1);
	set_en_low();
	temp = j;
	temp = temp | (i << 8);
	return(temp);    // return byte read
}

void ST7920_I2C_MCP23017_GLCD::write_word(int x, int y, uint16_t data) {
	expander_write(IODIRB, 0);	// set data port for output
	set_en_low();
	set_rs_low();
	set_rw_low();
	if(y > 31) {
		y -= 32;
		x += 8;
	}
	x |= 0x80;
	y |= 0x80;
	expander_write(GPIOB, y);	// Set vertical DDRAM address
	toggle_e();  
	expander_write(GPIOB, x);	// Set horizontal DDRAM address
	toggle_e();
	set_rs_high();    				// Signal for WRITE
	if(inversed == true) {
		expander_write(GPIOB, ((data >> 8) ^ 0xFF));		// Set horizontal DDRAM address
		toggle_e();
		expander_write(GPIOB, (data ^ 0xFF));		// Set vertical DDRAM address
		toggle_e();
	} else {
		expander_write(GPIOB, (data >> 8));		// Set horizontal DDRAM address
		toggle_e();
		expander_write(GPIOB, data);		// Set vertical DDRAM address
		toggle_e();
	}
}

void ST7920_I2C_MCP23017_GLCD::set_rs_low() {
	if(rs_high == true) {
		state = state - 0x20;
		expander_write(GPIOA, state);
		rs_high = false;
		_delay_us(delay_time);
	}
}

void ST7920_I2C_MCP23017_GLCD::set_rw_high() {
	if(rw_high == false) {
		state = state + 0x40;
		expander_write(GPIOA, state);
		rw_high = true;
		_delay_us(delay_time);
	}
}

void ST7920_I2C_MCP23017_GLCD::set_rw_low() {
	if(rw_high == true) {
		state = state - 0x40;
		expander_write(GPIOA, state);
		rw_high = false;
		_delay_us(delay_time);
	}
}

void ST7920_I2C_MCP23017_GLCD::set_en_high() {
	if(en_high == false) {
		state = state + 0x80;
		expander_write(GPIOA, state);
		en_high = true;
		_delay_us(delay_time);
	}
}

void ST7920_I2C_MCP23017_GLCD::set_en_low() {
	if(en_high == true) {
		state = state - 0x80;
		expander_write(GPIOA, state);
		en_high = false;
		_delay_us(delay_time);
	}
}

void ST7920_I2C_MCP23017_GLCD::toggle_e() {
	set_en_high();
	set_en_low();
}

void ST7920_I2C_MCP23017_GLCD::clcd_init() {
	expander_write(IODIRB, 0x00);    // set data port for output
	set_en_low();
	set_rs_low();
	set_rw_low();
	expander_write(GPIOB, 0x30);		// set 8-bit interface
	toggle_e();
	_delay_ms(1);
	expander_write(GPIOB, 0x30);    // set 8-bit interface, basic instruction set
	toggle_e();
	expander_write(GPIOB, 0x0C);    // display ON, cursor and blink OFF
	toggle_e();
	expander_write(GPIOB, 0x01);    // clear display, reset address
	toggle_e();
	expander_write(GPIOB, 0x06);    // display ON, no cursor
	toggle_e();
}

void ST7920_I2C_MCP23017_GLCD::set_cgram_address(uint8_t x, uint8_t y) {
	set_en_low();
	set_rs_low();
	set_rw_low();
	expander_write(IODIRB, 0x00);    // set data port for output
	expander_write(GPIOB, (0x40 | x));
	toggle_e();
	expander_write(GPIOB, (0x40 | y));;
	toggle_e();
}

void ST7920_I2C_MCP23017_GLCD::glcd_enable(void) {
	expander_write(IODIRB, 0x00);	// set data port for output
	set_en_low();
	set_rs_low();
	set_rw_low();
	expander_write(GPIOB, 0x36);	// Repeat with graphics bit set to on.
	toggle_e();
	expander_write(GPIOB, 0x0C);    // display ON, cursor and blink OFF
	toggle_e();
}
	
void ST7920_I2C_MCP23017_GLCD::write_data(uint8_t data) {
	expander_write(IODIRB, 0x00);    // set data port for output
	set_en_low();
	set_rs_high();
	set_rw_low();
	expander_write(GPIOB, data);    // write the byte to display at current address
	toggle_e();
}

void ST7920_I2C_MCP23017_GLCD::write_wdata(uint16_t data) {
	expander_write(IODIRB, 0x00);    // set data port for output
	set_en_low();
	set_rs_high();
	set_rw_low();
	expander_write(GPIOB, (data >> 8));		// write the byte to display at current address
	toggle_e();
	expander_write(GPIOB, data);
	toggle_e();
}
	
void ST7920_I2C_MCP23017_GLCD::clear_screen() {
	glcd_fill(0, 8, 0, 64, 0x0000);
}

void ST7920_I2C_MCP23017_GLCD::set_cursour(int symb, int str) {
	if(symb >= char_numb){
		char_numb = symb;
	} else {
		char_numb++;
	}
	if(char_numb > 20) {
		char_numb = 0;
		if(string_numb > str) {
			string_numb++;
		} else {
			string_numb = str + 1;
		}
	} else if(str >= string_numb) {
		string_numb = str;
	}
	forced_str_position = true;
}
	
void ST7920_I2C_MCP23017_GLCD::draw_letter(byte c, int str, int symb) {
	byte d = c;
	int string_numb_1 = str;
	int symbol = symb;
	d -= 0x20; 					// force into range of our font table (which starts at 0x20)	
	if(old_string_numb != string_numb_1) {
		symbol_pos = 0;
	}
	symbol = symbol - symbol_pos;
	if((d == 0x00) && (symbol == 0)) {
		old_string_numb = string_numb_1;
		symbol_pos = 1;
	} else {
		for(byte x = 0; x < 5; x++) {
			byte a = pgm_read_byte(&fonts[d][x]);
			int k = 6;
			int y = 0;
			while(k != -1) {
				int z = bitRead(a, k);
				if(z == 1) {
					draw_pixel(((symbol * 6) + x + 1), ((string_numb_1 * 8) + (y * (-1) + 7)));
				}
				y++;
				k--;
			}
		}
	}
}
	
void ST7920_I2C_MCP23017_GLCD::write_string(char * s) {
	char c;
	char buffer[128];
	if((char_numb != 0) && (forced_str_position == false)) {
		string_numb = string_numb + 1;
		char_numb = 0;
	}
	forced_str_position = false;
	unsigned char n;
	int k;
	int i = 0;
	int q = 0;
	while(c = *s++) {
		buffer[q] = c;
		q++;
	}
	k = q;
	while(i < k) {
		n = buffer[i];
		i++;
		if(n >= 0xC0) {
			switch(n) {
				case 0xD0: {
					n = buffer[i];
					i++;
					if(n == 0x81) {
						n = 0xA8;
						break;
					}
					if(n >= 0x90 && n <= 0xBF) {
						n = n + 0x30;
					}
					break;
				}
				case 0xD1: {
					n = buffer[i];
					i++;
					if(n == 0x91) {
						n = 0xB8;
						break;
					}
					if(n >= 0x80 && n <= 0x8F) {
						n = n + 0x70;
					}
					break;
				}
			}
		}
		draw_letter(n, string_numb, char_numb);
		char_numb++;
		if(char_numb == 21) {
			string_numb++;
			char_numb = 0;
			if(string_numb == 8) {
				clear_screen();
				string_numb = 0;
				char_numb = 0;
			}
		}
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_horizontal_line(uint8_t x1, uint8_t x2, uint8_t y) {
	int i = 1;
	if(x1 >= x2) {
		i = -1;
	}
	while(x1 != x2) {
		draw_pixel(x1, y);
		x1 = x1 + i;
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_vertical_line(uint8_t x, uint8_t y1, uint8_t y2) {
	int i = 1;
	if(y1 >= y2) {
		i = -1;
	}
	while(y1 != y2) {
		draw_pixel(x, y1);
		y1 = y1 + i;
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_line(int x1, int y1, int x2, int y2) {
	if(x1 == x2) {
		draw_vertical_line(x1, y1, y2);
	} else if(y1 == y2) {
		draw_horizontal_line(x1, x2, y1);
	} else {
		int dx = (x2 - x1 >= 0 ? 1 : -1);
		int dy = (y2 - y1 >= 0 ? 1 : -1);
		int lengthX = abs(x2 - x1);
		int lengthY = abs(y2 - y1);
		int length = max(lengthX, lengthY);
		if(length == 0) {
			draw_pixel(x1, y1);
		}
		if(lengthY <= lengthX) {
			int x = x1;
			int y = y1;
			int d = -lengthX;
			length++;
			while(length != 0) {
				draw_pixel(x, y);
				x += dx;
				d += 2 * lengthY;
				if(d > 0) {
					d -= 2 * lengthX;
					y += dy;
				}
				length--;
			}
		} else {
			int x = x1;
			int y = y1;
			int d = - lengthY;
			length++;
			while(length--) {
				draw_pixel(x, y);
				y += dy;
				d += 2 * lengthX;
				if(d > 0) {
					d -= 2 * lengthY;
					x += dx;
				}
			}
		}
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_frame(int x, int y, int width, int height) {
	draw_line(x, y, (x + width - 1), y);
	draw_line((x + width - 1), y, (x + width - 1), (y + height - 1));
	draw_line((x + width - 1), (y + height - 1), x, (y + height - 1));
	draw_line(x, (y + height - 1), x, y);
}
	
uint16_t ST7920_I2C_MCP23017_GLCD::reverse_bits(uint16_t value) {
	uint16_t new_value = 0x0000;
	uint16_t l = 0x8000;
	uint32_t k = 0x0001;
	while(k != 0x10000) {
		int z = value/l;
		if(z == 1) {
			value = value - l;
			new_value = new_value + z * k;
		}
		l = l >> 1;
		k = k << 1;
	}
	return new_value;
}
	
void ST7920_I2C_MCP23017_GLCD::draw_box(int x, int y, int width, int height) {
	if((x == 0) && (y == 0) && (width == 128) && (height == 64)) {
		glcd_fill(0, 8, 0, 64, 0xFFFF);
	} else if(width == 128){
		glcd_fill(0, 8, y, (y + height), 0xFFFF);
	} else {
		int x_1 = x;
		int y_1 = y;
		int w = width;
		int y_2 = y_1 + height;
		uint16_t value;
		int n = x_1 % 16;
		int m = (x_1 - n) / 16;
		n = 16 - n;
		if(((w-n)/16) >= 1) {
			value = round(pow(2, n) - 1);
			if(rotated == true) {
				value = reverse_bits(value);				//equal operation (value <<= (16 - n))
			}
			glcd_fill(m, (m + 1), y_1, y_2, value);
			m++;
			w = w - n;
			int k = w % 16;
			int l = (w - k) / 16;
			for(int i = 0; i < l; i++) {
				glcd_fill(m, (m + 1), y_1, y_2, 0xFFFF);
				w = w - 16;
				m++;
			}
			value = pow(2, 16) - pow(2, (16 - w));
			if(rotated == true) {
				value = reverse_bits(value);				//equal operation (value >>= (16 - w))
			}
			glcd_fill(m, (m + 1), y_1, y_2, value);
		} else {
			if(n < w) {
				value = round(pow(2, n) - 1);
					if(rotated == true) {
					value = reverse_bits(value);			//equal operation (value <<= (16 - n))
				}
				glcd_fill(m, (m + 1), y_1, y_2, value);
				m++;
				w = w - n;
				value = pow(2, 16) - pow(2, (16 - w));
				if(rotated == true) {
					value = reverse_bits(value);			//equal operation (value >>= (16 - w);)
				}
				glcd_fill(m, (m + 1), y_1, y_2, value);
			} else {
				value = pow(2, n) - pow(2, (n - w)); 
				if(rotated == true) {
					value = reverse_bits(value);			//equal operation (value >>= (n - w))
				}
				glcd_fill(m, m+1, y_1, y_2, value);
			}
		}
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_circle_by_quartes(int x0, int y0, int r, int q) {
	int x = -r;
	int eq = -1;
	int y = 0;
	int F = 1 - r;
	int delta_Fs = 3;
	int delta_Fd = 5 - 2 * r;
	while((x + y) <= 0) {
		switch(q) {
			case 0: {	//full circle
				draw_pixel(x0 + x, y0 + y + eq);
				draw_pixel(x0 + x, y0 - y);
				draw_pixel(x0 - x + eq, y0 + y + eq);
				draw_pixel(x0 - x + eq, y0 - y);
				draw_pixel(x0 + y + eq, y0 + x);
				draw_pixel(x0 + y + eq, y0 - x + eq);
				draw_pixel(x0 - y, y0 + x);
				draw_pixel(x0 - y, y0 - x + eq);
				break;
			}
			case 1: {	//1-st quarter
				draw_pixel(x0 - x + eq, y0 - y);
				draw_pixel(x0 + y + eq, y0 + x);
				break;
			}
			case 2: {	//2-nd quarter
				draw_pixel(x0 + x, y0 - y);
				draw_pixel(x0 - y, y0 + x);
				break;
			}
			case 3: {	//3-th quarter
				draw_pixel(x0 + x, y0 + y + eq);
				draw_pixel(x0 - y, y0 - x + eq);
				break;
			}
			case 4: {	//4-th quarter
				draw_pixel(x0 - x + eq, y0 + y + eq);
				draw_pixel(x0 + y + eq, y0 - x + eq);
				break;
			}
		}
		if(F > 0) {
			F += delta_Fd;
			x++;
			y++;
			delta_Fs += 2;
			delta_Fd += 4;
		} else {
			F += delta_Fs;
			y++;
			delta_Fs += 2;
			delta_Fd += 2;
		}
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_circle(int x0, int y0, int r) {
	draw_circle_by_quartes(x0, y0, r, 0);
}
	
void ST7920_I2C_MCP23017_GLCD::draw_filled_circle(int x0, int y0, int radius) {
	const int FULL = (1 << 2);
	const int HALF = (FULL >> 1);
	int rad1 = radius * 2;
	int w1 = (round(rad1/sqrt(2)));
	if((w1 % 2) == 1) {
		w1++;
	}
	int pos = (rad1 - w1)/2;
	draw_box(((x0 - radius) + pos), ((y0 - radius) + pos), w1, w1);
	int size = (rad1 << 2);
	int ray = (size >> 1);
	int dY2;
	int ray2 = ray * ray;
	int posmax;
	int Y,X;
	int x = ((rad1 & 1) == 1) ? ray : ray - HALF;
	int y = HALF;
	x0 -= (rad1>>1);
	y0 -= (rad1>>1);
	for(;; y+=FULL) {
		dY2 = (ray - y) * (ray - y);
		for(;; x-=FULL) {
			if(dY2 + (ray - x) * (ray - x) <= ray2) {
				continue;
			}
			if(x < y) {
				return;
			}
			X = (x >> 2) + 1;
			Y = y >> 2;
			posmax = rad1 - X;
			int mirrorY = rad1 - Y - 1;
			while(X < posmax) {
				draw_pixel(x0 + X, y0 + Y);
				draw_pixel(x0 + X, y0 + mirrorY);
				draw_pixel(x0 + Y, y0 + X);
				draw_pixel(x0 + mirrorY, y0 + X);
				X++;
			}
			break;
		}
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_filled_circle_by_semicircles(int x0, int y0, int rad, int q) {
	int x = rad;
	int y = 0;
	int eq = -1;
	int xChange = 1 - (rad << 1);
	int yChange = 0;
	int radError = 0;
	while(x >= y) {
		switch(q) {
			case 0: {
				for(int i = x0 - x; i <= x0 + x + eq; i++) {
					draw_pixel(i, y0 + y + eq);		//bottom of circle
					draw_pixel(i, y0 - y);		//top of circle
				}
				for(int i = x0 - y; i <= x0 + y + eq; i++) {
					draw_pixel(i, y0 + x + eq);		//bottom of circle
					draw_pixel(i, y0 - x);		//top of circle
				}
				break;
			}
			case 1:{
				for(int i = x0 - x; i <= x0 + x + eq; i++) {
					draw_pixel(i, y0 - y);		//top of circle
				}
				for(int i = x0 - y; i <= x0 + y + eq; i++) {
					draw_pixel(i, y0 - x);		//top of circle
				}
				break;
			}
			case 2: {
				for(int i = x0 - x; i <= x0 + x + eq; i++) {
					draw_pixel(i, y0 + y + eq);		//bottom of circle
				}
				for(int i = x0 - y; i <= x0 + y + eq; i++) {
					draw_pixel(i, y0 + x + eq);		//bottom of circle
				}
				break;
			}
		}
		y++;
		radError += yChange;
		yChange += 2;
		if(((radError << 1) + xChange) > 0) {
			x--;
			radError += xChange;
			xChange += 2;
		}
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_ellipse(int xc, int yc, int w, int h) {
	int width = ceil(w/2);
	int height = ceil(h/2);
	if(w == h) {
		draw_circle(xc, yc, width);
	} else {
		long int a2 = width * width;
		long int b2 = height * height;
		long int fa2 = 4 * a2, fb2 = 4 * b2;
		long int x, y, sigma;
		int x_1, y_1, x_2, y_2;
		for(x = 0, y = height, sigma = 2 * b2 + a2 * (1 - 2 * height); b2 * x <= a2 * y; x++) {
			if((((xc - x) >= 32) && (w == 128))) {
				x_1 = -1;
			} else {
				x_1 = 0;
			}
			if((((yc + y) >= 32) && (h == 64)) || ((h % 2) == 0)) {
				y_1 = -1;
			} else {
				y_1 = 0;
			}
			if((((xc + x) >= 32) && (w == 128)) || ((w % 2) == 0)) {
				x_2 = -1;
			} else {
				x_2 = 0;
			}
			if(((yc - y) >= 32) && (h == 64)) {
				y_2 = -1;
			} else {
				y_2 = 0;
			}
			draw_pixel(xc + x + x_2, yc + y + y_1);
			draw_pixel(xc - x + x_1, yc + y + y_1);
			draw_pixel(xc + x + x_2, yc - y + y_2);
			draw_pixel(xc - x + x_1, yc - y + y_2);
			if(sigma >= 0) {
				sigma += fa2 * (1 - y);
				y--;
			}
			sigma += b2 * ((4 * x) + 6);
		}
		for(x = width, y = 0, sigma = 2 * a2 + b2 * (1 - 2 * width); a2 * y <= b2 * x; y++) {
			if((((xc + x) >= 32) && (w == 128)) || ((w % 2) == 0)) {
				x_1 = -1;
			} else {
				x_1 = 0;
			}
			if(((yc - y) >= 32) && (h == 64)) {
				y_1 = -1;
			} else {
				y_1 = 0;
			}
			if((((xc - x) >= 32) && (w == 128))) {
				x_2 = -1;
			} else {
				x_2 = 0;
			}
			if((((yc + y) >= 32) && (h == 64)) || ((h % 2) == 0)) {
				y_2 = -1;
			} else {
				y_2 = 0;
			}
			draw_pixel(xc + x + x_1, yc + y + y_2);
			draw_pixel(xc - x + x_2, yc + y + y_2);
			draw_pixel(xc + x + x_1, yc - y + y_1);
			draw_pixel(xc - x + x_2, yc - y + y_1);
			if(sigma >= 0) {
				sigma += fb2 * (1 - x);
				x--;
			}
			sigma += a2 * ((4 * y) + 6);
		}
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_filled_ellipse(int x0, int y0, int el_width, int el_height) {
	if(el_width == el_height) {
		draw_filled_circle(x0, y0, round(el_width / 2));
	} else {
		const int FULL = (1 << 2);
		const int HALF = (FULL >> 1);
		int eq;
		float h_1, w_1, rad12;
		bool breaked;
		int el_width_height, for_h_1, for_w_1, rad1, size, ray, dY2, ray2, posmax, Y1, X1, x, y, k, new_pos, x01, y01, w, h, pos_x, pos_y, m, mirrorY;
		w = el_width/sqrt(2);
		h = el_height/sqrt(2);
		if((((el_width % 2) == 1) && ((w % 2) == 0)) || (((el_width % 2) == 0) && ((w % 2) == 1))) {
			w++;
		}
		if((((el_height % 2) == 1) && ((h % 2) == 0)) || (((el_height % 2) == 0) && ((h % 2) == 1))) {
			h++;
		}
		pos_x = (el_width - w)/2;
		pos_y = (el_height - h)/2;
		draw_box(((x0 - el_width/2) + pos_x), ((y0 - el_height/2) + pos_y), w, h);
		m = 0;
		while(m != 2) {
			breaked = false;
			x01 = x0;
			y01 = y0;
			if(m == 0) {
				el_width_height = el_width;
				for_h_1 = w;
				for_w_1 = h;
			} else if(m == 1) {
				el_width_height = el_height;
				for_h_1 = h;
				for_w_1 = w;
			}
			h_1 = ((float) el_width_height - (float) for_h_1)/4;
			w_1 = (for_w_1 * for_w_1)/(16 * h_1);
			rad12 = 2 * (h_1 + w_1);
			rad1 = rad12;
			size = (rad1 << 2);
			ray = (size >> 1);
			ray2 = ray * ray;
			x = ((rad1 & 1) == 1) ? ray : ray - HALF;
			y = HALF;
			k = h_1 * 2;
			new_pos = (abs(for_h_1 - (rad1 - (el_width_height - for_h_1))))/2;
			x01 -= (rad1>>1);
			y01 -= (rad1>>1);
			for(;; y += FULL) {
				dY2 = (ray - y) * (ray - y);
				for(;; x -= FULL) {
					if(dY2 + (ray - x) * (ray - x) <= ray2) {
						continue;
					}
					if(k == 0) {
						m++;
						if(m == 2) {
							return;
						} else {
							breaked = true;
							break;
						}
					}
					X1 = (x >> 2) + 1;
					Y1 = y >> 2;
					posmax = rad1 - X1;
					mirrorY = rad1 - Y1 - 1;
					while(X1 < posmax) {
						if(m == 0) {
							draw_pixel(x01 + Y1 - new_pos, y01 + X1);
							draw_pixel(x01 + mirrorY + new_pos, y01 + X1);
						} else if(m == 1) {
							if((y01 + Y1 + new_pos) && (y01 + mirrorY - new_pos) >= 32) {
								eq = -1;
							} else {
								eq = 0;
							}
							draw_pixel(x01 + X1, y01 + Y1 + new_pos);
							draw_pixel(x01 + X1, y01 + mirrorY - new_pos-1);
						}
						X1++;
					}
					k--;
					break;
				}
				if(breaked == true) {
					break;
				}
			}
		}			
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2) {
	draw_line(x0, y0, x1, y1);
	draw_line(x1, y1, x2, y2);
	draw_line(x2, y2, x0, y0);
}

void ST7920_I2C_MCP23017_GLCD::draw_filled_triangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	uint8_t t1x, t2x, y, minx, maxx, t1xp, t2xp;
	bool changed1 = false;
	bool changed2 = false;
	int8_t signx1, signx2, dx1, dy1, dx2, dy2;
	uint8_t e1, e2;
	if(y0 > y1) {
		SWAP(y0, y1);
		SWAP(x0, x1);
	}
	if(y0 > y2) {
		SWAP(y0, y2);
		SWAP(x0, x2);
	}
	if(y1 > y2) { 
		SWAP(y1, y2);
		SWAP(x1, x2);
	}
	t1x = t2x = x0;
	y = y0;
	dx1 = (int8_t)(x1 - x0); 
	if(dx1 < 0) {
		dx1 =- dx1;
		signx1 =- 1;
	} else {
		signx1 = 1;
	}
	dy1 = (int8_t)(y1 - y0);
	dx2 = (int8_t)(x2 - x0); 
	if(dx2 < 0) {
		dx2 =- dx2;
		signx2 =- 1;
	} else {
		signx2 = 1;
	}
	dy2 = (int8_t)(y2 - y0);
	if(dy1 > dx1) {
		SWAP(dx1, dy1);
		changed1 = true;
	}
	if(dy2 > dx2) {
		SWAP(dy2, dx2);
		changed2 = true;
	}
	e2 = (uint8_t)(dx2>>1);
	if(y0 == y1) {
		goto next;
	}
	e1 = (uint8_t)(dx1>>1);
	for(uint8_t i = 0; i < dx1;) {
		t1xp = 0;
		t2xp = 0;
		if(t1x < t2x) {
			minx = t1x; 
			maxx = t2x; 
		} else { 
			minx = t2x;
			maxx = t1x;
		}
		while(i < dx1) {
			i++;			
			e1 += dy1;
			while(e1 >= dx1) {
				e1 -= dx1;
				if(changed1) {
					t1xp = signx1;
				} else {
					goto next1;
				}
			}
			if(changed1) {
				break;
			} else {
				t1x += signx1;
			}
		}
		next1: 
		while(1) {
			e2 += dy2;		
			while(e2 >= dx2) {
				e2 -= dx2;
				if(changed2) {
					t2xp = signx2;
				} else {
					goto next2;
				}      
			}
			if(changed2) {
				break;
			} else {
				t2x += signx2;
			}
		}
		next2: 
		if(minx > t1x) {
			minx = t1x;
		} 
		if(minx > t2x) {
			minx = t2x;
		}
		if(maxx < t1x) {
			maxx = t1x;
		}
		if(maxx < t2x) {
			maxx = t2x;
		}
		draw_line(minx, y, maxx + 1, y);
		if(!changed1) {
			t1x += signx1;
		}
		t1x += t1xp;
		if(!changed2) {
			t2x += signx2;
		}
		t2x += t2xp;
		y += 1;
		if(y == y1) {
			break;
		}
	}
	next:
	dx1 = (int8_t)(x2 - x1); 
	if(dx1 < 0) {
		dx1 =- dx1;
		signx1 =- 1;
	} else {
		signx1 = 1;
	}
	dy1 = (int8_t)(y2 - y1);
	t1x = x1;
	if(dy1 > dx1) {
		SWAP(dy1, dx1);
		changed1 = true;
	} else {
		changed1 = false;
	}
	e1 = (uint8_t)(dx1>>1);
	for(uint8_t i = 0; i <= dx1; i++) {
		t1xp = 0;
		t2xp = 0;
		if(t1x < t2x) { 
			minx = t1x; 
			maxx = t2x; 
		} else { 
			minx = t2x;
			maxx = t1x;
		}
		while(i < dx1) {
			e1 += dy1;
			while(e1 >= dx1) {
				e1 -= dx1;
				if(changed1) {
					t1xp = signx1;
					break;
				} else {
					goto next3;
				}
			}
			if(changed1) {
				break;
			} else {
				t1x += signx1;
			}
			if(i < dx1) {
				i++;
			}
		}
		next3:
		while(t2x != x2) {
			e2 += dy2;
			while(e2 >= dx2) {
				e2 -= dx2;
				if(changed2) {
					t2xp = signx2;
				} else {
					goto next4;
				}
			}
			if(changed2) {
				break;
			} else {
				t2x += signx2;
			}
		}
		next4:
		if(minx > t1x) {
			minx = t1x;
		}
		if(minx > t2x) {
			minx = t2x;
		}
		if(maxx < t1x) {
			maxx = t1x;
		}
		if(maxx < t2x) {
			maxx = t2x;
		}
		draw_line(minx, y, maxx + 1, y);
		if(!changed1) {
			t1x += signx1;
		}
		t1x+=t1xp;
		if(!changed2) {
			t2x += signx2;
		}
		t2x += t2xp;
		y += 1;
		if(y > y2) {
			return;
		}
	}
}
	
void ST7920_I2C_MCP23017_GLCD::draw_rounded_frame(int x, int y, int w, int h, int r) {
	draw_line((x + r), y, (x + w - r - 1), y);
	draw_line((x + r), (y + h - 1), (x + w - r - 1), (y + h - 1));
	draw_line(x, (y + r), x, (y + h - r - 1));
	draw_line((x + w - 1), (y + r), (x + w - 1), (y + h - r - 1));
	draw_circle_by_quartes((x + w - r), (y + r), r, 1);
	draw_circle_by_quartes((x + r), (y + r), r, 2);
	draw_circle_by_quartes((x + r), (y + h - r), r, 3);
	draw_circle_by_quartes((x + w - r), (y + h - r), r, 4);
}
	
void ST7920_I2C_MCP23017_GLCD::draw_filled_rounded_box(int x, int y, int w, int h, int r) {
	draw_box((x + r), y, (w - r * 2), r);
	draw_box(x, (y + r), w, (h - r * 2));
	draw_box((x + r), (y + h - r), (w - r * 2), r);
	draw_filled_circle_by_semicircles((x + w - r), (y + r), r, 1);
	draw_filled_circle_by_semicircles((x + r), (y + r), r, 1);
	draw_filled_circle_by_semicircles((x + r), (y + h - r), r, 2);
	draw_filled_circle_by_semicircles((x + w - r), (y + h - r), r, 2);
}
	
void ST7920_I2C_MCP23017_GLCD::draw_bitmap(const uint16_t bitmap[], int w, int h) {
	int weight = ceil(w/16);
	int j, k; 
	int m = 0;
	uint16_t value;
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < weight; x++) {
			if(rotated == true) {
				j = (x * (-1) + 7);
				k = (y * (-1) + 63);
				value = reverse_bits((uint16_t) bitmap[y + x + m]);
			} else {
				j = x;
				k = y;
				value = (uint16_t) pgm_read_word(&bitmap[y + x + m]);
			}
			write_word(j, k, value);
		}
		m = m + (weight - 1);			//for draw less columns of bitmap than exist use (8 - weight)
	}
}

void ST7920_I2C_MCP23017_GLCD::cdisplay_clear(void) {
	expander_write(IODIRB, 0x00);	// set data port for output
	set_en_low();
	set_rs_low();
	set_rw_low();
	expander_write(GPIOB, 0x01);		// command to clear screen and reset address counter
	toggle_e();
}

void ST7920_I2C_MCP23017_GLCD::goto_x_y(uint8_t x, uint8_t y) {
	expander_write(IODIRB, 0x00);	// set data port for output
	uint8_t x1, y1;
	x1 = x;
	y1 = y;
	set_en_low();
	set_rs_low();
	set_rw_low();
	if(y1 > 31) {		// convert coordinates to weirdly-arranged 128x64 screen (the ST7920 is mapped for 256x32 displays).
		y1 -= 32;    	// because there are only 31 addressable lines in the ST7920
		x1 += 8;        // so we overflow x (7 visible bytes per line) to reach the bottom half
	}
	x1 |= 0x80;    // bit 7 signals that this is a data address write
	y1 |= 0x80;
	expander_write(GPIOB, y1);	// Set vertical DDRAM address
	toggle_e();  
	expander_write(GPIOB, x1);	// Set horizontal DDRAM address
	toggle_e();
}

void ST7920_I2C_MCP23017_GLCD::glcd_fill(int x_l, int x_h, int y_l, int y_h, uint16_t value) {
	uint8_t i, j, x1, y1;
	char_numb = 0;
	string_numb = 0;
	for(i = y_l; i < y_h; i++) {
		for(j = x_l; j < x_h; j++) {
			if(rotated == true) {
				x1 = (j * (-1) + 7);
				y1 = (i * (-1) + 63);
			} else {
				x1 = j;
				y1 = i;
			}
			write_word(x1, y1, value);
		}
	}
}

void ST7920_I2C_MCP23017_GLCD::draw_pixel(uint8_t x, uint8_t y) {
	uint8_t x_wd, x_pixel, x1, y1;
	x1 = x;
	y1 = y;
	if(rotated == true) {
		x1 = (x1 * (-1) + 127);
		y1 = (y1 * (-1) + 63);
	}
	uint16_t temp;
	uint16_t dot = 0x8000;    			// this will be rotated into it's correct position in the word
	x_wd = x1 / 16;        				// find address of word with our pixel (x; 0-7)
	x_pixel = x1 - (x_wd * 16);         	// get the modulo remainder; that's our pixel's position in the word
	goto_x_y(x_wd, y1);
	temp = read_word(1);    			// read word from screen at that position
	temp = (temp | (dot >> x_pixel));   // convert x_pixel into a bit position, 0-16
	write_word(x_wd, y1, temp);
}

void ST7920_I2C_MCP23017_GLCD::clear_pixel(uint8_t x, uint8_t y) {
	uint8_t x_wd, x_pixel, x1, y1;
	x1 = x;
	y1 = y;
	if(rotated == true) {
		x1 = (x1 * (-1) + 127);
		y1 = (y1 * (-1) + 63);
	}
	uint16_t temp;
	uint16_t dot = 0x7FFF;    			// this will be rotated into it's correct position in the word
	x_wd = x1 / 16;        				// find address of word with our pixel (x; 0-7)
	x_pixel = x1 - (x_wd * 16);        	// get the modulo remainder; that's our pixel's position in the word
	goto_x_y(x_wd, y1);
	temp = read_word(1);    			// read word from screen at that position
	temp = (temp & (dot >> x_pixel));   // convert x_pixel into a bit position, 0-16
	write_word(x_wd, y1, temp);
}

void ST7920_I2C_MCP23017_GLCD::write_number_x_y(uint8_t x, uint8_t y, uint8_t number) {
	uint8_t i = 0;
	uint8_t x1, y1;
	x1 = x;
	y1 = y;
	uint16_t temp = 0;
	for(i = 0; i < 5; i++) {
		temp = pgm_read_byte(&numbers[number][i]);
		temp = temp << 12;
		if(rotated == true) {
			x1 = (x1 * (-1) + 128);
			y1 = ((y1 + i) * (-1) + 64);
		} else {
			y1 = (y1 + i);
		}
		write_word(x1, y1, temp);
	}
}

void ST7920_I2C_MCP23017_GLCD::write_lnumber_x_y(uint8_t x, uint8_t y, uint16_t number) {
	uint8_t j[4];    	// the individual digits, from left to right
	if(number > 999) {
		j[0] = number / 1000;
		number = number - (1000 * j[0]);
	} else {
		j[0] = 0x0B;	// blank first zero if present
	}
	if(number > 99) {
		j[1] = number / 100;
		number = number - (100 * j[1]);
	} else {
		j[1] = 0;
	}
	if(number > 9) {
		j[2] = number / 10;
		number = number - (10 * j[2]);
	} else {
		j[2] = 0;
	}
	j[3] = number;        // at this point j[] has 4 separate decimal digits
	write_char(x, y, j[0], j[1], j[2], j[3]);
}

void ST7920_I2C_MCP23017_GLCD::write_char(int x, int y, uint8_t num_0, uint8_t num_1, uint8_t num_2, uint8_t num_3) {
	int j;
	uint8_t x1, y1;
	x1 = x;
	y1 = y;
	uint16_t temp = 0;
	uint16_t packed_number[5];
	for(j = 0; j < 5; j++) {
		temp = pgm_read_byte(&numbers[num_0][j]);
		temp = temp << 4;
		temp |= pgm_read_byte(&numbers[num_1][j]);
		temp = temp << 4;
		temp |= pgm_read_byte(&numbers[num_2][j]);
		temp = temp << 4;
		temp |= pgm_read_byte(&numbers[num_3][j]);
		packed_number[j] = temp;
	}
	for(j = 0; j < 5; j++) {
		if(rotated == true) {
			x1 = (x1 * (-1) + 128);
			y1 = ((y1 + j) * (-1) + 64);
		} else {
			y1 = (y1 + j);
		}
		write_word(x1, y1, packed_number[j]);
	}
}

void ST7920_I2C_MCP23017_GLCD::write_char_x_y(uint8_t x, uint8_t y, uint8_t number) {
	uint8_t h, i, j, l, m = x;
	uint8_t k = 0x08;
	h = 0;
	for(i = 0; i < 5; i++) {
		l = pgm_read_byte(&numbers[number][h]);
		for(j = 0; j < 3; j++) {
			if(l & k) {
				draw_pixel(m, y);
			}
			m++;
			k /= 2;
		}
		h++;
		y++;
		m = x;
		k = 0x08;
	}
}

void ST7920_I2C_MCP23017_GLCD::write_gnumber_x_y(uint8_t x, uint8_t y, uint16_t number) {
	uint8_t j[4];    // the individual digits, from left to right
	if(number > 999) {
		j[0] = number / 1000;
		number = number - (1000 * j[0]);
	} else {
		j[0] = 0x0b;	// blank first zero if present
	}
	if(number > 99) {
		j[1] = number / 100;
		number = number - (100 * j[1]);
	} else {
		j[1] = 0;
	}
	if(number > 9) {
		j[2] = number / 10;
		number = number - (10 * j[2]);
	} else {
		j[2] = 0;
	}
	j[3] = number;        // at this point j[] has 4 separate decimal digits
	write_char_x_y(x, y, j[0]);
	x = x + 4;
	write_char_x_y(x, y, j[1]);
	x = x + 4;
	write_char_x_y(x, y, j[2]);
	x = x + 4;
	write_char_x_y(x, y, j[3]);
}