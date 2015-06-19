library ieee;
use ieee.std_logic_1164.all;

entity io is
	port (	dip : in std_logic_vector(23 downto 0);--000-00,000-01,000-10
			seg7: out std_logic_vector(7 downto 0);
			segsel: out std_logic_vector(5 downto 0);
			--dispdata-001000,001001,001010,001011,001100,001101, 001110
			light: out std_logic_vector(15 downto 0);--010--0,010--1
			clk : in std_logic;
			c_in : in std_logic;
			c_out: out std_logic;--100---
			o_in : in std_logic;
			o_out : out std_logic;--101---
			write : in std_logic;
			addr : in std_logic_vector(6 downto 0);
			din	 : in std_logic_vector(7 downto 0);
			dout : out std_logic_vector(7 downto 0));
end entity io;

architecture one of io is
component scan_disp
port(datain : IN STD_LOGIC_VECTOR(53 downto 0);
	 translate : IN STD_LOGIC;
	 scan_clk : IN STD_LOGIC;
	 sel : OUT STD_LOGIC_VECTOR(5 downto 0);
	 dataout : OUT STD_LOGIC_VECTOR(7 downto 0));
end component scan_disp;

signal dispdata : std_logic_vector(55 downto 0);
signal lightdata : std_logic_vector(15 downto 0);

signal dip_out : std_logic_vector(7 downto 0);
signal disp_out : std_logic_vector(7 downto 0);
signal light_out: std_logic_vector(15 downto 0);
signal c_data, o_data : std_logic;
signal translate : std_logic;
begin
	with addr(2 downto 0) select
	dip_out <=	dip(23 downto 16) when "000",
				dip(15 downto 8) when "001",
				dip(7 downto 0) when others;
	with addr(2 downto 0) select
	disp_out <= dispdata(47 downto 40) when "101",
				dispdata(39 downto 32) when "100",
				dispdata(31 downto 24) when "011",
				dispdata(23 downto 16) when "010",
				dispdata(15 downto 8) when "001",
				dispdata(7 downto 0) when "000",
				dispdata(55 downto 48) when others;

	with addr(1) select
	light_out <= 	lightdata(15 downto 8) when '0',
					lightdata(7 downto 0) when others;
	
	with addr(5 downto 3) select
	dout <= dip_out when "000",
			disp_out when "001",
			light_out when "010",
			"0000000" & c_data when "011",
			"0000000" & o_data when "100",
			"0000000" & translate when "101",
			"00000000" when others;

	light <= lightdata;
	c_out <= c_data;
	o_out <= o_data;
	process(clk)
		begin
			if rising_edge(clk) then
				c_data <= c_in;
				o_data <= o_in;
				if write='1' then
					case addr(5 downto 0) is
						when "001101" => dispdata(47 downto 40) <= din;
						when "001100" => dispdata(39 downto 32) <= din;
						when "001011" => dispdata(31 downto 24) <= din;
						when "001010" => dispdata(23 downto 16) <= din;
						when "001001" => dispdata(15 downto 8) <= din;
						when "001000" => dispdata(7 downto 0) <= din;
						when "001110" => dispdata(55 downto 48) <= din;
						when "010000" => lightdata(15 downto 8) <= din;
						when "010001" => lightdata(7 downto 0) <= din;
						when "101000" => translate <= din(0);
						when others => NULL;
					end case;
				end if;
			end if;
		end process;
display:scan_disp PORT MAP(dispdata(53 downto 0), translate, clk,segsel,seg7);
end one;
