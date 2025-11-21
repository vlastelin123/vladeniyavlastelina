#include <iostream>
#include <cstdlib>   

// Функция для заполнения матрицы
void fillMatrix(int** matrix, int initialRows, int initialCols, int totalRows, int totalCols, int C, int D) {
    for (int i = 0; i < initialRows; ++i) {
        for (int j = 0; j < initialCols; ++j) {
            matrix[i][j] = (-1 + i) * C + (1 + j) * D;
        }
    }

    for (int i = 0; i < initialRows; i++) {
        for (int j = initialCols; j < totalCols; j++) {
            matrix[i][j] = (-1 + i) * C + (j - initialCols + 1) * D;
        }
    }

    for (int i = initialRows; i < totalRows; i++) {
        for (int j = 0; j < totalCols; j++) {
            matrix[i][j] = (i - initialRows + 1) * C + (j - initialCols + 1) * D;
        }
    }
    
}

// Функция для поиска столбцов из нулей
int* findZeroColumns(int** matrix, int rows, int cols, int* zeroCount) {
    int* zeroIndices = NULL;
    *zeroCount = 0;

    for (int j = 0; j < cols; j++) {
        bool hasZero = false;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 0) {
                hasZero = true;
                break;
            }
        }
        if (hasZero) {
            zeroIndices = (int*)realloc(zeroIndices, (*zeroCount + 1) * sizeof(int));
            zeroIndices[*zeroCount] = j;
            (*zeroCount)++;
        }
    }

    if (*zeroCount == 0) {
        free(zeroIndices);
        return NULL;
    }

    return zeroIndices;
}

// Функция для удаления столбцов
void removeColumnsFromOriginal(int** matrix, int rows, int* cols, int* zeroIndices, int zeroCount) {
    if (zeroCount == 0 || zeroIndices == NULL) {
        return;
    }

    int newCols = *cols - zeroCount;

    for (int i = 0; i < rows; i++) {
        int writeIndex = 0;
        for (int j = 0; j < *cols; j++) {
            bool isZeroColumn = false;
            for (int k = 0; k < zeroCount; k++) {
                if (j == zeroIndices[k]) {
                    isZeroColumn = true;
                    break;
                }
            }
            if (!isZeroColumn) {
                matrix[i][writeIndex] = matrix[i][j];
                writeIndex++;
            }
        }


    }

    *cols = newCols;
    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int*)realloc(matrix[i], newCols * sizeof(int));
    }
}

// Функция для создания матрицы
int** createMatrix(int rows, int cols) {
    int** matrix = (int**)realloc(NULL, rows * sizeof(int*));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)calloc(cols, sizeof(int));
    }

    return matrix;
}

// Функция для освобождения памяти
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
// Функция для работы с указателями
void pointerOperations() {
    std::cout << "\nПункт 2: Работа с указателями" << std::endl;

    double a, b;
    std::cout << "Введите значение переменной a: ";
    std::cin >> a;
    std::cout << "Введите значение переменной b: ";
    std::cin >> b;

    double* ptrA = &a;
    double* ptrB = &b;

    std::cout << "Исходные значения: a = " << a << ", b = " << b << std::endl;

    // Увеличиваем значение a в 3 раза через указатель
    *ptrA = *ptrA * 3;
    std::cout << "После увеличения a в 3 раза: a = " << a << ", b = " << b << std::endl;

    // Меняем местами значения через указатели
    double temp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = temp;

    std::cout << "После обмена значений: a = " << a << ", b = " << b << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int initialRows = 2;
    const int initialCols = 2;

    // Создаем матрицу 2x2
    char matrix22[2][2] = {
        {'A', 'B'},
        {'C', 'D'}
    };

    std::cout << "Матрица 2x2:" << std::endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << matrix22[i][j] << " ";
        }
        std::cout << std::endl;
    }
    

    int A, B;
    std::cout << "Введите количество строк для добавления (A): ";
    std::cin >> A;
    while (A < 0) {
        std::cout << "Ошибка! Введите неотрицательное значение для A: ";
        std::cin >> A;
    }

    std::cout << "Введите количество столбцов для добавления (B): ";
    std::cin >> B;
    while (B < 0) {
        std::cout << "Ошибка! Введите неотрицательное значение для B: ";
        std::cin >> B;
    }

    int C, D;
    std::cout << "Введите значение C: ";
    std::cin >> C;
    std::cout << "Введите значение D: ";
    std::cin >> D;
    matrix22[0][0] = A;
    matrix22[0][1] = B;
    matrix22[1][0] = C;
    matrix22[1][1] = D;

    int** M = (int**)realloc(NULL, 2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        M[i] = (int*)calloc(2, sizeof(int));
    }
    M[0][0] = A;
    M[0][1] = B;
    M[1][0] = C;
    M[1][1] = D;

    int totalRows = 2 + A;
    int totalCols = 2 + B;

    int** matrix = (int**)realloc(M, totalRows * sizeof(int*));

    // Инициализируем добавленные строки
    for (int i = 2; i < totalRows; i++) {
        matrix[i] = (int*)calloc(totalCols, sizeof(int));
    }

    // Изменяем размер существующих строк
    for (int i = 0; i < 2; i++) {
        matrix[i] = (int*)realloc(matrix[i], totalCols * sizeof(int));
    }

    // Заполняем матрицу
    fillMatrix(matrix, initialRows, initialCols, totalRows, totalCols, C, D);
   
    // Выводим исходную матрицу
    std::cout << "\nИсходная матрица (" << totalRows << "x" << totalCols << "):" << std::endl;
    for (int i = 0; i < totalRows; i++) {
        for (int j = 0; j < totalCols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }


    // Поиск нулевых столбцов
    int zeroCount;
    int* zeroIndices = findZeroColumns(matrix, totalRows, totalCols, &zeroCount);

    std::cout << "\nНайдено нулевых столбцов: " << zeroCount << std::endl;
    if (zeroCount > 0) {
        std::cout << "Индексы нулевых столбцов: ";
        for (int i = 0; i < zeroCount; i++) {
            std::cout << zeroIndices[i] << " ";
        }
        std::cout << std::endl;
    }

    // Удаление нулевых столбцов
    int currentCols = totalCols;
    removeColumnsFromOriginal(matrix, totalRows, &currentCols, zeroIndices, zeroCount);

    // Вывод результата
    std::cout << "\nМатрица после удаления " << zeroCount << " столбцов:" << std::endl;
    std::cout << "Новый размер: " << totalRows << "x" << currentCols << std::endl;
    for (int i = 0; i < totalRows; i++) {
        for (int j = 0; j < currentCols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    // Освобождение памяти
    if (zeroIndices != NULL) {
        free(zeroIndices);
    }
    freeMatrix(matrix, totalRows); // Освобождаем только исходную матрицу

    // Работа с указателями
    pointerOperations();

    return 0;
}