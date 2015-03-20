#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"
#include "QStruct.h"

Node * Q_create();
void enqueue(int process_number, int thread_number, int cpu_time, int io_time, int arrival_time, type_t type, int index, int number_of_cpu);
void Q_dequeue();
void Q_insert(Node *);
Boolean Q_isEmpty();
#endif