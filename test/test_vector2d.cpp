#include "vector2d.h"
#include <gtest/gtest.h>

TEST(constructVectorTest, NegativeNos)
{
    vector2d my_vector = vector2d(1, 2);
    ASSERT_EQ(1, my_vector.get_x());
    ASSERT_EQ(2, my_vector.get_y());
}

TEST(addVectorTest, NegativeNos)
{
    vector2d v1 = vector2d(1.5, 2.0);
    vector2d v2 = vector2d(1.0, 1.0);
    ASSERT_EQ(vector2d(2.5, 3.0), v1 + v2);
    v1 += v2;
    ASSERT_EQ(vector2d(2.5, 3.0), v1);
}

TEST(subtractVector, NegativeNos)
{
    vector2d v1 = vector2d(1.5, 2.0);
    vector2d v2 = vector2d(1.0, 1.0);
    ASSERT_EQ(vector2d(0.5, 1.0), v1 - v2);
}

TEST(scalarMultVector, NegativeNos)
{
    vector2d v1(2, 3);
    ASSERT_EQ(vector2d(4, 6), v1 * 2);
}

TEST(lengthVector, NegativeNos)
{
    vector2d v(6, 8);
    ASSERT_EQ(v.length(), 10);
}

TEST(dotProduct, NegativeNos)
{
    vector2d v(-6, 8);
    ASSERT_EQ(v.dot(vector2d(5, 12)), 66);
}

TEST(unit, NegativeNos)
{
    vector2d v(3, 4);
    ASSERT_EQ(v.unit(), vector2d(0.6, 0.8));
}

TEST(angleRadians, NegativeNos)
{
    vector2d v(1, 1);
    ASSERT_EQ(v.angleRadians(), 0.7853981633974483);
}

TEST(angleDegrees, NegativeNos)
{
    vector2d v(1, 1);
    ASSERT_EQ(v.angleDegrees(), 45);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};
