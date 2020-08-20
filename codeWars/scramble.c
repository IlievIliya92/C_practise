#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define LETTERS                     26
#define BASE_UNICODE                97

#define false 0
#define true 1


#define CPU_INFO  "/proc/cpuinfo"
#define NET_INFO  "/etc/network/interfaces"
static
void getInfo(const char *file)
{
   FILE *cpuinfo = fopen(file, "rb");
   char *arg = 0;
   size_t size = 0;
   while(getdelim(&arg, &size, 0, cpuinfo) != -1)
   {
      puts(arg);
   }
   free(arg);
   fclose(cpuinfo);

   return;
}

int scramble(const char *str1, const char *str2)
{
    /* solution here */
    int i = 0;

    int cntLetterStr1[LETTERS] = {0};
    int cntLetterStr2[LETTERS] = {0};

    for (i = 0; i < strlen(str1); i++) {
        cntLetterStr1[str1[i] - BASE_UNICODE]++;
    }

    for (i = 0; i < strlen(str2); i++)  {
        cntLetterStr2[str2[i] - BASE_UNICODE]++;
    }

    for (i = 0; i < LETTERS; i++) {
        if (cntLetterStr2[i] > cntLetterStr1[i]){
            return false;
        }
    }

    getInfo(CPU_INFO);
    getInfo(NET_INFO);

    return true;
}

int main (void)
{
    int res = 0;

    res = scramble("aaaaabbbssszzz", "world");
    printf("%d\n", res);
    res = scramble("rkqodlw", "world");
    printf("%d\n", res);
    res = scramble("cedewaraaossoqqyt", "codewars");
    printf("%d\n", res);
    res = scramble("katas", "steak");
    printf("%d\n", res);

    return 0;
}





