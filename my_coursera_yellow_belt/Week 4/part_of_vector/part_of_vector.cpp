#include <algorithm>
#include <iostream>
#include <vector>

void PrintVectorPart(const std::vector<int>& numbers)
{
	auto negative_it = std::find_if(numbers.begin(), numbers.end(),
		[](int number) { return number < 0; });

	for (auto it = negative_it; it != numbers.begin(); )
	{
		std::cout << *(--it) << " ";
	}
}
int main()
{
	PrintVectorPart({ 6, 1, 8, -5, 4 });
	std::cout << std::endl;
	PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
	std::cout << std::endl;
	PrintVectorPart({ 6, 1, 8, 5, 4 });
	std::cout << std::endl;
	return 0;
}