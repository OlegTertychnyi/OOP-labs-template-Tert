#pragma once

#include <iterator>
#include <cstddef>
#include <type_traits>

namespace Containers {

    // Шаблон итератора, параметризованный типом узла
    template <typename NodeType>
    class StackIterator {
    public:
        using value_type        = typename NodeType::value_type;
        using reference         = std::conditional_t<std::is_const_v<NodeType>, const value_type&, value_type&>;
        using pointer           = std::conditional_t<std::is_const_v<NodeType>, const value_type*, value_type*>;
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;

    private:
        NodeType* current;

    public:
        // Конструктор итератора
        explicit StackIterator(NodeType* node = nullptr) 
            : current(node) {}

        // Оператор разыменования
        reference operator*() const {
            return current->data;
        }

        // Оператор доступа к члену
        pointer operator->() const {
            return &(current->data);
        }

        // Префиксный инкремент
        StackIterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        // Постфиксный инкремент
        StackIterator operator++(int) {
            StackIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Операторы сравнения
        bool operator==(const StackIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const StackIterator& other) const {
            return !(*this == other);
        }
    };

}
