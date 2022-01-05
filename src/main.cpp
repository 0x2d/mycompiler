#include<stdio.h>
#include<unistd.h>
#include<errno.h>
extern char *optarg;

extern void codegen_eeyore(char *input_file_path, char *output_file_path);
extern void codegen_tigger(char *input_file_path, char *output_file_path);
extern void codegen_riscv(char *input_file_path, char *output_file_path);

int main(int argc, char *argv[]){
    int arg_temp = 0;
    char *input_file_path = nullptr;
    char *output_file_path = nullptr;

    //-S <inputfile> -o <outputfile>
    while(EOF != (arg_temp = getopt(argc,argv,"o:S:"))){
        switch(arg_temp){
            case 'o':
                output_file_path = optarg;
                break;
            case 'S':
                input_file_path = optarg;
                break;
            case '?':
                perror("Wrong arg!\n");
                return 1;
        }
    }

    if(!output_file_path){
        output_file_path = "./output.S";
    }

    codegen_eeyore(input_file_path, "./output.eeyore");
    codegen_tigger("./output.eeyore","./output.tigger");
    codegen_riscv("./output.tigger",output_file_path);
    
    return 0;
}