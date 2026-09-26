// 6502 CPU Emulation
// Created by amdulay on 9/23/26.
// Contains all CPU components and operations
#include <stdio.h>
#include "cpu.h"

// opcode definitions



// private function prototypes
char fetch_byte(CPU_6502* cpu);

// initialize 6502
void cpu_init(CPU_6502* cpu) {
    cpu->reg_file.a = 0x00;
    cpu->reg_file.x = 0x00;
    cpu->reg_file.y = 0x00;
    cpu->reg_file.sp = 0x00;
    cpu->reg_file.status = 0x20;
    cpu->reg_file.pc = 0x0000;
}

// display register file
void disp_regs(CPU_6502* cpu) {
    printf("Register File-------------------------------\n");
    printf("Flags:    N   O   X   B   D   I   Z   C\n");
    printf("Status: | ");
    for(int i = 8; i > 0; i--){
        printf("%d | ", cpu->reg_file.status >> (i - 1) & 1);
    }
    printf("\n");
    printf("A: 0x%02hhX ", cpu->reg_file.a);
    printf("X: 0x%02hhX ", cpu->reg_file.x);
    printf("Y: 0x%02hhX ", cpu->reg_file.y);
    printf("SP: 0x%02hhX ", cpu->reg_file.sp);
    printf("PC: 0x%04hhX\n", cpu->reg_file.pc);
    printf("--------------------------------------------\n");

}

// display zero page of memory
void disp_zp(CPU_6502* cpu) {
    printf("Zero Page-----------------------------------------------------------------------------\n");
    printf("Upper Nibble | Lower Nibble - >\n");
    printf("| ");
    for (int i = 0; i < 16; i++) {
        printf("    %hhX", i);
    }
    printf("\n");
    printf("v");
    for(int j = 0; j < 16; j++){
        if (j == 0) {
            printf(" %hhX |", j);
        }
        else {
            printf("  %hhX |", j);
        }
        for(int i = 0; i < 16; i++) {
            if(i == 15){
                printf("0x%02hhX", cpu->ram.mem[16*j + i]);
            }
            else {
                printf("0x%02hhX ", cpu->ram.mem[16*j + i]);
            }
        }
        printf("|\n");
    }
    printf("--------------------------------------------------------------------------------------\n");


}

// execute one clock cycle
void cpu_cycle(CPU_6502* cpu) {
    static unsigned char state = 0; // instruction execution state machine variable
    static unsigned char opcode;
    static unsigned char l_addr;
    static unsigned char temp;


    switch (state) {
        case 0: // read opcode (executes 1 cycle in the process)
            opcode = fetch_byte(cpu);
            cpu->reg_file.pc++;
            state++;
            break;
        case 1:
            switch (opcode) { // determine instruction type
                case LDA_IM:
                    cpu->reg_file.a = fetch_byte(cpu);
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case LDX_IM:
                    cpu->reg_file.x = fetch_byte(cpu);
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case LDY_IM:
                    cpu->reg_file.y = fetch_byte(cpu);
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case STA_ZP:
                    l_addr = fetch_byte(cpu);
                    state++;
                    break;
                case STX_ZP:
                    l_addr = fetch_byte(cpu);
                    state++;
                    break;
                case STY_ZP:
                    l_addr = fetch_byte(cpu);
                    state++;
                    break;
                case TAX:
                    cpu->reg_file.x = cpu->reg_file.a;
                    state = 0;
                    break;
                case TAY:
                    cpu->reg_file.y = cpu->reg_file.a;
                    state = 0;
                    break;
                case TXS:
                    cpu->reg_file.sp = cpu->reg_file.x;
                    state = 0;
                    break;
                case TSX:
                    cpu->reg_file.x = cpu->reg_file.sp;
                    state = 0;
                    break;
                case TXA:
                    cpu->reg_file.a = cpu->reg_file.x;
                    state = 0;
                    break;
                case TYA:
                    cpu->reg_file.a = cpu->reg_file.y;
                    state = 0;
                    break;
                case AND_IM:
                    cpu->reg_file.a = cpu->reg_file.a & fetch_byte(cpu);
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case ORA_IM:
                    cpu->reg_file.a = cpu->reg_file.a | fetch_byte(cpu);
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case EOR_IM:
                    cpu->reg_file.a = cpu->reg_file.a ^ fetch_byte(cpu);
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case ADC_IM:
                    cpu->reg_file.a = cpu->reg_file.a + fetch_byte(cpu) + (cpu->reg_file.status & 1);
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case SBC_IM:
                    cpu->reg_file.a = cpu->reg_file.a + (fetch_byte(cpu) ^ 0xFF) + (cpu->reg_file.status & 1);
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case ASL_AC:
                    cpu->reg_file.status = cpu->reg_file.status | (cpu->reg_file.a >> 7 & 1);
                    cpu->reg_file.a = cpu->reg_file.a << 1;
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case LSR_AC:
                    cpu->reg_file.a = cpu->reg_file.a >> 1;
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case ROL_AC:
                    temp = cpu->reg_file.status & 1;
                    cpu->reg_file.status = (cpu->reg_file.status & 0xFE) | (cpu->reg_file.a >> 7 & 1);
                    cpu->reg_file.a = cpu->reg_file.a << 1;
                    cpu->reg_file.a |= temp;
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case ROR_AC:
                    temp = cpu->reg_file.a & 1;
                    cpu->reg_file.a = ((cpu->reg_file.a >> 1) & 0xEF) | (cpu->reg_file.status << 7 & 0x8);
                    cpu->reg_file.status = (cpu->reg_file.status & 0xFE) | (temp);
                    cpu->reg_file.pc++;
                    state = 0;
                    break;
                case INX:
                    cpu->reg_file.x++;
                    state = 0;
                    break;
                case INY:
                    cpu->reg_file.y++;
                    state = 0;
                    break;
                case DEX:
                    cpu->reg_file.x--;
                    state = 0;
                    break;
                case DEY:
                    cpu->reg_file.y--;
                    state = 0;
                    break;
                case SEC:
                    cpu->reg_file.status |= 1;
                    state = 0;
                    break;
                case SED:
                    cpu->reg_file.status |= 8;
                    state = 0;
                    break;
                case SEI:
                    cpu->reg_file.status |= 4;
                    state = 0;
                    break;
                case CLC:
                    cpu->reg_file.status &= 0xFE;
                    state = 0;
                    break;
                case CLD:
                    cpu->reg_file.status &= 0xF7;
                    state = 0;
                    break;
                case CLI:
                    cpu->reg_file.status &= 0xFB;
                    state = 0;
                    break;
                case CLV:
                    cpu->reg_file.status &= 0xBF;
                    state = 0;
                    break;
                default:
                    break;
            }
            case 2:
                switch (opcode) {
                    case STA_ZP:
                        cpu->ram.mem[l_addr] = cpu->reg_file.a;
                        cpu->reg_file.pc++;
                        state = 0;
                        break;
                    case STX_ZP:
                        cpu->ram.mem[l_addr] = cpu->reg_file.x;
                        cpu->reg_file.pc++;
                        state = 0;
                        break;
                    case STY_ZP:
                        cpu->ram.mem[l_addr] = cpu->reg_file.y;
                        cpu->reg_file.pc++;
                        state = 0;
                        break;
                    case NOP:
                        cpu->reg_file.pc++;
                        state = 0;
                        break;
                    default:
                        break;
                }
            break;
        default: // yet-to-be defined instructions and error handling (if decode returns -1)
            printf("Unknown opcode\n");
            break;
    }
}

// fetch byte from memory
char fetch_byte(CPU_6502* cpu) {
    return cpu->rom.mem[cpu->reg_file.pc];
}


