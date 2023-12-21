----------------------------------------------------------------------
-- EECS31L Assignment 3
-- Locator Behavioral Model
----------------------------------------------------------------------
-- Student First Name : Andy
-- Student Last Name : Tran
-- Student ID : 57422363
----------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.ALL;


entity Locator_beh  is
    Port ( Clk : in  STD_LOGIC;
		   Start : in  STD_LOGIC;
           Rst : in  STD_LOGIC;
           Loc : out  STD_LOGIC_VECTOR (15 downto 0);
           Done : out  STD_LOGIC);
end Locator_beh;

architecture Behavioral of Locator_beh  is

   TYPE regArray_type IS 
      ARRAY (0 TO 7) OF std_logic_vector(15 DOWNTO 0); 
   SIGNAL regArray : regArray_type :=  (X"0000", X"000B", X"0023", X"0007", X"000A", X"0000", X"0000", X"0000");     
   TYPE Statetype IS (Start_State, Compute_State, End_State);
   SIGNAL Current_State, Next_State: Statetype;
-- do not modify any code above this line
-- additional variables/signals can be declared if needed below
-- add your code starting here

   
begin
    process (CLk, Start, Rst, Current_State)
    variable f_loc: std_logic_vector(31 DOWNTO 0):= X"00000000";
    variable acc_loc: std_logic_vector(31 DOWNTO 0):= X"00000000";
    variable vel_loc: std_logic_vector(31 DOWNTO 0):= X"00000000";
    begin
        case Current_State is
            when Start_State =>
                Loc <= X"0000";
                Done <= '0';
                if Start = '1' then
                    Next_State <= Compute_State;
                elsif Start = '0' then
                    Next_State <= Start_State;
                end if;
            when Compute_State =>
                Loc <= X"0000";
                Done <= '0';
                acc_loc := regArray(2) * regArray(2);
                acc_loc := acc_loc(15 downto 0) * regArray(1);
                acc_loc := X"0000" & '0' & acc_loc(15 downto 1);
                vel_loc := regArray(3) * regArray(2);
                f_loc := vel_loc + acc_loc + regArray(4);
                Next_State <= End_State;
            when End_State =>
                Loc <= f_loc(15 downto 0);
                Done <= '1';
                Next_State <= Start_State;
        end case;
        if (Clk = '1' and Clk'event) then
            if (Rst = '1') then
                Current_State <= Start_State;
            else
                Current_State <= Next_State;
            end if;
        end if; 
    end process;
end Behavioral;

