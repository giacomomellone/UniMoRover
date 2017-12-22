----------------------------------------------------------------------------------
-- PSE 2016/2017
-- Students: Mazzocchi, Mellone, Pistoni, Truffellini, Vidoni

-- Module Name:    Sync - Main 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
-- The following are libraries designed to create VGA objects
use WORK.frame.ALL; -- Green frame
use WORK.car_vga.ALL; -- Vehicle
use WORK.ultrasonic.ALL; -- Ultrasonic alerts
use WORK.button_vga.ALL; -- Command pad
use WORK.horn_vga.ALL;

entity Sync is
    Port ( CLK : in  STD_LOGIC;  --Corresponding to VGACLK on VGA.vhd
           HSYNC, VSYNC : out  STD_LOGIC;
           R,G,B : out  STD_LOGIC_VECTOR(3 downto 0);
			  KEYS: in STD_LOGIC_VECTOR(2 downto 0); --Useful for simulating the sensors, those are switches
			  BTN: in STD_LOGIC_VECTOR(4 downto 0) --Those are the command buttons
			  );
end Sync;

architecture Main of Sync is
	-- Horizontal timing
	shared variable H_tot : integer := 1800; -- Total number of pixels: Visible + Timing
	shared variable H_vis : integer := 1368; -- Visible pixels
	shared variable H_FP : integer := 72; -- Horizontal Front Porch
	shared variable H_SY : integer := 144; -- Horizontal Sync pulse
	shared variable H_BP : integer := 216; -- Horizontal Back Porch
	shared variable H_timing : integer := H_tot-H_vis; -- Total pixels used for timing
	
	-- Vertical timing
	shared variable V_tot : integer := 795; -- Total number of pixels: Visible + Timing
	shared variable V_vis : integer := 768; -- Visible pixels
	shared variable V_FP : integer := 1; -- Horizontal Front Porch
	shared variable V_SY : integer := 3; -- Horizontal Sync pulse
	shared variable V_BP : integer := 23; -- Horizontal Back Porch
	shared variable V_timing : integer := V_tot-V_vis; -- Total pixels used for timing
	
	-- I also need to define new variables
	signal DRAW_fr,DRAW_car,DRAW_AL1,DRAW_AL2,DRAW_AL3,DRAW_UP,DRAW_RIGHT,DRAW_LEFT,DRAW_DOWN,DRAW_M,DRAW_H: STD_LOGIC;
	signal  HPOS: integer range 0 to H_tot:=0;
	signal  VPOS: integer range 0 to V_tot:=0;
	
	-- Define green square offset
	signal SQ_X: integer range 0 to H_tot:=H_timing+120; --Initial position for the green square -- Xpos
	signal SQ_Y: integer range 0 to V_tot:=V_timing+40; --Initial position for the green square   -- Ypos
	signal H_side : Integer := 1200;
	signal V_side : Integer := 690;
	
	-- Define all car dimension
	signal CAR_X: integer range 0 to H_tot:=H_timing+400; --Initial position for car -- Xoff
	signal CAR_Y: integer range 0 to V_tot:=V_timing+210; --Initial position for the car (top left) -- Yoff
	
	------------------------------------------------------------
	-- Police-car like style
	------------------------------------------------------------
	-- Those variables refer to different parameters used for drawing the car
	signal A : Integer := 90;
	signal E : Integer := 70; 
	signal D1 : Integer := 160;
	signal D2 : Integer := 440;
	signal H : Integer := 110;
	signal T : Integer := 80; 
	signal P : Integer := 110; 
	signal F : Integer := 150;
	signal R1 : Integer := 60; 
	signal A1 : Integer := 250;
	signal H1 : Integer := 0;
	signal H2 : Integer := 110;
	signal AN : Integer := 120; -- Antenna length
	
	-------------------------------------------------------------
	-- Sedan like style
	-------------------------------------------------------------
	--signal A : Integer := 10;
	--signal E : Integer := 105; 
	--signal D1 : Integer := 180;
	--signal D2 : Integer := 440;
	--signal H : Integer := 110;
	--signal T : Integer := 340; 
	--signal P : Integer := 110; 
	--signal F : Integer := 150;
	--signal R1 : Integer := 60; 
	--signal A1 : Integer := 60;
	--signal H1 : Integer := 0;
	--signal H2 : Integer := 110;
	--signal AN : Integer := 140;
	
	--------------------------------------------------------------
	-- Define the offset of HC-SR04 lines
	signal AL_X1: integer range 0 to H_tot:=H_timing+324; --Initial position -- Alert position X1 LEFT
	signal AL_Y1: integer range 0 to V_tot:=V_timing+320; --Initial position -- Alert position Y1 LEFT
	signal AL_X2: integer range 0 to H_tot:=H_timing+924; --Initial position -- Alert position X2 RIGHT
	signal AL_Y2: integer range 0 to V_tot:=V_timing+320; --Initial position -- Alert position Y2 RIGHT
	signal Offset : Integer := 30;
	
	-- Define dimensions and offset of commands pad
	shared variable Xbtn : integer := H_timing+150; -- Buttons offset
	shared variable Ybtn : integer := V_timing+520;
	shared variable D : integer := 70; -- Distance from offset boundaries
	signal X_BTN_UP: integer range 0 to H_tot:=Xbtn+D;
	signal Y_BTN_UP: integer range 0 to V_tot:=Ybtn;
	signal X_BTN_RIGHT: integer range 0 to H_tot:=Xbtn+D+D;
	signal Y_BTN_RIGHT: integer range 0 to V_tot:=Ybtn+D;
	signal X_BTN_LEFT: integer range 0 to H_tot:=Xbtn;
	signal Y_BTN_LEFT: integer range 0 to V_tot:=Ybtn+D;
	signal X_BTN_DOWN: integer range 0 to H_tot:=Xbtn+D;
	signal Y_BTN_DOWN: integer range 0 to V_tot:=Ybtn+D+D;
	signal X_MOTOR: integer range 0 to H_tot:=H_timing+1150;
	signal Y_MOTOR: integer range 0 to V_tot:=V_timing+60;
	signal S : Integer := 50; -- Button side for command pad
	signal S_motor : Integer := 150; -- Motor alert side (Same entity of command pads,  but different sizes)
	
	-- Horn position parameters
	signal X_HORN: integer range 0 to H_tot:=H_timing+650; -- Horn offsets
	signal Y_HORN: integer range 0 to V_tot:=V_timing+260;
	signal D_HORN : Integer := 30;
	
	-- Next,procedure is called. HPOS is assigned to Xcur and VPOS to Ycur
begin
	SQ(HPOS,VPOS,SQ_X,SQ_Y,H_side,V_side,DRAW_fr); -- Green frame
	CAR(HPOS,VPOS,CAR_X,CAR_Y,A,A1,E,D1,D2,H,H1,H2,T,P,F,R1,AN,DRAW_car);
	ALERT(HPOS,VPOS,AL_X1,AL_Y1,Offset,DRAW_AL1);
	ALERT(HPOS,VPOS,AL_X2,AL_Y2,Offset,DRAW_AL2);
	BTNVGA(HPOS,VPOS,X_BTN_UP,Y_BTN_UP,S,DRAW_UP);
	BTNVGA(HPOS,VPOS,X_BTN_RIGHT,Y_BTN_RIGHT,S,DRAW_RIGHT);
	BTNVGA(HPOS,VPOS,X_BTN_LEFT,Y_BTN_LEFT,S,DRAW_LEFT);
	BTNVGA(HPOS,VPOS,X_BTN_DOWN,Y_BTN_DOWN,S,DRAW_DOWN);
	BTNVGA(HPOS,VPOS,X_MOTOR,Y_MOTOR,S_motor,DRAW_M); -- MOTOR ALERT
	HORN(HPOS,VPOS,X_HORN,Y_HORN,D_HORN,DRAW_H);
	
	process(CLK)
	begin
		if(CLK'event and CLK='1')then
		-- If DRAW is high, assign to the vga output the RGB signal of the procedure
			if(DRAW_fr = '1')then -- Draw the frame
				R<=(others=>'0');
				G<=(others=>'1');
				B<=(others=>'0');
			elsif(DRAW_car = '1')then -- Draw the car
				R<=(others=>'1');
				G<=(others=>'1');
				B<=(others=>'1');
			elsif(DRAW_AL1 = '1' AND KEYS(2)='1')then -- Draw the first alarm
				R<=(others=>'1');
				G<=(others=>'0');
				B<=(others=>'0');
			elsif(DRAW_AL2 = '1' AND KEYS(1)='1')then -- Draw the second alarm
				R<=(others=>'1');
				G<=(others=>'0');
				B<=(others=>'0');
			elsif(DRAW_M = '1' AND KEYS(0)='1')then -- Draw the motor
				R<=(others=>'1');
				G<=(others=>'0');
				B<=(others=>'0');
			elsif(DRAW_H = '1' AND BTN(4) = '1')then -- Draw the horn
				R<=(others=>'0');
				G<=(others=>'1');
				B<=(others=>'1');
			elsif(DRAW_UP = '1')then -- Draw the UP command
				if(BTN(0)='1')then -- If the button is pressed: UP command is pink
					R<=(others=>'1');
					G<=(others=>'0');
					B<=(others=>'1');
				else -- If the button is NOT pressed: UP command is white
					R<=(others=>'1');
					G<=(others=>'1');
					B<=(others=>'1');
			end if;
			elsif(DRAW_RIGHT = '1')then
				if(BTN(3)='1')then
					R<=(others=>'1');
					G<=(others=>'0');
					B<=(others=>'1');
				else
					R<=(others=>'1');
					G<=(others=>'1');
					B<=(others=>'1');
				end if;
			elsif(DRAW_LEFT = '1')then
				if(BTN(1)='1')then
					R<=(others=>'1');
					G<=(others=>'0');
					B<=(others=>'1');
				else
					R<=(others=>'1');
					G<=(others=>'1');
					B<=(others=>'1');
				end if;
			elsif(DRAW_DOWN = '1')then
				if(BTN(2)='1')then
					R<=(others=>'1');
					G<=(others=>'0');
					B<=(others=>'1');
				else
					R<=(others=>'1');
					G<=(others=>'1');
					B<=(others=>'1');
				end if;
			else
				R<=(others=>'0');
				G<=(others=>'0');
				B<=(others=>'0');
			end if; 
			if(DRAW_fr='0' AND DRAW_car='0' AND DRAW_AL1='0' AND DRAW_AL2='0' AND DRAW_UP='0'
			AND DRAW_RIGHT='0' AND DRAW_LEFT='0' AND DRAW_DOWN='0' AND DRAW_M='0' AND DRAW_H='0')then 
			-- Reason why it's useful to have DRAWs separed, in this way if all are zero then the pixels switch off
					R<=(others=>'0');
					G<=(others=>'0');
					B<=(others=>'0');
			end if;
			--Update HPOS and VPOS according to VGA timing parameters
			if(HPOS<H_tot)then
				HPOS<=HPOS+1;
			else
				HPOS<=0;
				if(VPOS<V_tot)then
					VPOS<=VPOS+1;
				else
					VPOS<=0;
				end if;
			end if;
			if(HPOS>H_FP and HPOS<H_BP)then 
				HSYNC<='0';
			else
				HSYNC<='1';
			end if;
			if(VPOS>V_FP and VPOS<V_BP)then
				VSYNC<='0';
			else
				VSYNC<='1';
			end if;
				if((HPOS>0 and HPOS<H_timing) or (VPOS>0 and VPOS<V_timing)) then
					R<=(others=>'0');
					G<=(others=>'0');
					B<=(others=>'0');
				end if;
		end if;
	end process;
end Main;