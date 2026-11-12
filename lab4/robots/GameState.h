/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Maintains the game state:  Location of all robots, junk and hero.
 */

// Wilhelm malé (wilma870)
// Oscar Jansson (oscja211)

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <QGraphicsScene>
#include "Unit.h"
#include "Robot.h"
#include "Junk.h"
#include "Hero.h"

class GameState {
public:

    /**
     * Initializes the game by creating a hero and the specified numer of robots.
     * Each robot is placed in a random, empty position on the game board.
     * Finally, the hero is teleported to a random location.
     */
    GameState(const int numberOfRobots);

    /**
     * Performs a deep copy of the other GameState. It creates a new hero and
     * clones each unit (robots and junk) from the other state, ensuring that
     * this new GameState has its own dynamically allocated memory.
     */
    GameState(const GameState& other);


    /**
     * Frees all dynamically allocated memory managed by this GameState object.
     * It deletes the hero and every unit in the units vector to prevent memory leaks.
     */
    ~GameState();


    /**
     * Implements the copy-and-swap idiom safely. It first cleans up its own
     * resources (hero and units) and then performs a deep copy of the resources
     * from the other GameState. Protects against self-assignment.
     */
    GameState& operator=(const GameState&);


    /**
     * Clear and redraw entire playing field
     */
    void draw(QGraphicsScene* scene) const;	// Clear and redraw entire playing field

    /**
     * Teleport hero to random location
     */
    void teleportHero();

    /**
     * Move robots one step towards hero
     */
    void moveRobots();

    /**
     * Identify crashed robots
     */
    void updateCrashes();

    /**
     * Count identified crashed robots
     */
    int countToBeJunked()const;

    /**
     * Replace each identified crashed robot with a junk
     */
    void junkTheCrashed();

    /**
     * Are there still robots that did not crash?
     */
    bool someRobotsAlive() const;

    /**
     * Is hero in same place as robot or junk?
     */
    bool heroDead() const;

    /**
     * Move hero towards dir
     */
    void moveHeroTowards (const Point& dir);

    /**
     * Return hero
     */
    Point getHeroAsPoint () const;

private:
    std::vector<Unit*> units;
    Hero* hero;

    // private helpers
    bool isEmpty(const Unit& unit) const;

};

#endif // GAMESTATE_H
