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
#define POP printf_op(op[pc]);


#define CASE    break;case
#define DEFAULT    break;default


#define EQ 0
#define NE 1
#define LE 2
#define GE 3
#define LT 4
#define GT 5
#define OP(x) op[pc][x]


int label_cache[label_cache_size];

void printf_op (int *op) {
    printf("op1 %d ", op[1]);
    printf("op2 %d ", op[2]);
    printf("op3 %d ", op[3]);
    printf("op4 %d ", op[4]);
    printf("           opcode");
}



void execute( int op[MEM_SIZE][5], int32_t word[MEM_SIZE][MAX_STR], char *option, int wpc)
{
    /*FILE *f;*/

    int32_t reg[32];
    reg[28] = MEM_SIZE / 2;
    float f_reg[32];
    int32_t hi, lo;
    int32_t mem[MEM_SIZE];
    /*int condition_bit = 0;*/
    int bb = 0;
    int float_flag = 0;
    int i;
    long int how_many_times_called[MEM_SIZE];
    for (i = 0; i < MEM_SIZE; i++) {
        mem[i] = INT_MAX;  //initialilze all memory to int_max. to detect invalid memory access
        how_many_times_called[i] = 0;
    }

    int pc = 0;

    int o0;
    int atoi_option = atoi(option);

    while (1){

        o0 = op[pc][0];
        how_many_times_called[pc] += 1;

        if (atoi_option == pc && option[0] - *"0" < 10 && option[0] - *"0" >= 0) {
            bb = 1;
        }
        if ((bb || o0 == BREAK) && !(o0 == 0)) { // This instruction is not in mips!!
            //printf("break\n");
            printf("\n");
            int temp;
            bb = 1;
            printf("pc: %d\n", pc);
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
            printf("\n    t8    t9    k0    k1    gp    sp    fp    ra\n");fflush(stdout);
            for (i = 24; i < 32; i++) {
                printf("%6d", reg[i]);fflush(stdout);
            }
            printf("\n");fflush(stdout);
            if (float_flag != 1) {
                printf("Press f to show floating point registers. Enter to continue");
                temp = getchar();
            }

            printf("stack: \n");
            for (i = 0; i < 9; i++) {
                if (mem[i] == INT_MAX) {
                    printf("     -");
                } else{
                     printf("%6d", mem[i]);fflush(stdout);
                }
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
        if (o0 == SQRT) {
            if (bb) { printf("sqrt "); POP printf("%d\n",SQRT-257); }
            f_reg[op[pc][1]] = sqrt(f_reg[op[pc][2]]);
        } else if (o0 == MOVE) {
            if (bb) { printf("move "); POP printf("%d\n",MOVE-257); }
            reg[op[pc][1]] = reg[op[pc][2]];
        } else if (o0 == NEG) {
            if (bb) { printf("neg "); POP printf("%d\n",NEG-257); }
            reg[op[pc][1]] = - reg[op[pc][2]];
        } else if (o0 == ADD) {
            if (bb) { printf("add "); POP printf("%d\n",ADD-257); }
            reg[op[pc][1]] = reg[op[pc][2]] + reg[op[pc][3]];
        } else if (o0 == ADDI) {
            if (bb) { printf("addi "); POP printf("%d\n",ADDI-257); }
            reg[op[pc][1]] = reg[op[pc][2]] + op[pc][3];
        } else if (o0 == SUB) {
            if (bb) { printf("sub "); POP printf("%d\n",SUB-257); }
            reg[op[pc][1]] = reg[op[pc][2]] - reg[op[pc][3]];
        } else if (o0 == SUBI) {
            if (bb) { printf("subi "); POP printf("%d\n",SUBI-257); }
            reg[op[pc][1]] = reg[op[pc][2]] - op[pc][3];
        } else if (o0 == MULT) {
            if (bb) { printf("mult "); POP printf("%d\n",MULT-257); }
            reg[op[pc][1]] = reg[op[pc][2]] * reg[op[pc][3]];
        } else if (o0 == MULTI) {
            if (bb) { printf("mult "); POP printf("%d\n",MULT-257); }
            reg[op[pc][1]] = reg[op[pc][2]] * op[pc][3];
        } else if (o0 == DIV) {
            if (bb) { printf("div "); POP printf("%d\n",DIV-257); }
            reg[op[pc][1]] = reg[op[pc][2]] / reg[op[pc][3]];
        } else if (o0 == DIVI) {
            if (bb) { printf("divi "); POP printf("%d\n",DIVI-257); }
            reg[op[pc][1]] = reg[op[pc][2]] / op[pc][3];
        } else if (o0 == MOVS) {
            if (bb) { printf("mov.s "); POP printf("%d\n",MOVS-257); }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]];
        } else if (o0 == NEGS) {
            if (bb) { printf("neg.s "); POP printf("%d\n",NEGS-257); }
            f_reg[op[pc][1]] =  - f_reg[op[pc][2]];
        } else if (o0 == ADDS) {
            if (bb) { printf("add.s "); POP printf("%d\n",ADDS-257); }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] + f_reg[op[pc][3]];
        } else if (o0 == SUBS) {
            if (bb) { printf("sub.s "); POP printf("%d\n",SUBS-257); }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] - f_reg[op[pc][3]];
        } else if (o0 == MULS) {
            if (bb) { printf("mul.s "); POP printf("%d\n",MULS-257); }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] * f_reg[op[pc][3]];
        } else if (o0 == DIVS) {
            if (bb) { printf("div.s "); POP printf("%d\n",DIVS-257); }
            f_reg[op[pc][1]] =  f_reg[op[pc][2]] / f_reg[op[pc][3]];
        } else if (o0 == SRL) {
            if (bb) { printf("srl "); POP printf("%d\n",SRL-257); }
            unsigned int o2,o3;
            o2 = (unsigned int) reg[op[pc][2]];
            o3 = (unsigned int) reg[op[pc][3]];
            if (o3>=32) {
                reg[op[pc][1]] = 0;
            } else {
                reg[op[pc][1]] = (int) (o2 >> o3);
            }   
        } else if (o0 == SLL) {
            if (bb) { printf("sll "); POP printf("%d\n",SLL-257); }
            unsigned int o2,o3;
            o2 = (unsigned int) reg[op[pc][2]];
            o3 = (unsigned int) reg[op[pc][3]];     
            reg[op[pc][1]] = (int) (o2 << o3);
        } else if (o0 == LI) {
            if (bb) { printf("li "); POP printf("%d\n",LI-257); }
            reg[op[pc][1]] = op[pc][2];
        } else if (o0 == LA) {
            if (bb) { printf("la "); POP printf("%d\n",LA-257); }
            reg[op[pc][1]] = op[pc][2];
        } else if (o0 == LWL) {
            if (bb) { printf("lwl "); POP printf("%d\n",LWL-257); }
            reg[op[pc][1]] = word[op[pc][2]][0];
        } else if (o0 == LWR) {
            if (bb) { printf("lwr "); POP printf("%d\n",LWR-257); }
            assert (reg[op[pc][2]] + op[pc][3] < MEM_SIZE);
            reg[op[pc][1]] = mem[reg[op[pc][2]] + op[pc][3]];
        } else if (o0 == LSL) {
            if (bb) { printf("l.sl "); POP printf("%d\n",LSL-257); }
            u temp;
            temp.i = word[op[pc][2]][0];
            f_reg[op[pc][1]] = temp.f;
        } else if (o0 == LSR) {
            if (bb) { printf("l.sr "); POP printf("%d\n",LSR-257); }
            u temp;
            assert (reg[op[pc][2]] + op[pc][3] < MEM_SIZE);
            temp.i = mem[reg[op[pc][2]] + op[pc][3]];
            f_reg[op[pc][1]] = temp.f;
        } else if (o0 == SW) {
            if (bb) { printf("sw "); POP printf("%d\n",SW-257); }
            assert (reg[op[pc][2]] + op[pc][3] < MEM_SIZE);
            mem[reg[op[pc][2]] + op[pc][3]] = reg[op[pc][1]];
        } else if (o0 == SS) {
            if (bb) { printf("s.s "); POP printf("%d\n",SS-257); }
            u temp;
            temp.f = f_reg[op[pc][1]];
            assert (reg[op[pc][2]] + op[pc][3] < MEM_SIZE);
            mem[(reg[op[pc][2]] + op[pc][3])] = temp.i;
        } else if (o0 == BEQ) {
            if (bb) { printf("beq "); POP printf("%d\n",BEQ-257); }
            if(reg[op[pc][1]] == reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == BNE) {
            if (bb) { printf("bne "); POP printf("%d\n",BNE-257); }
            if(reg[op[pc][1]] != reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == BLT) {
            if (bb) { printf("blt "); POP printf("%d\n",BLT-257); }
            if(reg[op[pc][1]] < reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == BGT) {
            if (bb) { printf("bgt "); POP printf("%d\n",BGT-257); }
            if(reg[op[pc][1]] > reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == CEQS) {
            if (bb) { printf("c.eq.s "); POP printf("%d\n",CEQS-257); }
            if (f_reg[op[pc][1]] == f_reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == CLES) {
            if (bb) { printf("c.le.s "); POP printf("%d\n",CLES-257); }
            if (f_reg[op[pc][1]] <= f_reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == CLTS) {
            if (bb) { printf("c.lt.s "); POP printf("%d\n",CLTS-257); }
            if (f_reg[op[pc][1]] < f_reg[op[pc][2]]) {
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == J) {
            if (bb) { printf("j "); POP printf("%d\n",J-257); }
            pc = op[pc][1];
            continue;
        } else if (o0 == JR) {
            if (bb) { printf("jr "); POP printf("%d\n",JR-257); }
            pc = reg[op[pc][1]];
            continue;
        } else if (o0 == JAL) {
            if (bb) { printf("jal "); POP printf("%d\n",JAL-257); }
            reg[31] = pc + 1;
            pc = op[pc][1];
            continue;
        } else if (o0 == JALR) {
            if (bb) { printf("jalr "); POP printf("%d\n",JALR-257); }
            reg[31] = pc + 1;
            pc = reg[op[pc][1]];
            continue;
        } else if (o0 == SRLI) {
            if (bb) { printf("srli "); POP printf("%d\n",SRLI-257); }
            unsigned int o2,o3;
            o2 = (unsigned int) reg[op[pc][2]];
            o3 = (unsigned int) op[pc][3];
            if (o3>=32) {
                reg[op[pc][1]] = 0;
            } else {
                reg[op[pc][1]] = (int) (o2 >> o3);
            }   
        } else if (o0 == SLLI) {
            if (bb) { printf("slli "); POP printf("%d\n",SLLI-257); }
            unsigned int o2,o3;
            o2 = (unsigned int) reg[op[pc][2]];
            o3 = (unsigned int) op[pc][3];     
            reg[op[pc][1]] = (int) (o2 << o3);
        } else if (o0 == PRINTC) {
            if (bb) { printf("print_c "); POP printf("%d\n",PRINTC-257); }
            printf("%c", reg[op[pc][1]]);
        } else if (o0 == READI) {
            if (bb) { printf("read_i "); POP printf("%d\n",READI-257); }
            if (scanf("%d", &reg[op[pc][1]]) != 1) {
                fprintf(stderr, "readi\n");
                exit(-1);
            }
        } else if (o0 == READF) {
            if (bb) { printf("read_f "); POP printf("%d\n",READF-257); }
            if (scanf("%f", &f_reg[op[pc][1]]) != 1) {
                fprintf(stderr, "readf\n");
                exit(-1);
            }
        } else if (o0 == BEQI) {
            if (bb) { printf("beqi\n"); POP printf("%d\n",BEQI-257); }
            if (reg[op[pc][1]] == op[pc][2]) { 
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == AND) {
            if (bb) { printf("and\n"); POP printf("%d\n",AND-257); }
            reg[op[pc][1]] = reg[op[pc][2]] & reg[op[pc][3]];
        } else if (o0 == OR) {
            if (bb) { printf("or\n"); POP printf("%d\n",OR-257); }
            reg[op[pc][1]] = reg[op[pc][2]] | reg[op[pc][3]];
        } else if (o0 == XOR) {
            if (bb) { printf("xor\n"); POP printf("%d\n",XOR-257); }
            reg[op[pc][1]] = reg[op[pc][2]] ^ reg[op[pc][3]];
        } else if (o0 == ANDI) {
            if (bb) { printf("andi\n"); POP printf("%d\n",ANDI-257); }
            reg[op[pc][1]] = reg[op[pc][2]] & op[pc][3];
        } else if (o0 == ORI) {
            if (bb) { printf("ori\n"); POP printf("%d\n",ORI-257); }
            reg[op[pc][1]] = reg[op[pc][2]] | op[pc][3];
        } else if (o0 == XORI) {
            if (bb) { printf("xori\n"); POP printf("%d\n",XORI-257); }
            reg[op[pc][1]] = reg[op[pc][2]] ^ op[pc][3];
        } else if (o0 == EXIT) {
            if (bb) { printf("exit\n"); POP printf("%d\n",EXIT-257); }
            break;
        } else if (o0 == SWAP) {
            if (bb) { printf("swap\n"); POP printf("%d\n",SWAP-257); }
            int32_t temp2 = reg[op[pc][1]];
            reg[op[pc][1]] = reg[op[pc][2]];
            reg[op[pc][2]] = temp2;
        } else if (o0 == SWAPS) {
            if (bb) { printf("swap.s\n"); POP printf("%d\n",SWAPS-257); }
            float temp2 = f_reg[op[pc][1]];
            f_reg[op[pc][1]] = f_reg[op[pc][2]];
            f_reg[op[pc][2]] = temp2;
        } else if (o0 == SELECT) {
            if (bb) { printf("select\n"); POP printf("%d\n",SELECT-257); }
            reg[OP(1)] = reg[OP(2)] ? reg[OP(3)] : reg[OP(4)];
        } else if (o0 == SELECTS) {
            if (bb) { printf("select.s\n"); POP printf("%d\n",SELECTS-257); }
            f_reg[OP(1)] = reg[OP(2)] ? f_reg[OP(3)] : f_reg[OP(4)];
        } else if (o0 == CMP) {
            if (bb) { printf("cmp\n"); POP printf("%d\n",CMP-257); }
            switch (OP(4)) {
                CASE EQ: reg[OP(1)] = reg[OP(2)] == reg[OP(3)];
                CASE NE: reg[OP(1)] = reg[OP(2)] != reg[OP(3)];
                CASE LE: reg[OP(1)] = reg[OP(2)] <= reg[OP(3)];
                CASE GE: reg[OP(1)] = reg[OP(2)] >= reg[OP(3)];
                CASE LT: reg[OP(1)] = reg[OP(2)] <  reg[OP(3)];
                CASE GT: reg[OP(1)] = reg[OP(2)] >  reg[OP(3)];
                DEFAULT: assert(0);
            }
        } else if (o0 == CMPI) {
            if (bb) { printf("cmpi\n"); POP printf("%d\n",CMPI-257); }
            switch (OP(4)) {
                CASE EQ: reg[OP(1)] = reg[OP(2)] == OP(3);
                CASE NE: reg[OP(1)] = reg[OP(2)] != OP(3);
                CASE LE: reg[OP(1)] = reg[OP(2)] <= OP(3);
                CASE GE: reg[OP(1)] = reg[OP(2)] >= OP(3);
                CASE LT: reg[OP(1)] = reg[OP(2)] <  OP(3);
                CASE GT: reg[OP(1)] = reg[OP(2)] >  OP(3);
                DEFAULT: assert(0);
            }
        } else if (o0 == CMPS) {
            if (bb) { printf("cmp.s\n"); POP printf("%d\n",CMPS-257); }
            switch (OP(4)) {
                 CASE EQ: reg[OP(1)] = f_reg[OP(2)] == f_reg[OP(3)];
                 CASE NE: reg[OP(1)] = f_reg[OP(2)] != f_reg[OP(3)];
                 CASE LE: reg[OP(1)] = f_reg[OP(2)] <= f_reg[OP(3)];
                 CASE GE: reg[OP(1)] = f_reg[OP(2)] >= f_reg[OP(3)];
                 CASE LT: reg[OP(1)] = f_reg[OP(2)] <  f_reg[OP(3)];
                 CASE GT: reg[OP(1)] = f_reg[OP(2)] >  f_reg[OP(3)];
                 DEFAULT: assert(0);
            }
        } else if (o0 == CVTSW) {
            if (bb) { printf("cvt.s.w\n"); POP printf("%d\n",CVTSW-257); }
            u temp2; 
            temp2.i = reg[op[pc][2]];
            f_reg[op[pc][1]] = temp2.f;
        } else if (o0 == CVTWS) {
            if (bb) { printf("cvt.w.s\n"); POP printf("%d\n",CVTWS-257); }
            u temp2; 
            temp2.f = f_reg[op[pc][2]];
            reg[op[pc][1]] = temp2.i;
        } else if (o0 == EXIT) {
            if (bb) { printf("exit "); POP printf("%d\n",EXIT-257); }
            break;
        } else if (o0 == BNEI) {
            if (bb) { printf("bnei "); POP printf("%d\n",BNEI-257); }
            if(reg[op[pc][1]] != op[pc][2]) {
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == BLTI) {
            if (bb) { printf("blti "); POP printf("%d\n",BLTI-257); }
            if(reg[op[pc][1]] < op[pc][2]) {
                pc = op[pc][3];
                continue;
            }
        } else if (o0 == BGTI) {
            if (bb) { printf("bgti "); POP printf("%d\n",BGTI-257); }
            if(reg[op[pc][1]] > op[pc][2]) {
                pc = op[pc][3];
                continue;
            }
        }

        pc += 1;

    }


    analyze_how_many_times_called(op, how_many_times_called);

    return;

}

