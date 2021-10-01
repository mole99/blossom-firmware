# Blossom Firmware

This repository contains the firmware for my open source PCB called Blossom which I designed with [KiCad](https://www.kicad.org/).

The repository for the KiCad project can be found under [blossom-kicad](https://github.com/mole99/blossom-kicad).

# Dependencies

- gcc-avr
- binutils-avr
- avr-libc
- avrdude

Usually installed via

```
sudo apt install gcc-avr avr-libc avrdude
```

# Compiling

To create the `hex` file just run

```
make program.hex
```

To upload the program to your board run

```
make upload
```

Note that you may need to change the `avrdude` options depending on your programmer.

# Functionality

The firmware in its current state is capable of driving the LEDs and displaying complex patterns. It can be registered which button and for how long it is pressed. Multiple button presses at once are not supported as of now.

# General Concept

General concept:

- INACTIVE 
	- Use WDT to wait for ~4s
  - Start ADC conversion
  - If value > threshold
  	- Go to ACTIVE
  
- ACTIVE
  - Use Timer 0 for multiplexing
  	- 54Hz refresh rate for the LEDs
  	- Start ADC conversion
	- Use Timer 1 for regular measurements
		- Intervall of 1 ms
		- Used for sleeping
		- Used for button deadtime
	- Upon ADC conversion complete
		- Set button states accordingly
		- Reset WDT counter
  - Use WDT to wait for ~30s
  	- Go to INACTIVE

# License

The code in this repository is licensed under the MIT License. A copy of the license can be found under `LICENSE`.