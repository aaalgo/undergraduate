library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity pc is
generic (width : integer := 10);
port (clk : in std_logic;
		reset : in std_logic;
		setdata : in std_logic_vector (width -1 downto 0);
		set : in std_logic;
		data : out std_logic_vector (width-1 downto 0));
end entity pc;

architecture rtl of pc is
signal data_t : std_logic_vector (width-1 downto 0);
begin
	data <= data_t;
	process(clk, reset)
	begin
		if reset = '1' then
			data_t <= "0000000000";
		elsif rising_edge(clk) then
			if set='1' then
				data_t <= setdata;
			else
				data_t <= data_t + '1';
			end if;
		end if;		
	end process;
end rtl;
