----------------------------------------------------------------------------------------------------------
-- Create Date:    20:58:39 03/14/2017 
-- Module Name:    VGA - Main 
-- Project Name:  VGA driver considering a 1368 x 768 @ 60 Hz monitor
-- http://tinyvga.com/vga-timing/1368x768@60Hz Timing informations

-- Description: VGA driver that prints on a monitor (resolution and timing has to be set in the
-- "Sync.vhd" file) the shape of a car with a 4 button command pad on the bottom left. When sensors and 
-- command buttons are activated they are displayed such as the user is aware of car's status.

-- The 4 direction buttons are visible also on the monitor, once pressed the related square turns pink; the 
-- central button instead is associated to horn function, when pressed it displays the relative blue symbol.
-- Those buttons are linked to the 4-digits 7-segment display just above them in the FPGA, this displays
-- the direction one wishes to drive the car ("Display7.vhd").
-- A PLL entity is used in order to generate the pixel clock and a 5 MHz clock, the latter is used to 
-- drive the counter adopted in the 7 segment display, otherwise it wouldn't be possible to switch among 
-- the differents 4 anodes/digits.
-- A total of 3 alerts are used: 2 out of them are due to the HC-SR04s, used for monitoring back and front obstacles,
-- the other one is linked to motors errors.
-- A uart interface block is used in order to communicate with a PIC18LF25K80 that will send and receive 
-- packets via radio @2.4GHz using the nRF24L01 module with another pic, vehicle side. 
----------------------------------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity VGA is 
Port( 	CLOCK_100 : in STD_LOGIC; -- Clock 100MHz
			VGA_HS, VGA_VS: out STD_LOGIC; -- Horizontal and vertical timing synchronization
			VGA_R,VGA_G,VGA_B: out STD_LOGIC_VECTOR(3 downto 0);
			ALERT: in STD_LOGIC_VECTOR(2 downto 0); -- 2 HC-SR04 alerts and 1 motor alert
			BTN: in STD_LOGIC_VECTOR(4 downto 0); -- Command pad buttons: 4 directions and 1 horn
			SEG : out  STD_LOGIC_VECTOR (7 downto 0); -- 7 segment display
			AN : out  STD_LOGIC_VECTOR (3 downto 0); -- Anode for driving the 7 segment display
			COMMAND : out STD_LOGIC_VECTOR (7 downto 0) -- Command byte (ASCII) sent to PIC18LF25K80
			);
end VGA;
 
architecture Main of VGA is

signal VGACLK,RESET,CLK5MHZ : STD_LOGIC:='0';

--------------------------------------------------------------------------------------------------------------
-- Clock using for generating VGA clock and 5MHz clock (for the 7 seg-display) starting from the 100MHz one
component PLL is  -- Add Source -> Clocking Wizard
port
 (-- Clock in ports
  CLK_IN           : in     std_logic;
  -- Clock out ports
  CLK_OUT          : out    std_logic;
  CLK_OUT2          : out    std_logic;
  -- Status and control signals
  RESET             : in     std_logic
 );
end component PLL;

---------------------------------------------------------------------------------------------------------------
-- VGA timing entity
component Sync is --I include the Sync component in the top entity
	 Port ( CLK : in  STD_LOGIC;
           HSYNC, VSYNC : out  STD_LOGIC; -- Horizontal and vertical timing
           R,G,B : out  STD_LOGIC_VECTOR(3 downto 0); -- Colors
			  KEYS: in STD_LOGIC_VECTOR(2 downto 0); -- Corresponding to the 3 kind of sensors (2 for distance
			  -- and 1 for the motor)
			  BTN: in STD_LOGIC_VECTOR(4 downto 0) -- Command pad
			  );
end component Sync;

----------------------------------------------------------------------------------------------------------------

component Display7 is
    Port ( BTN : in  STD_LOGIC_VECTOR (4 downto 0); -- Command pad
           SEG : out  STD_LOGIC_VECTOR (7 downto 0); -- 8 leds
			  AN : out  STD_LOGIC_VECTOR (3 downto 0); -- Anode
			  CLK : in STD_LOGIC;
			  COMMAND : out STD_LOGIC_VECTOR (7 downto 0) -- Command byte (ASCII) sent to uart entity
			 );
end component Display7;

----------------------------------------------------------------------------------------------------------------
-- Signal mapping
begin
	C1 : Sync Port map(VGACLK,VGA_HS,VGA_VS,VGA_R,VGA_G,VGA_B,ALERT,BTN);
	C2 : PLL Port map(CLOCK_100,VGACLK,CLK5MHZ,RESET);
	C3 : Display7 Port map(BTN,SEG,AN,CLK5MHZ,COMMAND);
	

end Main;

