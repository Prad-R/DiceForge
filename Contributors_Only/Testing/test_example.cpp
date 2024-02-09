#include "../Source/Generators/xorshift.h"
#include <iostream>

int main() {
    std::cout << "Helo?" << std::endl;

    DiceForge::XORShift32 rng = DiceForge::XORShift32(1234);

    std::cout << "\n\nRandom integers" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        std::cout << rng.next() << ", ";
    }

    std::cout << "\n\nRandom reals between 0 to 1" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        std::cout << rng.next_unit() << ", ";
    }

    std::cout << "\n\nRandom integers between 5 to 50" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        std::cout << rng.next_in_range(5, 50) << ", ";
    }

    std::cout << "\n\nRandom reals between 5 to 50" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        std::cout << rng.next_in_crange(5, 50) << ", ";
    }

    std::cout << std::endl;

    return 0;
}