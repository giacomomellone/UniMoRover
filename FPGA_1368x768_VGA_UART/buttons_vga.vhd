----------------------------------------------------------------------------------
-- PSE 2016/2017
-- Students: Mazzocchi, Mellone, Pistoni, Truffellini, Vidoni

-- Module Name:    buttons_vga
-- Description:    VGA printing of pressed key button
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

package button_vga is
procedure BTNVGA (signal Xcur,Ycur,Xbtn,Ybtn: in INTEGER; 
						signal S: in INTEGER;
						signal DRAW: out STD_LOGIC);
end button_vga;
package body button_vga is

procedure BTNVGA (signal Xcur,Ycur,Xbtn,Ybtn: in INTEGER; 
						signal S: in INTEGER;
						signal DRAW: out STD_LOGIC) is
begin
if((Xcur>Xbtn AND Xcur<(Xbtn+S)) AND (Ycur>Ybtn AND Ycur<(Ybtn+S))) then
	DRAW<='1';
	else
	DRAW<='0';
end if;
end BTNVGA;
end button_vga;

