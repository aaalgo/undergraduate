library ieee;
use ieee.std_logic_1164.all;

entity acc is
port (din : in std_logic_vector(7 downto 0);
	clk: in std_logic;
	write : in std_logic;
	zero : out std_logic;
	dout: out std_logic_vector(7 downto 0));
end entity acc;

architecture one of acc is
signal data : std_logic_vector(7 downto 0);
begin
	dout <= data;
	zero <= not (data(7) or data(6) or data(5) or data(4) or data(3) or data(2) or data(1) or data(0));
	process(clk, din)
	begin
		if clk'event and clk = '1' then
			if write = '1' then
				data <= din;
			end if;
		end if;
	end process;
end architecture one;
