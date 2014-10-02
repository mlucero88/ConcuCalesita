#include <iostream>
#include "Logger.h"

int main(int argc, char** argv) {

    string message1 = "logg message 1 ...";
    int    nNum     = 10;
    Logger::getLogger()->Log("message to be logged");
    Logger::getLogger()->Log(message1);

    LOGGER->Log(" Message is:%s Number is:%d",message1.c_str(), nNum);

    Logger::Estado estadoNinio = Logger::COLA_BOLETERIA;
    LOGGER->Log("nombreNene", estadoNinio);
	return 0;
}
