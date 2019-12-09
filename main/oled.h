#ifndef OLED_H
#define OLED_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <stddef.h>
#include <cstdarg>
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "freertos/task.h"

void delay(int x);

#define yield()


#define OLED_FONT_HEIGHT 8
#define OLED_FONT_WIDTH 6
#define OLED_DEFAULT_TTY_MODE false;
#define NO_RESET_PIN 255

/**
 * Driver for OLED displays with SSD1306 or SH1106 controller with write(), print(), println(), printf() support.
 *
 * Supported display sizes: 196x16, 28x32 and 128x64 pixels.
 * This driver supports only displays with internal charge pump and I2C interface.
 * The I2C communication is done by software bit-banging the configurable I/O pins.
 * Communication errors are not handled.
 *
 * The driver allocates 192, 512 or 1024 bytes memory on the heap for buffering.
 *
 * The display is technically organized into "pages" which is a set of 8 horizontal lines.
 * For a 128x34 display the memory contains 4 pages each of 128 bytes.
 * Each byte represents 8 pixels. Bit 0 is the top pixel, bit 7 is the bottom pixel.
 *
 * Bitmap graphics have the same format with the exception that they can have any width. The
 * height is always a multiple of 8.
 *
 * Text and bitmaps can be drawn to any position, but vertical positions at the
 * page boundaries (y=0, 8, 16, 24, 32, 40, 48, 56) provide better performance.
 *
 * For all drawing functions, the coordinate 0,0 is the top left corner of the display.
 * After drawing into the buffer, you have to call the display() method to send the data to
 * the display controller. Otherwise you won't see anything.
 *
 * This driver is distributed without license. You may use it for free.
 * Author: Stefan Frings, 2017
 *
 * Update by:
 * Author: Fabio Durigon, 2018
 * email: develop@dury.it
 *
 */
class OLED
	{
	public:

		enum tColor { BLACK, WHITE };
		enum tFillmode { HOLLOW, SOLID };
		enum tSize { NORMAL_SIZE, DOUBLE_SIZE };
		enum tScrollEffect { NO_SCROLLING = 0, HORIZONTAL_RIGHT = 0x26, HORIZONTAL_LEFT = 0x27, DIAGONAL_RIGHT = 0x29, DIAGONAL_LEFT = 0x2A };
		OLED(uint8_t i2c_address = 0x3C,int sda=22,int sdl=21, uint_fast8_t width = 128, uint_fast8_t height = 32, bool isSH1106 = false);

		virtual ~OLED();
		void begin();
		void set_power(bool enable);
		void set_invert(bool enable);
		void set_contrast(uint8_t contrast);
		void set_scrolling(tScrollEffect scroll_type, uint_fast8_t first_page = 0, uint_fast8_t last_page = 7);
		void scroll_up(uint_fast8_t num_lines = OLED_FONT_HEIGHT, uint_fast8_t delay_ms = 0);

		void display();

		void clear(tColor color = BLACK);
		void draw_bitmap(uint_fast8_t x, uint_fast8_t y, uint_fast8_t width, uint_fast8_t height, const uint8_t* data, tColor color = WHITE);
		void draw_bitmap_P(uint_fast8_t x, uint_fast8_t y, uint_fast8_t width, uint_fast8_t height, const uint8_t* data, tColor color = WHITE);
		void draw_pixel(uint_fast8_t x, uint_fast8_t y, tColor color = WHITE);
		void draw_line(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, tColor color = WHITE);
		void draw_circle(uint_fast8_t x, uint_fast8_t y, uint_fast8_t radius, tFillmode fillMode = HOLLOW, tColor color = WHITE);
		void draw_rectangle(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, tFillmode fillMode = HOLLOW, tColor color = WHITE);


		size_t draw_character(uint_fast8_t x, uint_fast8_t y, char c, tSize scaling = NORMAL_SIZE, tColor color = WHITE);
		void draw_string(uint_fast8_t x, uint_fast8_t y, const char* s, tSize scaling = NORMAL_SIZE, tColor color = WHITE);
		void draw_string_P(uint_fast8_t x, uint_fast8_t y, const char* s, tSize scaling = NORMAL_SIZE, tColor color = WHITE);
		void setCursor(uint_fast8_t x, uint_fast8_t y);
		size_t printf(uint_fast8_t x, uint_fast8_t y, const char *format, ...);
		void setTTYMode(bool Enabled);

		size_t write(uint8_t c);
		inline size_t write(unsigned long n)	{ return write((uint8_t)n);}
		inline size_t write(long n)				{ return write((uint8_t)n);}
		inline size_t write(unsigned int n)		{ return write((uint8_t)n);}
		inline size_t write(int n)				{ return write((uint8_t)n);}
		size_t write(const uint8_t *buffer, size_t len);

	private:
		const uint8_t i2c_address;
		const uint_fast8_t width;
		const uint_fast8_t height;
		const bool isSH1106;
		const uint_fast8_t pages;
		const uint_fast16_t bufsize;
		uint8_t *buffer;
		uint_fast8_t X;
		uint_fast8_t Y;
		bool ttyMode;

		void draw_byte(uint_fast8_t x, uint_fast8_t y, uint8_t b, tColor color);
		void draw_bytes(uint_fast8_t x, uint_fast8_t y, const uint8_t* data, uint_fast8_t size, tSize scaling, tColor color, bool useProgmem);

		// ESP32 stuff
		void i2c_start();
		void i2c_stop();
		bool i2c_send(uint8_t byte);
		i2c_cmd_handle_t cmd;
	};

#endif /* OLED_H */

