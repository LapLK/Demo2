This project is a simple General Purpose Input/Output (GPIO) example. 

By default the OS-JTAG is used for the terminal output. The terminal should be configured for 115200 8-N-1.

Supported platforms:
- TWR_K60D100M


The gpio.eww file will open the project for all of the supported platforms. Pick the specific project that corresponds to your hardware.

NOTE: if switching between platforms it is a good idea to do a make clean to make sure the code is properly configured for the new platform.



TWR_K60D100M example:

Pressing the push buttons on the board will cause E1 or E2 to turn on. Pressing SW1 will light E2 (the yellow LED), and pressing SW2 will light E1 (the orange LED). E3 (the green LED) and E4 (the blue LED) will blink. 

