#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 20  // 文件名/目录名最大长度
#define MAX_PATH_LEN 100 // 最大路径长度
#define MAX_OPEN_FILE 3  // 最大同时打开文件数

// 树型目录节点（文件或目录）
typedef struct DirNode {
    char name[MAX_NAME_LEN];    // 名称
    int type;                   // 0：目录，1：文件
    struct DirNode *parent;     // 父目录指针
    struct DirNode *subDirs;    // 子目录链表头（仅目录有效）
    struct DirNode *files;      // 文件链表头（仅目录有效）
    struct DirNode *next;       // 同级别下一个节点（目录/文件）
    // 文件属性（仅文件有效）
    char perm[4];               // 保护码（rwx，3位0/1）
    int fileLen;                // 文件长度
    int readPtr;                // 读写指针
} DirNode;

// 打开文件列表（支持多文件同时打开）
typedef struct OpenFileList {
    DirNode *fileNode;          // 指向打开的文件节点
    char fullPath[MAX_PATH_LEN];// 文件完整路径
    int isUsed;                 // 是否被占用
} OpenFileList;

// 全局变量：根目录、当前目录、打开文件列表
DirNode *root;
DirNode *currentDir;
OpenFileList openFileList[MAX_OPEN_FILE];

// 1. 创建新节点（目录或文件）
DirNode* createNode(const char* name, int type) {
    DirNode *node = (DirNode*)malloc(sizeof(DirNode));
    if (node == NULL) {
        printf("错误：内存分配失败，无法创建节点\n");
        return NULL;
    }
    // 复制名称并确保不越界
    strncpy(node->name, name, MAX_NAME_LEN-1);
    node->name[MAX_NAME_LEN-1] = '\0';
    node->type = type;
    node->parent = NULL;
    node->subDirs = NULL;       // 目录的子目录链表初始化为空
    node->files = NULL;         // 目录的文件链表初始化为空
    node->next = NULL;          // 同级别下一个节点初始化为空

    // 文件节点初始化属性
    if (type == 1) {
        strcpy(node->perm, "110"); // 默认权限：可读可写不可执行
        node->fileLen = 0;
        node->readPtr = 0;
    }
    return node;
}

// 2. 拆分路径为目录数组（如"/学校/计算机学院/软件专业"拆分为["学校", "计算机学院", "软件专业"]）
int splitPath(const char* path, char pathArr[][MAX_NAME_LEN]) {
    char temp[MAX_PATH_LEN];
    strncpy(temp, path, MAX_PATH_LEN - 1);
    temp[MAX_PATH_LEN - 1] = '\0'; // 确保字符串结束
    int count = 0;
    int isAbsolute = 0;

    // 检查是否为绝对路径
    if (temp[0] == '/') {
        isAbsolute = 1;
        strcpy(temp, temp + 1); // 去掉开头的'/'
        if (temp[0] == '\0') { // 路径是"/"，表示根目录
            strcpy(pathArr[count++], "学校");
            return count;
        }
    }

    if (isAbsolute) {
        // 绝对路径必须以"学校"为根
        char *token = strtok(temp, "/");
        if (token == NULL || strcmp(token, "学校") != 0) {
            printf("错误：绝对路径必须以/学校开头\n");
            return 0;
        }
        strcpy(pathArr[count++], token);

        // 处理剩余路径段
        token = strtok(NULL, "/");
        while (token != NULL) {
            if (strcmp(token, ".") == 0) { // 当前目录，跳过
                token = strtok(NULL, "/");
                continue;
            }
            if (strcmp(token, "..") == 0) { // 父目录，回退
                if (count > 1) { // 不能回退到根目录之上
                    count--;
                }
                token = strtok(NULL, "/");
                continue;
            }
            strcpy(pathArr[count++], token);
            token = strtok(NULL, "/");
        }
    } else {
        // 相对路径：收集当前目录到根的路径（逆序）
        DirNode *dir = currentDir;
        char reverseArr[10][MAX_NAME_LEN];
        int reverseCount = 0;
        while (dir != NULL) {
            strcpy(reverseArr[reverseCount++], dir->name);
            dir = dir->parent;
        }
        // 反转为正序存入路径数组
        for (int i = reverseCount - 1; i >= 0; i--) {
            strcpy(pathArr[count++], reverseArr[i]);
        }

        // 拆分剩余路径段
        if (temp[0] != '\0') { // 如果路径不为空
            char *token = strtok(temp, "/");
            while (token != NULL) {
                if (strcmp(token, ".") == 0) { // 当前目录，跳过
                    token = strtok(NULL, "/");
                    continue;
                }
                if (strcmp(token, "..") == 0) { // 父目录，回退
                    if (count > 1) { // 不能回退到根目录之上
                        count--;
                    }
                    token = strtok(NULL, "/");
                    continue;
                }
                strcpy(pathArr[count++], token);
                token = strtok(NULL, "/");
            }
        }
    }

    return count; // 返回路径段总数
}

// 3. 根据路径查找目录（返回最后一级目录节点，不存在则返回NULL）
DirNode* findDirByPath(const char* path) {
    char pathArr[10][MAX_NAME_LEN];
    int pathCount = splitPath(path, pathArr);
    if (pathCount == 0) {
        printf("错误：无效路径\n");
        return NULL;
    }

    // 从根目录开始逐级查找
    DirNode *current = root;
    for (int i = 1; i < pathCount; i++) { // i从1开始（跳过根目录"学校"）
        int found = 0;
        // 遍历当前目录的子目录链表
        DirNode *subDir = current->subDirs;
        while (subDir != NULL) {
            if (strcmp(subDir->name, pathArr[i]) == 0) {
                current = subDir;
                found = 1;
                break;
            }
            subDir = subDir->next;
        }
        // 某一级目录不存在
        if (!found) {
            printf("错误：路径不存在，缺失目录：%s\n", pathArr[i]);
            return NULL;
        }
    }
    return current;
}

// 4. 创建目录（支持绝对路径/相对路径）
int createDir(const char* path) {
    char pathArr[10][MAX_NAME_LEN];
    int pathCount = splitPath(path, pathArr);
    if (pathCount == 0) {
        return -1;
    }

    // 查找父目录（路径倒数第二级）
    char parentPath[MAX_PATH_LEN] = "";
    for (int i = 0; i < pathCount - 1; i++) {
        if (strlen(parentPath) + 1 + strlen(pathArr[i]) >= MAX_PATH_LEN) {
            printf("错误：路径过长\n");
            return -1;
        }
        strcat(parentPath, "/");
        strcat(parentPath, pathArr[i]);
    }
    DirNode *parentDir = findDirByPath(parentPath);
    if (!parentDir) {
        return -1;
    }

    // 提取要创建的目录名
    const char* dirName = pathArr[pathCount - 1];
    // 检查该目录是否已存在
    DirNode *subDir = parentDir->subDirs;
    while (subDir != NULL) {
        if (strcmp(subDir->name, dirName) == 0) {
            printf("错误：目录%s已存在\n", dirName);
            return -1;
        }
        subDir = subDir->next;
    }

    // 创建新目录并添加到父目录的子目录链表（头插法）
    DirNode *newDir = createNode(dirName, 0);
    if (newDir == NULL) {
        return -1;
    }
    newDir->parent = parentDir;
    newDir->next = parentDir->subDirs; // 新节点指向原链表头
    parentDir->subDirs = newDir;       // 父目录子目录链表头指向新节点

    // 打印创建成功信息
    if (strcmp(parentPath, "") == 0) {
        printf("成功创建目录：/%s\n", dirName);
    } else {
        printf("成功创建目录：%s/%s\n", parentPath, dirName);
    }
    return 0;
}

// 5. 创建文件（支持绝对路径/相对路径）
int createFile(const char* path) {
    char pathArr[10][MAX_NAME_LEN];
    int pathCount = splitPath(path, pathArr);
    if (pathCount == 0) {
        return -1;
    }

    // 查找父目录（路径倒数第二级）
    char parentPath[MAX_PATH_LEN] = "";
    for (int i = 0; i < pathCount - 1; i++) {
        if (strlen(parentPath) + 1 + strlen(pathArr[i]) >= MAX_PATH_LEN) {
            printf("错误：路径过长\n");
            return -1;
        }
        strcat(parentPath, "/");
        strcat(parentPath, pathArr[i]);
    }
    DirNode *parentDir = findDirByPath(parentPath);
    if (!parentDir) {
        return -1;
    }

    // 提取要创建的文件名
    const char* fileName = pathArr[pathCount - 1];
    // 检查该文件是否已存在
    DirNode *file = parentDir->files;
    while (file != NULL) {
        if (strcmp(file->name, fileName) == 0) {
            printf("错误：文件%s已存在\n", fileName);
            return -1;
        }
        file = file->next;
    }

    // 创建新文件并添加到父目录的文件链表（头插法）
    DirNode *newFile = createNode(fileName, 1);
    if (newFile == NULL) {
        return -1;
    }
    newFile->parent = parentDir;
    newFile->next = parentDir->files; // 新文件指向原链表头
    parentDir->files = newFile;       // 父目录文件链表头指向新文件

    // 打印创建成功信息
    if (strcmp(parentPath, "") == 0) {
        printf("成功创建文件：/%s\n", fileName);
    } else {
        printf("成功创建文件：%s/%s\n", parentPath, fileName);
    }
    return 0;
}

// 6. 切换当前目录
int cd(const char* path) {
    DirNode *targetDir = findDirByPath(path);
    if (!targetDir) {
        return -1;
    }
    // 检查目标是否为目录
    if (targetDir->type != 0) {
        printf("错误：%s不是目录，无法切换\n", path);
        return -1;
    }
    // 切换当前目录
    currentDir = targetDir;
    // 打印当前目录路径
    pwd();
    return 0;
}

// 辅助函数：获取当前目录的完整路径
void getCurrentPath(char path[]) {
    strcpy(path, "");
    DirNode *dir = currentDir;
    char temp[10][MAX_NAME_LEN];
    int count = 0;
    while (dir != NULL) {
        strcpy(temp[count++], dir->name);
        dir = dir->parent;
    }
    for (int i = count - 1; i >= 0; i--) {
        strcat(path, "/");
        strcat(path, temp[i]);
    }
}

// 7. 列出目录内容
void ls(const char* path) {
    DirNode *dir = findDirByPath(path);
    if (!dir) {
        return;
    }
    // 检查目标是否为目录
    if (dir->type != 0) {
        printf("错误：%s不是目录\n", path);
        return;
    }

    printf("\n【目录 %s 的内容】\n", path);
    printf("------------------------------------------------------\n");
    printf("%-18s %-10s\n", "名称", "类型");
    printf("------------------------------------------------------\n");

    // 列出所有子目录
    DirNode *subDir = dir->subDirs;
    while (subDir != NULL) {
        printf("%-18s %-10s\n", subDir->name, "目录");
        subDir = subDir->next;
    }

    // 列出所有文件
    DirNode *file = dir->files;
    while (file != NULL) {
        printf("%-18s %-10s\n", file->name, "文件");
        file = file->next;
    }

    printf("------------------------------------------------------\n");
}

// 8. 获取文件完整路径
void getFileFullPath(DirNode *file, char fullPath[]) {
    if (!file || file->type != 1) {
        strcpy(fullPath, "无效文件");
        return;
    }
    // 收集路径（逆序）
    char temp[10][MAX_NAME_LEN];
    int count = 0;
    DirNode *node = file;
    while (node != NULL) {
        strcpy(temp[count++], node->name);
        node = node->parent;
    }
    // 拼接为正序路径
    strcpy(fullPath, "");
    for (int i = count - 1; i >= 0; i--) {
        strcat(fullPath, "/");
        strcat(fullPath, temp[i]);
    }
}

// 9. 打开文件
DirNode* openFile(const char* path) {
    char pathArr[10][MAX_NAME_LEN];
    int pathCount = splitPath(path, pathArr);
    if (pathCount == 0) {
        return NULL;
    }

    // 查找父目录
    char parentPath[MAX_PATH_LEN] = "";
    for (int i = 0; i < pathCount - 1; i++) {
        if (strlen(parentPath) + 1 + strlen(pathArr[i]) >= MAX_PATH_LEN) {
            printf("错误：路径过长\n");
            return NULL;
        }
        strcat(parentPath, "/");
        strcat(parentPath, pathArr[i]);
    }
    DirNode *parentDir = findDirByPath(parentPath);
    if (!parentDir) {
        return NULL;
    }

    // 查找文件
    const char* fileName = pathArr[pathCount - 1];
    DirNode *file = parentDir->files;
    while (file != NULL) {
        if (strcmp(file->name, fileName) == 0) {
            // 检查文件是否已打开
            for (int i = 0; i < MAX_OPEN_FILE; i++) {
                if (openFileList[i].isUsed && openFileList[i].fileNode == file) {
                    printf("错误：文件%s已打开\n", fileName);
                    return NULL;
                }
            }
            // 查找空的打开文件列表项
            int emptyIdx = -1;
            for (int i = 0; i < MAX_OPEN_FILE; i++) {
                if (!openFileList[i].isUsed) {
                    emptyIdx = i;
                    break;
                }
            }
            if (emptyIdx == -1) {
                printf("错误：打开文件数已达上限（%d个）\n", MAX_OPEN_FILE);
                return NULL;
            }
            // 记录打开的文件
            openFileList[emptyIdx].fileNode = file;
            getFileFullPath(file, openFileList[emptyIdx].fullPath);
            openFileList[emptyIdx].isUsed = 1;
            printf("成功打开文件：%s\n", openFileList[emptyIdx].fullPath);
            return file;
        }
        file = file->next;
    }

    printf("错误：文件%s不存在\n", fileName);
    return NULL;
}

// 10. 根据文件名查找已打开的文件节点
DirNode* findOpenedFile(const char* fileName) {
    for (int i = 0; i < MAX_OPEN_FILE; i++) {
        if (openFileList[i].isUsed) {
            DirNode *file = openFileList[i].fileNode;
            if (strcmp(file->name, fileName) == 0) {
                return file;
            }
        }
    }
    return NULL;
}

// 11. 读取文件
int readFile(DirNode *file, int len) {
    if (!file || file->type != 1) {
        printf("错误：无效的文件\n");
        return -1;
    }
    // 检查读取权限
    if (file->perm[0] != '1') {
        printf("错误：文件%s无读取权限\n", file->name);
        return -1;
    }
    // 模拟读取：修正读取长度（避免超出文件末尾）
    int realReadLen = len;
    if (file->readPtr + len > file->fileLen) {
        realReadLen = file->fileLen - file->readPtr;
        if (realReadLen < 0) realReadLen = 0;
        printf("警告：已到达文件末尾，实际读取长度：%d\n", realReadLen);
    }
    // 移动读写指针
    file->readPtr += realReadLen;
    printf("成功读取文件%s：%d字节，当前指针位置：%d\n",
           file->name, realReadLen, file->readPtr);
    return 0;
}

// 12. 写入文件
int writeFile(DirNode *file, int len) {
    if (!file || file->type != 1) {
        printf("错误：无效的文件\n");
        return -1;
    }
    // 检查写入权限
    if (file->perm[1] != '1') {
        printf("错误：文件%s无写入权限\n", file->name);
        return -1;
    }
    // 模拟写入：移动指针并扩展文件长度
    file->readPtr += len;
    if (file->readPtr > file->fileLen) {
        file->fileLen = file->readPtr;
    }
    printf("成功写入文件%s：%d字节，文件当前长度：%d，当前指针位置：%d\n",
           file->name, len, file->fileLen, file->readPtr);
    return 0;
}

// 13. 关闭文件
int closeFile(const char* fileName) {
    // 查找已打开的文件
    for (int i = 0; i < MAX_OPEN_FILE; i++) {
        if (openFileList[i].isUsed) {
            DirNode *file = openFileList[i].fileNode;
            if (strcmp(file->name, fileName) == 0) {
                // 清空打开文件列表项
                openFileList[i].fileNode = NULL;
                strcpy(openFileList[i].fullPath, "");
                openFileList[i].isUsed = 0;
                printf("成功关闭文件：%s\n", fileName);
                return 0;
            }
        }
    }
    printf("错误：文件%s未打开\n", fileName);
    return -1;
}

// 14. 删除文件或空目录
int deleteNode(const char* path) {
    char pathArr[10][MAX_NAME_LEN];
    int pathCount = splitPath(path, pathArr);
    if (pathCount == 0) {
        return -1;
    }

    // 查找父目录
    char parentPath[MAX_PATH_LEN] = "";
    for (int i = 0; i < pathCount - 1; i++) {
        if (strlen(parentPath) + 1 + strlen(pathArr[i]) >= MAX_PATH_LEN) {
            printf("错误：路径过长\n");
            return -1;
        }
        strcat(parentPath, "/");
        strcat(parentPath, pathArr[i]);
    }
    DirNode *parentDir = findDirByPath(parentPath);
    if (!parentDir) {
        return -1;
    }

    const char* nodeName = pathArr[pathCount - 1];
    DirNode *prev = NULL, *curr = NULL;

    // 先尝试删除目录
    curr = parentDir->subDirs;
    while (curr != NULL) {
        if (strcmp(curr->name, nodeName) == 0) {
            // 目录必须为空（无子目录和文件）
            if (curr->subDirs != NULL || curr->files != NULL) {
                printf("错误：目录%s不为空，无法删除\n", nodeName);
                return -1;
            }
            // 检查目录是否为当前目录
            if (curr == currentDir) {
                printf("错误：无法删除当前所在目录\n");
                return -1;
            }
            // 从父目录子目录链表中移除
            if (prev == NULL) {
                parentDir->subDirs = curr->next;
            } else {
                prev->next = curr->next;
            }
            // 释放内存
            free(curr);
            printf("成功删除目录：%s/%s\n", parentPath, nodeName);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }

    // 再尝试删除文件
    prev = NULL;
    curr = parentDir->files;
    while (curr != NULL) {
        if (strcmp(curr->name, nodeName) == 0) {
            // 检查文件是否已打开
            for (int i = 0; i < MAX_OPEN_FILE; i++) {
                if (openFileList[i].isUsed && openFileList[i].fileNode == curr) {
                    printf("错误：文件%s正在打开中，无法删除\n", nodeName);
                    return -1;
                }
            }
            // 从父目录文件链表中移除
            if (prev == NULL) {
                parentDir->files = curr->next;
            } else {
                prev->next = curr->next;
            }
            // 释放内存
            free(curr);
            printf("成功删除文件：%s/%s\n", parentPath, nodeName);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("错误：%s不存在\n", nodeName);
    return -1;
}

// 15. 显示当前目录路径（pwd）
void pwd() {
    char path[MAX_PATH_LEN] = "";
    DirNode *dir = currentDir;
    char temp[10][MAX_NAME_LEN];
    int count = 0;

    // 收集路径（逆序）
    while (dir != NULL) {
        strcpy(temp[count++], dir->name);
        dir = dir->parent;
    }

    // 拼接为正序路径
    for (int i = count - 1; i >= 0; i--) {
        strcat(path, "/");
        strcat(path, temp[i]);
    }

    printf("当前目录：%s\n", path);
}

// 16. 修改文件权限
int chmodFile(const char* fileName, const char* newPerm) {
    // 检查权限格式
    if (strlen(newPerm) != 3) {
        printf("错误：权限码必须是3位（0/1），如110\n");
        return -1;
    }
    for (int i = 0; i < 3; i++) {
        if (newPerm[i] != '0' && newPerm[i] != '1') {
            printf("错误：权限码只能包含0和1\n");
            return -1;
        }
    }

    // 查找已打开的文件
    DirNode *file = findOpenedFile(fileName);
    if (!file) {
        // 查找未打开的文件
        char pathArr[10][MAX_NAME_LEN];
        int pathCount = splitPath(fileName, pathArr);
        if (pathCount == 0) return -1;

        char parentPath[MAX_PATH_LEN] = "";
        for (int i = 0; i < pathCount - 1; i++) {
            if (strlen(parentPath) + 1 + strlen(pathArr[i]) >= MAX_PATH_LEN) {
                printf("错误：路径过长\n");
                return -1;
            }
            strcat(parentPath, "/");
            strcat(parentPath, pathArr[i]);
        }
        DirNode *parentDir = findDirByPath(parentPath);
        if (!parentDir) return -1;

        const char* fname = pathArr[pathCount - 1];
        file = parentDir->files;
        while (file != NULL) {
            if (strcmp(file->name, fname) == 0) {
                break;
            }
            file = file->next;
        }
        if (!file) {
            printf("错误：文件%s不存在\n", fileName);
            return -1;
        }
    }

    // 修改权限
    strcpy(file->perm, newPerm);
    // 同步到已打开的文件列表
    for (int i = 0; i < MAX_OPEN_FILE; i++) {
        if (openFileList[i].isUsed && openFileList[i].fileNode == file) {
            strcpy(openFileList[i].fileNode->perm, newPerm);
        }
    }
    printf("成功修改文件%s权限为：%s（rwx）\n", fileName, newPerm);
    return 0;
}

// 17. 初始化打开文件列表
void initOpenFileList() {
    for (int i = 0; i < MAX_OPEN_FILE; i++) {
        openFileList[i].fileNode = NULL;
        strcpy(openFileList[i].fullPath, "");
        openFileList[i].isUsed = 0;
    }
}

// 18. 初始化学校文件系统（创建默认目录结构）
void initSchoolFS() {
    // 创建根目录"学校"
    root = createNode("学校", 0);
    if (root == NULL) {
        printf("错误：文件系统初始化失败\n");
        exit(1);
    }
    currentDir = root;
    initOpenFileList();

    // 创建默认目录结构
    printf("正在创建默认学校目录结构...\n");
    createDir("/学校/行政部门");
    createDir("/学校/教学院系");
    createDir("/学校/后勤部门");
    createDir("/学校/教学院系/计算机学院");
    createDir("/学校/教学院系/机械工程学院");
    createDir("/学校/教学院系/文学院");
    createDir("/学校/教学院系/计算机学院/软件专业");  // 修正原路径错误（原代码少了"教学院系"）
    createDir("/学校/教学院系/计算机学院/网络工程专业");
    createDir("/学校/行政部门/校长办公室");
    createDir("/学校/行政部门/教务处");
    createDir("/学校/行政部门/财务处");

    // 创建默认文件
    createFile("/学校/行政部门/教务处/课程表.txt");
    createFile("/学校/行政部门/财务处/缴费通知.txt");
    createFile("/学校/教学院系/计算机学院/软件专业/实验安排.doc");  // 修正原路径错误
    createFile("/学校/后勤部门/宿舍管理.txt");

    printf("学校文件系统初始化完成！\n");
}

// 19. 显示帮助信息
void printHelp() {
    printf("\n==================== 学校文件系统命令帮助 ====================\n");
    printf("1.  mkdir <路径>    - 创建目录（如：mkdir /学校/计算机学院/人工智能专业）\n");
    printf("2.  touch <路径>    - 创建文件（如：touch /学校/教务处/考试安排.txt）\n");
    printf("3.  cd <路径>       - 切换目录（如：cd /学校/教学院系/计算机学院，cd .. 返回上级）\n");
    printf("4.  ls [路径]       - 列出目录内容（默认当前目录，如：ls 或 ls /学校/行政部门）\n");
    printf("5.  open <路径>     - 打开文件（如：open /学校/教务处/课程表.txt）\n");
    printf("6.  close <文件名>  - 关闭文件（如：close 课程表.txt）\n");
    printf("7.  read <文件名> <长度> - 读取文件（需先open，如：read 课程表.txt 50）\n");
    printf("8.  write <文件名> <长度> - 写入文件（需先open，如：write 课程表.txt 100）\n");
    printf("9.  rm <路径>       - 删除文件或空目录（如：rm /学校/后勤部门/临时文件.txt）\n");
    printf("10. chmod <文件名> <权限> - 修改文件权限（如：chmod 课程表.txt 111）\n");
    printf("11. pwd             - 显示当前目录路径\n");
    printf("12. help            - 显示帮助信息\n");
    printf("13. exit            - 退出文件系统\n");
    printf("==============================================================\n\n");
}

// 20. 释放文件系统内存（递归释放所有节点）
void freeFS(DirNode *node) {
    if (!node) return;

    // 递归释放子目录
    DirNode *subDir = node->subDirs;
    while (subDir != NULL) {
        DirNode *temp = subDir;
        subDir = subDir->next;
        freeFS(temp);
    }

    // 递归释放文件
    DirNode *file = node->files;
    while (file != NULL) {
        DirNode *temp = file;
        file = file->next;
        free(temp);
    }

    // 释放当前节点
    free(node);
}

// 主函数：交互逻辑
int main() {
    char cmd[20], path[MAX_PATH_LEN], fileName[20], perm[4];
    int len;
    DirNode *targetFile = NULL;

    // 初始化学校文件系统
    initSchoolFS();
    printHelp();

    while (1) {
        // 显示命令提示符
        char prompt[MAX_PATH_LEN];
        getCurrentPath(prompt);
        printf("\n%s> ", prompt);
        scanf("%s", cmd);

        // 解析命令
        if (strcmp(cmd, "mkdir") == 0) {
            scanf("%s", path);
            createDir(path);
        } else if (strcmp(cmd, "touch") == 0) {
            scanf("%s", path);
            createFile(path);
        } else if (strcmp(cmd, "cd") == 0) {
            scanf("%s", path);
            cd(path);
        } else if (strcmp(cmd, "ls") == 0) {
            char input[MAX_PATH_LEN];
            // 尝试读取参数，如果没有参数，则使用当前目录
            if (scanf("%s", input) != 1) {
                // 清空输入缓冲区，避免影响后续输入
                while (getchar() != '\n');
                getCurrentPath(path);
            } else {
                strcpy(path, input);
            }
            ls(path);
        } else if (strcmp(cmd, "open") == 0) {
            scanf("%s", path);
            targetFile = openFile(path);
        } else if (strcmp(cmd, "close") == 0) {
            scanf("%s", fileName);
            closeFile(fileName);
        } else if (strcmp(cmd, "read") == 0) {
            scanf("%s %d", fileName, &len);
            targetFile = findOpenedFile(fileName);
            if (targetFile) {
                readFile(targetFile, len);
            } else {
                printf("错误：文件%s未打开\n", fileName);
            }
        } else if (strcmp(cmd, "write") == 0) {
            scanf("%s %d", fileName, &len);
            targetFile = findOpenedFile(fileName);
            if (targetFile) {
                writeFile(targetFile, len);
            } else {
                printf("错误：文件%s未打开\n", fileName);
            }
        } else if (strcmp(cmd, "rm") == 0) {
            scanf("%s", path);
            deleteNode(path);
        } else if (strcmp(cmd, "chmod") == 0) {
            scanf("%s %s", fileName, perm);
            chmodFile(fileName, perm);
        } else if (strcmp(cmd, "pwd") == 0) {
            pwd();
        } else if (strcmp(cmd, "help") == 0) {
            printHelp();
        } else if (strcmp(cmd, "exit") == 0) {
            printf("\n正在退出学校文件系统，释放内存...\n");
            freeFS(root);
            printf("文件系统内存已释放，程序正常退出！\n");
            break;
        } else {
            printf("错误：未知命令，请输入help查看支持的命令\n");
        }
    }

    return 0;
}