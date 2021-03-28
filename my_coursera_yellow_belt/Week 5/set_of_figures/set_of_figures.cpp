#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>

const float pi = 3.14;

class Figure 
{
public:
    Figure(const std::string& type): Type(type) {}

    virtual std::string Name() = 0;
    virtual float Perimeter() = 0;
    virtual long double Area() = 0;

    // Виртуальный деструктор.
    // При отсутствии проблем компиляции данного решения строка не является
    // необходимой и может быть опущена.
    // А вот что такое виртуальный деструктор - Вы узнаете уже на черном поясе.
    virtual ~Figure() = default;

    const std::string Type;
};

class Rect : public Figure 
{
public:
    Rect(int& w, int& h)
        : Figure("RECT"), P(2 * w + 2 * h), S(w* h) {}

    float Perimeter() override 
    {
        return P;
    }
    long double Area() override 
    {
        return S;
    }
    std::string Name() override
    {
        return Type;
    }
private:
    int P;
    double S;
};

class Circle : public Figure 
{
public:
    Circle(int& r): Figure("CIRCLE"), P(2 * pi * r), S(pi* r* r) {}

    float Perimeter() override 
    {
        return P;
    }
    long double Area() override 
    {
        return S;
    }
    std::string Name() override
    {
        return Type;
    }
private:
    float P;
    double S;
};

class Triangle : public Figure 
{
public:
    Triangle(int& a, int& b, int& c): Figure("TRIANGLE") 
    {
        P = a + b + c;
        S = sqrtl((P / 2) * (P / 2 - a) * (P / 2 - b) * (P / 2 - c));
    }

    float Perimeter() override 
    {
        return P;
    }
    long double Area() override 
    {
        return S;
    }
    std::string Name() override
    {
        return Type;
    }
private:
    float P;
    long double S;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream& is) {
    std::shared_ptr<Figure> fig;

    std::string figure_name;
    is >> figure_name;
    if (figure_name == "RECT") 
    {
        int a, b;
        is >> a >> b;
        fig = std::make_shared<Rect>(a, b);
        return fig;
    }
    if (figure_name == "TRIANGLE") 
    {
        int a, b, c;
        is >> a >> b >> c;
        fig = std::make_shared<Triangle>(a, b, c);
        return fig;
    }
    if (figure_name == "CIRCLE") 
    {
        int r;
        is >> r;
        fig = std::make_shared<Circle>(r);
        return fig;
    }
    throw std::invalid_argument("invalid figure name was specified");
}

int main() 
{
    std::vector<std::shared_ptr<Figure>> figures;
    for (std::string line; getline(std::cin, line); ) 
    {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "ADD") 
        {
            is >> std::ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT") 
        {
            for (const auto& current_figure : figures) 
            {
                std::cout << std::fixed << std::setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << std::endl;
            }
        }
    }
    return 0;
}