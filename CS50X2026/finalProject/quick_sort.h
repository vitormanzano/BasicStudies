#ifndef QUICK_SORT_H
#define QUICK_SORT_H

/**
 * Sorts an array of integers in ascending order using quicksort.
 *
 * The array is sorted in place: the original array is modified and there is
 * no return value.
 *
 * Parameters:
 *   list - the array of integers to sort.
 *   n    - the number of elements in the array.
 *
 * Complexity: O(n log n) time in the average case, O(n^2) in the worst case,
 * and O(log n) extra space on the call stack (recursive implementation).
 */
void quick_sort(int list[], int n);

#endif
