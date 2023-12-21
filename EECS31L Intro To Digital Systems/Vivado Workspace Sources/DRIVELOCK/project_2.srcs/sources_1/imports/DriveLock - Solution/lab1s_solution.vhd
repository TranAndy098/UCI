----------------------------------------------------------------------
-- EECS31L/CSE31L Assignment1
-- DriveLock Structural Model
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
ENTITY DriveLock_struct IS
   PORT (k, p, s, d: IN std_logic;
         w: OUT std_logic);
END DriveLock_struct;

ARCHITECTURE Struct OF DriveLock_struct IS

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
    SIGNAL n5: std_logic;
    SIGNAL n6: std_logic;
    SIGNAL n7: std_logic;

BEGIN
    Nor2_1: Nor2 PORT MAP(k, k, n1);
    Nor2_2: Nor2 PORT MAP(p, p, n2);
    Nor2_3: Nor2 PORT MAP(s, s, n3);
    Nor2_4: Nor2 PORT MAP(d, d, n4);
    
    Nor2_5: Nor2 PORT MAP(n1, n2, n5);
    Nor2_6: Nor2 PORT MAP(n3, n4, n6);
    
    Nor2_7: Nor2 PORT MAP(n5, n5, n7);
    
    Nor2_8: Nor2 PORT MAP(n7, n6, w);
END Struct;