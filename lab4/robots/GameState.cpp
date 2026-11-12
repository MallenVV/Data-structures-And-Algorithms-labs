/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

// Wilhelm malé (wilma870)
// Oscar Jansson (oscja211)

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>

GameState::GameState(const int  numberOfRobots ) {
    hero = new Hero();
    for (int i = 0; i < numberOfRobots; i++) {
        Unit *robot = new Robot{};
        while(!isEmpty(*robot)){
            delete robot;
            robot =  new Robot();
        }
        units.push_back(robot);
    }
    teleportHero();
}


GameState::GameState(const GameState& other)  {
    hero = new Hero(*other.hero);
    for (const Unit* unit : other.units) {
        units.push_back(unit->clone());
    }
}

GameState::~GameState() {
    delete hero;
    for (Unit* unit: units){
        delete unit;
    }
}

GameState& GameState::operator=(const GameState& other) {

    if (this == &other) {
        return *this;
    }

    for (Unit* unit : units) {
        delete unit;
    }
    units.clear();
    delete hero;

    hero = new Hero(*other.hero);
    for (const Unit* unit : other.units) {
        units.push_back(unit->clone());
    }
    return *this;
}


void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero->draw(scene);
    for (const Unit* unit: units)
        unit->draw(scene);
}
void GameState::teleportHero() {
    do hero->teleport();
    while (!isEmpty(*hero));
}

void GameState::moveRobots() {
    for(Unit* unit: units)
        unit->moveTowards(hero->asPoint());
}

void GameState::updateCrashes() {
    for(unsigned i=0; i < units.size(); ++i){
        for(unsigned j=i+1; j < units.size(); ++j){
            if(units[i]->at(*units[j])){
                units[i]->doCrash();
                units[j]->doCrash();
            }
        }
    }
}

int GameState::countToBeJunked() const{
    int numberDestroyed = 0;
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isToBeJunked())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed() {
    for(unsigned i=0; i < units.size(); ++i){
        if (units[i]->isToBeJunked()) {
            Junk *junk = new Junk(units[i]->asPoint());
            Unit *old_unit = units[i];
            units[i] = junk;
            delete old_unit;
        }
    }
}

bool GameState::someRobotsAlive() const {
    for(unsigned i=0; i < units.size(); ++i){
        if(units[i]->isAlive())
            return true;
    }
    return false;
}

bool GameState::heroDead() const {
    for(const Unit* unit: units){
        if(hero->at(*unit)){
            return true;
        }
    }
    return false;
}

void GameState::moveHeroTowards(const Point& dir) {
    hero->moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero->asPoint();}

bool GameState::isEmpty(const Unit& unit) const {
    for(const Unit *robot: units){
        if(robot->at(unit))
            return false;
    }
    return true;
}
