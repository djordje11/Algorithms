#include <iostream>
#include <vector>
#include <set>
#include <chrono>
 
 
class cmp{
    public:
    bool operator()(std::pair<int, int> x, std::pair<int, int> y)const
    {
        bool val = x.first * (x.first + x.second) == y.first * (y.first + y.second);
        if(!val)
            return x.first * (x.first + x.second) < y.first * (y.first + y.second);
        return x.first < y.first;
    }
};
    int dp[5000001] ;
    std::set<std::pair<int, int>, cmp> primes = {{2, 0}};
int main()
{
    std::ios::sync_with_stdio(false);
    int t;
 
    std::cin >> t;
    int a[1000000], b[1000000];
 
 
    for(int i = 0; i < t; i++)
        std::cin >> a[i] >> b[i];
    
    int max = 5000000;
 
    for(int i = 0; i <= max; i++)
        dp[i] = 1;
    dp[1] = 0;
    int current_max_calc = 2;
    bool cond = true;
    while(cond)
    {
        auto it = primes.begin();
 
        int f = it->first;
        int s = it->second;
        int value = f * (f + s);
 
 
        if(value > max)break;
        dp[value] = 1 + dp[f + s];
 
        if(cond)
        {
        for(int i = current_max_calc + 1; i < value; i++)
        {
            if(dp[i] == 1)
            {
                primes.insert({i, 0});
            }
            if(i * i > 5000000){ 
                cond = false;
            }
        }
        }
        current_max_calc = value;
        primes.erase(it);
        if(f * (f + s + 1) <= max)
            primes.insert({f, s+1});
    }
 
 
 
    for(auto it : primes)
    {
        int f = it.first;
        int s = it.second;
        while(f * (f + s) <= max)
        {
            dp[f * (f + s)] = 1 + dp[f+s];
            s++;
        }
    }
 
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
     //   auto t1 = high_resolution_clock::now();
    for(int i = 3; i <= max; i++)
        dp[i] += dp[i-1];
//auto t2 = high_resolution_clock::now();
    //auto ms_int = duration_cast<milliseconds>(t2 - t1);
 
   // std::cout << ms_int.count() << "ms\n";
    for(int i = 0; i < t; i++)
    {
        std::cout << dp[a[i]] - dp[b[i]] << "\n";
    }
    return 0;
}
