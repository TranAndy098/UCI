----------------------------------------------------------------------
-- EECS31L/CSE31L Assignment1
-- DriveLock Behavioral Model
----------------------------------------------------------------------
-- Student First Name : Your First Name
-- Student Last Name : Your Last Name
-- Student ID : Your Student ID
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY DriveLock_behav IS
   PORT (k, p, s, d: IN std_logic;
         w: OUT std_logic);
END DriveLock_behav;

ARCHITECTURE Behav OF DriveLock_behav IS


-- add your code here
BEGIN
   PROCESS (k, p, s, d)
   BEGIN
      w <= (NOT ((NOT k) NOR (NOT p))) NOR ((NOT s) NOR (NOT d)) AFTER 5.6 ns;
   END PROCESS;

END Behav;