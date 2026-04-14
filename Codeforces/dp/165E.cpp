#include <iostream>
#include <stack>
#include <chrono>
    #include <bits/stdc++.h>

 
        using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;


unsigned dp[4194304];
int a[1000000];
    unsigned curr;

void insert(unsigned k)
{
	if (dp[k])return;
	dp[k] = curr;
	if (k == 0)return;

	for (int i = 0; i < 22; i++)
	{
		if ((1 << i) & k)
		{
			unsigned pom = (~(1 << i)) & k;
			if (dp[pom])continue;
			insert(pom);
		}
	}
}




int main()
{
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(NULL);


	insert(0xA);

    int n;
    std::cin >> n;
    for(int i =0 ; i < n;i++)
        std::cin >> a[i];
    for(int i = 0; i < n; i++)
        insert(~(curr = a[i]) & 0x3FFFFF);


            auto t1 = high_resolution_clock::now();

    for(int i = 0; i < n; i++)
        if(dp[a[i]]) std::cout << dp[a[i]] << " ";
        else std::cout << "-1 ";
    std::cout << std::endl;



   // auto t2 = high_resolution_clock::now();
 
 
     //   auto ms_int = duration_cast<milliseconds>(t2 - t1);
 
    //std::cout << ms_int.count() << "ms\n";
      //  std::cout << std::endl;

	return 0;
}
