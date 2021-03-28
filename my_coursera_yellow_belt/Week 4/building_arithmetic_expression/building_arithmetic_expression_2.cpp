#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>
#include <string>

struct Operation 
{
    char type = 0;
    int number = 0;
};

bool NeedBrackets(char last, char current) 
{
    return (last == '+' || last == '-') && (current == '*' || current == '/');
}

int main() 
{
    int initial_number;
    std::cin >> initial_number;

    int number_of_operations;
    std::cin >> number_of_operations;
    std::vector<Operation> operations(number_of_operations);
    for (int i = 0; i < number_of_operations; ++i) 
    {
        std::cin >> operations[i].type;
        std::cin >> operations[i].number;
    }

    std::deque<std::string> expression;
    expression.push_back(std::to_string(initial_number));
    char last_type = '*';
    for (const auto& operation : operations) 
    {
        if (NeedBrackets(last_type, operation.type)) 
        {
            expression.push_front("(");
            expression.push_back(")");
        }
        expression.push_back(" ");
        expression.push_back(std::string(1, operation.type));
        expression.push_back(" ");
        expression.push_back(std::to_string(operation.number));

        last_type = operation.type;
    }

    for (const std::string& s : expression) 
    {
        std::cout << s;
    }

    return 0;
}
