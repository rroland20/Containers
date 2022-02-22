#pragma once

#include <iostream>
#include <stack>
#include <vector>

namespace ft {

    class stack {
    private:
    public:
        stack();
        stack(const stack& copy);
        stack	&operator=(const stack& other);
        virtual ~stack();
    };
}

