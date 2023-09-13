#include "serial_container.h"
#include "list.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//class MockElement is container element
template <typename T>
class MockElement {

public:
    MockElement() : data{0} {};
    MockElement(T d) : data{d} {};
    MockElement(const MockElement& other) {
        data = other.data;
    };
    virtual ~MockElement() {
        //std::cout << "DELETE" << this << std::endl;
        delete_element(); 
    };
    MOCK_METHOD(
        void,
        delete_element,
        ()
    );
    MockElement& operator=(const MockElement& rhs) {
        data = rhs.data;
        return *this;
    };

    T data;
};

// class Nice suppresses uninteresting call warnings:
// GMOCK WARNING: Uninteresting mock function call - returning directly. Function call: delete_element() ...
using ::testing::NiceMock;
template <typename T>
class Nice : public NiceMock<T> {
public:
    Nice() : NiceMock<T>() {};
    Nice(const Nice& other) = delete;

    template <typename A>
    explicit Nice(A&& arg) : NiceMock<T>(std::forward<A>(arg)) {};

    template <typename TArg1, typename TArg2, typename... An>
    Nice(TArg1&& arg1, TArg2&& arg2, An&&... args) : NiceMock<T>(std::forward<TArg1>(arg1), std::forward<TArg2>(arg2), std::forward<An>(args)...) {};

    Nice& operator=(const Nice& rhs) = delete;
};

template <>
Nice<MockElement<int>>::Nice(const Nice& other) {
    data = other.data;
};
template <>
Nice<MockElement<int>>& Nice<MockElement<int>>::operator=(const Nice<MockElement<int>>& rhs) {
    data = rhs.data;
    return *this;
};



template <typename T>
class MockContainerFixture: public testing::Test {

public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override {
        container = new T;
        for (std::size_t i = 0; i < elementsCount; ++i) {
            container->push_back(Nice<MockElement<int>>(i));
        }
    };
    void TearDown() override {
        deleteContainer();
    };

    void deleteContainer() {
        delete container;
        container = nullptr;
    };

    std::size_t elementsCount{3};
    T *container{nullptr};
    std::size_t count{0};
};

using MockContainerTypesWithMockEl = ::testing::Types<List<Nice<MockElement<int>>>, Serial<Nice<MockElement<int>>>>;
TYPED_TEST_SUITE(MockContainerFixture, MockContainerTypesWithMockEl);

TYPED_TEST(MockContainerFixture, Container_all_elements_delete) {
    for (std::size_t i = 0; i < this->elementsCount; ++i) {
        Nice<MockElement<int>>& element = (*this->container)[i];
        EXPECT_CALL(element, delete_element()).Times(1);
    }
    this->deleteContainer();
}

TYPED_TEST(MockContainerFixture, Container_all_elements_delete_count) {
    for (std::size_t i = 0; i < this->elementsCount; ++i) {
        Nice<MockElement<int>>& element = (*this->container)[i];
        ON_CALL(element, delete_element()).WillByDefault([this](){ this->count++; });
    }
    this->deleteContainer();
    EXPECT_EQ(this->count, this->elementsCount);
}