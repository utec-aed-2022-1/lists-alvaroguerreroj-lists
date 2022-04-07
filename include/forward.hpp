#pragma once

#include <deque>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

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

    ForwardList(std::initializer_list<T> il)
        : ForwardList<T>()
    {
        m_size = il.size();

        for (auto it = std::rbegin(il); it != std::rend(il); it++)
        {
            this->push_front(*it);
        }
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

    std::string to_string()
    {
        std::ostringstream oss;

        oss << "{ ";

        node_p it = m_head;
        while (it != nullptr)
        {
            oss << it->data << " ";
            it = it->next;
        }

        oss << "}";

        return oss.str();
    }

private:
    /**
     * Returns a `node_p` so that there are at least `n` remaining nodes (including the node
     * returned).
     *
     * If `n` is 0, returns `nullptr`.
     *
     * @param n The number of elements that should remain, should be smaller or equal to the
     * number of elements in the list.
     * @return A `node_p` with `n` remaining elements.
     */
    node_p last(size_type n = 1)
    {
        if (n == 0)
        {
            return nullptr;
        }
        if (n > m_size)
        {
            throw std::runtime_error("Size exceeded");
        }

        node_p it = m_head;

        std::deque<node_p> node_ps;
        for (unsigned i = 0; i < n; i++)
        {
            node_ps.push_back(it);
            it = it->next;
        }

        while (!(node_ps.back()->next == nullptr))
        {
            node_ps.pop_front();
            node_ps.push_back(node_ps.back()->next);
        }

        return node_ps.front();
    }
};
