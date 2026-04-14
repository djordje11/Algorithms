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
};
map<unsigned, pair<node*, int>> location_map;
node head;

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

    int q;
    cin >> q;
    while (q--)
    {
        char c;
        unsigned x;
        cin >> c >> x;
        insert(0);
        if (c == '+')
        {
            insert(x);
        }
        else if (c == '-')
        {
            auto it = location_map.find(x);
            it->second.second--;
            if (it->second.second == 0)
            {
                node* child = it->second.first;
                node* curr = child->parent;
                delete child;
                int j = 0;

                if (x & (1 << j))
                    curr->right = nullptr;
                else
                    curr->left = nullptr;
                j++;
                while (curr != nullptr && (curr->right == nullptr && curr->left == nullptr))
                {
                    node* tmp = curr;
                    curr = curr->parent;

                    if (x & (1 << j))
                        curr->right = nullptr;
                    else
                        curr->left = nullptr;
                    j++;

                    delete tmp;
                }


                location_map.erase(it);

            }
        }
        else if (c == '?')
        {
            node* tmp = &head;
            unsigned res = 0;
            for (int i = 29; i >= 0; i--)
            {
                if(tmp == nullptr)break;
                if (x & (1 << i))
                {
                    if (tmp->left != nullptr)
                    {
                        tmp = tmp->left;
                        res = res | (1 << i);
                    }
                    else if(tmp->right != nullptr)
                    {
                        tmp = tmp->right;  
                    }
                    else 
                    {
                        break;
                    }
                }
                else
                {
                    if (tmp->right != nullptr)
                    {
                        tmp = tmp->right;
                        res = res | (1 << i);
                    }
                    else if (tmp->left != nullptr)
                    {
                        tmp = tmp->left;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            cout << res << endl;
        }

    }
    return 0;
}