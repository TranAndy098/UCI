----------------------------------------------------------------------
-- Digital Design 101 Lab Assignment 1 - S21
-- LFDetector Behavioral Model
----------------------------------------------------------------------
-- Student First Name : Andy
-- Student Last Name : Tran
-- Student ID : 57422363
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY LFDetector_behav IS
   PORT (Fuel3, Fuel2, Fuel1, Fuel0: IN std_logic;
         FuelWarningLight: OUT std_logic);
END LFDetector_behav;

ARCHITECTURE Behavior OF LFDetector_behav IS

-- DO NOT modify any signals, ports, or entities above this line
-- add your code below this line
-- put your code in a PROCESS
-- use AND/OR/NOT keywords for behavioral function
BEGIN
    PROCESS (Fuel3, Fuel2, Fuel1, Fuel0)
    BEGIN
        FuelWarningLight <= (NOT Fuel3) AND (NOT Fuel2) after 3.4 ns;
    END PROCESS;

END Behavior;