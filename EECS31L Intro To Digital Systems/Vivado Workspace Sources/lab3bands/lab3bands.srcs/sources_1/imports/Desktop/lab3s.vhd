----------------------------------------------------------------------
-- EECS31L Assignment 3
-- Locator Structural Model
----------------------------------------------------------------------
-- Student First Name : Andy 
-- Student Last Name : Tran
-- Student ID : 57422363
----------------------------------------------------------------------

---------- Components library ----------

---------- 8x16 Register File ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY RegFile IS
   PORT (R_Addr1, R_Addr2, W_Addr: IN std_logic_vector(2 DOWNTO 0);
         R_en, W_en: IN std_logic;
         Reg_Data1 : OUT std_logic_vector(15 DOWNTO 0); 
			Reg_Data2 : OUT std_logic_vector(15 DOWNTO 0); 
         W_Data: IN std_logic_vector(15 DOWNTO 0); 
         Clk, Rst: IN std_logic);
END RegFile;

ARCHITECTURE Beh OF RegFile IS 
   TYPE regArray_type IS 
      ARRAY (0 TO 7) OF std_logic_vector(15 DOWNTO 0); 
   SIGNAL regArray : regArray_type;
BEGIN
   WriteProcess: PROCESS(Clk)    
   BEGIN
      IF (Clk = '1' AND Clk'EVENT) THEN
         IF (Rst = '1') THEN
            regArray(0) <= X"0000" AFTER 6.0 NS;
            regArray(1) <= X"000B" AFTER 6.0 NS;
            regArray(2) <= X"0023" AFTER 6.0 NS;
            regArray(3) <= X"0007" AFTER 6.0 NS;
            regArray(4) <= X"000A" AFTER 6.0 NS;
            regArray(5) <= X"0000" AFTER 6.0 NS;
            regArray(6) <= X"0000" AFTER 6.0 NS;
            regArray(7) <= X"0000" AFTER 6.0 NS;
         ELSE
            IF (W_en = '1') THEN
                regArray(conv_integer(W_Addr)) <= W_Data AFTER 6.0 NS;
                END IF;
        END IF;
     END IF;
   END PROCESS;
            
   ReadProcess1: PROCESS(R_en, R_Addr1, regArray)
   BEGIN
      IF (R_en = '1') THEN
        CASE R_Addr1 IS
            WHEN "000" =>
                Reg_Data1 <= regArray(0) AFTER 6.0 NS;
            WHEN "001" =>
                Reg_Data1 <= regArray(1) AFTER 6.0 NS;
            WHEN "010" =>
                Reg_Data1 <= regArray(2) AFTER 6.0 NS;
            WHEN "011" =>
                Reg_Data1 <= regArray(3) AFTER 6.0 NS;
            WHEN "100" =>
                Reg_Data1 <= regArray(4) AFTER 6.0 NS;
            WHEN "101" =>
                Reg_Data1 <= regArray(5) AFTER 6.0 NS;
            WHEN "110" =>
                Reg_Data1 <= regArray(6) AFTER 6.0 NS;
            WHEN "111" =>
                Reg_Data1 <= regArray(7) AFTER 6.0 NS;
            WHEN OTHERS =>
                Reg_Data1 <= (OTHERS=>'0') AFTER 6.0 NS;
        END CASE;
      ELSE
        Reg_Data1 <= (OTHERS=>'0') AFTER 6.0 NS;
      END IF;
   END PROCESS;
	
	ReadProcess2: PROCESS(R_en, R_Addr2, regArray)
   BEGIN
      IF (R_en = '1') THEN
        CASE R_Addr2 IS
            WHEN "000" =>
                Reg_Data2 <= regArray(0) AFTER 6.0 NS;
            WHEN "001" =>
                Reg_Data2 <= regArray(1) AFTER 6.0 NS;
            WHEN "010" =>
                Reg_Data2 <= regArray(2) AFTER 6.0 NS;
            WHEN "011" =>
                Reg_Data2 <= regArray(3) AFTER 6.0 NS;
            WHEN "100" =>
                Reg_Data2 <= regArray(4) AFTER 6.0 NS;
            WHEN "101" =>
                Reg_Data2 <= regArray(5) AFTER 6.0 NS;
            WHEN "110" =>
                Reg_Data2 <= regArray(6) AFTER 6.0 NS;
            WHEN "111" =>
                Reg_Data2 <= regArray(7) AFTER 6.0 NS;
            WHEN OTHERS =>
                Reg_Data2 <= (OTHERS=>'0') AFTER 6.0 NS;
        END CASE;
      ELSE
        Reg_Data2 <= (OTHERS=>'0') AFTER 6.0 NS;
      END IF;
   END PROCESS;
END Beh;


---------- 16-Bit ALU ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;


ENTITY ALU IS
    PORT (Sel: IN std_logic;
            A: IN std_logic_vector(15 DOWNTO 0);
            B: IN std_logic_vector(15 DOWNTO 0);
            ALU_Out: OUT std_logic_vector (15 DOWNTO 0) );
END ALU;

ARCHITECTURE Beh OF ALU IS

BEGIN
    PROCESS (A, B, Sel)
         variable temp: std_logic_vector(31 DOWNTO 0):= X"00000000";
    BEGIN
        IF (Sel = '0') THEN
            ALU_Out <= A + B AFTER 12 NS;                
        ELSIF (Sel = '1') THEN
            temp := A * B ;
                ALU_Out <= temp(15 downto 0) AFTER 12 NS; 
        END IF;
          
    END PROCESS;
END Beh;


---------- 16-bit Shifter ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Shifter IS
   PORT (I: IN std_logic_vector(15 DOWNTO 0);
         Q: OUT std_logic_vector(15 DOWNTO 0);
         sel: IN std_logic );
END Shifter;

ARCHITECTURE Beh OF Shifter IS 
BEGIN
   PROCESS (I,sel) 
   BEGIN
         IF (sel = '1') THEN 
            Q <= I(14 downto 0) & '0' AFTER 4.0 NS;
         ELSE
            Q <= '0' & I(15 downto 1) AFTER 4.0 NS;
         END IF;   
   END PROCESS; 
END Beh;


---------- 2-to-1 Selector ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Selector IS
   PORT (sel: IN std_logic;
         x,y: IN std_logic_vector(15 DOWNTO 0);
         f: OUT std_logic_vector(15 DOWNTO 0));
END Selector;

ARCHITECTURE Beh OF Selector IS 
BEGIN
   PROCESS (x,y,sel)
   BEGIN
         IF (sel = '0') THEN
            f <= x AFTER 3.0 NS;
         ELSE
            f <= y AFTER 3.0 NS;
         END IF;   
   END PROCESS; 
END Beh;


---------- 16-bit Register ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Reg IS
   PORT (I: IN std_logic_vector(15 DOWNTO 0);
         Q: OUT std_logic_vector(15 DOWNTO 0);
         Ld: IN std_logic; 
         Clk, Rst: IN std_logic );
END Reg;

ARCHITECTURE Beh OF Reg IS 
BEGIN
   PROCESS (Clk)
   BEGIN
      IF (Clk = '1' AND Clk'EVENT) THEN
         IF (Rst = '1') THEN
            Q <= X"0000" AFTER 4.0 NS;
         ELSIF (Ld = '1') THEN
            Q <= I AFTER 4.0 NS;
         END IF;   
      END IF;
   END PROCESS; 
END Beh;

---------- 16-bit Three-state Buffer ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY ThreeStateBuff IS
    PORT (Control_Input: IN std_logic;
          Data_Input: IN std_logic_vector(15 DOWNTO 0);
          Output: OUT std_logic_vector(15 DOWNTO 0) );
END ThreeStateBuff;

ARCHITECTURE Beh OF ThreeStateBuff IS
BEGIN
    PROCESS (Control_Input, Data_Input)
    BEGIN
        IF (Control_Input = '1') THEN
            Output <= Data_Input AFTER 2 NS;
        ELSE
            Output <= (OTHERS=>'Z') AFTER 2 NS;
        END IF;
    END PROCESS;
END Beh;

---------- Controller ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY Controller IS
    PORT(R_en: OUT std_logic;
         W_en: OUT std_logic;
         R_Addr1: OUT std_logic_vector(2 DOWNTO 0);
			R_Addr2: OUT std_logic_vector(2 DOWNTO 0);
         W_Addr: OUT std_logic_vector(2 DOWNTO 0);
         Shifter_Sel: OUT std_logic;
         Selector_Sel: OUT std_logic;
         ALU_sel : OUT std_logic;
         OutReg_Ld: OUT std_logic;
         Oe: OUT std_logic;
         Done: OUT std_logic;
         Start, Clk, Rst: IN std_logic); 
END Controller;


ARCHITECTURE Beh OF Controller IS

-------------------------------------------------------
-- Hint:
-- Controller shall consist of a CombLogic process 
-- containing case-statement and a StateReg process.
--      
-------------------------------------------------------

 -- add your code here
    TYPE Statetype IS (Start_State, Compute1_State, Compute2_State, Compute3_State, Compute4_State, Compute5_State, Compute6_State, End_State);
    SIGNAL Current_State, Next_State: Statetype;
begin
    process (CLk, Start, Rst, Current_State)
    begin
        R_en <= '1';
        W_en <= '1';
        Done <= '0';
        OutReg_Ld <= '0';
        Oe <= '0';
        Shifter_Sel <= '0';
        case Current_State is
            when Start_State =>
                W_en <= '0';
                R_Addr1 <= "000" after 2 ns;
			    R_Addr2 <= "000" after 2 ns;
                W_Addr <= "000" after 2 ns;
                Selector_Sel <= '0';
                ALU_sel <= '0';
                if Start = '1' then
                    Next_State <= Compute1_State after 11 ns;
                elsif Start = '0' then
                    Next_State <= Start_State after 11 ns;
                end if;
            when Compute1_State =>
                R_Addr1 <= "011" after 2 ns;
			    R_Addr2 <= "010" after 2 ns;
                W_Addr <= "101" after 2 ns;
                Selector_Sel <= '1';
                ALU_sel <= '1';
                Next_State <= Compute2_State after 11 ns;
            when Compute2_State =>
                R_Addr1 <= "001" after 2 ns;
			    R_Addr2 <= "010" after 2 ns;
                W_Addr <= "110" after 2 ns;
                Selector_Sel <= '1';
                ALU_sel <= '1';
                Next_State <= Compute3_State after 11 ns;
            when Compute3_State =>
                R_Addr1 <= "110" after 2 ns;
			    R_Addr2 <= "010" after 2 ns;
                W_Addr <= "110" after 2 ns;
                Selector_Sel <= '1';
                ALU_sel <= '1';
                Next_State <= Compute4_State after 11 ns;
            when Compute4_State =>
                R_Addr1 <= "000" after 2 ns;
			    R_Addr2 <= "110" after 2 ns;
                W_Addr <= "110" after 2 ns;
                Selector_Sel <= '0';
                ALU_sel <= '0';
                Next_State <= Compute5_State after 11 ns;
            when Compute5_State =>
                R_Addr1 <= "110" after 2 ns;
			    R_Addr2 <= "101" after 2 ns;
                W_Addr <= "110" after 2 ns;
                Selector_Sel <= '1';
                ALU_sel <= '0';
                Next_State <= Compute6_State after 11 ns;
            when Compute6_State =>
                R_Addr1 <= "110" after 2 ns;
			    R_Addr2 <= "100" after 2 ns;
                W_Addr <= "110" after 2 ns;
                Selector_Sel <= '1';
                ALU_sel <= '0';
                OutReg_Ld <= '1';
                Next_State <= End_State after 11 ns;
            when End_State =>
                W_en <= '0';
                R_Addr1 <= "000" after 2 ns;
			    R_Addr2 <= "000" after 2 ns;
                W_Addr <= "000" after 2 ns;
                Selector_Sel <= '0';
                ALU_sel <= '0';
                Done <= '1';
                Oe <= '1';
                Next_State <= Start_State after 11 ns;
        end case;
        if (Clk = '1' and Clk'event) then
            if (Rst = '1') then
                Current_State <= Start_State after 4 ns;
            else
                Current_State <= Next_State after 4 ns;
            end if;
        end if; 
    end process;
END Beh;


---------- Locator (with clock cycle =  37 NS )----------
--         INDICATE YOUR CLOCK CYCLE TIME ABOVE      ----

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

entity Locator_struct is
    Port ( Clk : in  STD_LOGIC;
		   Start : in  STD_LOGIC;
           Rst : in  STD_LOGIC;
           Loc : out  STD_LOGIC_VECTOR (15 downto 0);
           Done : out  STD_LOGIC);
end Locator_struct;

architecture Struct of Locator_struct is
    
    COMPONENT RegFile IS
        PORT (  R_Addr1, R_Addr2, W_Addr: IN std_logic_vector(2 DOWNTO 0);
                R_en, W_en: IN std_logic;
                Reg_Data1: OUT std_logic_vector(15 DOWNTO 0); 
				Reg_Data2: OUT std_logic_vector(15 DOWNTO 0);
                W_Data: IN std_logic_vector(15 DOWNTO 0); 
                Clk, Rst: IN std_logic );
    END COMPONENT;
    
    COMPONENT ALU IS
        PORT (Sel: IN std_logic;
                A: IN STD_LOGIC_VECTOR(15 DOWNTO 0);
                B: IN STD_LOGIC_VECTOR(15 DOWNTO 0);
                ALU_Out: OUT STD_LOGIC_VECTOR (15 DOWNTO 0) );
    END COMPONENT;

    COMPONENT Shifter IS
         PORT (I: IN std_logic_vector(15 DOWNTO 0);
               Q: OUT std_logic_vector(15 DOWNTO 0);
               sel: IN std_logic );
    END COMPONENT;

    COMPONENT Selector IS
        PORT (sel: IN std_logic;
              x,y: IN std_logic_vector(15 DOWNTO 0);
              f: OUT std_logic_vector(15 DOWNTO 0) );
    END COMPONENT;
   
    COMPONENT Reg IS
        PORT (I: IN std_logic_vector(15 DOWNTO 0);
              Q: OUT std_logic_vector(15 DOWNTO 0);
              Ld: IN std_logic; 
              Clk, Rst: IN std_logic );
    END COMPONENT;
    
    COMPONENT ThreeStateBuff IS
        PORT (Control_Input: IN std_logic;
              Data_Input: IN std_logic_vector(15 DOWNTO 0);
              Output: OUT std_logic_vector(15 DOWNTO 0) );
    END COMPONENT;
    
    COMPONENT Controller IS
       PORT(R_en: OUT std_logic;
            W_en: OUT std_logic;
            R_Addr1: OUT std_logic_vector(2 DOWNTO 0);
				R_Addr2: OUT std_logic_vector(2 DOWNTO 0);
            W_Addr: OUT std_logic_vector(2 DOWNTO 0);
            Shifter_sel: OUT std_logic;
            Selector_sel: OUT std_logic;
            ALU_sel : OUT std_logic;
            OutReg_Ld: OUT std_logic;
            Oe: OUT std_logic;
            Done: OUT std_logic;
            Start, Clk, Rst: IN std_logic); 
     END COMPONENT;

-- do not modify any code above this line
-- add signals needed below. hint: name them something you can keep track of while debugging/testing
-- add your code starting here
    SIGNAL R_Addr1_S, R_Addr2_S, W_Addr_S: std_logic_vector(2 DOWNTO 0);
    SIGNAL Reg_Data1_S, Reg_Data2_S: std_logic_vector(15 DOWNTO 0);
    SIGNAL OutReg_Ld_S: std_logic;
    SIGNAL Final_result_S: std_logic_vector(15 DOWNTO 0);
    SIGNAL ALU_result_S, Shifter_result_S, Selector_result_S: std_logic_vector(15 DOWNTO 0);
    SIGNAL Oe_S: std_logic;
    SIGNAL Shifter_sel_S, Selector_sel_S, ALU_sel_S: std_logic;
    SIGNAL R_en_S, W_en_S: std_logic;
BEGIN
    Controller_1: Controller PORT MAP (R_en => R_en_S, W_en => W_en_S, R_Addr1 => R_Addr1_S, R_Addr2 => R_Addr2_S, W_Addr => W_Addr_S, Shifter_sel => Shifter_sel_S, Selector_sel => Selector_sel_S, ALU_sel => ALU_sel_S, OutReg_Ld => OutReg_Ld_S, Oe => Oe_S, Done => Done, Start => Start, Clk => Clk, Rst => Rst);
    RegFile_1: RegFile PORT MAP (R_Addr1 => R_Addr1_S, R_Addr2 => R_Addr2_S, W_Addr => W_Addr_S, R_en => R_en_S, W_en => W_en_S, Reg_Data1 => Reg_Data1_S, Reg_Data2 => Reg_Data2_S, W_Data => Selector_result_S, Clk => Clk, Rst => Rst);
    ALU_1: ALU PORT MAP (Sel => ALU_sel_S, A => Reg_Data2_S, B => Reg_Data1_S, ALU_Out => ALU_result_S);
    Shifter_1: Shifter PORT MAP (I => Reg_Data2_S, Q => Shifter_result_S, sel => Shifter_sel_S);
    Selector_1: Selector PORT MAP (sel => Selector_sel_S, x => Shifter_result_S, y => ALU_result_S, f => Selector_result_S);
    Reg_1: Reg PORT MAP (I => Selector_result_S, Q => Final_result_S, Ld => OutReg_Ld_S, Clk => Clk, Rst => Rst);
    ThreeStateBuff_1: ThreeStateBuff PORT MAP (Control_Input => Oe_S, Data_Input => Final_result_S, Output => Loc);


end Struct;

