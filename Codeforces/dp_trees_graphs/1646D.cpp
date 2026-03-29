#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

int dp[2 * 100000 + 1][2];
int dp_min[2 * 100000 + 1][2];

int curr_arr[2 * 100000 + 1];

void dfs(vector<vector<int>>& graph, int curr, int par)
{
    dp[curr][0] = 0;
    dp[curr][1] = 1;

    dp_min[curr][0] = 1;
    dp_min[curr][1] = graph[curr].size();


    for (auto it : graph[curr])
    {
        if (it != par)
        {
            dfs(graph, it, curr);
            
            dp[curr][1] += dp[it][0];
            dp_min[curr][1] += dp_min[it][0];

            if (dp[it][1] > dp[it][0])
            {
                dp[curr][0] += dp[it][1];
                dp_min[curr][0] += dp_min[it][1];
            }
            else if (dp[it][1] < dp[it][0])
            {
                dp[curr][0] += dp[it][0];
                dp_min[curr][0] += dp_min[it][0];
            }
            else
            {
                dp[curr][0] += dp[it][0];
                dp_min[curr][0] += std::min(dp_min[it][1], dp_min[it][0]);
            }
        }
    }
}
int sum = 0;
void dfs2(vector<vector<int>>& graph, int curr, int par, bool is_par_included)
{
    bool current_included;

    if (is_par_included)
    {
        curr_arr[curr] = 1;
        current_included = false;
        
    }
    else
    {
        if (dp[curr][0] > dp[curr][1])
        {
            curr_arr[curr] = 1;
            current_included = false;
        }
        else if (dp[curr][1] > dp[curr][0])
        {
            curr_arr[curr] = graph[curr].size();
            current_included = true;
        }
        else
        {
            if (dp_min[curr][0] <= dp_min[curr][1])
            {
                curr_arr[curr] = 1;
                current_included = false;
            }
            else if(dp_min[curr][0] > dp_min[curr][1])
            {
                curr_arr[curr] = graph[curr].size();
                current_included = true;
            }

        }
    }
    sum += curr_arr[curr];
    for (auto it : graph[curr])
    {
        if (it != par)
        {
            dfs2(graph, it, curr, current_included);
        }
    }
}


int main()
{
    int n;
    cin >> n;
    
    vector<vector<int>> graph(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    if (n == 2)
    {
        cout << 2 << " " << 2 << endl << 1 << " " << 1 << endl;
        return 0;
    }
    dfs(graph, 1, 0);
    dfs2(graph, 1, 0, false);



    
    cout << max(dp[1][0], dp[1][1]) << " " << sum << endl;

    for (int i = 1; i <= n; i++)
        cout << curr_arr[i] << " ";
    cout << endl;


    return 0;
}