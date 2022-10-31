#pragma once
#include <cstddef>
#include <iterator>
#include <memory>

namespace Homework {

/// @brief An unidirectional linked list.
/// @tparam T           - a type of elements
/// @tparam Allocator   - an allocator to allocate memory for elements
template<typename T, class Allocator = std::allocator<T>>
class LinkedList {
private:
    struct Node {
		Node* next = nullptr;
		T* value;
	};

	using NodeAllocator = typename Allocator::template rebind<Node>::other;

    Node* head = nullptr;
	Node* tail = nullptr;
	Node* endNode = nullptr; //an empty node which is placed AFTER the tail node. Used by foreach loop.

	Allocator allocator;
	NodeAllocator nodeAllocator;
public:
	struct ForwardIterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		Node* node;

		ForwardIterator(Node* _node) : node(_node) { }

		pointer operator->() {
			return node->value;
		}

		reference operator*() const {
			return *(node->value);
		}

		ForwardIterator& operator++() {
			node = node->next;
			return *this;
		}

		ForwardIterator operator++(int) {
			ForwardIterator iterator = *this;
			++(*this);
			return iterator;
		}

		friend bool operator==(const ForwardIterator& a, const ForwardIterator& b) {
			return a.node == b.node;
		}

		friend bool operator!=(const ForwardIterator& a, const ForwardIterator& b) {
			return a.node != b.node;
		}
	};

	LinkedList() {
        //the list is empty, so its head and tail point to "the node after the tail"
		endNode = new Node();
		head = endNode;
		tail = endNode;
	}

	~LinkedList() {
		Node* current = head;
		while (current != nullptr) {
			Node* toDelete = current;
			current = current->next;

            //destroy the stored value
			allocator.destroy(toDelete->value);
			allocator.deallocate(toDelete->value, 1);

            //destroy the node
			nodeAllocator.destroy(toDelete);
			nodeAllocator.deallocate(toDelete, 1);
		}
	}

	void add(const T& value) {
        //allocate memory for a copy of the given value
		T* newValuePtr = allocator.allocate(1);
        //construct a copy of the value
		allocator.construct(newValuePtr, value);

        //create a node to store the value
		Node* node = nodeAllocator.allocate(1);
		nodeAllocator.construct(node);

		node->value = newValuePtr;
        
		if (head == endNode) { //if the list is empty, so set up the head
			head = node;
			tail = node;
		} else { //if the list is not empty, append the node to the tail
			tail->next = node;
			tail = node;
		}
        //the tail always points to "the node after the tail"
		tail->next = endNode;
	}

	ForwardIterator begin() const {
		return ForwardIterator(head);
	}

	ForwardIterator end() const {
		return ForwardIterator(endNode);
	}
};

};