#include <iostream>
#include <map>
#include <stdexcept>

template<typename KeyType, typename ValueType>
ValueType& GetRefStrict(std::map<KeyType, ValueType>& input_map, KeyType key) 
{
    if (input_map.count(key) == 0) 
    {
        throw std::runtime_error("no such key in dictionary");
    }
    return input_map[key];
}

int main()
{
    std::map<int, std::string> m = { {0, "value"} };
    std::string& item = GetRefStrict(m, 0);
    item = "newvalue";
    std::cout << m[0] << std::endl; // выведет newvalue

    return 0;
}