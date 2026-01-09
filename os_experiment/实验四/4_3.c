#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 常量定义
#define MAX_NAME_LEN 20      // 最大文件名/目录名长度
#define MAX_PATH_LEN 100     // 最大路径长度
#define MAX_CHILDREN 10      // 每个目录最大子节点数

// 目录/文件节点结构体
typedef struct DirNode {
    char name[MAX_NAME_LEN]; // 节点名称
    bool isDir;              // 是否为目录（true=目录，false=文件）
    struct DirNode *parent;  // 父节点指针
    struct DirNode *subDirs; // 子目录链表
    struct DirNode *files;   // 文件链表
    struct DirNode *next;    // 同级节点下一个指针
    int fileSize;            // 文件大小（仅文件有效）
    int readPtr;             // 文件读写指针（仅文件有效）
} DirNode;

// 全局变量
DirNode *root = NULL;        // 根节点
DirNode *currentDir = NULL;  // 当前工作目录
char prompt[MAX_PATH_LEN];   // 命令行提示符

// 函数声明
void initRoot();
void printHelp();
int splitPath(const char* path, char pathArr[][MAX_NAME_LEN]);
DirNode* findNode(const char* path, bool isDir);
DirNode* createDirNode(const char* name, DirNode* parent);
DirNode* createFileNode(const char* name, DirNode* parent);
void createDir(const char* path);
void createFile(const char* path);
void cd(const char* path);
void ls(const char* path);
DirNode* openFile(const char* path);
void readFile(DirNode* file, int len);
void writeFile(DirNode* file, int len);
void deleteNode(const char* path);
void pwd();
char* getNodePath(DirNode *node, char *path);
void freeAllNodes(DirNode *node);

// 获取节点完整路径
char* getNodePath(DirNode *node, char *path) {
    if (!node) {
        path[0] = '\0';
        return path;
    }
    char temp[10][MAX_NAME_LEN]; // 最多支持10级目录
    int count = 0;
    DirNode *dir = node;
    while (dir != NULL && count < 10) {
        strncpy(temp[count++], dir->name, MAX_NAME_LEN-1);
        temp[count-1][MAX_NAME_LEN-1] = '\0';
        dir = dir->parent;
    }
    path[0] = '\0';
    for (int i = count - 1; i >= 0; i--) {
        strncat(path, "/", MAX_PATH_LEN - strlen(path) - 1);
        strncat(path, temp[i], MAX_PATH_LEN - strlen(path) - 1);
    }
    return path;
}

// 递归释放所有节点内存
void freeAllNodes(DirNode *node) {
    if (!node) return;
    // 释放子目录链表
    DirNode *subDir = node->subDirs;
    while (subDir) {
        DirNode *nextSub = subDir->next;
        freeAllNodes(subDir);
        subDir = nextSub;
    }
    // 释放文件链表
    DirNode *file = node->files;
    while (file) {
        DirNode *nextFile = file->next;
        free(file);
        file = nextFile;
    }
    // 释放当前节点
    free(node);
}

// 分割路径为目录/文件名数组
int splitPath(const char* path, char pathArr[][MAX_NAME_LEN]) {
    if (!path || path[0] != '/') {
        return -1; // 仅支持绝对路径
    }
    char temp[MAX_PATH_LEN];
    strncpy(temp, path, MAX_PATH_LEN-1);
    temp[MAX_PATH_LEN-1] = '\0';
    
    int count = 0;
    char *token = strtok(temp + 1, "/"); // 跳过开头的/
    while (token != NULL && count < 10) {
        strncpy(pathArr[count], token, MAX_NAME_LEN-1);
        pathArr[count][MAX_NAME_LEN-1] = '\0';
        count++;
        token = strtok(NULL, "/");
    }
    return count;
}

// 初始化根节点
void initRoot() {
    root = (DirNode*)malloc(sizeof(DirNode));
    strncpy(root->name, "root", MAX_NAME_LEN-1);
    root->name[MAX_NAME_LEN-1] = '\0';
    root->isDir = true;
    root->parent = NULL;
    root->subDirs = NULL;
    root->files = NULL;
    root->next = NULL;
    root->fileSize = 0;
    root->readPtr = 0;
    currentDir = root;
    // 初始化提示符
    getNodePath(currentDir, prompt);
}

// 打印帮助信息
void printHelp() {
    printf("===== 树形文件系统 =====\n");
    printf("支持的命令：\n");
    printf("1. mkdir <绝对路径>  - 创建目录（如mkdir /root/docs）\n");
    printf("2. touch <绝对路径>  - 创建文件（如touch /root/docs/note.txt）\n");
    printf("3. cd <绝对路径>     - 切换目录（如cd /root/docs，cd /root返回根目录）\n");
    printf("4. ls <绝对路径>     - 列出目录内容（如ls /root/docs，ls .列出当前目录）\n");
    printf("5. open <绝对路径>   - 打开文件（如open /root/docs/note.txt）\n");
    printf("6. read <长度>       - 读取已打开文件（需先执行open）\n");
    printf("7. write <长度>      - 写入已打开文件（需先执行open）\n");
    printf("8. rm <绝对路径>     - 删除文件或空目录（如rm /root/docs/note.txt）\n");
    printf("9. pwd               - 显示当前工作目录路径\n");
    printf("10. help              - 显示帮助信息\n");
    printf("11. exit              - 退出文件系统\n");
    printf("========================\n");
}

// 查找指定路径的节点
DirNode* findNode(const char* path, bool isDir) {
    char pathArr[10][MAX_NAME_LEN];
    int pathCount = splitPath(path, pathArr);
    if (pathCount <= 0) {
        return NULL;
    }

    DirNode *current = root;
    // 遍历路径（除最后一个节点，查找父目录）
    for (int i = 0; i < pathCount - 1; i++) {
        if (!current || !current->isDir) {
            return NULL;
        }
        DirNode *subDir = current->subDirs;
        bool found = false;
        while (subDir) {
            if (strcmp(subDir->name, pathArr[i]) == 0 && subDir->isDir) {
                current = subDir;
                found = true;
                break;
            }
            subDir = subDir->next;
        }
        if (!found) {
            return NULL;
        }
    }

    // 查找最后一个节点
    char *targetName = pathArr[pathCount - 1];
    if (pathCount == 1 && strcmp(targetName, root->name) == 0) {
        return root; // 根目录特殊处理
    }

    if (isDir) {
        DirNode *subDir = current->subDirs;
        while (subDir) {
            if (strcmp(subDir->name, targetName) == 0) {
                return subDir;
            }
            subDir = subDir->next;
        }
    } else {
        DirNode *file = current->files;
        while (file) {
            if (strcmp(file->name, targetName) == 0) {
                return file;
            }
            file = file->next;
        }
    }
    return NULL;
}

// 创建目录节点
DirNode* createDirNode(const char* name, DirNode* parent) {
    DirNode *newDir = (DirNode*)malloc(sizeof(DirNode));
    strncpy(newDir->name, name, MAX_NAME_LEN-1);
    newDir->name[MAX_NAME_LEN-1] = '\0';
    newDir->isDir = true;
    newDir->parent = parent;
    newDir->subDirs = NULL;
    newDir->files = NULL;
    newDir->next = NULL;
    newDir->fileSize = 0;
    newDir->readPtr = 0;
    return newDir;
}

// 创建文件节点
DirNode* createFileNode(const char* name, DirNode* parent) {
    DirNode *newFile = (DirNode*)malloc(sizeof(DirNode));
    strncpy(newFile->name, name, MAX_NAME_LEN-1);
    newFile->name[MAX_NAME_LEN-1] = '\0';
    newFile->isDir = false;
    newFile->parent = parent;
    newFile->subDirs = NULL;
    newFile->files = NULL;
    newFile->next = NULL;
    newFile->fileSize = 0;
    newFile->readPtr = 0;
    return newFile;
}

// 创建目录
void createDir(const char* path) {
    char pathArr[10][MAX_NAME_LEN];
    int pathCount = splitPath(path, pathArr);
    if (pathCount <= 0) {
        printf("错误：仅支持绝对路径（以/开头）\n");
        return;
    }

    // 分离父目录路径和新目录名
    char parentPath[MAX_PATH_LEN] = "/";
    for (int i = 0; i < pathCount - 1; i++) {
        strncat(parentPath, pathArr[i], MAX_PATH_LEN - strlen(parentPath) - 1);
        if (i != pathCount - 2) {
            strncat(parentPath, "/", MAX_PATH_LEN - strlen(parentPath) - 1);
        }
    }
    char *newDirName = pathArr[pathCount - 1];

    // 查找父目录
    DirNode *parentDir = findNode(parentPath, true);
    if (!parentDir) {
        printf("错误：父目录「%s」不存在\n", parentPath);
        return;
    }

    // 检查父目录子目录是否已存在同名
    DirNode *subDir = parentDir->subDirs;
    while (subDir) {
        if (strcmp(subDir->name, newDirName) == 0) {
            printf("错误：目录「%s」已存在\n", newDirName);
            return;
        }
        subDir = subDir->next;
    }

    // 检查父目录子目录数量是否超限
    int dirCount = 0;
    subDir = parentDir->subDirs;
    while (subDir) {
        dirCount++;
        subDir = subDir->next;
    }
    if (dirCount >= MAX_CHILDREN) {
        printf("错误：父目录子目录数量已达上限（%d个）\n", MAX_CHILDREN);
        return;
    }

    // 创建新目录并添加到父目录
    DirNode *newDir = createDirNode(newDirName, parentDir);
    newDir->next = parentDir->subDirs;
    parentDir->subDirs = newDir;
    printf("成功：创建目录「%s/%s」\n", parentPath, newDirName);
}

// 创建文件
void createFile(const char* path) {
    char pathArr[10][MAX_NAME_LEN];
    int pathCount = splitPath(path, pathArr);
    if (pathCount <= 0) {
        printf("错误：仅支持绝对路径（以/开头）\n");
        return;
    }

    // 分离父目录路径和新文件名
    char parentPath[MAX_PATH_LEN] = "/";
    for (int i = 0; i < pathCount - 1; i++) {
        strncat(parentPath, pathArr[i], MAX_PATH_LEN - strlen(parentPath) - 1);
        if (i != pathCount - 2) {
            strncat(parentPath, "/", MAX_PATH_LEN - strlen(parentPath) - 1);
        }
    }
    char *newFileName = pathArr[pathCount - 1];

    // 查找父目录
    DirNode *parentDir = findNode(parentPath, true);
    if (!parentDir) {
        printf("错误：父目录「%s」不存在\n", parentPath);
        return;
    }

    // 检查父目录文件是否已存在同名
    DirNode *file = parentDir->files;
    while (file) {
        if (strcmp(file->name, newFileName) == 0) {
            printf("错误：文件「%s」已存在\n", newFileName);
            return;
        }
        file = file->next;
    }

    // 检查父目录文件数量是否超限
    int fileCount = 0;
    file = parentDir->files;
    while (file) {
        fileCount++;
        file = file->next;
    }
    if (fileCount >= MAX_CHILDREN) {
        printf("错误：父目录文件数量已达上限（%d个）\n", MAX_CHILDREN);
        return;
    }

    // 创建新文件并添加到父目录
    DirNode *newFile = createFileNode(newFileName, parentDir);
    newFile->next = parentDir->files;
    parentDir->files = newFile;
    printf("成功：创建文件「%s/%s」\n", parentPath, newFileName);
}

// 切换目录
void cd(const char* path) {
    DirNode *targetDir = findNode(path, true);
    if (!targetDir) {
        printf("错误：目录「%s」不存在\n", path);
        return;
    }
    currentDir = targetDir;
    getNodePath(currentDir, prompt);
    printf("成功：切换到目录「%s」\n", prompt);
}

// 列出目录内容
void ls(const char* path) {
    // 处理当前目录（.）
    char targetPath[MAX_PATH_LEN];
    if (strcmp(path, ".") == 0) {
        getNodePath(currentDir, targetPath);
    } else {
        strncpy(targetPath, path, MAX_PATH_LEN-1);
        targetPath[MAX_PATH_LEN-1] = '\0';
    }

    DirNode *targetDir = findNode(targetPath, true);
    if (!targetDir) {
        printf("错误：目录「%s」不存在\n", targetPath);
        return;
    }

    printf("===== 「%s」目录内容 =====\n", targetPath);
    // 列出子目录
    DirNode *subDir = targetDir->subDirs;
    if (subDir) {
        printf("【目录】\n");
        while (subDir) {
            printf("  %s/\n", subDir->name);
            subDir = subDir->next;
        }
    }
    // 列出文件
    DirNode *file = targetDir->files;
    if (file) {
        printf("【文件】\n");
        while (file) {
            printf("  %s （大小：%d字节）\n", file->name, file->fileSize);
            file = file->next;
        }
    }
    if (!targetDir->subDirs && !targetDir->files) {
        printf("  （空目录）\n");
    }
    printf("========================\n");
}

// 打开文件
DirNode* openFile(const char* path) {
    DirNode *targetFile = findNode(path, false);
    if (!targetFile) {
        printf("错误：文件「%s」不存在\n", path);
        return NULL;
    }
    if (targetFile->isDir) {
        printf("错误：「%s」是目录，无法打开\n", path);
        return NULL;
    }
    printf("成功：打开文件「%s」，当前读写指针：%d\n", path, targetFile->readPtr);
    return targetFile;
}

// 读取文件
void readFile(DirNode* file, int len) {
    if (!file || file->isDir) {
        printf("错误：无有效打开的文件\n");
        return;
    }
    if (len <= 0) {
        printf("错误：读取长度必须大于0\n");
        return;
    }

    int remainSize = file->fileSize - file->readPtr;
    int actualRead = (len > remainSize) ? remainSize : len;
    if (actualRead <= 0) {
        printf("提示：文件已读取完毕，无剩余内容可读取\n");
        return;
    }

    file->readPtr += actualRead;
    printf("成功：读取「%s」%d字节（剩余可读取：%d字节），当前指针：%d\n",
           file->name, actualRead, file->fileSize - file->readPtr, file->readPtr);
}

// 写入文件
void writeFile(DirNode* file, int len) {
    if (!file || file->isDir) {
        printf("错误：无有效打开的文件\n");
        return;
    }
    if (len <= 0) {
        printf("错误：写入长度必须大于0\n");
        return;
    }

    file->fileSize += len;
    file->readPtr = file->fileSize;
    printf("成功：写入「%s」%d字节，文件当前大小：%d字节，指针位置：%d\n",
           file->name, len, file->fileSize, file->readPtr);
}

// 删除文件/空目录
void deleteNode(const char* path) {
    // 查找目标节点
    DirNode *targetNode = findNode(path, true); // 先尝试按目录查找
    bool isDir = true;
    if (!targetNode) {
        targetNode = findNode(path, false); // 再按文件查找
        isDir = false;
    }
    if (!targetNode) {
        printf("错误：「%s」不存在\n", path);
        return;
    }

    // 目录非空无法删除
    if (isDir) {
        if (targetNode->subDirs != NULL || targetNode->files != NULL) {
            printf("错误：目录「%s」非空，无法删除\n", path);
            return;
        }
    }

    // 查找父节点
    DirNode *parentNode = targetNode->parent;
    if (!parentNode) {
        printf("错误：无法删除根目录\n");
        return;
    }

    // 从父节点链表中移除目标节点
    if (isDir) {
        DirNode *prev = NULL;
        DirNode *curr = parentNode->subDirs;
        while (curr) {
            if (curr == targetNode) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    parentNode->subDirs = curr->next;
                }
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    } else {
        DirNode *prev = NULL;
        DirNode *curr = parentNode->files;
        while (curr) {
            if (curr == targetNode) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    parentNode->files = curr->next;
                }
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    // 释放目标节点内存
    free(targetNode);
    printf("成功：删除「%s」\n", path);
}

// 显示当前工作目录
void pwd() {
    char path[MAX_PATH_LEN];
    getNodePath(currentDir, path);
    printf("当前目录：%s\n", path);
}

// 主函数
int main() {
    char cmd[20];
    char path[MAX_PATH_LEN];
    int len;
    DirNode *openFilePtr = NULL; // 当前打开的文件

    // 初始化
    initRoot();
    printHelp();

    while (1) {
        // 打印命令提示符
        printf("\n%s> ", prompt);
        // 读取命令（限制长度防止溢出）
        scanf("%19s", cmd);

        if (strcmp(cmd, "mkdir") == 0) {
            scanf("%99s", path);
            createDir(path);
        } else if (strcmp(cmd, "touch") == 0) {
            scanf("%99s", path);
            createFile(path);
        } else if (strcmp(cmd, "cd") == 0) {
            scanf("%99s", path);
            cd(path);
        } else if (strcmp(cmd, "ls") == 0) {
            scanf("%99s", path);
            ls(path);
        } else if (strcmp(cmd, "open") == 0) {
            scanf("%99s", path);
            openFilePtr = openFile(path);
        } else if (strcmp(cmd, "read") == 0) {
            scanf("%d", &len);
            readFile(openFilePtr, len);
        } else if (strcmp(cmd, "write") == 0) {
            scanf("%d", &len);
            writeFile(openFilePtr, len);
        } else if (strcmp(cmd, "rm") == 0) {
            scanf("%99s", path);
            // 记录打开文件的完整路径
            char openFilePath[MAX_PATH_LEN] = "";
            if (openFilePtr) {
                getNodePath(openFilePtr, openFilePath);
            }
            // 删除节点
            deleteNode(path);
            // 若删除的是当前打开的文件，重置指针
            char rmFilePath[MAX_PATH_LEN];
            strncpy(rmFilePath, path, MAX_PATH_LEN-1);
            rmFilePath[MAX_PATH_LEN-1] = '\0';
            if (openFilePtr && strcmp(openFilePath, rmFilePath) == 0) {
                openFilePtr = NULL;
                printf("提示：已删除当前打开的文件，文件指针已重置\n");
            }
        } else if (strcmp(cmd, "pwd") == 0) {
            pwd();
        } else if (strcmp(cmd, "help") == 0) {
            printHelp();
        } else if (strcmp(cmd, "exit") == 0) {
            printf("===== 退出树形文件系统 =====\n");
            freeAllNodes(root); // 释放所有内存
            break;
        } else {
            printf("错误：未知命令「%s」，输入help查看帮助\n", cmd);
        }
    }
    return 0;
}