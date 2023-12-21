----------------------------------------------------------------------
-- Digital Design Lab
-- XOR Gate Behavioral Model
----------------------------------------------------------------------
-- Student First Name : Your First Name
-- Student Last Name : Your Last Name
-- Student ID : Your Student ID
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY XOR_gate IS
	PORT(	a: IN std_logic;
			b: IN std_logic;
			F: OUT std_logic);
END XOR_gate;  


ARCHITECTURE behav OF XOR_gate IS

  -- add your code here
BEGIN
  -- XOR represented with 2-input NOR gates: ((a’ + b’)’ + (a + b)’)’ 
  F <= (((NOT(a)) NOR (NOT(b))) NOR (a NOR b)) AFTER 4.2 ns;
END behav;