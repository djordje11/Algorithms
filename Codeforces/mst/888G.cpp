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
    int value = -1, node = -1;
};
map<unsigned, pair<node*, int>> location_map;
node head;

void insert(unsigned x, unsigned nd)
{
    node* tmp = &head;
    for (int i = 29; i >= 0; i--)
    {
        node* par = tmp;
        if (x & (1 << i))
        {
            if (tmp->right == nullptr)
                tmp->right = new node;
            tmp = tmp->right;
        }
        else
        {
            if (tmp->left == nullptr)
                tmp->left = new node;
            tmp = tmp->left;
        }
        tmp->parent = par;
    }
    tmp->value = x;
    tmp->node = nd;

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



    return 0;
}