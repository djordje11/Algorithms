#include <functional>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
using ull = unsigned long long;
ull h[100000];
int previ[100000];
int main()
{
    int n, d;
    cin >> n >> d;

    for(int i = 0; i < n; i++)
        cin >> h[i];

    std::set<ull> skup;
    std::map<ull, int> mapa;
    std::map<ull, int> mapa2;
        std::set<ull> skup2;
    std::map<pair<ull, ull>, int> mapa3;

    skup.insert(h[0]);
    skup2.insert(h[0]);
    mapa.insert({h[0], 1});
    mapa2.insert({h[0], 1});
    mapa3.insert({{1, h[0]}, 0});
    for(int i = 1; i < n; i++)
    {
        auto it =  skup.upper_bound(h[i] - ull(d));
        auto zt = skup2.lower_bound(h[i] + ull(d));

        int value = 0;

        if(ull(d) < h[i] && it != skup.begin())
        {
            --it;
            value = mapa[*it] + 1;

            auto tmp = mapa3.find({value-1, *it});
            previ[i] = tmp->second;
        }
        if(zt != skup2.end())
        {
            if(mapa2[*zt] + 1 > value)
            {
                value = mapa2[*zt] + 1;
                auto tmp = mapa3.find({value-1, *zt});
                previ[i] = tmp->second;
            }
        }


        if(value == 0)continue;

        mapa3.insert({{value, h[i]}, i});
        auto jt = mapa.upper_bound(h[i]);

        if(jt == mapa.begin())
        {
            while(jt != mapa.end() && jt->second <= value)
            {
                auto tmp = jt;
                jt++;
                skup.erase(tmp->first);
                mapa.erase(tmp);
            }
            skup.insert(h[i]);
            mapa.insert({h[i] , value});
        }
        else 
        {
            --jt;
            if(jt->second < value)
            {
                bool not_insert = false;
                if(jt->first == h[i])
                {
                    jt->second = std::max(jt->second, value);
                    value = jt->second;
                    not_insert = true;
                }
                
                jt++;
                while(jt != mapa.end() && jt->second <= value)
                {
                    auto tmp = jt;
                    jt++;
                    skup.erase(tmp->first);
                    mapa.erase(tmp);
                }
                if(!not_insert)
                { 
                    mapa.insert({h[i], value});
                    skup.insert(h[i]);
                }
            }
        }
    


        jt = mapa2.lower_bound(h[i]);

        if(jt == mapa2.end())
        {
            jt--;
            while(true)
            {
                if(jt->second > value)
                    break;
                bool should_end;
                if(jt == mapa2.begin())
                    should_end = true;

                auto tmp = jt;
                jt--;
                skup2.erase(tmp->first);
                mapa2.erase(tmp);
                if(should_end)break;
            }

            skup2.insert(h[i]);
            mapa2.insert({h[i] , value});

        }
        else 
        {
            if(jt->second < value)
            {
                bool should_insert = true;
                if(h[i] == jt->first)
                {
                    jt->second = std::max(jt->second, value);
                    value = jt->second;
                    should_insert = false;
                }
                jt--;
                while(true)
                {
                    if(jt->second > value)
                        break;
                    bool should_end;
                    if(jt == mapa2.begin())
                        should_end = true;

                    auto tmp = jt;
                    jt--;
                    skup2.erase(tmp->first);
                    mapa2.erase(tmp);
                    if(should_end)break;
                }

                if(should_insert)
                {
                    skup2.insert(h[i]);
                    mapa2.insert({h[i] , value});
                }

            }
        }
    }


    auto zt = mapa3.rbegin();
    
    cout << zt->first.first << endl;

    int pos = zt->second;

    vector<int> stack;
    while(true)
    {
        stack.push_back(pos);
        if(pos == 0)break;
        pos = previ[pos];
    }

    for(auto it = stack.rbegin(); it != stack.rend(); it++)
        cout << *it + 1<< " ";
    cout << endl;


    return 0;
}