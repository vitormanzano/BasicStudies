# Makefile for the Algorithms Library
#
# This builds the three algorithms (bubble sort, binary search, quicksort) and
# the shared swap helper into a single static library: libalgorithms.a
#
# Usage:
#   make          build the static library (this is the default target)
#   make clean    remove the generated object files and the library
#
# To use the library in your own program, compile against the .a file:
#   cc -o program program.c libalgorithms.a

# ---- Variables -------------------------------------------------------------
# Defined once here and reused below with $(NAME), so a change (for example a
# compiler flag) only has to be made in one place.

CC = cc                  # the C compiler to use
CFLAGS = -Wall -Wextra   # warning flags: catch as many mistakes as possible
OBJ = bubble_sort.o binary_search.o quick_sort.o swap.o   # object files
LIB = libalgorithms.a    # the static library to produce (.a = archive)

# ---- Rules -----------------------------------------------------------------

# Default target: the first rule in the file, run when you type plain "make".
all: $(LIB)

# Build the library by bundling every object file into one archive.
#   ar  = the archiver tool that creates static libraries
#   r   = insert the files (replacing older versions)
#   c   = create the archive if it does not exist yet
#   s   = write an index, so the linker can find symbols quickly
$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

# Pattern rule: how to turn any source file (name.c) into its object (name.o).
# This single rule covers all of the .c files listed in OBJ.
#   $<  = the first prerequisite (the .c file)
#   $@  = the target being built  (the .o file)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove everything that "make" produces, to start from a clean state.
clean:
	rm -f $(OBJ) $(LIB)

# Tell make that "all" and "clean" are command names, not files to build.
# Without this, if a file named "all" or "clean" ever existed, make would think
# the target was already up to date and skip the recipe.
.PHONY: all clean
