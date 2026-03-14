// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cstdint>
#include "circle.h"
#include "tasks.h"

const double PI = 3.14159265358979323846;
const double EPSILON = 1e-6;

class CircleTest : public ::testing::Test {
 protected:
    Circle circle{1.0};
};

TEST_F(CircleTest, ConstructorSetsRadius) {
    Circle c(5.0);
    EXPECT_NEAR(c.getRadius(), 5.0, EPSILON);
}

TEST_F(CircleTest, ConstructorCalculatesFerence) {
    Circle c(5.0);
    double expected = 2 * PI * 5.0;
    EXPECT_NEAR(c.getFerence(), expected, EPSILON);
}

TEST_F(CircleTest, ConstructorCalculatesArea) {
    Circle c(5.0);
    double expected = PI * 5.0 * 5.0;
    EXPECT_NEAR(c.getArea(), expected, EPSILON);
}

TEST_F(CircleTest, SetRadiusUpdatesRadius) {
    circle.setRadius(3.0);
    EXPECT_NEAR(circle.getRadius(), 3.0, EPSILON);
}

TEST_F(CircleTest, SetRadiusUpdatesFerence) {
    circle.setRadius(3.0);
    double expected = 2 * PI * 3.0;
    EXPECT_NEAR(circle.getFerence(), expected, EPSILON);
}

TEST_F(CircleTest, SetRadiusUpdatesArea) {
    circle.setRadius(3.0);
    double expected = PI * 3.0 * 3.0;
    EXPECT_NEAR(circle.getArea(), expected, EPSILON);
}

TEST_F(CircleTest, SetFerenceUpdatesRadius) {
    double newFerence = 2 * PI * 7.0;
    circle.setFerence(newFerence);
    EXPECT_NEAR(circle.getRadius(), 7.0, EPSILON);
}

TEST_F(CircleTest, SetFerenceUpdatesFerence) {
    double newFerence = 2 * PI * 7.0;
    circle.setFerence(newFerence);
    EXPECT_NEAR(circle.getFerence(), newFerence, EPSILON);
}

TEST_F(CircleTest, SetFerenceUpdatesArea) {
    double newFerence = 2 * PI * 7.0;
    circle.setFerence(newFerence);
    double expected = PI * 7.0 * 7.0;
    EXPECT_NEAR(circle.getArea(), expected, EPSILON);
}

TEST_F(CircleTest, SetAreaUpdatesRadius) {
    double newArea = PI * 4.0 * 4.0;
    circle.setArea(newArea);
    EXPECT_NEAR(circle.getRadius(), 4.0, EPSILON);
}

TEST_F(CircleTest, SetAreaUpdatesFerence) {
    double newArea = PI * 4.0 * 4.0;
    circle.setArea(newArea);
    double expected = 2 * PI * 4.0;
    EXPECT_NEAR(circle.getFerence(), expected, EPSILON);
}

TEST_F(CircleTest, SetAreaUpdatesArea) {
    double newArea = PI * 4.0 * 4.0;
    circle.setArea(newArea);
    EXPECT_NEAR(circle.getArea(), newArea, EPSILON);
}

TEST_F(CircleTest, ZeroRadius) {
    Circle c(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST_F(CircleTest, LargeRadius) {
    Circle c(1000.0);
    EXPECT_NEAR(c.getRadius(), 1000.0, EPSILON);
    double expectedFerence = 2 * PI * 1000.0;
    EXPECT_NEAR(c.getFerence(), expectedFerence, EPSILON);
}

TEST_F(CircleTest, SmallRadius) {
    Circle c(0.001);
    EXPECT_NEAR(c.getRadius(), 0.001, EPSILON);
}

TEST_F(CircleTest, FerenceAreaRelationship) {
    Circle c(2.5);
    double radius = c.getRadius();
    double ference = c.getFerence();
    double area = c.getArea();

    EXPECT_NEAR(ference, 2 * PI * radius, EPSILON);
    EXPECT_NEAR(area, PI * radius * radius, EPSILON);
}

TEST_F(CircleTest, MultipleSetOperations) {
    circle.setRadius(2.0);
    EXPECT_NEAR(circle.getRadius(), 2.0, EPSILON);

    circle.setRadius(3.0);
    EXPECT_NEAR(circle.getRadius(), 3.0, EPSILON);

    circle.setRadius(4.0);
    EXPECT_NEAR(circle.getRadius(), 4.0, EPSILON);
}

TEST_F(CircleTest, SetFerenceThenSetRadius) {
    double newFerence = 2 * PI * 5.0;
    circle.setFerence(newFerence);
    EXPECT_NEAR(circle.getRadius(), 5.0, EPSILON);

    circle.setRadius(3.0);
    EXPECT_NEAR(circle.getRadius(), 3.0, EPSILON);
    EXPECT_NEAR(circle.getFerence(), 2 * PI * 3.0, EPSILON);
}

TEST(RopeTaskTest, RopeGapCalculation) {
    RopeResult result = solveRopeTask();
    EXPECT_GT(result.gap, 0.0);
    EXPECT_NEAR(result.gap, 1.0 / (2 * PI), EPSILON);
}

TEST(RopeTaskTest, RopeGapIndependentOfEarthRadius) {
    RopeResult result = solveRopeTask();
    double gap = result.gap;

    EXPECT_NEAR(gap, 0.159154943, 1e-5);
}

TEST(PoolTaskTest, PoolPathCostCalculation) {
    PoolResult result = solvePoolTask();

    double poolArea = PI * 3.0 * 3.0;
    double outerArea = PI * 4.0 * 4.0;
    double pathArea = outerArea - poolArea;
    double expectedPathCost = pathArea * 1000.0;

    EXPECT_NEAR(result.pathCost, expectedPathCost, EPSILON);
}

TEST(PoolTaskTest, PoolFenceCostCalculation) {
    PoolResult result = solvePoolTask();

    double outerRadius = 4.0;
    double fenceFerence = 2 * PI * outerRadius;
    double expectedFenceCost = fenceFerence * 2000.0;

    EXPECT_NEAR(result.fenceCost, expectedFenceCost, EPSILON);
}

TEST(PoolTaskTest, PoolTotalCostCalculation) {
    PoolResult result = solvePoolTask();

    double expectedTotal = result.pathCost + result.fenceCost;
    EXPECT_NEAR(result.totalCost, expectedTotal, EPSILON);
}

TEST(PoolTaskTest, PoolCostsPositive) {
    PoolResult result = solvePoolTask();

    EXPECT_GT(result.pathCost, 0.0);
    EXPECT_GT(result.fenceCost, 0.0);
    EXPECT_GT(result.totalCost, 0.0);
}

TEST(PoolTaskTest, PoolFenceCostGreaterThanPathCost) {
    PoolResult result = solvePoolTask();
    EXPECT_GT(result.fenceCost, result.pathCost);
}
