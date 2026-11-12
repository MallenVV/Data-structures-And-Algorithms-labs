/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

// Wilhelm malé (wilma870)
// Oscar Jansson (oscja211)

#ifndef UNIT_H
#define UNIT_H

#include "utilities.h"
#include <QGraphicsScene>

/* Root class for all pieces on the board.
 * Subclasses are Robot, Hero and Junk.
 */
class Unit {
public:

    /**
     * Create a unit at a random position
     */
    Unit();

    /**
    * Create unit at given point
    */
    Unit(const Point& p);

    /**
    * Destructor function
    */
    virtual ~Unit(){}

    /**
    * Virual clone function
    */
    virtual Unit* clone() const = 0;

    /**
    * Return Point representation of Unit
    */
    Point asPoint() const;

    /**
     * returnes true i the unit is alive.
     * this can only be true for robot
     */
    virtual bool isAlive()const;


    virtual void doCrash();

    /**
     * Crashes the Robot so that it can be turned into junk
     */
    virtual bool isToBeJunked()const ;

    /**
     * draws the Unit. Robot and Junk have different Draw methods.
     */
    virtual void draw(QGraphicsScene*)const;

    /**
     * Moves the Unit to the point p.
     */
    virtual void moveTowards(const Point&);


    /**
     * Returnes true if the unit is at the same location as another.
     */
    bool at(const Unit& u) const;

    /**
    * Teleport. Does not check for collision
    */
    void teleport();

    /**
    * Euclidean distance to u
    */
    double distanceTo(const Unit& u) const;

private:
    int x;  // x position of this unit
    int y;  // y position of this unit

    // private helpers
    void checkBounds();
};

#endif // UNIT_H
