#include <iostream>

using namespace std;

unsigned sizes[1000000];

int main()
{


    int t;
    cin >> t;


    while(t--)
    {

    
    int k;
    cin >> k;


    for(int i = 0; i < k; i++)
    {
        cin >> sizes[i];
        for(int j = 0; j< sizes[i]-1; j++)
        {
            int x;
            cin >> x;
        }
    }

    int start = 19;
    while(true)
    {
        bool found = false;
        for(int i = 0; i < k; i++)
        {
            if(sizes[i] & (1 << start))
            {
                found = true;
                break;

            }
        }
        if(found)break;
        start--;
    }

    unsigned mask = 0;
    for(int i = start; i >= 0; i--)
    {
        int num_of_found = 0;
        for(int j = 0; j < k; j++)
        {
            if(sizes[j] & (1 << i))
                num_of_found++;
        }
        if(num_of_found == 1)
        {
            mask = mask | (1<<i);
        }
        else if(num_of_found > 1)
        {
            for(int z = i; z >= 0; z--)
                mask = mask | (1 << z);
            break;
        }
    }

    cout << mask << endl;
    }
    return 0;
}