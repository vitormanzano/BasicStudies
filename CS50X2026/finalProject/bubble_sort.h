#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

/**
 * Sorts an array of integers in ascending order using bubble sort.
 *
 * The array is sorted in place: the original array is modified and there is
 * no return value.
 *
 * Parameters:
 *   list - the array of integers to sort.
 *   n    - the number of elements in the array.
 *
 * Complexity: O(n^2) time in the average and worst case, O(n) in the best
 * case (an already sorted array), and O(1) extra space.
 */
void bubble_sort(int list[], int n);

#endif
