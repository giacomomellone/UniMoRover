--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : vga_uart.vhf
-- /___/   /\     Timestamp : 12/13/2017 11:40:38
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -sympath "C:/Users/Giacomo/Dropbox/Ingegneria/Progettazione di Sistemi Embedded - Condivisa/REPORT/DA CONSEGNARE/VGA_Car_1368x768_UART/ipcore_dir" -intstyle ise -family spartan6 -flat -suppress -vhdl "C:/Users/Giacomo/Dropbox/Ingegneria/Progettazione di Sistemi Embedded - Condivisa/REPORT/DA CONSEGNARE/VGA_Car_1368x768_UART/vga_uart.vhf" -w "C:/Users/Giacomo/Dropbox/Ingegneria/Progettazione di Sistemi Embedded - Condivisa/REPORT/DA CONSEGNARE/VGA_Car_1368x768_UART/vga_uart.sch"
--Design Name: vga_uart
--Device: spartan6
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesized and simulated, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity vga_uart is
   port ( btn       : in    std_logic_vector (4 downto 0); 
          CLOCK_100 : in    std_logic; 
          RsRx      : in    std_logic; 
          AN        : out   std_logic_vector (3 downto 0); 
          RsTx      : out   std_logic; 
          SEG       : out   std_logic_vector (7 downto 0); 
          VGA_B     : out   std_logic_vector (3 downto 0); 
          VGA_G     : out   std_logic_vector (3 downto 0); 
          VGA_HS    : out   std_logic; 
          VGA_R     : out   std_logic_vector (3 downto 0); 
          VGA_VS    : out   std_logic);
end vga_uart;

architecture BEHAVIORAL of vga_uart is
   attribute BOX_TYPE   : string ;
   signal XLXN_59   : std_logic_vector (2 downto 0);
   signal XLXN_71   : std_logic;
   signal XLXN_79   : std_logic_vector (7 downto 0);
   signal XLXN_92   : std_logic_vector (7 downto 0);
   signal XLXN_97   : std_logic;
   signal XLXN_104  : std_logic;
   signal XLXN_105  : std_logic;
   signal XLXN_106  : std_logic;
   signal XLXN_111  : std_logic;
   signal XLXN_112  : std_logic;
   component VGA
      port ( CLOCK_100 : in    std_logic; 
             BTN       : in    std_logic_vector (4 downto 0); 
             VGA_HS    : out   std_logic; 
             VGA_VS    : out   std_logic; 
             VGA_R     : out   std_logic_vector (3 downto 0); 
             VGA_G     : out   std_logic_vector (3 downto 0); 
             VGA_B     : out   std_logic_vector (3 downto 0); 
             SEG       : out   std_logic_vector (7 downto 0); 
             AN        : out   std_logic_vector (3 downto 0); 
             COMMAND   : out   std_logic_vector (7 downto 0); 
             ALERT     : in    std_logic_vector (2 downto 0));
   end component;
   
   component uart
      port ( tx       : out   std_logic; 
             rx       : in    std_logic; 
             par_en   : in    std_logic; 
             rx_data  : out   std_logic_vector (7 downto 0); 
             rx_ready : out   std_logic; 
             tx_data  : in    std_logic_vector (7 downto 0); 
             tx_end   : out   std_logic; 
             tx_req   : in    std_logic; 
             rst      : in    std_logic; 
             clk      : in    std_logic);
   end component;
   
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
   component TX_counter
      port ( tx_req : out   std_logic; 
             tx_end : in    std_logic; 
             rst    : in    std_logic; 
             clk    : in    std_logic);
   end component;
   
   component RX_fsm
      port ( rx_data  : in    std_logic_vector (7 downto 0); 
             rst      : in    std_logic; 
             clk      : in    std_logic; 
             rx_ready : in    std_logic; 
             ALERT    : out   std_logic_vector (2 downto 0));
   end component;
   
begin
   XLXI_1 : VGA
      port map (ALERT(2 downto 0)=>XLXN_59(2 downto 0),
                BTN(4 downto 0)=>btn(4 downto 0),
                CLOCK_100=>CLOCK_100,
                AN(3 downto 0)=>AN(3 downto 0),
                COMMAND(7 downto 0)=>XLXN_79(7 downto 0),
                SEG(7 downto 0)=>SEG(7 downto 0),
                VGA_B(3 downto 0)=>VGA_B(3 downto 0),
                VGA_G(3 downto 0)=>VGA_G(3 downto 0),
                VGA_HS=>VGA_HS,
                VGA_R(3 downto 0)=>VGA_R(3 downto 0),
                VGA_VS=>VGA_VS);
   
   XLXI_2 : uart
      port map (clk=>CLOCK_100,
                par_en=>XLXN_71,
                rst=>XLXN_106,
                rx=>RsRx,
                tx_data(7 downto 0)=>XLXN_79(7 downto 0),
                tx_req=>XLXN_105,
                rx_data(7 downto 0)=>XLXN_92(7 downto 0),
                rx_ready=>XLXN_112,
                tx=>RsTx,
                tx_end=>XLXN_104);
   
   XLXI_7 : GND
      port map (G=>XLXN_71);
   
   XLXI_13 : TX_counter
      port map (clk=>CLOCK_100,
                rst=>XLXN_111,
                tx_end=>XLXN_104,
                tx_req=>XLXN_105);
   
   XLXI_15 : RX_fsm
      port map (clk=>CLOCK_100,
                rst=>XLXN_97,
                rx_data(7 downto 0)=>XLXN_92(7 downto 0),
                rx_ready=>XLXN_112,
                ALERT(2 downto 0)=>XLXN_59(2 downto 0));
   
   XLXI_16 : GND
      port map (G=>XLXN_97);
   
   XLXI_26 : GND
      port map (G=>XLXN_106);
   
   XLXI_29 : GND
      port map (G=>XLXN_111);
   
end BEHAVIORAL;


