----------------------------------------------------------------------------------------------------
                                          README
----------------------------------------------------------------------------------------------------

Assignment 3
Vanessa White
0832498
March 27th, 2015

------------------
      PART 1
------------------

How to run:

cd to PartOne from A3 folder

Compile: make dine
Run: bin/dine 3 2

For my algorithm and pseudo code I got it from this site: http://functionspace.org/topic/129/Algorithms-for-Dining-philosophers-problem

It speaks of Tannenbaum's algorithm. It uses semaphores and threads for hte philosophers and includes a critical section. Tannenbaum's allows for no 2 adjacent philosophers to eat at the same time. This is because only one philospoher at a time can call a mutex to get a chopstick.which is simulated in the critical section. The philospohers are then allowed to grab a chopstick once given up by the previous philosopher. 

Assumptions:

Any amount of philosophers will not go over 1025
------------------
      PART 2
------------------



How to run:

cd to PartTwo from A3 folder

Compile: make holes
Run: bin/holes testfile

I used a Queue for my process queue and memory queue
    head is my process queue
    memory_head is my memory queue

They add to the end of the queue and removes from the front. 

Note: For every single algorithm, the process queue (head) is loaded in order of the file. So the first line will always be loaded in first, then the second etc.

First Fit:

Processes are loaded into memory from the front of the process queue. They are added into memory sequentially until there is not enough room for the process. To keep track of where I counted in the array the number '1' is being placed to mark it as visited. In this case, the oldest process is removed, which is the head of the memory queue. It will continue to remove memory until there is enough room to enter the process that is needed. 

Best Fit:

Processes are loaded into memory from the front of the process queue. The are added into memory sequentially until there is not enough room for the
process. In this case, the oldest process is removed from memory. Then, I check to see if there are any holes that are closer to the size of the process waiting to be loaded in to memory. Basically, find the smallest hole that is big enough to hold the process waiting. If there is one found, load the process into memory. If not, remove the oldest process. It will continue until there is enough memory to hold all the processes. Once that happens, the algorithm is done.

Worst Fit:

Same process as best fit. The change is that when there is more room needed for a process to be loaded into memory it checks for the smallest hole in size than can hold the process waiting. Once found, it will load the process. If not, it will continue to remove the oldest process in memory until it can fit.

Next Fit:

This is a variation of first fit. This time, the last index where a process was inserted into memory is kept track of. Processes are added starting at the last index if there is enough room for them. If not, the oldest process is removed. The last index is still at the last spot inserted. Also while iterating, if it reaches the last spot in the array it will go back to the starting position and start counting from scratch again. If at the last index there is a hole and the hole is not big enough to hold the process it will continue to iterate. If it find another hole that can fit it, then it will insert the process into that hole.


Assumptions Made:

%memusage = [(128 - current memory size) / 128] * 100

cumulative %mem = (sum of all %memusage / current amount of load) 

average #processes = (sum of #of processes during loading / # of loads)

average #holes = (summ of #of holes during loading / # of loads)

Memory is added and removed in the same order everytime, so calculations may be the same for each fit.
