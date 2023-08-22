#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(strstr("-h", argv[1])){
        printf("[inpath] [outpath] [filter1] ... [filterN]\n");
        return 0;
    }
    if(argc < 3){
        printf("to few parameters\n");
        return 0;
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
            if(argc > 3){
                toWrite = 0;
                for(int filterCnt = 3; filterCnt < argc; filterCnt++){
                    char *find = strstr(readedString, argv[filterCnt]);
                    if(find != NULL){
                        int depth = 0;
                        int pos = (long)find - (long)readedString;
                        for(int i = 0; i < pos; i++){
                            if(readedString[i] == '{') depth++;
                            else if(readedString[i] == '}') depth--;
                        }
                        if(depth == 1 && readedString[pos + strlen(argv[filterCnt]) + 1] == ':'){
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
