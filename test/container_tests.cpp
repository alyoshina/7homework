#include "serial_container.h"
#include "list.h"

#include <gtest/gtest.h>

template <typename T>
class ContainerFixture: public testing::Test {

public:
    static void SetUpTestSuite() {
    };
    static void TearDownTestSuite() {
    };
    void SetUp() override {
        for (std::size_t i = 0; i < elementsCount; ++i) {
            container.push_back(i);
        }
    };
    void TearDown() override {
    };

    std::size_t elementsCount = 10;
    T container;
};

using ContainerTypes = ::testing::Types<Serial<int>, List<int>>;
TYPED_TEST_SUITE(ContainerFixture, ContainerTypes);

TYPED_TEST(ContainerFixture, Container_create) {
    EXPECT_EQ(this->container.size(), this->elementsCount);

    for (std::size_t i = 0; i < this->elementsCount; ++i) {
        EXPECT_TRUE(this->container[i] == i);
    }
}

TYPED_TEST(ContainerFixture, Container_push_back) {
    int insertValue = 30;
    this->container.push_back(insertValue);
    EXPECT_EQ(this->container.size(), this->elementsCount + 1);
    EXPECT_EQ(this->container[this->elementsCount], insertValue);
}

TYPED_TEST(ContainerFixture, Container_push_front) {
    int insertValue = 10;
    this->container.push_front(insertValue);
    EXPECT_EQ(this->container.size(), this->elementsCount + 1);
    EXPECT_EQ(this->container[0], insertValue);
}

TYPED_TEST(ContainerFixture, Container_insert_to_middle) {
    int insertValue = 20;
    this->container.insert(this->elementsCount/2, 20);
    EXPECT_EQ(this->container.size(), this->elementsCount + 1);
    EXPECT_EQ(this->container[this->elementsCount/2], insertValue);
}

TYPED_TEST(ContainerFixture, Container_delete_last) {
    int value = this->container[this->elementsCount - 2];
    this->container.erase(this->elementsCount - 1);
    EXPECT_EQ(this->container.size(), this->elementsCount - 1);
    EXPECT_EQ(this->container[this->container.size() - 1], value);
}

TYPED_TEST(ContainerFixture, Container_delete_first) {
    int value = this->container[1];
    this->container.erase(0);
    EXPECT_EQ(this->container.size(), this->elementsCount - 1);
    EXPECT_EQ(this->container[0], value);
}

TYPED_TEST(ContainerFixture, Container_delete_middle) {
    int value = this->container[this->elementsCount/2 + 1];
    this->container.erase(this->elementsCount/2);
    EXPECT_EQ(this->container.size(), this->elementsCount - 1);
    EXPECT_EQ(this->container[this->elementsCount/2], value);
}

TYPED_TEST(ContainerFixture, Container_get_size) {
    EXPECT_EQ(this->container.size(), this->elementsCount);
}

TYPED_TEST(ContainerFixture, Container_copy) {
    TypeParam container_copy;
    container_copy = this->container;
    for (std::size_t i = 0; i < this->elementsCount; ++i) {
        EXPECT_EQ(this->container[i], container_copy[i]);
    }
}