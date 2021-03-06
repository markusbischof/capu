/*
 * Copyright (C) 2012 BMW Car IT GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <gtest/gtest.h>
#include "capu/os/Math.h"

TEST(Math, abs1)
{
    capu::int_t val = 5;
    EXPECT_EQ(5, capu::Math::Abs(val));
    val = -5;
    EXPECT_EQ(5, capu::Math::Abs(val));
}

TEST(Math, abs2)
{
    capu::double_t val = 6;
    EXPECT_EQ(6, capu::Math::Abs(val));
    val = -6;
    EXPECT_EQ(6, capu::Math::Abs(val));
}

TEST(Math, abs3)
{
    capu::float_t val = 7;
    EXPECT_EQ(7, capu::Math::Abs(val));
    val = -7;
    EXPECT_EQ(7, capu::Math::Abs(val));
}

TEST(Math, PI)
{
    capu::float_t  val = capu::Math::PI_f;
    capu::double_t val2 = capu::Math::PI_d;
    EXPECT_TRUE(val > 3);
    EXPECT_TRUE(val2 > 3);
}

TEST(Math, Log2)
{
    EXPECT_FLOAT_EQ(3.321928f, capu::Math::Log2(10.f));
    EXPECT_NEAR(3.3219280948873644, capu::Math::Log2(10.0), 0.0000000000001);
}
