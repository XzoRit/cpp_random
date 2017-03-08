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

    std::random_device rand_dev{};
    std::mt19937 twister{rand_dev()};
    std::uniform_int_distribution<int> dist{1, 6};
};

BOOST_FIXTURE_TEST_CASE(roll_one_dice, dice_roller)
{
    std::map<int, int> rolls{};

    const int runs{1000000};
    for(int i{}; i < runs; ++i)
    {
        rolls[dist(twister)]++;
    }

    for(const auto& p : rolls)
    {
        BOOST_TEST_MESSAGE(p.first << " : " << std::string(p.second / 1000, '*'));
    }
}

BOOST_FIXTURE_TEST_CASE(test_roll_two_dices, dice_roller)
{
    std::map<int, int> rolls{};

    const int runs{1000000};
    for(int i{}; i < runs; ++i)
    {
        rolls[(dist(twister) + dist(twister))]++;
    }

    for(const auto& p : rolls)
    {
        BOOST_TEST_MESSAGE(p.first << " : " << std::string(p.second / 1000, '*'));
    }
}
