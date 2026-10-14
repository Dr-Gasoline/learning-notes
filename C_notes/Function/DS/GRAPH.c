/*
 * ==========================================
 * 图算法 
 * 包含：邻接矩阵、邻接表、DFS/BFS、Prim(矩阵+邻接表)、Kruskal
 * ==========================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 105
#define MAX_EDGES 10000
#define INF 0x3f3f3f3f

/* ========== 全局变量 ========== */
int nn, ne;                // 顶点数，边数
int visited[MAX_VERTICES]; // 访问标记
int stamp = 1;             // 时间戳。注意：每次执行新的搜索前，务必 stamp++; ！！！

// ---------- 邻接矩阵存储 ----------
int edge[MAX_VERTICES][MAX_VERTICES];

// ==========================================
// 第一部分：邻接矩阵操作
// ==========================================

// 初始化邻接矩阵
void initMatrix(int n) {
    nn = n;
    ne = 0;
    for (int i = 0; i < nn; i++) {
        for (int j = 0; j < nn; j++) {
            if (i == j) edge[i][j] = 0;
            else edge[i][j] = INF; // INF代表无边
        }
    }
}

// 添加一条无向边 (矩阵版)
void addEdgeMatrix(int u, int v, int w) {
    if (edge[u][v] == INF) ne++;
    edge[u][v] = w;
    edge[v][u] = w;
}

// 1. 邻接矩阵 DFS
void DFS_Matrix(int root) {
    visited[root] = stamp;
    // 此处可添加处理 root 的代码

    for (int i = 0; i < nn; i++) {
        if (visited[i] < stamp && edge[root][i] != INF) {
            DFS_Matrix(i);
        }
    }
}

// 2. 邻接矩阵 BFS
void BFS_Matrix(int start) {
    int queue[MAX_VERTICES];
    int f = 0, r = 0;

    queue[r++] = start;
    visited[start] = stamp;

    while (f != r) {
        int p = queue[f++]; // 出队
        // 此处可添加处理 p 的代码

        for (int i = 0; i < nn; i++) {
            if (visited[i] < stamp && edge[p][i] != INF) {
                queue[r++] = i;
                visited[i] = stamp;
            }
        }
    }
}

// 3. 邻接矩阵 Prim 最小生成树
void Prim_Matrix(int start) {
    int lowcost[MAX_VERTICES]; // 所有节点与当前生成树的权值距离
    int adjvex[MAX_VERTICES]; // 记录当前生成树中距离 i 最近的节点，若本轮选中 i ，则表示前驱节点

    for (int i = 0; i < nn; i++) { // 以start节点初始化数据
        lowcost[i] = edge[start][i];
        adjvex[i] = start;
    }
    lowcost[start] = 0; // 0代表已加入生成树

    for (int i = 1; i < nn; i++) { // 循环nn次，将所有节点加入生成树
        int min = INF, minIdx = -1;

        for (int j = 0; j < nn; j++) { // 记录当前最近的节点
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j];
                minIdx = j;
            }
        }
        if (minIdx == -1) break; // 图不连通
        // 在这里对新加入的路径 (adjvex[minIdx]---minIdx) 以及权重 (lowcost[minIdx]) 做调用

        lowcost[minIdx] = 0; // 加入生成树

        for (int j = 0; j < nn; j++) { // 根据新加入的节点，更新各节点到生成树的权值距离以及前驱
            if (lowcost[j] != 0 && edge[minIdx][j] < lowcost[j]) {
                lowcost[j] = edge[minIdx][j];
                adjvex[j] = minIdx;
            }
        }
    }
}

// ==========================================
// 第二部分：邻接表操作
// ==========================================

// ---------- 邻接表存储 ----------
typedef struct EdgeNode {
    int adjvex; // 边指向节点的编号
    int weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct VertexNode {
    int data;
    EdgeNode *firstedge;
} VertexNode;

VertexNode adjList[MAX_VERTICES];

// 初始化邻接表
void initAdjList(int n) {
    nn = n;
    ne = 0;
    for (int i = 0; i < nn; i++) {
        adjList[i].data = i;
        adjList[i].firstedge = NULL; // 若有多组测试用例，最好先 free 掉旧链表
    }
}

// 添加一条有向边 (u -> v)，无向图需调用两次
void addEdgeAL(int u, int v, int w) {
    EdgeNode *node = (EdgeNode *)malloc(sizeof(EdgeNode));
    node->adjvex = v;
    node->weight = w;
    node->next = adjList[u].firstedge;
    adjList[u].firstedge = node;
    ne++;
}

// 邻接表 DFS
void DFS_AL(int root) {
    visited[root] = stamp;
    // 此处可添加处理 root 的代码

    EdgeNode *p = adjList[root].firstedge;
    while (p != NULL) {
        if (visited[p->adjvex] < stamp) {
            DFS_AL(p->adjvex);
        }
        p = p->next;
    }
}

// 邻接表 BFS
void BFS_AL(int start) {
    int queue[MAX_VERTICES];
    int f = 0, r = 0;

    queue[r++] = start;
    visited[start] = stamp;

    while (f != r) {
        int p = queue[f++];
        // 此处可添加处理 p 的代码

        EdgeNode *node = adjList[p].firstedge;
        while (node != NULL) {
            if (visited[node->adjvex] < stamp) {
                visited[node->adjvex] = stamp;
                queue[r++] = node->adjvex;
            }
            node = node->next;
        }
    }
}

// 4. 邻接表 Prim 最小生成树
void Prim_AL(int start) {
    int lowcost[MAX_VERTICES];
    int adjvex[MAX_VERTICES];

    for (int i = 0; i < nn; i++) {
        lowcost[i] = INF;
        adjvex[i] = start;
    }

    EdgeNode *p = adjList[start].firstedge;
    while (p != NULL) {
        lowcost[p->adjvex] = p->weight;
        p = p->next;
    }
    lowcost[start] = 0;

    for (int i = 1; i < nn; i++) {
        int min = INF, minIdx = -1;

        for (int j = 0; j < nn; j++) {
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j];
                minIdx = j;
            }
        }

        if (minIdx == -1) break;
        // 在这里对新加入的路径 (adjvex[minInx]---minIdx) 以及权重 (lowcost[minIdx]) 做调用

        lowcost[minIdx] = 0;

        EdgeNode *q = adjList[minIdx].firstedge;
        while (q != NULL) {
            int v = q->adjvex;
            int w = q->weight;
            if (lowcost[v] != 0 && w < lowcost[v]) {
                lowcost[v] = w;
                adjvex[v] = minIdx;
            }
            q = q->next;
        }
    }
}

// ==========================================
// 第三部分：Kruskal 算法
// ==========================================

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

int cmpEdge(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

// 带路径压缩的并查集，兼容 0 索引
int findRoot(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = findRoot(parent, parent[x]);
    }
    return parent[x];
}

// 边集数组创建
Edge edges[MAX_EDGES];
int edgecnt=0;
// 邻接矩阵版本
void createEdges_Ma() {
    edgecnt = 0;
    for(int i = 0; i < nn; i++){
        for(int j = i + 1; j < nn; j++){
            if(edge[i][j] != INF){
                edges[edgecnt].u = i;
                edges[edgecnt].v = j;
                edges[edgecnt].weight = edge[i][j];
                edgecnt++;
            }
        }
    }
}
// 邻接表版本
void createEdges_AL() {
    edgecnt = 0;
    for(int i = 0; i < nn; i++){
        EdgeNode *p = adjList[i].firstedge;
        while(p != NULL){
            if(i < p->adjvex){
                edges[edgecnt].u = i;
                edges[edgecnt].v = p->adjvex;
                edges[edgecnt].weight = p->weight;
                edgecnt++;
            }
            p = p->next;
        }
    }
}

void Kruskal(Edge edges[], int vertexNum, int edgeNum) {
    int parent[MAX_VERTICES];
    int cnt = 0;

    // 初始化并查集，自己指向自己
    for (int i = 0; i < vertexNum; i++) {
        parent[i] = i; 
    }

    qsort(edges, edgeNum, sizeof(Edge), cmpEdge);

    for (int i = 0; i < edgeNum; i++) {
        int ru = findRoot(parent, edges[i].u);
        int rv = findRoot(parent, edges[i].v);

        if (ru != rv) {
            parent[ru] = rv; // 合并集合
            // 在这里对新加入的边 (edges[i].u, edges[i].v) 做操作

            cnt++;
            if (cnt == vertexNum - 1) break; // 生成树边数满足，提前结束
        }
    }
}

// ==========================================
// 第四部分：单源最短路径 Dijkstra 算法
// ==========================================

/* 
数组含义：dist[] 存最短距离，path[] 存前驱节点（用于回溯路径），inSet[] 标记是否已找到最短路。
*/

// 邻接矩阵版 Dijkstra
void Dijkstra_Matrix(int start, int dist[], int path[]) {
    int inSet[MAX_VERTICES] = {0}; // 0: 未确定最短路, 1: 已确定

    // 初始化
    for (int i = 0; i < nn; i++) {
        dist[i] = INF;
        path[i] = -1;
    }
    dist[start] = 0; // 起点距离为0，它将在第一轮循环中被选中

    // 循环 nn 次，每次确定一个节点的最短路
    for (int i = 0; i < nn; i++) {
        int min = INF, u = -1;

        // 1. 在未确定的节点中，找到 dist 最小的节点 u
        for (int j = 0; j < nn; j++) {
            if (!inSet[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // 若剩下的节点全为 INF，说明不连通，直接提前结束

        inSet[u] = 1; // 标记节点 u 的最短路径已确定

        // 2. 借助刚刚确定的 u，更新它的所有未确定的邻居 v
        for (int v = 0; v < nn; v++) {
            if (!inSet[v] && edge[u][v] != INF) {
                if (dist[u] + edge[u][v] < dist[v]) {
                    dist[v] = dist[u] + edge[u][v];
                    path[v] = u; // 记录 v 的前驱是 u
                }
            }
        }
    }
}

// 邻接表版 Dijkstra
void Dijkstra_AL(int start, int dist[], int path[]) {
    int inSet[MAX_VERTICES] = {0}; 

    for (int i = 0; i < nn; i++) {
        dist[i] = INF;
        path[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < nn; i++) {
        int min = INF, u = -1;

        for (int j = 0; j < nn; j++) {
            if (!inSet[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) break;

        inSet[u] = 1;

        // 借助节点 u 遍历它的所有出边，更新邻居
        EdgeNode *p = adjList[u].firstedge;
        while (p != NULL) {
            int v = p->adjvex;
            int w = p->weight;
            
            if (!inSet[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                path[v] = u;
            }
            p = p->next;
        }
    }
}

// 辅助函数：递归打印从起点到目标节点的最短路径
void printPath(int start, int end, int path[]) {
    if (end == start) {
        printf("%d", start);
        return;
    }
    if (path[end] == -1) {
        printf("No Path!"); // 不可达
        return;
    }
    // 先递归打印到前驱节点的路径
    printPath(start, path[end], path);
    // 再打印自己
    printf(" -> %d", end);
}