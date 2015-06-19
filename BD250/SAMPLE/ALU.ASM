	A1 = 0		;
	A2 = 1		;
	B1 = 2		;
	B2 = 3		;
	C1 = 4		;
	C2 = 5		;
	D1 = 6		;
	D2 = 7		;
	CARRY = 0x98	;

	CONST 0x10	;
	STORE A1	;
	CONST 0xE0	;
	STORE A2	;
	CONST 0x3F	;
	STORE B1	;
	CONST 0x4C	;
	STORE B2	;
	LOAD  A2	;
	ADD   B2	;
	STORE C2	;
	LOAD  A1	;
	ADDC  B1	;
	STORE C1	;
	LOAD  CARRY	;
	LOAD  C2	;
	LOAD  C1	;
LOOP:	JMP   LOOP	;
	END.
	
