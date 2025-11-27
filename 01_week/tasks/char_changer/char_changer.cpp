#include <cstddef>
#include <cctype>


size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    int counter = 0; // Счётчик повторяющихся символов
    int write = 0;   // Указатель для записи обработанного символа
    int read = 0;    // Указатель для чтения следующего элемента из массива
    char repeating_symbol = array[read]; // В процессе выполнения - редыдущий символ после read(отслеживаем повторения)

    while (repeating_symbol != '\0'){
        if (repeating_symbol == array[read]){
            counter++;
        } else {
            if (isalpha(repeating_symbol)){
                array[write] = toupper(repeating_symbol);
            } else if (isdigit(repeating_symbol)){
                array[write] = '*';
            } else if (repeating_symbol == ' '){
                array[write] = delimiter;
            } else {
                array[write] = '_';
            }

            write++;

            if (repeating_symbol == ' ') {
                counter = 1;
            }

            if (counter >= 10){
                counter = 0;
            }

            if (counter != 1){
                array[write] = static_cast<char>(counter + '0'); // Преобразуем число в символ
                counter = 1;
                write++;
            }

            repeating_symbol = array[read];
        }

        read++;
    }

    array[write] = '\0';
    return write;     
}