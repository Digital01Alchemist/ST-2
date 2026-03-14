// Copyright 2022 UNN-CS
#include <cmath>
#include "circle.h"
#include "tasks.h"

const double PI = 3.14159265358979323846;

RopeResult solveRopeTask() {
    Circle earth(6378100.0);

    double originalFerence = earth.getFerence();
    double newFerence = originalFerence + 1.0;

    Circle newEarth(0);
    newEarth.setFerence(newFerence);

    double gap = newEarth.getRadius() - earth.getRadius();

    return {gap};
}

PoolResult solvePoolTask() {
    double poolRadius = 3.0;
    double pathWidth = 1.0;
    double outerRadius = poolRadius + pathWidth;

    Circle pool(poolRadius);
    Circle outer(outerRadius);

    double pathArea = outer.getArea() - pool.getArea();
    double pathCost = pathArea * 1000.0;

    double fenceFerence = outer.getFerence();
    double fenceCost = fenceFerence * 2000.0;

    double totalCost = pathCost + fenceCost;

    return {pathCost, fenceCost, totalCost};
}
