#include <iostream>



int main()
{
    int t;
    int r[50000][5];
    std::cin >> t;
    while(t--)
    {
    int n;
    std::cin >> n;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            std::cin >> r[i][j];
        }
    }

    int curr_champ = 0;

    for(int i = curr_champ + 1; i < n; i++)
    {
        int cmp = 0;
        for(int j = 0; j < 5; j++)
        {
            if(r[curr_champ][j] < r[i][j])
                cmp++;
            else 
                cmp--;
        }

        if(cmp < 0)
        {
                //std::cout << i << " <--- " << curr_champ << std::endl;
                curr_champ = i;
        }
        else{}
                //std::cout << curr_champ << " <--- " << i << std::endl;

    }

    bool curr = true;
    for(int i = 0; i < curr_champ; i++)
    {
        int cmp = 0;
        for(int j = 0; j < 5; j++)
        {
            if(r[curr_champ][j] < r[i][j])
                cmp++;
            else 
                cmp--;
        }
        if(cmp < 0)
        {                
            //std::cout << i << " <--- " << curr_champ << std::endl;
            curr = false;
        }
        else{}
            //std::cout << curr_champ << " <--- " << i << std::endl;

    }
    if(curr)
        std::cout << curr_champ+1 << std::endl;
    else
        std::cout << "-1" << std::endl;

    }

    return 0;
}
