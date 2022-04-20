#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>

#include "circular_iterator.hpp"
#include "list.hpp"

template<typename T>
class CircularList : public List<T>
{
public:
    using typename List<T>::size_type;

    using iterator = CircularListIterator<T>;

    friend CircularListIterator<T>;

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

    CircularList(CircularList<T> const& other)
        : CircularList()
    {
        for (auto it = other.begin(); it != other.end(); it++)
        {
            this->push_back(*it);
        }
    }

    ~CircularList()
    {
        this->clear();
        delete m_head;
    }

    auto operator==(CircularList<T> const& other) const -> bool
    {
        if (this->m_size != other.m_size)
        {
            return false;
        }

        for (auto it1 = this->begin(), it2 = other.begin(); it1 != this->end(); it1++, it2++)
        {
            if (*it1 != *it2)
            {
                return false;
            }
        }

        return true;
    }

    auto operator!=(CircularList<T> const& other) const -> bool
    {
        return !(*this == other);
    }

    iterator begin() const
    {
        return iterator(this, m_head->next);
    }

    iterator end() const
    {
        return iterator(this, m_head);
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

    template<class... Args>
    void emplace_front(Args&&... args)
    {
        this->insert(T(args...), m_head, m_head->next);
    }

    void push_back(T data)
    {
        this->insert(data, m_head->prev, m_head);
    }

    template<class... Args>
    void emplace_back(Args&&... args)
    {
        this->insert(T(args...), m_head->prev, m_head);
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

        T ret = m_head->prev->data;

        this->remove(m_head->prev);

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

    bool is_empty() const
    {
        return m_size == 0;
    }

    bool empty() const
    {
        return this->is_empty();
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

    void sort()
    {
        if (m_size < 2)
        {
            return;
        }

        bool has_swapped;
        do
        {
            has_swapped = false;

            node* it1 = m_head->next;
            node* it2 = m_head->next->next;

            while (it2 != m_head)
            {
                if (it1->data > it2->data)
                {
                    this->swap_nodes(it1, it2);
                    std::swap(it1, it2);

                    has_swapped = true;
                }

                it1 = it2;
                it2 = it2->next;
            }
        } while (has_swapped);
    }

    bool is_sorted()
    {
        if (m_size == 0)
        {
            return true;
        }

        node* it = m_head->next;

        while (it->next != m_head)
        {
            if (!(it->data < it->next->data))
            {
                return false;
            }

            it = it->next;
        }

        return true;
    }

    size_type size()
    {
        return m_size;
    }

    void reverse()
    {
        if (m_size < 2)
        {
            return;
        }

        node* it = m_head->next;

        while (it != m_head)
        {
            std::swap(it->next, it->prev);
            it = it->prev;
        }
        std::swap(it->next, it->prev);
    }

    std::string name()
    {
        return "CircularList";
    }

    std::string to_string()
    {
        std::ostringstream oss;

        oss << "{ ";

        node* it = m_head->next;
        while (it != m_head)
        {
            oss << it->data << " ";
            it = it->next;
        }

        oss << "}";

        return oss.str();
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

    void swap_nodes(node* n1, node* n2)
    {
        std::tie(n1->prev->next, n1->next->prev, n2->prev->next, n2->next->prev)
            = std::make_tuple(n2, n2, n1, n1);

        std::swap(n1->next, n2->next);
        std::swap(n1->prev, n2->prev);
    }

    node* nth_pointer(size_type pos)
    {
        // NOTE: Could be optimized by checking whether the position is closer to the beginning
        // or the end.
        this->verify_required_size(pos + 1);

        node* it = m_head->next;

        while (pos != 0)
        {
            it = it->next;
            pos--;
        }

        return it;
    }
};
