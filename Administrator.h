#pragma once
#include "ConferenceEntity.h"
#include <string>

class Administrator : public ConferenceEntity {
private:
    std::string fullName;         // ФИО
    std::string position;         // должность
    std::string responsibility;   // область ответственности

public:
    Administrator();
    ~Administrator();

    void show() override;
};