#pragma once

#include <memory>
#include <functional>
#include <vector>
#include "iterator.h"

namespace Containers {

    template <class T, class Allocator = std::pmr::polymorphic_allocator<T>>
    class Stack {
    public:
        // Определение структуры Node внутри Stack
        struct Node {
            using value_type = T; // Для доступа итератору

            T data;
            Node* next;

            Node(const T& value) : data(value), next(nullptr) {}
            Node(T&& value) : data(std::move(value)), next(nullptr) {}
        };

        using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
        using NodeAllocatorTraits = std::allocator_traits<NodeAllocator>;

        // Определение типов итераторов с использованием StackIterator
        using iterator = StackIterator<Node>;
        using const_iterator = StackIterator<const Node>;

    private:
        Node* top_ptr;
        std::size_t stack_size;
        NodeAllocator allocator;

    public:
        // Конструктор
        explicit Stack(const Allocator& alloc = Allocator()) 
            : top_ptr(nullptr), stack_size(0), allocator(alloc) {}

        // Конструктор копирования
        Stack(const Stack& other) 
            : top_ptr(nullptr), stack_size(0), allocator(NodeAllocatorTraits::select_on_container_copy_construction(other.allocator)) {
            // Собираем элементы в вектор для сохранения порядка
            std::vector<T> elems;
            Node* current = other.top_ptr;
            while(current) {
                elems.push_back(current->data);
                current = current->next;
            }
            // Добавляем элементы в обратном порядке
            for(auto it = elems.rbegin(); it != elems.rend(); ++it) {
                push(*it);
            }
        }

        // Перемещающий конструктор
        Stack(Stack&& other) noexcept 
            : top_ptr(other.top_ptr), stack_size(other.stack_size), allocator(std::move(other.allocator)) {
            other.top_ptr = nullptr;
            other.stack_size = 0;
        }

        // Оператор копирования
        Stack& operator=(const Stack& other) {
            if (this != &other) {
                clear();
                if constexpr (NodeAllocatorTraits::propagate_on_container_copy_assignment::value) {
                    allocator = other.allocator;
                }
                // Собираем элементы в вектор для сохранения порядка
                std::vector<T> elems;
                Node* current = other.top_ptr;
                while(current) {
                    elems.push_back(current->data);
                    current = current->next;
                }
                // Добавляем элементы в обратном порядке
                for(auto it = elems.rbegin(); it != elems.rend(); ++it) {
                    push(*it);
                }
            }
            return *this;
        }

        // Перемещающий оператор присваивания
        Stack& operator=(Stack&& other) noexcept {
            if (this != &other) {
                clear();
                if (NodeAllocatorTraits::propagate_on_container_move_assignment::value) {
                    allocator = std::move(other.allocator);
                }
                top_ptr = other.top_ptr;
                stack_size = other.stack_size;
                other.top_ptr = nullptr;
                other.stack_size = 0;
            }
            return *this;
        }

        // Деструктор
        ~Stack() {
            clear();
        }

        // Метод push для lvalue
        void push(const T& item) {
            Node* new_node = NodeAllocatorTraits::allocate(allocator, 1);
            try {
                NodeAllocatorTraits::construct(allocator, new_node, item);
            } catch (...) {
                NodeAllocatorTraits::deallocate(allocator, new_node, 1);
                throw;
            }

            new_node->next = top_ptr;
            top_ptr = new_node;
            ++stack_size;
        }

        // Метод push для rvalue
        void push(T&& item) {
            Node* new_node = NodeAllocatorTraits::allocate(allocator, 1);
            try {
                NodeAllocatorTraits::construct(allocator, new_node, std::move(item));
            } catch (...) {
                NodeAllocatorTraits::deallocate(allocator, new_node, 1);
                throw;
            }

            new_node->next = top_ptr;
            top_ptr = new_node;
            ++stack_size;
        }

        // Метод pop
        void pop() {
            if (empty()) {
                throw std::out_of_range("Pop from empty stack.");
            }
            Node* old_top = top_ptr;
            top_ptr = top_ptr->next;
            NodeAllocatorTraits::destroy(allocator, old_top);
            NodeAllocatorTraits::deallocate(allocator, old_top, 1);
            --stack_size;
        }

        // Метод top (не const)
        T& top() {
            if (empty()) {
                throw std::out_of_range("Accessing top of empty stack.");
            }
            return top_ptr->data;
        }

        // Метод top (const)
        const T& top() const {
            if (empty()) {
                throw std::out_of_range("Accessing top of empty stack.");
            }
            return top_ptr->data;
        }

        // Метод empty
        bool empty() const {
            return stack_size == 0;
        }

        // Метод size
        std::size_t size() const {
            return stack_size;
        }

        // Метод clear
        void clear() {
            while (!empty()) {
                pop();
            }
        }

        // Методы для итераторов
        iterator begin() { return iterator(top_ptr); }
        iterator end() { return iterator(nullptr); }

        const_iterator begin() const { return const_iterator(top_ptr); }
        const_iterator end() const { return const_iterator(nullptr); }

        // Доступ к элементам по индексу (используется итератором, но теперь можно убрать, если не нужен)
        T& at(std::size_t idx) {
            if (idx >= stack_size) {
                throw std::out_of_range("Index out of range.");
            }
            Node* current = top_ptr;
            for (std::size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            return current->data;
        }

        const T& at(std::size_t idx) const {
            if (idx >= stack_size) {
                throw std::out_of_range("Index out of range.");
            }
            Node* current = top_ptr;
            for (std::size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            return current->data;
        }
    };

}
