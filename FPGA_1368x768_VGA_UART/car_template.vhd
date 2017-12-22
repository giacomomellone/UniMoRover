----------------------------------------------------------------------------------
-- PSE 2016/2017
-- Students: Mazzocchi, Mellone, Pistoni, Truffellini, Vidoni

-- Description: 	CAR template for VGA
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

package car_vga is
procedure CAR (signal Xcur,Ycur,Xoff,Yoff: in INTEGER; 
					signal A,A1,E,D1,D2,H,H1,H2,T,P,F,R1,AN: in INTEGER;
					signal DRAW: out STD_LOGIC
				  );
end car_vga;

package body car_vga is

procedure CAR (signal Xcur,Ycur,Xoff,Yoff: in INTEGER;
					signal A,A1,E,D1,D2,H,H1,H2,T,P,F,R1,AN: in INTEGER;
					signal DRAW: out STD_LOGIC) is
begin

if((Ycur>Yoff+H AND Ycur<Yoff+H+F AND (Xcur=Xoff OR Xcur=Xoff+A+A1+T+P+E))
	OR
	(Xcur>Xoff AND Xcur<Xoff+A+A1+T+P+E AND Ycur=Yoff+H+F)
	OR
	--(((Xcur>Xoff AND Xcur<Xoff+A) OR (Xcur>Xoff+A+A1+T AND Xcur<Xoff+A+A1+T+P+E)) AND (Ycur=Yoff+H)) This is the
	-- versione with the line 'P'
	(((Xcur>Xoff AND Xcur<Xoff+A) OR (Xcur>Xoff+A+A1+T+P AND Xcur<Xoff+A+A1+T+P+E)) AND (Ycur=Yoff+H))
	OR
	((Xcur>Xoff+A+A1 AND Xcur<Xoff+A+A1+T+P) AND Ycur=Yoff) -- Roof top
	OR
	--((Xcur>=Xoff+A AND Xcur<=Xoff+A+A1) AND Ycur=Yoff+H2) -- Part with only A1
	((Xcur>=Xoff+A AND Xcur<=Xoff+A+A1+T+P) AND Ycur=Yoff+H2) -- Part with only A1 and added part for car door 
	OR
	--((Ycur>Yoff AND Ycur<Yoff+H) AND (Xcur>Xoff+A+A1+T AND Xcur<Xoff+A+A1+T+P)) -- Windshield
	((Ycur>Yoff AND Ycur<Yoff+H) AND (Xcur=Xoff+A+A1+T+P)) -- Parte del baule
	OR
	((Ycur>Yoff AND Ycur<Yoff+H+F) AND (Xcur=Xoff+A+A1+T)) -- Car door
	OR
	((Ycur>Yoff+H2 AND Ycur<=Yoff+H2+H1) AND Xcur=Xoff+A) -- H1
	OR
	((Ycur>Yoff AND Ycur<=Yoff+H2) AND Xcur=Xoff+A+A1) -- H2
	--((Ycur>Yoff AND Ycur<=Yoff+H2+H1+F) AND Xcur=Xoff+A+A1) -- H2 + car door part
	OR
	((Ycur>Yoff+H2-AN AND Ycur<Yoff+H2) AND Xcur=Xoff+A) -- Antenna
	OR
	((Ycur>Yoff+H+F AND Ycur<Yoff+H+F+R1) AND (Xcur>Xoff+D1-R1 AND Xcur<Xoff+D1+R1))
	OR
	((Ycur>Yoff+H+F AND Ycur<Yoff+H+F+R1) AND (Xcur>Xoff+D2-R1 AND Xcur<Xoff+D2+R1))
	--OR
	--((Ycur*(A-C)=(Xcur*H-(Yoff*A-H*Xoff-C*Yoff-C*H))) AND (Ycur>Yoff AND Ycur<Yoff+H))
	--OR
	--((((Xcur-(Xoff+D1))**2)+((Ycur-(Yoff+H+F))**2)<((R1)**2)) AND (Ycur>Yoff+H+F AND Ycur<Yoff+H+F+R1)) -- First wheel
	)then
	DRAW<='1';
	else
	DRAW<='0';
end if;


end CAR;
end car_vga;

