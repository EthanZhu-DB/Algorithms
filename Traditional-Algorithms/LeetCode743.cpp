class Solution {
private:
    static const int N = 110, M = 1e4+10; //从这里看出，这个图是一个稠密图，应该用矩阵存储比较好
    struct{
        int a, b, w;  
    }edge[M];
    int dist[N], backup[N];
    int n, m, k;
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        for(int i = 0 ; i < times.size(); i++){
            edge[i] = {times[i][0], times[i][1], times[i][2]};
        }
        n = N, m = times.size(), k = K;
        bellman_ford();
        int maximum = 0;
        for(int i = 1 ; i <= n; i++){
            if(dist[i] >= 0x3f3f3f3f / 2) return -1;
            maximum = max(maximum, dist[i]);
        }
        return maximum;
    }
    void bellman_ford(){
        memset(dist, 0x3f, sizeof dist);
        dist[k] = 0;
        
        for(int i = 0; i < n; i++){   //迭代点的个数次
            memcpy(backup, dist, sizeof dist);   //无记忆化操作
            for(int j = 0; j < m; j++){
                int a = edge[j].a, b = edge[j].b, w = edge[j].w;
                dist[b] = min(dist[b], backup[a] + w);    //无记忆松弛
            }
        }
    }
};

//朴素dijkstra算法
class Solution {
private:
    static const int N = 110, M = 1e5+10;
    int g[N][N];
    int dist[N];
    int n, k;
    bool visited[N];
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        memset(g, 0x3f, sizeof(g));  //记住这里一定要对二维矩阵初始化，否则所有的矩阵两点间距离都为0
        for(int i = 0; i < times.size(); i++){
            g[times[i][0]][times[i][1]] = times[i][2];
        }
        n = N, k = K;
        dijkstra();
        int maximum = INT_MIN;
        for(int i = 1; i <= n; i++){
            if(dist[i] == 0x3f3f3f3f) return -1;
            maximum = max(maximum, dist[i]);
        }
        return maximum;
        
    }
    void dijkstra(){
        memset(dist, 0x3f, sizeof dist);
        dist[k] = 0;
        
        for(int i = 0 ; i < n; i++){
            int t = -1;
            for(int j = 1; j <= n; j++){
                if(!visited[j] && (t == -1 || dist[t] > dist[j])){
                    t = j;
                }
            }
            cout << t << " ";
            visited[t] = true;
            
            for(int j = 1; j <= n; j++){
                dist[j] = min(dist[j], dist[t]+g[t][j]);
            }
        }
        
    }
};

