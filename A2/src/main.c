#include "PQueue.h"
#include "Queue.h"
#include <unistd.h>
#include <getopt.h>


void FCFS(int, int, Boolean, Boolean);
void RR(int quantum);

int main(int argc, char const *argv[])
{
    /*Declaring variables*/
    Node * process = malloc(sizeof(Node) * 100);
    Node * data;
    int threadNum;
    char line[1024];
    char * token;
    int i,j,k, lineCount, processNum, arguments;
    int quantum = 0;
    Boolean flagRR = false;
    /*Boolean flagFCFS = false;*/
    Boolean flagV = false;
    Boolean flagD = false;

    arguments = 0;

    /*parsing the command line*/
    if(argc == 1)
    {
        printf("\nFCFS\n");
        /*flagFCFS = true;*/
        /*FCFS();*/
    }
    else
    {
        while(++arguments< argc)
        {
            if(strcmp(argv[arguments], "-d") == 0)
            {
                flagD = true;
            }

            if(strcmp(argv[arguments], "-v") == 0)
            {
                flagV = true;
            }

            if(strcmp(argv[arguments], "-r") == 0)
            {
                printf("\nROUND ROBIN SIMULATION: NOT IMPLEMENTED\n");

                quantum = atoi(argv[arguments+1]);
                printf("\nRound Robin(quantum = 10 time units):\n");
                flagRR = true;
                /*RR(quantum);*/
            }
        }
    }

    /*Get first line and store it*/
    fgets(line, sizeof(line), stdin);

    token = strtok(line, " ");
    process[0].number_of_processes = atoi(token);
    token = strtok(NULL, " ");
    process[0].thread_switch = atoi(token);
    token = strtok(NULL, " ");
    process[0].process_switch = atoi(token);

    for(k = 1; k <= process[0].number_of_processes; k++)
    {
        lineCount = 0;

        /*Get the process number and the number of threads*/
        fgets(line, sizeof(line), stdin);
        token = strtok(line, " ");
        processNum = atoi(token);
        process[processNum].process_number = processNum;

        token = strtok(NULL, " ");
        process[processNum].number_of_threads= atoi(token);

        /*Get the cpu and io times*/
        for(i = 1; i <= process[processNum].number_of_threads; i++)
        {
            while(fgets(line, sizeof(line), stdin) != NULL)
            {
                if(lineCount == 0)
                {
                    token = strtok(line, " ");
                    threadNum = atoi(token);
                    process[processNum].info[threadNum].thread_number  = threadNum;
                    token = strtok(NULL, " ");
                    process[processNum].info[threadNum].arrival_time = atoi(token);
                    token = strtok(NULL, " ");
                    process[processNum].info[threadNum].number_of_cpu = atoi(token);
                    lineCount++;
                }
                else if(lineCount == 1)
                {

                    token = strtok(line, " ");
                    j = atoi(token);

                    token = strtok(NULL, " ");
                    process[processNum].info[threadNum].cpu_time[j] = atoi(token);

                    if(process[processNum].info[threadNum].number_of_cpu != j)
                    {
                        token = strtok(NULL, " ");
                        process[processNum].info[threadNum].io_time[j] = atoi(token);
                    }
                    else
                    {
                        process[processNum].info[threadNum].io_time[j] = 0;
                    }
                    
                    if(process[processNum].info[threadNum].number_of_cpu == j)
                    {
                        lineCount = 0;
                        break;
                    }
                }

            }
        }
    }

    lineCount = 0;

    /*Insert into the priority queue*/
    for(i = 1; i <= process[0].number_of_processes; i++)
    {
        
        for(j = 1; j <= process[i].number_of_threads; j++)
        {
            
            for(k = 1; k <= process[i].info[j].number_of_cpu; k++)
            {

                data = initNode(process[i].info[j].arrival_time, i, j, process[i].info[j].cpu_time[k], process[i].info[j].io_time[k], process[i].info[j].arrival_time, PROCESS_ARRIVES, k, process[i].info[j].number_of_cpu);
                insert(data);
               /* printf("Process %d Thread %d Arrival %d CPU Index %d\n", head->process_number, head->threadNum, head->info[head->threadNum].arrival_time, head->info[head->threadNum].currentBurst);
                head = head->next;*/
            }
        }
    }

    /*if round robin flag is true*/
    if(flagRR == true)
    {
        RR(quantum);
    }
    else
    {
        FCFS(process[0].thread_switch, process[0].process_switch, flagV, flagD);
    }

    free(process);

    return 0;
}

void RR(int quantum){
    int time = 0;
    int avgTurnaround = 0;
    double utilization = 0;

    printf("Total time required is %d time units\n", time);
    printf("Average Turnaround Time is %d time units\n", avgTurnaround);
    printf("CPU Utilization is %f\n", utilization);
}


void FCFS(int ts, int ps, Boolean v, Boolean d){
    Node * nextEvent = NULL;
    char * str;
    char verbose[1024];
    int clock = 0;
    int currBurst = 0;
    int threadNum = 0;
    int tArrival = 0;
    int ioArrival = 0;
    int cpuIdle = 0;
    int length = 0;
    double utilization = 0;
    double avgTurnaround = 0;

    str = malloc(sizeof(char) * 1024);
    length = len;

    strcat(str, "\n");
    while(!isEmpty())
    {
        /*get head then pop it off*/
        nextEvent = head;
        dequeue();

        if(clock < tArrival)
        {
            cpuIdle += (tArrival - clock);
            clock = tArrival;
        }

        switch(nextEvent->type)
        {
            case PROCESS_ARRIVES:
                tArrival = nextEvent->info[threadNum].arrival_time;
                threadNum = nextEvent->threadNum;
                currBurst = nextEvent->info[threadNum].currentBurst;

                nextEvent->start = clock;
                clock += nextEvent->info[threadNum].cpu_time[currBurst];
                nextEvent->finish = clock;

                if(v == true)
                {
                    sprintf(verbose, "At time %d: Thread: %d of Process %d moves from new to ready state\n", clock, threadNum, nextEvent->process_number);
                    strcat(str, verbose);
                }

                /*calculate turnaround time*/
                nextEvent->turnaround = nextEvent->finish - nextEvent -> start;

                /*calculate total avg turnaround*/
                avgTurnaround += nextEvent->finish - nextEvent->start;

                ioArrival = nextEvent->info[threadNum].io_time[currBurst] + clock;
                nextEvent->info[threadNum].arrival_time = ioArrival;
                nextEvent->type = IO_READY;

                tArrival = nextEvent->info[threadNum].arrival_time;
                insert(nextEvent);

                /*detailed*/
                if(d == true)
                {
                    printf("\nThread %d of Process %d: \n", threadNum, nextEvent->process_number);

                    printf("\narrival time: %d\n", nextEvent->start);
                    printf("service time: %d\n", nextEvent->info[threadNum].cpu_time[currBurst]);
                    printf("I/O time: %d\n", nextEvent->info[threadNum].io_time[currBurst]);
                    printf("turnaround time: %d\n", nextEvent->turnaround);
                    printf("finish time: %d\n\n", nextEvent->finish);
                }

                /*verbose mode*/
                if(v == true)
                {
                    sprintf(verbose, "At time %d: Thread: %d of Process %d moves from new to blocked state\n", clock, threadNum, nextEvent->process_number);
                    strcat(str, verbose);
                }

                
            break;

            case IO_READY:
                nextEvent->type = PROCESS_TERMINATION;
                clock += ts;
                clock += ps;
                insert(nextEvent);
                if(v == true)
                {
                    sprintf(verbose, "At time %d: Thread: %d of Process %d moves from blocked to terminated state\n", clock, threadNum, nextEvent->process_number);
                    strcat(str, verbose);
                }
                break;

            case PROCESS_TERMINATION:
                break;

        }
    }

    /*print out verbose mode*/
    if(v == true)
    {
        printf("%s\n", str);
    }

    printf("Total time required is %d time units\n", clock);
    avgTurnaround = avgTurnaround / length;
    printf("Average Turnaround Time is %.2f time units\n", avgTurnaround);
    utilization = (((double)clock - (double)cpuIdle) / (double)clock) * 100.0;
    printf("CPU Utilization is %.2f\n", utilization);
    


}