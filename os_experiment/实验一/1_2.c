#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//PCB的定义
typedef struct pcb {
    char name[10];//进程名
    int pid;//进程标识符
    int needTime;//进程需要运行的时间
    int runTime;//进程已经运行的时间
    struct pcb* link;//指针域
} pcb;

pcb* head = NULL;//就绪队列头指针

//创建进程
pcb *createProcess(char *name, int pid, int needTime) {
    pcb *p = (pcb *)malloc(sizeof(pcb));
    strcpy(p->name, name);
    p->pid = pid;
    p->needTime = needTime;
    p->runTime = 0;
    p->link = NULL;
    return p;
}

//添加进程到就绪队列中
void add(pcb* p) {
    if(head == NULL) {
        head = p;
    }
    else {
        pcb* curr = head;
        while(curr->link != NULL) {
            curr = curr->link;
        }
        curr->link = p;
    }
}

//获取就绪队列头部的进程
pcb* get() {
    if(head == NULL) {
        return NULL;
    }
    pcb* curr = head;
    head = head->link;
    curr->link = NULL;
    return curr;
}

void showState(pcb* p) {
    printf("运行进程：%s (PID: %d), 已运行: %d / %d\n", p->name, p->pid, p->runTime, p->needTime);
}

//进程的调度,按照FCFS每次取就绪队列最前端的进程运行
void run() {
    int totalTime = 0;
    int timePiece = 2;
    printf("开始运行所有进程\n");
    while(head != NULL) {
        pcb* curr = get();
        if(curr == NULL) {
            break;
        }

        //计算进程的用时
        int runtime = (curr->needTime - curr->runTime) < timePiece ? (curr->needTime - curr->runTime) : timePiece;
        curr->runTime += runtime;
        totalTime += runtime;
        showState(curr);
        if(curr->runTime == curr->needTime) {
            printf("进程%s (PID: %d) 已完成, 累计用时: %d\n", curr->name, curr->pid, totalTime);
            free(curr);
        }
        else {
            add(curr);
        }
    }
    printf("所有进程已完成, 总用时: %d\n", totalTime);
}

int main() {
    pcb* p1 = createProcess("p1", 1, 3);
    pcb* p2 = createProcess("p2", 2, 5);
    pcb* p3 = createProcess("p3", 3, 2);
    pcb* p4 = createProcess("p4", 4, 7);
    pcb* p5 = createProcess("p5", 5, 4);

    add(p1);
    add(p2);
    add(p3);
    add(p4);
    add(p5);

    run();
    return 0;
}