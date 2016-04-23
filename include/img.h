#ifndef IMG_H
#define IMG_H

/*
��������������! ������ ����� ��������� ��� �������������� � ����������� �������
����� BMP � ��� ���������� ��������.  ���� ���������:

����������/���������:
(1) ��������� BITMAPFILEHEADER � BITMAPINFOHEADER.
        -> ������ ��� �������� ������������ ����������.
        -> ������� ������� �� �������.
(2) is_8bit
        ->  �������������� �������.
������:
(1) ����������� img() ��������� ���������� ������ � ������ � ��������� �������� �� ������.
    ��� �� ��������� ������ read_bitmap_f() � read_bitmap_i() ��� ���������� ����������
    � ���������, � ������� �������������� �������.
(2) read_bitmap_f -> ���������� ������ ����� � ������ BITMAPFILEHEADER.
(3) read_bitmap_i -> ���������� ������ ����������� BITMAPFILEHEADER.
(4) read_bimg -> ���������� ������� ��������.
(5) write_bimg -> ������ ������� ��������.
(6) ���������� ~img() ��������� �������� �����.


��� ������ ������������ ������ BMP 8-������ ������.
*/





class img
{
    public:
/*
----------------------------------------------------------------------------------------------
��������� ����������.
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
���������� ����������.
----------------------------------------------------------------------------------------------
*/

        void read_bitmap_f(typeBITMAPFILEHEADER &);

        /* ���������� 1 � ������ �� 8-������� �������, � 0 � ������ 8-�������. */
        int read_bitmap_i(typeBITMAPINFOHEADER &);

/*
----------------------------------------------------------------------------------------------
����������� � ����������
----------------------------------------------------------------------------------------------
*/
        img(const char*);
        ~img();
/*
----------------------------------------------------------------------------------------------
���������� � ������ ������� ��������.
----------------------------------------------------------------------------------------------
*/
        void read_bimg(char** &, unsigned int, unsigned int, unsigned int);
        /* ���������� 0 � ������ ��������� ������, � 1 � ������ ������ ������. */
        int write_bimg(char**, unsigned int, unsigned int, unsigned int, unsigned int);
/*
----------------------------------------------------------------------------------------------
����������.
----------------------------------------------------------------------------------------------
*/
        bool is_8bit;

    protected:

    private:


};

#endif // IMG_H
