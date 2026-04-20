#include <iostream>


int first_base;
int second_base;
int first[200000][7];
int second[200000][7];
int first_counter = 0;
int second_counter = 0;

int calc_base_leng(int k)
{
    int i = 0;
    while (true)
    {
        k /= 7;
        i++;
        if (k == 0)break;
    }
    return i;
}

void print_all(int k, int array[200000][7], int& counter)
{
    int a[10];
    int length = calc_base_leng(k - 1);
    for (int i = 0; i < k; i++)
    {
        int r = i;
        for (int j = length-1; j >= 0; j--)
        {
            array[counter][j] = r % 7;
            r /= 7;
        }

        //std::cout << std::endl;
        counter++;
    }
}

#include <set>
int main()
{
    int n, m;
    std::cin >> n >> m;

    first_base = calc_base_leng(n-1);
    second_base = calc_base_leng(m-1);
    //std::cout << first_base << " " << second_base << std::endl;

    if (first_base + second_base > 7)
    {
        //std::cout << "ovde" << std::endl;
        std::cout << 0 << std::endl;
        return 0;
    }


    print_all(n, first, first_counter);
    print_all(m, second, second_counter);
    //std::cout << first_counter << " " << second_counter << std::endl;

    int counter = 0;
    for (int i = 0; i < first_counter; i++)
    {
        std::set<int> tmp;
        bool distinct = true;
        for (int j = 0; j < first_base; j++)
        {
            if (tmp.count(first[i][j]))
            {
                distinct = false;
                break;
            }
            tmp.insert(first[i][j]);

        }
        if (!distinct)continue;


        for (int k = 0; k < second_counter; k++)
        {
            std::set<int> new_tmp;
            bool distinct = true;
            for (int j = 0; j < second_base; j++)
            {
                if (tmp.count(second[k][j]) || new_tmp.count(second[k][j]))
                {
                    distinct = false; break;
                }
                new_tmp.insert(second[k][j]);

            }
            counter += distinct;

        }




    }
    std::cout << counter << std::endl;
    return 0;
}
