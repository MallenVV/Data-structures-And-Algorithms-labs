/**
 * File: KDTree.h
 * Author: Wilehlm Malé (wilma870)
 *         Oscar Jansson (Oscja211)
 * ------------------------
 * An interface representing a kd-tree in some number of dimensions. The tree
 * can be constructed from a set of data and then queried for membership and
 * nearest neighbors.
 */

#ifndef KDTREE_INCLUDED
#define KDTREE_INCLUDED

#include "Point.h"
#include "Node.h"
#include "BoundedPQueue.h"
#include <stdexcept>
#include <cmath>

// "using namespace" in a header file is conventionally frowned upon, but I'm
// including it here so that you may use things like size_t without having to
// type std::size_t every time.
using namespace std;

template <size_t N, typename ElemType>
class KDTree {
public:
    // Constructor: KDTree();
    // Usage: KDTree<3, int> myTree;
    // ----------------------------------------------------
    // Constructs an empty KDTree.
    KDTree();
    
    // Destructor: ~KDTree()
    // Usage: (implicit)
    // ----------------------------------------------------
    // Cleans up all resources used by the KDTree.
    ~KDTree();
    
    // KDTree(const KDTree& rhs);
    // KDTree& operator=(const KDTree& rhs);
    // Usage: KDTree<3, int> one = two;
    // Usage: one = two;
    // -----------------------------------------------------
    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);
    
    // size_t dimension() const;
    // Usage: size_t dim = kd.dimension();
    // ----------------------------------------------------
    // Returns the dimension of the points stored in this KDTree.
    size_t dimension() const;
    
    // size_t size() const;
    // bool empty() const;
    // Usage: if (kd.empty())
    // ----------------------------------------------------
    // Returns the number of elements in the kd-tree and whether the tree is
    // empty.
    size_t size() const;
    bool empty() const;
    
    // bool contains(const Point<N>& pt) const;
    // Usage: if (kd.contains(pt))
    // ----------------------------------------------------
    // Returns whether the specified point is contained in the KDTree.
    bool contains(const Point<N>& pt) const;
    
    // void insert(const Point<N>& pt, const ElemType& value);
    // Usage: kd.insert(v, "This value is associated with v.");
    // ----------------------------------------------------
    // Inserts the point pt into the KDTree, associating it with the specified
    // value. If the element already existed in the tree, the new value will
    // overwrite the existing one.
    void insert(const Point<N>& pt, const ElemType& value);
    
    // ElemType& operator[](const Point<N>& pt);
    // Usage: kd[v] = "Some Value";
    // ----------------------------------------------------
    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, then it is added to the KDTree using the
    // default value of ElemType as its key.
    ElemType& operator[](const Point<N>& pt);
    
    // ElemType& at(const Point<N>& pt);
    // const ElemType& at(const Point<N>& pt) const;
    // Usage: cout << kd.at(v) << endl;
    // ----------------------------------------------------
    // Returns a reference to the key associated with the point pt. If the point
    // is not in the tree, this function throws an out_of_range exception.
    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;
    
    // ElemType kNNValue(const Point<N>& key, size_t k) const
    // Usage: cout << kd.kNNValue(v, 3) << endl;
    // ----------------------------------------------------
    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the most common value associated with those
    // points. In the event of a tie, one of the most frequent value will be
    // chosen.
    ElemType kNNValue(const Point<N>& key, size_t k) const;

    // traverses the tree in search of the point given and returns the node that contains it
    Node<N,ElemType>* findNode(const Point<N>& pt)const;

    // recursivly traverses the tree looking for closest points and adding them to a boundedPriorityQueue and when att root has the closest Nodes
    void searchTree(Node<N,ElemType>* curr, const Point<N>& key, const int depth, BoundedPQueue<Node<N,ElemType>*>& bpq)const;

    // deletes the root that then deletes the entire tree recursivly
    void deleteTree();

    // deep copies the tree structure such that copy constructor and copy assignment gets a deep copy
    Node<N,ElemType>* copy_subtree(Node<N,ElemType>* n);

private:
    int dim;
    int amount;

    Node<N,ElemType>* root;
};

/** KDTree class implementation details */

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(): dim{N}, amount{0}, root{nullptr}{
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    deleteTree();
    amount = 0;
    dim = 0;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree<N, ElemType>& other): dim{other.dim}, amount{other.amount}{
    root = copy_subtree(other.root);
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree<N, ElemType>& other){
    if (this == &other){
        return *this;
    }

    deleteTree();
    dim = other.dim;
    amount = other.amount;

    root = copy_subtree(other.root);

    return *this;
}

template <size_t N, typename ElemType>
Node<N,ElemType>* KDTree<N, ElemType>::copy_subtree(Node<N,ElemType>* n) {

    if (n == nullptr) {
        return nullptr;
    }

    Node<N,ElemType>* copy = new Node{*n};
    return copy;
}


template <size_t N, typename ElemType>
void KDTree<N, ElemType>::deleteTree() {

    if (!empty()){
        delete root;
        root = nullptr;
    }
}


template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    return dim;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const{
    return amount;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const{
    return root == nullptr;
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value) {

    int i = 0;

    if (empty()){
        root = new Node<N,ElemType>{};
        root->point = pt;
        root->value = value;
        amount++;
    }
    else if (root->point == pt){
        root->value = value;
    }
    else {
        Node<N,ElemType>* node = root;

        while(true) {
            if (node->point[i % N] > pt[i % N]) {
                if (node->left == nullptr) {
                    node->left = new Node<N,ElemType>{};
                    node->left->point = pt;
                    node->left->value = value;
                    amount++;
                    break;
                }
                else if (node->left->point == pt){
                    node->left->value = value;
                    break;
                }
                else {
                    node = node->left;
                }
            }

            else if (node->point[i % N] <= pt[i % N]) {
                if (node->right == nullptr) {
                    node->right = new Node<N,ElemType>{};
                    node->right->point = pt;
                    node->right->value = value;
                    amount++;
                    break;
                }
                else if (node->right->point == pt){
                    node->right->value = value;
                    break;
                }
                else {
                    node = node->right;
                }
            }
            i++;
        }
    }
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const{
    return findNode(pt) != nullptr;
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt) {
    Node<N,ElemType>* node = findNode(pt);
    if (node != nullptr){
        return node->value;
    }
    ElemType value = ElemType{};
    insert(pt, value);
    return findNode(pt)->value;
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) {
    Node<N,ElemType>* node = findNode(pt);
    if (node == nullptr) {
        throw out_of_range("out of range");
    }
    return node->value;
}

template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const {
    Node<N,ElemType>* node = findNode(pt);
    if (node == nullptr) {
        throw out_of_range("out of range");
    }

    return node->value;
}

template <size_t N, typename ElemType>
Node<N,ElemType>* KDTree<N, ElemType>::findNode(const Point<N>& pt) const{

    int i = 0;

    if (empty()){
        return nullptr;
    }
    Node<N,ElemType>* node = root;

    while(node != nullptr) {
        if (node->point[i % N] > pt[i % N]) {

            if (node->point == pt){
                return node;
            }

            if (node->left != nullptr) {
                node = node->left;
            }
            else {
                return nullptr;
            }
        }

        else if (node->point[i % N] <= pt[i % N]) {
            if (node->point == pt){
                return node;
            }

            if (node->right != nullptr) {
                node = node->right;
            }
            else {
                return nullptr;
            }
        }
        i++;
    }
    return nullptr;

}


template <size_t N, typename ElemType>
void KDTree<N, ElemType>::searchTree(Node<N,ElemType>* curr, const Point<N>& key, int depth, BoundedPQueue<Node<N,ElemType>*>& bpq) const{

    if (curr != nullptr){

        bpq.enqueue(curr, Distance(curr->point, key));

        if (curr->point[depth % N] > key[depth % N]) {
            searchTree(curr->left, key, depth+1, bpq);
            if (bpq.size() != bpq.maxSize() || bpq.worst() > abs(curr->point[depth % N] - key[depth % N])){

                searchTree(curr->right, key, depth+1, bpq);
            }
        }
        else {
            searchTree(curr->right, key, depth+1, bpq);
            if (bpq.size() != bpq.maxSize() || bpq.worst() > abs(curr->point[depth % N] - key[depth % N])){

                searchTree(curr->left, key, depth+1, bpq);
            }
        }
    }
}


template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const{

    BoundedPQueue<Node<N,ElemType>*> bpq(k);
    searchTree(root, key, 0, bpq);

    ElemType value;
    ElemType topValue;
    int topAmount = 0;
    map<ElemType, int> counter;
        while (!bpq.empty()){
            value = bpq.dequeueMin()->value;

            if (counter[value]){
                counter[value] += 1;
            }
            else {
                counter[value] = 1;
            }

            if (counter[value] > topAmount){
                topValue = value;
                topAmount = counter[value];
            }
        }
        return topValue;
}



#endif // KDTREE_INCLUDED
