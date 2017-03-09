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

const auto roll_one_dice = []()
{
    static std::random_device rand_dev{};
    static std::mt19937 twister{rand_dev()};
    static std::uniform_int_distribution<int> dist{1, 6};

    return dist(twister);
};

using roll_results = std::map<int, int>;

const auto runs{200000};
const auto scale{runs / 1000};

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
    BOOST_TEST_MESSAGE(
        std::accumulate(
            std::begin(rolls), std::end(rolls), std::string{},
            [](const auto& a, const auto& b)
            {
                return a
                    + std::to_string(b.first)
                    + std::string(b.second / scale, '*')
                    + '\n';
            })
        );
}

BOOST_FIXTURE_TEST_CASE(roll_the_dices, dice_roller)
{
    for(int i{1}; i <= 10; ++i) print_roll_results(roll(i));
}
