#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>

using namespace std;
using ull = unsigned long long;

ull prime = 31;
ull moduo = 1000000000 + 9;

int main()
{
    char goods[27];
    char s[1501];
    int k;

    cin >> s;
    cin >> goods;
    cin >> k;

    int n = std::strlen(s);

    set<pair<ull, ull>> hashes;

        ull prod[1500];
        prod[0] = 1;       
    for(int i = 1; i < n; i++)
        prod[i] = (prod[i-1]*prime)%moduo;
    for(int i = 0; i < n; i++)
    {
        int num_of_beds = 0;
        ull hash=0; 
        for(int j = i; j < n; j++)
        {
            if(goods[s[j] - 'a'] == '0')
                num_of_beds++;
            if(num_of_beds > k)
                break;
            hash += ((s[j] - '0') * prod[j-i]) % moduo;

            auto it = hashes.find({hash, j - i + 1});

            if(it == hashes.end())
            {
                hashes.insert({{hash, j-i+1}});
            }
        }
    }

    int cnt = 0;
    cout << hashes.size() << endl;
    
    return 0;
}
