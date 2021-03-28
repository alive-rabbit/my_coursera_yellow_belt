#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s) 
{
    os << "{";
    bool first = true;
    for (const auto& x : s) 
    {
        if (!first) 
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) 
{
    os << "{";
    bool first = true;
    for (const auto& x : s) 
    {
        if (!first) 
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) 
{
    os << "{";
    bool first = true;
    for (const auto& kv : m) 
    {
        if (!first) 
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::pair<K, V>& p) 
{
    os << "{" << p.first << ": " << p.second;
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {})
{
    if (t != u) 
    {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) 
        {
            os << " hint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}

void Assert(bool b, const std::string& hint) 
{
    AssertEqual(b, true, hint);
}

class TestRunner 
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) 
    {
        try 
        {
            func();
            std::cerr << test_name << " OK" << std::endl;
        }
        catch (std::exception& e)
        {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        }
        catch (...) 
        {
            ++fail_count;
            std::cerr << "Unknown exception caught" << std::endl;
        }
    }

    ~TestRunner() 
    {
        if (fail_count > 0) 
        {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

void AssertRational(const Rational& submitted, const std::pair<int, int>& correct, const std::string& message)
{
    AssertEqual(std::pair<int, int>(submitted.Numerator(), submitted.Denominator()), correct, message);
}

const auto p = [](int numerator, int denominator) 
{
    return std::pair<int, int>(numerator, denominator);
};

void TestPredefined() 
{
    AssertRational(Rational(1, 1), p(1, 1), "Canonical form of 1/1 is 1/1");
    AssertRational(Rational(3, 5), p(3, 5), "Canonical form of 3/5 is 3/5");
    AssertRational(Rational(2147483647, 2147483647), p(1, 1), "Canonical form of 2147483647/2147483647 is 1/1");
    AssertRational(Rational(-5, 4), p(-5, 4), "Canonical form of -5/4 is -5/4");
    AssertRational(Rational(5, -4), p(-5, 4), "Canonical form of 5/-4 is -5/4");
    AssertRational(Rational(-6, -2), p(3, 1), "Canonical form of -6/-2 is 3/1");
    AssertRational(Rational(21, 56), p(3, 8), "Canonical form of 21/56 is 3/8");
    AssertRational(Rational(0, 100), p(0, 1), "Canonical form of 0/100 is 0/1");
    AssertRational(Rational(), p(0, 1), "Canonical form of default constructed is 0/1");
}

int main() 
{
    TestRunner runner;
    runner.RunTest(TestPredefined, "TestPredefined");
    return 0;
}