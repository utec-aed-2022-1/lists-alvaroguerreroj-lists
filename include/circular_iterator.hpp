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

    cl const* m_cl{nullptr};
    node* m_node_p{nullptr};

public:
    CircularListIterator() = default;

    CircularListIterator(cl const* cl, node* node_p)
        : m_cl(cl),
          m_node_p(node_p)
    {
    }

    CircularListIterator(CircularListIterator const& other) = default;
    CircularListIterator(CircularListIterator&& other) noexcept = default;

    ~CircularListIterator() = default;

    auto operator*() -> T&
    {
        return m_node_p->data;
    }

    auto operator->() -> T*
    {
        return &(m_node_p->data);
    }

    auto operator->() const -> T const*
    {
        return &(m_node_p->data);
    }

    auto operator=(cl_iter const& other) -> CircularListIterator<T>& = default;
    auto operator=(cl_iter&& other) noexcept -> CircularListIterator<T>& = default;

    void swap(cl_iter& other)
    {
        using std::swap;
        swap(m_cl, other.m_cl);
        swap(m_node_p, other.m_node_p);
    }

    void swap(cl_iter&& other)
    {
        using std::swap;
        swap(m_cl, other.m_cl);
        swap(m_node_p, other.m_node_p);
    }

    auto operator==(cl_iter const& other) const -> bool
    {
        return m_cl == m_cl && m_node_p == other.m_node_p;
    }

    auto operator!=(cl_iter const& other) const -> bool
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

template<typename T>
struct std::iterator_traits<CircularListIterator<T>>
{
    using difference_type = int;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::bidirectional_iterator_tag;
};
