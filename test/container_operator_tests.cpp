#include "serial_container.h"
#include "list.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

template <class ContainerClass, typename T>
class MockContainer : public ContainerClass {

public:
    MockContainer() : ContainerClass() {};
    MockContainer(std::initializer_list <T> l) : ContainerClass(l) {};
    MOCK_METHOD1(
        assign_operator,
        ContainerClass&(const ContainerClass& rhs)
    );
    virtual ContainerClass& operator=(const ContainerClass& rhs) override { 
        return assign_operator(rhs); 
    };

    MOCK_METHOD1(
        move_operator,
        ContainerClass&(ContainerClass&& rhs)
    );
    virtual ContainerClass& operator=(ContainerClass&& rhs) override { 
        return move_operator(std::move(rhs)); 
    };

    ContainerClass* getParent() { return dynamic_cast<ContainerClass*>(this); };
};

template <typename T>
class MockFixture: public testing::Test {

public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override {};
    void TearDown() override {};

    T mock_container;
};

using MockContainerTypes = ::testing::Types<MockContainer<List<int>, int>, MockContainer<Serial<int>, int>>;

TYPED_TEST_SUITE(MockFixture, MockContainerTypes);


TYPED_TEST(MockFixture, Container_move_operator) {
    TypeParam mock_c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_CALL(this->mock_container, move_operator(testing::_))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::ReturnRef(*this->mock_container.getParent()));
    *this->mock_container.getParent() = std::move(*mock_c.getParent());
}

TYPED_TEST(MockFixture, Container_assign_operator) {
    TypeParam mock_c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_CALL(this->mock_container, assign_operator(testing::_))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::ReturnRef(*this->mock_container.getParent()));
    *this->mock_container.getParent() = *mock_c.getParent();
}