#ifndef HOLES_H
#define HOLES_H

#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Boolean.h"

void readFile(const char *str);
void firstFit(const char *str);
void bestFit(const char *str);
void worstFit(const char *str);
void nextFit(const char *str);
void insertIntoMemory();
void removeFromMemory();
int countHoles();
float getCumulative(int currLoads);
float calculateMemUsage(int memsize);
void clearMemory();
void read(const char *str);

#endif