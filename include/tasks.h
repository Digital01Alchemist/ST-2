// Copyright 2022 UNN-CS
#ifndef INCLUDE_TASKS_H_
#define INCLUDE_TASKS_H_

struct RopeResult {
    double gap;
};

struct PoolResult {
    double pathCost;
    double fenceCost;
    double totalCost;
};

RopeResult solveRopeTask();
PoolResult solvePoolTask();

#endif  // INCLUDE_TASKS_H_
