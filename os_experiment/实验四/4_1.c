#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10        // 最大用户数（题目要求n个用户）
#define MAX_FILES_PER_USER 10// 每个用户最大文件数（题目要求m个文件）
#define MAX_OPEN_FILES 1     // 一次最多打开文件数（题目要求：一次运行只能打开一个）
#define FILENAME_LEN 20      // 文件名最大长度
#define USERNAME_LEN 20      // 用户名最大长度
#define PERM_R 1 << 0        // 读权限（bit0）
#define PERM_W 1 << 1        // 写权限（bit1）
#define PERM_X 1 << 2        // 执行权限（bit2）

// 用户文件目录项（UFD）：存储单个文件的属性
typedef struct FileEntry {
    char filename[FILENAME_LEN];  // 文件名
    int permission;               // 保护码（0-7，三位二进制对应r/w/x）
    int length;                   // 文件长度（字节数）
    int rw_ptr;                   // 读写指针（记录当前操作位置）
    int is_valid;                 // 文件有效性标记（1=有效，0=已删除）
} FileEntry;

// 主目录项（MFD）：存储单个用户的信息
typedef struct UserEntry {
    char username[USERNAME_LEN];  // 用户名
    FileEntry files[MAX_FILES_PER_USER];// 该用户的文件目录
    int file_count;               // 当前文件数量
    int is_valid;                 // 用户有效性标记（1=有效）
} UserEntry;

// 打开文件目录项（AFD）：存储当前打开的文件信息
typedef struct OpenFileEntry {
    char filename[FILENAME_LEN];  // 打开的文件名
    FileEntry *file_ptr;          // 指向UFD中对应的文件项
    int permission;               // 打开时的权限（同步UFD的保护码）
    int rw_ptr;                   // 当前读写指针（独立于UFD，关闭后不保留）
    int is_valid;                 // 条目有效性标记（1=有效）
} OpenFileEntry;

// 全局变量：文件系统核心数据结构
UserEntry mfd[MAX_USERS];         // 主目录（存储所有用户）
OpenFileEntry afd[MAX_OPEN_FILES];// 打开文件目录（存储当前打开的文件）
UserEntry *current_user = NULL;   // 当前登录用户指针

/**
 * 初始化文件系统：初始化MFD和AFD，添加测试用户
 */
void init_system() {
    // 初始化AFD：所有条目设为无效
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        afd[i].is_valid = 0;
        afd[i].file_ptr = NULL;
    }

    // 初始化MFD：添加2个测试用户（user1、user2）
    strcpy(mfd[0].username, "user1");
    mfd[0].file_count = 0;
    mfd[0].is_valid = 1;

    strcpy(mfd[1].username, "user2");
    mfd[1].file_count = 0;
    mfd[1].is_valid = 1;

    // 其余用户槽位设为无效
    for (int i = 2; i < MAX_USERS; i++) {
        mfd[i].is_valid = 0;
    }

    printf("=== 文件系统初始化完成 ===\n");
    printf("测试用户：user1、user2（无需密码，直接输入用户名登录）\n");
}

/**
 * 用户登录：根据用户名查找MFD，设置当前登录用户
 * @return 1=登录成功，0=登录失败
 */
int login() {
    char username[USERNAME_LEN];
    printf("\n请输入用户名：");
    scanf("%s", username);

    // 遍历MFD查找用户
    for (int i = 0; i < MAX_USERS; i++) {
        if (mfd[i].is_valid && strcmp(mfd[i].username, username) == 0) {
            current_user = &mfd[i];
            printf("登录成功！当前用户：%s\n", current_user->username);
            return 1;
        }
    }

    printf("登录失败：用户名不存在！\n");
    return 0;
}

/**
 * 1. 创建文件（Create）：在当前用户UFD中添加新文件
 */
int create_file() {
    // 检查文件数量是否达上限
    if (current_user->file_count >= MAX_FILES_PER_USER) {
        printf("错误：文件数量已达上限（最多%d个）！\n", MAX_FILES_PER_USER);
        return 0;
    }

    char filename[FILENAME_LEN];
    int permission;

    // 输入文件名并检查重复
    printf("请输入文件名：");
    scanf("%s", filename);
    for (int i = 0; i < MAX_FILES_PER_USER; i++) {
        if (current_user->files[i].is_valid && strcmp(current_user->files[i].filename, filename) == 0) {
            printf("错误：文件名「%s」已存在！\n", filename);
            return 0;
        }
    }

    // 输入保护码（0-7，对应r/w/x三位权限）
    printf("请输入保护码（0-7，二进制rwx，如7=111=读写执行）：");
    scanf("%d", &permission);
    if (permission < 0 || permission > 7) {
        printf("错误：保护码无效！必须是0-7的整数。\n");
        return 0;
    }

    // 查找UFD中的空闲槽位
    int empty_idx = -1;
    for (int i = 0; i < MAX_FILES_PER_USER; i++) {
        if (!current_user->files[i].is_valid) {
            empty_idx = i;
            break;
        }
    }

    // 初始化文件项
    FileEntry *new_file = &current_user->files[empty_idx];
    strcpy(new_file->filename, filename);
    new_file->permission = permission;
    new_file->length = 0;         // 初始长度为0
    new_file->rw_ptr = 0;         // 初始读写指针为0
    new_file->is_valid = 1;       // 标记为有效文件
    current_user->file_count++;    // 更新文件计数

    printf("成功：文件「%s」创建完成，保护码：%d\n", filename, permission);
    return 1;
}

/**
 * 2. 删除文件（Delete）：从当前用户UFD中删除文件（标记为无效）
 */
int delete_file() {
    char filename[FILENAME_LEN];
    printf("请输入要删除的文件名：");
    scanf("%s", filename);

    // 查找文件并检查是否已打开
    for (int i = 0; i < MAX_FILES_PER_USER; i++) {
        FileEntry *file = &current_user->files[i];
        if (file->is_valid && strcmp(file->filename, filename) == 0) {
            // 检查文件是否正在打开
            for (int j = 0; j < MAX_OPEN_FILES; j++) {
                if (afd[j].is_valid && afd[j].file_ptr == file) {
                    printf("错误：文件「%s」正在打开中，无法删除！\n", filename);
                    return 0;
                }
            }

            // 标记文件为无效（逻辑删除）
            file->is_valid = 0;
            current_user->file_count--;
            printf("成功：文件「%s」已删除\n", filename);
            return 1;
        }
    }

    printf("错误：文件「%s」不存在！\n", filename);
    return 0;
}

/**
 * 3. 打开文件（Open）：将文件添加到AFD，初始化读写指针
 */
int open_file() {
    // 检查AFD是否已满（一次只能打开一个文件）
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        if (afd[i].is_valid) {
            printf("错误：当前已打开一个文件，请先关闭！\n");
            return 0;
        }
    }

    char filename[FILENAME_LEN];
    printf("请输入要打开的文件名：");
    scanf("%s", filename);

    // 查找用户文件
    FileEntry *target_file = NULL;
    for (int i = 0; i < MAX_FILES_PER_USER; i++) {
        if (current_user->files[i].is_valid && strcmp(current_user->files[i].filename, filename) == 0) {
            target_file = &current_user->files[i];
            break;
        }
    }

    if (target_file == NULL) {
        printf("错误：文件「%s」不存在！\n", filename);
        return 0;
    }

    // 查找AFD空闲槽位并初始化
    int afd_idx = -1;
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        if (!afd[i].is_valid) {
            afd_idx = i;
            break;
        }
    }

    OpenFileEntry *open_file = &afd[afd_idx];
    strcpy(open_file->filename, filename);
    open_file->file_ptr = target_file;
    open_file->permission = target_file->permission;
    open_file->rw_ptr = 0;         // 打开时读写指针置0
    open_file->is_valid = 1;       // 标记为有效打开文件

    printf("成功：文件「%s」打开完成\n", filename);
    return 1;
}

/**
 * 4. 关闭文件（Close）：从AFD中移除文件
 */
int close_file() {
    char filename[FILENAME_LEN];
    printf("请输入要关闭的文件名：");
    scanf("%s", filename);

    // 查找AFD中的打开文件
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        if (afd[i].is_valid && strcmp(afd[i].filename, filename) == 0) {
            afd[i].is_valid = 0;    // 标记为无效
            afd[i].file_ptr = NULL; // 解除指针关联
            printf("成功：文件「%s」关闭完成\n", filename);
            return 1;
        }
    }

    printf("错误：文件「%s」未打开！\n", filename);
    return 0;
}

/**
 * 5. 读取文件（Read）：移动读写指针（模拟读取，无实际I/O）
 */
int read_file() {
    char filename[FILENAME_LEN];
    int read_len;

    printf("请输入要读取的文件名：");
    scanf("%s", filename);
    printf("请输入读取字节数：");
    scanf("%d", &read_len);

    // 查找AFD中的打开文件
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        OpenFileEntry *open_file = &afd[i];
        if (open_file->is_valid && strcmp(open_file->filename, filename) == 0) {
            // 检查读权限（bit0是否为1）
            if (!(open_file->permission & PERM_R)) {
                printf("错误：文件「%s」无读取权限！\n", filename);
                return 0;
            }

            // 计算实际可读字节数（不超过文件长度）
            int real_read = read_len;
            if (open_file->rw_ptr + read_len > open_file->file_ptr->length) {
                real_read = open_file->file_ptr->length - open_file->rw_ptr;
                printf("警告：文件剩余字节不足，实际读取%d字节\n", real_read);
            }

            // 移动读写指针
            open_file->rw_ptr += real_read;
            printf("成功：读取完成，当前读写指针位置：%d\n", open_file->rw_ptr);
            return 1;
        }
    }

    printf("错误：文件「%s」未打开！\n", filename);
    return 0;
}

/**
 * 6. 写入文件（Write）：移动读写指针并扩展文件长度（模拟写入）
 */
int write_file() {
    char filename[FILENAME_LEN];
    int write_len;

    printf("请输入要写入的文件名：");
    scanf("%s", filename);
    printf("请输入写入字节数：");
    scanf("%d", &write_len);

    // 查找AFD中的打开文件
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        OpenFileEntry *open_file = &afd[i];
        if (open_file->is_valid && strcmp(open_file->filename, filename) == 0) {
            // 检查写权限（bit1是否为1）
            if (!(open_file->permission & PERM_W)) {
                printf("错误：文件「%s」无写入权限！\n", filename);
                return 0;
            }

            // 移动读写指针并扩展文件长度
            open_file->rw_ptr += write_len;
            if (open_file->rw_ptr > open_file->file_ptr->length) {
                open_file->file_ptr->length = open_file->rw_ptr;
            }

            printf("成功：写入完成，文件当前长度：%d，读写指针位置：%d\n",
                   open_file->file_ptr->length, open_file->rw_ptr);
            return 1;
        }
    }

    printf("错误：文件「%s」未打开！\n", filename);
    return 0;
}

/**
 * 7. 扩展命令：移动读写指针（Lseek）
 * 功能：直接设置文件的读写指针位置（需文件已打开）
 */
int lseek_file() {
    char filename[FILENAME_LEN];
    int target_pos;

    printf("请输入要移动指针的文件名（需已打开）：");
    scanf("%s", filename);
    printf("请输入目标指针位置（非负整数）：");
    scanf("%d", &target_pos);

    // 检查目标位置合法性
    if (target_pos < 0) {
        printf("错误：目标位置不能为负数！\n");
        return 0;
    }

    // 查找AFD中的打开文件
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        OpenFileEntry *open_file = &afd[i];
        if (open_file->is_valid && strcmp(open_file->filename, filename) == 0) {
            open_file->rw_ptr = target_pos;
            printf("成功：读写指针已移动到位置%d\n", target_pos);
            return 1;
        }
    }

    printf("错误：文件「%s」未打开！\n", filename);
    return 0;
}

/**
 * 8. 扩展命令：修改保护级别（Chmod）
 * 功能：修改文件的三位保护码（需文件存在，无需打开）
 */
int chmod_file() {
    char filename[FILENAME_LEN];
    int new_perm;

    printf("请输入要修改的文件名：");
    scanf("%s", filename);
    printf("请输入新保护码（0-7，二进制rwx）：");
    scanf("%d", &new_perm);

    // 检查保护码合法性
    if (new_perm < 0 || new_perm > 7) {
        printf("错误：保护码无效！必须是0-7的整数。\n");
        return 0;
    }

    // 查找文件并更新保护码
    for (int i = 0; i < MAX_FILES_PER_USER; i++) {
        FileEntry *file = &current_user->files[i];
        if (file->is_valid && strcmp(file->filename, filename) == 0) {
            // 同步已打开文件的权限（如果文件正在打开）
            for (int j = 0; j < MAX_OPEN_FILES; j++) {
                if (afd[j].is_valid && afd[j].file_ptr == file) {
                    afd[j].permission = new_perm;
                    printf("警告：文件正在打开，已同步更新权限！\n");
                }
            }

            file->permission = new_perm;
            printf("成功：文件「%s」保护码已修改为%d\n", filename, new_perm);
            return 1;
        }
    }

    printf("错误：文件「%s」不存在！\n", filename);
    return 0;
}

/**
 * 9. 扩展命令：更换文件名（Rename）
 * 功能：修改文件的名称（需文件存在，支持已打开文件同步更新）
 */
int rename_file() {
    char old_name[FILENAME_LEN], new_name[FILENAME_LEN];

    printf("请输入原文件名：");
    scanf("%s", old_name);
    printf("请输入新文件名：");
    scanf("%s", new_name);

    // 检查新文件名是否重复
    for (int i = 0; i < MAX_FILES_PER_USER; i++) {
        if (current_user->files[i].is_valid && strcmp(current_user->files[i].filename, new_name) == 0) {
            printf("错误：新文件名「%s」已存在！\n", new_name);
            return 0;
        }
    }

    // 查找原文件并修改名称
    for (int i = 0; i < MAX_FILES_PER_USER; i++) {
        FileEntry *file = &current_user->files[i];
        if (file->is_valid && strcmp(file->filename, old_name) == 0) {
            // 同步已打开文件的名称（如果文件正在打开）
            for (int j = 0; j < MAX_OPEN_FILES; j++) {
                if (afd[j].is_valid && afd[j].file_ptr == file) {
                    strcpy(afd[j].filename, new_name);
                    printf("警告：文件正在打开，已同步更新文件名！\n");
                }
            }

            strcpy(file->filename, new_name);
            printf("成功：文件名已从「%s」修改为「%s」\n", old_name, new_name);
            return 1;
        }
    }

    printf("错误：原文件「%s」不存在！\n", old_name);
    return 0;
}

/**
 * 显示命令菜单
 */
void show_menu() {
    printf("\n==================== 文件系统命令菜单 ====================\n");
    printf("1. 创建文件（Create）        2. 删除文件（Delete）\n");
    printf("3. 打开文件（Open）          4. 关闭文件（Close）\n");
    printf("5. 读取文件（Read）          6. 写入文件（Write）\n");
    printf("7. 移动读写指针（Lseek）     8. 修改保护级别（Chmod）\n");
    printf("9. 更换文件名（Rename）      0. 退出系统\n");
    printf("==========================================================\n");
    printf("请输入命令编号（0-9）：");
}

/**
 * 主函数：程序入口
 */
int main() {
    int choice;

    // 初始化系统并强制登录
    init_system();
    while (!login()) {
        printf("请重新尝试登录！\n");
    }

    // 命令循环（持续接收用户操作）
    while (1) {
        show_menu();
        scanf("%d", &choice);

        // 根据选择执行对应命令
        switch (choice) {
            case 1: create_file(); break;
            case 2: delete_file(); break;
            case 3: open_file(); break;
            case 4: close_file(); break;
            case 5: read_file(); break;
            case 6: write_file(); break;
            case 7: lseek_file(); break;
            case 8: chmod_file(); break;
            case 9: rename_file(); break;
            case 0:
                printf("\n感谢使用，退出文件系统！\n");
                return 0;
            default:
                printf("错误：无效的命令编号，请输入0-9之间的数字！\n");
                break;
        }
    }

    return 0;
}