#ifndef LABWORK_3_ANDREWRYZHIKOV_IMAGE_H
#define LABWORK_3_ANDREWRYZHIKOV_IMAGE_H

#include <fstream>

struct Color {
    uint8_t r, g, b;

    Color();

    Color(uint8_t r, uint8_t g, uint8_t b);
};


class Image {
public:
    Image(int width, int height);

    Color GetColor(int x, int y) const;

    void SetColor(int x, int y, int colorPreset);

    void Update (int** mass);

    void Export(const std::string& path) const;

private:
    int m_width;
    int m_height;
    Color* m_colors;
};


#endif //LABWORK_3_ANDREWRYZHIKOV_IMAGE_H
