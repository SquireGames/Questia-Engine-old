#include "QENG/Test/Test.h"

#include "gtest/gtest.h"
#include "QENG/math/FixedVector.h"

TEST(FixedVector, op_equals)
{
	qe::FixedVector<int, 3> v1 (1, 2, 3);
	qe::FixedVector<int, 3> v2 (1, 2, 3);
	qe::FixedVector<int, 3> v3 (1, 2, 1);

	EXPECT_EQ(true, (v1 == v2));
	EXPECT_EQ(false, (v1 == v3));
}

TEST(FixedVector, op_plus)
{
	qe::FixedVector<int, 3> v1 (1, 2, 3);
	qe::FixedVector<int, 3> v2 (2, 3, 4);
	qe::FixedVector<int, 3> v3 (3, 5, 7);

	EXPECT_EQ(v3, v1 + v2);
}



