#include <stdio.h>

typedef struct Table {
    int size;//大小（KB）
    int start;//始址
    int flag;//状态，表示是否分配，已分配为1，未分配为0
} Table;

Table part[5];

// 初始化分区表（预设5个固定分区）
void initPart() {
    // 分区大小和始址按连续不重叠方式设置
    part[0] = (Table){100, 0, 0};     // 分区0：100KB，始址0
    part[1] = (Table){200, 100, 0};   // 分区1：200KB，始址100
    part[2] = (Table){500, 300, 0};   // 分区2：500KB，始址300
    part[3] = (Table){300, 800, 0};   // 分区3：300KB，始址800
    part[4] = (Table){400, 1100, 0};  // 分区4：400KB，始址1100
}

void display() {
    for(int i = 0;i < 5;i++) {
        printf("分区号: %d, 大小: %d, 始址: %d, 状态: %d\n", i, part[i].size, part[i].start, part[i].flag);
    }
}

void allocate() {
    int needSize;
    printf("请输入作业所需内存大小(KB):");
    scanf("%d", &needSize);

    if (needSize <= 0) {
        printf("错误：内存大小必须为正数！\n");
        return;
    }

    // 遍历分区表，找到第一个未分配且足够大的分区
    for (int i = 0; i < 5; i++) {
        if (part[i].flag == 0 && part[i].size >= needSize) {
            part[i].flag = 1;
            printf("分配成功！使用分区号：%d\n", i);
            return;
        }
    }

    // 无合适分区
    printf("分配失败：没有足够大的未分配分区！\n");
}

void recycle() {
    int partNumber;
    printf("请输入要回收的分区号：");
    scanf("%d", &partNumber);

    // 检查分区号合法性
    if (partNumber < 0 || partNumber >= 5) {
        printf("错误：分区号不存在！\n");
        return;
    }

    // 检查分区状态
    if (part[partNumber].flag == 0) {
        printf("错误：该分区未分配，无需回收！\n");
        return;
    }

    // 执行回收
    part[partNumber].flag = 0;
    printf("回收成功！分区号：%d\n", partNumber);
}

int main() {
    int choice;
    initPart();

    do {
        printf("\n===== 固定分区存储管理模拟 =====");
        printf("\n1. 显示分区表");
        printf("\n2. 分配内存");
        printf("\n3. 回收内存");
        printf("\n4. 退出程序");
        printf("\n请选择操作(1-4):");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display();
            break;
        case 2:
            allocate();
            break;
        case 3:
            recycle();
            break;
        case 4:
            printf("程序已退出！\n");
            break;
        default:
            printf("错误:请输入1-4之间的数字!\n");
        }
    } while (choice != 4);

    return 0;
}