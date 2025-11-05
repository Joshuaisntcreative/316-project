#include <stdio.h>
#include <ctype.h>
#include "JAINARINE_23985568_2.h"
#include <string.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();


/*****************************************************/
/* lookup - a function to lookup operators and parentheses
and return the token */

int lookup(char ch)
{
    switch (ch)
    {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        getChar();
        if(nextChar == '=')
        {
            addChar();
            nextToken = PLUSEQUALS;
            getChar();
        }
        else{
        nextToken = ADD_OP;
        }

        break;
    case '-':
        addChar();
        getChar();
        if (nextChar == '=') {
            addChar();
            nextToken = MINUSEQUALS;  // -=
            getChar();
        } else {
            nextToken = SUB_OP;       // -
        }
        break;

    case '*':
        addChar();
        getChar();
        if (nextChar == '=') {
            addChar();
            nextToken = MULTEQUALS;   // *=
            getChar();
        } else {
            nextToken = MULT_OP;      // *
        }
        break;
    case '/':
        addChar();
        getChar();
        if (nextChar == '=') {
            addChar();
            nextToken = DIVIDEEQUALS; // /=
            getChar();
        } else {
            nextToken = DIV_OP;       // /
        }
        break;

    case '%':
        addChar();
        getChar();
        if(nextChar == '=')
        {
            addChar();
            nextToken = MODEQUALS;
            getChar();
        }else{
            nextToken = MOD_OP;
            }
    case '^':
        addChar();
        nextToken = POW_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}



//you want a separate look up table for the +=, -=,...
//we can tell the lexical analyser to look at this special table if the codes for the


/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{
    if (lexLen <= 98)
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}

//called when there is an operator detected by the lexical analyser and will determine whether the token is a regular operator or an incremental one i.e (+, +=)
//will call get next char to peek ahead and determine if the next char is a =, if so we will handle the call differently.



/*****************************************************/
/* getChar - a function to get the next character of
input and determine its character class */
void getChar()
{
    //getc returns an int.
    if ((nextChar = getc(in_fp)) != EOF)
    {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else if (nextChar == '\n')
        {
            charClass = NEWLINE;
        }
        else
            charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}


/*****************************************************/

/* getNonBlank - a function to call getChar until it
returns a non-whitespace character */
void getNonBlank()
{
    while (isspace(nextChar))
        getChar();
}
/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
expressions */
int lex()
{
    lexLen = 0;
    getNonBlank();
    switch (charClass)
    {
        /* Parse identifiers */
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT)
        {
            addChar();
            getChar();
        }
        checkKeyword();
        break;
    /* Parse integer literals */
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT)
        {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    /* Parentheses and operators */
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case NEWLINE:
        nextToken = EOL;
        break;
    /* EOF */
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    } /* End of switch */
    printf("Next token is: %d, Next lexeme is %s\n",
           nextToken, lexeme);
    return nextToken;
} /* End of function lex */

//had to cheat a bit, I didn't see a better way in C to compare strings, this function just handles the keywords at the start of the front.in files
int checkKeyword() {
    if (strcmp(lexeme, "int") == 0)
        nextToken = INT_KEYWORD;
    else if (strcmp(lexeme, "unsigned") == 0)
        nextToken = UNSIGNED_KEYWORD;
    else if (strcmp(lexeme, "signed") == 0)
        nextToken = SIGNED_KEYWORD;
    else if (strcmp(lexeme, "short") == 0)
        nextToken = SHORT_KEYWORD;
    else if (strcmp(lexeme, "long") == 0)
        nextToken = LONG_KEYWORD;
    else
        nextToken = IDENT;   // default if not a keyword

    return nextToken;
}

