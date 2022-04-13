#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>

#include "list.hpp"

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
        : m_head(nullptr),
          m_tail(nullptr),
          m_size(0)
    {
    }

    ~DoubleList()
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
        this->verify_required_size(1);

        return m_tail->data;
    }

    void push_front(T data)
    {
        if (m_size == 0)
        {
            m_head = new node(data);
            m_tail = m_head;
        }
        else
        {
            node* new_head = new node(data, m_head);

            m_head->prev = new_head;

            m_head = new_head;
        }

        m_size++;
    }

    void push_back(T data)
    {
        if (m_size == 0)
        {
            this->push_front(data);
        }
        else
        {
            m_tail->next = new node(data, nullptr, m_tail);

            m_tail = m_tail->next;

            m_size++;
        }
    }

    T pop_front()
    {
        this->verify_required_size(1);

        if (m_size == 1)
        {
            delete m_head;

            m_head = nullptr;
            m_tail = nullptr;

            m_size--;

            return m_head->data;
        }
        else
        {
            T ret = m_head->data;

            node* next_head = m_head->next;

            delete m_head;

            m_head = next_head;
            m_head->prev = nullptr;

            m_size--;

            return ret;
        }
    }

    T pop_back()
    {
        this->verify_required_size(1);

        if (m_size == 1)
        {
            return this->pop_front();
        }
        else
        {
            T ret = m_tail->data;

            node* next_tail = m_tail->prev;

            delete m_tail;

            m_tail = next_tail;
            m_tail->next = nullptr;

            m_size--;

            return ret;
        }
    }

    void insert(T data, size_type pos)
    {
        this->verify_required_size(pos);

        if (pos == 0)
        {
            this->push_front(data);
        }
        else
        {
            node* nth_p = this->nth_pointer(pos);

            this->insert(data, nth_p->prev, nth_p);
        }
    }

    void remove(size_type pos)
    {
        this->verify_required_size(1);

        if (pos == 0)
        {
            this->pop_front();
        }
        else if (pos == m_size - 1)
        {
            this->pop_back();
        }
        else
        {
            node* it = this->nth_pointer(pos);

            this->remove(it);
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
        m_tail = nullptr;

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

            while (it2 != nullptr)
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

    size_type size()
    {
        return m_size;
    }

    void reverse()
    {
        node* it = m_head;

        while (it != nullptr)
        {
            std::swap(it->next, it->prev);
            it = it->prev;
        }

        std::swap(m_head, m_tail);
    }

    std::string name()
    {
        return "DoubleLinkedList";
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
        if (n1->prev == nullptr)
        {
            if (n2->next != nullptr)
            {
                std::tie(n1->next->prev, n2->prev->next, n2->next->prev)
                    = std::make_tuple(n2, n1, n1);
            }
        }
        else
        {
            if (n2->next == nullptr)
            {

                std::tie(n1->prev->next, n1->next->prev, n2->prev->next)
                    = std::make_tuple(n2, n2, n1);
            }
            else
            {

                std::tie(n1->prev->next, n1->next->prev, n2->prev->next, n2->next->prev)
                    = std::make_tuple(n2, n2, n1, n1);
            }
        }

        std::swap(n1->next, n2->next);
        std::swap(n1->prev, n2->prev);
    }

    node* nth_pointer(size_type pos)
    {
        // NOTE: Could be optimized by checking whether the position is closer to the beginning
        // or the end.
        this->verify_required_size(pos + 1);

        node* it = m_head;

        while (pos != 0)
        {
            it = it->next;
            pos--;
        }

        return it;
    }
};
