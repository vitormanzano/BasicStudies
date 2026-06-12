#include "bubble_sort.h"
#include "swap.h"


void bubble_sort(int list[], int n) 
{
    int new_n = n;
    while (new_n > 1)
    {
        int last_swap = 0;
        for (int j = 0; j < new_n; j++)
        {
            if (list[j] > list[j + 1]) 
            {
                swap(&list[j], &list[j + 1]);
                last_swap = j + 1;
            }
        }
        new_n = last_swap;
    }
}

