#pragma once

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <tuple>

#include "list.hpp"

template<typename T>
class ForwardList : public List<T>
{
public:
    using typename List<T>::size_type;

private:
    using node = Node<T>;

private:
    node* m_head;
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
        this->clear();
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
        node* new_head = new Node<T>(data, m_head);
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
            node* back_p = this->last();
            back_p->next = new Node<T>(data);
            back_p = back_p->next;

            m_size++;
        }
    }

    T pop_front()
    {
        this->verify_required_size(1);

        T ret = m_head->data;
        node* next_head = m_head->next;
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
            node* second_to_last = this->last(2);

            T ret = second_to_last->next->data;
            delete second_to_last->next;
            second_to_last->next = nullptr;

            m_size--;

            return ret;
        }
    }

    void insert(T data, size_type pos)
    {
        if (pos == 0)
        {
            this->push_front(data);
        }
        else
        {
            node* it = this->nth_pointer(pos - 1);
            it->next = new Node<T>(data, it->next);

            m_size++;
        }
    }

    void remove(size_type pos)
    {
        if (pos == 0)
        {
            this->pop_front();
        }
        else
        {
            this->verify_required_size(pos);

            node* it = this->nth_pointer(pos - 1);
            node* next_next = it->next->next;
            delete it->next;
            it->next = next_next;

            m_size--;
        }
    }

    T& operator[](size_type pos)
    {
        return this->nth_pointer(pos)->data;
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
        node* it = m_head;

        while (it != nullptr)
        {
            node* next = it->next;
            delete it;

            it = next;
        }

        m_head = nullptr;
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

            node* it1 = m_head;
            node* it2 = m_head->next;

            if (it1->data > it2->data)
            {
                std::tie(m_head, it1->next, it2->next) = std::make_tuple(it2, it2->next, it1);
                std::swap(it1, it2);

                has_swapped = true;
            }

            while (it2->next != nullptr)
            {
                node* it0 = it1;
                it1 = it2;
                it2 = it2->next;

                if (it1->data > it2->data)
                {
                    std::tie(it0->next, it1->next, it2->next)
                        = std::make_tuple(it2, it2->next, it1);
                    std::swap(it1, it2);

                    has_swapped = true;
                }
            }

        } while (has_swapped);
    }

    bool is_sorted()
    {
        if (m_size == 0)
        {
            return true;
        }

        node* it = m_head;

        while (it->next != nullptr)
        {
            if (!(it->data < it->next->data))
            {
                return false;
            }

            it = it->next;
        }

        return true;
    }

    void reverse()
    {
        node* old_head = nullptr;
        node* it = m_head;

        while (it != nullptr)
        {
            node* next = it->next;
            it->next = old_head;
            old_head = it;
            it = next;
        }

        m_head = old_head;
    }

    std::string name()
    {
        return "ForwardList";
    }

    std::string to_string()
    {
        std::ostringstream oss;

        oss << "{ ";

        node* it = m_head;
        while (it != nullptr)
        {
            oss << it->data << " ";
            it = it->next;
        }

        oss << "}";

        return oss.str();
    }

private:
    node* nth_pointer(size_type pos)
    {
        verify_required_size(pos);

        node* it = m_head;

        while (pos != 0)
        {
            it = it->next;

            pos--;
        }

        return it;
    }

    /**
     * Returns a `node*` so that there are at least `n` remaining nodes (including the node
     * returned).
     *
     * If `n` is 0, returns `nullptr`.
     *
     * @param n The number of elements that should remain, should be smaller or equal to the
     * number of elements in the list.
     * @return A `node*` with `n` remaining elements.
     */
    node* last(size_type n = 1)
    {
        if (n == 0)
        {
            return nullptr;
        }

        this->verify_required_size(n);

        node* it = m_head;
        size_type remaining = m_size;

        while (remaining > n)
        {
            it = it->next;
            remaining--;
        }

        return it;
    }

    void verify_required_size(size_type n)
    {
        if (n > m_size)
        {
            throw std::runtime_error("Insufficient size");
        }
    }
};
