#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

using String = std::string;

// Структура для хранения данных об энергетическом напитке
struct EnergyBeverage {
    String Name;          // Название напитка
    String Flavor;        // Вкус напитка
    double Score;         // Оценка от 0.0 до 5.0
    String Analog;        // Похожий напиток (может быть пустым)
    double Cost;          // Цена в рублях
    EnergyBeverage* next; // Указатель на следующий элемент
};

// Прототипы функций
EnergyBeverage* createNode(String name, String flavor, double score, String analog, double cost);
void insertNode(EnergyBeverage* head, String name, String flavor, double score, String analog, double cost);
void showCatalog(EnergyBeverage* head);
void addNewItem(EnergyBeverage* head);
void sortByPrice(EnergyBeverage* head);
void displayUniqueFlavors(EnergyBeverage* head);
void groupByFlavor(EnergyBeverage* head);
void clearMemory(EnergyBeverage* head);

int main() {
    // Установка локали для корректного отображения русского текста
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    // Создание заголовочного элемента списка
    EnergyBeverage catalogHead;
    catalogHead.next = nullptr;
    
    // Заполнение начальными данными (не менее 6 элементов)
    insertNode(&catalogHead, "Red Bull", "Классический", 4.5, "Monster", 120.50);
    insertNode(&catalogHead, "Monster", "Зелёный", 4.2, "Red Bull", 115.00);
    insertNode(&catalogHead, "Burn", "Цитрусовый", 3.8, "", 95.00);
    insertNode(&catalogHead, "Adrenaline Rush", "Тропический", 4.0, "", 110.00);
    insertNode(&catalogHead, "Gorilla", "Кола", 3.5, "", 85.00);
    insertNode(&catalogHead, "Bullet", "Ягодный", 4.3, "", 105.00);
    insertNode(&catalogHead, "Flash", "Апельсиновый", 3.9, "Red Bull", 100.00);
    insertNode(&catalogHead, "Dynamite", "Лимонный", 4.1, "", 98.00);
    
    int userChoice = -1;
    
    // Основной цикл меню
    while (userChoice != 0) {
        std::cout << "\n╔══════════════════════════════════════╗" << std::endl;
        std::cout << "║      КАТАЛОГ ЭНЕРГЕТИЧЕСКИХ НАПИТКОВ     ║" << std::endl;
        std::cout << "╠══════════════════════════════════════╣" << std::endl;
        std::cout << "║  0. Завершение работы                ║" << std::endl;
        std::cout << "║  1. Отобразить весь каталог          ║" << std::endl;
        std::cout << "║  2. Добавить новый напиток           ║" << std::endl;
        std::cout << "║  3. Упорядочить по цене              ║" << std::endl;
        std::cout << "║  4. Показать уникальные вкусы        ║" << std::endl;
        std::cout << "║  5. Группировать по вкусам           ║" << std::endl;
        std::cout << "╚══════════════════════════════════════╝" << std::endl;
        std::cout << "\nВыберите действие (0-5): ";
        
        std::cin >> userChoice;
        
        // Проверка корректности ввода
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Пожалуйста, введите число от 0 до 5." << std::endl;
            continue;
        }
        
        switch (userChoice) {
            case 0:
                std::cout << "\nПрограмма завершает работу..." << std::endl;
                break;
            case 1:
                showCatalog(&catalogHead);
                break;
            case 2:
                addNewItem(&catalogHead);
                break;
            case 3:
                sortByPrice(&catalogHead);
                break;
            case 4:
                displayUniqueFlavors(&catalogHead);
                break;
            case 5:
                groupByFlavor(&catalogHead);
                break;
            default:
                std::cout << "Неверный выбор! Пожалуйста, введите число от 0 до 5." << std::endl;
        }
    }
    
    // Освобождение выделенной памяти
    clearMemory(&catalogHead);
    
    return 0;
}

// ============================================================================
// ФУНКЦИЯ: Создание нового узла списка
// ============================================================================
EnergyBeverage* createNode(String name, String flavor, double score, String analog, double cost) {
    EnergyBeverage* newNode = new EnergyBeverage;
    newNode->Name = name;
    newNode->Flavor = flavor;
    newNode->Score = score;
    newNode->Analog = analog;
    newNode->Cost = cost;
    newNode->next = nullptr;
    return newNode;
}

// ============================================================================
// ФУНКЦИЯ: Добавление узла в начало списка
// ============================================================================
void insertNode(EnergyBeverage* head, String name, String flavor, double score, String analog, double cost) {
    EnergyBeverage* newNode = createNode(name, flavor, score, analog, cost);
    newNode->next = head->next;
    head->next = newNode;
}

// ============================================================================
// ФУНКЦИЯ 1: Просмотр всего каталога (обязательная функция)
// ============================================================================
void showCatalog(EnergyBeverage* head) {
    EnergyBeverage* current = head->next;
    
    if (current == nullptr) {
        std::cout << "\n[ИНФОРМАЦИЯ] Каталог напитков пуст!" << std::endl;
        return;
    }
    
    std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                КАТАЛОГ ЭНЕРГЕТИЧЕСКИХ НАПИТКОВ               │" << std::endl;
    std::cout << "├─────────────────────────────────────────────────────────────┤" << std::endl;
    
    int counter = 1;
    while (current != nullptr) {
        std::cout << "│ " << std::setw(2) << counter << ". " << std::left << std::setw(20) << current->Name;
        std::cout << " │ Вкус: " << std::setw(15) << current->Flavor;
        std::cout << " │ Оценка: " << std::fixed << std::setprecision(1) << std::setw(4) << current->Score << "/5.0";
        std::cout << " │" << std::endl;
        
        std::cout << "│     ";
        std::cout << "Похожий: " << std::left << std::setw(20) 
                  << (current->Analog.empty() ? "отсутствует" : current->Analog);
        std::cout << " Цена: " << std::fixed << std::setprecision(2) 
                  << std::setw(7) << current->Cost << " руб.";
        std::cout << "       │" << std::endl;
        
        if (current->next != nullptr) {
            std::cout << "├─────────────────────────────────────────────────────────────┤" << std::endl;
        }
        
        current = current->next;
        counter++;
    }
    
    std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
}

// ============================================================================
// ФУНКЦИЯ 2: Создание нового элемента (обязательная функция)
// ============================================================================
void addNewItem(EnergyBeverage* head) {
    String name, flavor, analog;
    double score, cost;
    
    std::cout << "\n╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║          ДОБАВЛЕНИЕ НОВОГО ЭНЕРГЕТИЧЕСКОГО НАПИТКА      ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
    
    // Очистка буфера ввода
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Ввод названия
    std::cout << "Введите название напитка: ";
    std::getline(std::cin, name);
    
    // Ввод вкуса
    std::cout << "Введите вкус напитка: ";
    std::getline(std::cin, flavor);
    
    // Ввод оценки с проверкой
    bool validScore = false;
    while (!validScore) {
        std::cout << "Введите оценку (от 0.0 до 5.0): ";
        std::cin >> score;
        
        if (std::cin.fail() || score < 0.0 || score > 5.0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Оценка должна быть числом от 0.0 до 5.0." << std::endl;
        } else {
            validScore = true;
        }
    }
    
    // Очистка буфера для ввода строки
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Ввод похожего напитка
    std::cout << "Введите похожий напиток (оставьте пустым, если нет): ";
    std::getline(std::cin, analog);
    
    // Ввод цены с проверкой
    bool validCost = false;
    while (!validCost) {
        std::cout << "Введите цену (в рублях): ";
        std::cin >> cost;
        
        if (std::cin.fail() || cost < 0.0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Цена должна быть положительным числом." << std::endl;
        } else {
            validCost = true;
        }
    }
    
    // Добавление нового элемента в список
    insertNode(head, name, flavor, score, analog, cost);
    
    std::cout << "\n[УСПЕХ] Напиток \"" << name << "\" успешно добавлен в каталог!" << std::endl;
}

// ============================================================================
// ФУНКЦИЯ 3: Сортировка каталога по стоимости (вариантная функция 1)
// ============================================================================
void sortByPrice(EnergyBeverage* head) {
    if (head->next == nullptr || head->next->next == nullptr) {
        std::cout << "\n[ИНФОРМАЦИЯ] Недостаточно элементов для сортировки!" << std::endl;
        return;
    }
    
    // Сбор всех элементов в вектор для удобства сортировки
    std::vector<EnergyBeverage*> items;
    EnergyBeverage* current = head->next;
    
    while (current != nullptr) {
        items.push_back(current);
        current = current->next;
    }
    
    // Сортировка по возрастанию цены методом пузырька
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 0; i < items.size() - 1; i++) {
            if (items[i]->Cost > items[i + 1]->Cost) {
                std::swap(items[i], items[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
    
    // Восстановление связей в списке
    head->next = nullptr;
    // Добавляем элементы в обратном порядке, чтобы сохранить порядок возрастания
    for (int i = items.size() - 1; i >= 0; i--) {
        items[i]->next = head->next;
        head->next = items[i];
    }
    
    std::cout << "\n[УСПЕХ] Каталог отсортирован по цене (по возрастанию)!" << std::endl;
    showCatalog(head);
}

// ============================================================================
// ФУНКЦИЯ 4: Вывод уникальных вкусов (похожих нет) (вариантная функция 2)
// ============================================================================
void displayUniqueFlavors(EnergyBeverage* head) {
    std::vector<String> allFlavors;
    std::vector<String> flavorsWithAnalogs;
    
    EnergyBeverage* current = head->next;
    
    // Сбор информации о всех вкусах и вкусах с аналогами
    while (current != nullptr) {
        // Добавление вкуса в общий список, если его еще нет
        if (std::find(allFlavors.begin(), allFlavors.end(), current->Flavor) == allFlavors.end()) {
            allFlavors.push_back(current->Flavor);
        }
        
        // Если у напитка есть аналог, добавляем его вкус в отдельный список
        if (!current->Analog.empty()) {
            if (std::find(flavorsWithAnalogs.begin(), flavorsWithAnalogs.end(), current->Flavor) == flavorsWithAnalogs.end()) {
                flavorsWithAnalogs.push_back(current->Flavor);
            }
        }
        
        current = current->next;
    }
    
    // Определение уникальных вкусов (без аналогов)
    std::vector<String> uniqueFlavors;
    for (const auto& flavor : allFlavors) {
        if (std::find(flavorsWithAnalogs.begin(), flavorsWithAnalogs.end(), flavor) == flavorsWithAnalogs.end()) {
            uniqueFlavors.push_back(flavor);
        }
    }
    
    // Вывод результатов
    std::cout << "\n┌─────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│          УНИКАЛЬНЫЕ ВКУСЫ (БЕЗ АНАЛОГОВ)         │" << std::endl;
    std::cout << "├─────────────────────────────────────────────────┤" << std::endl;
    
    if (uniqueFlavors.empty()) {
        std::cout << "│          Уникальных вкусов не найдено           │" << std::endl;
    } else {
        std::cout << "│ Найдено уникальных вкусов: " << std::setw(3) << uniqueFlavors.size() 
                  << "                    │" << std::endl;
        std::cout << "├─────────────────────────────────────────────────┤" << std::endl;
        
        for (size_t i = 0; i < uniqueFlavors.size(); i++) {
            std::cout << "│ " << std::setw(2) << i + 1 << ". " << std::left << std::setw(35) 
                      << uniqueFlavors[i] << " │" << std::endl;
        }
    }
    
    std::cout << "└─────────────────────────────────────────────────┘" << std::endl;
}

// ============================================================================
// ФУНКЦИЯ 5: Вывод по вкусам с использованием переходов (вариантная функция 3)
// ============================================================================
void groupByFlavor(EnergyBeverage* head) {
    if (head->next == nullptr) {
        std::cout << "\n[ИНФОРМАЦИЯ] Каталог напитков пуст!" << std::endl;
        return;
    }
    
    // Группировка напитков по вкусам
    std::vector<String> flavors;
    std::vector<std::vector<EnergyBeverage*>> groupedItems;
    
    EnergyBeverage* current = head->next;
    
    while (current != nullptr) {
        // Поиск вкуса в списке
        auto it = std::find(flavors.begin(), flavors.end(), current->Flavor);
        
        if (it == flavors.end()) {
            // Новый вкус - создаем новую группу
            flavors.push_back(current->Flavor);
            std::vector<EnergyBeverage*> newGroup;
            newGroup.push_back(current);
            groupedItems.push_back(newGroup);
        } else {
            // Существующий вкус - добавляем в соответствующую группу
            size_t index = std::distance(flavors.begin(), it);
            groupedItems[index].push_back(current);
        }
        
        current = current->next;
    }
    
    // Последовательный вывод групп
    for (size_t i = 0; i < flavors.size(); i++) {
        std::cout << "\n┌─────────────────────────────────────────────────────────────┐" << std::endl;
        std::cout << "│ ВКУС: " << std::left << std::setw(47) << flavors[i] << "│" << std::endl;
        std::cout << "│ Напитков в категории: " << std::setw(34) << groupedItems[i].size() << "│" << std::endl;
        std::cout << "├─────────────────────────────────────────────────────────────┤" << std::endl;
        
        for (size_t j = 0; j < groupedItems[i].size(); j++) {
            EnergyBeverage* item = groupedItems[i][j];
            std::cout << "│ " << std::setw(2) << j + 1 << ". " << std::left << std::setw(25) << item->Name;
            std::cout << " Оценка: " << std::fixed << std::setprecision(1) << std::setw(4) << item->Score;
            std::cout << " Цена: " << std::fixed << std::setprecision(2) << std::setw(7) << item->Cost << " руб.";
            
            if (!item->Analog.empty()) {
                std::cout << " │" << std::endl;
                std::cout << "│     Похож на: " << std::left << std::setw(42) << item->Analog << "│" << std::endl;
            } else {
                std::cout << " │" << std::endl;
            }
            
            if (j < groupedItems[i].size() - 1) {
                std::cout << "├─────────────────────────────────────────────────────────────┤" << std::endl;
            }
        }
        
        std::cout << "└─────────────────────────────────────────────────────────────┘" << std::endl;
        
        // Переход к следующей группе (кроме последней)
        if (i < flavors.size() - 1) {
            std::cout << "\nДля продолжения нажмите Enter...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
}

// ============================================================================
// ФУНКЦИЯ: Освобождение выделенной памяти
// ============================================================================
void clearMemory(EnergyBeverage* head) {
    EnergyBeverage* current = head->next;
    
    while (current != nullptr) {
        EnergyBeverage* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    
    head->next = nullptr;
}
