#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <cstring>

typedef long long ll;
unsigned long long a[2 * 100000];
unsigned long long bottom[2 * 100000 + 2];
unsigned long long tops[2 * 100000 + 2];

unsigned long long moduo = 1000000000 + 7;
int main()
{

        int n;
        std::cin >> n;
        unsigned long long count = 1;
        unsigned long long times = 1;
        for (int i = 2; i <= n; i++)
        {
            count = (count * i) % moduo;
            times = (times * 2) % moduo;
        }
        if (times > count)
            std::cout << ((moduo - times) + count) % moduo << std::endl;
        else
            std::cout << count - times << std::endl;

    return 0;
}
