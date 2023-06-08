#include "FILE_INFO.h"
#include <exception>

Bmp::Bmp(std::ifstream &in) {
    ReadFileHeader(in);
    ReadImgHeader(in);
    ReadPanel(in);
}


//        bfType	2	The characters "BM"
//        bfSize	4	The size of the file in bytes
//        bfReserved1	2	Unused - must be zero
//        bfReserved2	2	Unused - must be zero
//        bfOffBits	4	Offset to start of Pixel Data
void Bmp::ReadFileHeader(std::ifstream &in) {
    char file_type = Read::ReadByte(in);
    if (file_type != 'B') {
        throw std::runtime_error("Invalid file: Invalid file header: Invalid file type");
    }
    file_type = Read::ReadByte(in);
    if (file_type != 'M') {
        throw std::runtime_error("Invalid file: Invalid file header: Invalid file type");
    }
    file_header.size = Read::Read32(in);
    Read::Skip(in, 4);
    file_header.offset = Read::Read32(in);
}


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

void Bmp::ReadImgHeader(std::ifstream &in) {
    img_header.size = Read::Read32(in);
    if (file_header.size < 40) {
        throw std::runtime_error("Invalid file: Invalid image header: Invalid image header size");
    }
    img_header.width = Read::Read32(in);
    img_header.height = Read::Read32(in);
    if (Read::Read16(in) != 1) {
        throw std::runtime_error("Invalid file: Invalid image header: biPlanes must be 1");
    }
    if (Read::Read16(in) != 24) {
        throw std::runtime_error("Invalid file: Invalid image header: Bits per pixel must be 24");
    }
    if (Read::Read32(in) != 0) {
        throw std::runtime_error("Invalid file: Invalid image header: File should be uncompressed.");
    }
    img_header.size_image = Read::Read32(in);
    img_header.x_per_meter = Read::Read32(in);
    img_header.y_per_meter = Read::Read32(in);
    img_header.crl_used = Read::Read32(in);
    img_header.crl_important = Read::Read32(in);
}

void Bmp::ReadPanel(std::ifstream &in) {
    panel.SetSize(img_header.height, img_header.width);
    for (int32_t height = 0; height < panel.height(); ++height) {
        for (int32_t width = 0; width < panel.width(); ++width) {
            Pixel new_pixel = Read::ReadPixel(in);
            panel.SetPixel(height, width, new_pixel);
        }
        Read::Skip(in, panel.padding_amount());
    }
}

void Bmp::Save(std::ofstream &out) {
    file_header.size = panel.padding_amount() * panel.height() +
                       panel.width() * panel.height() * 3 + 14 + 40;
    //  header - 14 bytes
    //  img - 40 bytes
    SaveFileHeader(out);
    SaveImgHeader(out);
    SavePanel(out);
}

//        bfType	2	The characters "BM"
//        bfSize	4	The size of the file in bytes
//        bfReserved1	2	Unused - must be zero
//        bfReserved2	2	Unused - must be zero
//        bfOffBits	4	Offset to start of Pixel Data
void Bmp::SaveFileHeader(std::ofstream &out) {
    Write::WriteByte(out, 'B');
    Write::WriteByte(out, 'M');
    Write::Write32(out, file_header.size);
    Write::Write16(out, 0);
    Write::Write16(out, 0);
    Write::Write32(out, file_header.offset);
}


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
void Bmp::SaveImgHeader(std::ofstream &out) {
    Write::Write32(out, img_header.size);
    Write::Write32(out, img_header.width);
    Write::Write32(out, img_header.height);
    Write::Write16(out, 1);
    Write::Write16(out, 24);
    Write::Write32(out, 0);
    Write::Write32(out, img_header.size_image);
    Write::Write32(out, img_header.x_per_meter);
    Write::Write32(out, img_header.y_per_meter);
    Write::Write32(out, img_header.crl_used);
    Write::Write32(out, img_header.crl_important);
}

void Bmp::SavePanel(std::ofstream &out) {
    for (int32_t height = 0; height < panel.height(); ++height) {
        for (int32_t width = 0; width < panel.width(); ++width) {
            Write::WritePixel(out, panel.GetPixel(height, width));
        }
        Write::WriteZeros(out, panel.padding_amount());
    }
}
