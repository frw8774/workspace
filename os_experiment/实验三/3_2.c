#include <stdio.h>
#include <stdlib.h>

// 定义空闲分区结构体（链表节点）
typedef struct FreeBlock {
    int id;             // 分区编号
    int start_addr;     // 分区起始地址
    int size;           // 分区大小
    int status;         // 分区状态：0-空闲，1-占用
    struct FreeBlock *next; // 链表后继指针
} FreeBlock;

// 全局变量：记录上次分配的分区位置（循环首次适应算法核心）
FreeBlock *last_alloc = NULL;
// 全局变量：记录分区编号自增（避免重复）
int global_block_id = 1;

// 创建新分区节点
FreeBlock* create_block(int id, int start_addr, int size, int status) {
    FreeBlock *new_block = (FreeBlock*)malloc(sizeof(FreeBlock));
    if (new_block == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    new_block->id = id;
    new_block->start_addr = start_addr;
    new_block->size = size;
    new_block->status = status;
    new_block->next = NULL;
    return new_block;
}

// 初始化空闲分区链（默认初始一个1024大小的空闲分区）
void init_partition(FreeBlock **head) {
    // 释放原有链表（避免重复初始化内存泄漏）
    FreeBlock *temp = *head;
    while (temp != NULL) {
        FreeBlock *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    last_alloc = NULL;
    global_block_id = 1;

    // 创建初始空闲分区
    *head = create_block(global_block_id++, 0, 1024, 0);
    printf("分区初始化成功！初始空闲分区：起始地址0，大小1024\n");
}

// 循环首次适应算法：分配分区
int allocate_partition(FreeBlock **head, int req_size, int *alloc_id, int *alloc_start) {
    if (req_size <= 0 || *head == NULL) {
        printf("无效的申请大小或分区未初始化！\n");
        return 0; // 分配失败
    }

    // 确定查找起始点：上次分配的下一个分区（首次为链表头）
    FreeBlock *current = (last_alloc == NULL) ? *head : last_alloc->next;
    FreeBlock *search_start = current; // 记录查找起点，避免无限循环

    // 循环遍历空闲分区链
    do {
        // 找到空闲且大小满足要求的分区
        if (current->status == 0 && current->size >= req_size) {
            // 情况1：分区大小恰好等于申请大小，直接标记为占用
            if (current->size == req_size) {
                current->status = 1;
                *alloc_id = current->id;
                *alloc_start = current->start_addr;
                last_alloc = current; // 更新上次分配位置
                printf("分配成功！分区编号：%d，起始地址：%d，分配大小：%d\n",
                       *alloc_id, *alloc_start, req_size);
                return 1;
            }
            // 情况2：分区大小大于申请大小，分割为占用分区和空闲分区
            else {
                // 创建新的空闲分区（分割后的剩余部分）
                FreeBlock *new_free = create_block(global_block_id++, 
                                                  current->start_addr + req_size,
                                                  current->size - req_size, 0);
                // 插入新分区到链表中
                new_free->next = current->next;
                current->next = new_free;
                // 更新当前分区为占用状态（大小改为申请大小）
                current->size = req_size;
                current->status = 1;
                *alloc_id = current->id;
                *alloc_start = current->start_addr;
                last_alloc = current; // 更新上次分配位置
                printf("分配成功！分区编号：%d，起始地址：%d，分配大小：%d\n",
                       *alloc_id, *alloc_start, req_size);
                return 1;
            }
        }
        // 继续遍历下一个分区（循环到链表头）
        current = (current->next == NULL) ? *head : current->next;
    } while (current != search_start); // 遍历一圈后未找到则退出

    // 遍历完所有分区未找到合适的
    printf("无足够大的空闲分区，分配失败！\n");
    return 0;
}

// 分区回收：合并相邻空闲分区（避免内存碎片）
int free_partition(FreeBlock **head, int free_id) {
    if (*head == NULL) {
        printf("分区未初始化！\n");
        return 0;
    }

    FreeBlock *target = *head;   // 待回收分区
    FreeBlock *prev = NULL;      // 待回收分区的前驱
    // 查找待回收的分区
    while (target != NULL && target->id != free_id) {
        prev = target;
        target = target->next;
    }

    // 未找到分区或分区已空闲
    if (target == NULL) {
        printf("不存在编号为%d的分区！\n", free_id);
        return 0;
    }
    if (target->status == 0) {
        printf("编号为%d的分区已处于空闲状态！\n", free_id);
        return 0;
    }

    // 1. 标记当前分区为空闲
    target->status = 0;
    printf("开始回收编号为%d的分区...\n", free_id);

    // 2. 合并后继空闲分区（如果存在）
    FreeBlock *next_block = target->next;
    if (next_block != NULL && next_block->status == 0) {
        target->size += next_block->size; // 合并大小
        FreeBlock *temp = next_block;
        target->next = next_block->next;  // 跳过后继分区
        free(temp); // 释放后继分区节点
        printf("合并后继空闲分区成功！\n");
    }

    // 3. 合并前驱空闲分区（如果存在）
    if (prev != NULL && prev->status == 0) {
        prev->size += target->size; // 合并大小
        prev->next = target->next;  // 跳过当前分区
        free(target); // 释放当前分区节点
        printf("合并前驱空闲分区成功！\n");
    }

    printf("分区回收完成！\n");
    return 1;
}

// 打印当前所有分区状态
void print_partition(FreeBlock *head) {
    if (head == NULL) {
        printf("暂无分区信息！\n");
        return;
    }
    printf("\n==================== 分区状态 ====================\n");
    printf("分区编号\t起始地址\t分区大小\t分区状态\n");
    printf("----------------------------------------------------\n");
    FreeBlock *current = head;
    while (current != NULL) {
        char *status = (current->status == 0) ? "空闲" : "占用";
        printf("%d\t\t%d\t\t%d\t\t%s\n",
               current->id, current->start_addr, current->size, status);
        current = current->next;
    }
    printf("====================================================\n\n");
}

// 释放所有分区内存
void free_all_partition(FreeBlock **head) {
    FreeBlock *temp = *head;
    while (temp != NULL) {
        FreeBlock *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    last_alloc = NULL;
}

// 主函数：菜单交互
int main() {
    FreeBlock *head = NULL;
    int choice, req_size, free_id, alloc_id, alloc_start;

    while (1) {
        printf("\n===== 可变式分区管理（循环首次适应算法）=====\n");
        printf("1. 初始化分区\n");
        printf("2. 分配分区\n");
        printf("3. 回收分区\n");
        printf("4. 查看分区状态\n");
        printf("5. 退出程序\n");
        printf("===============================================\n");
        printf("请输入操作选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                init_partition(&head);
                break;
            case 2:
                printf("请输入需要分配的内存大小：");
                scanf("%d", &req_size);
                if (allocate_partition(&head, req_size, &alloc_id, &alloc_start)) {
                    // 分配成功，无需额外操作（分配函数已打印信息）
                }
                break;
            case 3:
                printf("请输入需要回收的分区编号：");
                scanf("%d", &free_id);
                free_partition(&head, free_id);
                break;
            case 4:
                print_partition(head);
                break;
            case 5:
                free_all_partition(&head);
                printf("程序已退出，内存已释放！\n");
                exit(0);
            default:
                printf("无效的选择，请重新输入！\n");
                break;
        }
    }
    return 0;
}