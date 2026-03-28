#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
bool used[200001];
int parent[200001];
int count1[200001];
int stack[200001];
int edges[200001][2];
bool cl_connected[200001];

int find_parent(int x)
{
    if (parent[x] == x)return x;
    return parent[x] = find_parent(parent[x]);
}

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
            count1[i] = 1;
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
                        count1[parent[j]] += count1[i];
                        should_break = true;
                      //  class_repr.erase(i);
                        for(int k = 0 ; k < stck_count; k++)
                            parent[stack[k]] = parent[j]; 

                        break;
                    }
                    stack[stck_count++] = j;
                    used[j] = true;
                    parent[j] = i;
                    count1[i]++;
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
                        count1[parent[j]] += count1[i];
                        should_break = true;
                     //   class_repr.erase(i);
                        for(int k = 0 ; k < stck_count; k++)
                            parent[stack[k]] = parent[j]; 

                        break;
                    }
                    stack[stck_count++] = j;
                    used[j] = true;
                    parent[j] = i;
                    count1[i]++;
                }

            }



        }

    }

    //for(auto it : class_repr)
    //{
    //    cout << it << " size " << count1[it] << endl;
  //  }
//
    vector<int> class_repr;


    for(int i = 1; i <= n; i++)
        if(parent[i] ==i)
            class_repr.push_back(i);


    std::map<pair<int,int>, int> count_edges;
    for(int i = 0; i < m; i++)
    {
        int x = parent[edges[i][0]];
        int y = parent[edges[i][1]];
        if(x == y)
            continue;
        cl_connected[x] = cl_connected[y] = true;
        if(x > y)
            swap(x, y);
        auto it = count_edges.find({x, y});
        if(it == count_edges.end())
        {
            count_edges.insert({{x, y}, 1});
        }
        else 
        {
            it->second++;
        }
    }

    for(auto it : class_repr)
        if(!cl_connected[it])
        {
            std::cout << 1 << endl << n;
            return 0;
        }
    vector<pair<int,int>> parrented;
    for(auto it : count_edges)
    {
        int x = it.first.first;
        int y = it.first.second;
        int num_of_edges = it.second;

        if(count1[x] * count1[y] > num_of_edges)
        {
            int px = find_parent(x);
            int py = find_parent(y);
            
            if(px != py)
            {
                parent[px] = py;
                parrented.push_back({px, py});
                //count1[py] += count1[px];
            }
        }
    }

    for(auto it : parrented)
        count1[it.second] += count1[it.first];

    int cnt = 0;
    std::vector<int> c_s;
    for(int i = 1; i <= n; i++)
        if(parent[i] == i)c_s.push_back(count1[i]);


    std::sort(c_s.begin(), c_s.end());

    std::cout <<  c_s.size() << std::endl;

    for(auto it : c_s)
        cout << it << " ";
    cout << endl;

    return 0;
}