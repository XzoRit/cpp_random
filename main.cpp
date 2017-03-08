#define BOOST_TEST_MODULE random_test
#include <boost/test/unit_test.hpp>
#include <random>
#include <map>

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

roll_results roll(int num_of_dices)
{
    const int runs{1000000};
    roll_results rolls{};

    for(int i{}; i < runs; ++i)
    {
        int sum{};
        for(int j{}; j < num_of_dices; ++j)
        {
            sum += dist(twister);
        }

        rolls[sum]++;
    }

    return rolls;
}

void print_roll_results(const roll_results& rolls)
{
    for(const auto& p : rolls)
    {
        BOOST_TEST_MESSAGE(p.first << " : " << std::string(p.second / 1000, '*'));
    }
    BOOST_TEST_MESSAGE('\n');
}

BOOST_FIXTURE_TEST_CASE(roll_one_dice, dice_roller)
{
    print_roll_results(roll(1));
    print_roll_results(roll(2));
    print_roll_results(roll(3));
    print_roll_results(roll(4));
    print_roll_results(roll(5));
}
