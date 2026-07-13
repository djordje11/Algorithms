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
    node* ch[2] = { nullptr, nullptr };
    bool visited = false;
    int cnt = 0;
    //node* left = nullptr, * right = nullptr;
    node* parent = nullptr;
    int value = -1;int node1 = -1;
};

node head;
node* start_node = nullptr, * lca = nullptr;
const int BIT_NUM = 29;

void insert(unsigned x, unsigned nd)
{
    node* tmp = &head;
    for (int i = BIT_NUM; i >= 0; i--)
    {
        node* par = tmp;
        if (x & (1 << i))
        {
            if (tmp->ch[1] == nullptr)
            {
                tmp->ch[1] = new node;
                tmp->cnt++;
            }
            tmp = tmp->ch[1];
        }
        else
        {
            if (tmp->ch[0] == nullptr)
            {
                tmp->ch[0] = new node;
                tmp->cnt++;
            }
            tmp = tmp->ch[0];
        }
        tmp->parent = par;
    }
    tmp->value = x;
    tmp->node1 = nd;
}

using ull = unsigned long long;

ull smallest_edge(node* l, node* r, int bit)
{
    if (bit == 1)return 0;

    if (l->cnt == 2 && r->cnt == 2)
    {
        return min(smallest_edge(l->ch[0], r->ch[0], bit - 1), smallest_edge(l->ch[1], r->ch[1], bit - 1));
    }

    if (l->ch[0] != nullptr && r->ch[0] != nullptr)
        return smallest_edge(l->ch[0], r->ch[0], bit - 1);

    if (l->ch[1] != nullptr && r->ch[1] != nullptr)
        return smallest_edge(l->ch[1], r->ch[1], bit - 1);

    if (l->ch[0] != nullptr && r->ch[1] != nullptr)
        return (ull(1) << (bit - 2)) | smallest_edge(l->ch[0], r->ch[1], bit - 1);

    if (l->ch[1] != nullptr && r->ch[0] != nullptr)
        return (ull(1) << (bit - 2)) | smallest_edge(l->ch[1], r->ch[0], bit - 1);

    return 0;
}

ull mst(node* curr, int bit)
{
    if (bit == 0)
        return 0;
    ull res = 0;

    for (int i = 0; i < 2; i++)
        if (curr->ch[i])
            res += mst(curr->ch[i], bit - 1);

    if (curr->cnt == 2)
    {
        res += (ull(1) << (bit - 1)) | smallest_edge(curr->ch[0], curr->ch[1], bit);
    }
    return res;
}


int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        insert(x, i);
    }

    cout << mst(&head, BIT_NUM + 1) << endl;

    return 0;
}
