#include <iostream>

using namespace std;

using ull = unsigned long long;

ull p[10001];
ull s[10001];
ull dp[2][10000];
int main()
{
    ull n, c;
    cin >> n >> c;

    for(int i = 1; i <= n; i++)
        cin >> p[i];
    
    for(int i = 1; i <= n; i++)
        cin >> s[i];

    dp[1][0] = s[1];
    dp[1][1] = p[1];

    for(int i = 2; i <= n; i++)
    {
        dp[i%2][0] = dp[(i+1)%2][0] + s[i];
        for(int j = 1; j < i; j++)
        {
            dp[i%2][j] = min(dp[(i+1)%2][j-1] + p[i] + ull(i-j)*c, dp[(i+1)%2][j] + s[i]);
        }
        dp[i%2][i] = dp[(i+1)%2][i-1] + p[i];
    }
    ull mini = ull(1)<<63;
    for(int i = 0; i <= n; i++)
    {
        mini = min(mini, dp[n%2][i]);
        
    }

    cout << mini << endl;
    return 0;
}
