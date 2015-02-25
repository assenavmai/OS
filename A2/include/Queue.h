#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"
#include "QStruct.h"

Node * Q_create();
void enqueue(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int arrival_time, int number_of_cpu, int cpu_time, int io_time, int thread_number);
int peek();

#endif