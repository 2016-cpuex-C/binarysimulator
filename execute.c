#include "y.tab.h"
#include "global.h"
#include "analyze.c"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>

#define label_cache_size 60

typedef union {
    int32_t i;
    float f;
    uint32_t ui;
} u;


int label_cache[label_cache_size];


void execute( int op[MEM_SIZE][5], int32_t word[MEM_SIZE][MAX_STR], char *option, int wpc)
{
    /*FILE *f;*/

    int32_t reg[32];
    reg[28] = MEM_SIZE / 2;
    float f_reg[32];
    int32_t hi, lo;
    int32_t mem[MEM_SIZE];
    /*int condition_bit = 0;*/
    int break_bit = 0;
    int float_flag = 0;
    int i;
    long int how_many_times_called[MEM_SIZE];
    for (i = 0; i < MEM_SIZE; i++) {
        mem[i] = INT_MAX;  //initialilze all memory to int_max. to detect invalid memory access
        how_many_times_called[i] = 0;
    }

    int pc = 0;

    int op_pc_0;
    int atoi_option = atoi(option);

    while (1){

        op_pc_0 = op[pc][0];
        how_many_times_called[pc] += 1;

        if (atoi_option == pc && option[0] - *"0" < 10 && option[0] - *"0" >= 0) {
            break_bit = 1;
        }
        if (break_bit || op_pc_0 == BREAK) { // This instruction is not in mips!!
            //printf("break\n");
            printf("\n");
            int temp;
            break_bit = 1;
            printf("pc: %d\n", pc + 1);
            printf("reg: ");fflush(stdout);
            printf("\n    zr    at    v0    v1    a0    a1    a2    a3\n");fflush(stdout);
            for (i = 0; i < 8; i++) {
                printf("%6d", reg[i]);fflush(stdout);
            }
            printf("\n    t0    t1    t2    t3    t4    t5    t6    t7\n");fflush(stdout);
            for (i = 8; i < 16; i++) {
                printf("%6d", reg[i]);fflush(stdout);
            }
            printf("\n    s0    s1    s2    s3    s4    s5    s6    s7\n");fflush(stdout);
            for (i = 16; i < 24; i++) {
                printf("%6d", reg[i]);fflush(stdout);
            }
            printf("\n    t8    t9    k0    k1    gp    sp    fp    ra    hi    lo\n");fflush(stdout);
            for (i = 24; i < 32; i++) {
                printf("%6d", reg[i]);fflush(stdout);
            }
            printf("%6d", hi);fflush(stdout);
            printf("%6d", lo);fflush(stdout);
            printf("\n");fflush(stdout);
            if (float_flag != 1) {
                printf("Press f to show floating point registers. Enter to continue");
                temp = getchar();
            }

            if (temp == 102 || float_flag) {
                float_flag = 1;
                int i;
                printf("f_reg: ");fflush(stdout);
                printf("\n");fflush(stdout);
                for (i = 0; i < 8; i++) {
                    if (f_reg[i] == 0) {
                        printf("  %2.2f", 0.0);fflush(stdout);
                    } else {
                        printf("  %2.2f ", f_reg[i]);fflush(stdout);
                    }
                }
                printf("\n");fflush(stdout);
                for (i = 8; i < 16; i++) {
                    if (f_reg[i] == 0) {
                        printf("  %2.2f", 0.0);fflush(stdout);
                    } else {
                        printf("  %2.2f ", f_reg[i]);fflush(stdout);
                    }
                }
                printf("\n");fflush(stdout);
                for (i = 16; i < 24; i++) {
                    if (f_reg[i] == 0) {
                        printf("  %2.2f", 0.0);fflush(stdout);
                    } else {
                        printf("  %2.2f ", f_reg[i]);fflush(stdout);
                    }
                }
                printf("\n");fflush(stdout);
                for (i = 24; i < 32; i++) {
                    if (f_reg[i] == 0) {
                        printf("  %2.2f", 0.0);fflush(stdout);
                    } else {
                        printf("  %2.2f ", f_reg[i]);fflush(stdout);
                    }
                }
                printf("\n");fflush(stdout);
                printf("Press enter to continue.");
                temp = getchar();
            }
            printf("\n");

        }

        //printf("%d ", pc);
        if (op_pc_0 == MOVE) {
            if (break_bit) {
                printf("move ");
                printf("%d\n",MOVE-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]];
        } else if (op_pc_0 == NEG) {
            if (break_bit) {
                printf("neg ");
                printf("%d\n",NEG-257);
            }
            reg[op[pc][1]] = - reg[op[pc][2]];
        } else if (op_pc_0 == ADD) {
            if (break_bit) {
                printf("add ");
                printf("%d\n",ADD-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] + reg[op[pc][3]];
        } else if (op_pc_0 == ADDI) {
            if (break_bit) {
                printf("addi ");
                printf("%d\n",ADDI-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] + op[pc][3];
        } else if (op_pc_0 == SUB) {
            if (break_bit) {
                printf("sub ");
                printf("%d\n",SUB-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] - reg[op[pc][3]];
        } else if (op_pc_0 == SUBI) {
            if (break_bit) {
                printf("subi ");
                printf("%d\n",SUBI-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] - op[pc][3];
        } else if (op_pc_0 == MULT) {
            if (break_bit) {
                printf("mult ");
                printf("%d\n",MULT-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] * reg[op[pc][3]];
        } else if (op_pc_0 == MULTI) {
            if (break_bit) {
                printf("mult ");
                printf("%d\n",MULT-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] * op[pc][3];
        } else if (op_pc_0 == DIV) {
            if (break_bit) {
                printf("div ");
                printf("%d\n",DIV-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] / reg[op[pc][3]];
        } else if (op_pc_0 == DIVI) {
            if (break_bit) {
                printf("divi ");
                printf("%d\n",DIVI-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] / op[pc][3];
        } else if (op_pc_0 == MOVS) {
            if (break_bit) {
                printf("mov.s ");
                printf("%d\n",MOVS-257);
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]];
        } else if (op_pc_0 == NEGS) {
            if (break_bit) {
                printf("neg.s ");
                printf("%d\n",NEGS-257);
            }
            f_reg[op[pc][1]] =  - f_reg[op[pc][2]];
        } else if (op_pc_0 == ADDS) {
            if (break_bit) {
                printf("add.s ");
                printf("%d\n",ADDS-257);
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] + f_reg[op[pc][3]];
        } else if (op_pc_0 == SUBS) {
            if (break_bit) {
                printf("sub.s ");
                printf("%d\n",SUBS-257);
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] - f_reg[op[pc][3]];
        } else if (op_pc_0 == MULS) {
            if (break_bit) {
                printf("mul.s ");
                printf("%d\n",MULS-257);
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] * f_reg[op[pc][3]];
        } else if (op_pc_0 == DIVS) {
            if (break_bit) {
                printf("div.s ");
                printf("%d\n",DIVS-257);
            }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] / f_reg[op[pc][3]];
        } else if (op_pc_0 == SRL) {
            if (break_bit) {
                printf("srl ");
                printf("%d\n",SRL-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] >> op[pc][3];
        } else if (op_pc_0 == SLL) {
            if (break_bit) {
                printf("sll ");
                printf("%d\n",SLL-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] << op[pc][3];
        } else if (op_pc_0 == LI) {
            if (break_bit) {
                printf("li ");
                printf("%d\n",LI-257);
            }
            reg[op[pc][1]] = op[pc][2];
        } else if (op_pc_0 == LA) {
            if (break_bit) {
                printf("la ");
                printf("%d\n",LA-257);
            }
            reg[op[pc][1]] = op[pc][2];
        } else if (op_pc_0 == LWL) {
            if (break_bit) {
                printf("lwl ");
                printf("%d\n",LWL-257);
            }
            reg[op[pc][1]] = word[op[pc][2]][0];
        } else if (op_pc_0 == LWR) {
            if (break_bit) {
                printf("lwr ");
                printf("%d\n",LWR-257);
            }
            assert (reg[op[pc][2]] + op[pc][3] < MEM_SIZE);
            reg[op[pc][1]] = mem[reg[op[pc][2]] + op[pc][3]];
        } else if (op_pc_0 == LSL) {
            if (break_bit) {
                printf("l.sl ");
                printf("%d\n",LSL-257);
            }
            u temp;
            temp.i = word[op[pc][2]][0];
            f_reg[op[pc][1]] = temp.f;
        } else if (op_pc_0 == LSR) {
            if (break_bit) {
                printf("l.sr ");
                printf("%d\n",LSR-257);
            }
            u temp;
            assert (reg[op[pc][2]] + op[pc][3] < MEM_SIZE);
            temp.i = mem[reg[op[pc][2]] + op[pc][3]];
            f_reg[op[pc][1]] = temp.f;
        } else if (op_pc_0 == SW) {
            if (break_bit) {
                printf("sw ");
                printf("%d\n",SW-257);
            }
            assert (reg[op[pc][2]] + op[pc][3] < MEM_SIZE);
            mem[reg[op[pc][2]] + op[pc][3]] = reg[op[pc][1]];
        } else if (op_pc_0 == SS) {
            if (break_bit) {
                printf("s.s ");
                printf("%d\n",SS-257);
            }
            u temp;
            temp.f = f_reg[op[pc][1]];
            assert (reg[op[pc][2]] + op[pc][3] < MEM_SIZE);
            mem[(reg[op[pc][2]] + op[pc][3])] = temp.i;
        } else if (op_pc_0 == BEQ) {
            if (break_bit) {
                printf("beq ");
                printf("%d\n",BEQ-257);
            }
            if(reg[op[pc][1]] == reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (op_pc_0 == BNE) {
            if (break_bit) {
                printf("bne ");
                printf("%d\n",BNE-257);
            }
            //if (reg[op[pc][1]] == reg[op[pc][2]]) printf("%d\n", reg[op[pc][1]]);
            if(reg[op[pc][1]] != reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (op_pc_0 == BLT) {
            if (break_bit) {
                printf("blt ");
                printf("%d\n",BLT-257);
            }
            if(reg[op[pc][1]] < reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (op_pc_0 == BGT) {
            if (break_bit) {
                printf("bgt ");
                printf("%d\n",BGT-257);
            }
            if(reg[op[pc][1]] > reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (op_pc_0 == CEQS) {
            if (break_bit) {
                printf("c.eq.s ");
                printf("%d\n",CEQS-257);
            }
            if (f_reg[op[pc][1]] == f_reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (op_pc_0 == CLES) {
            if (break_bit) {
                printf("c.le.s ");
                printf("%d\n",CLES-257);
            }
            if (f_reg[op[pc][1]] <= f_reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (op_pc_0 == CLTS) {
            if (break_bit) {
                printf("c.lt.s ");
                printf("%d\n",CLTS-257);
            }
            if (f_reg[op[pc][1]] < f_reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (op_pc_0 == J) {
            if (break_bit) {
                printf("j ");
                printf("%d\n",J-257);
            }
            pc = op[pc][1];
            continue;
        } else if (op_pc_0 == JR) {
            if (break_bit) {
                printf("jr ");
                printf("%d\n",JR-257);
            }
            pc = reg[op[pc][1]];
            continue;
        } else if (op_pc_0 == JAL) {
            if (break_bit) {
                printf("jal ");
                printf("%d\n",JAL-257);
            }
            reg[31] = pc + 1;
            pc = op[pc][1];
            continue;
        } else if (op_pc_0 == JALR) {
            if (break_bit) {
                printf("jalr ");
                printf("%d\n",JALR-257);
            }
            reg[31] = pc + 1;
            pc = reg[op[pc][1]];
            continue;
        } else if (op_pc_0 == PRINTI) {
            if (break_bit) {
                printf("print_i ");
                printf("%d\n",PRINTI-257);
            }
            printf("%d", reg[op[pc][1]]);
        } else if (op_pc_0 == PRINTF) {
            if (break_bit) {
                printf("print_f ");
                printf("%d\n",PRINTF-257);
            }
            printf("%f", f_reg[op[pc][1]]);
        } else if (op_pc_0 == PRINTC) {
            if (break_bit) {
                printf("print_c ");
                printf("%d\n",PRINTC-257);
            }
            printf("%c", reg[op[pc][1]]);
        } else if (op_pc_0 == READI) {
            if (break_bit) {
                printf("read_i ");
                printf("%d\n",READI-257);
            }
            if (scanf("%d", &reg[op[pc][1]]) != 1) {
                fprintf(stderr, "readi\n");
                exit(-1);
            }
        } else if (op_pc_0 == READF) {
            if (break_bit) {
                printf("read_f ");
                printf("%d\n",READF-257);
            }
            if (scanf("%f", &f_reg[op[pc][1]]) != 1) {
                fprintf(stderr, "readf\n");
                exit(-1);
            }
        } else if (op_pc_0 == BEQI) {
            if (break_bit) {
                printf("beqi\n");
                printf("%d\n",BEQI-257);
            }
            if (reg[op[pc][1]] == op[pc][2]) { 
                pc = op[pc][3];
                continue;
            }
        } else if (op_pc_0 == AND) {
            if (break_bit) {
                printf("and\n");
                printf("%d\n",AND-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] & reg[op[pc][3]];
        } else if (op_pc_0 == OR) {
            if (break_bit) {
                printf("or\n");
                printf("%d\n",OR-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] | reg[op[pc][3]];
        } else if (op_pc_0 == XOR) {
            if (break_bit) {
                printf("xor\n");
                printf("%d\n",XOR-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] ^ reg[op[pc][3]];
        } else if (op_pc_0 == ANDI) {
            if (break_bit) {
                printf("andi\n");
                printf("%d\n",ANDI-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] & op[pc][3];
        } else if (op_pc_0 == ORI) {
            if (break_bit) {
                printf("ori\n");
                printf("%d\n",ORI-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] | op[pc][3];
        } else if (op_pc_0 == XORI) {
            if (break_bit) {
                printf("xori\n");
                printf("%d\n",XORI-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] ^ op[pc][3];
        } else if (op_pc_0 == EXIT) {
            if (break_bit) {
                printf("exit\n");
                printf("%d\n",EXIT-257);
            }
            break;
        } else if (op_pc_0 == SWAP) {
            if (break_bit) {
                printf("swap\n");
                printf("%d\n",SWAP-257);
            }
            int temp2 = reg[op[pc][1]];
            f_reg[op[pc][1]] = reg[op[pc][2]];
            f_reg[op[pc][2]] = temp2;
        } else if (op_pc_0 == SWAPS) {
            if (break_bit) {
                printf("swap.s\n");
                printf("%d\n",SWAPS-257);
            }
            float temp2 = reg[op[pc][1]];
            reg[op[pc][1]] = reg[op[pc][2]];
            reg[op[pc][2]] = temp2;
        } else if (op_pc_0 == SELECT) {
            if (break_bit) {
                printf("select\n");
                printf("%d\n",SELECT-257);
            }
            reg[op[pc][1]] = reg[op[pc][2]] ? reg[op[pc][3]] : reg[op[pc][4]];
        } else if (op_pc_0 == SELECTS) {
            if (break_bit) {
                printf("select.s\n");
                printf("%d\n",SELECTS-257);
            }
            f_reg[op[pc][1]] = reg[op[pc][2]] ? f_reg[op[pc][3]] : f_reg[op[pc][4]];
        } else if (op_pc_0 == CMP) {
            if (break_bit) {
                printf("cmp\n");
                printf("%d\n",CMP-257);
            }
            if (op[pc][1] == 0) {
                reg[op[pc][2]] = (reg[op[pc][3]] == reg[op[pc][4]]); 
            } else if (op[pc][1] == 1) {
                reg[op[pc][2]] = (reg[op[pc][3]] != reg[op[pc][4]]); 
            } else if (op[pc][1] == 2) {
                reg[op[pc][2]] = (reg[op[pc][3]] <= reg[op[pc][4]]); 
            } else if (op[pc][1] == 3) {
                reg[op[pc][2]] = (reg[op[pc][3]] >= reg[op[pc][4]]); 
            } else if (op[pc][1] == 4) {
                reg[op[pc][2]] = (reg[op[pc][3]] < reg[op[pc][4]]); 
            } else if (op[pc][1] == 5) {
                reg[op[pc][2]] = (reg[op[pc][3]] > reg[op[pc][4]]); 
            }
        } else if (op_pc_0 == CMPI) {
            if (break_bit) {
                printf("cmpi\n");
                printf("%d\n",CMPI-257);
            }
            if (op[pc][1] == 0) {
                reg[op[pc][2]] = (reg[op[pc][3]] == op[pc][4]); 
            } else if (op[pc][1] == 1) {
                reg[op[pc][2]] = (reg[op[pc][3]] != op[pc][4]); 
            } else if (op[pc][1] == 2) {
                reg[op[pc][2]] = (reg[op[pc][3]] <= op[pc][4]); 
            } else if (op[pc][1] == 3) {
                reg[op[pc][2]] = (reg[op[pc][3]] >= op[pc][4]); 
            } else if (op[pc][1] == 4) {
                reg[op[pc][2]] = (reg[op[pc][3]] < op[pc][4]); 
            } else if (op[pc][1] == 5) {
                reg[op[pc][2]] = (reg[op[pc][3]] > op[pc][4]); 
            }
        } else if (op_pc_0 == CMPS) {
            if (break_bit) {
                printf("cmp.s\n");
                printf("%d\n",CMPS-257);
            }
            if (op[pc][1] == 0) {
                reg[op[pc][2]] = (f_reg[op[pc][3]] == f_reg[op[pc][4]]); 
            } else if (op[pc][1] == 1) {
                reg[op[pc][2]] = (f_reg[op[pc][3]] != f_reg[op[pc][4]]); 
            } else if (op[pc][1] == 2) {
                reg[op[pc][2]] = (f_reg[op[pc][3]] <= f_reg[op[pc][4]]); 
            } else if (op[pc][1] == 3) {
                reg[op[pc][2]] = (f_reg[op[pc][3]] >= f_reg[op[pc][4]]); 
            } else if (op[pc][1] == 4) {
                reg[op[pc][2]] = (f_reg[op[pc][3]] < f_reg[op[pc][4]]); 
            } else if (op[pc][1] == 5) {
                reg[op[pc][2]] = (f_reg[op[pc][3]] > f_reg[op[pc][4]]); 
            }
        } else if (op_pc_0 == CVTSW) {
            if (break_bit) {
                printf("cvt.s.w\n");
                printf("%d\n",CVTSW-257);
            }
            u temp2; 
            temp2.ui = reg[op[pc][2]];
            f_reg[op[pc][1]] = temp2.f;
        } else if (op_pc_0 == CVTWS) {
            if (break_bit) {
                printf("cvt.w.s\n");
                printf("%d\n",CVTWS-257);
            }
            u temp2; 
            temp2.f = f_reg[op[pc][2]];
            reg[op[pc][1]] = temp2.ui;

        } else if (op_pc_0 == SIN) {
            if (break_bit) {
                printf("sin ");
                printf("%d\n",SIN-257);
            }
            f_reg[op[pc][1]] = sin(f_reg[op[pc][2]]);
        } else if (op_pc_0 == COS) {
            if (break_bit) {
                printf("cos ");
                printf("%d\n",COS-257);
            }
            f_reg[op[pc][1]] = cos(f_reg[op[pc][2]]);
        } else if (op_pc_0 == ATAN) {
            if (break_bit) {
                printf("atan ");
                printf("%d\n",ATAN-257);
            }
            f_reg[op[pc][1]] = atan(f_reg[op[pc][2]]);
        } else if (op_pc_0 == FLOOR) {
            if (break_bit) {
                printf("floor ");
                printf("%d\n",FLOOR-257);
            }
            f_reg[op[pc][1]] = floor(f_reg[op[pc][2]]);
        } else if (op_pc_0 == SQRT) {
            if (break_bit) {
                printf("sqrt ");
                printf("%d\n",SQRT-257);
            }
            f_reg[op[pc][1]] = sqrt(f_reg[op[pc][2]]);
        } else if (op_pc_0 == FTOI) {
            if (break_bit) {
                printf("ftoi ");
                printf("%d\n",FTOI-257);
            }
            if (f_reg[op[pc][2]] > 0) {
                reg[op[pc][1]] = floor(f_reg[op[pc][2]]);
            } else {
                reg[op[pc][1]] = ceil(f_reg[op[pc][2]]);
            }
        } else if (op_pc_0 == ITOF) {
            if (break_bit) {
                printf("itof ");
                printf("%d\n",ITOF-257);
            }
            f_reg[op[pc][1]] = (float) reg[op[pc][2]];
        } else if (op_pc_0 == EXIT) {
            if (break_bit) {
                printf("exit ");
                printf("%d\n",EXIT-257);
            }
            break;
        }

        pc += 1;

    }


    analyze_how_many_times_called(op, how_many_times_called);

    return;

}

