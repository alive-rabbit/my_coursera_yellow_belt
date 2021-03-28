#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::vector<std::string> SplitIntoWords(const std::string& str)
{
    std::vector<std::string> result;

    auto str_begin = begin(str);
    const auto str_end = end(str);

    while (true) 
    {

        auto it = find(str_begin, str_end, ' ');

        result.push_back(std::string(str_begin, it));

        if (it == str_end) 
        {
            break;
        }
        else 
        {
            str_begin = it + 1;
        }
    }

    return result;
}

int main() 
{
    std::string s = "C Cpp Java Python";

    std::vector<std::string> words = SplitIntoWords(s);
    std::cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) 
    {
        if (it != begin(words)) 
        {
            std::cout << "/";
        }
        std::cout << *it;
    }
    std::cout << std::endl;

    return 0;
}