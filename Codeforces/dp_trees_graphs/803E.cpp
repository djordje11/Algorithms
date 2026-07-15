#include <iostream>
#include <string>
using namespace std;


bool dp[1000][1001][2];
#define L 0
#define W 1

int main()
{
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;
    int tmp_k = k;

    if (s[0] == 'L')
    {
        dp[0][1][L] = true;
    }
    else if (s[0] == 'W')
    {
        dp[0][1][W] = true;
    }
    else if (s[0] == 'D')
    {
        dp[0][0][W] = dp[0][0][L] = true;
    }
    else
    {
        dp[0][0][W] = dp[0][0][L] = dp[0][1][L] = dp[0][1][W] = true;
    }


    for (int i = 1; i < n; i++)
    {
        char c = s[i];

        if (c == 'L')
        {
            if (k != 1)
            {
                dp[i][0][L] = dp[i - 1][1][W];
                dp[i][0][W] = dp[i - 1][1][W];
            }
            for (int m = 1; m <= k; m++)
            {
                dp[i][m][L] = dp[i - 1][m - 1][L];
                dp[i][m][W] = (m + 1 < k) ? dp[i - 1][m + 1][W] : 0;
            }
        }
        else if (c == 'W')
        {
            if (k != 1)
            {
                dp[i][0][L] = dp[i - 1][1][L];
                dp[i][0][W] = dp[i - 1][1][L];
            }
            for (int m = 1; m <= k; m++)
            {
                dp[i][m][W] = dp[i - 1][m - 1][W];
                dp[i][m][L] = (m + 1 < k) ? dp[i - 1][m + 1][L] : 0;
            }
        }
        else if (c == 'D')
        {
            for (int m = 0; m <= k; m++)
            {
                dp[i][m][W] = dp[i - 1][m][W];
                dp[i][m][L] = dp[i - 1][m][L];
            }
        }
        else if (c == '?')
        {
            if (k != 1)
            {
                dp[i][0][L] = dp[i - 1][1][W] || dp[i - 1][1][L];
                dp[i][0][W] = dp[i - 1][1][L] || dp[i - 1][1][W];
            }

            dp[i][0][L] = dp[i][0][L] || dp[i - 1][0][L];
            dp[i][0][W] = dp[i][0][W] || dp[i - 1][0][W];

            for (int m = 1; m <= k; m++)
            {
                if (m != k)
                {
                    dp[i][m][W] = dp[i - 1][m][W];
                    dp[i][m][L] = dp[i - 1][m][L];
                }
                dp[i][m][W] = dp[i][m][W] || dp[i - 1][m - 1][W] || ((m + 1 < k ? dp[i - 1][m + 1][W] : false));
                dp[i][m][L] = dp[i][m][L] || dp[i - 1][m - 1][L] || (m + 1 < k ? dp[i - 1][m + 1][L] : false);
            }
        }
    }





    int start;
    int not_start;
    int start_num;

    if (dp[n - 1][k][W])
    {
        start = 'W';
        not_start = 'L';
        start_num = 1;

    }
    else if (dp[n - 1][k][L])
    {
        start = 'L';
        not_start = 'W';
        start_num = 0;
    }
    else {
        cout << "NO" << endl;
        return 0;
    }
    s[n - 1] = start;
    k--;
    for (int i = n - 2; i >= 0; i--)
    {
        if (s[i] == start)
        {
            k--;
        }
        else if (s[i] == not_start)
        {
            k++;
        }
        else if (s[i] == '?')
        {
            if (k == 0)
            {
                if (i - 1 >= 0 && dp[i-1][1][start_num])
                {
                    s[i] = not_start;
                    k++;
                }
                else if (i - 1 >= 0 && dp[i - 1][1][1 - start_num])
                {
                    s[i] = start;
                    k--;
                }
                else
                {
                    s[i] = 'D';
                }
            }
            else if (k > 0)
            {
                if (i - 1 >= 0 && k + 1 < tmp_k && dp[i - 1][k + 1][start_num])
                {
                    s[i] = not_start;
                    k++;
                }
                else if (i - 1 >= 0 && k - 1 >= 0 && dp[i - 1][k - 1][start_num])
                {
                    s[i] = start;
                    k--;
                }
                else if (i - 1 >= 0 && dp[i - 1][k][start_num])
                {
                    s[i] = 'D';
                }
                else if (i == 0)
                {
                    s[i] = start;
                }
            }
            else if (k < 0)
            {
                int lala = -k;
                if (i - 1 >= 0 && lala + 1 < tmp_k && dp[i - 1][lala + 1][1 - start_num])
                {
                    s[i] = start;
                    k--;
                }
                else if (i - 1 >= 0 && lala - 1 >= 0 && dp[i - 1][lala - 1][1 - start_num])
                {
                    s[i] = not_start;
                    k++;
                }
                else if (i - 1 >= 0 && dp[i - 1][lala][1 - start_num])
                {
                    s[i] = 'D';
                }
                else if (i == 0)
                {
                    s[i] = not_start;
                }
            }
        }
    }
    cout << s << endl;

    return 0;
}
