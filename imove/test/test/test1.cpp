//
// Created by Wouter Posdijk on 23/05/16.
//

#include <cmath>
#include "gtest/gtest.h"

TEST (SquareRootTest, PositiveNos) {
    EXPECT_EQ (18.0, sqrt (324.0));
    EXPECT_EQ (25.4, sqrt (645.16));
    EXPECT_EQ (50.332, sqrt (2533.310224));
}

TEST (AlternatingGPointTest, ChangeLocationAfterFive){

    //AlternatingGravityPointAction action();

}