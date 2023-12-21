--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   15:48:45 01/11/2012
-- Design Name:   
-- Module Name:   C:/Users/Yas/Yas/Yasaman/LIFE/PhD/SummerII_11/Lab2/Lab2_watch/TestBench_S.vhd
-- Project Name:  Lab2_watch
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: Wristwatch_S
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY TestBench_S IS
END TestBench_S;
 
ARCHITECTURE behavior OF TestBench_S IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Wristwatch_S
    PORT(
         clk : IN  std_logic;
         Button : IN  std_logic_vector(1 downto 0);
         Mode : OUT  std_logic_vector(1 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal Button : std_logic_vector(1 downto 0) := (others => '0');

 	--Outputs
   signal Mode : std_logic_vector(1 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Wristwatch_S PORT MAP (
          clk => clk,
          Button => Button,
          Mode => Mode
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- insert stimulus here 
		Button <= "10";
		WAIT UNTIL clk = '1' AND clk'EVENT;
		Wait for 15 NS ;
		ASSERT ( Mode = "11")  REPORT "Failed Menu_State -> Stopwatch_State" SEVERITY Warning;
		
		Button <= "11";
		WAIT UNTIL clk = '1' AND clk'EVENT;
		Wait for 15 NS ;
		ASSERT ( Mode = "00")  REPORT "Failed Menu_State -> Menu_State" SEVERITY Warning;
		
		Button <= "00";
		WAIT UNTIL clk = '1' AND clk'EVENT;
		Wait for 15 NS ;
		ASSERT ( Mode = "01")  REPORT "Failed Menu_State -> Time_State" SEVERITY Warning;

      wait;
   end process;

END;
