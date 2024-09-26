A simple program written in C that takes input from a midi device and lets you write text with it.\
Only works on linux
If you want to change the keymap, just change or add values in the keymap.h file

## Build instructions

- Make sure the midipath string in the main function matches the path of the device file you want to read from
- Use make to compile the program
- Run it with make run

## For future me:

- Make it get the midi input automatically
- Make other versions for other operating systems
