#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers, int border) 
{
    const auto first_not_less = numbers.lower_bound(border);

    if (first_not_less == numbers.begin()) 
    {
        return first_not_less;
    }

    const auto last_less = prev(first_not_less);
    if (first_not_less == numbers.end()) 
    {
        return last_less;
    }

    const bool is_left = (border - *last_less <= *first_not_less - border);
    return is_left ? last_less : first_not_less;
}

int main() 
{
    std::set<int> numbers = { 1, 4, 6 };
    std::cout <<
        *FindNearestElement(numbers, 0) << " " <<
        *FindNearestElement(numbers, 3) << " " <<
        *FindNearestElement(numbers, 5) << " " <<
        *FindNearestElement(numbers, 6) << " " <<
        *FindNearestElement(numbers, 100) << std::endl;

    std::set<int> empty_set;

    std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
    return 0;
}