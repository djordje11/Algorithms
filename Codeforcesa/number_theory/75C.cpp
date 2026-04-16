#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <chrono>

using namespace std;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
int primes[10000000];
void create_divisors(map<int, int> &divisors, int num, map<int, int>::iterator curr, set<int>& skup)
{
    if(curr == divisors.end())
    {
        skup.insert(num);
        return;
    }

    int p = 1;
    auto next = ++curr;
    curr--;
    for(int i = 0; i <= curr->second; i++)
    {
        create_divisors(divisors, num*p, next,  skup);
        p *= curr->first;
    }

}
int main()
{
    int a, b;
    int tmp_a = a, tmp_b = b;
    cin >> a >> b;
    auto t1 = high_resolution_clock::now();
    if(a > b)
        swap(a, b);
 

    int count = 0;
    map<int, int> divisors;

    int k = std::sqrt(a) + 1;
    for(int i = 2; i <= k ; i++)
    {
        bool is_prime = true;
        for(int j = 0; j < count; j++)
        {
            if(i % primes[j] == 0)
            {
                is_prime = false;
                break;
            }
        }
        if(is_prime)
        {    
            primes[count++] = i;
            int c = 0;
            while(a % i == 0)
            {
                a = a/i;
                c++;
            }

            if(c > 0)
                divisors.insert({i, c});

        }
        if(a == 1)break;
    }

    if(a != 1)
    {
        divisors.insert({a, 1});
    }

    for(auto it = divisors.begin(); it != divisors.end(); )
    {
        int prime = it->first;
        int factor = it->second;

        int c = 0;
        while(b % prime == 0 && c < factor)
        {
            b = b / prime;
            c++;
        }
        if(c == 0)
        {
            auto jt = it++;
            divisors.erase(jt);
        }
        else {
            it->second = c;
            it++;
        }
        if(b == 1)break;
    }

    a = tmp_a;
    b = tmp_b;

    std::set<int> divisors_set;

    create_divisors(divisors, 1, divisors.begin(), divisors_set);
        auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    //std::cout << ms_int.count() << "ms\n";
    //std::cout << ms_double.count() << "ms\n";    
    int m;
    cin >> m;
 
    for (int i = 0; i < m; i++)
    {
        int l, h;
        cin >> l >> h;
 
 
        auto it = divisors_set.upper_bound(h); // it points to 10
 
        if (it != divisors_set.begin()) {
            --it;
            if (*it >= l)
                cout << *it << endl;
            else
                cout << -1 << endl;
        }
        else {
            cout << -1 << endl;
        }
 
    }

    return 0;
}
