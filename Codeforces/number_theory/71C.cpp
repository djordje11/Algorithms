#include <iostream>
#include <cmath>
#include <set>

int main()
{
    int n;
    bool a[100000];
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];


    std::set<int> factors;

    int k = n;
    {
        int i = 2;
        while (k > 1)
        {
            if (k % i == 0)
            {
                factors.insert(i);
                k = k / i;
            }
            else {
                i++;
            }
        }
    }
    if (n % 2 == 0)
    {
        factors.erase(2);
        if (n % 4 == 0)factors.insert(4);
    }

    for (auto it : factors)
    {

        for (int i = 0; i < n / it; i++)
        {
            bool yes = true;
            for (int j = 0; j < it; j++)
            {
                if (a[j * n / it + i] == false)
                {
                    yes = false;
                    break;
                }
            }
            if (yes == true)
            {
                std::cout << "YES" << std::endl;
                return 0;
            }
        }

    }

    std::cout << "NO" << std::endl;
    return 0;
}
