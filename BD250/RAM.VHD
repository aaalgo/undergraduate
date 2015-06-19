library ieee;
use ieee.std_logic_1164.all;
LIBRARY lpm;
USE lpm.lpm_components.ALL;

entity ram is
port (addr : in std_logic_vector (6 downto 0);
		clk :  in std_logic;
		write  :  in std_logic;
		din : in std_logic_vector (7 downto 0);
		dout : out std_logic_vector (7 downto 0));
end entity ram;

architecture one of ram is
begin
	ram:lpm_ram_dq
		GENERIC MAP(lpm_widthad=>7,
					lpm_width=>8,
					LPM_INDATA => "REGISTERED",
					LPM_OUTDATA => "UNREGISTERED",
					LPM_ADDRESS_CONTROL => "UNREGISTERED")
		PORT MAP(data=> din,
				address=>addr,
				inclock => clk,
				we=>write,
				q=>dout);
end architecture one;
