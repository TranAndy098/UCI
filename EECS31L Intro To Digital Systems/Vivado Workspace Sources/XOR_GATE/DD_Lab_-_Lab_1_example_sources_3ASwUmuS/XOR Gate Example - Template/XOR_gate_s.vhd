----------------------------------------------------------------------
-- Digital Design Lab
-- XOR Gate Structural Model
----------------------------------------------------------------------
-- Student First Name : Your First Name
-- Student Last Name : Your Last Name
-- Student ID : Your Student ID
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY NOR2 IS
   PORT (x: IN std_logic;
         y: IN std_logic;
         F: OUT std_logic);
END NOR2;  

ARCHITECTURE behav OF NOR2 IS
BEGIN
   PROCESS(x, y)
   BEGIN
      F <= x NOR y AFTER 1.4 ns; 
   END PROCESS;
END behav;
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY XOR_gate_struct IS
   PORT (a, b: IN std_logic;
         F: OUT std_logic);
END XOR_gate_struct;

ARCHITECTURE Struct OF XOR_gate_struct IS

-- add your code here

END Struct;