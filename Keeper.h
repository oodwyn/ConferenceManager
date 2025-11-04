#pragma once
#include "ConferenceEntity.h"
#include <string>

class Keeper {
private:
    ConferenceEntity** data; // Указатель на динамический массив указателей на базовый класс
    int size; // Текущее колво элементов в массиве
    int capacity; // Выделенное колво байт

public:
    Keeper(); // Конструктор
    ~Keeper(); // Деструктор

    void add(); // Метод добавления объекта
    void remove(); // Метод удаления объекта
    void removeMenu(); // Метод меню удаления
    void removeAll(); // Метод для полного удаления
    void showAll(); // Метод отображения всех объектов
    void edit(); // Метод для редактирования объекта

    void saveToFile();
    void loadFromFile();
};