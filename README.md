# OS

Course Code: CIS3110
University of Guelph
Instructor: Xining Li

This repository consists of the assignments done in my Operating Systems I class. 

Assignment 4:

Dining Philosophers and Memory Management Simulator.

--------------------
Dining Philosopher
--------------------

Uses Tannebaum's algorithm which consists the use of pthreads and semaphores. 

Compile: make dine
Run: ./dine [# of philosophers][max times a philosopher can eat]
For example: ./dine 3 2 means that there are 3 philosophers and each can only eat two times.

-----------------------------
Memory management simulator
-----------------------------

Implements:

  Best Fit
  Worst Fit
  Next Fit
  Best Fit
