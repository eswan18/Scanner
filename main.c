#include <string.h>
#include "token.h"

extern FILE *yyin;
extern char *yytext;

int scan(char *filename);
int parse(char *filename);

int main(int argc, char *argv[]) {
        char *filename;
	char *option;
        if (argc >= 3) {
                option = argv[1];
		filename = argv[2];
        } else {
		fprintf(stderr,"error: provide both an option (e.g. -scan, -parse) and a filename when invoking cminor.\nfor example: './cminor -parse myfile.cminor'\n");
		return(1);
        }
	
	if (strcmp(option,"-scan") == 0) {
		scan(filename);
	} else if (strcmp(option,"-parse") == 0) {
		scan(filename);
		parse(filename);
	}
	
        return 0;
}

int scan(char *filename) {
        yyin  = fopen(filename,"r");
        while(yyin) {
                token_t t = yylex();
                if (!t)
                        break;
                printf("%s", token_string(t));
                if ( t == TOKEN_STRING_LITERAL || t == TOKEN_CHAR_LITERAL) {
                        char string[600];
                        strcpy(string,yytext);
                        convertString(string);
                        printf(" %s", string);
                }
                if ( t == TOKEN_IDENTIFIER && strlen(yytext) > 255 ) {
                        fprintf(stderr,"scan error: %s is too long to be a valid identifier.\n",yytext);
                        exit(1);
                }
                printf("\n");
        }
        fclose(yyin);
	return 0;
}

int parse(char *filename) {
	return 0;
}
