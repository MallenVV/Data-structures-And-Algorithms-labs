// Wilhelm Malé (wilma870)
// Oscar Jansson (oscja211)

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

  unsigned size() const;

  void parent_swap(const T& t, int node);

  void child_swap(const T& t, int node);

private:
  int last_position{-1};
};

//Constructor
template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){

}

//Destructor
template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
    // delete vector_array;
}

//Add object to the top of the stack
template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    last_position++;
    parent_swap(t, last_position);
}

//recursive traversal swaping with parent
template <typename T, typename C>
void MyPriorityQueue<T,C>::parent_swap(const T& t, int node){

    if (node != 0){
        int parent_pos = (node-1)/2;
        T parent = vector_array[parent_pos];
        if (strictly_larger_operator(parent, t)){
            vector_array[node] = parent;
            vector_array[parent_pos] = t;

            parent_swap(t, parent_pos);
        }
    }
}

//Return the object with the highest priority
template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

//remove the object with the highest priority
template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
//    std::cout << "vector[0]: " << vector_array[0] << std::endl;
//    std::cout << "vector[last_position]: " << vector_array[last_position] << std::endl;

    T temp = vector_array[0];
    T last = vector_array[last_position];

    vector_array[0] = vector_array[last_position];
    vector_array[last_position] = temp;


    T first = vector_array[0];
    last = vector_array[last_position];

    vector_array.pop_back();
    last_position--;


    child_swap(vector_array[0], 0);
}

//recursive traversal swaping with smallest child
template <typename T, typename C>
void MyPriorityQueue<T,C>::child_swap(const T& t, int node){

    int child_pos = 0;
    if (2*node+2 < vector_array.size()){
        if (strictly_larger_operator(vector_array[2*node+1], vector_array[2*node+2])){
            child_pos = 2*node+2;
        }
        else {
            child_pos = 2*node+1;
        }
    }

    else if (2*node+1 == vector_array.size()-1){
        child_pos = 2*node+1;
    }

    if (child_pos != 0){
        T child = vector_array[child_pos];
        if (strictly_larger_operator(t, child)){
            T temp = t;
            vector_array[node] = child;
            vector_array[child_pos] = temp;

            child_swap(temp, child_pos);
        }
    }

}

//Remove every element in the priority queue
template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.size() == 0;
}

//returns the amount of elements in the queue
template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}

#endif // MY_PRIORITY_QUEUE_H
