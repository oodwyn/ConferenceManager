#include <iostream>
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramEvent.h"

int main() {
    setlocale(LC_ALL, "Russian"); // Для корректного отображения русского языка в консоли

    std::cout << "Тестирование 2\n" << std::endl;

    // Создаем объект через конструктор с параметрами
    Speaker mainSpeaker("Иванов Иван Иванович", "МГУ", "Квантовые вычисления", "Обзор...");

    // Создаем второй объект как копию первого
    Speaker copiedSpeaker = mainSpeaker;

    // Меняем данные у копии через set-методы
    copiedSpeaker.setFullName("Петров Петр Петрович");
    copiedSpeaker.setReportTitle("Нейронные сети");

    // Выводим информацию об обоих объектах
    std::cout << "\nИнформация об объектах\n" << std::endl;
    mainSpeaker.show();
    copiedSpeaker.show();

    // Создаем остальные объекты для проверки
    Administrator mainAdmin("Сидорова Анна Викторовна", "Организатор", "Регистрация участников");
    mainAdmin.show();

    ProgramEvent mainEvent("День 1", "10:00", "Открытие конференции");
    mainEvent.show();

    std::cout << "\nЗавершение программы, вызов деструкторов\n" << std::endl;

    return 0;
}