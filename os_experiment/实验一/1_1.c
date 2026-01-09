#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义进程控制块PCB
typedef struct pcb {
    int priority;//进程的优先级，采用动态优先级
    int needTime;//进程需要运行的时间
    int runTime;//进程已经运行的时间
    char name[10];//进程名
    int pid;//进程标识符PID
    struct pcb *link;//指针域
} pcb;

pcb *head = NULL;//就绪队列的头指针

//创建进程
pcb *createProcess(char *name, int pid, int priority, int needTime) {
    pcb *p = (pcb *)malloc(sizeof(pcb));
    strcpy(p->name, name);
    p->pid = pid;
    p->priority = priority;
    p->needTime = needTime;
    p->runTime = 0;
    p->link = NULL;
    return p;
}

//将进程添加到就绪队列中
void add(pcb *p) {
    if (head == NULL) {
        head = p;
    }
    else {
        pcb *curr = head;
        while (curr->link != NULL)
        {
            curr = curr->link;
        }
        curr->link = p;
    }
}

//获取队列中优先级最高的进程
pcb *get() {
    if (head == NULL) {
        return NULL;
    }
    pcb *highest = head;
    pcb *prev = NULL;
    pcb *curr = head;
    pcb *prevCurrent = NULL;
    while (curr != NULL) {
        if (curr->priority > highest->priority)
        {
            highest = curr;
            prev = prevCurrent;
        }
        prevCurrent = curr;
        curr = curr->link;
    }
    if (prev == NULL) { 
        head = highest->link;
    }
    else {
        prev->link = highest->link;
    }
    highest->link = NULL;
    return highest;
}

//展示进程当前状态
void showState(pcb *p) {
    printf("运行进程：%s (PID: %d), 优先级: %d, 已运行: %d / %d\n", p->name, p->pid, p->priority, p->runTime, p->needTime);
}

//进程调度，若进程在规定的时间片内未运行完，则该进程的优先级减1，并将该进程重新加入就绪队列中去
void run() {
    int time = 0;
    printf("开始运行所有进程\n");
    pcb *curr = head;
    while (head != NULL) {
        time++;
        printf("时间片: %d\n", time);
        pcb* curr = get();
        if(curr == NULL) {
            break;
        }
        curr->runTime++;
        showState(curr);
        if(curr->runTime >= curr->needTime) {
            printf("进程%s (PID: %d) 已完成\n", curr->name, curr->pid);
            free(curr);
        }
        else {
            curr->priority--;
            printf("在该时间片内进程%s (PID: %d)未完成, 优先级减为: %d, 重新加入就绪队列\n", curr->name, curr->pid, curr->priority);
            add(curr);
        }
    }
    printf("所有进程都已完成\n");
}

int main() {
    pcb* p1 = createProcess("p1", 1, 5, 3);
    pcb* p2 = createProcess("p2", 2, 3, 5);
    pcb* p3 = createProcess("p3", 3, 4, 2);
    pcb* p4 = createProcess("p4", 4, 6, 4);
    pcb* p5 = createProcess("p5", 5, 2, 1);

    add(p1);
    add(p2);
    add(p3);
    add(p4);
    add(p5);

    run();

    return 0;
}