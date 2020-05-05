//
// Created by Yan on 9/29/2017.
//

#ifndef PROJECT_COMMUNICATION_HPP
#define PROJECT_COMMUNICATION_HPP

#include <vector>
#include <string>
#include <fstream>

#define     LOG_DIR "./Log/"

namespace spider {
    class Communication {
    public:
        Communication();
        virtual ~Communication();
        void init(std::string);
        void parseBuffer();
        void addData(std::string read);

    private:
        std::string     buffer;
        std::string     fileName;
        std::fstream   log;
    };
}

#endif //PROJECT_COMMUNICATION_HPP
