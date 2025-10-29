#include "Keeper.h"
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramEvent.h"
#include <iostream>
#include <string>

// Конструктор
Keeper::Keeper() {
    this->capacity = 4; // Нач. вместимость массива
    this->size = 0;
    this->data = new ConferenceEntity*[this->capacity]; // Выделяем память под массив указателей
    std::cout << "Keeper создан с вместимостью " << this->capacity << std::endl;
}

// Деструктор
Keeper::~Keeper() {
    // Удаляем объекты на которые указывают указатели в массиве
    for (int i = 0; i < this->size; i++) {
        delete this->data[i];
    }
    // Удаляем сам массив указателей
    delete[] this->data;
    std::cout << "Keeper удален, память очищена" << std::endl;
}

// Метод для вывода всех объектов
void Keeper::showAll() {
    std::cout << "\n Все записи: " << std::endl;
    if (this->size == 0) {
        std::cout << "Список пуст" << std::endl;
    } else {
        for (int i = 0; i < this->size; i++) {
            std:: cout << "--- Запись №" << i + 1 << " ---" << std::endl;
            this->data[i]->show(); // Для каждого типа вызывается нужный show()
        }
    }
    std::cout << "\n" << std::endl;
}

// Метод добавления объекта
void Keeper::add() {
    // Проверка и расширение массива
    if (this->size >= this->capacity) {
        std::cout << "Достигнут лимит массива, идет расширение!!!" << std::endl;
        int newCapacity = this->capacity * 2;
        ConferenceEntity** newData = new ConferenceEntity*[newCapacity];

        // Копируем указатели
        for (int i = 0; i < this->size; i++) {
            newData[i] = this->data[i];
        }

        delete[] this->data; // Удаляем старый массив
        this->data = newData; // Дата указывает на новый массив
        this->capacity = newCapacity;
        std::cout << "Вместимость увеличена до " << this->capacity << std::endl;
    }

    // Меню выбора типа объекта
    int choice;
    std::cout << "\nКакой объект добавить?\n";
    std::cout << "1. Выступающий\n";
    std::cout << "2. Администратор\n";
    std::cout << "3. Событие программы\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    std::cin.ignore(); // Очистка буфера ввода после std::cin

    // Создание объекта
    switch (choice) {
        case 1: {
            std::string fullName, org, title, anno;
            std::cout << "Введите ФИО: ";
            std::getline(std::cin, fullName);
            std::cout << "Введите организацию: ";
            std::getline(std::cin, org);
            std::cout << "Введите название доклада: ";
            std::getline(std::cin, title);
            std::cout << "Введите аннотацию: ";
            std::getline(std::cin, anno);
            // Создаем объект в динамической памяти
            this->data[this->size] = new Speaker(fullName, org, title, anno);
            break;
        }
        case 2: {
            std::string fullName, pos, resp;
            std::cout << "Введите ФИО: ";
            std::getline(std::cin, fullName);
            std::cout << "Введите должность: ";
            std::getline(std::cin, pos);
            std::cout << "Введите зону ответственности: ";
            std::getline(std::cin, resp);
            this->data[this->size] = new Administrator(fullName, pos, resp);
            break;
        }
        case 3: {
            std::string day, time, name;
            std::cout << "Введите день: ";
            std::getline(std::cin, day);
            std::cout << "Введите время: ";
            std::getline(std::cin, time);
            std::cout << "Введите наименование события: ";
            std::getline(std::cin, name);
            this->data[this->size] = new ProgramEvent(day, time, name);
            break;
        }
        default: {
            std::cout << "Неверный выбор" << std::endl;
            return; // Выходим из функции
        }
    }
    this->size++; // Увеличиваем счетчик элементов массива
    std::cout << "Объект успешно добавлен" << std::endl;
}

// Метод удаления объекта

void Keeper::remove() {
    if (this->size == 0) {
        std::cout << "Список пуст, удалять нечего" << std::endl;
        return;
    }

    showAll();
    int index;
    std::cout << "Введите номер записи для удаления: ";
    std::cin >> index;

    index--; //

    // Проверка корректности индекса
    if (index < 0 || index >= this->size) {
        std::cout << "Неверный номер записи!!" << std::endl;
        return;
    }

    // Освобождаем память из-под удаляемого объекта
    delete this->data[index];

    // Сдвигаем все последующие элементы на одну позицию
    for (int i = index; i < this->size - 1; i++) {
        this->data[i] = this->data[i + 1];
    }

    this->size--;
    std::cout << "Запись №" << index << " успешно удалена" << std::endl;
}