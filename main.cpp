#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<vector>
#include"symtable.h"
#include"ast.h"
#include"parser.tab.h"
extern char *optarg;
extern AST *root;
extern FILE *yyin;
extern FILE *yyout;
extern TABLE *root_symtable;
extern std::vector<TABLE *>symtable_vector;
extern TABLE *symtable_ptr;

int main(int argc, char *argv[]){
    int arg_temp = 0;
    char *input_file_path = NULL;
    char *output_file_path = NULL;

    //-f <inputfile> -o <outputfile>
    while(EOF != (arg_temp = getopt(argc,argv,"o:f:"))){
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

    FILE *input_file = NULL;
    FILE *output_file = NULL;

    if(input_file_path){
        input_file = fopen(input_file_path,"r");
        yyin = input_file;
    }
    if(output_file_path){
        output_file = fopen(output_file_path,"w");
        yyout = output_file;
    }

    root_symtable = new TABLE("root");
    symtable_vector.push_back(root_symtable);
    symtable_ptr = root_symtable;
    yyparse();
    root->irgen();

    if(input_file){
        fclose(input_file);
        yyin = stdin;
    }
    if(output_file){
        fclose(output_file);
        yyout = stdout;
    }
    
    return 0;
}