#include <iostream>
#include "Streams.h"

int main() {

    auto value = Streams::readValue<int>();
    std::cout << value << std::endl;
    return 0;
}
