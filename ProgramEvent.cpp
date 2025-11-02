#include "ProgramEvent.h"
#include <iostream>

// Конструктор
ProgramEvent::ProgramEvent() {
    this->day = "Не указан";
    this->time = "Не указано";
    this->eventName = "Без названия";
    std::cout << "Конструктор по умолчанию для ProgramEvent" << std::endl;
}

// Конструктор с параметрами
ProgramEvent::ProgramEvent(std::string day, std::string time, std::string name) {
    this->day = day;
    this->time = time;
    this->eventName = name;
    std::cout << "Конструктор с параметрами для ProgramEvent: " << this->eventName << std::endl;
}

// Конструктор копирования
ProgramEvent::ProgramEvent(const ProgramEvent& other) {
    this->day = other.day;
    this->time = other.time;
    this->eventName = other.eventName;
    std::cout << "Вызван конструктор копирования для ProgramEvent: " << this->eventName << std::endl;
}

// Деструктор
ProgramEvent::~ProgramEvent() {
    std::cout << "Вызван деструктор для ProgramEvent: " << this->eventName << std::endl;
}

// Методы Get

std::string ProgramEvent::getDay() {
    return this->day;
}
std::string ProgramEvent::getTime() {
    return this->time;
}
std::string ProgramEvent::getEventName() {
    return this->eventName;
}

// Методы Set

void ProgramEvent::setDay(std::string day) {
    this->day = day;
}
void ProgramEvent::setTime(std::string time) {
    this->time = time;
}
void ProgramEvent::setEventName(std::string name) {
    this->eventName = name;
}

void ProgramEvent::show(std::ostream& os) const {
    os << "-------------------------------------\n";
    os << "Тип:           Событие программы\n";
    os << "День:          " << this->day << "\n";
    os << "Время:         " << this->time << "\n";
    os << "Наименование:  " << this->eventName << "\n";
    os << "-------------------------------------\n" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const ProgramEvent& programEvent) {
    programEvent.show(os); // Вызываем метод show, передавая ему поток вывода
    return os; // Возвращаем поток для цепочек вывода
}