----------------------------------------------------------------------
-- EECS31L Assignment 2
-- FSM Behavioral Model
----------------------------------------------------------------------
-- Student First Name : Andy
-- Student Last Name : Tran
-- Student ID : 57422363
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

entity Lab2b_FSM is
    Port ( Input : in  STD_LOGIC_VECTOR(2 DOWNTO 0);
           Clk : in  STD_LOGIC;
           Permit : out  STD_LOGIC;
           ReturnChange : out  STD_LOGIC);
end Lab2b_FSM;

architecture Behavioral of Lab2b_FSM is

-- DO NOT modify any signals, ports, or entities above this line
-- Recommendation: Create 2 processes (one for updating state status and the other for describing transitions and outputs)
-- Figure out the appropriate sensitivity list of both the processes.
-- Use CASE statements and IF/ELSE/ELSIF statements to describe your processes.
-- add your code here



Signal Needed_Amount: STD_LOGIC_VECTOR(2 DOWNTO 0):="100";
Signal Prev_Input: STD_LOGIC_VECTOR(2 DOWNTO 0):="011";

begin
    process (Clk)
    begin
        if (Clk = '1' and Clk'event) then
            if Input /= Prev_Input then
                if Input = "000" then 
                    Permit <= '0';
                    ReturnChange <= '0';
                    Prev_Input <= Input;
                elsif Input = "111" then 
                    Permit <= '0';
                    if Needed_Amount = "100" then
                        ReturnChange <= '0';
                    else 
                        ReturnChange <= '1';
                    end if;
                    Prev_Input <= Input;
                    Needed_Amount <= "100";
                else 
                    Prev_Input <= Input;
                    Needed_Amount <= Needed_Amount - Input;
                    if Input > Needed_Amount then
                        Permit <= '1';
                        ReturnChange <= '1';
                        Needed_Amount <= "100";
                    elsif Needed_Amount = Input then
                        Permit <= '1';
                        ReturnChange <= '0';
                        Needed_Amount <= "100";
                    else
                       Permit <= '0';
                       ReturnChange <= '0';
                       end if;
                end if;
            else
                if Needed_Amount = "100" then
                    Permit <= '0';
                    ReturnChange <= '0';
                end if;
            end if;
        end if;
    end process;
end Behavioral;