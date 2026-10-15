// A tiny test framework.
//
//   TEST(name_of_the_test) { ... }       declares a test
//   EXPECT_TRUE(something)               the test fails if `something` is false
//   EXPECT_FALSE(something)              the test fails if `something` is true
//   EXPECT_EQUAL(actual, expected)       the test fails if the two values differ
#pragma once

#include <functional>
#include <sstream>
#include <string>

void registerTest(const std::string& name, std::function<void()> body);
void recordFailure(const std::string& message, const char* file, int line);

struct TestRegistration {
    TestRegistration(const std::string& name, std::function<void()> body) { registerTest(name, body); }
};

#define TEST(testName)                                                       \
    static void testName();                                                  \
    static TestRegistration testName##_registration(#testName, testName);    \
    static void testName()

#define EXPECT_TRUE(condition)                                               \
    do {                                                                     \
        if (!(condition)) {                                                  \
            recordFailure("expected " #condition " to be true", __FILE__, __LINE__); \
        }                                                                    \
    } while (false)

#define EXPECT_FALSE(condition)                                              \
    do {                                                                     \
        if (condition) {                                                     \
            recordFailure("expected " #condition " to be false", __FILE__, __LINE__); \
        }                                                                    \
    } while (false)

#define EXPECT_EQUAL(actual, expected)                                       \
    do {                                                                     \
        if (!((actual) == (expected))) {                                     \
            std::ostringstream message;                                      \
            message << "expected " #actual " to be " << (expected) << ", but it was " << (actual); \
            recordFailure(message.str(), __FILE__, __LINE__);                \
        }                                                                    \
    } while (false)
