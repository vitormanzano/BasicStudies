#include "quick_sort.h"
#include "swap.h"

int partition(int list[], int low, int high)
{
    int pivot = list[low];
    int i = low;
    int j = high;

    while (i < j)
    {
        // Find the first element greater than the pivot
        while (list[i] <= pivot && i <= high - 1)
            i++;

        // Find the first element smaller than the pivot
        while (list[j] > pivot && j >= low + 1)
            j--;

        if (i < j)
            swap(&list[i], &list[j]);
    }

    swap(&list[low], &list[j]);
    return j;
}


static void quick_sort_rec(int list[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(list, low, high);

        // Recursively call for left and right. Based on the Partition Index
        quick_sort_rec(list, low, pi - 1);
        quick_sort_rec(list, pi + 1, high);
    }
}


void quick_sort(int list[], int n)
{
    quick_sort_rec(list, 0, n - 1);
}

