#pragma once

template<typename T>
struct Node
{
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr)
        : data(data),
          next(next),
          prev(prev)
    {
    }
};
