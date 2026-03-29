#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> dp;

int max_d[100000 + 1];
bool are[100000 + 1];
bool can[100000 + 1];
int n, m, d;
void dfs(vector<vector<int>>& graph, int curr, int par)
{   
    int childs = graph[curr].size() - (par == 0 ?  0 : 1);

    if(are[curr])
    {
        max_d[curr] = 0;
    }
    int curr_max[2] {-1, 0};
    int curr_max2[2] {-1, 0};
    int ch = 0;
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            ch++;
            dfs(graph, it, curr);

            if(max_d[it] != -1)
            {
                max_d[curr] = std::max(max_d[it] + 1, max_d[curr]);
                if(max_d[it] + 1 > curr_max[0])
                {
                    curr_max2[0] = curr_max[0];
                    curr_max2[1] = curr_max[1];

                    curr_max[0] = max_d[it]+1;
                    curr_max[1] = 1;
                }
                else if(max_d[it] + 1 == curr_max[0])
                {
                    curr_max[1]++;
                }
                else if(max_d[it] + 1 > curr_max2[0])
                {
                    curr_max2[0] = max_d[it] + 1;
                    curr_max2[1] = 1;
                }
                else if(max_d[it] + 1 == curr_max2[0])
                {
                    curr_max2[1]++;
                }
            }
        }
    }
    dp[curr] = vector<int>(ch+1);
    if(max_d[curr] > d)can[curr] = false;
    int i = 1;
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            if(curr_max[0] != -1 && curr_max[0] > 1 + max_d[it])
            {
                dp[curr][i] = curr_max[0];
            }
            else if(curr_max[0] == 1 + max_d[it])
            {
                if(curr_max[1] > 1)
                {
                    dp[curr][i] = curr_max[0];
                }
                else {
                    dp[curr][i] = curr_max2[0];
                }
            }
            i++;
        }
    }    

}


void dfs2(vector<vector<int>>& graph, int curr, int par, int max_from_upper)
{   
    
    if(max_from_upper != -1 && ++max_from_upper> d)
        can[curr] =false;

    if(are[curr] && max_from_upper == -1)
    {
        max_from_upper = 0;
    }

    int childs = graph[curr].size() - (par == 0 ?  0 : 1);
    
    int i = 1;
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            
            dfs2(graph, it, curr, max(max_from_upper, dp[curr][i]));
            i++;
        }
    }
}
int main()
{
    cin >> n >> m >> d;

    dp = vector<vector<int>>(n+1);
    vector<vector<int>> graph(n+1);

    for(int i = 1; i <= m; i++)
    {
        int x;
        cin >> x;
        are[x] = true;
    }

    max_d[1] = -1;
    can[1] = true;
    for(int i = 2; i <= n; i++)
    {
        max_d[i] = -1;
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
        can[i] = true;
    }

    dfs(graph, 1, -1);
    dfs2(graph, 1, 0, -1);

    int count = 0;
    for(int i = 1; i <= n; i++)
        if(can[i])count++;
    cout << count << endl;

    return 0;
}