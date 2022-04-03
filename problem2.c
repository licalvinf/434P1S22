#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("A begins\n");
    int a = getpid();
    int b;
    int c;
    int d;
    int tpid;
    printf("Process A forks to B\n");
    b = fork();
    
    if(b == 0){
        printf("B begins\n");
        printf("B goes to sleep for 30 seconds\n");
        sleep(30);
        printf("B returns with code 4\n");
        _exit(4);
    }
    else if (b>0){
        printf("Process A forks to C\n");
        c = fork();
        if (c == 0){
            printf("C begins\n");
            printf("Process C forks to D\n");
            d = fork();
            if(d ==0){
                printf("D begins\n");
                printf("D goes to sleep for 30 seconds\n");
                sleep(30);
                printf("D returns with code 10\n");
                _exit(10);
            }
            else if(d>0){
                printf("Process C waiting for process D to terminate\n");
                tpid = wait(NULL);
                printf("Process C has received terminating signal %d\n", tpid);
                printf("C returns with code 6\n");
                _exit(6);
            }
        }
        else if (c>0){
            printf("Process A waiting for process B and C to terminate\n");
            tpid = wait(NULL);
            printf("Process A has received terminating signal %d\n", tpid);
            tpid = wait(NULL);
            printf("Process A has received terminating signal %d\n", tpid);
            printf("A returns with code 2\n");
            exit(2);
        }
    }

    return 0;
}