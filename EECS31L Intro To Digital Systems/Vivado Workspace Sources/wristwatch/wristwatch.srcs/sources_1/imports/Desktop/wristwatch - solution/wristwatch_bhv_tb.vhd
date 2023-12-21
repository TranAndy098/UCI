--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   15:41:50 01/22/2013
-- Design Name:   
-- Module Name:   C:/Users/Aras/Documents/EECS 31L/lab4/Students submission/student4b/Wristwatch_B_tb.vhd
-- Project Name:  student4b
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: Wristwatch_B
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
 
ENTITY Wristwatch_B_tb IS
END Wristwatch_B_tb;
 
ARCHITECTURE behavior OF Wristwatch_B_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Wristwatch_B
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
   uut: Wristwatch_B PORT MAP (
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
      -- hold reset state for 100 ns.
	   Button <= "11";
      wait for 100 ns;	

      wait for clk_period*10;

  		Button <= "10";
		WAIT UNTIL clk = '1' AND clk'EVENT;
		Wait for 15 NS ;
		ASSERT ( Mode = "11")  REPORT "Failed s0 -> s3" SEVERITY Warning;
		
		Button <= "11";
		WAIT UNTIL clk = '1' AND clk'EVENT;
		Wait for 15 NS ;
		ASSERT ( Mode = "00")  REPORT "Failed s3 -> s0" SEVERITY Warning;
		
		Button <= "00";
		WAIT UNTIL clk = '1' AND clk'EVENT;
		Wait for 15 NS ;
		ASSERT ( Mode = "01")  REPORT "Failed s0 -> s1" SEVERITY Warning;

      wait;
   end process;

END;