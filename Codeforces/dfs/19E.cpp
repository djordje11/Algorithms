#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define N_MAX 1000001
using ull = signed long long;

bool visited[N_MAX];
int level[N_MAX];
int h[N_MAX];
int edges[N_MAX][2];
map<pair<int, int>, int> edges_map;
int edges_cycles[N_MAX];
int cycle_type[N_MAX];
int cycle_cord[N_MAX][2];
int cyc_id = 1;
int color[N_MAX];

/////

int t_in[N_MAX];
int t_out[N_MAX];

int parrent[N_MAX];
int t = 0;

void dfs1(int curr, int par, vector<vector<int>>& graph)
{
    t_in[curr] = t++;
    visited[curr] = true;
    parrent[curr] = par;
    for (auto it : graph[curr])
    {
        if (!visited[it])
        {
            dfs1(it, curr, graph);
        }
    }
    t_out[curr] = t++;
}

bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}

////
bool first_cycle_found = false;
int cycle_top, cycle_bot;
bool after = false;
bool in = false;
bool before = false;
int cur_min_after = -1;
int right_in = -1, left_in = -1;
int overlap = true;
std::vector<int> st;
bool more_than_two = false;

void dfs(int curr, int par, vector<vector<int>>& graph, int curr_level)
{
    visited[curr] = true;
    level[curr] = curr_level;
    h[curr] = curr_level;
    if (!first_cycle_found)
        st.push_back(curr);
    for (auto it : graph[curr])
    {
        if (it == par)continue;

        bool found = false;
        if (visited[it] && level[it] < level[curr])
        {
            if ((level[curr] - level[it] + 1) % 2 == 0)
            {
                int x = curr;
                int y = it;
                if (x > y)swap(x, y);
                auto jt = edges_map[{x, y}];
                edges_cycles[jt] = cyc_id;

                int tmp = curr;

                while (is_ancestor(it, tmp))
                {
                    int x = tmp;
                    int y = parrent[tmp];
                    if (x > y)swap(x, y);

                    auto zt = edges_map[{x, y}];

                    if (edges_cycles[zt] == 0)
                    {
                        edges_cycles[zt] = cyc_id;
                        tmp = parrent[tmp];
                    }
                    else
                    {
                        found = true;
                        cycle_type[edges_cycles[zt]] = 2;
                        tmp = cycle_cord[edges_cycles[zt]][0];
                    }
                }

                if (found)
                {
                    cycle_type[cyc_id] = 2;
                }
                else {
                    cycle_type[cyc_id] = 1;
                }
                cycle_cord[cyc_id][0] = it;
                cycle_cord[cyc_id++][1] = curr;
            }
            else if (!first_cycle_found)
            {
                first_cycle_found = true;
                cycle_top = it;
                cycle_bot = curr;
                right_in = cycle_bot;
                left_in = cycle_top;
                after = true;
                cur_min_after = cycle_top;
            }
            else
            {
                more_than_two = true;
                if (after)
                {
                    if (is_ancestor(cycle_bot, it))
                    {
                        cur_min_after = cycle_bot;
                    }
                    else if (is_ancestor(cur_min_after, it))
                    {
                            cur_min_after = it;
                    }
                }
                else if (in)
                {
                    if (is_ancestor(it, st[st.size() - 1]))
                    {
                        right_in = st[st.size() - 1];
                        int l = it;
                        if (is_ancestor(it, cycle_top))
                            l = cycle_top;
                        if (is_ancestor(left_in, l))
                            left_in = l;
                    }
                    else
                    {
                        overlap = false;
                    }
                }
                else if (before)
                {
                    overlap = false;
                }
            }
        }
        if (!visited[it])
        {
            dfs(it, curr, graph, curr_level + 1);
        }
        h[curr] = min(h[curr], h[it]);
    }
    if (cycle_bot == curr)
    {
        after = false;
        in = true;
    }
    if (cycle_top == curr)
    {
        in = false;
        before = true;
    }
    if (curr == st[st.size() - 1])
    {
        st.pop_back();
    }
    return;
}

vector<vector<int>> graph(N_MAX);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;

    while (t--)
    {
        int n, m;
        cin >> n >> m;

        for (int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            edges[i][0] = x;
            edges[i][1] = y;
            graph[x].push_back(y);
            graph[y].push_back(x);

            if (x > y)swap(x, y);
            edges_map.insert({ {x, y}, i });
        }


        for (int i = 1; i <= n; i++)
            if (!visited[i])
                dfs1(i, 0, graph);

        for (int i = 1; i <= n; i++)
            visited[i] = false;

        for (int i = 1; i <= n; i++)
            if (!visited[i])
                dfs(i, 0, graph, 0);

        int x, y;
        std::set<int> result;
        if (!first_cycle_found)
        {
            //all
            for (int i = 1; i <= m; i++)
                result.insert(i);
        }
        else if (cur_min_after == cycle_bot || left_in == right_in || is_ancestor(right_in, left_in) || !overlap || (cur_min_after != -1 && !is_ancestor(cur_min_after, right_in)))
        {
            
        }
        else
        {
            if (!more_than_two)
            {
                int tmp1 = cycle_bot;
                int tmp2 = cycle_top;
                if (tmp1 > tmp2)swap(tmp1, tmp2);
                result.insert(edges_map[{tmp1, tmp2}] + 1);
            }

            int from = right_in;
            int to = cur_min_after;
            if (is_ancestor(cur_min_after, left_in))
                to = left_in;

            while (from != to)
            {
                x = from;
                y = parrent[from];

                if (x > y)swap(x, y);

                auto jt = edges_map[{x, y}];
                if (edges_cycles[jt] == 0)
                {
                    result.insert(jt + 1);
                }
                from = parrent[from];
            }
        }
        cout << result.size() << endl;
        for (auto it : result)
            cout << it << " ";
        cout << endl;

    }

    return 0;
}
