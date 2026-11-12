// Wilhelm malé (wilma870)
// Oscar Jansson (oscja211)
// syftet med filen är att definera Tour objectet och hantera insert metoder

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include "cmath"
#include "set"

Tour::Tour(){
}

Tour::~Tour()
{

    Node* node = m_start->next;

    while (node != m_start){
        Node* next = node->next;
        delete node;
        node = next;
    }
    delete m_start;
}

void Tour::show() const
{
    if (m_start == nullptr){
        return;
    }

    Node* curr = m_start;
    do {
        cout << curr->point << endl;
        curr = curr->next;
    }
    while (curr != m_start);
}

void Tour::draw(QGraphicsScene *scene) const
{
    if (m_start == nullptr){
        return;
    }
    Node* curr = m_start;
    scene->clear();

    do {
        curr->point.drawTo(curr->next->point,scene);
        curr = curr->next;

    }
    while (curr != m_start);
}

int Tour::size() const
{
    if (m_start == nullptr){
        return 0;
    }

    Node* curr = m_start;
    int counter = 0;
    do {
        counter++;
        curr = curr->next;
    }
    while (curr != m_start);
    return counter;
}

// calculates the total distance of the tour
double Tour::distance() const
{

    if (m_start == nullptr){
        return 0;
    }
    Node* curr = m_start;
    double distance = 0;

    do {
        Point prev = curr->point;
        curr = curr->next;
        distance += prev.distanceTo(curr->point);
    }
    while (curr != m_start);
    return distance;
}

void Tour::insertNearest(const Point& p)
{
    Node* curr = m_start;

    if (curr == nullptr){
        Node* n = new Node (p,nullptr);
        n->next = n;
        m_start = n;
        return;
    }

    Node* smallest = m_start;
    double smallest_distance = m_start->point.distanceTo(p);
    do {
        double distance = curr->point.distanceTo(p);
        if (smallest_distance > distance){
            smallest_distance = distance;
            smallest = curr;
        }
        curr = curr->next;
    }
    while (curr != m_start);

    Node* n = new Node(p,smallest->next);
    smallest->next = n;
}

void Tour::insertSmallest(const Point& p)
{
    Node* node = m_start;

    if (node == nullptr){
        Node* n = new Node (p,nullptr);
        n->next = n;
        m_start = n;
        return;
    }

    double smallest_dist = 0;
    Node* smallest;

    do {

        double dist1 = node->point.distanceTo(node->next->point);
        double dist2 = node->point.distanceTo(p) + p.distanceTo(node->next->point);

        double dist = dist2 - dist1;

        if (dist < smallest_dist || smallest_dist == 0){
            smallest = node;
            smallest_dist = dist;
        }

        node = node->next;
    }
    while (node != m_start);

    Node* n = new Node(p,smallest->next);
    smallest->next = n;
}
