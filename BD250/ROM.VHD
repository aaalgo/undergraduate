library ieee;
use ieee.std_logic_1164.all;

entity rom is
port (addr : in std_logic_vector (9 downto 0);
		data : out std_logic_vector (15 downto 0));
end entity rom;

architecture one of rom is
COMPONENT lpm_rom
	GENERIC (LPM_WIDTH: POSITIVE;
		LPM_WIDTHAD: POSITIVE;
		LPM_FILE: STRING;
		LPM_ADDRESS_CONTROL: STRING := "REGISTERED";
		LPM_OUTDATA: STRING := "REGISTERED");
	PORT (address: IN STD_LOGIC_VECTOR(LPM_WIDTHAD-1 DOWNTO 0);
		inclock: IN STD_LOGIC := '0';
		outclock: IN STD_LOGIC := '0';
		memenab: IN STD_LOGIC := '1';
		q: OUT STD_LOGIC_VECTOR(LPM_WIDTH-1 DOWNTO 0));
END COMPONENT;

begin

M0:	lpm_rom generic map (	LPM_WIDTH => 16,
							LPM_WIDTHAD => 8,
							LPM_FILE => "rom.mif",
							LPM_ADDRESS_CONTROL => "UNREGISTERED",
							LPM_OUTDATA => "UNREGISTERED")
			port	map	(	address => addr(7 downto 0),
							q => data);
end architecture one;
