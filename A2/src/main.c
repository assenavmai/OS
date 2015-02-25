#include "PQueue.h"
#include "Queue.h"
#include <unistd.h>
#include <getopt.h>

int main(int argc, char const *argv[])
{
    Node process[10];
   /* Thread thread[51];*/
   /* FILE * f;*/
    Boolean isDFlag, isVFlag, isRFlag;
    char line[1024];
    char * token;
    int i,j,k, n, lineCount, processNum, quantum;

    isRFlag = false;
    isVFlag = false;
    isDFlag = false;

    /*while((opt = getopt(argc, argv, "dvr")) != -1)
    {
        switch(opt)
        {
            case 'd':
                printf("detail\n");
                break;
            case 'r':
                printf("robin\n");
                break;
            case 'v':
                printf("v flag\n");
                break;
        }   
    }*/
    /*f = fopen("t1.txt", "r");

    if(f == NULL)
    {
        fprintf(stderr, "%s\n", "Error opening file: main.c, line 12.");
        exit(1);
    }*/

    if(argc == 1)
    {
        printf("\nFCFS Scheduling.\n");
        exit(1);
    }
    if(argc == 4)
    {
        isDFlag = true;
        isVFlag = true;
    }
    if(argc > 1)
    {
        printf("boom %s\n", argv[1]);
        printf("boom %s\n", argv[2]);
        printf("boom %s\n", argv[3]);

        for(n = 1; n < 5; n++)
        {
            if(strcmp(argv[n], "-d") == 0)
            {
                isDFlag = true;
            }
            if(strcmp(argv[n], "-r") == 0 && strcmp(argv[n+1], ))
            {
                printf("robin\n");
            }
            if(strcmp(argv[n], "-v") == 0)
            {
                printf("vermacose\n");
            }
        }
    }
    
    fgets(line, sizeof(line), stdin);

    token = strtok(line, " ");
    process[0].number_of_processes = atoi(token);
    token = strtok(NULL, " ");
    process[0].thread_switch = atoi(token);
    token = strtok(NULL, " ");
    process[0].process_switch = atoi(token);


    printf("\n\t\tNumber of Processes: %d\n", process[0].number_of_processes);
    printf("\t\tThread Switch: \t%d\n", process[0].thread_switch);
    printf("\t\tProcess Switch: %d\n", process[0].process_switch);

    for(k = 1; k <= process[0].number_of_processes; k++)
    {
        lineCount = 0;

        fgets(line, sizeof(line), stdin);
        token = strtok(line, " ");
        processNum = atoi(token);
        process[processNum].process_number = processNum;

        token = strtok(NULL, " ");
        process[processNum].number_of_threads= atoi(token);

        printf("\n\t\tProcess Number: %d\n", process[processNum].process_number);
        printf("\t\tNumber of Threads: %d\n", process[processNum].number_of_threads);

        for(i = 1; i <= process[processNum].number_of_threads; i++)
        {
            while(fgets(line, sizeof(line), stdin) != NULL)
            {
                if(lineCount == 0)
                {
                    token = strtok(line, " ");
                    process[processNum].info.thread_number = atoi(token);
                    token = strtok(NULL, " ");
                    process[processNum].info.arrival_time = atoi(token);
                    token = strtok(NULL, " ");
                    process[processNum].info.number_of_cpu = atoi(token);
                    printf("\nThread Number: %d\n", process[processNum].info.thread_number);
                    printf("Arrival Time: %d\n", process[processNum].info.arrival_time);
                    printf("Number of CPU: %d\n", process[processNum].info.number_of_cpu);
                    lineCount++;
                }
                else if(lineCount == 1)
                {

                    token = strtok(line, " ");
                    j = atoi(token);

                    token = strtok(NULL, " ");
                    process[processNum].info.cpu_time[j] = atoi(token);

                    if(process[processNum].info.number_of_cpu != j)
                    {
                        token = strtok(NULL, " ");
                        process[processNum].info.io_time[j] = atoi(token);
                    }
                    else
                    {
                        process[processNum].info.io_time[j] = 0;
                    }
                    
                    printf("\nCpu time %d\n", process[processNum].info.cpu_time[j]);
                    printf("IO time %d\n", process[processNum].info.io_time[j]);
                    
                    if(process[processNum].info.number_of_cpu == j)
                    {
                        lineCount = 0;
                        break;
                    }
                }

            }
        }
    }

    return 0;
}