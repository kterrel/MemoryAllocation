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

choice - 1<br/>
Program name - P1<br/>
Program size (KB) - 8<br/>
Program P1 added successfully: 2 page(s) used.<br/>
<br/>
choice - 1<br/>
Program name - P2<br/>
Program size (KB) - 7<br/>
Program P2 added successfully: 2 page(s) used.<br/>
<br/>
choice - 1<br/>
Program name - P3<br/>
Program size (KB) - 9<br/>
Program P3 added successfully: 3 page(s) used.<br/>
<br/>
choice - 3<br/>
There are 1 fragment(s).<br/>
<br/>
choice - 4<br/>
<br/>
P1 P1 P2 P2 P3 P3  P3  Free<br/>
Free Free Free Free Free Free Free Free<br/>
Free Free Free Free Free Free Free Free<br/>
Free Free Free Free Free Free Free Free<br/>
<br/>
choice - 2<br/>
Program name - P2<br/>
Program P2 successfully killed, 2 page(s) reclaimed.<br/>
<br/>
choice - 3<br/>
There are 2 fragment(s)<br/>
<br/>
choice - 5<br/>
