/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

// Wilhelm malé (wilma870)
// Oscar Jansson (oscja211)

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include <QGraphicsScene>

class Junk : public Unit {
public:
    Junk(const Point& p): Unit(p){}

    /*
    * Draws this junk onto the given QGraphicsScene.
    */

    void draw(QGraphicsScene* scene) const override;

    void moveTowards(const Point&) override;

    bool isAlive()const override;

    bool isToBeJunked() const override;

    void doCrash() override;

    Junk* clone() const override;

    Junk(const Junk&) = default;


};

#endif // JUNK_H
