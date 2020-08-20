#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define COUNTRY_CODE_SYMBOL         '('
#define COUNTRY_CODE_SYMBOL_END     ')'
#define DIGIT_SEPARATOR_SYMBOL      '-'
#define EMPTY_SPACE_SYMBOL          ' '

#define PHONE_NUMBER_STR_LEN        14

static
void create_phone_number(char *phnum, const unsigned char *nums)
{
    int i = 0;
    int j = 0;

    /* 0 1 2 3 4 5 6 7 8  9 10 11 12 13  index in phnum
     * ( 1 2 3 )   4 5 6  - 7  8  9  0   value that has to be placed in phnum
     */

    for (i = 0; i < PHONE_NUMBER_STR_LEN; i++)
    {
        if (i == 0) {
            phnum[i] = COUNTRY_CODE_SYMBOL;
        } else if (i == 4 ) {
            phnum[i] = COUNTRY_CODE_SYMBOL_END;
        } else if (i == 5 ) {
            phnum[i] = EMPTY_SPACE_SYMBOL;
        } else if (i == 9 ) {
            phnum[i] = DIGIT_SEPARATOR_SYMBOL;
        } else {
            /* https://www.fileformat.info/info/unicode/category/Nd/list.htm
             * vtoriq array sa celi chisla i trqbva da se napravqt na symvoli (charove)
             * '0' = 0030
             * '1' = 0031
             * zatova 1 + '0' = '1' (ravno e na 0031 koeto e simvola 1)
             */
            phnum[i] = nums[j] + '0';
            j++;
        }
    }
    /* Add terminating zero */
    phnum[PHONE_NUMBER_STR_LEN] = '\0';

    return;
}

int main (void)
{
    char phnum[15];
    const unsigned char numbersArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    create_phone_number(phnum, numbersArray);

    printf("%s\n", phnum);

    return 0;
}





