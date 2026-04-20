#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

int a[100000];
int divs[100000][2];

void calculate(int l, int r, map<int, int>& count, int &count_alive, vector<int>& res, int l_cond, int r_cond)
{
    
    for (int i = l; i <= r; i++)
    {
        if( (divs[i][0] == -1  || divs[i][0] < l_cond) && (divs[i][1] == -1 || divs[i][1] > r_cond))
        {
            auto it = count.find(a[i]);
            if(it == count.end())
            {
                res.push_back(i);
                count.insert({a[i], 1});
                count_alive++;
            }
            else 
            {
                it->second++;
                count_alive++;
            }
        }
    }
}

struct seg_tree
{
    seg_tree* left = (nullptr), * right = nullptr;
    int m_l, m_r, m;
    std::vector<int> left_alive, right_alive;
    std::map<int, int> left_count, right_count;
    int left_count_alive = 0, right_count_alive = 0;

    seg_tree(int l, int r)
    {
        this->m_l = l;
        this->m_r = r;
        if (r - l <= 3)
        {
            //left_alive = calculate(l, r);
            return;
        }

        m = (r + l) / 2;
        left = new seg_tree(l, m);
        right = new seg_tree(m + 1, r);

        calculate(l, m, left_count, left_count_alive, left_alive, l, m);
        calculate(m + 1, r, right_count, right_count_alive, right_alive, m+1, r);
    }


    void count_r(int position_l, int position_r, map<int,int>& count, vector<int>& res)
    {
        if (position_l > m_r || position_r < m_l)
            return ;
        int ret = 0;
        if (m_r - m_l <= 3)
        {
            calculate(std::max(m_l, position_l), std::min(m_r, position_r), count, ret, res,position_l, position_r);
            return ;
        }

        if (position_l > m)
            return right->count_r(position_l, position_r, count,res);


        if (position_r < m + 1)
            return left->count_r(position_l, position_r, count, res);

        
        if(position_r >= m_r)
        {
            for(auto it : right_alive)
            {
                int desni = divs[it][1];
                int levi = divs[it][0];

                if( (desni == -1 || desni > position_r) && (levi == -1 || levi < position_l))
                {
                    int num = a[it];
                    auto jt = count.find(num);
                    if(jt == count.end())
                    {
                        count.insert({num, right_count[num]});
                        res.push_back(it);
                    }
                    else 
                    {
                        jt->second += right_count[num];
                    }
                }
            }
        }
        else
        {
            right->count_r(position_l, position_r, count, res);
        }

        if(position_l <= m_l)
        {
            for(auto it : left_alive)
            {
                int desni = divs[it][1];
                int levi = divs[it][0];

                if( (desni == -1 || desni > position_r) && (levi == -1 || levi < position_l))
                {
                    int num = a[it];
                    auto jt = count.find(num);
                    if(jt == count.end())
                    {
                        count.insert({num, left_count[num]});
                        res.push_back(it);
                    }
                    else 
                    {
                        jt->second += left_count[num];
                    }
                }
            }
        }
        else
        {
            left->count_r(position_l, position_r, count, res);
        }
    }

};
void calc(std::map<int, int>& positions, std::map<int, int>& inv_positions, int n, bool fw)
{
    for(int i = fw ? 0 : n-1; fw ? i<n : i >= 0; fw ? i++ : i--)
    {
        auto it = positions.find(a[i]);
        if(it == positions.end())
        {
            positions.insert({a[i], i});
            inv_positions.insert({i, a[i]});
        }
        else
        {
            int val = it->first;
            int pos = it->second;
            it->second = i;

            inv_positions.erase(pos);
            inv_positions.insert({i, a[i]});
        }
        if(fw)
        {
            auto it = inv_positions.lower_bound(i);
            if(it != inv_positions.begin())
            {
                --it;
                bool should_break = false;
                while(true)
                {
                    if(it == inv_positions.begin())
                        should_break = true;
                    if(it->second % a[i])
                    {
                        divs[i][0] = it->first;
                        break;
                    }
                    if(should_break)break;
                    it--;
                }
            }
        }
        else 
        {
            auto jt = inv_positions.upper_bound(i);
            while(jt != inv_positions.end())
            {
                if(jt->second % a[i])
                {
                    divs[i][1] = jt->first;
                    break;
                }
                jt++;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        divs[i][0] = divs[i][1] = -1;
        cin >> a[i];
    }


    std::map<int, int> positions;
    std::map<int, int> inv_positions;

    std::map<int, int> back_positions;
    std::map<int, int> back_inv_positions;
    
    
    calc(positions, inv_positions, n, true);
    calc(back_positions, back_inv_positions, n, false);
    
    seg_tree s(0, n-1);
    int m;
    cin >> m;
    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        std::vector<int> res;
        map<int, int> count;
        s.count_r(x-1, y-1, count, res);
        int k = y - x + 1;
        for(auto it : count)
            k -= it.second;
        cout << k << endl;
    }


    return 0;
}
