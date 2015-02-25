#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"
#include "QStruct.h"


Node * create();
void insert(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int number_of_threads, Thread * info);
void display();
void makeEmpty();

#endif