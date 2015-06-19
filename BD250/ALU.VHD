library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity alu is
port (din1, din2 : in std_logic_vector(7 downto 0);
		cin  : in std_logic;
		oin  : in std_logic;
		func : in std_logic_vector(3 downto 0);
		dout : out std_logic_vector(7 downto 0);
		cout : out std_logic;
		over : out std_logic);
end alu;

architecture rtl of alu is
signal sum: std_logic_vector(8 downto 0);
signal shiftl: std_logic_vector(7 downto 0);
signal shiftr: std_logic_vector(7 downto 0);
signal din2_t,dout_t : std_logic_vector(7 downto 0);
signal cin_t : std_logic;
signal cin_s : std_logic;
begin
	shiftl <= din1(6 downto 0) & cin_s;
	shiftr <= cin_s & din1(7 downto 1);
	dout_t <= sum(7 downto 0) when func(3 downto 2)="00" else
			not din1 when func(3 downto 1)="100" else
			din1 and din2 when func(3 downto 1)="010" else
			din1 or din2 when func(3 downto 1)="011" else
			shiftl when func(3 downto 1)="101" else shiftr;
	cin_s <= '0' when func(0) = '0' else cin;
	dout <= dout_t;
	din2_t <= din2 when func(1)='0' else not din2;
	cin_t <= cin_s when func(1)='0' else not cin_s;
	sum <= din1+din2_t+cin_t;
	cout <= sum(8) when func(3 downto 2) = "00" else
			din1(7) when func(3 downto 1) = "101" else
			din1(0) when func(3 downto 1) = "110" else cin;
	over <=	sum(8) xor din1(7) xor din2_t(7) xor sum(7) when func(2 downto 1) = "00" else oin;
end rtl;
