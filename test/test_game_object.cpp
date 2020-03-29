#include "game_object.h"
#include "world.h"
#include <gtest/gtest.h>

TEST(constructVectorTest, NegativeNos)
{
    game_object go(vector2d(1, 2));
    ASSERT_EQ(vector2d(1, 2), go.get_position());
}

TEST(accelerate, NegativeNos)
{
    game_object g(vector2d(1, 1));
    g.accelerate(vector2d(1, 1));
    g.move();
    ASSERT_EQ(g.get_position(), vector2d(2, 2));
}

TEST(changeDirection, NegativeNos)
{
    game_object g(vector2d(1, 1));
    g.change_direction(2);
    ASSERT_EQ(g.get_direction(), 2);
}

TEST(gravity, NegativeNos)
{
    world w;
    auto object = new game_object(vector2d(1, 1));
    w.add_game_object(object, object_type::movable);
    double gravity = 1;

    object->add_behavior([gravity](game_object* o) {
        o->accelerate(vector2d(0, gravity));
    });

    w.move();
    ASSERT_EQ(object->get_position(), vector2d(1, 2));
}

TEST(multipleBehaviors, NegativeNos)
{
    world w;
    auto object = new game_object(vector2d(1, 1));
    w.add_game_object(object, object_type::movable);
    double gravity = 1;

    object->add_behavior([gravity](game_object* o) {
        o->accelerate(vector2d(0, gravity));
    });

    object->add_behavior([](game_object* o) {
        o->accelerate(vector2d(1, 0));
    });

    w.move();
    ASSERT_EQ(object->get_position(), vector2d(2, 2));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};
