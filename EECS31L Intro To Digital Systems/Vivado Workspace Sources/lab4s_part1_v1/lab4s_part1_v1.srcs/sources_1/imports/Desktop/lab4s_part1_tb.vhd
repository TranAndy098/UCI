--------------------------------------------------------------------------------
-- Company: EECS 31L - S'21
-- Engineer: 
--
-- Create Date:   
-- Design Name:   
-- Module Name:   
-- Project Name:  lab04 part 1
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: Locator_struct
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
USE std.textio.ALL; -- for write, writelin
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY lab4s_tb IS
END lab4s_tb;
 
ARCHITECTURE behavior OF lab4s_tb IS
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Locator_struct
    PORT(
         Clk : IN  std_logic;
         Start : IN  std_logic;
         Rst : IN  std_logic;
         Loc : OUT  std_logic_vector(15 downto 0);
		 Done : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal Clk : std_logic := '0';
   signal Start : std_logic := '0';
   signal Rst : std_logic := '1';

     --Outputs
   signal Loc : std_logic_vector(15 downto 0);
   signal Done : std_logic;

   -- Clock period definitions; change to correct value; code will not compile w/o it
   constant Clk_period : time := 22 ns;
 
BEGIN
 
    -- Instantiate the Unit Under Test (UUT)
   uut: Locator_struct PORT MAP (
          Clk => Clk,
          Start => Start,
          Rst => Rst,
		  Loc => Loc,
          Done => Done
        );

   -- Clock process definitions
   Clk_process :process
   begin
        Clk <= '0';
        wait for Clk_period/2;
        Clk <= '1';
        wait for Clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
    variable stringbuff : LINE;
   begin        
		-- feel free to change any code below. This is not complete, just a template to start with.
		-- add your assert statement where appropriate based on your FSMD
		
        WRITE (stringbuff, string'("Simulation starts at "));
        WRITE (stringbuff, now);
        WRITELINE (output, stringbuff);

        Rst <= '1';
        WAIT FOR 100 NS; -- allow time for everything to rst
        Rst <= '0';
        WAIT FOR 15 NS; -- give some time between pressing rst & start button
        
        Start <= '1';
        WAIT UNTIL rising_edge(clk); -- wait for a rising edge so that it is easier to calculate next several wait statements
        WAIT FOR 10 NS; -- hold for some amount of time
        Start <= '0';
       
		-- remove line below & add your own waits, asserts, etc.
		WAIT FOR 400 NS; -- arbitrary wait time
		ASSERT Done = '1' REPORT "Done = 1 fail with test case 1" SEVERITY WARNING;
        ASSERT Loc = X"1b50" REPORT "Loc = 6992/1b50 fail with test case 2" SEVERITY WARNING;
        WAIT FOR 100 NS;
        
        Rst <= '1';
        WAIT FOR 100 NS; -- allow time for everything to rst
        Rst <= '0';
        WAIT FOR 15 NS; -- give some time between pressing rst & start button
        
        Start <= '1';
        WAIT UNTIL rising_edge(clk); -- wait for a rising edge so that it is easier to calculate next several wait statements
        WAIT FOR 10 NS; -- hold for some amount of time
        Start <= '0';
       
		-- remove line below & add your own waits, asserts, etc.
		WAIT FOR 400 NS; -- arbitrary wait time
		ASSERT Done = '1' REPORT "Done = 1 fail with test case 3" SEVERITY WARNING;
        ASSERT Loc = X"1b50" REPORT "Loc = 6992/1b50 fail with test case 4" SEVERITY WARNING;
        WAIT FOR 100 NS;
        
        WRITE (stringbuff, string'("Simulation Ends at "));
        WRITE (stringbuff, now);
        WRITELINE (output, stringbuff);

        wait; -- will wait forever
   end process;

END;
