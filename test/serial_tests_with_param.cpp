#include "serial_container.h"

#include <gtest/gtest.h>

class SerialTestWithParam: public testing::TestWithParam<int> {

public:
    static std::size_t index;
    Serial<int> container{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
};

std::size_t SerialTestWithParam::index = 0;

TEST_P(SerialTestWithParam, Elements) {
    EXPECT_EQ(container[index], GetParam());
    index++;
}

INSTANTIATE_TEST_SUITE_P(EvenElement, SerialTestWithParam, testing::Values(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));