#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;
bool used[100001];
int parent[100001];
int count[100001];
int stack[100001];
int edges[100001][2];
int main()
{
    int n, m;
    cin >> n >> m;
    vector<set<int>> graph(n+1);



    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].insert(y);
        graph[y].insert(x);
        edges[i][0] = x;
        edges[i][1] = y;
    }

    //set<int> class_repr;
    for(int i = 1; i <= n; i++)
    {
        if(!used[i])
        {
            used[i] = true;
            //class_repr.insert(i);
            parent[i] = i;
            int start = 0;
            count[i] = 1;
            int stck_count = 0;                
            bool should_break = false;

            for(auto it : graph[i])
            {
                for(int j = start+1; j < it; j++)
                {
                    if(j == i)continue;
                    if(used[j] == true)
                    {
                        parent[i] = parent[j];
                        count[parent[j]] += count[i];
                        should_break = true;
                      //  class_repr.erase(i);
                        for(int k = 0 ; k < stck_count; k++)
                            parent[stack[k]] = parent[j]; 

                        break;
                    }
                    stack[stck_count++] = j;
                    used[j] = true;
                    parent[j] = i;
                    count[i]++;
                }

                if(should_break)
                    break;
                start = it;
            }

            if((!should_break && graph[i].size() > 0) || graph[i].size() == 0)
            {
                int start; 
                if(graph[i].size() != 0)
                    start = *graph[i].rbegin();
                else start = 0;
                for(int j = start+1; j < n+1; j++)
                {
                    if(j == i)continue;
                    if(used[j] == true)
                    {
                        parent[i] = parent[j];
                        count[parent[j]] += count[i];
                        should_break = true;
                     //   class_repr.erase(i);
                        for(int k = 0 ; k < stck_count; k++)
                            parent[stack[k]] = parent[j]; 

                        break;
                    }
                    stack[stck_count++] = j;
                    used[j] = true;
                    parent[j] = i;
                    count[i]++;
                }

            }



        }

    }
    std::map<pair<int,int>, int> count_edges;
    vector<int> class_repr;

    for(int i = 1; i <= n; i++)
    {
        if(parent[i] == i)
            class_repr.push_back(i);
    }

    for(int i = 0; i < class_repr.size(); i++)
    {
        for(int j = i + 1; j < class_repr.size(); j++)
        {
            int x = class_repr[i];
            int y = class_repr[j];
            if(x > y)
                swap(x, y);
            count_edges.insert({{x, y}, 0});
        }
    }




    for(int i = 0; i < m; i++)
    {
        int x = parent[edges[i][0]];
        int y = parent[edges[i][1]];
        if(x == y)
            continue;

        if(x > y)
            swap(x, y);
        auto it = count_edges.find({x, y});
        
        it->second++;
    }

    for(auto it : count_edges)
    {
        int x = it.first.first;
        int y = it.first.second;
        int num_of_edges = it.second;

        if(count[x] * count[y] > num_of_edges)
        {
            if(parent[x] == x)
                parent[x] = y;
            else
                parent[y] = parent[x]; 
        }
    }
    int cnt = -1;

    for(int i = 1; i <= n; i++)
        if(parent[i] == i)cnt++;

    std::cout << cnt << std::endl;

    return 0;
}