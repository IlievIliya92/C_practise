/*
Given the string representations of two integers, return the string representation of the sum of those integers.

For example:

strsum("1", "2")     => 3

A string representation of an integer will contain no characters besides the ten numerals "0" to "9".
*/

/*********************
 *      INCLUDES
 *********************/
#include <malloc.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


/*********************
 *      DEFINES
 *********************/
#define TEST_CASES       3
#define ENTRY_MAX_LEN    10
#define RESULT_MAX_LEN   10

/**********************
 *      TYPEDEFS
 **********************/
typedef enum test_entries_t {
    ENTRY_0 = 0,
    ENTRY_1,
    ENTRIES,
} test_entries_t;

typedef struct datum_dec_t
{
    long int a;
    long int b;
    long int res;
    char *end;
} datum_dec_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static char *strsum(const char *a, const char *b);

/**********************
 *  STATIC VARIABLES
 **********************/
static char resStr[RESULT_MAX_LEN];

/**********************
 *   MAIN __START
 **********************/
int main()
{
    const char datum[TEST_CASES][ENTRIES][ENTRY_MAX_LEN] = {{"123" , "456"},
                                                            {"0001" , "9"},
                                                            {"0000" , "0"}};
    int i = 0;
    char *res;

    for (i = 0; i < TEST_CASES; i++)
    {
        strsum(datum[i][ENTRY_0], datum[i][ENTRY_1]);
        printf("%s\n", resStr);
    }

    return 0;
}


/**********************
 *   LOCAL FUNCTIONS
 **********************/

static char *strsum(const char *a, const char *b)
{
    datum_dec_t data;

    data.a = 0;
    data.b = 0;
    data.res = 0;
    data.end = NULL;

    data.a = strtol(a, &data.end, 10);
    data.b = strtol(b, &data.end, 10);
    data.res = data.a + data.b;

    sprintf(resStr, "%ld", data.res);

    return resStr;
}

