#include <iostream>
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramEvent.h"
#include "Keeper.h"

int main() {
    setlocale(LC_ALL, "Russian"); // Для корректного отображения русского языка в консоли

    std::cout << "Тестирование 3\n" << std::endl;
    Keeper conferenceManager; // Создаем контейнер

    // Добавление тест
    std::cout << "\n--- Добавляю первого выступающего ---\n";
    conferenceManager.add();

    std::cout << "\n--- Добавляю администратора ---\n";
    conferenceManager.add();

    // Вывод
    conferenceManager.showAll();

    // Удаление тест
    std::cout << "\n--- Удаляю запись ---\n";
    conferenceManager.remove();

    // Вывод
    conferenceManager.showAll();

    std::cout << "\n--- Программа завершает работу ---" << std::endl;

    return 0;
}