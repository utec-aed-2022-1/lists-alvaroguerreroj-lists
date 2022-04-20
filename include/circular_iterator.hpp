#pragma once

#include <stdexcept>
#include <utility>

template<typename T>
class CircularList;

template<typename T>
class CircularListIterator
{
private:
    using cl_iter = CircularListIterator<T>;
    using cl = CircularList<T>;

    using node = typename cl::node;

    cl const* m_cl;
    node* m_node_p;

public:
    CircularListIterator() = delete;

    CircularListIterator(cl const* cl, node* node_p)
        : m_cl(cl),
          m_node_p(node_p)
    {
    }

    CircularListIterator(CircularListIterator const& other)
        : m_cl(other.m_cl),
          m_node_p(other.m_node_p)
    {
    }

    ~CircularListIterator() = default;

    auto operator*() -> T&
    {
        return m_node_p->data;
    }

    auto operator=(cl_iter const& other) -> CircularListIterator<T>&
    {
        if (this != &other)
        {
            this->swap(CircularListIterator<T>(other));
        }

        return *this;
    }

    void swap(cl_iter& other)
    {
        std::swap(m_cl, other.m_cl);
        std::swap(m_node_p, other.m_node_p);
    }

    auto operator==(cl_iter const& other) -> bool
    {
        return m_cl == m_cl && m_node_p == other.m_node_p;
    }

    auto operator!=(cl_iter const& other) -> bool
    {
        return !(*this == other);
    }

    auto operator++() -> cl_iter&
    {
        m_node_p = m_node_p->next;

        return *this;
    }

    auto operator++(int) -> cl_iter
    {
        cl_iter ret(*this);

        ++*this;

        return ret;
    }

    auto operator--() -> cl_iter&
    {
        m_node_p = m_node_p->prev;

        return *this;
    }

    auto operator--(int) -> cl_iter
    {
        cl_iter ret(*this);

        --*this;

        return ret;
    }

    auto operator+=(int n) -> cl_iter&
    {
        if (n < 0)
        {
            return *this -= -n;
        }

        while (n != 0)
        {
            n--;
            ++*this;
        }
    }

    auto operator-=(int n) -> cl_iter&
    {
        if (n < 0)
        {
            return *this += -n;
        }

        while (n != 0)
        {
            n--;
            --*this;
        }
    }
};
