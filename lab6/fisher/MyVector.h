// Wilhelm Malé (wilma870)
// Oscar Jansson (oscja211)

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
#include <fstream>
#include <iostream>

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);


    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    bool empty()const;

    T* begin();

    T* end();

    T const* cbegin() const;

    T const* cend() const;

    void clear();

    unsigned size()const;

private:

    unsigned capacity{1};
    T* list{nullptr};
    unsigned amount{0};

};
//constructor
template<typename T>
MyVector<T>::MyVector() : list{new T[capacity]}{
}

//destructor
template<typename T>
MyVector<T>::~MyVector(){
    delete[] list;
}

//copy constructor
template<typename T>
MyVector<T>::MyVector(const MyVector& other) : amount{other.amount}, capacity{other.capacity}, list{new T[other.capacity]}{
    std::copy(other.cbegin(), other.cend(), begin());
}

//Copy Assignment Operator
template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){

    if (this == &other){       // 1. self-assignment check
        return *this;
    }

    delete[] list;
    list = new T[other.capacity];
    capacity = other.capacity;
    amount = other.amount;

    std::copy(other.cbegin(), other.cend(), begin());
    return *this;
}

//adds an object to tha back of the vector
template<typename T>
void MyVector<T>::push_back(const T& e){
    if (capacity == amount) {
        T* new_list{new T[capacity*2]};

        std::copy(cbegin(), cend(), new_list);

        delete[] list;
        list = new_list;
        capacity*=2;
    }
    list[amount] = e;
    amount++;
}

//remove the last object in the vector
template<typename T>
void MyVector<T>::pop_back(){
    if (amount > 0){
        amount--;
    }
}

// used to find certain index in the vector
template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return list[i];
}

//
template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return list[i];
}

//returns true if MyVector is empty
template<typename T>
bool MyVector<T>::empty()const{
    return amount == 0;
}

// removes the contents of the vector
template<typename T>
void MyVector<T>::clear(){
    amount = 0;
    capacity = 1;

    delete[] list;
    T* new_list{new T[capacity]};
    list = new_list;
}

//get the size of the vector
template<typename T>
unsigned MyVector<T>::size()const{
    return amount;
}

//returns an iterator to the begining
template<typename T>
T* MyVector<T>::begin(){
    return list;
}

//returns an iterator to the end
template<typename T>
T* MyVector<T>::end(){
    return list + amount;
}

//returns an iterator to the begining
template<typename T>
T const* MyVector<T>::cbegin()const{
    return list;
}

//returns an iterator to the end
template<typename T>
T const* MyVector<T>::cend()const{
    return list + amount;
}

#endif // MY_VECTOR_H
