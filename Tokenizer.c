/*
*  Tokenizer.c 
*    will read characters from a given FILE variable and convert them into lexical structs. 
*  CMSC 403 Spring 2021
*  Author: Mark Groves
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Tokenizer.h"

//pointer because string values instead of char
char *keywords[] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};

char *operators[] = {"+", "*", "!=", "==", "%"};

char delimiters[] = {'.', '(', ')', ',', '{', '}', ';', '[', ']'};

// declare struct for new lexeme
struct lexics curr;


/*********************
* TOKENIZER function *
*********************/
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
    int line = 1;
    int wordLineNums[60];
	char ch;
    char buffer[MY_CHAR_MAX][MY_CHAR_MAX];
    int a,i,j = 0;

	while ((ch = fgetc(inf)) != EOF) {
		// char is new line
        if (ch == '\n') {
			line++;
		}

        // char is alphanumeric
        if (isalpha(ch)) {
	    	buffer[i][j++] = ch;	

            //copy rest of lexime into buffer
		    while (isalnum(ch = fgetc(inf))) {
					// move to next char in lexeme
		    		buffer[i][j++] = ch;
		    }


			(*numLex)++;

			// printf("%s",buffer[i]);
			// exit(0);

			// copy lexeme to struct
			strcpy(curr.lexeme, buffer[i]);

			// decide if lexime is a VARTYPE or not
			if((strcmp(buffer[i],"int") == 0) || (strcmp(buffer[i],"void") == 0)){
				//printf("VARTYPE: %s\n", buffer[i]);
				curr.token = VARTYPE;
			}
			else if ((strcmp(buffer[i],"while") == 0)) {
				//printf("WHILE: %s\n", buffer[i]);
				curr.token = WHILE_KEYWORD;
			}
			else if ((strcmp(buffer[i],"return") == 0)) {
				//printf("RETURN: %s\n", buffer[i]);
				curr.token = RETURN_KEYWORD;
			}
			else {
				//printf("IDENTIFIER: %s\n", buffer[i]);
				curr.token = IDENTIFIER;
			}


			//add struct to array
			aLex[i] = curr;
			
			// sorry  had to do this cause fseek() was being annoying
			if((strcmp(curr.lexeme,"expletive")) == 0) {
				return TRUE;
			}

			//move to next index in buffer
		    i++;
			//reset ch index
			j = 0;	
			fseek(inf, -1, SEEK_CUR);
		} 

        // char is a digit
		else if (isdigit(ch)) {
	    	buffer[i][j++] = ch;	

            //copy rest of number
		    while (isdigit(ch = fgetc(inf))) {
		    		buffer[i][j++] = ch;
		    }

			// end lexime with EOL
		    buffer[i][j] = '\0';
			(*numLex)++;
			//printf("DIGIT: %s\n", buffer[i]);

			// copy lexeme to struct
			strcpy(curr.lexeme, buffer[i]);
			curr.token = NUMBER;

			//add struct to array
			aLex[i] = curr;
		    i++;
			j = 0;
			fseek(inf, -1, SEEK_CUR);	
		}

		// char is whitespace
		else if (isspace(ch)){
			continue;
		}

        // char is punctuation
		else if(ispunct(ch)) {	
	    	buffer[i][j++] = ch;
			(*numLex)++;

		 	if ((strcmp(buffer[i],"{") == 0)) {
				//printf("LEFT_BRACKET: %s\n", buffer[i]);
				strcpy(curr.lexeme, buffer[i]);
				curr.token = LEFT_BRACKET;
				
			}
			else if ((strcmp(buffer[i],"}") == 0)) {
				//printf("RIGHT_BRACKET: %s\n", buffer[i]);
				strcpy(curr.lexeme, buffer[i]);
				curr.token = RIGHT_BRACKET;	
			}
			else if ((strcmp(buffer[i],"(") == 0)) {
				//printf("LEFT_PARENTHESIS: %s\n", buffer[i]);
				strcpy(curr.lexeme, buffer[i]);
				curr.token = LEFT_PARENTHESIS;
			}
			else if ((strcmp(buffer[i],")") == 0)) {
				//printf("RIGHT_PARENTHESIS: %s\n", buffer[i]);
				strcpy(curr.lexeme, buffer[i]);
				curr.token = RIGHT_PARENTHESIS;
			}
			else if ((strcmp(buffer[i],",") == 0)) {
				//printf("COMMA: %s\n", buffer[i]);
				strcpy(curr.lexeme, buffer[i]);
				curr.token = COMMA; 
			}
			else if ((strcmp(buffer[i],";") == 0)) {
				//printf("EOL: %s\n", buffer[i]);
				strcpy(curr.lexeme, buffer[i]);
				curr.token = EOL;
			}
			else if ((strcmp(buffer[i],"=") == 0)) {
				//printf("EQUAL: %s\n", buffer[i]);
				// lex is == (BINOP)
				if ((ch = fgetc(inf)) == '=' ) {
					buffer[i][j++] = ch;
					strcpy(curr.lexeme, buffer[i]);
					curr.token = BINOP;
				}

				// lex is = (EQUAL)
				else {
					strcpy(curr.lexeme, buffer[i]);
					curr.token = EQUAL;
					fseek(inf, -1, SEEK_CUR);
				}
				
			}
			else if ((strcmp(buffer[i],"+") == 0)) {
				//printf("BINOP: %s\n", buffer[i]);
				strcpy(curr.lexeme, buffer[i]);
				curr.token = BINOP;
			}
			else if ((strcmp(buffer[i],"*") == 0)) {
				//printf("BINOP: %s\n", buffer[i]);
				strcpy(curr.lexeme, buffer[i]);
				curr.token = BINOP;
			}
			else if ((strcmp(buffer[i],"!") == 0)) {
				// lex is !=
				if ((ch = fgetc(inf)) == '=' ) {
					buffer[i][j++] = ch;
					//printf("BINOP: %s\n", buffer[i]);
					strcpy(curr.lexeme, buffer[i]);
					curr.token = BINOP;
					//fseek(inf, -1, SEEK_CUR);
				}
				else {
					return FALSE;
				}
			}
			else if ((strcmp(buffer[i],"%") == 0)) {
				//printf("BINOP: %s\n", buffer[i]);
				strcpy(curr.lexeme, buffer[i]);
				curr.token = BINOP;
			}

			//add struct to array
			aLex[i] = curr;
		    i++;
		 	j = 0;		 
	    }
	} // end while

    //printf("\n");
    return TRUE;
}