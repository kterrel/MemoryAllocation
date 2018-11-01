# MemoryAllocation

This is a C++ program that emulates the operating system's responsibility of allocating memory to certain programs. It's a simple page-based view of memory management.

On program startup, it will have some 32 pages of contiguous, unused memory with each page being 4 KB long. It then allows the user to "run" programs that require chunks of this memory for some allocated period of time. It also allows the users to "kill" programs (i.e., "Ctrl-c" or "kill -9" in most OS's) that are in progress. The pages used by programs that are killed can then be re-used for future programs.

This program utilizes linked lists and pointers.

## Running the tests

Example I/O:

1. Add program
2. Kill program
3. Fragmentation
4. Print memory
5. Exit

choice - 1
Program name - P1
Program size (KB) - 8
Program P1 added successfully: 2 page(s) used.

choice - 1
Program name - P2
Program size (KB) - 7
Program P2 added successfully: 2 page(s) used.

choice - 1
Program name - P3
Program size (KB) - 9
Program P3 added successfully: 3 page(s) used. 

choice - 3
There are 1 fragment(s).

choice - 4

P1 P1 P2 P2 P3 P3  P3  Free
Free Free Free Free Free Free Free Free
Free Free Free Free Free Free Free Free
Free Free Free Free Free Free Free Free

choice - 2 
Program name - P2
Program P2 successfully killed, 2 page(s) reclaimed.

choice - 3
There are 2 fragment(s)

choice - 5
