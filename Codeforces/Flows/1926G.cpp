#include <cstdint>
#include <iostream>
#include <vector>


using namespace std;


int dp_s[100001];
int dp_p[100001];
int dp[100001];
char stud[100000 + 2];
#define BIGNUM 1000000

void dfs(vector<vector<int>>& graph, int curr, int par)
{

    if(stud[curr] == 'S')
    {
        dp_p[curr] = BIGNUM;
    }
    else if(stud[curr] == 'P')
    {
        dp_s[curr] = BIGNUM;
    }

    if(graph[curr].size() == 1 && curr != 1)
    {
        // leaf
        if(stud[curr] == 'C')
        {
            dp_p[curr] = BIGNUM;
            dp_s[curr] = BIGNUM;

        }
    }

    for(auto it : graph[curr])
    {
        if(it != par)
        {



            dfs(graph, it, curr);
            if(dp_s[it] == BIGNUM && dp_p[it] == BIGNUM)
                continue;

            if(stud[curr] == 'S')
            {
                dp_s[curr] += min(dp_s[it], dp_p[it]+1);
            }
            else if(stud[curr] == 'P')
            {
                dp_p[curr] += min(dp_p[it], dp_s[it] + 1);
            }
            else if(stud[curr] == 'C')
            {
                dp_s[curr] += min(dp_s[it], 1 + dp_p[it]);
                dp_p[curr] += min(dp_p[it], 1 + dp_s[it]);
            }

            if(dp_s[curr] > BIGNUM)dp_s[curr] = BIGNUM;
            if(dp_p[curr] > BIGNUM)dp_p[curr] = BIGNUM;
        }
    }
    int s_min = BIGNUM, p_min = BIGNUM;
    if(stud[curr] == 'C')
    {
        for(auto it : graph[curr])
        {
            if(it != par)
            {
                if(dp_s[it] != BIGNUM)
                {
                    s_min = min(dp_s[curr] - min(dp_s[it], 1 + dp_p[it]) + dp_s[it], s_min);
                }
                if(dp_p[it] != BIGNUM)
                {
                    p_min = min( dp_p[curr] - min(dp_p[it], 1 + dp_s[it]) + dp_p[it], p_min);
                }
            }
        }

        if(p_min != BIGNUM)
            dp_p[curr] = p_min;
        if(s_min != BIGNUM)
            dp_s[curr] = s_min;
    }

}


int main()
{

    int t;
    cin >> t;
    while(t--)
    {
    int n;
    cin >> n;
    vector<vector<int>> graph(n+1);

    dp[1] = dp_p[1] = dp_s[1] = 0; 
    for(int i = 2; i <= n; i++)
    {
        dp[i] = dp_p[i] = dp_s[i] = 0;
        int x;
        cin >> x;
        graph[x].push_back(i);
        graph[i].push_back(x);
    }

    cin >> (stud + 1);

    dfs(graph, 1, 0);
    if(n == 1)cout << 0 << endl;
    else
    {
        if(dp_p[1] == BIGNUM && dp_s[1] == BIGNUM)
            cout << 0 << endl;
        else
            cout << min(dp_p[1], dp_s[1]) << endl;
    }
    }
    return 0;
}
