# UniMoRover

UniMoRover is a project developped under the framework of Embedded System Programming exam, in the University of Modena and Reggio Emilia, Italy.
The goal was the development of a remotely controlled vehicle starting from a commercial solution for children (Peg Perego), conveniently modified in order to obtain a completely controllable system provided with sensors and intelligence for obstacle detection.

The main features are listed:
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

The pdf *UniMoRover.pdf* and the slides *UniMoRover_slides.pptx* are made available (in italian) to examine in depth the project.

Link to the video demonstration: [Video UniMoRover](https://drive.google.com/file/d/15m4ykpq-TjEOaIIhjdyY90AE6_lhhyMw/view?usp=sharing)

![UniMoRover](https://i.imgur.com/HacAzaw.jpg)


**Developped by:**
- _Mazzocchi Enrico_
- _Mellone Giacomo_
- _Pistoni Luca_
- _Truffellini Samuele_
- _Vidoni Aldo_
