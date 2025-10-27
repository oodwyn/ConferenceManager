#pragma once
#include "ConferenceEntity.h"
#include <string>

class Administrator : public ConferenceEntity {
private:
    std::string fullName;         // ФИО
    std::string position;         // должность
    std::string responsibility;   // область ответственности

public:
    // Конструкторы и деструктор
    Administrator();
    Administrator(std::string fullName, std::string pos, std::string resp);
    Administrator(const Administrator& other);
    ~Administrator();

    // Методы Get
    std::string getFullName();
    std::string getPosition();
    std::string getResponsibility();

    // методы Set
    void setFullName(std::string fullName);
    void setPosition(std::string pos);
    void setResponsibility(std::string resp);

    void show() override;
};