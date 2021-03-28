#include <iostream>
#include <vector>
#include <algorithm>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) 
{
    // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
    int range_length = range_end - range_begin;
    if (range_length < 2) 
    {
        return;
    }

    // 2. Создаем вектор, содержащий все элементы текущего диапазона
    std::vector<typename RandomIt::value_type> elements(range_begin, range_end);

    // 3. Разбиваем вектор на три равные части
    auto one_third = elements.begin() + range_length / 3;
    auto two_third = elements.begin() + range_length * 2 / 3;

    // 4. Вызываем функцию MergeSort от каждой трети вектора
    MergeSort(elements.begin(), one_third);
    MergeSort(one_third, two_third);
    MergeSort(two_third, elements.end());

    // 5. С помощью алгоритма merge cливаем первые две трети во временный вектор
    std::vector<typename RandomIt::value_type> interim_result;
    merge(elements.begin(), one_third, one_third, two_third, back_inserter(interim_result));

    merge(interim_result.begin(), interim_result.end(), two_third, elements.end(), range_begin);
}

int main() 
{
    std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
    MergeSort(begin(v), end(v));
    for (int x : v) 
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}