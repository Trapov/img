#include "img.h"
#include <fstream>
/*
----------------------------------------------------------------------------------------------
Объявление потока файла.
----------------------------------------------------------------------------------------------
*/
std::fstream imgf;


/*
----------------------------------------------------------------------------------------------
Перегрузка оператора, для запись в структуры.
----------------------------------------------------------------------------------------------
*/
std::istream& operator>> (std::istream& in, img::typeBITMAPFILEHEADER& value)
{
    in.read((char*)&value.bfType, sizeof(value.bfType));
    in.read((char*)&value.bfSize, sizeof(value.bfSize));
    in.read((char*)&value.bfReserved1, sizeof(value.bfReserved1));
    in.read((char*)&value.bfReserved2, sizeof(value.bfReserved2));
    in.read((char*)&value.bfOffBits, sizeof(value.bfOffBits));

    return in;
}
std::istream& operator>> (std::istream& in, img::typeBITMAPINFOHEADER& value)
{
    in.read((char*)&value.biSize, sizeof(value.biSize));
    in.read((char*)&value.biWidth, sizeof(value.biWidth));
    in.read((char*)&value.biHeight, sizeof(value.biHeight));
    in.read((char*)&value.biPlanes, sizeof(value.biPlanes));
    in.read((char*)&value.biBitCount, sizeof(value.biBitCount));
    in.read((char*)&value.biCompression, sizeof(value.biCompression));
    in.read((char*)&value.biSizeImage, sizeof(value.biSizeImage));
    in.read((char*)&value.biXPelsPerMeter, sizeof(value.biXPelsPerMeter));
    in.read((char*)&value.biYPelsPerMeter, sizeof(value.biYPelsPerMeter));
    in.read((char*)&value.biClrUsed, sizeof(value.biClrUsed));
    in.read((char*)&value.biClrImportant, sizeof(value.biClrImportant));

    return in;
}

/*
----------------------------------------------------------------------------------------------
Считывание и запись структур.
----------------------------------------------------------------------------------------------
*/
void img::read_bitmap_f(typeBITMAPFILEHEADER& buf)
{
    imgf >> buf;
}
int img::read_bitmap_i(typeBITMAPINFOHEADER& buf)
{
    imgf >> buf;
    if ( buf.biBitCount !=8 )
    {
        return 1;
    } else { return 0;}
}


/*
----------------------------------------------------------------------------------------------
Конструктор и деструктор.
----------------------------------------------------------------------------------------------
*/
img::img(const char * name_of_img_)
{
    imgf.open(name_of_img_, std::ios_base::in | std::ios_base::out | std::ios::binary);
    img::read_bitmap_f(img::BITMAPFILEHEADER);
    if ((img::read_bitmap_i(img::BITMAPINFOHEADER))==1) {img::is_8bit=0;} else {img::is_8bit=1;} ;
    imgf.seekg(0, std::ios::beg);
    //ctor
}

img::~img()
{
    imgf.close();
    //dtor
}
/*
----------------------------------------------------------------------------------------------
Считывание и запись массива пикселей:
----------------------------------------------------------------------------------------------
*/
void img::read_bimg(char ** &smth, unsigned int bfOfBits,
                    unsigned int biX,
                    unsigned int biY)
{
    imgf.seekg(bfOfBits, std::ios::beg);
    for (unsigned int y = 0 ; y < biY ; y++) {
        for (unsigned int x = 0; x < biX ; x++) {
            unsigned char buf;
            imgf.read((char*)&buf, sizeof(char));
            smth[y][x] = buf;
        }
    }

}
int img::write_bimg(char ** smth, unsigned int bfOfBits,
                    unsigned int biX,
                    unsigned int biY, unsigned int change)
{
    imgf.seekp(bfOfBits, std::ios::beg);
    for (unsigned int y = 0 ; y < biY ; y++) {
        for (unsigned int x = 0; x < biX ; x++) {
            if (change == 0) {return 0;}
            unsigned char buf;
            buf = smth[y][x];
            imgf.write((char*)&buf, sizeof(char));
            change--;
        }
    }
    return 1;
}
