----------------------------------------------------------------
-- PSE 2016/2017
-- Students: Mazzocchi, Mellone, Pistoni, Truffellini, Vidoni

-- Counter to enable tx_req each TOT ms
----------------------------------------------------------------
-- The role of this FSM is to enable the transmission of data each 50ms (the interval can
-- be easily changed modifying the wait_cnt value, counting the number of clock cycles).
-- Once that the value has been reached the tx_req signal is set high, requesting for data
-- sending. This approach allows to send command pad information even if no button is pushed
-- (sending in this way the STOP signal) so having the advantage of receiving continuosly,
-- every 50ms, ACKs packets vehicle sides so to update VGA signals display, at the cost of an 
-- higher employ of resources

library ieee;
use ieee.std_logic_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.MATH_REAL.ALL;


entity TX_counter is
port (
	-- Control
	clk			: in	std_logic;		-- Main clock
	rst			: in	std_logic;		-- Main reset
	-- External Interface
	tx_req		: out	std_logic;		-- Request SEND of data
	tx_end		: in	std_logic		-- Data SENT
);
end TX_counter;

architecture Behavioral of TX_counter is

	-- Types
	type state is (idle,count,send,stop);

	-- TX Signals
	signal tx_fsm, next_state			:	state;							-- Control of transmission
	
	-- Counter signal
	signal wait_cnt 		: unsigned(24 downto 0);
   signal counter_on  	: std_logic;
   signal count_done  	: std_logic;

begin

-- -------------------------------------------------------------------------
-- WAITING FLAG REGISTERS
-- -------------------------------------------------------------------------

	 counter_core : process (CLK)
    begin
        if (rising_edge(CLK)) then
            if (counter_on = '1') then
                wait_cnt <= wait_cnt + 1;
            else
                wait_cnt <= (others => '0');
            end if;
        end if;
    end process;

-- Using counter_core is possible to do different counters

    counter_50ms : process (CLK)
    begin
        if (rising_edge(CLK)) then
				if (wait_cnt = "10011000100101101000000") then -- 5*10^6 counts, 50ms with 100MHz clock
				--if (wait_cnt = "100110001001011010000000") then -- 10*10^6 counts, 100ms with 100MHz clock
				--if (wait_cnt = "1001100010010110100000000") then -- 20*10^6 counts, 200ms with 100MHz clock
				--if (wait_cnt = "10111110101111000010000000") then -- 50*10^6 counts, 500ms with 100MHz clock
                count_done <= '1';
            else
                count_done <= '0';
            end if;
        end if;
    end process;
	 
-- -------------------------------------------------------------------------
-- ---------------------- Transmitter FSM ----------------------------------
-- -------------------------------------------------------------------------

	-- Serial data Transmitter
	SYNC_PROC :process(clk)
	begin
		if rising_edge(clk) then
			-- Reset condition

			if rst = '1' then
					tx_fsm		<=	idle;
					counter_on	<= '0';
					tx_req		<= '0';
			else
				-- external tx request detection
					tx_fsm		<=	next_state;

				-- FSM description
					case tx_fsm is
					
					-- Wait to transfer data
						when idle =>
						-- Send Init Bit
							tx_req 		<= '0';
							counter_on 	<= '0';
							tx_fsm		<=	count;
							
					-- Counter enabled
						when count =>
							tx_req 		<= '0';
							counter_on 	<= '1';	-- Counter starts
							if (count_done = '1') then
								tx_fsm		<=	send;
							else 
								tx_fsm 	<= count;
							end if;
							
					-- Transmission request
						when send =>
							tx_req 		<= '1';
							counter_on 	<= '0';	-- Counter stop
							tx_fsm		<=	stop;
							
					-- End of communication
						when stop =>
						-- Transmission stopped and wait for tx_end
							tx_req 		<= '0';
							counter_on 	<= '0';	-- Counter stop
							if (tx_end = '1') then
								tx_fsm		<=	idle;
							else 
								tx_fsm 	<= stop;
							end if;
							
					-- Invalid States
						when others => null;
					end case;
				end if;
			end if;
	end process;
end Behavioral;
