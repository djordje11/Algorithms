#include <iostream>


int main()
{
    int t = 0;
    std::cin >> t;
    
    while (t--)
    {
        int n, x;
        std::cin >> n >> x;

        unsigned long long sum = 0;
        for (int a = 1; a <= n; a++)
        {
            for (int b = 1; b <= n / a; b++)
            {
                int res = std::min(x - a - b, (n - a * b) / (a + b));
                if (res >= 1) sum += res;
            }
        }
        std::cout << sum << std::endl;
        
    }


    return 0;
}
 
