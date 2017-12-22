----------------------------------------------------------------------------------
-- PSE 2016/2017
-- Students: Mazzocchi, Mellone, Pistoni, Truffellini, Vidoni

-- Description: Red and white square on VGA
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

package frame is
procedure SQ (signal Xcur,Ycur,Xpos,Ypos: in INTEGER; 
				  signal H,V: in INTEGER;
				  signal DRAW: out STD_LOGIC
				  );
end frame;

package body frame is

procedure SQ  (signal Xcur,Ycur,Xpos,Ypos: in INTEGER; 
					signal H,V: in INTEGER;
					signal DRAW: out STD_LOGIC) is
begin

if((Xcur>Xpos AND Xcur<(Xpos+H) AND (Ycur=Ypos OR Ycur=Ypos+V))
	OR
	(Ycur>Ypos AND Ycur<(Ypos+V) AND (Xcur=Xpos OR Xcur=Xpos+H))
	)then
	DRAW<='1';
	else
	DRAW<='0';
end if;

end SQ;
end frame;

