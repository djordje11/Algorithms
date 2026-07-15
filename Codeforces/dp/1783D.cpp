#include <iostream>
#include <map>
#define MODUO 998244353
long unsigned dp_raw[2][180100];
int used_raw[2][180100];

int main()
{
    int n;
    int array[300];

    std::cin >> n;
    for(int i = 0; i < n; i++)
        std::cin >> array[i];



    long unsigned* dp = dp_raw[0] + 90050;
    dp[array[1]] = 1;
    long unsigned* dp_new = dp_raw[1] + 90050;

    int *used = used_raw[0];
    used[0] = array[1];
    int cnt_used = 1;
    int* used_new = used_raw[1];


    for(int i = 2; i < n; i++)
    {
        int cnt_used_new = 0;
        for(int j = 0; j < cnt_used; j++)
        {
            if(used[j] == 0)
            {
                if(dp_new[array[i]] == 0)
                    used_new[cnt_used_new++] = array[i];
                dp_new[array[i]] = (dp_new[array[i]] + dp[0]) % MODUO;
            }
            else
            {
                if(dp_new[array[i] + used[j]] == 0)
                    used_new[cnt_used_new++] = array[i] + used[j];
                if(dp_new[array[i] - used[j]] == 0)
                    used_new[cnt_used_new++] = array[i] - used[j];
                dp_new[array[i] + used[j]] = (dp_new[array[i] + used[j]] + dp[used[j]]) % MODUO;
                dp_new[array[i] - used[j]] = (dp_new[array[i] - used[j]] + dp[used[j]]) % MODUO; 
            }
            dp[used[j]] = 0;
        }
        cnt_used = cnt_used_new;
        std::swap(dp, dp_new);
        std::swap(used, used_new);
    }

    long unsigned sum = 0;


    for(int i =0; i < cnt_used; i++)
        sum = (sum + dp[used[i]]) % MODUO ;
    std::cout << sum << std::endl;
    return 0;
}
