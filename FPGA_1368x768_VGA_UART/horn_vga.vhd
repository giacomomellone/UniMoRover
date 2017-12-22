----------------------------------------------------------------------------------
-- PSE 2016/2017
-- Students: Mazzocchi, Mellone, Pistoni, Truffellini, Vidoni

-- Module Name:    HORN, displayed when pressing the central button
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

package horn_vga is
procedure HORN (signal Xcur,Ycur,Xpos,Ypos,Offset: in INTEGER; 
				  signal DRAW: out STD_LOGIC
				  );
end horn_vga;

package body horn_vga is

procedure HORN (signal Xcur,Ycur,Xpos,Ypos,Offset: in INTEGER; 
					signal DRAW: out STD_LOGIC) is
begin

if((Xcur = Xpos AND (Ycur<Ypos+50 AND Ycur>Ypos-50)) OR 
	(Xcur = Xpos+Offset AND (Ycur<Ypos+27 AND Ycur>Ypos-27)) OR 
	(Xcur = Xpos+2*Offset AND (Ycur<Ypos+12 AND Ycur>Ypos-12)) 
	)then
	DRAW<='1';
	else
	DRAW<='0';
end if;


end HORN;
end horn_vga;

