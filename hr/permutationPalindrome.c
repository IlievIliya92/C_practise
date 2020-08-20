// C program to print all permutations with duplicates allowed
#include <stdio.h>
#include <string.h>

/* Function to swap values at two pointers */
static void swap(char *x, char *y)
{
    char temp;

    temp = *x;
    *x = *y;
    *y = temp;

    return;
}


static void permute(char *a, int l, int r)
{
   int i;

   if (l == r)
     printf("%s\n", a);
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a + l), (a + i));
          permute(a, l + 1, r);
          swap((a + l), (a + i)); //backtrack
       }
   }
}

/* Driver program to test above functions */
int main()
{
    char str[] = "madam";
    int n = strlen(str);

    permute(str, 0, n-1);

    return 0;
}
