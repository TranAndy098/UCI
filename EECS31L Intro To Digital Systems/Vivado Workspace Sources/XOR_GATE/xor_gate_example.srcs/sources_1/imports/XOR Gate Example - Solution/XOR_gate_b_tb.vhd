LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY Testbench IS
END Testbench;

ARCHITECTURE tb OF Testbench IS
    COMPONENT XOR_gate IS
    	PORT(	a: IN std_logic;
                b: IN std_logic;
                F: OUT std_logic);
    END COMPONENT;
    
    SIGNAL a, b, F: std_logic;

BEGIN
    testObject : XOR_gate PORT MAP (a, b, F);
    
    PROCESS
    BEGIN
        a <= '0'; b <= '0';
        WAIT FOR 10 ns;
        a <= '0'; b <= '1';
        WAIT FOR 10 ns;
        a <= '1'; b <= '0';
        WAIT FOR 10 ns;
        a <= '1'; b <= '1';
        WAIT;
    END PROCESS;



END tb;