#include <cstdint>
#include <iostream>

int main()
{
    int N, R;
    std::cin >> N >> R;
    uint64_t answer = 0;
    for (int i = 0; i < N; ++i)
    {
        int W, H, D;
        std::cin >> W >> H >> D;

        answer += static_cast<uint64_t>(W) * H * D;
    }
    answer *= R;
    std::cout << answer << std::endl;
    return 0;
}