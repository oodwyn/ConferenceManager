#include "ProgramEvent.h"
#include <iostream>

ProgramEvent::ProgramEvent() {
}

ProgramEvent::~ProgramEvent() {
}

void ProgramEvent::show() {
    std::cout << "Событие программы" << std::endl;
}