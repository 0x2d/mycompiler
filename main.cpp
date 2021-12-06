#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include"y.tab.h"
extern char *optarg;

int main(int argc, char *argv[]){

    if(argc<2){
        perror("Need more arg!\n");
        return 1;
    }

    int arg_temp = 0;
    char *input_file_path = nullptr;
    char *output_file_path = nullptr;

    //-f <inputfile> -o <outputfile>
    while(EOF != (arg_temp = getopt(argc,argv,"of:"))){
        switch(arg_temp){
            case 'o':
                output_file_path = optarg;
                break;
            case 'f':
                input_file_path = optarg;
                break;
            case '?':
                perror("Wrong arg!\n");
                return 1;
        }
    }

    FILE *input_file;
    FILE *output_file;

    input_file = fopen(input_file_path, "r");
    if(output_file_path){
        output_file = fopen(output_file_path,"w");
    } else{
        output_file = fopen("b.out","w");
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}