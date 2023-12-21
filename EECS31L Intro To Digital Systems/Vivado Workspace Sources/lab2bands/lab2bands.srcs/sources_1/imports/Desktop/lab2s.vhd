---------------------------------------------------------------------
-- EECS31L Assignment 2
-- FSM Structural Model
----------------------------------------------------------------------
-- Student First Name : Andy
-- Student Last Name : Tran
-- Student ID : 57422363
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Lab2s_FSM IS
     Port (Input : in  STD_LOGIC_VECTOR(2 DOWNTO 0);
           Clk : in  STD_LOGIC;
           Permit : out  STD_LOGIC;
           ReturnChange : out  STD_LOGIC);
END Lab2s_FSM;

ARCHITECTURE Structural OF Lab2s_FSM IS

-- DO NOT modify any signals, ports, or entities above this line
-- Required - there are multiple ways to complete this FSM; however, you will be restricted to the following as a best practice:
-- Create 2 processes (one for updating state status and the other for describing transitions and outputs)
-- For the combinatorial process, use Boolean equations consisting of AND, OR, and NOT gates while expressing the delay in terms of the NAND gates. 
-- Remember to use your calculated delay from the lab handout.
-- For the state register process, use IF statements. Remember to use the calculated delay from the lab handout.
-- Figure out the appropriate sensitivity list of both the processes.
-- add your code here


    Subtype StateType is STD_LOGIC_VECTOR (3 downto 0);    
    Signal Current_State, Next_State: StateType := "0000";

begin
CombLogic: Process (Current_State, Input)
    begin
    
    Next_State(3) <= (((NOT Input(2)) AND (Input(1)) AND (NOT Input(0))) AND ((NOT Current_State(3)) AND (Current_State(2)) AND (Current_State(1)) AND (NOT Current_State(0)))) OR (((Input(2)) AND (NOT Input(1)) AND (NOT Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2)) AND (Current_State(1)) AND (NOT Current_State(0))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(0))))) OR (((Input(2)) AND (Input(1)) AND (Input(0))) AND ((NOT Current_State(3)) AND (NOT Current_State(0)))) AFTER 5.6 NS;
    
    Next_State(2) <= (((NOT Input(2)) AND (NOT Input(1)) AND (NOT Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2)) AND (Current_State(1)) AND (Current_State(0))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(1))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (Current_State(1)) AND (NOT Current_State(0))))) OR (((NOT Input(2)) AND (NOT Input(1)) AND (Input(0))) AND (((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(1))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (Current_State(1)) AND (NOT Current_State(0))))) OR (((NOT Input(2)) AND (Input(1)) AND (NOT Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2)) AND (Current_State(1)) AND (NOT Current_State(0))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(1))))) OR (((Input(2)) AND (NOT Input(1)) AND (NOT Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2)) AND (NOT Current_State(1)) AND (NOT Current_State(0))) OR ((NOT Current_State(3)) AND (NOT Current_State(2)) AND (Current_State(1)) AND (Current_State(0))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(1)) AND (Current_State(0))))) OR (((Input(2)) AND (Input(1)) AND (Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2)) AND (Current_State(1)) AND (Current_State(0))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(1)) AND (Current_State(0))))) AFTER 5.6 NS;
    
    Next_State(1) <= (((NOT Input(2)) AND (NOT Input(1)) AND (NOT Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(1)) AND (Current_State(0))) OR ((NOT Current_State(3)) AND (Current_State(1)) AND (NOT Current_State(0))))) OR (((NOT Input(2)) AND (NOT Input(1)) AND (Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2)) AND (Current_State(1))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (Current_State(1)) AND (NOT Current_State(0))))) OR (((NOT Input(2)) AND (Input(1)) AND (NOT Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(1)) AND (NOT Current_State(0))) OR ((NOT Current_State(3)) AND (NOT Current_State(2)) AND (Current_State(0))))) OR (((Input(2)) AND (NOT Input(1)) AND (NOT Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2)) AND (NOT Current_State(1))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(1)) AND (Current_State(0))))) OR (((Input(2)) AND (Input(1)) AND (Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(1)) AND (Current_State(0))) OR ((NOT Current_State(3)) AND (NOT Current_State(2)) AND (Current_State(1)) AND (NOT Current_State(0))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(0))))) AFTER 5.6 NS;
    
    Next_State(0) <= (((NOT Input(2)) AND (NOT Input(1)) AND (Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(1))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (Current_State(1)) AND (NOT Current_State(0))))) OR (((NOT Input(2)) AND (Input(1)) AND (NOT Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(1)) AND (NOT Current_State(0))) OR ((NOT Current_State(3)) AND (NOT Current_State(2)) AND (Current_State(1))) OR ((NOT Current_State(3)) AND (Current_State(2)) AND (NOT Current_State(1)) AND (Current_State(0))))) OR (((Input(2)) AND (NOT Input(1)) AND (NOT Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2)) AND (NOT Current_State(1)) AND (NOT Current_State(0))))) OR (((Input(2)) AND (Input(1)) AND (Input(0))) AND (((NOT Current_State(3)) AND (NOT Current_State(2)) AND (NOT Current_State(1)) AND (NOT Current_State(0))))) AFTER 5.6 NS;
    
    Permit <= ((NOT Current_State(3)) AND (Current_State(2)) AND (Current_State(1)) AND (Current_State(0))) OR ((Current_State(3) AND (NOT Current_State(2)) AND (NOT Current_State(1)) AND (NOT Current_State(0))));
    
    ReturnChange <= (Current_State(3) AND (NOT Current_State(2)) AND (NOT Current_State(0)));
    
    end process CombLogic;
    
StateRegister: Process (clk)
    begin
        if(Clk = '1' AND Clk'EVENT ) then
            Current_State <= Next_State after 4 ns;
        end if;
    end Process StateRegister;
END Structural;