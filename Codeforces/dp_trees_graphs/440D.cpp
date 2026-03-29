#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

int parents[401];
int childs[401];

vector<int> dp[401][401];

int cnt[401][401];
int edges[401][2];

vector<pair<int, int>> dist[401][401];

int k;
int curr_min = INT_MAX;
int curr_min_start = -1;

void init_dfs(vector<vector<int>>& graph, int curr, int par)
{
    childs[curr] = graph[curr].size() - (par == 0 ?  0 : 1);
    parents[curr] = par;

    dp[curr][1] = vector<int>(childs[curr] + 1, 0);
    dist[curr][1] = vector<pair<int, int>>(childs[curr] + 1, {0, 0});
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            init_dfs(graph, it, curr);
            for(int s = 2; s <= k; s++)
            {
                dp[curr][s] = vector<int>(childs[curr]+1, 0);
                dist[curr][s] = vector<pair<int, int>>(childs[curr] + 1, {0, 0});
            }
        }

    }

}

void dfs(vector<vector<int>>& graph, int curr, int par)
{    
    dp[curr][1][0] = childs[curr];
    if(k == 1)
    {
        if(childs[curr] + (par == 0 ? 0 : 1) < curr_min)
        {
            curr_min = childs[curr] + (par == 0 ? 0 : 1);
            curr_min_start = curr;
        }
    }

    int i = 1;
    cnt[curr][0] = 1;

    for(auto it : graph[curr])
    {
        if(it != par)
        {
            dfs(graph, it, curr);

            cnt[curr][i] = cnt[curr][i-1] + cnt[it][childs[it]];

            
            dp[curr][1][i] = childs[curr];


            for(int s = 2; s <= k; s++)
            {
                dp[curr][s][i] = INT_MAX;

                if(cnt[curr][i-1] >= s)
                {
                    dp[curr][s][i] = dp[curr][s][i-1];
                    //
                }

                if(cnt[it][childs[it]] >= s-1)
                {
                    if(dp[it][s-1][childs[it]] + childs[curr] - 1 < dp[curr][s][i])
                    {
                        dp[curr][s][i] = dp[it][s-1][childs[it]] + childs[curr] - 1;
                        dist[curr][s][i].first = s-1;
                        dist[curr][s][i].second = it; 
                    }
                }
                for(int j = 2; j <= s-1; j++)
                {
                    if(cnt[curr][i-1] >= j && cnt[it][childs[it]] >= s-j)
                    {
                        if(dp[curr][j][i-1]+dp[it][s-j][childs[it]] -1 < dp[curr][s][i])
                        {
                            dp[curr][s][i] = dp[curr][j][i-1]+dp[it][s-j][childs[it]] -1;
                            dist[curr][s][i].first = s-j;
                            dist[curr][s][i].second = it;
                        }
                    }
                }
            }
            if(dp[curr][k][i] != INT_MAX)
            {
                if(dp[curr][k][i] + (par != 0 ? 1 : 0) < curr_min)
                {
                    curr_min = dp[curr][k][i] + (par != 0 ? 1 : 0);
                    curr_min_start = curr;
                }
                //curr_min = std::min(curr_min, dp[curr][k][i] + (par != 0 ? 1 : 0));
            }
            i++;
        }
    }
}

int main()
{
    int n;
    cin >> n >> k;

    vector<vector<int>> graph(n+1);

    for(int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
        edges[i-1][0] = x;
        edges[i-1][1] = y;
    }

    init_dfs(graph, 1, 0);

    dfs(graph, 1, 0);

    queue<pair<int, int>> q;
    q.push({curr_min_start, k});
    std::set<int> res;
    while(!q.empty())
    {
        auto curr = q.front();
        res.insert(curr.first);
        q.pop();
        int sum = 0;
        int start = childs[curr.first];
        int num = curr.second;
        while(sum < curr.second - 1)
        {
            sum += dist[curr.first][num][start].first;
            if(dist[curr.first][num][start].first != 0)
                q.push({dist[curr.first][num][start].second , dist[curr.first][num][start].first});
            num -= dist[curr.first][num][start].first;
            start--;
        }
    }

    cout << curr_min << endl;



    for(int i = 1; i < n; i++)
    {
        if(res.count(edges[i][0]) && !res.count(edges[i][1]))
            cout << i << " ";

        if(res.count(edges[i][1]) && !res.count(edges[i][0]))
            cout << i << " ";

    }

    return 0;
}