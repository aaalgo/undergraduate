    LED1 = 0x88;
    LED2 = 0x89;
    LED3 = 0x8A;
    LED4 = 0x8B;
    LED5 = 0x8C;
    LED6 = 0x8D;
    DOTS = 0x8E;
    DIP1 = 0x80;
    DIP2 = 0x81;
    DIP3 = 0x82;
    TRANS = 0xA8;
    LIGHT1 = 0x90;
    LIGHT2 = 0x91;
    A = 20;
    B = 21;
    C = 22;
    D = 23;
    NIL = 127;
    CONST 0xFC;
    STORE 0;
    CONST 0x60;
    STORE 1;
    CONST 0xDA;
    STORE 2;
    CONST 0xF2;
    STORE 3;
    CONST 0x66;
    STORE 4;
    CONST 0xB6;
    STORE 5;
    CONST 0xBE;
    STORE 6;
    CONST 0xE0;
    STORE 7;
    CONST 0xFE;
    STORE 8;
    CONST 0xF6;
    STORE 9;
    CONST 0xEE;
    STORE 10;
    CONST 0x3E;
    STORE 11;
    CONST 0x9C;
    STORE 12;
    CONST 0x7A;
    STORE 13;
    CONST 0x9E;
    STORE 14;
    CONST 0x8E;
    STORE 15;
    
    CONST 1;
    STORE A;
    STORE B;
    CONST 0;
    STORE TRANS;
    LOAD NIL;
LOOP:   LOAD A;
    ANDI 0x0F;
    LACC;
    STORE LED6;
    LOAD A;
    SHR;
    SHR;
    SHR;
    SHR;
    LACC;
    STORE LED5;
    LOAD A;
    STORE LIGHT1;
    LOAD NIL;
WAIT1: LOAD DIP1;
    JZ WAIT1;
WAIT2: LOAD DIP1;
    JZ WAIT3;
    JMP WAIT2;
WAIT3:
    LOAD A;
    ADD  B;
    STORE C;
    LOAD NIL;
    LOAD A;
    STORE B;
    LOAD NIL;
    LOAD C;
    STORE A;
    LOAD NIL;
    JMP LOOP;
END.

