#include "Speaker.h"
#include <iostream>

// Конструкторы и деструктор

// Конструктор по умолчанию: инициализирует поля пустыми значениями
Speaker::Speaker() {
    this->fullName = "Не указано";
    this->organization = "Не указана";
    this->reportTitle = "Без названия";
    this->annotation = "Нет аннотации";
    std::cout << "Конструктор по умолчанию для Speaker" << std::endl;
}

// Конструктор с параметрами: принимает данные и записывает их в поля
Speaker::Speaker(std::string fullName, std::string org, std::string title, std::string anno) {
    this->fullName = fullName;
    this->organization = org;
    this->reportTitle = title;
    this->annotation = anno;
    std::cout << "Конструктор с параметрами для Speaker: " << this->fullName << std::endl;
}

// Конструктор копирования: создает копию другого объекта Speaker
Speaker::Speaker(const Speaker& other) {
    this->fullName = other.fullName;
    this->organization = other.organization;
    this->reportTitle = other.reportTitle;
    this->annotation = other.annotation;
    std::cout << "Конструктор копирования для Speaker: " << this->fullName << std::endl;
}

// Деструктор: вызывается при уничтожении объекта
Speaker::~Speaker() {
    std::cout << "Деструктор для Speaker: " << this->fullName << std::endl;
}

// Реализация методов Get

std::string Speaker::getFullName() {
    return this->fullName;
}
std::string Speaker::getOrganization() {
    return this->organization;
}
std::string Speaker::getReportTitle() {
    return this->reportTitle;
}
std::string Speaker::getAnnotation() {
    return this->annotation;
}

// Реализация методов Set

void Speaker::setFullName (std::string fullName) {
    this->fullName = fullName;
}
void Speaker::setOrganization(std::string org) {
    this->organization = org;
}
void Speaker::setReportTitle(std::string title) {
    this->reportTitle = title;
}
void Speaker::setAnnotation(std::string anno) {
    this->annotation = anno;
}

void Speaker::show() {
    std::cout << "-------------------------------------\n";
    std::cout << "Тип:         Выступающий\n";
    std::cout << "ФИО:         " << this->fullName << "\n";
    std::cout << "Организация: " << this->organization << "\n";
    std::cout << "Доклад:      " << this->reportTitle << "\n";
    std::cout << "Аннотация:   " << this->annotation << "\n";
    std::cout << "-------------------------------------\n" << std::endl;
}