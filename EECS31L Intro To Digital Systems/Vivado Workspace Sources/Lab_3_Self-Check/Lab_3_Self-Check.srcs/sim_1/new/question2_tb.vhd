LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE std.textio.ALL;

ENTITY lab3s_tb IS
END lab3s_tb;
 
ARCHITECTURE behavior OF lab3s_tb IS
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Add_4bit
    PORT(
         A, B: in std_logic_vector (3 downto 0);
          Cin: in std_logic;
          F: out std_logic_vector (3 downto 0);
          Cout: out std_logic
        );
    END COMPONENT;


   --Inputs
   signal A : std_logic_vector(3 downto 0) := "0000";
   signal B : std_logic_vector(3 downto 0) := "0000";
   signal Cin : std_logic := '0';

     --Outputs
   signal F : std_logic_vector(3 downto 0);
   signal Cout : std_logic;

 
BEGIN
 
    -- Instantiate the Unit Under Test (UUT)
   uut: Add_4bit PORT MAP (
          A => A,
          B => B,
          Cin => Cin,
		  F => F,
          Cout => Cout
        );

  
 

   -- Stimulus process
   stim_proc: process
    variable stringbuff : LINE;
   begin        
		-- feel free to change any code below. This is not complete, just a template to start with.
		-- add your assert statement where appropriate based on your FSMD
		
        WRITE (stringbuff, string'("Simulation starts at "));
        WRITE (stringbuff, now);
        WRITELINE (output, stringbuff);
        Cin <= '0';
        WAIT FOR 10 NS; -- allow time for everything to rst
        A <= "0000";
        B <= "0001";
        
        WAIT FOR 10 NS; -- allow time for everything to rst
        A <= "0000";
        B <= "1111";
        
        WAIT FOR 10 NS; -- allow time for everything to rst
        A <= "1111";
        B <= "0001";
        
        WAIT FOR 10 NS; -- allow time for everything to rst
        A <= "1010";
        B <= "0101";
        
        WAIT FOR 10 NS; -- allow time for everything to rst
        A <= "1011";
        B <= "0001";
        WRITE (stringbuff, string'("Simulation Ends at "));
        WRITE (stringbuff, now);
        WRITELINE (output, stringbuff);

        wait; -- will wait forever
   end process;

END;
