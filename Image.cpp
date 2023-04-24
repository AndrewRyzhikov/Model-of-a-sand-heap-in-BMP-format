#include "Image.h"

Color::Color() : r(255), g(255), b(255) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

Image::Image(int width, int height) {
    m_width = width;
    m_height = height;
    m_colors = new Color[width * height];
}

void Image::SetColor(int x, int y, int colorPreset) {
    Color color;
    if (colorPreset == 0) {
        color.r = 255;
        color.g = 255;
        color.b = 255;
    }
    if (colorPreset == 1) {
        color.r = 0;
        color.g = 255;
        color.b = 0;
    }
    if (colorPreset == 2) {
        color.r = 83;
        color.g = 55;
        color.b = 122;
    }
    if (colorPreset == 3) {
        color.r = 255;
        color.g = 255;
        color.b = 0;
    }
    if (colorPreset >= 4) {
        color.r = 0;
        color.g = 0;
        color.b = 0;
    }
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

Color Image::GetColor(int x, int y) const {
    return m_colors[y * m_width + x];
}

void Image::Export(const std::string& path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);


    unsigned char bmpPad[3] = {0, 0, 0};
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize =
            fileHeaderSize + informationHeaderSize + m_width * m_height * 3 +
            paddingAmount * m_height;

    unsigned char fileHeader[fileHeaderSize];

    // file type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    // file size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    // reserved
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    fileHeader[8] = 0;
    fileHeader[9] = 0;

    // pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;


    unsigned char informationHeader[informationHeaderSize];

    // Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // image width
    informationHeader[4] = m_width;
    informationHeader[5] = m_width >> 8;
    informationHeader[6] = m_width >> 16;
    informationHeader[7] = m_width >> 24;

    // image height
    informationHeader[8] = m_height;
    informationHeader[9] = m_height >> 8;
    informationHeader[10] = m_height >> 16;
    informationHeader[11] = m_height >> 24;


    // Planes
    informationHeader[12] = m_width;
    informationHeader[13] = m_width >> 8;

    // Bits per pixel (RGB)
    informationHeader[14] = 24;
    informationHeader[15] = 0;

    for (int i = 16; i < 40; ++i) {
        informationHeader[i] = 0;
    }

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r);
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g);
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b);
            unsigned char color[] = {b, g, r};
            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }

    f.close();
}

void Image::Update(int** mass) {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            SetColor(x, y, mass[y][x]);
        }
    }
}
