library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.ALL;


entity Add_2bit is
    port ( A, B: in std_logic_vector (1 downto 0);
          Cin: in std_logic;
          F: out std_logic_vector (1 downto 0);
          Cout: out std_logic);
        
end Add_2bit;

architecture Behavioral of Add_2bit is
signal C: std_logic_vector(2 downto 0);
begin
    process(A,B,Cin)
        begin
            C(0) <= Cin;
            for i in 0 to 2 loop
                F(i) <= A(i) XOR B(i) XOR C(i);
                C(i+1) <= (A(i) AND B(i)) OR (C(i) AND (A(i) XOR B(i)));
            end loop;
                Cout <= C(2);
        end process;

end Behavioral;
----------4bit adder -------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

entity Add_4bit is
    port ( A, B: in std_logic_vector (3 downto 0);
           Cin: in std_logic;
           F: out std_logic_vector (3 downto 0);
           Cout: out std_logic);
        
end Add_4bit;

architecture structural of Add_4bit is
    component Add_2bit is
        port ( A, B: in std_logic_vector (1 downto 0);
               Cin: in std_logic;
               F: out std_logic_vector (1 downto 0);
               Cout: out std_logic);
    end component;
    signal C: std_logic;
begin
    Add2_1 : Add_2bit PORT MAP (A => A(1 downto 0), B => B(1 downto 0), Cin => Cin, F => F(1 downto 0), Cout=>C);
    Add2_2 : Add_2bit PORT MAP (A=> A(3 downto 2), B => B(3 downto 2), Cin => Cin, F => F(3 downto 2), Cout=>Cout);
end structural;