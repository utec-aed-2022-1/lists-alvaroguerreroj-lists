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
        node_p it = m_head;

        while (it != nullptr)
        {
            node_p next = it->next;
            delete it;

            it = next;
        }
    }

    T front()
    {
        this->verify_required_size(1);

        return m_head->data;
    }

    T back()
    {
        return this->last()->data;
    }

    void push_front(T data)
    {
        node_p new_head = new Node<T>(data, m_head);
        m_head = new_head;

        m_size++;
    }

    void push_back(T data)
    {
        if (this->is_empty())
        {
            this->push_front(data);
        }
        else
        {
            node_p back_p = this->last();
            back_p->next = new Node<T>(data);
            back_p = back_p->next;

            m_size++;
        }
    }

    T pop_front()
    {
        this->verify_required_size(1);

        T ret = m_head->data;
        node_p next_head = m_head->next;
        delete m_head;
        m_head = next_head;

        m_size--;

        return ret;
    }

    T pop_back()
    {
        if (m_size == 1)
        {
            return this->pop_front();
        }
        else
        {
            node_p second_to_last = this->last(2);

            T ret = second_to_last->next->data;
            delete second_to_last->next;
            second_to_last->next = nullptr;

            m_size--;

            return ret;
        }
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
        return m_size == 0;
    }

    operator bool()
    {
        return !this->is_empty();
    }

    size_type size()
    {
        return m_size;
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
    node_p nth_pointer(size_type pos)
    {
        verify_required_size(pos);

        node_p it = m_head;

        while (pos != 0)
        {
            it = it->next;

            pos--;
        }

        return it;
    }

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

        this->verify_required_size(n);

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

    void verify_required_size(size_type n)
    {
        if (n > m_size)
        {
            throw std::runtime_error("Insufficient size");
        }
    }
};
