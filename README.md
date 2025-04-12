# SSD1306_driver
Design a lean OLED driver to run a 64x128 display

This is all new to me, so my design process will include my learning process.
04/11/2025
Using the SSD1306's datasheet found here https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf to get I2C protocol right.
I'm running all my code on a raspberry pi pico for now to test and get a better conceptual understanding. My current process is:
1. Implement I2C manually with GPIO Pins
2. Test by following SSD1306 initialization steps to power on the display
3. Convert my code to using the built in I2C peripherals
4. Generate my own functions for sending control commands to the display, drawing, clearing, etc
5. Test by drawing some simple patterns

After this I will start work towards converting code to run on STM32
