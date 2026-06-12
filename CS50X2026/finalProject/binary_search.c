#include "binary_search.h"

int binary_search(int list[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (list[mid] == target)
            return mid;

        if (list[mid] < target)
            low = mid + 1;

        else
            high = mid - 1;
    }
    return -1;
}
