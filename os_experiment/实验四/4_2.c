#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USER 10
#define MAX_FILE_PER_USER 10
#define MAX_OPEN_FILE 5

// 数据结构同实验题1
typedef struct UFDItem {
    char fileName[20];
    char perm[4];
    int fileLen;
    int readPtr;
    int isUsed;
} UFDItem;

typedef struct MFDItem {
    char userName[20];
    UFDItem ufd[MAX_FILE_PER_USER];
    int isUsed;
} MFDItem;

typedef struct AFDItem {
    char userName[20];
    char fileName[20];
    char perm[4];
    int readPtr;
    UFDItem *ufdPtr;
    int isUsed;
} AFDItem;

// 全局变量
MFDItem mfd[MAX_USER];
AFDItem afd[MAX_OPEN_FILE];
char currentUser[20];

// 初始化函数（同实验题1）
void initFS() {
    for (int i = 0; i < MAX_USER; i++) {
        mfd[i].isUsed = 0;
        memset(mfd[i].userName, 0, sizeof(mfd[i].userName));
        for (int j = 0; j < MAX_FILE_PER_USER; j++) {
            mfd[i].ufd[j].isUsed = 0;
            memset(mfd[i].ufd[j].fileName, 0, sizeof(mfd[i].ufd[j].fileName));
            memset(mfd[i].ufd[j].perm, '0', 3);
            mfd[i].ufd[j].perm[3] = '\0';
            mfd[i].ufd[j].fileLen = 0;
            mfd[i].ufd[j].readPtr = 0;
        }
    }
    for (int i = 0; i < MAX_OPEN_FILE; i++) {
        afd[i].isUsed = 0;
        memset(afd[i].userName, 0, sizeof(afd[i].userName));
        memset(afd[i].fileName, 0, sizeof(afd[i].fileName));
        memset(afd[i].perm, '0', 3);
        afd[i].perm[3] = '\0';
        afd[i].readPtr = 0;
        afd[i].ufdPtr = NULL;
    }
    strcpy(mfd[0].userName, "user1");
    mfd[0].isUsed = 1;
    strcpy(currentUser, "user1");
}

// 辅助查找函数（同实验题1）
MFDItem* findCurrentUser() {
    for (int i = 0; i < MAX_USER; i++) {
        if (mfd[i].isUsed && strcmp(mfd[i].userName, currentUser) == 0) {
            return &mfd[i];
        }
    }
    return NULL;
}

UFDItem* findFileInUFD(const char* fileName) {
    MFDItem *user = findCurrentUser();
    if (!user) return NULL;
    for (int i = 0; i < MAX_FILE_PER_USER; i++) {
        if (user->ufd[i].isUsed && strcmp(user->ufd[i].fileName, fileName) == 0) {
            return &user->ufd[i];
        }
    }
    return NULL;
}

AFDItem* findFileInAFD(const char* fileName) {
    for (int i = 0; i < MAX_OPEN_FILE; i++) {
        if (afd[i].isUsed && strcmp(afd[i].userName, currentUser) == 0 && strcmp(afd[i].fileName, fileName) == 0) {
            return &afd[i];
        }
    }
    return NULL;
}

// 核心功能函数（同实验题1，省略重复代码，仅保留声明）
void createFile(const char* fileName, const char* perm);
void deleteFile(const char* fileName);
void openFile(const char* fileName);
void closeFile(const char* fileName);
void readFile(const char* fileName, int len);
void writeFile(const char* fileName, int len);
void lseekFile(const char* fileName, int offset);
void changeFileName(const char* oldName, const char* newName);
void changePerm(const char* fileName, const char* newPerm);

// 实现核心功能函数（同实验题1）
void createFile(const char* fileName, const char* perm) {
    if (strlen(perm) != 3) { printf("错误：保护码必须是3位（rwx，0/1）\n"); return; }
    MFDItem *user = findCurrentUser();
    if (!user) { printf("错误：当前用户未登录\n"); return; }
    if (findFileInUFD(fileName)) { printf("错误：文件%s已存在\n", fileName); return; }
    for (int i = 0; i < MAX_FILE_PER_USER; i++) {
        if (!user->ufd[i].isUsed) {
            strcpy(user->ufd[i].fileName, fileName);
            strcpy(user->ufd[i].perm, perm);
            user->ufd[i].fileLen = 0;
            user->ufd[i].readPtr = 0;
            user->ufd[i].isUsed = 1;
            printf("成功创建文件：%s\n", fileName);
            return;
        }
    }
    printf("错误：用户文件数已达上限\n");
}

void deleteFile(const char* fileName) {
    UFDItem *file = findFileInUFD(fileName);
    if (!file) { printf("错误：文件%s不存在\n", fileName); return; }
    if (findFileInAFD(fileName)) { printf("错误：文件%s正在打开中\n", fileName); return; }
    file->isUsed = 0;
    printf("成功删除文件：%s\n", fileName);
}

void openFile(const char* fileName) {
    UFDItem *file = findFileInUFD(fileName);
    if (!file) { printf("错误：文件%s不存在\n", fileName); return; }
    if (findFileInAFD(fileName)) { printf("错误：文件%s已打开\n", fileName); return; }
    for (int i = 0; i < MAX_OPEN_FILE; i++) {
        if (!afd[i].isUsed) {
            strcpy(afd[i].userName, currentUser);
            strcpy(afd[i].fileName, fileName);
            strcpy(afd[i].perm, file->perm);
            afd[i].readPtr = file->readPtr;
            afd[i].ufdPtr = file;
            afd[i].isUsed = 1;
            printf("成功打开文件：%s\n", fileName);
            return;
        }
    }
    printf("错误：打开文件数已达上限\n");
}

void closeFile(const char* fileName) {
    AFDItem *afdItem = findFileInAFD(fileName);
    if (!afdItem) { printf("错误：文件%s未打开\n", fileName); return; }
    afdItem->ufdPtr->readPtr = afdItem->readPtr;
    afdItem->isUsed = 0;
    printf("成功关闭文件：%s\n", fileName);
}

void readFile(const char* fileName, int len) {
    AFDItem *afdItem = findFileInAFD(fileName);
    if (!afdItem) { printf("错误：文件%s未打开\n", fileName); return; }
    if (afdItem->perm[0] != '1') { printf("错误：无读取权限\n"); return; }
    if (afdItem->readPtr + len > afdItem->ufdPtr->fileLen) {
        len = afdItem->ufdPtr->fileLen - afdItem->readPtr;
        printf("警告：已到文件末尾，实际读取：%d字节\n", len);
    }
    afdItem->readPtr += len;
    printf("成功读取%s：%d字节，当前指针：%d\n", fileName, len, afdItem->readPtr);
}

void writeFile(const char* fileName, int len) {
    AFDItem *afdItem = findFileInAFD(fileName);
    if (!afdItem) { printf("错误：文件%s未打开\n", fileName); return; }
    if (afdItem->perm[1] != '1') { printf("错误：无写入权限\n"); return; }
    afdItem->readPtr += len;
    if (afdItem->readPtr > afdItem->ufdPtr->fileLen) {
        afdItem->ufdPtr->fileLen = afdItem->readPtr;
    }
    printf("成功写入%s：%d字节，文件长度：%d\n", fileName, len, afdItem->ufdPtr->fileLen);
}

void lseekFile(const char* fileName, int offset) {
    AFDItem *afdItem = findFileInAFD(fileName);
    if (!afdItem) { printf("错误：文件%s未打开\n", fileName); return; }
    if (offset < 0 || offset > afdItem->ufdPtr->fileLen) {
        printf("错误：偏移量无效（0-%d）\n", afdItem->ufdPtr->fileLen);
        return;
    }
    afdItem->readPtr = offset;
    printf("成功移动指针到：%d\n", offset);
}

void changeFileName(const char* oldName, const char* newName) {
    UFDItem *oldFile = findFileInUFD(oldName);
    if (!oldFile) { printf("错误：文件%s不存在\n", oldName); return; }
    if (findFileInUFD(newName)) { printf("错误：新文件名已存在\n"); return; }
    if (findFileInAFD(oldName)) { printf("错误：文件正在打开中\n"); return; }
    strcpy(oldFile->fileName, newName);
    printf("成功重命名为：%s\n", newName);
}

void changePerm(const char* fileName, const char* newPerm) {
    if (strlen(newPerm) != 3) { printf("错误：保护码必须是3位\n"); return; }
    UFDItem *file = findFileInUFD(fileName);
    if (!file) { printf("错误：文件%s不存在\n", fileName); return; }
    strcpy(file->perm, newPerm);
    AFDItem *afdItem = findFileInAFD(fileName);
    if (afdItem) strcpy(afdItem->perm, newPerm);
    printf("成功修改保护码为：%s\n", newPerm);
}

// 显示主菜单
void showMainMenu() {
    system("clear"); // Windows用system("cls")
    printf("==================== 文件管理系统 ====================\n");
    printf("当前登录用户：%s\n", currentUser);
    printf("1. 创建文件       2. 删除文件       3. 打开文件\n");
    printf("4. 关闭文件       5. 读取文件       6. 写入文件\n");
    printf("7. 移动读写指针   8. 修改文件名     9. 修改保护级别\n");
    printf("10. 查看文件列表  11. 退出系统\n");
    printf("======================================================\n");
    printf("请输入功能编号（1-11）：");
}

// 查看当前用户文件列表
void showFileList() {
    MFDItem *user = findCurrentUser();
    if (!user) { printf("错误：当前用户未登录\n"); return; }
    printf("\n当前用户文件列表：\n");
    printf("------------------------------------------------------\n");
    printf("%-15s %-10s %-10s %-10s\n", "文件名", "保护码(rwx)", "文件长度", "状态");
    printf("------------------------------------------------------\n");
    int count = 0;
    for (int i = 0; i < MAX_FILE_PER_USER; i++) {
        if (user->ufd[i].isUsed) {
            count++;
            char status[10];
            strcpy(status, findFileInAFD(user->ufd[i].fileName) ? "已打开" : "未打开");
            printf("%-15s %-10s %-10d %-10s\n",
                   user->ufd[i].fileName,
                   user->ufd[i].perm,
                   user->ufd[i].fileLen,
                   status);
        }
    }
    if (count == 0) {
        printf("                      无文件\n");
    }
    printf("------------------------------------------------------\n");
    printf("按任意键返回菜单...");
    getchar();
    getchar(); // 吸收回车
}

int main() {
    int choice;
    char fileName[20], newName[20], perm[4];
    int len, offset;

    initFS();

    while (1) {
        showMainMenu();
        scanf("%d", &choice);
        getchar(); // 吸收回车

        switch (choice) {
            case 1: // 创建文件
                printf("\n===== 创建文件 =====\n");
                printf("请输入文件名：");
                scanf("%s", fileName);
                printf("请输入保护码（3位，rwx，如110）：");
                scanf("%s", perm);
                createFile(fileName, perm);
                break;

            case 2: // 删除文件
                printf("\n===== 删除文件 =====\n");
                printf("请输入文件名：");
                scanf("%s", fileName);
                deleteFile(fileName);
                break;

            case 3: // 打开文件
                printf("\n===== 打开文件 =====\n");
                printf("请输入文件名：");
                scanf("%s", fileName);
                openFile(fileName);
                break;

            case 4: // 关闭文件
                printf("\n===== 关闭文件 =====\n");
                printf("请输入文件名：");
                scanf("%s", fileName);
                closeFile(fileName);
                break;

            case 5: // 读取文件
                printf("\n===== 读取文件 =====\n");
                printf("请输入文件名：");
                scanf("%s", fileName);
                printf("请输入读取长度：");
                scanf("%d", &len);
                readFile(fileName, len);
                break;

            case 6: // 写入文件
                printf("\n===== 写入文件 =====\n");
                printf("请输入文件名：");
                scanf("%s", fileName);
                printf("请输入写入长度：");
                scanf("%d", &len);
                writeFile(fileName, len);
                break;

            case 7: // 移动读写指针
                printf("\n===== 移动读写指针 =====\n");
                printf("请输入文件名：");
                scanf("%s", fileName);
                printf("请输入偏移量（0-文件长度）：");
                scanf("%d", &offset);
                lseekFile(fileName, offset);
                break;

            case 8: // 修改文件名
                printf("\n===== 修改文件名 =====\n");
                printf("请输入旧文件名：");
                scanf("%s", fileName);
                printf("请输入新文件名：");
                scanf("%s", newName);
                changeFileName(fileName, newName);
                break;

            case 9: // 修改保护级别
                printf("\n===== 修改保护级别 =====\n");
                printf("请输入文件名：");
                scanf("%s", fileName);
                printf("请输入新保护码（3位，rwx，如110）：");
                scanf("%s", perm);
                changePerm(fileName, perm);
                break;

            case 10: // 查看文件列表
                showFileList();
                break;

            case 11: // 退出系统
                printf("\n退出文件管理系统...\n");
                return 0;

            default:
                printf("\n错误：无效的功能编号！\n");
        }

        printf("\n按任意键返回菜单...");
        getchar();
        getchar(); // 吸收回车
    }
}