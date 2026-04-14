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
    int count = 0;
};
map<unsigned, pair<node*, int>> location_map;
node head;

node* stack[19];
void insert(unsigned x)
{
    node* tmp = &head;
    bool new_inserted = false;

    for (int i = 18; i >= 0; i--)
    {
        node* par = tmp;
        stack[i] = tmp;
        if (x & (1 << i))
        {
            if (tmp->right == nullptr)
            {
                new_inserted = true;
                tmp->right = new node;
            }
            tmp = tmp->right;
        }
        else
        {
            if (tmp->left == nullptr)
            {  
                new_inserted = true;
                tmp->left = new node;
            }
            tmp = tmp->left;
        }
        tmp->parent = par;
    }
    if(new_inserted)
    {
        for (int i = 18; i >= 0; i--)
            stack[i]->count+=1;
    }
 }

int where_is_found = 0;
bool dfs(unsigned x, int k, node* curr, unsigned& res)
{
    if(curr->count == 1 << (k+1))
        return false;
    if(k == 0)
    {
        if(x & 1)
        {
            if(curr->right == nullptr)
            {
                where_is_found = k;
                res = (res | 1);
                return true;
            }
            if(curr->left == nullptr)
            {
                where_is_found = k;
                res = (res | 1) ^ 1;
                return true;
            }
            return false;
        }
        else{
            if(curr->left == nullptr)
            {
                where_is_found = k;
                res = (res | 1) ^ 1;
                return true;
            }
            if(curr->right == nullptr)
            {
                where_is_found = k;
                res = (res | 1);
                return true;
            }
            return false;
        }      
    }
    if(x & (1 << k))
    {
        if(curr->right == nullptr)
        {
            where_is_found = k;
            res = (res | (1<<k));
            return true;
        }

        bool ret = dfs(x, k-1, curr->right, res);

        if(ret){
            res = (res | (1<<k));
            return true;
        }
        if(curr->left == nullptr)
        {
            where_is_found = k;
            res = (res | (1<<k)) ^ (1<<k);
            return true;
        }
        ret = dfs(x, k-1, curr->left, res);
        if(ret) {
            res = (res | (1<<k)) ^ (1<<k);
            return true;
        }
        return false;
    }
    else
    {
        if(curr->left == nullptr)
        {
            where_is_found = k;
            res = (res | (1<<k)) ^ (1<<k);
            return true;
        } 
        bool ret = dfs(x, k-1, curr->left, res);
        if(ret){
            res = (res | (1<<k)) ^ (1<<k);
            return true;
        }
        if(curr->right == nullptr)
        {
            where_is_found = k;
            res = (res | (1<<k));
            return true;
        }
        ret = dfs(x, k-1, curr->right, res);
        if(ret) {
            res = (res | (1<<k));
            return true;
        }
        return false;
    }
}

 int main()
 {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        insert(x);
    }

    unsigned acc = 0;

    for(int i = 0; i < m; i++)
    {
        unsigned x;
        cin >> x;
        acc = acc ^ x;

        unsigned res = 0;
        unsigned mask = 0xFFFFFFFF;
        dfs(acc, 18, &head, res);
        if(where_is_found > 0)
            mask <<= (where_is_found);
        cout << ((res ^ acc) & mask) << endl;

    }


    return 0;
}