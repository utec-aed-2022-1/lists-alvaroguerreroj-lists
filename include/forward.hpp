#pragma once

#include <iostream>

#include "list.hpp"

// TODO: Implement all methods
template<typename T>
class ForwardList : public List<T>
{
public:
    using typename List<T>::size_type;

private:
    using node_p = Node<T>*;

private:
    node_p m_head;
    size_type m_size;

public:
    ForwardList()
        : m_head(nullptr),
          m_size(0)
    {
    }

    ~ForwardList()
    {
        // TODO
    }

    T front()
    {
        throw("sin definir");
    }

    T back()
    {
        throw("sin definir");
    }

    void push_front(T data)
    {
        node_p new_head = new Node<T>(data, m_head);
        m_head = new_head;

        m_size++;
    }

    void push_back(T data)
    {
        throw("sin definir");
    }

    T pop_front()
    {
        throw("sin definir");
    }

    T pop_back()
    {
        throw("sin definir");
    }

    T insert(T data, size_type pos)
    {
        throw("sin definir");
    }

    bool remove(size_type pos)
    {
        throw("sin definir");
    }

    T& operator[](size_type pos)
    {
        throw("sin definir");
    }

    bool is_empty()
    {
        throw("sin definir");
    }

    size_type size()
    {
        throw("sin definir");
    }

    void clear()
    {
        throw("sin definir");
    }

    void sort()
    {
        throw("sin definir");
    }

    bool is_sorted()
    {
        throw("sin definir");
    }

    void reverse()
    {
        throw("sin definir");
    }

    std::string name()
    {
        return "ForwardList";
    }
};
