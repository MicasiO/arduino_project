## Digital notebook
This project serves the purpose of a digital notebook with two save states.
The output is an 2x16 LCD display, showing 32 possible characters total.
The input responsible for writing to the display is a joystick: shifting the X axis moves the cursor inside the LCD, while shifting the Y axis cycles through the alphabet at the current cursor position.
Clicking the built-in joystick button erases the character at the current cursor position.
There are two buttons that are responsible for save states, each saving to a different storage slot. Pressing one of the buttons once will save the written characters that are on the LCD, while pressing and holding for about 1 second will load the data from that specific slot.
