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
    if (head == NULL) {
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

JCB* get(int currentTime) {
    JCB* p = head;
    JCB* shortest = NULL;
    JCB* prev = NULL;
    JCB* prevShortest = NULL;

    // 先找到第一个已到达的作业作为初始最短作业
    while (p != NULL) {
        if (p->submitTime <= currentTime) {
            shortest = p;
            prevShortest = prev;
            break;
        }
        prev = p;
        p = p->link;
    }

    // 如果没有已到达的作业，返回NULL（此时系统可能需要等待，直到有作业提交）
    if (shortest == NULL) return NULL;

    // 继续遍历，从所有已到达的作业中找最短的
    prev = p;  // p此时是第一个已到达作业的下一个节点
    p = p->link;
    while (p != NULL) {
        if (p->submitTime <= currentTime && p->needTime < shortest->needTime) {
            shortest = p;
            prevShortest = prev;
        }
        prev = p;
        p = p->link;
    }

    // 从链表中移除选中的作业
    if (prevShortest == NULL) {
        head = shortest->link;
    } else {
        prevShortest->link = shortest->link;
    }
    shortest->link = NULL;

    return shortest;
}

void SJF() {
    int currentTime = 0;
    int jobCount = 0;
    float totalTurnaround = 0;
    float totalWeighted = 0;

    JCB* curr;
    // 循环获取已到达的最短作业，直到所有作业完成
    while (1) {
        curr = get(currentTime);
        if (curr == NULL) {
            // 没有已到达的作业，需要检查是否还有未处理的作业，有的话推进时间到下一个作业的提交时间
            if (head == NULL) break;  // 所有作业都已处理，退出
            // 找到下一个作业的提交时间，推进currentTime
            JCB* temp = head;
            int nextSubmit = temp->submitTime;
            while (temp != NULL) {
                if (temp->submitTime < nextSubmit) {
                    nextSubmit = temp->submitTime;
                }
                temp = temp->link;
            }
            currentTime = nextSubmit;
            continue;
        }

        jobCount++;
        int startTime = currentTime;  // 此时curr已到达，startTime就是currentTime
        int finishTime = startTime + curr->needTime;
        int turnaround = finishTime - curr->submitTime;
        float weighted = (float)turnaround / curr->needTime;
        printf("作业%s的开始时间为: %d, 完成时间为: %d, 周转时间为: %d, 带权周转时间为: %.2f\n", 
               curr->name, startTime, finishTime, turnaround, weighted);
        totalTurnaround += turnaround;
        totalWeighted += weighted;
        currentTime = finishTime;
        free(curr);
    }

    printf("平均周转时间：%.2f\n", (float)totalTurnaround / jobCount);
    printf("带权平均周转时间：%.2f\n", totalWeighted / jobCount);
}

int main() {
    add(createJCB("J1", 0, 4));
    add(createJCB("J2", 2, 3));
    add(createJCB("J3", 4, 1));
    add(createJCB("J4", 5, 2));

    SJF();

    return 0;
}