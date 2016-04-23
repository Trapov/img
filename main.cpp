#include <iostream>
#include <windows.h> // Для установления кодировки.


#include <bitset> // Для подмены младших битов.
#include "img.h" // Класс для работы с BMP-8 битными.


#include <conio.h> // Для удобного ввода текста. GETCH();
#include <iomanip>

const char* name_of_file = "lena512.bmp";

int main()
{
/*
----------------------------------------------------------------------------------------------
Кодировка
----------------------------------------------------------------------------------------------
*/

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

/*
----------------------------------------------------------------------------------------------
Конструктор
----------------------------------------------------------------------------------------------
*/


    img * imgf = new img(name_of_file);
    img::typeBITMAPFILEHEADER buf_f; // Создание структор, для записи в них данных
    img::typeBITMAPINFOHEADER buf_i; //
    imgf->read_bitmap_f(buf_f); // запись
    imgf->read_bitmap_i(buf_i); //
    // Выделение памяти под массив пикселей, для работы.
    char ** array_of_pixels = new char*[buf_i.biHeight];
    for ( unsigned int i = 0 ; i < buf_i.biHeight ; i++) {
        array_of_pixels[i] = new char [buf_i.biWidth];
    }

    //Создание битсетов для изображения и кодируемого текста, для удобного обращения с битами.
    std::bitset<8> bitofimg = 0;
    std::bitset<8> bitoftext = 0;

    //вычисление свободных байтов для записи
    int bytes_free = (buf_i.biHeight*buf_i.biWidth)/8;

    //Вывод информации
    std::cout << "Высота изображения (пиксели): " << buf_i.biHeight << std::endl;
    std::cout << "Ширина изображения (пиксели): " << buf_i.biWidth << std::endl;
    std::cout << "Размер изображения (в байтах) : " << buf_i.biSizeImage << std::endl;
    std::cout << "Количество свободных байтов для информации : " << bytes_free<< std::endl;
    std::cout << std::setfill('*') << std::setw(78) << "*" << std::ends << std::endl;


/*
----------------------------------------------------------------------------------------------
Интерактив
----------------------------------------------------------------------------------------------
*/
    std::cout << "Что делать далее:\n"
              << "(1) Прочитать информацию из изображения\n"
              << "(2) Сохранить в изображение информацию\n"
              << "(3) Выход \n";

    int choose1;
    while (1) {
        std::cin >> choose1;
        if (choose1 == 1) break;
        if (choose1 == 2) break;
        if (choose1 == 3) break;
    }

    switch(choose1){
        case 1 : {
            // Считывание информации о пикселях в массив
            imgf->read_bimg(array_of_pixels, buf_f.bfOffBits, buf_i.biWidth, buf_i.biHeight);

            unsigned int key = 0;
            std::cout << "Введите ключ : "; std::cin >> key;
            if (key == 0) break;
            char * text = new char[key];
            unsigned int y = 0;
            unsigned int x = 0;
            unsigned int count_of_bits = 0;
            for (unsigned int i = 0 ; i<key; i++ ) {

                for (count_of_bits = 0 ; count_of_bits < 8 ; count_of_bits++) {
                    if (x==buf_i.biWidth) {x=0; y++;}
                    bitofimg = array_of_pixels[y][x];
                    bitoftext[count_of_bits] = bitofimg[7];
                    x++;
                }
                bitofimg = 0;
                text[i] = (char)bitoftext.to_ulong();
                bitoftext = 0;
                std::cout << text[i];
            }
            break;
        }
        case 2 : {

            // Считывание информации о пикселях в массив
            imgf->read_bimg(array_of_pixels, buf_f.bfOffBits, buf_i.biWidth, buf_i.biHeight);

            std::cout << "Введите ваш текст : " << std::endl;

            char * text = new char[bytes_free];

            unsigned int i = 0;
            while((text[i] = getch()) != 13 ){
                std::cout << text[i];
                i++;
            }
            int bytes_of_text = i*sizeof(char);
            if ((bytes_free)<bytes_of_text) {
                std::cout << "\nНе хватает свободных битов для кодирования информации! \n";
            } else {
                std::cout << "\nВведенный текст может быть закодирован! \n";
                for ( unsigned int arrelem = 0 ; arrelem < i ; arrelem++)
                {
                    bitoftext = text[arrelem];
                    std::cout << bitoftext << std::endl;
                    bitoftext = 0;
                }




                char choose;
                while (1) {
                    std::cout << "Записать? (Y,N) : ";
                    std::cin >> choose;
                    if (choose == 'Y') break;
                    if (choose == 'N') break;
                }

                if (choose == 'Y') {
                    unsigned int y = 0;
                    unsigned int x = 0;
                    unsigned int arrelem = 0;
                    unsigned int count_of_bits = 0;
                    for (arrelem = 0; arrelem < i ; arrelem++)
                    {
                        std::cout << text[arrelem] << std::endl;
                        bitoftext = text[arrelem];
                        std::cout << bitoftext << std::endl;

                        for (count_of_bits = 0 ; count_of_bits < 8 ; count_of_bits++) {
                            if (x==buf_i.biWidth) {x=0; y++;}
                            bitofimg = array_of_pixels[y][x];
                            std:: cout << "ДО : " << bitofimg << std::endl;
                            bitofimg[7] = bitoftext[count_of_bits];

                            array_of_pixels[y][x] = bitofimg.to_ulong();
                            std:: cout << "ПОСЛЕ : " << (std::bitset<8>)array_of_pixels[y][x] << std::endl;
                            x++;


                        }
                        bitoftext = 0;
                    }
                    std:: cout << "\n Количество изменений : \n" << arrelem*count_of_bits << std::endl;
                    imgf->write_bimg(array_of_pixels, buf_f.bfOffBits, buf_i.biWidth, buf_i.biHeight, (arrelem*count_of_bits));

                }

                if (choose == 'N') return 0;

            }

            break;
        }
        case 3: {break;}
    }


/*
----------------------------------------------------------------------------------------------
Освобождение памяти.
----------------------------------------------------------------------------------------------
*/
    for (unsigned int i = 0; i < buf_i.biHeight; i++) {
        delete []array_of_pixels[i];
    }
    delete []array_of_pixels;
    delete imgf;
    return 0;
}
