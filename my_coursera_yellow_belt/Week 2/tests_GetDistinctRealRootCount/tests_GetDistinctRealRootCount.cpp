#include <iostream>
#include <map>
#include <ostream>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

int GetDistinctRealRootCount(double a, double b, double c);

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

void TestRootCount() 
{
	std::mt19937 gen;
	std::uniform_real_distribution<> unif(-10, 10);

	for (auto i = 0; i < 100; ++i) 
	{
		const auto a = unif(gen);
		const auto b = unif(gen);
		const auto c = unif(gen);

		const auto count = GetDistinctRealRootCount(a, b, c);

		Assert(count >= 0 && count <= 2,
			"Quadratic equation has only 0, 1 or 2 real roots.");
	}
}

void TestOneRoot() 
{
	std::mt19937 gen;
	std::uniform_real_distribution<> unif(-10, 10);

	for (auto i = 0; i < 100; ++i) 
	{
		const auto x_1 = unif(gen);

		const auto p = x_1 + x_1;
		const auto q = x_1 * x_1;

		const auto count = GetDistinctRealRootCount(1, p, q);
		std::stringstream description;
		description << std::showpos << "x^2" << p << "x" << q
			<< " = 0 has 1 real root.";

		AssertEqual(count, 1, description.str());
	}
}

void TestNoRoots() 
{
	AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0,
		"x^2+1 = 0 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(1, 3, 4), 0,
		"x^2+3x+4 = 0 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(1, -2, 10), 0,
		"x^2-2x+10 = 0 has 0 real roots.");
}

void TestLinearEquation() 
{
	AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1,
		"2x+1 = 0 has 1 real root.");
	AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1,
		"-x = 0 has 1 real root.");
	AssertEqual(GetDistinctRealRootCount(0, 120, -10), 1,
		"120x - 10 = 0 has 1 real root.");
}

void TestConstant() 
{
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0,
		"c = 0, where c = 1 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0,
		"c = 0, where c = -10 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0,
		"c = 0, where c = 189238910 has 0 real roots.");
}

int main() 
{
	TestRunner runner;
	runner.RunTest(TestRootCount, "TestRootCount");
	runner.RunTest(TestOneRoot, "TestOneRoot");
	runner.RunTest(TestNoRoots, "TestNoRoots");
	runner.RunTest(TestLinearEquation, "TestLinearEquation");
	runner.RunTest(TestConstant, "TestConstant");
	return 0;
}
