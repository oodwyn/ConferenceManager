#include "Administrator.h"
#include <iostream>

// Конструктор
Administrator::Administrator() {
    this->fullName = "Не указано";
    this->position = "Не указана";
    this->responsibility = "Не указана";
    std::cout << "Конструктор по умолчанию для Administrator" << std::endl;
}

// Конструктор с параметрами
Administrator::Administrator(std::string fullName, std::string pos, std::string resp) {
    this->fullName = fullName;
    this->position = pos;
    this->responsibility = resp;
    std::cout << "Конструктор с парамерами для Administrator: " << this->fullName << std::endl;
}

// Конструктор копирования
Administrator::Administrator(const Administrator& other) {
    this->fullName = other.fullName;
    this->position = other.position;
    this->responsibility = other.responsibility;
    std::cout << "Конструктор копирования для Administrator: " << this->fullName << std::endl;
}

// Деструктор
Administrator::~Administrator() {
    std::cout << "Деструктор для Administrator: " << this->fullName << std::endl;
}

// Get методы

std::string Administrator::getFullName() {
    return this->fullName;
}
std::string Administrator::getPosition() {
    return this->position;
}
std::string Administrator::getResponsibility() {
    return this->responsibility;
}

// Set методы

void Administrator::setFullName(std::string fullName) {
    this->fullName = fullName;
}
void Administrator::setPosition(std::string pos) {
    this->position = pos;
}
void Administrator::setResponsibility(std::string resp) {
    this->responsibility = resp;
}

void Administrator::show(std::ostream& os) const {
    os << "-------------------------------------\n";
    os << "Тип:          Администратор\n";
    os << "ФИО:          " << this->fullName << "\n";
    os << "Должность:    " << this->position << "\n";
    os << "Зона ответ.:  " << this->responsibility << "\n";
    os << "-------------------------------------\n" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Administrator& administrator) {
    administrator.show(os); // Вызываем метод show, передавая ему поток вывода
    return os; // Возвращаем поток для цепочек вывода
}
