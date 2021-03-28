#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <string>

// Возвращает пустую строку, если имя неизвестно
std::string FindNameByYear(const std::map<int, std::string>& names, int year) 
{
    auto iter_after = names.upper_bound(year);
    std::string name;
    if (iter_after != names.begin()) 
    {
        name = (--iter_after)->second;
    }
    return name;
}

class Person 
{
public:
    void ChangeFirstName(int year, const std::string& first_name)
    {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const std::string& last_name)
    {
        last_names[year] = last_name;
    }
    std::string GetFullName(int year) {
        const std::string first_name = FindNameByYear(first_names, year);
        const std::string last_name = FindNameByYear(last_names, year);
        if (first_name.empty() && last_name.empty()) 
        {
            return "Incognito";
        }
        else if (first_name.empty()) 
        {
            return last_name + " with unknown first name";
        }
        else if (last_name.empty()) 
        {
            return first_name + " with unknown last name";
        }
        else 
        {
            return first_name + " " + last_name;
        }
    }
private:
    std::map<int, std::string> first_names;
    std::map<int, std::string> last_names;
};



int main() 
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) 
    {
        std::cout << person.GetFullName(year) << std::endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) 
    {
        std::cout << person.GetFullName(year) << std::endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) 
    {
        std::cout << person.GetFullName(year) << std::endl;
    }

    return 0;
}