#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;
int a[102];
#define MAX_N 501
int previous[MAX_N];
int min_edge[MAX_N];
bool visited[MAX_N];
int graph[MAX_N][MAX_N];
int graph_reverse[MAX_N][MAX_N];

int max_flow(int n)
{
    bool found = true; 
    while(found)
    {
        found = false;
        for(int i = 1; i <= n; i++)
            visited[i] = previous[i] = visited[i] = false;
 
        queue<int> bfs;
        visited[1] = true;
        min_edge[1] = 1000000;
        bfs.push(1);

        while(!bfs.empty())
        {
            int curr = bfs.front();
            bfs.pop();
            for(int i = 1; i <= n; i++)
            {
                if( (graph_reverse[curr][i] > 0|| graph[curr][i] > 0) && !visited[i])
                {
                    previous[i] = curr;
                    min_edge[i] = min(min_edge[curr], abs(max(graph[curr][i], graph_reverse[curr][i])));
                    bfs.push(i);
                    visited[i] = true;
                    if(i == n)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }
        
        if(found)
        {
            int y = n;
            while(y != 1)
            {
                int x = previous[y];
                if(graph[x][y] >= min_edge[n])
                {
                    graph[x][y] -= min_edge[n];
                    graph_reverse[y][x] += min_edge[n];
                }
                else
                {
                    graph_reverse[x][y] -= min_edge[n];
                    graph[y][x] += min_edge[n];   
                }
                y = x;
            }
        }
    }
    return 0;
}

int main()
{
    vector<int> primes;
    primes.push_back(2);

    for(int i = 3; i*i <= 1000000000; i+=2)
    {
        bool found = false;
        for(auto it : primes)
        {
            if(it*it > i)break;
            if(i % it == 0)
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            primes.push_back(i);
        }
    }

    int n, m;
    cin >> n >> m;
    int edges[100][2];
    for(int i = 2; i <= n+1; i++)
    {
        cin >> a[i];
    }
    for(int i = 0; i < m; i++)
    {
        cin >> edges[i][0] >> edges[i][1];
        edges[i][0]++;edges[i][1]++;
        if(edges[i][0] % 2)
            swap(edges[i][0], edges[i][1]);
    }

    vector<map<int, int>> factors(n+2);
    int diff_factors = 0;
    for(int i = 2; i <= n+1; i++)
    {
        int tmp = a[i];
        for(auto it : primes)
        {
            int cnt = 0;
            if(it * it > a[i])break;
            while(tmp % it == 0 && tmp != 1)
            {
                tmp /= it;
                cnt++;
            }
            if(cnt > 0)
            {
                diff_factors++;
                factors[i].insert({it, cnt});
            }
        }
        if(tmp != 1)
        {
            diff_factors++;
            factors[i].insert({tmp, 1});
        }
    }

    int count = 1; count++;
    vector<map<int, int>> factors_map(n+2);
    for(int i = 2; i <= n + 1; i++)
    {
        for(auto it : factors[i])
        {
            if(i%2 == 0)
                graph[1][count] = it.second;
            else
                graph[count][2+diff_factors] = it.second;

            factors_map[i].insert({it.first, count++});
        }
    }

    for(int i = 0; i < m; i++)
    {
        int x = edges[i][0], y = edges[i][1];

        for(auto it = factors[x].begin(), jt = factors[y].begin(); it != factors[x].end() && jt != factors[y].end(); )
        {
            if(it->first == jt->first)
            {
                graph[factors_map[x][it->first]][factors_map[y][jt->first]] = min(jt->second, it->second);
                it++;
                jt++;
            }
            else if(it->first > jt->first)
            {
                jt++;
            }
            else 
            {
                it++;
            }
        }
    }

    max_flow(2+diff_factors);
    
    int sum = 0;
    for(int i = 1; i <= 2 + diff_factors; i++)
    {
        sum += graph_reverse[i][1];
    }

    cout << sum << endl;
    return 0;
}
