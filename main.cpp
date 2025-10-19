#include <iostream>
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramEvent.h"

int main() {
    setlocale(LC_ALL, "Russian"); // Для корректного отображения русского языка в консоли

    // Тестовое создание объектов
    Speaker testSpeaker;
    Administrator testAdmin;
    ProgramEvent testEvent;

    std::cout << "\nПроверка вызова методов show():" << std::endl;
    testSpeaker.show();
    testAdmin.show();
    testEvent.show();

    std::cout << "\n\nПрограмма завершила работу. Нажмите Enter для выхода.";
    std::cin.get(); 

    return 0;
}