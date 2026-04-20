#include <iostream>
#include <set>
#include <chrono>





int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);


    std::set<unsigned> skup;
    std::set<unsigned> skup2;
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int n, p;
    std::cin >> n >> p;
    int x;
    for(int i = 0; i < n; i++)
    {
            std::cin >> x;
            skup.insert(x);
    }

    for(auto it : skup)
    {
        bool insert = true;
        int pom = it;
        while(pom > 0)
        {
            if(skup2.count(pom))
            {
                insert = false;
                break;
            }
            if(pom % 2 == 1)
            {
                pom /= 2;
                continue;
            }
            if(pom % 4 == 0)
            {
                pom /= 4;
                continue;
            }
            break;
        }

        if(insert)
            skup2.insert(it);

    }


    unsigned moduo = 1000000000 + 7;
std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    unsigned dp[2 * 100000 + 1] = {1, 2};

    for(int i = 2; i < 2 * 100000 + 1; i++)
        dp[i] = (1 + dp[i-1] + dp[i-2]) % moduo;

    unsigned sum = 0;
    for(auto it : skup2)
    {
        int pom = it;
        int r = 0;
        while(pom >>= 1)r++;
        if(p - r > 0)
        {
            sum = (sum + dp[p-r-1]) % moduo;       
        }
    }
    std::cout << sum << std::endl;

    return 0;
}
