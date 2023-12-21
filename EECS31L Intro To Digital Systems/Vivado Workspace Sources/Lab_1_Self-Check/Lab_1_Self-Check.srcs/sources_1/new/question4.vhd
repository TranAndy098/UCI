----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/23/2021 10:03:14 PM
-- Design Name: 
-- Module Name: question4 - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY MyLogic IS
END MyLogic;
ARCHITECTURE Struct OF MyLogic IS

    COMPONENT And2 IS
        PORT (x, y: IN std_logic;
              f: OUT std_logic);
    END COMPONENT;

    COMPONENT CustomHW IS
        PORT (x: IN std_logic;
              f: OUT std_logic);
    END COMPONENT;

    SIGNAL n1, n2: std_logic;

BEGIN
    And2_1: And2 PORT MAP (x => i0,y => i2,f => n1);
    And2_2: And2 PORT MAP (x => i1,y => n2,f => d);
    CustHW: CustomHW PORT MAP (x => n1,f => n2);
END Struct;