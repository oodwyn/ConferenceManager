#pragma once
#include "ConferenceEntity.h"

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
    void showAll(); // Метод отображения всех объектов
};