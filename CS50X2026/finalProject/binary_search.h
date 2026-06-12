#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

/**
 * Searches for a target value in a sorted array of integers.
 *
 * PRECONDITION: the array MUST already be sorted in ascending order. Searching
 * an unsorted array gives undefined (wrong) results. Use bubble_sort or
 * quick_sort first if needed.
 *
 * Parameters:
 *   list   - the sorted array of integers to search.
 *   n      - the number of elements in the array.
 *   target - the value to look for.
 *
 * Returns:
 *   the index (0-based) of the target if it is found, or -1 if the target is
 *   not present in the array.
 *
 * Complexity: O(log n) time and O(1) extra space (iterative implementation).
 */
int binary_search(int list[], int n, int target);

#endif
