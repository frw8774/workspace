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
        while(curr->link != NULL) {
            curr = curr->link;
        }
        curr->link = p;
    }
}

JCB* get(int currentTime) {
    JCB* p = head;
    JCB* highestJob = NULL;  // 记录响应比最高的作业
    JCB* prev = NULL;        // 遍历指针的前驱
    JCB* prevHighest = NULL; // 最高响应比作业的前驱
    float maxRatio = -1.0;   // 记录最大响应比（初始为负数，确保能被覆盖）

    // 遍历所有作业，筛选已提交且计算响应比
    while (p != NULL) {
        // 仅考虑已提交的作业（提交时间 <= 当前系统时间）
        if (p->submitTime <= currentTime) {
            // 计算等待时间
            int waitTime = currentTime - p->submitTime;
            // 计算响应比：1 + 等待时间/服务时间
            float responseRatio = 1.0 + (float)waitTime / p->needTime;

            // 更新最高响应比作业
            if (responseRatio > maxRatio) {
                maxRatio = responseRatio;
                highestJob = p;
                prevHighest = prev;
            }
        }
        prev = p;
        p = p->link;
    }

    // 如果找到最高响应比作业，将其从链表中移除
    if (highestJob != NULL) {
        if (prevHighest == NULL) {
            // 最高响应比作业是头节点
            head = highestJob->link;
        } else {
            // 最高响应比作业是中间或尾部节点
            prevHighest->link = highestJob->link;
        }
        highestJob->link = NULL;
    }

    return highestJob;
}

// HRRN调度核心逻辑
void HRRN() {
    int currentTime = 0;     // 当前系统时间
    int jobCount = 0;        // 作业总数
    float totalTurnaround = 0.0;    // 总周转时间
    float totalWeightedTurn = 0.0;  // 总带权周转时间

    // 先统计作业总数
    JCB* temp = head;
    while (temp != NULL) {
        jobCount++;
        temp = temp->link;
    }
    // 循环调度，直到所有作业处理完毕
    while (head != NULL) {
        // 获取当前已提交作业中响应比最高的作业
        JCB* currentJob = get(currentTime);
        // 如果没有已提交作业，推进时间到下一个作业的提交时间
        if (currentJob == NULL) {
            // 找到下一个作业的提交时间
            JCB* nextJob = head;
            int nextSubmitTime = nextJob->submitTime;
            while (nextJob != NULL) {
                if (nextJob->submitTime < nextSubmitTime) {
                    nextSubmitTime = nextJob->submitTime;
                }
                nextJob = nextJob->link;
            }
            currentTime = nextSubmitTime;  // 时间推进到下一个作业提交
            continue;
        }

        // 计算作业的开始时间、完成时间
        int startTime = currentTime;
        int finishTime = startTime + currentJob->needTime;
        // 计算周转时间（完成时间 - 提交时间）
        int turnaroundTime = finishTime - currentJob->submitTime;
        // 计算带权周转时间（周转时间 / 服务时间）
        float weightedTurn = (float)turnaroundTime / currentJob->needTime;

        // 累加总时间
        totalTurnaround += turnaroundTime;
        totalWeightedTurn += weightedTurn;

        // 打印当前作业信息
        printf("作业%s的提交时间为: %d, 需要系统提供服务的时间为: %d, 开始时间: %d, 完成时间: %d, 周转时间: %d, 带权周转时间: %.2f\n",
               currentJob->name,
               currentJob->submitTime,
               currentJob->needTime,
               startTime,
               finishTime,
               turnaroundTime,
               weightedTurn);

        // 更新系统当前时间为作业完成时间
        currentTime = finishTime;

        // 释放当前作业内存
        free(currentJob);
    }

    // 打印平均时间指标
    printf("\n调度统计结果: \n");
    printf("平均周转时间: %.2f\n", totalTurnaround / jobCount);
    printf("带权平均周转时间: %.2f\n", totalWeightedTurn / jobCount);
}

int main() {
    add(createJCB("J1", 0, 4));
    add(createJCB("J2", 2, 3));
    add(createJCB("J3", 4, 1));
    add(createJCB("J4", 5, 2));
    add(createJCB("J5", 6, 5));

    HRRN();
    return 0;
}