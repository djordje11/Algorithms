    #include <iostream>
     #include <set>
    int main()
    {
        int a[1000000];
        int n, m;
        std::cin >> n >> m;
        bool dont_move[1000];

        for(int i = 0; i < 1000; i++)
            dont_move[i] = false;
     
        std::set<int> reminders;
     
        for(int i = 0; i < n; i++)
            std::cin >> a[i];
     
     
        int lala[1001];
        int reminders_size = 0;
        for(int i = 0; i < n; i++)
        {
            int k = a[i] % m;
            if(dont_move[k])continue;
            int count = 0;
            for(auto it : reminders)
            {   
                lala[count++] = (it+k) % m;
            }
     
            reminders.insert(k);
            for(int j = 0; j < count; j++)
                reminders.insert(lala[j]);
            if(reminders.size() == reminders_size)
                dont_move[k] = true;
            reminders_size = reminders.size();
        }
     
        if(reminders.count(0))
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;
     
     
        return 0;
    }
