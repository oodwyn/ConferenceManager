#pragma once
#include "ConferenceEntity.h"
#include <string> 

class Speaker : public ConferenceEntity {
private:
    std::string fullName;      // ФИО
    std::string organization;  // организация/ВУЗ
    std::string reportTitle;   // доклад
    std::string annotation;    // аннотация доклада

public:
    // Конструктор и деструктор
    Speaker();
    ~Speaker();

    // Переопределенный метод для вывода информации
    void show() override;
};