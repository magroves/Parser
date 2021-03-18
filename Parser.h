#ifndef PARSER_H
#define PARSER_H

#include "Givens.h"

void getNextToken();
void function();
void header();
void arg_decl();
void body();
void statement_list();
void statement();
void while_loop();
void _return();
void assignment();
void expression();
void term();
_Bool parser(struct lexics *someLexics, int numberOfLexics);
#endif