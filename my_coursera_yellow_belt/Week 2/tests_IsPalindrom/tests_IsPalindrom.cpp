#include <iostream>
#include <map>
#include <ostream>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& s)
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
std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
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
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m)
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

template <class T, class U>
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

void Assert(bool b, const std::string& hint) { AssertEqual(b, true, hint); }

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
void TestIsPalindrom() 
{
    Assert(IsPalindrom(""), "empty string is a palindrome");
    Assert(IsPalindrom("a"), "one letter string is a palindrome");
    Assert(IsPalindrom("abba"), "abba is a palindrome");
    Assert(IsPalindrom("abXba"), "abXba is a palindrome");
    Assert(IsPalindrom("a b X b a"), "`a b X b a` is a palindrome");
    Assert(IsPalindrom("  ABBA  "), "`  ABBA  ` is a palindrome");

    Assert(!IsPalindrom("XabbaY"), "XabbaY is not a palindrome");
    Assert(!IsPalindrom("abXYba"), "abXYba is not a palindrome");
    Assert(!IsPalindrom("Xabba"), "Xabba is not a palindrome");
    Assert(!IsPalindrom("abbaX"), "abbaX is not a palindrome");
    Assert(
        !IsPalindrom("was it a car or a cat i saw"),
        "`was it a car or a cat i saw` is not a palindrome because spaces do not match"
    );
    Assert(!IsPalindrom("ABBA   "), "`ABBA   ` is not a palindrome");
    Assert(!IsPalindrom("  ABBA"), "`  ABBA` is not a palindrome");
}

int main() 
{
    TestRunner runner;
    runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
    return 0;
}
