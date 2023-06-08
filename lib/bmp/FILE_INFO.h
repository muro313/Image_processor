#pragma once
#include "../in_out/Read.h"
#include "../in_out/Write.h"
#include "../ColorPanel/ColorPanel.h"

struct FileHeader{
    int32_t size;
    int32_t offset;
};


//    biSize	4	Header Size - Must be at least 40
//    biWidth	4	Image width in pixels
//    biHeight	4	Image height in pixels
//    biPlanes	2	Must be 1
//    biBitCount	2	Bits per pixel - 1, 4, 8, 16, 24, or 32
//    biCompression	4	Compression type (0 = uncompressed)
//    biSizeImage	4	Image Size - may be zero for uncompressed images
//    biXPelsPerMeter	4	Preferred resolution in pixels per meter
//    biYPelsPerMeter	4	Preferred resolution in pixels per meter
//    biClrUsed	4	Number Color Map entries that are actually used
//    biClrImportant	4	Number of significant colors
struct ImageHeader{
    int32_t size; //at least 40
    int32_t width;
    int32_t height;
    int32_t size_image;
    int32_t x_per_meter;
    int32_t y_per_meter;
    int32_t crl_used;
    int32_t crl_important;
};



class Bmp{
public:
    Bmp(std::ifstream& in);
    void Save(std::ofstream& out);
    friend class Filter;
    FileHeader file_header{};
    ImageHeader img_header{};
    Panel panel;
private:

    void ReadFileHeader(std::ifstream& in);

    void ReadImgHeader(std::ifstream& in);

    void ReadPanel(std::ifstream& in);

    void SaveFileHeader(std::ofstream& out);

    void SaveImgHeader(std::ofstream& out);

    void SavePanel(std::ofstream& out);
};