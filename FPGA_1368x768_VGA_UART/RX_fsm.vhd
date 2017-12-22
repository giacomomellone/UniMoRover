----------------------------------------------------------------------------------
-- PSE 2016/2017
-- Students: Mazzocchi, Mellone, Pistoni, Truffellini, Vidoni

-- Receiver Finite state Machine, used for translating messages coming from UART
-- to suitable alert signals to be displayed on VGA
----------------------------------------------------------------------------------
-- This FSM has the role of waiting for data reception and message translation.
-- When a data from the uart is ready (about 50ms between the ACKs messages) the rx_ready
-- bit is set, the FSM is activated and when the data is received as a byte (ASCII) is then 
-- translated to a suitable form for being displayed through VGA entity (ALERT).

library ieee;
use ieee.std_logic_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.MATH_REAL.ALL;


entity RX_fsm is
port ( 
	-- Control
	clk			: in	std_logic;		-- Main clock
	rst			: in	std_logic;		-- Main reset
	-- External interface
	rx_ready 	: in  std_logic;
   rx_data 		: in  std_logic_vector (7 downto 0);
   ALERT 		: out  std_logic_vector (2 downto 0)
);
end RX_fsm;

architecture Behavioral of RX_fsm is

	-- Types
	type state is (idle,read_data,stop);

	-- RX Signals
	signal rx_fsm, next_state			:	state;			-- Control of transmission, check next_state
	signal DATA : std_logic_vector(7 downto 0);			-- Vector for backupping received data			

begin

-- -------------------------------------------------------------------------
-- ------------------------ Receiver FSM -----------------------------------
-- -------------------------------------------------------------------------
	
	-- Serial data Receiver
	SYNC_PROC :process(clk)
	begin
		if rising_edge(clk) then
			-- Reset condition

			if rst = '1' then
					rx_fsm		<=	idle;
					DATA			<= "00000000";
					ALERT 		<= "000";
			else
				-- external tx request detection
					rx_fsm		<=	next_state;

				-- FSM description
					case rx_fsm is
					
					-- Wait to receive data
						when idle =>
						-- Wait to receive ready_rx bit
							if (rx_ready = '1') then
								DATA			<= rx_data;		-- Save the received data in a vector, to preserve it
								rx_fsm		<=	read_data;
							else 
								rx_fsm 	<= idle;
							end if;
							
					-- KEY/ALERT assignment
						when read_data =>
							-- In this example DATA can assume the values
								-- A <= "01000001" bynary value
								-- B <= "01000010"
								-- C <= "01000011"
								-- D <= "01000100"
								-- ...
							case DATA is
							  when "01000001" =>   ALERT 	<= "000"; -- A
							  when "01000010" =>   ALERT	<= "001"; -- B
							  when "01000011" =>   ALERT	<= "010"; -- C
							  when "01000100" =>   ALERT	<= "011"; -- D
							  when "01000101" =>   ALERT 	<= "100"; -- E
							  when "01000110" =>   ALERT	<= "101"; -- F
							  when "01000111" =>   ALERT	<= "110"; -- G
							  when "01001000" =>   ALERT	<= "111"; -- H
							  when others => ALERT 	<= "000";
							end case;
							rx_fsm <= stop;
							
					-- End of communication		
						when stop =>
							rx_fsm		<=	idle;
							
							
					-- Invalid States
						when others => null;
					end case;
				end if;
			end if;
	end process;
end Behavioral;

