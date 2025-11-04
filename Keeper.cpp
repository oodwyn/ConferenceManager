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
            this->data[i]->show(std::cout); // Для каждого типа вызывается нужный show()
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
    showAll();
    int index;
    std::cout << "Введите номер записи для удаления: ";
    std::cin >> index;
    std::cin.ignore(32767, '\n'); // Очистка буфера

    index--;

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

// Метод меню удаления
void Keeper::removeMenu() {
    if (this->size == 0) {
        std::cout << "Список пуст, удалять нечего" << std::endl;
        return;
    }
    int choice;
    std::cout << "\n--- Меню удаления ---\n";
    std::cout << "1. Удалить одну запись\n";
    std::cout << "2. Удалить ВСЕ записи\n";
    std::cout << "0. Назад\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    std::cin.ignore(32767, '\n'); // Очистка буфера

    switch (choice) {
        case 1:
            this->remove(); // Вызываем метод для удаления одной записи
            break;
        case 2:
            this->removeAll(); // Вызываем метод для удаления всех записей
            break;
        case 0:
            return;
        default:
            std::cout << "Неверный выбор" << std::endl;
    }
}

// Метод удаления всех записей
void Keeper::removeAll() {
    std::cout << "Вы уверены, что хотите удалить все записи?(yes/no): ";
    std::string confirmation;
    std::getline(std::cin, confirmation);

    if (confirmation == "yes" || confirmation == "YES") {
        // Удаляем каждый объект
        for (int i = 0; i < this->size; ++i) {
            delete this->data[i];
            this->data[i] = nullptr; // Обнуляем указатель
        }
        this->size = 0; // Сбрасываем счетчик
        std::cout << "Все записи были успешно удалены" << std::endl;
    } else {
        std::cout << "Удаление отменено" << std::endl;
    }
}

//Метод сохранения в файл
void Keeper::saveToFile() {

    // Открываем файл для записи
    std::string filename;
    std::cout << "Введите имя файла для сохранения: ";
    std::getline(std::cin, filename);

    // Если ничего не ввели
    if (filename.empty()) {
        filename = "conference_data.txt";
    }

    std::ofstream outFile(filename);
    // Проверяем файл на то, открылся ли
    if (!outFile.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл на запись: " + filename);
    }

    for (int i = 0; i < this->size; ++i) {
        if (auto sp = dynamic_cast<Speaker*>(this->data[i])) {
            outFile << "--- Speaker ---" << std::endl;
            outFile << "FullName: " << sp->getFullName() << std::endl;
            outFile << "Organization: " << sp->getOrganization() << std::endl;
            outFile << "ReportTitle: " << sp->getReportTitle() << std::endl;
            outFile << "Annotation: " << sp->getAnnotation() << std::endl;
        } else if (auto adm = dynamic_cast<Administrator*>(this->data[i])) {
            outFile << "--- Administrator ---" << std::endl;
            outFile << "FullName: " << adm->getFullName() << std::endl;
            outFile << "Position: " << adm->getPosition() << std::endl;
            outFile << "Responsibility: " << adm->getResponsibility() << std::endl;
        } else if (auto evt = dynamic_cast<ProgramEvent*>(this->data[i])) {
            outFile << "--- ProgramEvent ---" << std::endl;
            outFile << "Day: " << evt->getDay() << std::endl;
            outFile << "Time: " << evt->getTime() << std::endl;
            outFile << "EventName: " << evt->getEventName() << std::endl;
        }
        outFile << "--- End ---" << std::endl; // Конец записи
    }
    // Закрываем файл
    outFile.close();
    std::cout << "Данные успешно записаны в файл " << filename << std::endl;
}

void Keeper::loadFromFile() {
    // Открываем файл для чтения
    std::string filename;
    std::cout << "Введите имя файла для загрузки: ";
    std::getline(std::cin, filename);

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

    std::string line;
    while (std::getline(inFile, line)) {
        // Проверяем место и расширяем массив при необходимости
        if (this->size >= this->capacity) {
            int newCapacity = this->capacity * 2;
            ConferenceEntity** newData = new ConferenceEntity*[newCapacity];
            for (int j = 0; j < this->size; ++j) { newData[j] = this->data[j]; }
            delete[] this->data;
            this->data = newData;
            this->capacity = newCapacity;
        }

        if (line == "--- Speaker ---") {
            std::string fullName, org, title, anno;
            std::getline(inFile, fullName); // Читаем "FullName: ..."
            std::getline(inFile, org);
            std::getline(inFile, title);
            std::getline(inFile, anno);
            std::getline(inFile, line); // Читаем "--- End ---"

            // Убираем ключи, оставляя только значения
            fullName = fullName.substr(fullName.find(": ") + 2);
            org = org.substr(org.find(": ") + 2);
            title = title.substr(title.find(": ") + 2);
            anno = anno.substr(anno.find(": ") + 2);

            this->data[this->size++] = new Speaker(fullName, org, title, anno);

        } else if (line == "--- Administrator ---") {
            std::string fullName, pos, resp;
            std::getline(inFile, fullName);
            std::getline(inFile, pos);
            std::getline(inFile, resp);
            std::getline(inFile, line);

            fullName = fullName.substr(fullName.find(": ") + 2);
            pos = pos.substr(pos.find(": ") + 2);
            resp = resp.substr(resp.find(": ") + 2);

            this->data[this->size++] = new Administrator(fullName, pos, resp);

        } else if (line == "--- ProgramEvent ---") {
            std::string day, time, name;
            std::getline(inFile, day);
            std::getline(inFile, time);
            std::getline(inFile, name);
            std::getline(inFile, line);

            day = day.substr(day.find(": ") + 2);
            time = time.substr(time.find(": ") + 2);
            name = name.substr(name.find(": ") + 2);

            this->data[this->size++] = new ProgramEvent(day, time, name);
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

// Метод для копирования объекта
void Keeper::copy() {
    if (this->size == 0) {
        std::cout << "Список пуст, копировать нечего" << std::endl;
        return;
    }

    // Проверяем, есть ли место в массиве, и расширяем его, если нужно
    if (this->size >= this->capacity) {
        std::cout << "Вместимость хранилища недостаточна. Расширяем..." << std::endl;
        int newCapacity = this->capacity * 2;
        ConferenceEntity** newData = new ConferenceEntity*[newCapacity];
        for (int j = 0; j < this->size; ++j) { newData[j] = this->data[j]; }
        delete[] this->data;
        this->data = newData;
        this->capacity = newCapacity;
        std::cout << "Вместимость увеличена до " << this->capacity << std::endl;
    }

    showAll();
    int index;
    std::cout << "Введите номер записи, которую нужно скопировать: ";
    std::cin >> index;
    std::cin.ignore(32767, '\n');
    index--;

    if (index < 0 || index >= this->size) {
        std::cout << "Неверный номер записи" << std::endl;
        return;
    }

    // Определяем тип объекта для копирования
    ConferenceEntity* original = this->data[index];
    ConferenceEntity* newCopy = nullptr;

    std::cout << "\n--- Создание копии Записи #" << index + 1 << " ---" << std::endl;
    // Используем dynamic_cast, чтобы вызвать правильный конструктор копирования
    if (auto sp = dynamic_cast<Speaker*>(original)) {
        newCopy = new Speaker(*sp);
    } else if (auto adm = dynamic_cast<Administrator*>(original)) {
        newCopy = new Administrator(*adm);
    } else if (auto evt = dynamic_cast<ProgramEvent*>(original)) {
        newCopy = new ProgramEvent(*evt);
    }

    if (newCopy) {
        this->data[this->size] = newCopy; // Добавляем указатель на новую копию
        this->size++; // Увеличиваем счетчик
        std::cout << "Копия успешно создана и добавлена в конец списка" << std::endl;
    } else {
        std::cout << "Не удалось определить тип объекта для копирования" << std::endl;
    }
}