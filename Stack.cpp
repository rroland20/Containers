#include "Stack.hpp"

ft::stack::stack() {}

ft::stack::stack(const stack& copy) { *this = copy; }

ft::stack    &ft::stack::operator=(const stack& other) {
    if (this != &other) {
    }
    return (*this);
}

ft::stack::~stack() {}

