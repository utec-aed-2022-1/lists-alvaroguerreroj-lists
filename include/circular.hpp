#pragma once

#include <iostream>
#include <stdexcept>

#include "list.hpp"

// TODO: Implement all methods
template<typename T>
class CircularList : public List<T>
{
public:
    using typename List<T>::size_type;

private:
    using node = Node<T>;

private:
    node* m_head; // sentinel
    size_type m_size;

public:
    // TODO: Check whether `m_head` can be initialized passing `m_head` as an argument.
    CircularList()
        : m_head(new node(T())),
          m_size(0)
    {
        m_head->next = m_head;
        m_head->prev = m_head;
    }

    ~CircularList()
    {
        this->clear();
        delete m_head;
    }

    T front()
    {
        this->verify_required_size(1);

        return m_head->next->data;
    }

    T back()
    {
        this->verify_required_size(1);

        return m_head->prev->data;
    }

    void push_front(T data)
    {
        this->insert(data, m_head, m_head->next);
    }

    void push_back(T data)
    {
        this->insert(data, m_head->prev, m_head);
    }

    T pop_front()
    {
        this->verify_required_size(1);

        T ret = m_head->next->data;

        this->remove(m_head->next);

        return ret;
    }

    void remove(size_type pos)
    {
        this->verify_required_size(1);

        node* it = this->nth_pointer(pos);

        this->remove(it);
    }

    void clear()
    {
        node* it = m_head->next;

        while (it != m_head)
        {
            node* next = it->next;
            delete it;
            it = next;
        }

        m_head->next = m_head;
        m_head->prev = m_head;

        m_size = 0;
    }

private:
    void verify_required_size(size_type n)
    {
        if (n > m_size)
        {
            throw std::runtime_error("Insufficient size");
        }
    }

    void insert(T data, node* left, node* right)
    {
        node* new_element = new node(data, right, left);
        left->next = new_element;
        right->prev = new_element;

        m_size++;
    }

    void remove(node* it)
    {
        it->prev->next = it->next;
        it->next->prev = it->prev;

        delete it;

        m_size--;
    }

    node* nth_pointer(size_type pos)
    {
        // NOTE: Could be optimized by checking whether the position is closer to the beginning
        // or the end.
        this->verify_required_size(pos);

        node* it = m_head->next;

        while (pos != 0)
        {
            it = it->next;
            pos--;
        }

        return it;
    }
};
