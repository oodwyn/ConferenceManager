#include <iostream>
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramEvent.h"
#include "Keeper.h"

void showMenu() {
    std::cout << "\n===== МЕНЮ УПРАВЛЕНИЯ КОНФЕРЕНЦИЕЙ =====" << std::endl;
    std::cout << "1. Добавить запись" << std::endl;
    std::cout << "2. Удалить запись" << std::endl;
    // --- НОВЫЙ ПУНКТ ---
    std::cout << "3. Редактировать запись" << std::endl;
    std::cout << "4. Показать все записи" << std::endl;
    std::cout << "5. Сохранить данные в файл" << std::endl;
    std::cout << "6. Загрузить данные из файла" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Ваш выбор: ";
}


int main() {
    setlocale(LC_ALL, "Russian"); // Для корректного отображения русского языка в консоли

    std::cout << "Тестирование 4\n" << std::endl;
    Keeper conferenceManager;
    const std::string filename = "conference_data.txt";
    int choice;

    try {
        conferenceManager.loadFromFile(filename);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << " Создан пустой список." << std::endl;
    }

    while (true) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Пожалуйста, введите число." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                conferenceManager.add();
                break;
            case 2:
                conferenceManager.remove();
                break;
                // --- НОВЫЙ CASE ---
            case 3:
                conferenceManager.edit();
                break;
            case 4:
                conferenceManager.showAll();
                break;
            case 5:
                try {
                    conferenceManager.saveToFile(filename);
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 6:
                try {
                    conferenceManager.loadFromFile(filename);
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 0:
                std::cout << "Завершение работы программы..." << std::endl;
                return 0;
            default:
                std::cout << "Неверный пункт меню. Попробуйте снова." << std::endl;
                break;
        }
    }
}