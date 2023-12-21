
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   16:00:15 07/19/2011
-- Design Name:   DriveLock_behav
-- Module Name:   D:/Work Files/Xilinx Stuff/EECS 31L/2011_summer/lab1a/lab1b_tb.vhd
-- Project Name:  lab1a
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: DriveLock_behav
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
USE ieee.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;

ENTITY lab1b_tb_vhd IS
END lab1b_tb_vhd;

ARCHITECTURE behavior OF lab1b_tb_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT DriveLock_behav
	PORT(
		k : IN std_logic;
		p : IN std_logic;
		s : IN std_logic;
		d : IN std_logic;          
		w : OUT std_logic
		);
	END COMPONENT;

	--Inputs
	SIGNAL k :  std_logic := '0';
	SIGNAL p :  std_logic := '0';
	SIGNAL s :  std_logic := '0';
	SIGNAL d :  std_logic := '0';

	--Outputs
	SIGNAL w :  std_logic;

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: DriveLock_behav PORT MAP(
		k => k,
		p => p,
		s => s,
		d => d,
		w => w
	);

	tb : PROCESS
	BEGIN

		-- Wait 100 ns for global reset to finish
		wait for 100 ns;

		-- Place stimulus here

		k <= '0';p <= '0';s <= '0';d <='0';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 0" SEVERITY WARNING;
		
		k <= '0';p <= '0';s <= '0';d <='1';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 1" SEVERITY WARNING;
		
		k <= '0';p <= '0';s <= '1';d <='0';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 2" SEVERITY WARNING;
		
		k <= '0';p <= '0';s <= '1';d <='1';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 3" SEVERITY WARNING;

		k <= '0';p <= '1';s <= '0';d <='0';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 4" SEVERITY WARNING;
		
		k <= '0';p <= '1';s <= '0';d <='1';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 5" SEVERITY WARNING;
		
		k <= '0';p <= '1';s <= '1';d <='0';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 6" SEVERITY WARNING;
		
		k <= '0';p <= '1';s <= '1';d <='1';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 7" SEVERITY WARNING;

		k <= '1';p <= '0';s <= '0';d <='0';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 8" SEVERITY WARNING;
		
		k <= '1';p <= '0';s <= '0';d <='1';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 9" SEVERITY WARNING;
		
		k <= '1';p <= '0';s <= '1';d <='0';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 10" SEVERITY WARNING;
		
		k <= '1';p <= '0';s <= '1';d <='1';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 11" SEVERITY WARNING;

		k <= '1';p <= '1';s <= '0';d <='0';
		wait for 10 ns;
		ASSERT w = '1' REPORT "w = 1 failed with testvector 12" SEVERITY WARNING;
		
		k <= '1';p <= '1';s <= '0';d <='1';
		wait for 10 ns;
		ASSERT w = '1' REPORT "w = 1 failed with testvector 13" SEVERITY WARNING;
		
		k <= '1';p <= '1';s <= '1';d <='0';
		wait for 10 ns;
		ASSERT w = '1' REPORT "w = 1 failed with testvector 14" SEVERITY WARNING;
		
		k <= '1';p <= '1';s <= '1';d <='1';
		wait for 10 ns;
		ASSERT w = '0' REPORT "w = 0 failed with testvector 15" SEVERITY WARNING;

		wait; -- will wait forever
	END PROCESS;

END;
