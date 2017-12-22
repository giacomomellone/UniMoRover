# UniMoRover

Development of a remotely controlled vehicle starting from a commercial solution for children (Peg Perego), conveniently modified in order to obtain a completely controllable system provided with sensors and intelligence for obstacle detection.
* Wireless communication between PIC μC @2.4 GHz using Serial Peripheral Interface (SPI) and nRF24L01 modules.
* Controlled Area Network (CAN).
* FPGA programming in order to print on a VGA monitor the sensors’ status and send commands to the vehicle.
* Vehicle automatic stop as soon as ultrasonic sensors HC-SR04s detect an obstacle.
* Motor drivers

The software/firmware are made available. 
The following integrated development environments have been used to program:
* MPLAB X IDE v3.65, PIC programming using C
* ISE Design Suite 14.7, FPGA programming using VHDL

A .zip is providen in case the folders didn't contains all the files. 
