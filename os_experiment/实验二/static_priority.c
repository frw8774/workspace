#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 常量定义
#define RESOURCE_NUM 3  // 资源种类：0-内存(MB)、1-打印机(台)、2-磁盘(台)
#define MAX_JOB 10       // 最大支持作业数
#define PRIORITY_LOW 10  // 优先级参考：数值越小，优先级越高（1最高，10最低）

// 系统资源结构体
typedef struct {
    int total[RESOURCE_NUM];   // 各类资源总数
    int free[RESOURCE_NUM];    // 各类资源空闲数
} SystemResource;

// 作业结构体（新增静态优先级字段）
typedef struct {
    int id;                     // 作业ID
    int arrive_time;            // 到达时间
    int need_res[RESOURCE_NUM]; // 所需各类资源数
    int run_time;               // 估计运行时间
    int priority;               // 静态优先级（数值越小优先级越高，输入后保持不变）
    int start_time;             // 开始执行时间
    int finish_time;            // 完成时间
    float turnaround_time;      // 周转时间（完成时间-到达时间）
    float weighted_turnaround;  // 带权周转时间（周转时间/运行时间）
    int status;                 // 作业状态：0-等待、1-运行、2-完成
} Job;

// 初始化系统资源
void init_system_resource(SystemResource *sys_res) {
    // 配置系统总资源：1024MB内存、2台打印机、3台磁盘
    sys_res->total[0] = 1024;
    sys_res->total[1] = 2;
    sys_res->total[2] = 3;
    // 初始空闲资源等于总资源
    memcpy(sys_res->free, sys_res->total, sizeof(int) * RESOURCE_NUM);
    
    printf("=== 系统资源初始化完成 ===\n");
    printf("总内存:%dMB,空闲内存:%dMB\n", sys_res->total[0], sys_res->free[0]);
    printf("总打印机:%d台,空闲打印机:%d台\n", sys_res->total[1], sys_res->free[1]);
    printf("总磁盘:%d台,空闲磁盘:%d台\n", sys_res->total[2], sys_res->free[2]);
    printf("============================\n");
}

// 输入作业信息（新增静态优先级输入/默认预设）
int input_jobs(Job jobs[]) {
    int n;
    printf("请输入作业数量(最大%d):", MAX_JOB);
    scanf("%d", &n);

    // 合法性校验，默认生成4个测试作业（带不同优先级）
    if (n < 1 || n > MAX_JOB) {
        printf("作业数量无效,自动生成4个测试作业\n");
        n = 4;
        // 作业1：0时刻到达，优先级2，512MB内存、1台打印机、1台磁盘，运行5时间单位
        jobs[0] = (Job){1, 0, {512, 1, 1}, 5, 2, 0, 0, 0.0, 0.0, 0};
        // 作业2：1时刻到达，优先级1（最高），256MB内存、1台打印机、1台磁盘，运行3时间单位
        jobs[1] = (Job){2, 1, {256, 1, 1}, 3, 1, 0, 0, 0.0, 0.0, 0};
        // 作业3：2时刻到达，优先级3，128MB内存、0台打印机、1台磁盘，运行4时间单位
        jobs[2] = (Job){3, 2, {128, 0, 1}, 4, 3, 0, 0, 0.0, 0.0, 0};
        // 作业4：3时刻到达，优先级2，64MB内存、0台打印机、1台磁盘，运行2时间单位
        jobs[3] = (Job){4, 3, {64, 0, 1}, 2, 2, 0, 0, 0.0, 0.0, 0};
    } else {
        // 手动输入作业信息（新增优先级输入）
        for (int i = 0; i < n; i++) {
            printf("=== 输入第%d个作业信息 ===\n", i+1);
            jobs[i].id = i+1;
            printf("到达时间:");
            scanf("%d", &jobs[i].arrive_time);
            printf("所需内存(MB):");
            scanf("%d", &jobs[i].need_res[0]);
            printf("所需打印机(台):");
            scanf("%d", &jobs[i].need_res[1]);
            printf("所需磁盘(台):");
            scanf("%d", &jobs[i].need_res[2]);
            printf("估计运行时间:");
            scanf("%d", &jobs[i].run_time);
            printf("静态优先级(1最高,10最低):");
            scanf("%d", &jobs[i].priority);
            jobs[i].status = 0; // 初始状态为等待
            printf("============================\n");
        }
    }

    // 输出作业清单（新增优先级列）
    printf("=== 作业信息清单 ===\n");
    printf("作业ID\t到达时间\t内存需求\t打印机需求\t磁盘需求\t运行时间\t静态优先级\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               jobs[i].id, jobs[i].arrive_time, jobs[i].need_res[0],
               jobs[i].need_res[1], jobs[i].need_res[2], jobs[i].run_time, jobs[i].priority);
    }
    printf("============================\n");
    return n;
}

// 按静态优先级规则排序作业（核心修改：先优先级，再到达时间，后作业ID）
void sort_jobs_by_priority(Job jobs[], int n) {
    Job temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            // 排序规则：1. 优先级数值小的优先；2. 优先级相同，到达时间早的优先；3. 前两者相同，ID小的优先
            if (jobs[j].priority > jobs[j+1].priority ||
                (jobs[j].priority == jobs[j+1].priority && jobs[j].arrive_time > jobs[j+1].arrive_time) ||
                (jobs[j].priority == jobs[j+1].priority && jobs[j].arrive_time == jobs[j+1].arrive_time && jobs[j].id > jobs[j+1].id)) {
                temp = jobs[j];
                jobs[j] = jobs[j+1];
                jobs[j+1] = temp;
            }
        }
    }
    printf("作业已按静态优先级规则完成排序(优先级越小越优先)\n");
    printf("============================\n");
}

// 检查空闲资源是否满足作业需求
int is_resource_enough(SystemResource *sys_res, Job *job) {
    for (int i = 0; i < RESOURCE_NUM; i++) {
        if (sys_res->free[i] < job->need_res[i]) {
            return 0; // 资源不足
        }
    }
    return 1; // 资源充足
}

// 为作业分配资源
void allocate_resource(SystemResource *sys_res, Job *job) {
    for (int i = 0; i < RESOURCE_NUM; i++) {
        sys_res->free[i] -= job->need_res[i];
    }
    job->status = 1; // 标记为运行状态
    printf("作业%d(优先级%d)资源分配成功\n", job->id, job->priority);
    printf("分配内存:%dMB,剩余空闲内存:%dMB\n", job->need_res[0], sys_res->free[0]);
    printf("分配打印机:%d台,剩余空闲打印机:%d台\n", job->need_res[1], sys_res->free[1]);
    printf("分配磁盘:%d台,剩余空闲磁盘:%d台\n", job->need_res[2], sys_res->free[2]);
    printf("============================\n");
}

// 释放作业占用的资源
void release_resource(SystemResource *sys_res, Job *job) {
    for (int i = 0; i < RESOURCE_NUM; i++) {
        sys_res->free[i] += job->need_res[i];
    }
    job->status = 2; // 标记为完成状态
    printf("作业%d(优先级%d)执行完成,资源释放成功:\n", job->id, job->priority);
    printf("释放内存:%dMB,剩余空闲内存:%dMB\n", job->need_res[0], sys_res->free[0]);
    printf("释放打印机:%d台,剩余空闲打印机:%d台\n", job->need_res[1], sys_res->free[1]);
    printf("释放磁盘:%d台,剩余空闲磁盘:%d台\n", job->need_res[2], sys_res->free[2]);
    printf("============================\n");
}

// 静态优先级作业调度核心逻辑
void job_schedule(Job jobs[], int n, SystemResource *sys_res) {
    int current_time = 0;          // 当前系统时间
    int completed_job = 0;         // 已完成作业数
    int running_jobs[MAX_JOB] = {0};// 运行中作业索引（0为无效标记）
    int running_count = 0;         // 运行中作业数量

    printf("=== 开始静态优先级作业调度 ===\n");
    printf("============================\n");

    while (completed_job < n) {
        // 1. 尝试为已到达的等待作业分配资源（按优先级排序后的顺序）
        for (int i = 0; i < n; i++) {
            if (jobs[i].status == 0 && jobs[i].arrive_time <= current_time) {
                if (is_resource_enough(sys_res, &jobs[i])) {
                    jobs[i].start_time = current_time;
                    allocate_resource(sys_res, &jobs[i]);
                    running_jobs[running_count++] = i; // 加入运行队列
                }
            }
        }

        // 2. 无运行作业时，推进时间到下一个作业到达时间
        if (running_count == 0) {
            int next_arrive = -1;
            for (int i = 0; i < n; i++) {
                if (jobs[i].status == 0) {
                    next_arrive = (next_arrive == -1) ? jobs[i].arrive_time : fmin(next_arrive, jobs[i].arrive_time);
                }
            }
            if (next_arrive != -1) {
                current_time = next_arrive;
                printf("当前无运行作业,系统时间推进到:%d\n", current_time);
                printf("============================\n");
            }
            continue;
        }

        // 3. 找到运行队列中最早完成的作业
        int earliest_idx = -1;
        int earliest_finish = -1;
        for (int i = 0; i < running_count; i++) {
            int job_idx = running_jobs[i];
            int finish_time = jobs[job_idx].start_time + jobs[job_idx].run_time;
            if (earliest_finish == -1 || finish_time < earliest_finish) {
                earliest_finish = finish_time;
                earliest_idx = i;
            }
        }

        // 4. 推进系统时间到最早完成时间
        current_time = earliest_finish;
        printf("系统时间推进到:%d\n", current_time);
        printf("============================\n");

        // 5. 处理完成的作业
        int finished_job_idx = running_jobs[earliest_idx];
        Job *finished_job = &jobs[finished_job_idx];
        finished_job->finish_time = current_time;
        finished_job->turnaround_time = finished_job->finish_time - finished_job->arrive_time;
        finished_job->weighted_turnaround = finished_job->turnaround_time / (float)finished_job->run_time;
        release_resource(sys_res, finished_job);
        completed_job++;

        // 6. 从运行队列移除完成的作业
        for (int i = earliest_idx; i < running_count-1; i++) {
            running_jobs[i] = running_jobs[i+1];
        }
        running_jobs[--running_count] = 0;

        // 输出作业调度详情
        printf("作业%d调度详情:\n", finished_job->id);
        printf("优先级:%d | 到达时间:%d | 开始时间:%d | 完成时间:%d\n",
               finished_job->priority, finished_job->arrive_time, finished_job->start_time, finished_job->finish_time);
        printf("周转时间:%.1f | 带权周转时间:%.2f\n",
               finished_job->turnaround_time, finished_job->weighted_turnaround);
        printf("============================\n");
    }

    printf("=== 所有作业调度完成 ===\n");
    printf("============================\n");
}

// 输出调度统计结果（新增优先级列）
void output_statistics(Job jobs[], int n) {
    float avg_turnaround = 0.0;
    float avg_weighted_turnaround = 0.0;

    printf("=== 作业调度统计总表 ===\n");
    printf("作业ID\t优先级\t到达时间\t开始时间\t完成时间\t周转时间\t带权周转时间\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t\t%d\t\t%.1f\t\t%.2f\n",
               jobs[i].id, jobs[i].priority, jobs[i].arrive_time, jobs[i].start_time,
               jobs[i].finish_time, jobs[i].turnaround_time, jobs[i].weighted_turnaround);
        avg_turnaround += jobs[i].turnaround_time;
        avg_weighted_turnaround += jobs[i].weighted_turnaround;
    }

    // 计算平均值
    avg_turnaround /= n;
    avg_weighted_turnaround /= n;
    printf("============================\n");
    printf("平均周转时间:%.1f\n", avg_turnaround);
    printf("平均带权周转时间:%.2f\n", avg_weighted_turnaround);
    printf("============================\n");
}

// 主函数
int main() {
    SystemResource sys_res;
    Job jobs[MAX_JOB];

    // 初始化系统资源
    init_system_resource(&sys_res);

    // 输入作业信息
    int job_num = input_jobs(jobs);

    // 按静态优先级排序作业
    sort_jobs_by_priority(jobs, job_num);

    // 执行调度
    job_schedule(jobs, job_num, &sys_res);

    // 输出统计
    output_statistics(jobs, job_num);

    return 0;
}