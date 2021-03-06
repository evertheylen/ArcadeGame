// Boost.Geometry Index
// Unit Test

// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <rtree/test_rtree.hpp>

int test_main(int, char* [])
{
    typedef bg::model::point<double, 3, bg::cs::cartesian> Indexable;
    testset::modifiers<Indexable>(bgi::dynamic_rstar(5, 2), std::allocator<int>());
    return 0;
}
