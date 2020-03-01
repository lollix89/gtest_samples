

#ifndef GTEST_SAMPLE_STREAMS_H
#define GTEST_SAMPLE_STREAMS_H


#include <iostream>

class Streams {

public:

    Streams() = default;

    template <class T>
    static T readValue(std::istream& stream = std::cin){

        std::cout << "input a value " << std::endl;
        T value;
        stream >> value;

        auto stream_state = [](std::ios& stream){
            std::cout << " good()=" << stream.good();
            std::cout << " eof()=" << stream.eof();
            std::cout << " fail()=" << stream.fail();
            std::cout << " bad()=" << stream.bad();
            std::cout << std::endl;
        };

        while(stream.fail()){
//        stream_state(stream);

            stream.clear();
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            auto c = stream.peek();
            if(c == EOF){
                throw std::runtime_error("EOF");
            }

            stream >> value;

//        stream_state(stream);
        }
        return value;
    }

};


#endif //GTEST_SAMPLE_STREAMS_H
