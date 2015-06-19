A = 0
B = 1
C = 2
	NOP		; XXX
F:	CONST	1	;
	STORE	A	;
	ADD	A	;
	STORE	B	;
	ADD	B	;
	ADDI	9	;
LOOP:	JMP LOOP	;
	CONST	9	;
	END.
