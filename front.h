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
#define LEFT_PAREN 25
#define RIGHT_PAREN 26


//custom tokens codes for the project
#define UNSIGNED 27
#define SIGNED 28
#define BYTE 29
#define SHORT 30
#define LONG 31
#define PLUSEQUALS 32
#define MINUSEQUALS 33
#define MULTEQUALS 34
#define DIVIDEEQUALS 35
#define MODEQUALS 36
#define EOF_TOKEN -1

extern int nextToken;
extern char lexeme[];
extern FILE *in_fp;


int lex();
void getChar();
void addChar();
void getNonBlank();


#endif