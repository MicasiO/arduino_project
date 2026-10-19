## Build
Dependencies: 
- `arduino-cli`
- Libraries:
  - `LiquidCrystal` (`arduino-cli lib install "LiquidCrystal"`)
  - `ezButton` (`arduino-cli lib install "ezButton"`)

 Clone this repository and run `make upload` to compile upload the code to your Arduino. 

 ## Timer1 (16 bit) config
 - Mode: `CTC` - resets ticks when comparison is matched
 - Prescaler: 64
 - Compare match value: 29999 (120 ms)

## ISR roles
- Timer1 ISR (`ISR(TIMER1_COMPA_vect)`)
  - fires tick every 120 ms
  - purpose: slow down continuous joystick movements and read button hold durations
- Button interrupt 1 (`ISR_BUTTON1()`) and button interrupt 2 (`ISR_BUTTON2()`)
  - Handles save button single press or hold
  - different buttons handle saving data to different "slots"
 
## EEPROM layout
- Address 0: magic number (value: `0xAB`)
- Address 1: version number (current value: `0x01`)
- Addresses 2-36: slot 0 (1 byte for additional magic number, the rest for LCD data)
- Addresses 37-71: slot 1 (1 byte for additional magic number, the rest for LCD data)

## Wiring
- 16x2 LCD:
  - RS: Pin 12
  - Enable (E): Pin 11
  - D4: Pin 5
  - D5: Pin 4
  - D6: Pin 8   
  - D7: Pin 9
  - R/W, VSS, LED-: GND
  - VDD, LED+: 5
  - VO: 1k resistor
  - 2-Axis Joystick:VRx (X-axis): Analog Pin A1 (Cycles characters A–Z and spaces)   VRy (Y-axis): Analog Pin A0 (Moves cursor across columns/rows)   GND / VCC: Connected to board GND and 5VControl Buttons (Internal Pull-Ups Enabled):Slot 0 Button: Pin 2 (INT0) to GND (Short press = Save, Long hold = Load)   Slot 1 Button: Pin 3 (INT1) to GND (Short press = Save, Long hold = Load)   Delete Button: Pin 7 to GND (Clears active character space)[cite: 1, 2, 3]
 
