    // CF.cpp : This file contains the 'main' function. Program execution begins and ends there.
    //
     
    #include <iostream>
    using namespace std;
    #include <set>
    #include <map>

    struct node
    {
        map<int, node*> childs;
        node* parent = nullptr;
        bool is_end = true;

    };
    node head;
    std::set<node*> moj_ends{&head};

    void insert(const std::string& s)
    {
        node* tmp = &head;
        for (int i = 0; i < s.length(); i++)
        {   
            if(tmp->is_end == true)
            {
                moj_ends.erase(tmp);
            } 
            tmp->is_end = false;

            node* par = tmp;
            int curr = s[i] - 'a';

            auto it = tmp->childs.find(curr);

            if(it == tmp->childs.end())
            {
                tmp->childs.insert({curr, new node});
            }

            tmp = tmp->childs[curr];
            tmp->parent = par;
        }
        moj_ends.insert(tmp);
    }
    

    int dfs(node* curr)
    {
        if(curr->is_end)return 1;

        bool has[4] = {false, false, false, false};
        for(auto it : curr->childs)
        {
            int ret = dfs(it.second);
            has[ret] = true;
        }
        if (has[3] || (has[0] && has[1]))
            return 2;
        
        if(has[2] && has[1])
            return 0;

        if(has[2] && has[0])
            return 1;

        if(has[2])
            return 3;
        if(has[1])return 0;
        if(has[0])return 1;

        return 1;
    }

    int dfs1(node* curr, bool has[4])
    {
        if(curr->is_end)return 1;

        for(auto it : curr->childs)
        {
            int ret = dfs(it.second);
            has[ret] = true;
        }
        if (has[3] || (has[0] && has[1]))
            return 2;
        
        if(has[2] && has[1])
            return 0;

        if(has[2] && has[0])
            return 1;

        if(has[2])
            return 3;
        
        if(has[1])return 0;
        if(has[0])return 1;

        return 1;
    }


    int main()
    {
        unsigned long long n, k;
        cin >> n >> k;

        for (int i = 0; i < n; i++)
        {
            std::string s;
            cin >> s;
            insert(s);
        }
     
        bool has[4] = {false, false, false, false};
        dfs1(&head, has);

        
        if((has[1] && has[0]) || has[3])
        {
            cout << "First" << endl;
        }
        else if(has[1] && has[2])
        {
            if(k%2 == 1)
                cout << "First" << endl;
            else 
                cout << "Second" << endl;
        }
        else if(has[0] && has[2])
        {
            cout << "Second" << endl;
        }
        else if(has[2])
        {
            cout << "Second" << endl;
        }
        else if(has[1])
        {
            if(k%2 == 1)
                cout << "First" << endl;
            else 
                cout << "Second" << endl;
        }
        else 
        {
            cout << "Second" << endl;
        }


        return 0;
    }