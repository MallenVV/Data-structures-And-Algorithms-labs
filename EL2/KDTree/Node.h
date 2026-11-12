/**
 * File: Node.h
 * Author: Wilehlm Malé (wilma870)
 *         Oscar Jansson (Oscja211)
 * ------------------------
 * An interface representing a Node containing Point, Value, left child, right child.
 */

#ifndef NODE_H
#define NODE_H

#include "Point.h"
#include "BoundedPQueue.h"
#include <stdexcept>
#include <cmath>


template <size_t N, typename ElemType>
class Node {

public:
    Point<N> point;
    Node* left = nullptr;
    Node* right = nullptr;
    ElemType value;

    //Constructor
    Node() = default;
    //Destructor
    ~Node();
    //Copy constructor
    Node(const Node& other);
    //Copy assignment
    Node& operator=(const Node& other);
};

template <size_t N, typename ElemType>
Node<N,ElemType>::~Node(){
    delete left;
    delete right;
}

template <size_t N, typename ElemType>
Node<N,ElemType>::Node(const Node<N,ElemType>& other): point{other.point}, left{nullptr}, right{nullptr}, value{other.value}{
    if (other.left != nullptr){
        left = new Node(*other.left);
    }

    if (other.right != nullptr){
        right = new Node(*other.right);
    }
}

template <size_t N, typename ElemType>
Node<N,ElemType>& Node<N,ElemType>::operator=(const Node<N,ElemType>& other){
    if (this == &other){
        return *this;
    }

    delete left;
    delete right;

    point = other.point;
    left = nullptr;
    right = nullptr;
    value = other.value;

    if (other.left != nullptr){
        left = new Node(*other.left);
    }

    if (other.right != nullptr){
        right = new Node(*other.right);
    }

    return *this;
}


#endif // NODE_H
