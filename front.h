#ifndef LEXICAL_ANALYSER_H
#define LEXICAL_ANALYSER_H

#include <stdio.h>

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99


//Token codes

// going to define the custom codes for the project after right paren to make it easier to understand
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MOD_OP 25
#define POW_OP 26
#define LEFT_PAREN 27
#define RIGHT_PAREN 28
#define PARENS 29


//custom tokens codes for the project
#define UNSIGNED 37
#define SIGNED 38
#define BYTE 39
#define SHORT 40
#define LONG 41
#define PLUSEQUALS 42
#define MINUSEQUALS 43
#define MULTEQUALS 44
#define DIVIDEEQUALS 45
#define MODEQUALS 46
#define EOF_TOKEN -1

extern int nextToken;
extern char lexeme[];
extern FILE *in_fp;


int lex();
void getChar();
void addChar();
void getNonBlank();
void peekAhead();
int specialLookupTable(char lex[]);

#endif