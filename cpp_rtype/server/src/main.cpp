//
// Created by Sebastien on 08/01/2018.
//

#include <ctime>
#include<iostream>
#include "../Games/Rtype/Rtype.hpp"


int main() {
    std::srand(std::time(nullptr));

    const std::string ip = "127.0.0.1";
    int tcpPort = 12000;

    Rtype rt(ip, tcpPort);
    try {
        rt.run();
    } catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}