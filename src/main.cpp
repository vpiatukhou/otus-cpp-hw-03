#include <iostream>
#include <string>
#include <map>

#include "MyAllocator.h"
#include "FixedPoolStrategy.h"
#include "DynamicPoolStrategy.h"
#include "LinkedList.h"

namespace Homework {

    const int NUMBER_OF_ELEMENTS = 10;

    int factorial(int number) {
        if (number == 0) {
            return 1;
        }
        int result = 1;
        for (int i = 1; i <= number; ++i) {
            result *= i;
        }
        return result;
    }

    template<class Map> 
    void printMap(Map map) {
        for (int i = 0; i < NUMBER_OF_ELEMENTS; ++i) {
            std::cout << i << ' ' << map[i] << std::endl;
        }
    }
}

int main() {
    std::cout << "A map with a default allocator.\n" << std::endl;
    {
        std::map<int, int> map;
        for (int i = 0; i < Homework::NUMBER_OF_ELEMENTS; ++i) {
            map[i] = Homework::factorial(i);
        }
        Homework::printMap(map);
    }
    std::cout << "\nA map with a custom allocator (with a fixed number of elements).\n" << std::endl;
    {
        using Allocator = Homework::MyAllocator<std::pair<const int, int>, Homework::NUMBER_OF_ELEMENTS, Homework::FixedPoolStrategy>;

        std::map<int, int, std::less<int>, Allocator> map;
        
        for (int i = 0; i < Homework::NUMBER_OF_ELEMENTS; ++i) {
            map[i] = Homework::factorial(i);
        }

        Homework::printMap(map);
     }
    std::cout << "\nA map with a custom allocator (with a variable number of elements).\n" << std::endl;
    {
        using Allocator = Homework::MyAllocator<std::pair<const int, int>, Homework::NUMBER_OF_ELEMENTS, Homework::DynamicPoolStrategy>;
        
        std::map<int, int, std::less<int>, Allocator> map;
        
        for (int i = 0; i < Homework::NUMBER_OF_ELEMENTS; ++i) {
            map[i] = Homework::factorial(i);
        }

        Homework::printMap(map);
    }
    std::cout << "\nA custom linked list with a custom allocator.\n" << std::endl;
    {
        using Allocator = Homework::MyAllocator<int, Homework::NUMBER_OF_ELEMENTS, Homework::FixedPoolStrategy>;
        Homework::LinkedList<int, Allocator> list;
        for (int i = 0; i < Homework::NUMBER_OF_ELEMENTS; ++i) {
            list.add(Homework::factorial(i));
        }

        //print all values
        for (auto value : list) {
            std::cout << value << std::endl;
        }
    }
    return 0;
}