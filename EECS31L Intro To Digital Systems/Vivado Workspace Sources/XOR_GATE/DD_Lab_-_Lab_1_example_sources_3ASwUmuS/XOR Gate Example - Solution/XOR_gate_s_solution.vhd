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
    COMPONENT Nor2 IS
        PORT (  x: IN std_logic;
                y: IN std_logic;
                F: OUT std_logic);
    END COMPONENT;
    
    SIGNAL n1: std_logic;
    SIGNAL n2: std_logic;
    SIGNAL n3: std_logic;
    SIGNAL n4: std_logic;

BEGIN
    Nor2_1: Nor2 PORT MAP(a, a, n1);
    Nor2_2: Nor2 PORT MAP(b, b, n2);
    Nor2_3: Nor2 PORT MAP(n1, n2, n3);
    Nor2_4: Nor2 PORT MAP(a, b, n4);
    Nor2_5: Nor2 PORT MAP(n3, n4, F);
END Struct;