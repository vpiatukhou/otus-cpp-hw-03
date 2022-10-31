#include "LinkedList.h"
#include <gtest/gtest.h>

namespace HomeworkTest {
    struct Foo {
        int value;

        Foo(int _value) : value(_value) { };
    };
};

TEST(MyLinkedListTest, addPrimitiveType) {
    //given
    std::size_t listSize = 3;

    Homework::LinkedList<int> list;
    
    //when
    for (std::size_t i = 0; i < listSize; ++i) {
        list.add(i);
    }

    //then
    int i = 0;
    for (int element : list) {
        ASSERT_EQ(i, element);
        ++i;
    }
    ASSERT_EQ(i, listSize);
}

TEST(MyLinkedListTest, addObjectType) {
    //given
    std::size_t listSize = 3;

    Homework::LinkedList<HomeworkTest::Foo> list;
    
    //when
    for (std::size_t i = 0; i < listSize; ++i) {
        list.add(HomeworkTest::Foo(i));
    }

    //then
    int i = 0;
    for (HomeworkTest::Foo element : list) {
        ASSERT_EQ(i, element.value);
        ++i;
    }
    ASSERT_EQ(i, listSize);
}