#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>


template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, std::string prefix) 
{

	auto left = lower_bound(range_begin, range_end, prefix);

	std::string upper_bound = prefix;
	++upper_bound[upper_bound.size() - 1];

	auto right = lower_bound(range_begin, range_end, upper_bound);

	return { left, right };
}

int main() 
{
	const std::vector<std::string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

	const auto mo_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it) 
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	const auto mt_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	std::cout << (mt_result.first - begin(sorted_strings)) << " " <<
		(mt_result.second - begin(sorted_strings)) << std::endl;

	const auto na_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	std::cout << (na_result.first - begin(sorted_strings)) << " " <<
		(na_result.second - begin(sorted_strings)) << std::endl;

	return 0;
}