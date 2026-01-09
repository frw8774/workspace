#include <stdio.h>
#include <stdint.h>

// 页表项结构：存储物理块号
typedef struct {
    uint32_t physical_block_num;  // 物理块号
} PageTableEntry;

// 段表项结构：存储页表基址（页表起始地址）和页表长度（该段拥有的页数）
typedef struct {
    uint32_t page_table_base;     // 页表基址（指向页表的起始位置）
    uint32_t page_table_length;   // 页表长度（该段的页数）
} SegmentTableEntry;

#define SEGMENT_TABLE_SIZE 2      // 段表大小（系统支持2个段：段0、段1）
#define PAGE_OFFSET_BITS 4        // 页内偏移位数（4位，对应页大小16字节）
#define PAGE_SIZE (1 << PAGE_OFFSET_BITS)  // 页大小：16字节

// 定义段表（全局变量，初始化2个段的信息）
SegmentTableEntry segment_table[SEGMENT_TABLE_SIZE] = {
    {0, 3},  // 段0：页表基址0，页表长度3（拥有页0、页1、页2）
    {3, 2}   // 段1：页表基址3，页表长度2（拥有页0、页1）
};

// 定义页表（全局变量，整合所有段的页表项，共3+2=5个页表项）
PageTableEntry page_table[5] = {
    {10},  // 段0-页0：物理块号10
    {20},  // 段0-页1：物理块号20
    {30},  // 段0-页2：物理块号30
    {40},  // 段1-页0：物理块号40
    {50}   // 段1-页1：物理块号50
};

//打印段表完整信息
void print_segment_table() {
    printf("\n================== 完整段表信息 ==================\n");
    printf("段号\t页表基址（十六进制）\t页表长度（页数）\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < SEGMENT_TABLE_SIZE; i++) {
        printf("%u\t0x%08X\t\t\t%u\n", 
               i, 
               segment_table[i].page_table_base, 
               segment_table[i].page_table_length);
    }
    printf("==================================================\n");
}

//打印页表完整信息
void print_page_table() {
    printf("\n================== 完整页表信息 ==================\n");
    // 先打印表头
    printf("页表项索引\t物理块号\t所属段-页对应关系\n");
    printf("--------------------------------------------------\n");
    // 遍历全局页表，标注每个页表项的所属段和页
    for (int i = 0; i < sizeof(page_table)/sizeof(PageTableEntry); i++) {
        char belong_info[50] = "未关联（无效项）";
        // 判断属于段0的页表项
        if (i >= segment_table[0].page_table_base && 
            i < segment_table[0].page_table_base + segment_table[0].page_table_length) {
            int page_num = i - segment_table[0].page_table_base;
            snprintf(belong_info, sizeof(belong_info), "段0-页%u", page_num);
        }
        // 判断属于段1的页表项
        else if (i >= segment_table[1].page_table_base && 
                 i < segment_table[1].page_table_base + segment_table[1].page_table_length) {
            int page_num = i - segment_table[1].page_table_base;
            snprintf(belong_info, sizeof(belong_info), "段1-页%u", page_num);
        }
        // 打印页表项信息
        printf("%u\t\t%u\t\t%s\n", 
               i, 
               page_table[i].physical_block_num, 
               belong_info);
    }
    printf("==================================================\n");
}

uint32_t segment_page_address_translation(uint32_t logical_addr) {
    // 1. 拆分逻辑地址：段号(S)、段内页号(P)、页内偏移(W)
    uint32_t segment_num = (logical_addr >> (16)) & 0xFF;  // 取高8位作为段号（20位地址：第19-12位）
    uint32_t page_num = (logical_addr >> PAGE_OFFSET_BITS) & 0xFF;  // 中间8位作为页号（第11-4位）
    uint32_t offset = logical_addr & ((1 << PAGE_OFFSET_BITS) - 1);  // 低4位作为页内偏移（第3-0位）

    // 打印拆分后的逻辑地址信息
    printf("--------------------------------------------------\n");
    printf("转换前逻辑地址：0x%05X（十进制：%u）\n", logical_addr, logical_addr);
    printf("逻辑地址拆分：段号(S)=%u，段内页号(P)=%u，页内偏移(W)=%u\n", 
           segment_num, page_num, offset);

    // 2. 查找段表，判断段号是否有效
    if (segment_num >= SEGMENT_TABLE_SIZE) {
        printf("段表查找失败：段号%u超出段表大小%u，地址无效！\n", segment_num, SEGMENT_TABLE_SIZE);
        return 0xFFFFFFFF;  // 返回无效地址标记
    }
    SegmentTableEntry *seg_entry = &segment_table[segment_num];
    printf("段表项信息：页表基址=0x%08X，页表长度=%u\n", 
           seg_entry->page_table_base, seg_entry->page_table_length);

    // 3. 查找页表，判断页号是否有效
    if (page_num >= seg_entry->page_table_length) {
        printf("页表查找失败：段%u的页号%u超出页表长度%u，地址无效！\n", 
               segment_num, page_num, seg_entry->page_table_length);
        return 0xFFFFFFFF;  // 返回无效地址标记
    }
    // 计算页表项在全局页表中的索引（页表基址 + 段内页号）
    uint32_t page_table_index = seg_entry->page_table_base + page_num;
    PageTableEntry *page_entry = &page_table[page_table_index];
    printf("页表项信息：物理块号=%u\n", page_entry->physical_block_num);

    // 4. 计算物理地址：物理块号 * 页大小 + 页内偏移
    uint32_t physical_addr = (page_entry->physical_block_num * PAGE_SIZE) + offset;
    return physical_addr;
}

int main() {
    printf("=== 段页式存储管理地址转换模拟===\n");
    printf("基础配置信息：页大小=%u字节，段表大小=%u，总页表项数=%lu\n", 
           PAGE_SIZE, SEGMENT_TABLE_SIZE, sizeof(page_table)/sizeof(PageTableEntry));

    //打印完整段表和页表
    print_segment_table();
    print_page_table();

    // 定义测试用例（包含有效地址和无效地址）
    uint32_t test_logical_addrs[] = {
        0x0000F,   // 段0-页0-偏移15（有效）
        0x00110,   // 段0-页1-偏移0（有效）
        0x00205,   // 段0-页2-偏移5（有效）
        0x0100A,   // 段1-页0-偏移10（有效）
        0x01103,   // 段1-页1-偏移3（有效）
        0x00300,   // 段0-页3-偏移0（无效：页号超出段0页表长度）
        0x02000,   // 段2-页0-偏移0（无效：段号超出段表大小）
        0x0120F    // 段1-页2-偏移15（无效：页号超出段1页表长度）
    };
    int test_count = sizeof(test_logical_addrs) / sizeof(uint32_t);

    // 遍历测试用例进行地址转换
    printf("\n=== 开始执行地址转换测试 ===\n");
    for (int i = 0; i < test_count; i++) {
        uint32_t phy_addr = segment_page_address_translation(test_logical_addrs[i]);
        if (phy_addr != 0xFFFFFFFF) {
            printf("转换后物理地址：0x%05X（十进制：%u）\n", phy_addr, phy_addr);
        }
    }
    printf("--------------------------------------------------\n");
    printf("=== 地址转换模拟结束 ===\n");
    return 0;
}