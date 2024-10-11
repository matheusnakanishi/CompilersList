%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>

int total_lines = 0;
int blank_lines = 0;
int lines_w_comments = 0;
int nb_nc_lines = 0;
int semi_colons = 0;
int preproc_direct = 0;

%}

%%

^[ \t]*\n               {total_lines++; blank_lines++;}
\n                      {total_lines++;}
"//".*                  {lines_w_comments++;}
";"                     {semi_colons++;}
"#include"|"#define"    {preproc_direct++;}
.			;

%%

int main(int argc, char **argv){

        printf(" total    blank lines w/   nb, nc    semi- preproc. file\n");
        printf(" lines    lines comments    lines   coluns  direct.     \n");
        printf("------+--------+--------+--------+--------+--------+----\n");

        for(int i = 1; i < argc; i++){
                FILE *file = fopen(argv[i], "r");
                if(!file){
                        perror(argv[i]);
                        continue;
                }

                yyin = file;
                total_lines = 0;
                blank_lines = 0;
                lines_w_comments = 0;
                semi_colons = 0;
                preproc_direct = 0;

                yylex();
                fclose(file);

                printf("%6d %8d %8d %8d %8d %8d %s\n", total_lines, blank_lines, lines_w_comments, (total_lines-blank_lines-lines_w_comments), semi_colons, preproc_direct, argv[i]);

        }
        return 0;
}
