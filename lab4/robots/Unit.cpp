/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

// Wilhelm malé (wilma870)
// Oscar Jansson (oscja211)

#include "Unit.h"
#include "constants.h"
#include "utilities.h"
#include <cstdlib>
#include <cmath>


/**
 * Creats a unit in the form of robot or junk.
 * Places it on a random space at the start of the game
 */
Unit::Unit() {
    teleport();
}

/**
 * Creats a deep copy of Unit saving its location and
 * making sure that the new Unit har its own dynamically allocated memory.
 */
Unit::Unit(const Point& p) {
    x = p.x;
    y = p.y;
}

/**
 * Returnes the Point of the unit
 */
Point Unit::asPoint() const {
    return Point{x, y};
}

/**
 * Returnes true if the unit is at the same location as another.
 */
bool Unit::at(const Unit& u) const {
    return (x == u.x && y == u.y);
}

/**
 * Moves the Unit to the point p.
 */
void Unit::moveTowards(const Point& p) {
    if (x > p.x) x--;
    if (x < p.x) x++;
    if (y > p.y) y--;
    if (y < p.y) y++;
    checkBounds();
}

/**
 * returnes true i the unit is alive.
 * this can only be true for robot
 */
bool Unit::isAlive() const{
    return false;
}

/**
 * returnes true i the unit is is going to become junk this tick.
 * this can only be true for robot
 */
bool Unit::isToBeJunked()const{
    return false;
}

/**
 * Crashes the Robot so that it can be turned into junk
 */
void Unit::doCrash(){

}

/**
 * draws the Unit. Robot and Junk have different Draw methods.
 */
void Unit::draw(QGraphicsScene*)const{

}

void Unit::teleport() {
    x = rand_int (MIN_X, MAX_X);
    y = rand_int (MIN_Y, MAX_Y);
}

double Unit::distanceTo(const Unit& u) const {
    double dx = u.x - x;
    double dy = u.y - y;
    return sqrt(dx * dx + dy * dy);
}

/*
 * Put this unit inside playing field if outside
 */
void Unit::checkBounds() {
    if (x < MIN_X) x = MIN_X;
    if (x > MAX_X) x = MAX_X;
    if (y < MIN_Y) y = MIN_Y;
    if (y > MAX_Y) y = MAX_Y;
}


