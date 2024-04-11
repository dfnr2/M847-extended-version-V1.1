# M847-extended
M847 extended project files

This is a fork of Roland Huisman's M847 bootloader extended project.

This fork cleans up the code for readability and configurability, and is
functionally identical to the original code.

Changes include:

- More readable definition of the programs stored in the bootloader FLASH. You
  can look at the code and tell which program is in which slot.

- Slightly cleaner KITT implementation

Roland's original notes:

This is a project to add a bootloader or
bootstraploader to a Digital / DEC PDP8/e PDP8/m PDP8/f computer.

Originally Digital had an M847 diode bootstrap loader. Because the EPROM was not
invented yet, there were 32 x 12 diodes making it a 32 word bootloader.
So a -not programmed- board had 384 diodes in the program field. You could
write your program by cutting out these diodes.

Quite a lot of work to 'reprogram' such a board.

The M847 extended version does not have a 32 word limit. So much bigger programs
can be loaded. The idea is to put in as much test programs and bootloaders as
possible. The first 15 programs are selectable by the dipswitches on the board.
This makes such a program a default program.

After toggeling the SW switch one time, the default will be loaded.

Toggling more than once shows up the programnumber into the address lights.
After a time out of 3 seconds the displayed program will be loaded. If a not
existing program is selected, the programnumber stays in the address line after
the 3 second time out. Then you can start toggling in the program again.

The initial V1 version puts out a lot of debugging data and is slowed down a lot.
This can be tuned up but it does give a nice blinkenlight effect while loading.

The PCB has been made in trough hole components. This because people can built
it without any special tools. The ATMEGA328 needs to have an Arduino bootloader
in it. You can buy them already flashed but you can program this also with an
Arduino as ISP programmer.

The picture "Flash Arduino bootloader.jpg" shows how to connect an Arduino as
ISP to flash the arduino bootloader into the Atmega328. I used a 6 pin cable and
on the programmer side I took out wire 5. Wire 5 goes to digital pin 10 on the
Arduino ISP. You have to do this only once. If you bought an Atmega328 with
arduino bootloader in it then there is no need to flash the CPU with the
bootloader.

Now you have to put in the "M847 extedned edition Vxx.ino". For this the board
needs 5V. The easiest way is to put the board in the PDP, connect a fully wired
serial cross cable and powerup the PDP.

In the Arduino IDE you have to select the "Arduino Uno board" and your com port
which you want to use on the PC. Then just open the .ino file and press upload.
Now you are ready to use the board.

First demo: https://youtu.be/0nqb3zyAv2g
Second demo: https://youtu.be/xYt5kZuUb3A

To do: Test in parallel with my real M847 to check if it gives some sort of collisions...

Regards, Roland Huisman




Copyright 2019 Roland Huisman

Permission is hereby granted, free of charge, to any person obtaining a copy of
this project and associated documentation files , to deal in the project without
restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the project, and
to permit persons to whom the project is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the project.

THE PROJECT IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE PROJECT OR THE USE OR OTHER DEALINGS IN THE PROJECT.
