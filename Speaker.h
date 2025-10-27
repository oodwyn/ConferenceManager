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
    // Конструкторы и деструктор
    Speaker(); // Конструктор по умолчанию
    Speaker(std::string fullName, std::string org, std::string title, std::string anno); // Конструктор с параметрами
    Speaker(const Speaker& other); // Конструктор копирования
    ~Speaker(); // Деструктор

    // Методы Get (получение данных)
    std::string getFullName();
    std::string getOrganization();
    std::string getReportTitle();
    std::string getAnnotation();

    // Методы Set (установка данных)
    void setFullName(std::string fullName);
    void setOrganization(std::string org);
    void setReportTitle(std::string title);
    void setAnnotation(std::string anno);

    // Переопределенный метод для вывода информации
    void show() override;
};