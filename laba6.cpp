#include <iostream>
#include <cstdlib>   

using namespace std;

// Инициализация данных матрицы
void initializeTable(int** dataTable, int startRows, int startCols, int finalRows, int finalCols, int paramC, int paramD) {
    // Заполняем начальный блок
    for (int row = 0; row < startRows; ++row) {
        for (int col = 0; col < startCols; ++col) {
            dataTable[row][col] = (-1 + row) * paramC + (1 + col) * paramD;
        }
    }

    // Заполняем расширенные столбцы в начальных строках
    for (int row = 0; row < startRows; row++) {
        for (int col = startCols; col < finalCols; col++) {
            dataTable[row][col] = (-1 + row) * paramC + (col - startCols + 1) * paramD;
        }
    }

    // Заполняем добавленные строки
    for (int row = startRows; row < finalRows; row++) {
        for (int col = 0; col < finalCols; col++) {
            dataTable[row][col] = (row - startRows + 1) * paramC + (col - startCols + 1) * paramD;
        }
    }
}

// Поиск столбцов с нулевыми элементами
int* locateEmptyColumns(int** dataTable, int rowCount, int colCount, int* emptyCount) {
    int* emptyColumnIndexes = NULL;
    *emptyCount = 0;

    for (int col = 0; col < colCount; col++) {
        bool foundZero = false;
        for (int row = 0; row < rowCount; row++) {
            if (dataTable[row][col] == 0) {
                foundZero = true;
                break;
            }
        }
        if (foundZero) {
            emptyColumnIndexes = (int*)realloc(emptyColumnIndexes, (*emptyCount + 1) * sizeof(int));
            emptyColumnIndexes[*emptyCount] = col;
            (*emptyCount)++;
        }
    }

    if (*emptyCount == 0) {
        free(emptyColumnIndexes);
        return NULL;
    }

    return emptyColumnIndexes;
}

// Удаление отмеченных столбцов
void eliminateColumns(int** dataTable, int rowCount, int* colCount, int* emptyColumnIndexes, int emptyCount) {
    if (emptyCount == 0 || emptyColumnIndexes == NULL) {
        return;
    }

    int updatedColCount = *colCount - emptyCount;

    for (int row = 0; row < rowCount; row++) {
        int targetIndex = 0;
        for (int col = 0; col < *colCount; col++) {
            bool shouldRemove = false;
            for (int k = 0; k < emptyCount; k++) {
                if (col == emptyColumnIndexes[k]) {
                    shouldRemove = true;
                    break;
                }
            }
            if (!shouldRemove) {
                dataTable[row][targetIndex] = dataTable[row][col];
                targetIndex++;
            }
        }
    }

    *colCount = updatedColCount;
    for (int row = 0; row < rowCount; ++row) {
        dataTable[row] = (int*)realloc(dataTable[row], updatedColCount * sizeof(int));
    }
}

// Создание структуры данных
int** buildDataStructure(int rowCount, int colCount) {
    int** dataStructure = (int**)realloc(NULL, rowCount * sizeof(int*));

    for (int i = 0; i < rowCount; i++) {
        dataStructure[i] = (int*)calloc(colCount, sizeof(int));
    }

    return dataStructure;
}

// Освобождение ресурсов
void releaseResources(int** dataStructure, int rowCount) {
    for (int i = 0; i < rowCount; i++) {
        free(dataStructure[i]);
    }
    free(dataStructure);
}

// Работа с указателями
void demonstratePointers() {
    cout << "\nПункт 2: Работа с указателем" << endl;

    double valueOne, valueTwo;
    cout << "Введите первую переменную: ";
    cin >> valueOne;
    cout << "Введите вторую переменную: ";
    cin >> valueTwo;

    double* pointerOne = &valueOne;
    double* pointerTwo = &valueTwo;

    cout << "Начальные значения: valueOne = " << valueOne << ", valueTwo = " << valueTwo << endl;

    // Увеличиваем первое значение втрое через указатель
    *pointerOne = *pointerOne * 3;
    cout << "После утроения valueOne: valueOne = " << valueOne << ", valueTwo = " << valueTwo << endl;

    // Обмен значениями через указатели
    double temporary = *pointerOne;
    *pointerOne = *pointerTwo;
    *pointerTwo = temporary;

    cout << "После обмена значений: valueOne = " << valueOne << ", valueTwo = " << valueTwo << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int initialRowSize = 2;
    const int initialColSize = 2;

    // Создаем базовую матрицу 2 на 2
    char baseTable[2][2] = {
        {'A', 'B'},
        {'C', 'D'}
    };

    cout << "Базовая матрица 2x2:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << baseTable[i][j] << " ";
        }
        cout << endl;
    }
    

    int A, B;
    cout << "Введите количество дополнительных строк (A): ";
    cin >> A;
    while (A < 0) {
        cout << "Некорректный ввод! Введите неотрицательное значение для A: ";
        cin >> A;
    }

    cout << "Введите количество дополнительных столбцов (B): ";
    cin >> B;
    while (B < 0) {
        cout << "Некорректный ввод! Введите неотрицательное значение для B: ";
        cin >> B;
    }

    int C, D;
    cout << "Введите значение C: ";
    cin >> C;
    cout << "Введите значение D: ";
    cin >> D;
    
    baseTable[0][0] = A;
    baseTable[0][1] = B;
    baseTable[1][0] = C;
    baseTable[1][1] = D;

    int** primaryData = (int**)realloc(NULL, 2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        primaryData[i] = (int*)calloc(2, sizeof(int));
    }
    primaryData[0][0] = A;
    primaryData[0][1] = B;
    primaryData[1][0] = C;
    primaryData[1][1] = D;

    int totalRowCount = 2 + A;
    int totalColCount = 2 + B;

    int** mainTable = (int**)realloc(primaryData, totalRowCount * sizeof(int*));

    // Инициализируем новые строки
    for (int i = 2; i < totalRowCount; i++) {
        mainTable[i] = (int*)calloc(totalColCount, sizeof(int));
    }

    // Изменяем размер существующих строк
    for (int i = 0; i < 2; i++) {
        mainTable[i] = (int*)realloc(mainTable[i], totalColCount * sizeof(int));
    }

    // Заполняем матрицу данными
    initializeTable(mainTable, initialRowSize, initialColSize, totalRowCount, totalColCount, C, D);
   
    // Отображаем исходную матрицу
    cout << "\nИсходная матрица (" << totalRowCount << "x" << totalColCount << "):" << endl;
    for (int i = 0; i < totalRowCount; i++) {
        for (int j = 0; j < totalColCount; j++) {
            cout << mainTable[i][j] << "\t";
        }
        cout << endl;
    }


    // Ищем пустые столбцы
    int emptyColumnCount;
    int* emptyColumns = locateEmptyColumns(mainTable, totalRowCount, totalColCount, &emptyColumnCount);

    cout << "\nОбнаружено пустых столбцов: " << emptyColumnCount << endl;
    if (emptyColumnCount > 0) {
        cout << "Индексы пустых столбцов: ";
        for (int i = 0; i < emptyColumnCount; i++) {
            cout << emptyColumns[i] << " ";
        }
        cout << endl;
    }

    // Удаляем пустые столбцы
    int currentColumnCount = totalColCount;
    eliminateColumns(mainTable, totalRowCount, &currentColumnCount, emptyColumns, emptyColumnCount);

    // Показываем результат
    cout << "\nМатрица после удаления " << emptyColumnCount << " столбцов:" << endl;
    cout << "Обновленный размер: " << totalRowCount << "x" << currentColumnCount << endl;
    for (int i = 0; i < totalRowCount; i++) {
        for (int j = 0; j < currentColumnCount; j++) {
            cout << mainTable[i][j] << "\t";
        }
        cout << endl;
    }

    // Очищаем память
    if (emptyColumns != NULL) {
        free(emptyColumns);
    }
    releaseResources(mainTable, totalRowCount);

    // Работа с указателями
    demonstratePointers();

    return 0;
}
