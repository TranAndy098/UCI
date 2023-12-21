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

	 Signal Current_State, Next_State: StateType:=Menu_State;
	 
begin

CombLogic: Process ( Button, Current_State)
 begin
   --Combinational Logic Process
   case Current_State IS
	 When Menu_State =>
	   Mode <= "00";
		if (Button = "00") then
		  Next_State <= Time_State;
		elsif (Button = "01") then
		  Next_State <= Alarm_State;
		elsif (Button = "10") then
		  Next_State <= Stopwatch_State;
		else 
		  Next_State <= Menu_State;
		end if;
		
	 When Time_State =>
	   Mode <= "01";
		if (Button = "11") then
		  Next_State <= Menu_State;
		else 
		  Next_State <= Time_State;
		end if;	
		
	When Alarm_State =>
	   Mode <= "10";
		if (Button = "11") then
		  Next_State <= Menu_State;
		else 
		  Next_State <= Alarm_State;
		end if;

	When Stopwatch_State =>
	   Mode <= "11";
		if (Button = "11") then
		  Next_State <= Menu_State;
		else 
		  Next_State <= Stopwatch_State;
		end if;
 end case;

end Process CombLogic;

StateRegister: Process (clk)
 begin
 -- State Register Process
 
   if(clk = '1' AND clk'EVENT ) then
    Current_State <= Next_State;
   end if;
 end Process StateRegister;
 
end Behavioral;