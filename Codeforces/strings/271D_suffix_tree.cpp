#include <cstring>
#include <iostream>

using namespace std;
using ull = unsigned long long;
char goods[27];

struct trie
{
    struct trie* nodes[26];
    trie()
    {
        for(int i = 0; i < 26; i++)
            nodes[i] = nullptr;
    }
    void insert(char* s, int curr, int n)
    {
        if(curr == n)
            return;
        if(nodes[s[curr] - 'a'] == nullptr)
            nodes[s[curr] - 'a'] = new trie;
        nodes[s[curr] - 'a']->insert(s, curr+1, n);
    }
    int count(int k, int curr)
    {
        if(curr > k)return 0;
        int ret = 1;
        for(int i = 0; i < 26; i++)
        {
            if(nodes[i] != nullptr)
            {
                ret += nodes[i]->count(k, curr + (goods[i] == '0'));
            }
        }
        return ret;
    }
};

int main()
{
    char s[1501];
    int k;

    cin >> s;
    cin >> goods;
    cin >> k;

    int n = strlen(s);

    trie t;

    for(int i = 0; i < n; i++)
    {
        t.insert(s, i, n);    
    }
    
    cout << t.count(k, 0) - 1 << endl;
    return 0;
}
