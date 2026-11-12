// Wilhelm malé (wilma870)
// Oscar Jansson (oscja211)
// Syftet med filen är att declarera Tour objectet

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {

public:
    //Node start;
    Tour();

    ~Tour();

    // shows the points in the route in order
    void show() const;

    // draws the route of the curent tour
    void draw(QGraphicsScene* scene)const ;

    // returns the amount of nodes the list tour includes
    int size()const;

    // calculates the total distance of the tour
    double distance()const;

    // inserts the point into the position that has the shortst lenght to another point.
    void insertNearest(const Point& p);

    // instsers the point into a position that creates the smallest difference in total lenght.
    void insertSmallest(const Point& p);

private:
    Node* m_start = nullptr;
};

#endif // TOUR_H
