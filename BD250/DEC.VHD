library ieee;
use ieee.std_logic_1164.all;

entity dec is
	port (	inst	: in std_logic_vector(15 downto 0);
			addr	: out std_logic_vector(7 downto 0);
			alu_func: out std_logic_vector(3 downto 0);
			new_pc	: out std_logic_vector(9 downto 0);
			dec_const: out std_logic_vector(7 downto 0);
			jmp		: out std_logic;
			jmpz	: out std_logic;
			load	: out std_logic;
			store	: out std_logic;
			acc_pc	: out std_logic;
			acc_addr: out std_logic;
			acc_write: out std_logic;
			load_const: out std_logic;
			instance : out std_logic);
end entity dec;

architecture one of dec is
signal opcode	: std_logic_vector(1 downto 0);
begin
	opcode <= inst(15 downto 14);

	addr <= inst(7 downto 0);
	alu_func <= inst(12 downto 9) when opcode = "01" else "1110";
	new_pc <= inst(9 downto 0);
	dec_const <= inst(7 downto 0);
	
	jmp <= '1' when opcode = "11" and inst(13) = '0' else '0';
	acc_pc <= inst(12);
	jmpz <= '1' when opcode = "11" and inst(13) = '1' else '0';
	load <= '1' when opcode = "10" and inst(13) = '0' else '0';
	load_const <= inst(12);
	store <= '1'  when opcode = "10" and inst(13) = '1' else '0';
	acc_addr <= '1' when inst(11) = '1' else '0';
	instance <= inst(13);
	acc_write <= '1' when opcode = "01" or (opcode = "10" and inst(13) = '0');
end architecture one;


