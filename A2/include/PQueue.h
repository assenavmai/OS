#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"
#include "QStruct.h"


void insert(Node *);
void dequeue();
Boolean isEmpty();
int peek();
void IOinsert(Node * readyEvent);
#endif