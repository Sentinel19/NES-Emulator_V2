//
// Created by amdulay on 9/23/26.
//

#ifndef NES_EMULATOR_CPU_H
#define NES_EMULATOR_CPU_H

// instructions

// Access Instructions
#define LDA_IM 0xA9 // immediate
#define LDA_ZP 0xA5 // zero page
#define LDA_ZPX 0xB5 // zero page X
#define LDA_AB 0xAD // absolute
#define LDA_ABX 0xBD // absolute X
#define LDA_ABY 0xB9 // absolute Y
#define LDA_INX 0xA1 // indirect X
#define LDA_INY 0xB1 // indirect Y

#define STA_ZP 0x85 // zero page
#define STA_ZPX 0x95 // zero page X
#define STA_AB 0x8D // absolute
#define STA_ABX 0x9D // absolute X
#define STA_ABY 0x99 // absolute Y
#define STA_INX 0x81 // indirect X
#define STA_INY 0x91 // indirect Y

#define LDX_IM 0xA2 // immediate
#define LDX_ZP 0xA6 // zero page
#define LDX_ZPY 0xB6 // zero page Y
#define LDX_AB 0xAE // absolute
#define LDX_ABY 0xBE // absolute Y

#define STX_ZP 0x86 // zero page
#define STX_ZPY 0x96 // zero page Y
#define STX_AB 0x8E // absolute

#define LDY_IM 0xA0 // immediate
#define LDY_ZP 0xA4 // zero page
#define LDY_ZPX 0xB4 // zero page X
#define LDY_AB 0xAC // absolute
#define LDY_ABX 0xBC // absolute X

#define STY_ZP 0x84 // zero page
#define STY_ZPX 0x94 // zero page X
#define STY_AB 0x8C // absolute

// Transfer Instructions
#define TAX 0xAA // implied

#define TXA 0x8A // implied

#define TAY 0xA8 // implied

#define TYA 0x98 // implied

// Stack Instructions
#define TSX 0xBA // implied

#define TXS 0x9A // implied


// Jump to Subroutine
#define JSR 0x20// absolute

// Logical Instructions
#define AND_IM 0x29 // immediate
#define EOR_IM 0x49 // immediate
#define ORA_IM 0x09 // immediate
#define BIT_ZP 0x24 // zero page

// Arithmetic Instructions
#define ADC_IM 0x69 // immediate
#define SBC_IM 0xE9 // immediate

#define INX 0xE8 // implied
#define INY 0xC8 // implied
#define DEX 0xCA // implied
#define DEY 0x88 // implied

// Shifting Instructions
#define LSR_AC 0x4A // accumulator
#define ASL_AC 0x0A // accumulator
#define ROL_AC 0x2A // accumulator
#define ROR_AC 0x6A // accumulator

// Misc
#define NOP 0xEA // implied
#define SEC 0x38 // implied
#define CLC 0x18 // implied
#define CLD 0xD8 // implied
#define CLI 0x58 // implied
#define CLV 0xB8 // implied
#define SED 0xF8 // implied
#define SEI 0x78 // implied

// public struct definitions
typedef struct {
    char a;
    char x;
    char y;
    char sp;
    char status;
    short int pc;
} registers;

typedef struct {
    signed char mem[65536]; // 16-bit addressing yields 64kB of memory
} memory;

typedef struct {
    signed char mem[65536];
} prog;

typedef struct {
    registers reg_file;
    memory ram;
    prog rom;
} CPU_6502;

// public function prototypes
void cpu_init(CPU_6502* cpu);
void disp_regs(CPU_6502* cpu);
void disp_zp(CPU_6502* cpu);
void cpu_cycle(CPU_6502* cpu);

#endif //NES_EMULATOR_CPU_H
