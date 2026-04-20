#include <iostream>


int divisidors[1000000];
int counter = 0;

void printDivisors(int n) 
{ 
    int i; 
    for (i = 1; i * i < n; i++) { 
        if (n % i == 0) 
            divisidors[counter++] = i; 
    } 
    if (i - (n / i) == 1) { 
        i--; 
    } 
    for (; i >= 1; i--) { 
        if (n % i == 0) 
            divisidors[counter++] = n / i; 
    } 
} 

int main()
{
    //counter = 0;
    //printDivisors(100);
    //for(int i = 0; i < counter; i++)
    //    std::cout << divisidors[i] << " ";

    int a[1000001];
    int n;
    std::cin >> n;

    int moduo = 1000000000 + 7;

    unsigned dp[1000001] = {1, 0};

    for(int i = 1; i <= n; i++)
        std::cin >> a[i];

    for(int i = 1; i <= n; i++)
    {
        dp[i] = 0;
        if(a[i] % i == 0 && dp[i-1] == 1) dp[i] = 1;
        counter = 0;
        printDivisors(a[i]);
        for(int j = counter-1; j >= 0; j--)
        {
            if(divisidors[j] < i)
                dp[divisidors[j]] = (dp[divisidors[j]] + dp[divisidors[j] - 1]) % moduo;
        }
        //for(int j = i-1; j >= 1; j--)
        //{
        //    if(a[i] % j == 0)dp[j]= (dp[j] + dp[j-1]) % moduo;   
        //}
    }


    unsigned sum = 0;

    for(int i = 1; i <= n; i++)
        sum = (sum + dp[i]) % moduo;

    std::cout << sum << std::endl;
    //for(int i = 1; i <= n; i++)
    //    std::cout << dp[i] << " ";
    //std::cout << std::endl;

    return 0;
}
