#include <longint/longint.h>

int main()
{
    using tolstenko_l_s::LongInt;

    LongInt l = 258;
    std::cout << l << std::endl;
    std::cout << l / -3 << std::endl << std::endl;

    std::cout << LongInt(17 * 19) / 17 << std::endl;
    std::cout << LongInt(-17 * 19) / 17 << std::endl;
    std::cout << LongInt(17 * 19) / -17 << std::endl;
    std::cout << LongInt(-17 * 19) / -17 << std::endl << std::endl;

    std::cout << LongInt(56 * 74 * 32 * 79) << std::endl;
    std::cout << LongInt(-56 * 74 * 32 * 79) << std::endl << std::endl;

    std::cout << LongInt(-56 * 74 * 32 * 79 * 19) / 19 << std::endl;
    std::cout << LongInt(56 * 74 * 32 * 79 * 19) / -19 << std::endl << std::endl;
}
