#pragma once // Защита от двойного включения одного и того же файла
#include <ostream>
// Абстрактный базовый класс для всех сущностей конференции
class ConferenceEntity {
public:
    // Виртуальный деструктор
    virtual ~ConferenceEntity() = 0;

    // Виртуальный метод для отображения информации
    virtual void show(std::ostream& os) const = 0;
};