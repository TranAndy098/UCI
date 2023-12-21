----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:13:13 01/11/2012 
-- Design Name: 
-- Module Name:    Wristwatch_B - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Wristwatch_B is
    Port ( clk : in  STD_LOGIC;
           Button : in  STD_LOGIC_VECTOR (1 downto 0);
           Mode : out  STD_LOGIC_VECTOR (1 downto 0));
end Wristwatch_B;

architecture Behavioral of Wristwatch_B is

TYPE StateType IS
   (Menu_State, Time_State, Alarm_State, Stopwatch_State );

	 Signal Current_State, Next_State: StateType;
	 
begin
-- insert the code here
end Behavioral;

