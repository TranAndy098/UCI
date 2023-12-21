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

TYPE StateType IS
    (Input_State, Exact_State, Change_State, Cancel_State, Buffer_State);
    
    Signal Current_State, Next_State: StateType;
    Signal Needed_Amount: STD_LOGIC_VECTOR(2 DOWNTO 0):="100";
    Signal Prev_Input: STD_LOGIC_VECTOR(2 DOWNTO 0):="011";

begin 
CombLogic: Process (Input, Current_State)
    begin
        case Current_State IS
            when Input_State =>
              Permit <= '0';
              ReturnChange <= '0';
              if Input = "111" then
                Prev_Input <= Input;
                Next_State <= Cancel_State;
              elsif Input = "000" then
                Prev_Input <= Input;
                Next_State <= Buffer_State;
              else
                  if Input /= Prev_Input then
                      Needed_Amount <= Needed_Amount - Input;
                      Prev_Input <= Input;
                      if Input > Needed_Amount then
                        Next_State <= Change_State;
                      elsif Needed_Amount = Input then
                        Next_State <= Exact_State;
                      else
                        Next_State <= Input_State;
                      end if;
                  else
                      Next_State <= Input_State;
                  end if;
              end if;
              
            when Change_State =>
              Permit <= '1';
              ReturnChange <= '1';
              Needed_Amount <= "100";
              Next_State <= Input_State;
              
            when Exact_State =>
              Permit <= '1';
              ReturnChange <= '0';
              Needed_Amount <= "100";
              Next_State <= Input_State;
            
            when Cancel_State =>
              Permit <= '0';
              if Needed_Amount = "100" then
                ReturnChange <= '0';
              else 
                ReturnChange <= '1';
              end if;
              Needed_Amount <= "100";
              Next_State <= Input_State;
            
            when Buffer_State =>
              Permit <= '0';
              ReturnChange <= '0';
              Prev_Input <= Input;
              if Input = "000" then
                Next_State <= Input_State;
              else
                if Input = "111" then
                  Next_State <= Cancel_State;
                else
                  Needed_Amount <= Needed_Amount - Input;
                  if Input > Needed_Amount then
                    Next_State <= Change_State;
                  elsif Needed_Amount = Input then
                    Next_State <= Exact_State;
                  else
                    Next_State <= Input_State;
                  end if;
                end if;
              end if;
    end case;
end Process CombLogic;

StateRegister: Process (clk)
 begin
 -- State Register Process
 
   if(Clk = '1' AND Clk'EVENT ) then
    Current_State <= Next_State;
   end if;
 end Process StateRegister;
end Behavioral;