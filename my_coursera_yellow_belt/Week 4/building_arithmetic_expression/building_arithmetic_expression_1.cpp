#include <iostream>
#include <vector>
#include <string>
#include <deque>

struct Operation 
{
    char type = 0;
    int number = 0;
};

int main() 
{
    int initial_number;
    std::cin >> initial_number;

    int number_of_operations;
    std::cin >> number_of_operations;
    std::vector<Operation> operations(number_of_operations);  // (*)
    for (int i = 0; i < number_of_operations; ++i) 
    {
        std::cin >> operations[i].type;
        std::cin >> operations[i].number;
    }

    std::deque<std::string> expression;
    expression.push_back(std::to_string(initial_number));
    for (const auto& operation : operations) 
    {
        expression.push_front("(");
        expression.push_back(") ");
        expression.push_back(std::string(1, operation.type));
        expression.push_back(" ");
        expression.push_back(std::to_string(operation.number));
    }

    for (const std::string& s : expression)
    {
        std::cout << s;
    }

    return 0;
}