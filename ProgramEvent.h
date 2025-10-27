#pragma once
#include "ConferenceEntity.h"
#include <string>

class ProgramEvent : public ConferenceEntity {
private:
    std::string day;            // день
    std::string time;           // время выступления
    std::string eventName;      // наименование

public:
    // Конструктор
    ProgramEvent();

    // Конструктор с параметрами
    ProgramEvent(std::string day, std::string time, std::string name);

    // Конструктор копирования
    ProgramEvent(const ProgramEvent& other);

    // Деструктор
    ~ProgramEvent();

    // Методы Get
    std::string getDay();
    std::string getTime();
    std::string getEventName();

    // Методы Set
    void setDay(std::string day);
    void setTime(std::string time);
    void setEventName(std::string name);

    void show() override;
};