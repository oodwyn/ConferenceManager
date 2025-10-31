#include "Keeper.h"
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramEvent.h"
#include <iostream>
#include <string>
#include <fstream> // для работы с файловыми потоками
#include <stdexcept> // для обработки исключений

// Конструктор
Keeper::Keeper() {
    this->capacity = 4; // Нач вместимость массива
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

void Keeper::saveToFile(const std::string& filename) {

    // Открываем файл для записи
    std::ofstream outFile(filename);

    // Проверяем файл на то, открылся ли
    if (!outFile.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл на запись: " + filename);
    }

    // Запись общего колва объектов
    outFile << this->size << std::endl;

    for (int i = 0; i < this->size; i++) {
        // dynamic_cast - проверяем, является ли объект представителем дочернего класса
        if (auto sp = dynamic_cast<Speaker*>(this->data[i])) {
            outFile << 1 << std::endl; // Маркер "1" для Speaker
            outFile << sp->getFullName() << std::endl;
            outFile << sp->getOrganization() << std::endl;
            outFile << sp->getReportTitle() << std::endl;
            outFile << sp->getAnnotation() << std::endl;
        } else if (auto adm = dynamic_cast<Administrator*>(this->data[i])) {
            outFile << 2 << std::endl; // Маркер "2" для Administrator
            outFile << adm->getFullName() << std::endl;
            outFile << adm->getPosition() << std::endl;
            outFile << adm->getResponsibility() << std::endl;
        } else if (auto evt = dynamic_cast<ProgramEvent*>(this->data[i])) {
            outFile << 3 << std::endl; // Маркер "3" для ProgramEvent
            outFile << evt->getDay() << std::endl;
            outFile << evt->getTime() << std::endl;
            outFile << evt->getEventName() << std::endl;
        }
    }

    // Закрываем файл
    outFile.close();
    std::cout << "Данные успешно записаны в файл " << filename << std::endl;
}

void Keeper::loadFromFile(const std::string& filename) {
    // Открываем файл для чтения
    std::ifstream inFile(filename);

    // Если файл не открылся
    if (!inFile.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл для чтения: " + filename);
    }

    // Очищаем данные перед загрузкой
    for (int i = 0; i < this->size; i++) {
        delete this->data[i];
    }
    this->size = 0;

    // Читаем общее колво записей
    int recordCount;
    inFile >> recordCount;
    if (inFile.fail()) {
        throw std::runtime_error("Ошибка: некорректный формат файла");
        return;
    }

    inFile.ignore(); // Убираем символ /n после recordCount

    // Читаем каждую запись
    for (int i = 0; i < recordCount; i++) {
        if (this->size >= this->capacity) {
            std::cout << "Вместимость хранилища недостаточна!! Расширяем..." << std::endl;
            int newCapacity = this->capacity * 2;
            ConferenceEntity** newData = new ConferenceEntity*[newCapacity];

            for (int j = 0; j < this->size; j++) {
                newData[j] = this->data[j];
            }

            delete[] this->data;
            this->data = newData;
            this->capacity = newCapacity;
            std::cout << "Вместимость увеличена до " << this->capacity << std::endl;
        }

        int type;
        inFile >> type;
        if (inFile.fail()) continue; // Если не удалось прочитать тип, пропускаем
        inFile.ignore();

        switch (type) {
            case 1: { // Загружаем Speaker
                std::string fullName, org, title, anno;
                std::getline(inFile, fullName);
                std::getline(inFile, org);
                std::getline(inFile, title);
                std::getline(inFile, anno);
                this->data[this->size] = new Speaker(fullName, org, title, anno);
                this->size++;
                break;
            }
            case 2: { // Загружаем Administrator
                std::string fullName, pos, resp;
                std::getline(inFile, fullName);
                std::getline(inFile, pos);
                std::getline(inFile, resp);
                this->data[this->size] = new Administrator(fullName, pos, resp);
                this->size++;
                break;
            }
            case 3: { // Загружаем ProgramEvent
                std::string day, time, name;
                std::getline(inFile, day);
                std::getline(inFile, time);
                std::getline(inFile, name);
                this->data[this->size] = new ProgramEvent(day, time, name);
                this->size++;
                break;
            }
            default: // Если в файле какой-то неизвестный тип, пропускаем его
                continue;
        }
    }
    // Закрываем файл
    inFile.close();
    std::cout << "Данные успешно загружены из файла " << filename << std::endl;
}

void Keeper::edit() {
    if (this->size == 0) {
        std::cout << "Список пуст, редактировать нечего" << std::endl;
        return;
    }

    showAll();

    int index;
    std::cout << "Введите номер записи для редактирования: ";
    std::cin >> index;
    index--;

    if (index < 0 || index >= this->size) {
        std::cout << "Неверное номер записи" << std::endl;
        return;
    }

    // Получаем указатель на выбранный объект
    ConferenceEntity* current_obj = this->data[index];
    std::cout << "\n--- Редактирование записи № " << index + 1 << " ---" << std::endl;

    // С помощью dynamic_cast определяем тип объекта
    if (auto sp = dynamic_cast<Speaker*>(current_obj)) {
        int choice;
        std::string newValue;

        std::cout << "Что вы хотите изменить?\n";
        std::cout << "1. ФИО\n";
        std::cout << "2. Организация\n";
        std::cout << "3. Название доклада\n";
        std::cout << "4. Аннотация\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore(); // Очистка буфера

        switch (choice) {
            case 1:
                std::cout << "Введите новое ФИО: ";
                std::getline(std::cin, newValue);
                sp->setFullName(newValue);
                break;
            case 2:
                std::cout << "Введите новую организацию: ";
                std::getline(std::cin, newValue);
                sp->setOrganization(newValue);
                break;
            case 3:
                std::cout << "Введите новое название доклада: ";
                std::getline(std::cin, newValue);
                sp->setReportTitle(newValue);
                break;
            case 4:
                std::cout << "Введите новую аннотацию: ";
                std::getline(std::cin, newValue);
                sp->setAnnotation(newValue);
                break;
            case 0:
                return;
            default:
                std::cout << "!! Неверный выбор." << std::endl;
                return;
        }
    } else if (auto adm = dynamic_cast<Administrator*>(current_obj)) {
        int choice;
        std::string newValue;

        std::cout << "Что вы хотите изменить?\n";
        std::cout << "1. ФИО\n";
        std::cout << "2. Должность\n";
        std::cout << "3. Зона ответственности\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Введите новое ФИО: ";
                std::getline(std::cin, newValue);
                adm->setFullName(newValue);
                break;
            case 2:
                std::cout << "Введите новую должность: ";
                std::getline(std::cin, newValue);
                adm->setPosition(newValue);
                break;
            case 3:
                std::cout << "Введите новую зону ответственности: ";
                std::getline(std::cin, newValue);
                adm->setResponsibility(newValue);
                break;
            case 0:
                return;
            default:
                std::cout << "!! Неверный выбор." << std::endl;
                return;
        }
    } else if (auto evt = dynamic_cast<ProgramEvent*>(current_obj)) {
            int choice;
            std::string newValue;

            std::cout << "Что вы хотите изменить?\n";
            std::cout << "1. День\n";
            std::cout << "2. Время\n";
            std::cout << "3. Наименование\n";
            std::cout << "0. Назад\n";
            std::cout << "Ваш выбор: ";
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1:
                    std::cout << "Введите новый день: ";
                    std::getline(std::cin, newValue);
                    evt->setDay(newValue);
                    break;
                case 2:
                    std::cout << "Введите новое время: ";
                    std::getline(std::cin, newValue);
                    evt->setTime(newValue);
                    break;
                case 3:
                    std::cout << "Введите новое наименование: ";
                    std::getline(std::cin, newValue);
                    evt->setEventName(newValue);
                    break;
                case 0:
                    return;
                default:
                    std::cout << "!! Неверный выбор." << std::endl;
                    return;
            }
    }
    std::cout << "Запись успешно обновлена." << std::endl;
}