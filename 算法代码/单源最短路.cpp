/**
 * 题目来源是洛谷P4779
 * 描述如下：
 * 给定一个 n 个点，m 条有向边的带非负权图，请你计算从 s 出发，到每个点的距离。
 * 数据保证你能从 s 出发到任意点。
 * 
 * 输入格式：
 * 第一行为三个正整数n,m,s
 * 第二行起m行，每行三个非负整数u_i,v_i,W_i，表示从u_i到v_i有一条权值为w_i的有向边
 * 
 * 输出格式：
 * 输出一行n个空格分割的非负整数，表示s到每个点的距离
 * 
 * 
 */
#include <bits/stdc++.h>
using namespace std;
int N;
int M;
int S;
const int max_limit = 1e9;
void Dijkstra(int** G) {
    int dist[N + 1];
    for(int i = 1; i <= N; i++) {
        dist[i] = max_limit;
    }
    dist[S] = 0;
    set<int> u;
    for(int i = 1; i <= N; i++) {
        u.insert(i);
    }
    while(!u.empty()) {
        int min_distance = max_limit;
        int min_p;    
        for(int i : u) {
            if(dist[i] < min_distance) {
                min_distance = dist[i];
                min_p = i;
            }
        }
        u.erase(min_p);
        int v = min_p;
        for(int i = 1; i <= N; i++) {
            if(G[v][i] != max_limit) {
                dist[i] = min(dist[i], dist[v] + G[v][i]);
            }
        }
    }
    for(int i = 1; i <= N; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;
}
int main() {
    cin >> N >> M >> S;
    int** G = (int**)malloc(sizeof(int*) * (N + 1));
    for(int i = 0; i <= N; i++) {
        G[i] = (int*)malloc(sizeof(int) * (N + 1));
    }
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            G[i][j] = max_limit;
        }
    }
    for(int i = 1; i <= N; i++) {
        G[i][i] = 0;
    }
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u][v] = w;
    }
    Dijkstra(G);
    return 0;
}
