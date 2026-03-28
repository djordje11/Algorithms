#include <cstdint>
#include <vector>
#include <iostream>
#include <set>
// in undirected graph checks if edges is in some cicle
// in_cycle[i] true if edge with num i is in cycle

using namespace std;

#define N_MAX 100001
#define M_MAX 100001

int t_in[N_MAX];
int tme = 1;
int t_out[100000 + 1];

int parent[100001];
int pakets[100001][3];
int questions[100001][3];
bool has_parent[100001];
int stack[100001], stack_size = 0;

void dfs3(int curr, int parr, vector<vector<int>>& graph)
{
    t_in[curr] = tme++;
    for(auto it : graph[curr])
    {
        if(it != parr)
        {
            dfs3(it, curr, graph);
        }
    } 
    t_out[curr] = tme++;
}

bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}

int main()
{
    int n, m;
    cin >> n >> m;


    vector<vector<int>> graph(n+1);
    for(int i = 1; i <= n; i++)
        parent[i] = i;
    int paket_num = 1;
    int quest_num = 1;
    for(int i = 0; i < m; i++)
    {
        int t;
        int x, y;
        cin >> t;
        if(t == 1)
        {
            cin >> x >> y;
            has_parent[x] = true;
            parent[x] = parent[y];
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        else if(t == 2)
        {
            stack_size = 0;
            cin >> x;
            stack[stack_size++] = x; 
            int curr = parent[x];
            stack[stack_size++] = curr; 
            while(curr != parent[curr])
            {
                curr = parent[curr];
                stack[stack_size++] = curr;
            }
            pakets[paket_num][0] = x;
            pakets[paket_num][1] = curr;
            pakets[paket_num++][2] = i;
                        
            for(int j = 0; j < stack_size; j++)
                parent[stack[j]] = curr;
        }
        else if(t == 3)
        {
            cin >> questions[quest_num][0] >> questions[quest_num][1];
            questions[quest_num++][2] = i;
        }
    }

    for(int i = 1; i <= n; i++)
        if(!has_parent[i])
            dfs3(i, 0, graph);

    for(int i = 1; i < quest_num; i++)
    {
        int x = questions[i][0];
        int y = questions[i][1];
        int t = questions[i][2];
        if(pakets[y][2] > t)
            cout << "NO" << endl;
        else
        {
            int top = pakets[y][1];
            int bot = pakets[y][0];

            if((is_ancestor(x, bot) && is_ancestor(top, x)) || x == bot || x == top)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }


    return 0;
}