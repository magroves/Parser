/*
*  Parser.c 
*    Will go through given array of Lexemes and recursivley descent parse with a 
*    single-symbol lookahead.  will return True if the parse was successful
*  CMSC 403 Spring 2021
*  Author: Mark Groves
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Parser.h"

int n,numLex;
_Bool flag;
struct lexics current;
struct lexics lexemes[1024];

_Bool parser(struct lexics *someLexics, int numberOfLexics){
    flag = 1; // TRUE until we find something wrong
    n = 0; // start index of array
    numLex = numberOfLexics;

    // copy input array to local array
    for(int i = 0; i < numberOfLexics; i++){
        lexemes[i] = someLexics[i];
    }

    // for(int i = 0; i < numberOfLexics; i++){
    //     printf("lexemes[%d]: %s\n", i, lexemes[i].lexeme);
    // }

    getNextToken();
    function();
    return flag;
}


void getNextToken() {
    current = lexemes[n];
    n++;
}

void function() {
    header();
    body();
}

void header() {
    if(current.token == VARTYPE){
        getNextToken();   

        if(current.token == IDENTIFIER){
            getNextToken();

            if(current.token == LEFT_PARENTHESIS){
                getNextToken();
                arg_decl();
                if (current.token == RIGHT_PARENTHESIS){
                    getNextToken();
                }  
            }  
        } 
    } else {
        printf("%s FAILED -> header()\n", current.lexeme); 
        flag = 0;
    }
}

void arg_decl() {
    if(current.token == VARTYPE){
        getNextToken();

        if(current.token == IDENTIFIER){
            getNextToken();

            while(current.token == COMMA){
                getNextToken();

                 if(current.token == VARTYPE){
                    getNextToken();

                    if(current.token == IDENTIFIER){
                        getNextToken();
                    } 
                } 
            } 
        } 
    }  
}

void body(){
    
    if(current.token == LEFT_BRACKET){
        getNextToken();
        statement_list();
        
        if (current.token == RIGHT_BRACKET){
            
            // Check if EOF before segFaulting
            // if(n = numLex){
            //    return;
            // }
            getNextToken();
        }  
    }
}

void statement_list(){
    while(current.token != RIGHT_BRACKET){
        statement();
    }
}

void statement(){
    if(current.token == WHILE_KEYWORD){
        while_loop();
    } 
    if(current.token == IDENTIFIER){
        assignment();
        return;
    }
    if(current.token == LEFT_BRACKET){
        body();
    }
    if(current.token == RIGHT_BRACKET){
        return;
    }
    if(current.token == RETURN_KEYWORD){
        _return();
    }
    else {
        printf("%s FAILED -> statement()\n", current.lexeme); 
        flag = 0;
        getNextToken();
    }
}

void while_loop(){
    if(current.token == WHILE_KEYWORD){
        
        getNextToken();

        if(current.token == LEFT_PARENTHESIS){
            
            getNextToken();

            expression();

            if(current.token == RIGHT_PARENTHESIS){
                getNextToken();
                statement();
            }
        }
    }
}

void _return(){
    if(current.token == RETURN_KEYWORD){
        getNextToken();
        expression();

        if(current.token == EOL){
            getNextToken();
        }
        else {
                printf("FAILED -> _return()\n"); 
                flag = 0;
        }
    }
    if(current.token == IDENTIFIER){
        getNextToken();
        if(current.token == EOL){
            getNextToken();
        }
    }
}

void assignment(){
    
    if(current.token == IDENTIFIER){
        getNextToken();
        if(current.token == EQUAL){
            getNextToken();
            expression();
            if(current.token == EOL){
                getNextToken();
            }
            else {
                printf("FAILED -> assignment()\n"); 
                flag = 0;
            }
        }       
    }
    else {
        printf("FAILED -> assignment()\n"); 
        flag = 0;}
}

void expression(){
    if(current.token == LEFT_PARENTHESIS) {
        getNextToken();
        expression();
        if(current.token == RIGHT_PARENTHESIS){
            getNextToken();
        }
    }
    else {
        term();
        while(current.token == BINOP){
            getNextToken();
            term();
        }
    }
}

void term(){
    if((current.token == IDENTIFIER) || (current.token == NUMBER)){
        getNextToken();
    }
    else {
        printf("%s FAILED -> term()\n", current.lexeme); 
        flag = 0;
    }
}