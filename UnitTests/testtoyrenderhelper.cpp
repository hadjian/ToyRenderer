#include <toyrenderhelper.h>
#include <gtest/gtest.h>

#include <limits>
#include <cstdio>
using namespace std;


TEST(RenderHelperTest, Rotate) {
  float d=20.0;
  ToyRotationMatrix rot(d);
  EXPECT_FLOAT_EQ(1.0, rot(0,0)); EXPECT_FLOAT_EQ(   0.0, rot(0,1)); EXPECT_FLOAT_EQ(    0.0, rot(0,2)); EXPECT_FLOAT_EQ(0.0, rot(0,3));
  EXPECT_FLOAT_EQ(0.0, rot(1,0)); EXPECT_FLOAT_EQ(cos(d), rot(1,1)); EXPECT_FLOAT_EQ(-sin(d), rot(1,2)); EXPECT_FLOAT_EQ(0.0, rot(1,3));
  EXPECT_FLOAT_EQ(0.0, rot(2,0)); EXPECT_FLOAT_EQ(sin(d), rot(2,1)); EXPECT_FLOAT_EQ( cos(d), rot(2,2)); EXPECT_FLOAT_EQ(0.0, rot(2,3));
  EXPECT_FLOAT_EQ(0.0, rot(3,0)); EXPECT_FLOAT_EQ(   0.0, rot(3,1)); EXPECT_FLOAT_EQ(    0.0, rot(3,2)); EXPECT_FLOAT_EQ(1.0, rot(3,3));

  rot.makeIdentity();
  rot.rotateY(d);
  EXPECT_FLOAT_EQ( cos(d), rot(0,0)); EXPECT_FLOAT_EQ(0.0, rot(0,1)); EXPECT_FLOAT_EQ(sin(d), rot(0,2)); EXPECT_FLOAT_EQ(0.0, rot(0,3));
  EXPECT_FLOAT_EQ(    0.0, rot(1,0)); EXPECT_FLOAT_EQ(1.0, rot(1,1)); EXPECT_FLOAT_EQ(   0.0, rot(1,2)); EXPECT_FLOAT_EQ(0.0, rot(1,3));
  EXPECT_FLOAT_EQ(-sin(d), rot(2,0)); EXPECT_FLOAT_EQ(0.0, rot(2,1)); EXPECT_FLOAT_EQ(cos(d), rot(2,2)); EXPECT_FLOAT_EQ(0.0, rot(2,3));
  EXPECT_FLOAT_EQ(    0.0, rot(3,0)); EXPECT_FLOAT_EQ(0.0, rot(3,1)); EXPECT_FLOAT_EQ(   0.0, rot(3,2)); EXPECT_FLOAT_EQ(1.0, rot(3,3));

  rot.makeIdentity();
  rot.rotateZ(d);
  EXPECT_FLOAT_EQ(cos(d), rot(0,0)); EXPECT_FLOAT_EQ(-sin(d), rot(0,1)); EXPECT_FLOAT_EQ(0.0, rot(0,2)); EXPECT_FLOAT_EQ(0.0, rot(0,3));
  EXPECT_FLOAT_EQ(sin(d), rot(1,0)); EXPECT_FLOAT_EQ( cos(d), rot(1,1)); EXPECT_FLOAT_EQ(0.0, rot(1,2)); EXPECT_FLOAT_EQ(0.0, rot(1,3));
  EXPECT_FLOAT_EQ(   0.0, rot(2,0)); EXPECT_FLOAT_EQ(    0.0, rot(2,1)); EXPECT_FLOAT_EQ(1.0, rot(2,2)); EXPECT_FLOAT_EQ(0.0, rot(2,3));
  EXPECT_FLOAT_EQ(   0.0, rot(3,0)); EXPECT_FLOAT_EQ(    0.0, rot(3,1)); EXPECT_FLOAT_EQ(0.0, rot(3,2)); EXPECT_FLOAT_EQ(1.0, rot(3,3));

}

