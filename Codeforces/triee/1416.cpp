// CF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include <limits>
#include <map>
#include <vector>
#include <set>
#include <utility>

struct node
{
    node* left = nullptr, * right = nullptr;
    node* parent = nullptr;
    unsigned left_count = 0, right_count = 0;
};
map<unsigned, pair<node*, int>> location_map;
node head;
unsigned long long  inversion[30];
unsigned long long normal[30];
void insert(unsigned x)
{
    node* tmp = &head;
    for (int i = 29; i >= 0; i--)
    {
        node* par = tmp;
        if (x & (1 << i))
        {
            if (tmp->right == nullptr)
                tmp->right = new node;
            tmp->right_count++;
            normal[i] += tmp->left_count;
            tmp = tmp->right;
        }
        else
        {
            if (tmp->left == nullptr)
                tmp->left = new node;
            tmp->left_count++;
            inversion[i] += tmp->right_count;
            tmp = tmp->left;
        }
        tmp->parent = par;
    }
    auto it = location_map.find(x);
    if (it == location_map.end())
    {
        location_map.insert({ x, {tmp, 1} });
    }
    else
    {
        it->second.second++;
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        insert(x);
    }

    unsigned res = 0;
    long long unsigned sum = 0;
    for (int i = 29; i >= 0; i--)
    {
        if (inversion[i] > normal[i])
            res = res | (1 << i);
        sum = sum + min(inversion[i], normal[i]);
    }

    cout << sum << " " << res << endl;

    return 0;
}
