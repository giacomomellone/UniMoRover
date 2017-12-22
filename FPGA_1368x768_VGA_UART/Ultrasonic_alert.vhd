----------------------------------------------------------------------------------
-- Create Date:    11:27:38 04/14/2017 
-- Module Name:    Ultrasonic_alert - Behavioral 
-- Description: The aim is to alert on the VGA car template that there's an obstacle
-- on the range

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

package ultrasonic is
procedure ALERT (signal Xcur,Ycur,Xpos,Ypos,Offset: in INTEGER; 
				  signal DRAW: out STD_LOGIC
				  );
end ultrasonic;

package body ultrasonic is

procedure ALERT (signal Xcur,Ycur,Xpos,Ypos,Offset: in INTEGER; 
					signal DRAW: out STD_LOGIC) is
begin

if((Xcur>Xpos AND Xcur<(Xpos+(5*Offset)) AND (Ycur>Ypos AND Ycur<Ypos+(5*Offset)))
	AND
	((Xcur=Xpos OR Xcur=Xpos+Offset OR Xcur=Xpos+Offset*2 OR Xcur=Xpos+Offset*3 OR Xcur=Xpos+Offset*4) OR
	(Ycur=Ypos OR Ycur=Ypos+Offset OR Ycur=Ypos+Offset*2 OR Ycur=Ypos+Offset*3 OR Ycur=Ypos+Offset*4))
	)then
	DRAW<='1'; -- How to remain in this state for a given number of seconds? Maybe not necessary
	else
	DRAW<='0';
end if;


end ALERT;
end ultrasonic;

