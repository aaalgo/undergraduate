	A     = 1	;
	CARRY = 0x98	;
START:	CONST	0x80	;
	STORE	A	;
LOOP:	LOAD	A	;
	SHR		;
	STORE	A	;
	LOAD CARRY	;
	JZ   LOOP	;
	CONST START	;
	JACC		;
STOP:	JMP STOP	;
	END.
