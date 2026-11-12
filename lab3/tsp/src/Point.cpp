// Wilhelm malé (wilma870)
// Oscar Jansson (oscja211)
// syftet med filen är att definera Point objectet


#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include "Point.h"

Point::Point(double _x, double _y)
    : x(_x), y(_y) {}

double Point::distanceTo(Point that) const
{
    double dx = x - that.x;
    double dy = y - that.y;
    return std::sqrt(dx*dx + dy*dy);
}

void Point::draw(QGraphicsScene *scene) const
{
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(x, y, 1, 1);
    item->setBrush(QBrush(QColor(255, 0, 0)));
    scene->addItem(item);
}

void Point::drawTo(Point that, QGraphicsScene *scene) const
{
    QGraphicsLineItem *item = new QGraphicsLineItem(x, y, that.x, that.y);
    scene->addItem(item);
}

string Point::toString() const
{
    stringstream string;
    string << "(" << std::fixed << std::setprecision(1) << std::showpoint
        << x << ", " << y << ")";
    return string.str();
}

ostream& operator <<(ostream& out, const Point& p) {
    out << p.toString();
    return out;
}
