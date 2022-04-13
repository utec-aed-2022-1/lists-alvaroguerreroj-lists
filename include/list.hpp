#pragma once

#include <string>

#include "node.hpp"

template<typename T>
class List
{
public:
    using size_type = size_t;

public:
    List() {};
    virtual ~List() {};

    // Contrato
    virtual T front() = 0;
    virtual T back() = 0;
    virtual void push_front(T) = 0;
    virtual void push_back(T) = 0;
    virtual T pop_front() = 0;
    virtual T pop_back() = 0;
    virtual void insert(T, size_type) = 0;
    virtual void remove(size_type) = 0;
    virtual T& operator[](size_type) = 0; // debe ser declarado en cada clase hija
    virtual bool is_empty() = 0;
    virtual size_type size() = 0;
    virtual void clear() = 0;
    virtual void sort() = 0;
    virtual bool is_sorted() = 0;
    virtual void reverse() = 0;
    virtual std::string name() = 0;
};
