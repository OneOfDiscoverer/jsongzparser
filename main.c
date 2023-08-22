#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>
#include "list.h"

int main(int argc, char* argv[]){
    switch(argc){
        case 2:
            if(strstr("-h", argv[1])){
                printf("[inpath] [outpath] [filter1],[filter2], ... ,[filterN]\n");
                return 0;
            }
        case 1:
            printf("to few parameters\n");
            return 0;
        default:
        {
            char sep[1] = ",";
            char *istr;
            book bk;
            for(int i = 3; i < argc; i++){
                istr = strtok (argv[i],sep);
                if(istr == NULL){
                    bk.str = istr;
                    pushBack(&bk);
                }
                else{
                    while (istr != NULL){
                        bk.str = istr;
                        pushBack(&bk);
                        istr = strtok (NULL,sep);
                    }
                }
            }
            break;
        }
    }    
    gzFile inputGz = gzopen(argv[1], "r");
    if(inputGz == NULL){
        perror("input file not opened");
        exit(EXIT_FAILURE);
    }
    gzFile outputGz = gzopen(argv[2], "w");
    if(outputGz == NULL){
        perror("output file not opened");
        exit(EXIT_FAILURE);
    }
    char readedString[65535];
    long strCounter = 0;
    while(1){
        gzgets(inputGz, readedString, sizeof(readedString));
        if((strCounter % 2)){
            char toWrite = 1;
            if(getAt(0)){
                toWrite = 0;
                for(int filterCnt = 0; getAt(filterCnt); filterCnt++){
                    char *find = strstr(readedString, getAt(filterCnt)->bk.str);
                    if(find != NULL){
                        int depth = 0;
                        int pos = (long)find - (long)readedString;
                        for(int i = 0; i < pos; i++){
                            if(readedString[i] == '{') depth++;
                            else if(readedString[i] == '}') depth--;
                        }
                        if(depth == 1 && readedString[pos + strlen(getAt(filterCnt)->bk.str) + 1] == ':'){ //костыльное определение сигнатуры ключа ^\_/^
                            toWrite = 1;
                        }
                    }
                }
            }
            if(toWrite){
                gzwrite(outputGz, readedString, strlen(readedString));
            }
        }
        if(gzeof(inputGz)) {
            break;
        }
        strCounter++;
    }
    gzclose(inputGz);
    gzclose(outputGz);
    return 0;
}
