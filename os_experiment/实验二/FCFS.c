#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct JCB {
    char name[10];
    int submitTime;
    int needTime;
    struct JCB* link;
} JCB;

JCB* head = NULL;

JCB* createJCB(char* name, int submitTime, int needTime) {
    JCB* p = (JCB*)malloc(sizeof(JCB));
    strcpy(p->name, name);
    p->submitTime = submitTime;
    p->needTime = needTime;
    p->link = NULL;
    return p;
}

void add(JCB* p) {
    if(head == NULL) {
        head = p;
    }
    else {
        JCB* curr = head;
        while (curr->link != NULL) {
            curr = curr->link;
        }
        curr->link = p;
    }
}

JCB* get() {
    if(head == NULL) {
        return NULL;
    }
    else {
        JCB* curr = head;
        head = curr->link;
        curr->link = NULL;
        return curr;
    }
}

void FCFS() {
    if (head == NULL) {
        printf("没有作业需要调度！\n");
        return;
    }

    JCB* curr;
    int currentTime = 0;        // 系统当前时间
    int totalTurnaround = 0;    // 总周转时间
    float totalWeighted = 0;    // 总带权周转时间
    int jobCount = 0;           // 作业总数

    while ((curr = get()) != NULL) {
        jobCount++;
        // 计算开始时间：取当前时间与作业提交时间的最大值
        int startTime = (curr->submitTime > currentTime) ? curr->submitTime : currentTime;
        // 计算完成时间
        int finishTime = startTime + curr->needTime;
        // 计算周转时间（完成时间 - 提交时间）
        int turnaround = finishTime - curr->submitTime;
        // 计算带权周转时间（周转时间 / 运行时间）
        float weighted = (float)turnaround / curr->needTime;
        printf("作业%s的开始时间为: %d, 完成时间为: %d, 周转时间为: %d, 带权周转时间为: %.2f\n", curr->name, startTime, finishTime, turnaround, weighted);
        totalTurnaround += turnaround;
        totalWeighted += weighted;
        currentTime = finishTime;
        JCB* temp = curr;
        free(temp);
    }
    printf("平均周转时间：%.2f\n", (float)totalTurnaround / jobCount);
    printf("带权平均周转时间：%.2f\n", totalWeighted / jobCount);
}

int main() {

    add(createJCB("J1", 0, 2));
    add(createJCB("J2", 1, 3));
    add(createJCB("J3", 2, 1));
    add(createJCB("J4", 4, 5));

    // 执行FCFS调度
    FCFS();
    return 0;
}