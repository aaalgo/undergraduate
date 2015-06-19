LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY scan_disp IS
	PORT(datain : IN STD_LOGIC_VECTOR(53 downto 0);
		 translate : IN STD_LOGIC;
		 scan_clk : IN STD_LOGIC;
		 sel : OUT STD_LOGIC_VECTOR(5 downto 0);
		 dataout : OUT STD_LOGIC_VECTOR(7 downto 0));
END scan_disp;

ARCHITECTURE rtl OF scan_disp IS
COMPONENT yima_7seg
	PORT(datain : IN STD_LOGIC_VECTOR(3 downto 0);
		 show : OUT STD_LOGIC_VECTOR(7 downto 1));
END COMPONENT;

COMPONENT count_6
	PORT(clk : IN STD_LOGIC;
		 countout : OUT STD_LOGIC_VECTOR(2 downto 0));
END COMPONENT;

SIGNAL count : STD_LOGIC_VECTOR(2 downto 0);
SIGNAL data : STD_LOGIC_VECTOR(3 downto 0);
SIGNAL translated : STD_LOGIC_VECTOR(7 downto 0);
SIGNAL untranslated : STD_LOGIC_VECTOR(7 downto 0);
SIGNAL freq : STD_LOGIC_VECTOR(10 downto 0);
BEGIN
disp : yima_7seg PORT MAP(data, translated(7 downto 1));
count1 : count_6 PORT MAP(freq(10),count);

	WITH count SELECT
		data <= datain(43 downto 40) WHEN "000",
				datain(35 downto 32) WHEN "001",
				datain(27 downto 24) WHEN "010",
				datain(19 downto 16) WHEN "011",
				datain(11 downto 8) WHEN "100",
				datain(3 downto 0) WHEN "101",
				"0000" WHEN OTHERS;
	WITH count SELECT
		translated(0) <= datain(53) WHEN "000",
				datain(52) WHEN "001",
				datain(51) WHEN "010",
				datain(50) WHEN "011",
				datain(49) WHEN "100",
				datain(48) WHEN "101",
				'0' WHEN OTHERS;
	WITH count SELECT
		untranslated <= datain(47 downto 40) WHEN "000",
				datain(39 downto 32) WHEN "001",
				datain(31 downto 24) WHEN "010",
				datain(23 downto 16) WHEN "011",
				datain(15 downto 8) WHEN "100",
				datain(7 downto 0) WHEN "101",
				"00000000" WHEN OTHERS;
	dataout <= translated when translate = '1' else untranslated;
	PROCESS(scan_clk)
	BEGIN
		if scan_clk'event and scan_clk = '1' then
			freq <= freq + '1';
		end if;
	END PROCESS;
	PROCESS(freq(10))
	BEGIN
		sel <= "000000";
		CASE count IS
			WHEN "000" => sel(0) <= '1';
			WHEN "001" => sel(1) <= '1';
			WHEN "010" => sel(2) <= '1';
			WHEN "011" => sel(3) <= '1';
			WHEN "100" => sel(4) <= '1';
			WHEN "101" => sel(5) <= '1';
			WHEN OTHERS => null;
		END CASE;
	END PROCESS;		
END rtl; 
