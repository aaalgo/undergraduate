library ieee;
use ieee.std_logic_1164.all;

entity cpu is
	port (	seg7	: out std_logic_vector (7 downto 0);
			segsel	: out std_logic_vector (5 downto 0);
			light	: out std_logic_vector(15 downto 0);
			dip		: in std_logic_vector(23 downto 0);
			clk		: in std_logic;
			reset	: in std_logic);
end entity cpu;

architecture one of cpu is
component acc is
	port (	din		: in std_logic_vector(7 downto 0);
			clk		: in std_logic;
			write	: in std_logic;
			zero	: out std_logic;
			dout	: out std_logic_vector(7 downto 0));
end component acc;

component alu is
	port (	din1	: in std_logic_vector(7 downto 0);
			din2	: in std_logic_vector(7 downto 0);
			cin		: in std_logic;
			oin		: in std_logic;
			func	: in std_logic_vector(3 downto 0);
			dout	: out std_logic_vector(7 downto 0);
			cout	: out std_logic;
			over	: out std_logic);
end component alu;

component pc is
	generic(width	: integer := 10);
	port (	clk		: in std_logic;
			reset	: in std_logic;
			setdata	: in std_logic_vector (width -1 downto 0);
			set		: in std_logic;
			data	: out std_logic_vector (width-1 downto 0));
end component pc;

component ram is
	port (	addr	: in std_logic_vector (6 downto 0);
			clk		:  in std_logic;
			write 	:  in std_logic;
			din		: in std_logic_vector (7 downto 0);
			dout	: out std_logic_vector (7 downto 0));
end component ram;

component rom is
	port (	addr	: in std_logic_vector(9 downto 0);
			data	: out std_logic_vector (15 downto 0));
end component rom;

component io is
	port (	dip		: in std_logic_vector(23 downto 0);
			seg7	: out std_logic_vector(7 downto 0);
			segsel	: out std_logic_vector(5 downto 0);
			light	: out std_logic_vector(15 downto 0);
			clk		: in std_logic;
			c_in	: in std_logic;
			c_out	: out std_logic;
			o_in	: in std_logic;
			o_out	: out std_logic;
			write	: in std_logic;
			addr	: in std_logic_vector(6 downto 0);
			din		: in std_logic_vector(7 downto 0);
			dout	: out std_logic_vector(7 downto 0));
end component io;

component dec is
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
end component dec;

constant PC_WIDTH	: integer := 10;
constant INST_WIDTH	: integer := 16;
constant ADDR_WIDTH	: integer := 8;
constant RAM_SIZE	: integer := 128;

signal inst_addr	: std_logic_vector(PC_WIDTH-1 downto 0);
signal inst_addr_new: std_logic_vector(PC_WIDTH-1 downto 0);
signal dec_pc_new : std_logic_vector(PC_WIDTH-1 downto 0);
signal reset_pc		: std_logic;
signal acc_pc		: std_logic;

signal instruct		: std_logic_vector(INST_WIDTH-1 downto 0);

signal load_const	: std_logic;
signal load			: std_logic;
signal store		: std_logic;
signal ram_write	: std_logic;
signal io_write		: std_logic;
signal mem_in		: std_logic_vector(7 downto 0);
signal mem_out		: std_logic_vector(7 downto 0);
signal ram_out		: std_logic_vector(7 downto 0);
signal io_out		: std_logic_vector(7 downto 0);
signal addr			: std_logic_vector(7 downto 0);
signal dec_addr	: std_logic_vector(7 downto 0);
signal acc_addr		: std_logic;

signal flag_carry_n : std_logic;
signal flag_carry	: std_logic;
signal flag_over_n	: std_logic;
signal flag_over	: std_logic;

signal const		: std_logic_vector(7 downto 0);
signal flag_zero	: std_logic;

signal acc_in		: std_logic_vector(7 downto 0);
signal acc_out		: std_logic_vector(7 downto 0);
signal acc_write	: std_logic;

signal alu_out		: std_logic_vector(7 downto 0);
signal alu_in2		: std_logic_vector(7 downto 0);
signal alu_func		: std_logic_vector(3 downto 0);
signal instance		: std_logic;

signal jmp			: std_logic;
signal jmpz			: std_logic;
begin
	inst_addr_new <= dec_pc_new when acc_pc = '0' else dec_pc_new(9 downto 8) & acc_out;
	reset_pc <= '1' when  (jmp = '1') or (jmpz = '1' and flag_zero = '1') else '0';

M0: pc	generic	map (	width => PC_WIDTH)
		port	map (	clk => clk,
						reset => reset,
						setdata => inst_addr_new,
						set => reset_pc,
						data => inst_addr);

	addr <= dec_addr when acc_addr = '0' else acc_out;
	ram_write <= store and not addr(7);
	io_write <= store and addr(7);
	mem_out <= ram_out when addr(7) = '0' else io_out;
	mem_in <= acc_out;
M1: ram	port	map (	addr => addr(6 downto 0),
						clk => clk,
						write => ram_write,
						din => mem_in,
						dout => ram_out);
M2: io	port	map (	dip => dip,
						seg7 => seg7,
						segsel => segsel,
						light => light,
						clk => clk,
						c_in => flag_carry_n,
						c_out => flag_carry,
						o_in => flag_over_n,
						o_out => flag_over,
						write => io_write,
						addr => addr(6 downto 0),
						din => mem_in,
						dout => io_out);

	acc_in <= mem_out when load = '1' and load_const = '0' else
				const when load = '1' and load_const = '1' else alu_out;
M3: acc port	map (	din => acc_in,
						clk => clk,
						write => acc_write,
						zero => flag_zero,
						dout => acc_out);

	alu_in2 <= mem_out when instance = '0' else const;
M4: alu port	map (	din1 => acc_out,
						din2 => alu_in2,
						cin => flag_carry,
						oin => flag_over,
						func => alu_func,
						dout => alu_out,
						cout => flag_carry_n,
						over => flag_over_n);

M5:	rom	port	map (	addr => inst_addr,
						data => instruct);

M6: dec port	map (	inst => instruct,
						addr => dec_addr,
						alu_func => alu_func, 
						new_pc => dec_pc_new,
						dec_const => const,
						jmp => jmp,
						jmpz => jmpz,
						load => load,
						store => store,
						acc_pc => acc_pc,
						acc_addr => acc_addr,
						acc_write => acc_write,
						load_const => load_const,
						instance => instance);
end architecture;

