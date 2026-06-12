// Demo program for the Algorithms Library.
//
// This is not part of the library itself; it is a small driver that shows each
// algorithm (bubble sort, quicksort, binary search) in action, so the library
// can be demonstrated from the command line.

#include <stdio.h>

#include "bubble_sort.h"
#include "quick_sort.h"
#include "binary_search.h"

// Prints an array on a single line, with a label in front of it.
static void print_array(const char *label, int list[], int n)
{
    printf("%s", label);
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
}

// Copies n elements from src into dst, so each sort can run on fresh data.
static void copy_array(int dst[], int src[], int n)
{
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

int main(void)
{
    int data[] = {9, 3, 7, 1, 8, 2, 5, 4, 6, 0};
    int n = sizeof(data) / sizeof(data[0]);

    printf("=== Algorithms Library demo ===\n\n");
    print_array("Original array:  ", data, n);
    printf("\n");

    // --- Bubble sort -------------------------------------------------------
    // Run on a copy so the original stays unsorted for the next demo.
    int bubble_data[10];
    copy_array(bubble_data, data, n);
    bubble_sort(bubble_data, n);
    print_array("Bubble sort:     ", bubble_data, n);

    // --- Quicksort ---------------------------------------------------------
    int quick_data[10];
    copy_array(quick_data, data, n);
    quick_sort(quick_data, n);
    print_array("Quicksort:       ", quick_data, n);
    printf("\n");

    // --- Binary search -----------------------------------------------------
    // Binary search needs a sorted array, so we search the quicksorted one.
    printf("Binary search on the sorted array:\n");

    int found = 7;
    int pos = binary_search(quick_data, n, found);
    if (pos != -1)
        printf("  %d found at index %d\n", found, pos);
    else
        printf("  %d not found\n", found);

    int missing = 42;
    pos = binary_search(quick_data, n, missing);
    if (pos != -1)
        printf("  %d found at index %d\n", missing, pos);
    else
        printf("  %d not found\n", missing);

    return 0;
}
