#include "list.h"

#include <gtest/gtest.h>

class ListTestWithParam: public testing::TestWithParam<int> {

public:
    static std::size_t index;
    List<int> container{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
};

std::size_t ListTestWithParam::index = 0;

TEST_P(ListTestWithParam, Elements) {
    EXPECT_EQ(container[index], GetParam());
    index++;
}

INSTANTIATE_TEST_SUITE_P(EvenElement, ListTestWithParam, testing::Values(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));