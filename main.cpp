#include <iostream>
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramEvent.h"
#include "Keeper.h"

void showMenu() {
    std::cout << "\n===== МЕНЮ УПРАВЛЕНИЯ КОНФЕРЕНЦИЕЙ =====" << std::endl;
    std::cout << "1. Добавить запись" << std::endl;
    std::cout << "2. Удалить запись" << std::endl;
    std::cout << "3. Редактировать запись" << std::endl;
    std::cout << "4. Показать все записи" << std::endl;
    std::cout << "5. Сохранить данные в файл" << std::endl;
    std::cout << "6. Загрузить данные из файла" << std::endl;
    std::cout << "7. Создать копию записи" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Ваш выбор: ";
}


int main() {
    setlocale(LC_ALL, "Russian"); // Для корректного отображения русского языка в консоли

    Keeper conferenceManager;
    int choice;

    while (true) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Пожалуйста, введите число." << std::endl;
            continue;
        }
        std::cin.ignore(32767, '\n'); // Чтобы при вводе названия не засчитался символ /n после выбора

        switch (choice) {
            case 1:
                conferenceManager.add();
                break;
            case 2:
                conferenceManager.removeMenu();
                break;
            case 3:
                conferenceManager.edit();
                break;
            case 4:
                conferenceManager.showAll();
                break;
            case 5:
                try {
                    conferenceManager.saveToFile();
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 6:
                try {
                    conferenceManager.loadFromFile();
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 7:
                try {
                    conferenceManager.copy();
                    break;
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