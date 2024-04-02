#include "../src/Core/2D.h"
#include <iomanip>
template <typename Type>
void test_double_integral_one()
{
    auto f = [](auto x, auto y)
    {
        return std::sin(x) * std::cos(y * y);
    };

    auto pi = std::asin(1) * 2;

    auto bound_x = std::tuple<Type, Type>{0.0, pi / 2};
    auto bound_y = std::tuple<Type, Type>{0.0, pi / 2};

    auto int_x_y = DiceForge::integral(f, bound_x, bound_y, DiceForge::dy_dx);
    auto int_y_x = DiceForge::integral(f, bound_y, bound_x, DiceForge::dx_dy);

    std::cout << std::setprecision(17) << "int_x_y = " << int_x_y << std::endl;
    std::cout << std::setprecision(17) << "int_y_x = " << int_y_x << std::endl;
}

template <typename Type>
void test_double_integral_2()
{
    auto z = [](auto x, auto y)
    {
        return 16 - x * x - y * y;
    };

    auto bound_y = std::make_tuple(Type{0}, Type{2});

    auto lower = [](auto y)
    { return y * y / 4; };
    auto upper = [](auto y)
    { return (y + 2) / 4; };

    auto bound_x = std::make_tuple(lower, upper);

    auto calculated_answer = DiceForge::integral(z, bound_y, bound_x, DiceForge::dx_dy);

    auto actual_answer = 20803.0 / 1680.0;

    std::cout << std::setprecision(17) << "calculated_answer = " << calculated_answer << std::endl;
    std::cout << std::setprecision(17) << "actual_answer = " << actual_answer << std::endl;
}

int main()
{
    std::cout<<"for test case one :"<<std::endl;
    test_double_integral_one<double>();
    std::cout<<"for test case two :"<<std::endl;
    test_double_integral_2<double>();
}