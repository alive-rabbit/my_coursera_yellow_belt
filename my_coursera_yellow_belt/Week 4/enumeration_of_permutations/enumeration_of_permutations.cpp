#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    int range_length;
    std::cin >> range_length;
    std::vector<int> permutation(range_length);

    iota(permutation.rbegin(), permutation.rend(), 1);

    do 
    {
        for (int num : permutation) 
        {
            std::cout << num << ' ';
        }
        std::cout << std::endl;
    } while (prev_permutation(permutation.begin(), permutation.end()));

    return 0;
}