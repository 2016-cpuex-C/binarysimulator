%{
#include <stdio.h>
#include <string.h>
#include "execute.c"
#include "global.h"

static int op[MEM_SIZE][5]; 
static int32_t word[MEM_SIZE][MAX_STR]; 

int pc = -1;
int wpc = 0;
FILE *f;
int parse_error_flag = 0;
int text_flag = 0;
extern FILE *yyin;
%}

%union {
int num;
char *str; 
} 


%type <num> MOVE
%type <num> NEG
%type <num> ADD
%type <num> ADDI
%type <num> SUB
%type <num> SUBI
%type <num> MULT
%type <num> MULTI
%type <num> DIV
%type <num> DIVI
%type <num> MOVS
%type <num> NEGS
%type <num> ADDS
%type <num> SUBS
%type <num> MULS
%type <num> DIVS
%type <num> SRL
%type <num> SLL
%type <num> LI
%type <num> LA
%type <num> LWL
%type <num> LWR
%type <num> LSL
%type <num> LSR
%type <num> SW
%type <num> SS
%type <num> BEQ
%type <num> BNE
%type <num> BLT
%type <num> BGT
%type <num> CEQS
%type <num> CLES
%type <num> CLTS
%type <num> J
%type <num> JR
%type <num> JAL
%type <num> JALR
%type <num> PRINTI
%type <num> PRINTF
%type <num> PRINTC
%type <num> READI
%type <num> READF
%type <num> SIN
%type <num> COS
%type <num> ATAN
%type <num> FLOOR
%type <num> SQRT
%type <num> FTOI
%type <num> ITOF
%type <num> EXIT
%type <num> PRINTB
%type <num> BREAK



%type <num> ENTER
%type <str> LABEL
%type <str> LINE
%type <num> DATA
%type <num> TEXT
%type <num> GLOBL
%type <num> ASCIIZ WORD
%type <str> HEX
%type <num> IMMEDIATE REGISTER F_REGISTER NOTHING
%start list






%token MOVE
%token NEG
%token ADD
%token ADDI
%token SUB
%token SUBI
%token MULT
%token MULTI
%token DIV
%token DIVI
%token MOVS
%token NEGS
%token ADDS
%token SUBS
%token MULS
%token DIVS
%token SRL
%token SLL
%token LI
%token LA
%token LWL
%token LWR
%token LSL
%token LSR
%token SW
%token SS
%token BEQ
%token BNE
%token BLT
%token BGT
%token CEQS
%token CLES
%token CLTS
%token J
%token JR
%token JAL
%token JALR
%token PRINTI
%token PRINTF
%token PRINTC
%token READI
%token READF
%token SIN
%token COS
%token ATAN
%token FLOOR
%token SQRT
%token FTOI
%token ITOF
%token EXIT
%token PRINTB
%token BREAK


%token ENTER
%token LINE
%token LABEL
%token DATA
%token TEXT
%token GLOBL
%token ASCIIZ WORD
%token HEX
%token IMMEDIATE REGISTER F_REGISTER NOTHING


%% 

list:   
        |
        list stat 
        {
        }
        |
        list error
        {
        }
        ;
stat:    
         LINE {
            if (text_flag == 1 || strcmp("11111111111111111111111111111111\n", $1) == 0) {
                fprintf(f, "%d ", pc);
                text_flag = 1;
                int temp = bin2int($1, 0, 5);
                if (temp == 1) {
                    fprintf(f, " move");
                    op[pc][0] = MOVE; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 2) {
                    fprintf(f, " neg");
                    op[pc][0] = NEG; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 3) {
                    fprintf(f, " add");
                    op[pc][0] = ADD; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 20); 
                } else if (temp == 4) {
                    fprintf(f, " addi");
                    op[pc][0] = ADDI; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    if (bin2int($1, 16, 16) == 1) {
                        op[pc][3] = bin2int($1, 17, 31) - 32768; 
                    } else {
                        op[pc][3] = bin2int($1, 17, 31); 
                    }
                } else if (temp == 5) {
                    fprintf(f, " sub");
                    op[pc][0] = SUB; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 20); 
                } else if (temp == 6) {
                    fprintf(f, " subi");        
                    op[pc][0] = SUBI; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    if (bin2int($1, 16, 16) == 1) {
                        op[pc][3] = bin2int($1, 17, 31) - 32768; 
                    } else {
                        op[pc][3] = bin2int($1, 17, 31); 
                    }
                } else if (temp == 7) {
                    fprintf(f, " mult");        
                    op[pc][0] = MULT; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 20); 
                } else if (temp == 8) {
                    fprintf(f, " multi");        
                    op[pc][0] = MULTI; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    if (bin2int($1, 16, 16) == 1) {
                        op[pc][3] = bin2int($1, 17, 31) - 32768; 
                    } else {
                        op[pc][3] = bin2int($1, 17, 31); 
                    }
                } else if (temp == 9) {
                    fprintf(f, " div");
                    op[pc][0] = DIV; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 20); 
                } else if (temp == 10) {
                    fprintf(f, " divi");        
                    op[pc][0] = DIVI; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    if (bin2int($1, 16, 16) == 1) {
                        op[pc][3] = - bin2int($1, 17, 31); 
                        op[pc][3] = bin2int($1, 17, 31) - 32768; 
                    } else {
                        op[pc][3] = bin2int($1, 17, 31); 
                    }
                } else if (temp == 11) {
                    fprintf(f, " mov.s");        
                    op[pc][0] = MOVS; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 12) {
                    fprintf(f, " neg.s");        
                    op[pc][0] = NEGS; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 13) {
                    fprintf(f, " add.s");        
                    op[pc][0] = ADDS;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 20); 
                } else if (temp == 14) {
                    fprintf(f, " sub.s");        
                    op[pc][0] = SUBS;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 20); 
                } else if (temp == 15) {
                    fprintf(f, " mul.s");        
                    op[pc][0] = MULS;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 20); 
                } else if (temp == 16) {
                    fprintf(f, " div.s");        
                    op[pc][0] = DIVS ;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 20); 
                } else if (temp == 17) {
                    fprintf(f, " srl");
                    op[pc][0] = SRL ;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 18) {
                    fprintf(f, " sll");        
                    op[pc][0] = SLL ;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 19) {
                    fprintf(f, " li");        
                    op[pc][0] = LI ;
                    op[pc][1] = bin2int($1, 6, 10); 
                    if (bin2int($1, 11, 11) == 1) {
                        op[pc][2] = - bin2int($1, 12, 26); 
                        op[pc][2] = bin2int($1, 12, 26) - 32768; 
                    } else {
                        op[pc][2] = bin2int($1, 12, 26); 
                    }
                } else if (temp == 20) {
                    fprintf(f, " la");        
                    op[pc][0] = LA ;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 26); 
                } else if (temp == 21) {
                    fprintf(f, " lwl");        
                    op[pc][0] = LWL;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 26); 
                } else if (temp == 22) {
                    fprintf(f, " lwr");        
                    op[pc][0] = LWR;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 23) {
                    fprintf(f, " l.sl");        
                    op[pc][0] = LSL;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 26); 
                } else if (temp == 24) {
                    fprintf(f, " l.sr");        
                    op[pc][0] = LSR;
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 25) {
                    fprintf(f, " sw");        
                    op[pc][0] = SW; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 26) {
                    fprintf(f, " s.s");        
                    op[pc][0] = SS; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 27) {
                    fprintf(f, " beq");        
                    op[pc][0] = BEQ; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 28) {
                    fprintf(f, " bne");        
                    op[pc][0] = BNE; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 29) {
                    fprintf(f, " blt");        
                    op[pc][0] = BLT; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 30) {
                    fprintf(f, " bgt");        
                    op[pc][0] = BGT; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 31) {
                    fprintf(f, " c.eq.s");        
                    op[pc][0] = CEQS; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 32) {
                    fprintf(f, " c.le.s");        
                    op[pc][0] = CLES; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 33) {
                    fprintf(f, " c.lt.s");
                    op[pc][0] = CLTS; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                    op[pc][3] = bin2int($1, 16, 31); 
                } else if (temp == 34) {
                    fprintf(f, " j");        
                    op[pc][0] = J; 
                    op[pc][1] = bin2int($1, 6, 21); 
                } else if (temp == 35) {
                    fprintf(f, " jr");        
                    op[pc][0] = JR; 
                    op[pc][1] = bin2int($1, 6, 10); 
                } else if (temp == 36) {
                    fprintf(f, " jal");        
                    op[pc][0] = JAL; 
                    op[pc][1] = bin2int($1, 6, 21); 
                } else if (temp == 37) {
                    fprintf(f, " jalr");        
                    op[pc][0] = JALR; 
                    op[pc][1] = bin2int($1, 6, 10); 
                } else if (temp == 38) {
                    fprintf(f, " print_i");        
                    op[pc][0] = PRINTI; 
                    op[pc][1] = bin2int($1, 6, 10); 
                } else if (temp == 39) {
                    fprintf(f, " print_f");        
                    op[pc][0] = PRINTF; 
                    op[pc][1] = bin2int($1, 6, 10); 
                } else if (temp == 40) {
                    fprintf(f, " print_c");        
                    op[pc][0] = PRINTC; 
                    op[pc][1] = bin2int($1, 6, 10); 
                } else if (temp == 41) {
                    fprintf(f, " read_i");        
                    op[pc][0] = READI; 
                    op[pc][1] = bin2int($1, 6, 10); 
                } else if (temp == 42) {
                    fprintf(f, " read_f");        
                    op[pc][0] = READF; 
                    op[pc][1] = bin2int($1, 6, 10); 
                } else if (temp == 43) {
                    fprintf(f, " sin");        
                    op[pc][0] = SIN; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 44) {
                    fprintf(f, " cos");        
                    op[pc][0] = COS; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 45) {
                    fprintf(f, " atan");        
                    op[pc][0] = ATAN; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 46) {
                    fprintf(f, " floor");        
                    op[pc][0] = FLOOR; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 47) {
                    fprintf(f, " sqrt");        
                    op[pc][0] = SQRT; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 48) {
                    fprintf(f, " ftoi");        
                    op[pc][0] = FTOI; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 49) {
                    fprintf(f, " itof");
                    op[pc][0] = ITOF; 
                    op[pc][1] = bin2int($1, 6, 10); 
                    op[pc][2] = bin2int($1, 11, 15); 
                } else if (temp == 50) {
                    fprintf(f, " exit");
                    op[pc][0] = EXIT; 
                } else if (temp == 51) {
                    fprintf(f, " print_b");
                    op[pc][0] = PRINTB; 
                    op[pc][1] = bin2int($1, 6, 10); 
                } else if (temp == 52) {
                    fprintf(f, " break");
                    op[pc][0] = BREAK; 
                }
                pc += 1;
            } else {
                word[wpc][0] = bin2int($1, 0, 31);
                wpc += 1;;
                pc = wpc;
            }

         }
         ;
%%
int32_t bin2int(char bin[32], int a, int b) 
{
    int i, j;
    i = 0;
    j = a;
    while ( j <= b ) {
        i <<= 1;
        if ( bin[j] == '1') i++;
        j++;
        
    }
    return i;
}
main(int argc, char *argv[])
{

    FILE *fh;
    if (argc == 2 && (fh = fopen(argv[1], "r"))) {
        yyin = fh;
    }
    if (argc == 3 && (fh = fopen(argv[2], "r"))) {
        yyin = fh;
    }

    f = fopen("parse.log", "w"); 
    int i;
    for (i = 0; i < MEM_SIZE; i++) {
        word[i][0] = INT_MAX;
    }
    yyparse();
    fclose(f); 

    execute(op, word, argv[1], wpc);
}

yyerror(s)
char *s;
{
    if (parse_error_flag == 0) { 
        printf("parse error. more information in parse.log \n");
        parse_error_flag = 1;
    }
    fprintf(f, "\n%s",s);
}

yywrap()
{
    return(1);
}
