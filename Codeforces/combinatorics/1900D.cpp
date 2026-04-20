    #include <iostream>
    #include <algorithm>
     #include <chrono>
     #include <map>
#define PHI_NUM_TO_CALC 100000

unsigned long long phi_map[PHI_NUM_TO_CALC + 1] = {0, 1, 1};
unsigned long long primes[PHI_NUM_TO_CALC] = {2};
int primes_count = 1;
void init_phi_map()
{

    
    for(int i = 3; i <= PHI_NUM_TO_CALC; i++)
    {
        int j;
        for(j = 0; j < primes_count; j++)
        {
            unsigned long long p = primes[j];

            while(i % p == 0)
            {
                p = p * primes[j];
            }

            if(p == primes[j])
            {
                continue;
            }

            p = p / primes[j];


            if(p == i)
                phi_map[i] = p - p/primes[j]; 
            else
                phi_map[i] = phi_map[p] * phi_map[i / p];
            break;

        }
        if(j == primes_count)
        {
            phi_map[i] = i-1;
            primes[primes_count++] = i;
        }
    }
}



 int main()
{
        using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();

    init_phi_map();
        unsigned long long a[8 * 10000];
        unsigned long long dp[8 * 10000];
        unsigned long long k = 0;
        unsigned long long t;
        std::cin >> t;
     
        while(t--)
        {
        unsigned long long n;
        std::cin >> n;
     
        for(unsigned long long i = 0; i < n; i++)
            std::cin >> a[i];
     
     
        std::sort(a, a + n);
     
        unsigned long long sum =0 ;
        bool same = false;
        unsigned long long dp_sum = 0;
        std::map<unsigned long long, unsigned long long> apirens;
        int divisors[1000];

        for(unsigned long long i = 0; i < n-1; i++)
        {
            unsigned long long mul = n-1 - i;
            int count = 0;; 

            int j = 1;
            for(; j*j <= a[i]; j++)
            {
                if(a[i] % j == 0)
                {
                    divisors[count++] = j;
                }
            }

            int old_count = count - ((j-1)*(j-1) == a[i]);

            for(int k = 0; k < old_count; k++)
            {
                divisors[count++] = a[i] / divisors[k];
            }
          
            for(int j = 0; j < count; j++)
            {
                if(apirens.find(divisors[j]) == apirens.end())
                {
                    apirens[divisors[j]] = 1;
                }
                else
                {
                    sum += apirens[divisors[j]] * phi_map[divisors[j]] * mul;
                    apirens[divisors[j]]++;
                }
            }
        }
          std::cout << sum << std::endl;
        }
      
        return 0;
    }
