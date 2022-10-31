#include "LinkedList.h"
#include "MyAllocator.h"
#include "FixedPoolStrategy.h"
#include <gtest/gtest.h>

namespace HomeworkTest {
    struct Foo {
        int value;

        Foo(int _value) : value(_value) { };
    };
};

TEST(IntegrationTests, linkedListWithFixedPoolAllocator) {
    //given
    const std::size_t poolSize = 10;

    Homework::LinkedList<HomeworkTest::Foo, Homework::MyAllocator<HomeworkTest::Foo, poolSize, Homework::FixedPoolStrategy>> list;
    
    //when
    for (std::size_t i = 0; i < poolSize; ++i) {
        list.add(HomeworkTest::Foo(i));
    }

    //then
    int i = 0;
    for (HomeworkTest::Foo element : list) {
        ASSERT_EQ(i, element.value);
        ++i;
    }
    ASSERT_EQ(i, poolSize);
}