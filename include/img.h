#ifndef IMG_H
#define IMG_H

/*
Предупреждение! Данный класс рассчитан для взаимодействия с заголовками формата
файла BMP и его структурой пикселей.  Ниже объявлены:

Переменные/Структуры:
(1) Заголовки BITMAPFILEHEADER и BITMAPINFOHEADER.
        -> Служит для хранения заголовочных переменных.
        -> Заранне созданы их объекты.
(2) is_8bit
        ->  Восьмибитность формата.
Методы:
(1) Конструктор img() выполняет связывание потока с файлом и выполняет проверку на формат.
    Так же выполняет методы read_bitmap_f() и read_bitmap_i() для считывания информации
    о заголвках, в заранее подготовленные объекты.
(2) read_bitmap_f -> Считывание хэдера файла в объект BITMAPFILEHEADER.
(3) read_bitmap_i -> Считывание хэдера изображения BITMAPFILEHEADER.
(4) read_bimg -> Считывание массива пикселей.
(5) write_bimg -> Запись массива пикселей.
(6) Деструктор ~img() выполняет закрытие файла.


Все методы поддерживают ТОЛЬКО BMP 8-битный формат.
*/





class img
{
    public:
/*
----------------------------------------------------------------------------------------------
Структуры заголовков.
----------------------------------------------------------------------------------------------
*/
        struct typeBITMAPFILEHEADER
        {
                unsigned short bfType;
                unsigned int bfSize;
                unsigned short bfReserved1;
                unsigned short bfReserved2;
                unsigned int bfOffBits;
        } BITMAPFILEHEADER;

        struct typeBITMAPINFOHEADER
        {
               unsigned int biSize;
               unsigned int biWidth;
               unsigned int biHeight;
               unsigned short biPlanes;
               unsigned short biBitCount;
               unsigned int biCompression;
               unsigned int biSizeImage;
               unsigned int biXPelsPerMeter;
               unsigned int biYPelsPerMeter;
               unsigned int biClrUsed;
               unsigned int biClrImportant;
         } BITMAPINFOHEADER;


/*
----------------------------------------------------------------------------------------------
Считывание заголовков.
----------------------------------------------------------------------------------------------
*/

        void read_bitmap_f(typeBITMAPFILEHEADER &);

        /* Возвращает 1 в случае не 8-битного формата, и 0 в случае 8-битного. */
        int read_bitmap_i(typeBITMAPINFOHEADER &);

/*
----------------------------------------------------------------------------------------------
Конструктор и деструктор
----------------------------------------------------------------------------------------------
*/
        img(const char*);
        ~img();
/*
----------------------------------------------------------------------------------------------
Считывание и запись массива пикселей.
----------------------------------------------------------------------------------------------
*/
        void read_bimg(char** &, unsigned int, unsigned int, unsigned int);
        /* Возвращает 0 в случае частичной замены, и 1 в случае полной замены. */
        int write_bimg(char**, unsigned int, unsigned int, unsigned int, unsigned int);
/*
----------------------------------------------------------------------------------------------
Переменные
----------------------------------------------------------------------------------------------
*/
        bool is_8bit;

    protected:

    private:


};

#endif // IMG_H
