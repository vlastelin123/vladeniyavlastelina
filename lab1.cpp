#include <iostream>
#include <string>
#include <vector>

class Clock {
private:
    int day;
    int month;
    int year;
    int hours;
    int minutes;
    std::string dayOfWeek;

    bool isValidDate(int d, int m, int y) {
        if (y < 0) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1) return false;

        int maxDays = 31;
        if (m == 4 || m == 6 || m == 9 || m == 11) {
            maxDays = 30;
        } else if (m == 2) {
            maxDays = 28; // по условию в феврале всегда 28 дней
        }
        return d <= maxDays;
    }

    bool isValidTime(int h, int m) {
        return h >= 0 && h < 24 && m >= 0 && m < 60;
    }

    bool isValidDayOfWeek(const std::string& dow) {
        const std::vector<std::string> days = {
            "понедельник", "вторник", "среда", 
            "четверг", "пятница", "суббота", "воскресенье"
        };
        for (const auto& validDay : days) {
            if (dow == validDay) return true;
        }
        return false;
    }

    void normalizeTime() {
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours >= 24) {
            day += hours / 24;
            hours %= 24;
            normalizeDate();
        }
    }

    void normalizeDate() {
        while (day > daysInMonth(month, year)) {
            day -= daysInMonth(month, year);
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }

    int daysInMonth(int m, int y) {
        if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
        if (m == 2) return 28; // по условию
        return 31;
    }

    // Вспомогательная функция для получения следующего дня недели
    std::string getNextDayOfWeek(const std::string& currentDay) {
        const std::vector<std::string> days = {
            "понедельник", "вторник", "среда", 
            "четверг", "пятница", "суббота", "воскресенье"
        };
        
        for (size_t i = 0; i < days.size(); ++i) {
            if (currentDay == days[i]) {
                if (i == days.size() - 1) {
                    return days[0]; // воскресенье -> понедельник
                } else {
                    return days[i + 1];
                }
            }
        }
        return currentDay; // fallback
    }

public:
    // Конструктор по умолчанию
    Clock() : day(1), month(1), year(2000), hours(0), minutes(0), dayOfWeek("понедельник") {
        std::cout << "Создан объект с помощью конструктора по умолчанию" << std::endl;
    }

    // Конструктор полного заполнения
    Clock(int d, int m, int y, int h, int min, const std::string& dow) {
        setDate(d, m, y);
        setTime(h, min);
        setDayOfWeek(dow);
        std::cout << "Создан объект с помощью конструктора полного заполнения" << std::endl;
    }

    // Конструктор копирования
    Clock(const Clock& other) {
        day = other.day;
        month = other.month;
        year = other.year;
        hours = other.hours;
        minutes = other.minutes;
        dayOfWeek = other.dayOfWeek;
        std::cout << "Создан объект с помощью конструктора копирования" << std::endl;
    }

    // Деструктор
    ~Clock() {
        std::cout << "Деструктор вызван для объекта с датой: "
                  << day << "." << month << "." << year << std::endl;
    }

    // Сеттеры с проверками
    void setDate(int d, int m, int y) {
        if (isValidDate(d, m, y)) {
            day = d;
            month = m;
            year = y;
        } else {
            std::cout << "Ошибка: Некорректная дата" << std::endl;
        }
    }

    void setTime(int h, int m) {
        if (isValidTime(h, m)) {
            hours = h;
            minutes = m;
        } else {
            std::cout << "Ошибка: Некорректное время" << std::endl;
        }
    }

    void setDayOfWeek(const std::string& dow) {
        if (isValidDayOfWeek(dow)) {
            dayOfWeek = dow;
        } else {
            std::cout << "Ошибка: Некорректный день недели. Установлен понедельник." << std::endl;
            dayOfWeek = "понедельник";
        }
    }

    // Геттеры
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    std::string getDayOfWeek() const { return dayOfWeek; }

    // Метод добавления X минут
    void addMinutes(int x) {
        if (x < 0) {
            std::cout << "Ошибка: нельзя добавить отрицательное количество минут" << std::endl;
            return;
        }
        
        int daysToAdd = 0;
        minutes += x;
        
        // Обработка перехода через часы и дни
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        
        if (hours >= 24) {
            daysToAdd = hours / 24;
            hours %= 24;
        }
        
        // Добавляем дни и обновляем день недели
        if (daysToAdd > 0) {
            for (int i = 0; i < daysToAdd; ++i) {
                day++;
                dayOfWeek = getNextDayOfWeek(dayOfWeek);
                
                // Проверяем, не перешли ли на следующий месяц
                if (day > daysInMonth(month, year)) {
                    day = 1;
                    month++;
                    
                    if (month > 12) {
                        month = 1;
                        year++;
                    }
                }
            }
        }
    }

    // Вывод всей информации
    void printInfo() const {
        std::cout << "Дата: " << day << "." << month << "." << year << std::endl;
        std::cout << "Время: ";
        if (hours < 10) std::cout << "0";
        std::cout << hours << ":";
        if (minutes < 10) std::cout << "0";
        std::cout << minutes << std::endl;
        std::cout << "День недели: " << dayOfWeek << std::endl;
    }
};

int main() {
    // Демонстрация работы класса
    std::cout << "=== Создание объекта с конструктором по умолчанию ===" << std::endl;
    Clock clock1;
    clock1.printInfo();
    std::cout << std::endl;

    std::cout << "=== Создание объекта с конструктором полного заполнения ===" << std::endl;
    Clock clock2(15, 3, 2024, 14, 30, "пятница");
    clock2.printInfo();
    std::cout << std::endl;

    std::cout << "=== Создание объекта с конструктором копирования ===" << std::endl;
    Clock clock3(clock2);
    clock3.printInfo();
    std::cout << std::endl;

    std::cout << "=== Изменение дня недели ===" << std::endl;
    clock1.setDayOfWeek("воскресенье");
    std::cout << "Новый день недели: " << clock1.getDayOfWeek() << std::endl;
    std::cout << std::endl;

    std::cout << "=== Попытка установить некорректный день недели ===" << std::endl;
    clock1.setDayOfWeek("Некоторый день");
    std::cout << "Текущий день недели: " << clock1.getDayOfWeek() << std::endl;
    std::cout << std::endl;

    std::cout << "=== Добавление минут ===" << std::endl;
    std::cout << "До добавления: " << std::endl;
    clock2.printInfo();
    clock2.addMinutes(90); // добавляем 1 час 30 минут
    std::cout << "После добавления 90 минут: " << std::endl;
    clock2.printInfo();
    std::cout << std::endl;

    std::cout << "=== Добавление большого количества минут (переход через сутки) ===" << std::endl;
    Clock clock4(31, 12, 2023, 23, 30, "воскресенье");
    std::cout << "До добавления: " << std::endl;
    clock4.printInfo();
    clock4.addMinutes(150); // 2 часа 30 минут (переход через полночь и смену года)
    std::cout << "После добавления 150 минут: " << std::endl;
    clock4.printInfo();
    std::cout << std::endl;

    std::cout << "=== Тест добавления минут с переходом нескольких дней ===" << std::endl;
    Clock clock5(28, 2, 2024, 20, 0, "среда"); // 28 февраля
    std::cout << "До добавления: " << std::endl;
    clock5.printInfo();
    clock5.addMinutes(2880); // 48 часов = 2 суток
    std::cout << "После добавления 2880 минут (2 суток): " << std::endl;
    clock5.printInfo();
    std::cout << std::endl;

    std::cout << "=== Работа деструкторов при выходе из области видимости ===" << std::endl;
    // Деструкторы вызовутся автоматически при завершении main
    return 0;
}
