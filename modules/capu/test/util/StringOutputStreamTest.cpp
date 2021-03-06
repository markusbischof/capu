/*
 * Copyright (C) 2013 BMW Car IT GmbH
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

#include "StringOutputStreamTest.h"

namespace capu
{
    StringOutputStreamTest::StringOutputStreamTest()
    {
    }

    StringOutputStreamTest::~StringOutputStreamTest()
    {
    }

    void StringOutputStreamTest::SetUp()
    {
    }

    void StringOutputStreamTest::TearDown()
    {
    }

    TEST_F(StringOutputStreamTest, WriteFloat)
    {
        outputStream << 47.11f;
        outputStream.flush();
        EXPECT_STREQ("47.110001", outputStream.c_str());
        EXPECT_EQ(9U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, WriteInt32)
    {
        outputStream << 4711;
        outputStream.flush();
        EXPECT_STREQ("4711", outputStream.c_str());
        EXPECT_EQ(4U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, WriteUInt32)
    {
        outputStream << 4711u;
        outputStream.flush();
        EXPECT_STREQ("4711", outputStream.c_str());
        EXPECT_EQ(4U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, WriteString)
    {
        outputStream << String("Hello World");
        outputStream.flush();
        EXPECT_STREQ("Hello World", outputStream.c_str());
        EXPECT_EQ(11U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, WriteBool)
    {
        outputStream << true;
        outputStream.flush();
        EXPECT_STREQ("1", outputStream.c_str());
        EXPECT_EQ(1U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, WriteCharArray)
    {
        outputStream << "Hello World";
        outputStream.flush();
        EXPECT_STREQ("Hello World", outputStream.c_str());
        EXPECT_EQ(11U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, WriteUInt16)
    {
        outputStream << static_cast<uint16_t>(4711);
        outputStream.flush();
        EXPECT_STREQ("4711", outputStream.c_str());
        EXPECT_EQ(4U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, WriteGuid)
    {
        outputStream << Guid("AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE");
        outputStream.flush();
        EXPECT_STREQ("AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE", outputStream.c_str());
        EXPECT_EQ(36U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, WriteData)
    {
        outputStream.write("Some data to write", 18);
        outputStream.flush();
        EXPECT_STREQ("Some data to write", outputStream.c_str());
        EXPECT_EQ(18U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, Flush)
    {
        outputStream << 4711;
        outputStream.flush();
        EXPECT_EQ(CAPU_OK, outputStream.flush());
        EXPECT_EQ(4U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, MultipleData)
    {
        outputStream << 4711 << " " << 47.11f << " " << "Hello World" << " " << true;
        outputStream.flush();
        EXPECT_STREQ("4711 47.110001 Hello World 1", outputStream.c_str());
        EXPECT_EQ(28U, outputStream.length());
    }

    TEST_F(StringOutputStreamTest, Resize)
    {
        outputStream << "Exactly 16 chars";
        outputStream.flush();
        EXPECT_STREQ("Exactly 16 chars", outputStream.c_str());
        EXPECT_EQ(16U, outputStream.length());
    }
}