#include <iostream>
#include <cstdlib>   

using namespace std;

// Инициализация данных матрицы
void initializeTable(int** dataTable, int startRows, int startCols, int finalRows, int finalCols, int A, int B, int C, int D) {
    // Заполняем начальную матрицу
    dataTable[0][0] = A;
    dataTable[0][1] = B;
    dataTable[1][0] = C;
    dataTable[1][1] = D;

    // Заполняем расширенные столбцы в первой строке
    for (int col = startCols; col < finalCols; col++) {
        int i = -1;
        int j = col - startCols + 1;
        dataTable[0][col] = i * C + j * D;
    }

    // Заполняем расширенные столбцы во второй строке
    for (int col = startCols; col < finalCols; col++) {
        int i = 0;
        int j = col - startCols + 1;
        dataTable[1][col] = i * C + j * D;
    }

    // Заполняем добавленные строки
    for (int row = startRows; row < finalRows; row++) {
        for (int col = 0; col < finalCols; col++) {
            int i = row - startRows + 1;
            int j = col - startCols + 1;
            dataTable[row][col] = i * C + j * D;
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
    int** dataStructure = (int**)malloc(rowCount * sizeof(int*));

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
    cout << "\nПункт 2: Работа с указателями" << endl;

    double a, b;
    cout << "Введите значение переменной a: ";
    cin >> a;
    cout << "Введите значение переменной b: ";
    cin >> b;

    double* ptrA = &a;
    double* ptrB = &b;

    cout << "Исходные значения: a = " << a << ", b = " << b << endl;

    // Увеличиваем первое значение втрое через указатель
    *ptrA = *ptrA * 3;
    cout << "После увеличения a в 3 раза: a = " << a << ", b = " << b << endl;

    // Обмен значениями через указатели
    double temp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = temp;

    cout << "После обмена значений: a = " << a << ", b = " << b << endl;
    delete ptrA;
    delete ptrB;
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int initialRowSize = 2;
    const int initialColSize = 2;

    int A, B, C, D;
    
    cout << "Введите значения A, B, C, D:" << endl;
    cout << "A (количество дополнительных строк): ";
    cin >> A;
    while (A < 0) {
        cout << "Ошибка! Введите неотрицательное значение для A: ";
        cin >> A;
    }

    cout << "B (количество дополнительных столбцов): ";
    cin >> B;
    while (B < 0) {
        cout << "Ошибка! Введите неотрицательное значение для B: ";
        cin >> B;
    }

    cout << "C: ";
    cin >> C;
    cout << "D: ";
    cin >> D;

    // Создаем начальную матрицу 2x2 с значениями A, B, C, D
    cout << "\nНачальная матрица 2x2:" << endl;
    cout << A << "\t" << B << endl;
    cout << C << "\t" << D << endl;

    int totalRowCount = 2 + A;
    int totalColCount = 2 + B;

    // Создаем матрицу 2x2 и расширяем ее
    int** mainTable = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        mainTable[i] = (int*)malloc(2 * sizeof(int));
    }
    
    // Заполняем начальные значения
    mainTable[0][0] = A;
    mainTable[0][1] = B;
    mainTable[1][0] = C;
    mainTable[1][1] = D;

    // Расширяем матрицу до нужного размера
    mainTable = (int**)realloc(mainTable, totalRowCount * sizeof(int*));
    for (int i = 2; i < totalRowCount; i++) {
        mainTable[i] = (int*)malloc(totalColCount * sizeof(int));
    }

    // Расширяем существующие строки
    for (int i = 0; i < 2; i++) {
        mainTable[i] = (int*)realloc(mainTable[i], totalColCount * sizeof(int));
    }

    // Заполняем матрицу данными по правильной формуле
    initializeTable(mainTable, initialRowSize, initialColSize, totalRowCount, totalColCount, A, B, C, D);
   
    // Отображаем исходную расширенную матрицу
    cout << "\nРасширенная матрица (" << totalRowCount << "x" << totalColCount << "):" << endl;
    cout << "A = " << A << " (добавлено строк: " << A << "), B = " << B << " (добавлено столбцов: " << B << ")" << endl;
    for (int i = 0; i < totalRowCount; i++) {
        for (int j = 0; j < totalColCount; j++) {
            cout << mainTable[i][j] << "\t";
        }
        cout << endl;
    }

    // Ищем столбцы с нулями
    int emptyColumnCount;
    int* emptyColumns = locateEmptyColumns(mainTable, totalRowCount, totalColCount, &emptyColumnCount);

    cout << "\nНайдено столбцов с нулями: " << emptyColumnCount << endl;
    if (emptyColumnCount > 0) {
        cout << "Индексы столбцов с нулями: ";
        for (int i = 0; i < emptyColumnCount; i++) {
            cout << emptyColumns[i] << " ";
        }
        cout << endl;
    }

    // Удаляем столбцы с нулями
    int currentColumnCount = totalColCount;
    eliminateColumns(mainTable, totalRowCount, &currentColumnCount, emptyColumns, emptyColumnCount);

    // Показываем результат
    cout << "\nМатрица после удаления " << emptyColumnCount << " столбцов:" << endl;
    cout << "Новый размер: " << totalRowCount << "x" << currentColumnCount << endl;
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
