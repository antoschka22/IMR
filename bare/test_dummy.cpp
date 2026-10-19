#include <gtest/gtest.h>

#include "core.hpp"

// Test fixture for mylib tests
class MyTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code that will be called before each test
    }

    void TearDown() override {
        // Cleanup code that will be called after each test
    }
};

// Test the add function
TEST_F(MyTest, Add) {
    // Assert
    EXPECT_EQ(9, imr_core::add(5,4) );
}
/*
// Test the a test which fails
TEST_F(MyTest, TrueFalse) {
    // Assert
    EXPECT_EQ(false, true );
}
*/