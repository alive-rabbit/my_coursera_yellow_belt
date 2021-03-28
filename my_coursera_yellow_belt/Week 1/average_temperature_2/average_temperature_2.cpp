#include <iostream>
#include <vector>

int main() 
{
    int n;
    std::cin >> n;
    std::vector<int> temperatures(n);
    int64_t sum = 0;
    for (int& temperature : temperatures) 
    {
        std::cin >> temperature;
        sum += temperature;
    }

    int average = sum / n;

    std::vector<int> above_average_indices;
    for (int i = 0; i < n; ++i) 
    {
        if (temperatures[i] > average) 
        {
            above_average_indices.push_back(i);
        }
    }

    std::cout << above_average_indices.size() << std::endl;
    for (int i : above_average_indices) 
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
