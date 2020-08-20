
/*
Welcome.

In this kata you are required to, given a string, replace every letter with its position in the alphabet.

If anything in the text isn't a letter, ignore it and don't return it.

"a" = 1, "b" = 2, etc.
Example

alphabet_position("The sunset sets at twelve o' clock.");

Should return "20 8 5 19 21 14 19 5 20 19 5 20 19 1 20 20 23 5 12 22 5 15 3 12 15 3 11" (as a string)

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LETTERS                     27

#define BASE_UNICODE                96
#define LAST_LETTER_UNICODE         BASE_UNICODE + LETTERS

#define BASE_UNICODE_M              64
#define LAST_LETTER_UNICODE_M       BASE_UNICODE_M + LETTERS


typedef enum {
    VALID_LETTER_M = 0,
    VALID_LETTER_S,
    INVALID_SYMBOL
} symbol_status_t;

static
symbol_status_t isLetter(char symbol)
{
    symbol_status_t res = INVALID_SYMBOL;

    if (symbol > BASE_UNICODE && symbol < LAST_LETTER_UNICODE)
    {
        res = VALID_LETTER_S;
    }
    else if (symbol > BASE_UNICODE_M && symbol < LAST_LETTER_UNICODE_M)
    {
        res = VALID_LETTER_M;
    }
    else
    {
        res = INVALID_SYMBOL;
    }

    return res;
}

static
char leterToPostion(char letter)
{
    char position = 0;
    symbol_status_t type = INVALID_SYMBOL;

    type = isLetter(letter);

    switch(type)
    {
        case VALID_LETTER_M:
            position = letter - BASE_UNICODE_M;
            break;

        case VALID_LETTER_S:
            position = letter - BASE_UNICODE;
            break;

        default:
            /*  */
            break;
    }

    return position;
}

static
char *alphabet_position(char *text)
{
    if (text == NULL)
    {
        fprintf(stderr, "[%s] The text is empty!\n", __func__);
        return NULL;
    }

    int postion = 0;
    char letterFormat[4];

    int buffLen = 0;
    char *buff = NULL;

    buffLen = strlen(text) * 2;
    buff =(char *)malloc(sizeof(char) * buffLen);
    if (buff == NULL)
    {
        fprintf(stderr, "[%s] Memory allocation failed!\n", __func__);
        return NULL;
    }
    memset(buff, '\0', buffLen);

    while(*text)
    {
        postion = leterToPostion(*text);
        if (postion != 0) {
            sprintf(letterFormat, "%d ", postion);
            strcat(buff, letterFormat);
        }

        text++;
    }

    buff[strlen(buff) - 1] = '\0';

    return buff;
}


int main (void)
{

    char *ptr;

    ptr = alphabet_position("abcde xyz");

//    ptr = alphabet_position("a B C ddda $$$$$$$$$...? a");

    printf("%s\n", ptr);



    free(ptr);

    return 0;
}





