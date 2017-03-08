#define BOOST_TEST_MODULE random_test
#include <boost/test/unit_test.hpp>
#include <random>
#include <map>
#include <iomanip>
#include <numeric>
#include <algorithm>

namespace utf = boost::unit_test;

class dice_roller
{
public:
    dice_roller()
    {}

    ~dice_roller()
    {}
};

std::random_device rand_dev{};
std::mt19937 twister{rand_dev()};
std::uniform_int_distribution<int> dist{1, 6};

using roll_results = std::map<int, int>;
const auto runs{100000};
const auto scale{100};

const auto roll_one_dice = []()
{
    return dist(twister);
};

const auto roll = [](int num_of_dices)
{
    roll_results rolls{};

    for(int i{}; i < runs; ++i)
    {
        std::vector<int> dice_rolls(num_of_dices);
        std::generate(std::begin(dice_rolls), std::end(dice_rolls), roll_one_dice);

        const auto sum_of_rolls =
            std::accumulate(std::begin(dice_rolls), std::end(dice_rolls), 0);

        rolls[sum_of_rolls]++;
    }

    return rolls;
};

void print_roll_results(const roll_results& rolls)
{
    for(const auto& p : rolls)
    {
        BOOST_TEST_MESSAGE(std::setw(2)
            << p.first
            << " : "
            << std::string(p.second / scale, '*'));
    }
    BOOST_TEST_MESSAGE('\n');
}

BOOST_FIXTURE_TEST_CASE(roll_the_dices, dice_roller)
{
    for(int i{1}; i <= 10; ++i) print_roll_results(roll(i));
}
