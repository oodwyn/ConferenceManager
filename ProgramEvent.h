#pragma once
#include "ConferenceEntity.h"
#include <string>

class ProgramEvent : public ConferenceEntity {
private:
    std::string day;            // день
    std::string time;           // время выступления
    std::string eventName;      // наименование

public:
    ProgramEvent();
    ~ProgramEvent();

    void show() override;
};