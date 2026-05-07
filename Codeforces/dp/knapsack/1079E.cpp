#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

short dp[10001][101];

int a[101];
short cnt[101][10001];
int nums[101];

int main()
{
    int n;
    cin >> n;
    set<int> el;
    int sum = 0;

    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        nums[a[i]]++;
        sum += a[i];
        el.insert(a[i]);
    }

    for(int i = 1; i <= n; i++)
    {
        for(int k = i; k >= 1; k--)
        {
            for(int j = sum - a[i]; j >= 1; j--)
            {
                if(dp[j][k-1] == 0)
                {   
                    continue;
                }
                if(dp[j][k-1] == -1)
                {
                    dp[j+a[i]][k] = -1;
                }
                else 
                {
                    if(dp[j][k-1] == a[i])
                    {
                        if(dp[j+a[i]][k] == 0 || dp[j+a[i]][k] == a[i])
                            dp[j+a[i]][k] = a[i];
                        else
                            dp[j+a[i]][k] = -1;
                    }
                    else 
                    {
                        dp[j+a[i]][k] = -1;
                    }
                }
            }
        }
        dp[a[i]][1] = a[i];
    }

    if(el.size() == 2)
    {
        cout << n << endl;
        return 0;
    }

    int max = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= sum; j++)
        {
            if(dp[j][i] > 0){  max = std::max(max, i);}

        }
    }

    cout << max << endl;
    return 0;
}
