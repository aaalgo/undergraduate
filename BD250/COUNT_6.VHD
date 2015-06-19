LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY count_6 IS
	PORT(clk : IN STD_LOGIC;
		 countout : OUT STD_LOGIC_VECTOR(2 downto 0));
END count_6;

ARCHITECTURE behav OF count_6 IS
BEGIN
	PROCESS(clk)
	VARIABLE count_t : STD_LOGIC_VECTOR(2 downto 0);
	BEGIN
		IF(clk'event AND clk='1') THEN
			IF(count_t="101") THEN
				count_t := "000";
			ELSE
				count_t := count_t+'1';
			END IF;
		END IF;
	countout <= count_t;
	END PROCESS;
END behav;


