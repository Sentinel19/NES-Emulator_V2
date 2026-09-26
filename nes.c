// NES Emulator main file
// Created by amdulay on 4/16/26.
// Acts as overall wrapper for emulator. Contains clock timing solution

#include <stdio.h>
#include "nes.h"
#include "cpu.h"

int main(){

    // initialize system pieces
    CPU_6502 cpu;
    cpu_init(&cpu);

    //cpu.reg_file.status |= 1;
    cpu.rom.mem[0] = LDA_IM;
    cpu.rom.mem[1] = 0x03;
    cpu.rom.mem[2] = TAX;
    cpu.rom.mem[3] = DEX;


    // execute cycles (to be replaced with while loop with delay)
    for(int i = 0; i < 6; i++) {
        cpu_cycle(&cpu);
    }

    disp_regs(&cpu);
    disp_zp(&cpu);

    return 0;
}





