#include "token.h"
extern yyin;
extern yytext;

int main(int argc, char *argv[]) {
        char *filename;
        if (argc >= 2) {
                filename = argv[1];
        } else {
                /* add error message here */
                return(1);
        }
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
