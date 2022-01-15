#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "container.h"

void SimpleFunction(container* container);
void CommandLineArgsErrorMessage();
void SortFunction(container* container);
int BinarySearchByTime(container* container, double selected, int low, int high);
int InviteMessage();
int ReadInt(int min, int max);

// Поля для имён файлов ввода и вывода.
char* input_file;
char* output_file;

/*
 * Как программа работает:
 * 1. Проверяет количество данных и файлы ввода-вывода на открываемость.
 *    Аргументы командной строки состоят из трёх компонент:
 *    1.1. Имя программы.
 *    1.2. Имя файла ввода.
 *    1.3. Имя файлы вывода.
 * 2. Инициализирует контейнер.
 * 3. Даёт выбор пользователю считать данные для контейнера из файла или случайно.
 * 4. Заполняет контейнер одним из способов.
 * 5. Подсчитывает общую для всех альтернатив функцию.
 * 6. Сортирует транспортные средства прямо в контейнере по возрастанию значения общей функции.
 * 7. Выводит отсортированные данные в выходной файл.
 */
int main(int argc, char** argv)
{
    double begin;
    FILE *file;
    if(argc!=3) {
        CommandLineArgsErrorMessage();
        return 1;
    }
    input_file = *(argv+1);
    output_file = *(argv+2);
    if((file=fopen(input_file, "r"))== nullptr) {
        printf("Input file failure!");
        CommandLineArgsErrorMessage();
        return 1;
    }
    fclose(file);
    if((file=fopen(output_file, "r"))== nullptr) {
        printf("Output file failure");
        CommandLineArgsErrorMessage();
        return 1;
    }
    fclose(file);
    container cont;
    int select = InviteMessage();
    container* contPtr = &(cont);
    Initialize(contPtr);
    if(select == 1) {
        // Время выполнения программы начинаю считать после последнего введённого аргумента.
        begin = clock();
        Input(contPtr, file);
    }
    if(select==2) {
        printf("How many vehicles do you want to create? From 1 to 10000.\n");
        int size = ReadInt(1, MAX_LENGTH);
        // Время выполнения программы начинаю считать после последнего введённого аргумента.
        begin = clock();
        srand(time(NULL));
        cont = InputRandom(contPtr, size);
        file = fopen(input_file, "w");
        for(int i=0; i<contPtr->length; i++) {
            RawOutput(contPtr->pointer_arr[i], file);
        }
        fclose(file);
    }
    SimpleFunction(contPtr);
    SortFunction(contPtr);
    printf("Done! You may want to check your output file!\n");
    double end = clock();
    double time = (end-begin)/CLOCKS_PER_SEC;
    printf("Execution time: %lf\n", time);
	return 0;
}

/*
 * РЕАЛИЗАЦИЯ ФУНКЦИЙ
 */

/*
 * Binary Insertion Sort.
 * Алгоритм сортировки, основанный на двоичном поиске.
 * 1. Выбираем некоторый элемент.
 * 2. Ищем подходящую для него локацию.
 * 3. Вставляем элемент в локацию, раздвигая все элементы, идущие за этой локацией.
 */
void SortFunction(container* container) {
    for(int i=1; i<container->length; ++i) {
        int j = i-1;
        double selected = container->pointer_arr[i]->ideal_time;
        int location = BinarySearchByTime(container, selected, 0, j);
        while(j>=location) {
            vehicle temporary = container->arr[j+1];
            container->arr[j+1] = container->arr[j];
            container->arr[j] = temporary;
            j--;
        }
        container->pointer_arr[j+1]->ideal_time = selected;
    }
    FILE* file;
    file = fopen(output_file, "w");
    for(int i=0; i<container->length; i++) {
        Output(container->pointer_arr[i], file);
    }
    fclose(file);
    return;
}

// Бинарный поиск.
int BinarySearchByTime(container* container, double selected, int low, int high) {
    while(low<=high) {
        int mid = low + (high - low) / 2;
        if(selected == container->pointer_arr[mid]->ideal_time) {
            return mid+1;
        }
        if(selected > container->pointer_arr[mid]->ideal_time) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

// Метод подсчёта общей функции для всех элементов контейнера.
void SimpleFunction(container* container) {
    for(int i=0; i<container->length; i++) {
        container->pointer_arr[i]->ideal_time = container->pointer_arr[i]->way_length
                                                /container->pointer_arr[i]->speed;
    }
}


/*
 * ДОПОЛНИТЕЛЬНОЕ
 */

// Удобный метод для считывания целых чисел с консоли в диапозоне от min до max включительно.
int ReadInt(int min, int max) {
    char string_input[MAX_LENGTH];
    scanf("%s", string_input);
    int input;
    while(true) {
        input = atoi(string_input);
        if(input >= min && input <= max) {
            return input;
        } else {
            printf("Sorry, wrong input! Please, correct it.\n");
            scanf("%s", &string_input);
        }
    }
}


/*
 * УВЕДОМЛЕНИЯ
 */

// Сообщение, предлагающее пользователю выбрать способ ввода данных.
int InviteMessage() {
    printf("Welcome!\n");
    printf("Do you wish to input data through your file or randomly?\n");
    printf("Print in just one digit, one or two.\n");
    printf("1. Through specified file.\n");
    printf("2. Randomly.\n");
    return ReadInt(1, 2);
}

// Сообщение, которое появляется при неправильных аргументах командной строки.
void CommandLineArgsErrorMessage() {
    printf("Sorry, your command line arguments are unsuitable.\n");
    printf("Press ENTER to close the program...\n");
    while( getchar() != '\n' );
}
