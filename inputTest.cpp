#include <fstream>
#include <cmath>
#include "gtest/gtest.h"
#include "Streams.h"

TEST(readValue, givenInput_outputExpectedValue){

    std::istringstream input_with_some_invalid_values("!!!46\n@\n5");
    EXPECT_EQ(Streams::readValue<int>(input_with_some_invalid_values), 5);
    EXPECT_EQ(input_with_some_invalid_values.peek(), EOF);

    // swap input_with_some_invalid_values with a new one
    std::istringstream("ciao@\n").swap(input_with_some_invalid_values);
    EXPECT_EQ(Streams::readValue<std::string>(input_with_some_invalid_values), "ciao@");
    EXPECT_EQ(input_with_some_invalid_values.peek(), '\n');

    // swap input_with_some_invalid_values with a new one
    std::istringstream("!32.1\n").swap(input_with_some_invalid_values);
    try{
        Streams::readValue<int>(input_with_some_invalid_values);
    }catch(const std::runtime_error &ex){
        EXPECT_EQ(std::string(ex.what()), "EOF");
    }
    EXPECT_EQ(input_with_some_invalid_values.peek(), EOF);

    // swap input_with_some_invalid_values with a new one
    std::istringstream("32.1\n").swap(input_with_some_invalid_values);
    EXPECT_EQ(Streams::readValue<int>(input_with_some_invalid_values), 32);
    EXPECT_EQ(input_with_some_invalid_values.peek(), '.');

    // swap input_with_some_invalid_values with a new one
    std::istringstream("   32.1 4\n").swap(input_with_some_invalid_values);
    EXPECT_EQ(Streams::readValue<int>(input_with_some_invalid_values), 32);
    EXPECT_EQ(input_with_some_invalid_values.peek(), '.');

    // swap input_with_some_invalid_values with a new one
    std::istringstream("-32.1 4\n7").swap(input_with_some_invalid_values);
    EXPECT_EQ(Streams::readValue<unsigned int>(input_with_some_invalid_values), std::pow(2,32) -32);
    EXPECT_EQ(input_with_some_invalid_values.peek(), '.');

    // swap input_with_some_invalid_values with a new one
    std::istringstream("@-32.1 4\n7").swap(input_with_some_invalid_values);
    EXPECT_EQ(Streams::readValue<unsigned int>(input_with_some_invalid_values), 7);
    EXPECT_EQ(input_with_some_invalid_values.peek(), EOF);

    // swap input_with_some_invalid_values with a new one
    std::istringstream("@-32.1 4\n7").swap(input_with_some_invalid_values);
    EXPECT_EQ(Streams::readValue<std::string>(input_with_some_invalid_values), "@-32.1");
    EXPECT_EQ(input_with_some_invalid_values.peek(), ' ');

    // swap input_with_some_invalid_values with a new one
    std::istringstream("@-22.1\n 4\n7").swap(input_with_some_invalid_values);
    EXPECT_EQ(Streams::readValue<std::string>(input_with_some_invalid_values), "@-22.1");
    EXPECT_EQ(input_with_some_invalid_values.peek(), '\n');

    // swap input_with_some_invalid_values with a new one
    std::istringstream("@-22.1\n 4\n7").swap(input_with_some_invalid_values);
    EXPECT_FLOAT_EQ(Streams::readValue<float>(input_with_some_invalid_values), 4.f);
    EXPECT_EQ(input_with_some_invalid_values.peek(), '\n');

    // swap input_with_some_invalid_values with a new one
    std::istringstream("-22.1000002@\n 4\n7").swap(input_with_some_invalid_values);
    EXPECT_FLOAT_EQ(Streams::readValue<double>(input_with_some_invalid_values), -22.1000002);
    EXPECT_EQ(input_with_some_invalid_values.peek(), '@');

    // swap input_with_some_invalid_values with a new one
    std::istringstream("-@\n 4.31\n7").swap(input_with_some_invalid_values);
    EXPECT_FLOAT_EQ(Streams::readValue<double>(input_with_some_invalid_values), 4.31);
    EXPECT_EQ(input_with_some_invalid_values.peek(), '\n');
}