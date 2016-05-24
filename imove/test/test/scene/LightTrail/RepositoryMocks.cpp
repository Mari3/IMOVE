//
// Created by Wouter Posdijk on 24/05/16.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../../../src/util/Repository.h"

template <typename T>
class RepositoryMock : Repository<T> {
};