Sample code for driving 132x64 OLED display with SH1106 driver via ESP-IDF's I2C master driver
====================

See main code main.c_.

----------
About
----------

This sample code implement procedures to read values from 132 OLED display with
SH1106 driver via ESP-IDF's I2C master driver. It's built on the work done on
the SSD1306 by yanbe (from http://github.com/yanbe/ssd1306-esp-idf-i2c).


----------
For local setup
----------

I've used the Wemos X-OLED shield which uses pins 4 and 5 for I2C SDA/SCL; just
make sure those pins are set correctly in `main.c`. The data sheet I've used
as reference is available here: https://www.elecrow.com/download/SH1106%20datasheet.pdf
