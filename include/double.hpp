#pragma once

#include <iostream>
#include <stdexcept>

#include "list.hpp"

// TODO: Implement all methods
template<typename T>
class DoubleList : public List<T>
{
public:
    using typename List<T>::size_type;

private:
    using node = Node<T>;

private:
    node* m_head;
    node* m_tail;
    size_type m_size;

public:
    DoubleList()
        : m_head(new node(T(), nullptr, nullptr)),
          m_tail(new node(T(), nullptr, m_head)),
          m_size(0)
    {
        // NOTE: Not sure if it's necessary to set `m_head->next`. When `m_head` is initialized
        // `m_tail` has not been defined yet so it may be erroneous.
        m_head->next = m_tail;
    }

    ~DoubleList()
    {
        this->clear();

        delete m_head;
        delete m_tail;
    }

    T front()
    {
        this->verify_required_size(1);

        return m_head->next->data;
    }

    T back()
    {
        this->verify_required_size(1);

        return m_tail->prev->data;
    }

    void push_front(T data)
    {
        this->insert(data, m_head, m_head->next);
    }

    void push_back(T data)
    {
        this->insert(data, m_tail->prev, m_tail);
    }

    T pop_front()
    {
        this->verify_required_size(1);

        T ret = m_head->next->data;

        this->remove(m_head->next);

        return ret;
    }

    T pop_back()
    {
        this->verify_required_size(1);

        T ret = m_tail->prev->data;

        this->remove(m_tail->prev);

        return ret;
    }

    void insert(T data, size_type pos)
    {
        node* nth_p = this->nth_pointer(pos);

        this->insert(data, nth_p->prev, nth_p);
    }

    void remove(size_type pos)
    {
        this->verify_required_size(1);

        node* it = this->nth_pointer(pos);

        this->remove(it);
    }

    T& operator[](size_type pos)
    {
        return this->nth_pointer(pos)->data;
    }

    bool is_empty()
    {
        return m_size == 0;
    }

    void clear()
    {
        node* it = m_head->next;

        while (it != m_tail)
        {
            node* next = it->next;
            delete it;
            it = next;
        }

        m_head->next = m_tail;
        m_tail->prev = m_head;

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
