# Algorithms Library

#### Video Demo: <URL HERE>

#### Description:

Algorithms Library is a small, reusable library written in C that implements
three classic algorithms: binary search, bubble sort, and quicksort.
The goal of the project is to package these algorithms as clean, well-documented
header files so that I, or anyone else, can drop them into a C project, include
them, and call them directly without having to rewrite the algorithms from
scratch.

The three algorithms were chosen on purpose, because together they cover the two
most fundamental operations on a collection of data, searching it and sorting it, 
and they show two very different approaches to the same problem:

- Binary search is a searching algorithm. Given an already sorted array, it
  finds the position of a target element in `O(log n)` time by repeatedly cutting
  the search range in half. It is a great example of how the right strategy can
  turn a slow linear scan into a very fast lookup.
- Bubble sort is a sorting algorithm that is famous for being simple to write
  and easy to understand, but slow. It runs in `O(n²)` time because it compares
  and swaps neighboring elements over and over until the whole array is in order.
  It represents the "naive" approach to sorting.
- Quicksort is a sorting algorithm that, in the average case, is one of the
  fastest general-purpose sorts, running in `O(n log n)` time. It uses a
  divide-and-conquer strategy: it picks a pivot, partitions the array around it,
  and then sorts each partition recursively. It represents the "smart" approach
  to the same problem bubble sort solves.

Because this is a library and not a standalone program, the focus is on a clear
and stable public interface (the function declarations in the header files),
correct implementations, and documentation so that another programmer can
understand how to use each function just by reading the header.

#### Project structure

Each algorithm lives in its own pair of files: a header (`.h`) that declares the
public function, and a source file (`.c`) that contains the implementation.

- `bubble_sort.h` / `bubble_sort.c` - declaration and implementation of the
  bubble sort algorithm.
- `binary_search.h` / `binary_search.c` - declaration and implementation of the
  binary search algorithm.
- `quick_sort.h` / `quick_sort.c` - declaration and implementation of the
  quicksort algorithm.
- `swap.h` / `swap.c` - a small helper that swaps two integers, shared by both
  sorting algorithms so the swap logic is written only once.

This keeps the library modular: a project that only needs sorting can include
just the sorting headers, and someone reading the code can find each algorithm in
one obvious place.

#### How to use

To use an algorithm from this library, include the matching header in your C
source file and compile your code together with the library's `.c` files.

The public functions are:

```c
void bubble_sort(int list[], int n);             // sort ascending, in place
void quick_sort(int list[], int n);              // sort ascending, in place
int  binary_search(int list[], int n, int target); // returns index, or -1
```

In every function, `list` is the array of integers and `n` is the number of
elements in it. The array does not know its own size in C, so you have to pass
`n` yourself. Where the array is declared you can compute it with
`sizeof(v) / sizeof(v[0])`; once the array is passed into a function it decays to
a pointer and that trick no longer works.

Important: `binary_search` requires the array to already be sorted in ascending
order. If it is not, sort it first (for example with `quick_sort`) and only then
search.

Example program:

```c
#include <stdio.h>
#include "quick_sort.h"
#include "binary_search.h"

int main(void)
{
    int v[] = {9, 3, 7, 1, 8, 2, 5, 4, 6, 0};
    int n = sizeof(v) / sizeof(v[0]);

    quick_sort(v, n);                 // now v is sorted

    int pos = binary_search(v, n, 7); // search the sorted array
    if (pos != -1)
        printf("Found 7 at index %d\n", pos);
    else
        printf("7 is not in the array\n");

    return 0;
}
```

Compile it together with the library source files. The two sorting algorithms
also need `swap.c`:

```
cc -o program program.c quick_sort.c binary_search.c swap.c
```

#### Design choices

- All algorithms operate on arrays of `int`. Keeping a single, concrete type
  makes the library simple to read and to demonstrate. A more general version
  could use `void *` plus a comparison function (like the standard `qsort`), but
  that adds complexity that is not needed for the goals of this project.
- One algorithm per pair of files. Each algorithm is declared in its own header
  and implemented in its own source file, so the public interface of each one is
  easy to find and a project can include only what it needs.
- The `swap` helper lives in its own file instead of being copied into both
  sorts. Because it has to be shared across files, it is a normal (non-`static`)
  function: marking it `static` would hide it inside a single file and the other
  sorts would not be able to link against it.
- Binary search and quicksort are written iteratively and recursively
  respectively, in the most standard way, with comments explaining the key steps
  (the partition logic and the recursion base case).
- Every public function is documented in its header with its parameters, return
  value, complexity and, for binary search, its precondition, so the library can
  be understood just by reading the headers.
