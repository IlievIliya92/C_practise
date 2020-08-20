/*
Complete the function that determines the score of a hand in the card game Blackjack (aka 21).

The function receives an array of strings that represent each card in the hand ("2", "3", ..., "10", "J", "Q", "K" or "A") and should return the score of the hand (integer).

Note: in C the function receives a character array with the card 10 represented by the character T.
Scoring rules:

Number cards count as their face value (2 through 10). Jack, Queen and King count as 10. An Ace can be counted as either 1 or 11.

Return the highest score of the cards that is less than or equal to 21. If there is no score less than or equal to 21 return the smallest score more than 21.

Scoring rules:

Number cards count as their face value (2 through 10). Jack, Queen and King count as 10. An Ace can be counted as either 1 or 11.

Return the highest score of the cards that is less than or equal to 21. If there is no score less than or equal to 21 return the smallest score more than 21.
Examples

["A"]                           ==>  11
["A", "J"]                      ==>  21
["A", "10", "A"]                ==>  12
["5", "3", "7"]                 ==>  15
["5", "4", "3", "2", "A", "K"]  ==>  25

*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



static
int score_hand(size_t n, const char cards[n])
{
    int result = 0;
    int aceN = 0;
    int i = 0;

    for(i = 0; i < n; i++)
    {
        if (cards[i] == 'T' || cards[i] == 'J' ||
            cards[i] == 'Q' || cards[i] == 'K' )
        {
            result += 10;
        }
        else if (cards[i] ==  'A')
        {
            aceN++;
        }
        else
        {
            result += cards[i] - '0';
        }
    }

    for (i = 0; i < aceN; i++)
    {
        if (result <= 10) {
            result += 11;

            if (result > 21) {
                 result -= 11;
                 result += 1;
            }
        } else {
            result += 1;
        }
    }


    return result;
}

int main (void)
{
    int res = 0;

    const char cards[3] = {'8', 'A', 'A'};
    const char cards2[5] =  {'A', '2', '2', '7', '9'};
    const char cards3[2] =  {'A', 'J'};
    const char cards4[4] = {'A', 'A', 'A', 'J'};
    const char cards5[5] = {'A', '2', 'A', '3', 'A'};

    res = score_hand(3, cards);
    printf("%d\n", res);

    res = score_hand(5, cards2);
    printf("%d\n", res);

    res = score_hand(2, cards3);
    printf("%d\n", res);

    res = score_hand(4, cards4);
    printf("%d\n", res);

    res = score_hand(5, cards5);
    printf("%d\n", res);

    return 0;
}





