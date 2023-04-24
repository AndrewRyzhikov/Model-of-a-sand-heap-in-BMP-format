#include <iostream>
#include "Sandpile.h"
#include "Image.h"


Sandpile::Sandpile() {}

void Sandpile::SetWidth(int width) {
    width_ = width;
}

void Sandpile::SetHeight(int height) {
    height_ = height;
}

void Sandpile::SetFreq(int freq) {
    freq_ = freq;
}

void Sandpile::SetMaxIter(int max_iter) {
    maxIter_ = max_iter;
}

void Sandpile::SetCell(int y, int x, int num) {
    grid_[y][x] = num;
}

void Sandpile::CreatGrid() {
    grid_= new int *[height_];
    for (int i = 0; i < height_; i++) {
        grid_[i] = new int[width_];
        for (int j = 0; j < width_; j++) {
            grid_[i][j] = 0;
        }
    }
}

int Sandpile::GetCell(int y, int x) {
    return grid_[y][x];
}

int Sandpile::GetWidth() {
    return width_;
}

int Sandpile::GetHeight() {
    return height_;
}

int Sandpile::GetFreq() {
    return freq_;
}

int Sandpile::GetMaxIter() {
    return maxIter_;
}




void Sandpile::Expend(int** &Grid) {
    int** newGrid = new int*[height_ + 2];
    for (int y = 0; y < height_ + 2; ++y) {
        newGrid[y] = new int[width_ + 2];
        for (int x = 0; x < width_ + 2; ++x) {
            if (x == 0 or y == 0 or x == width_ + 2 - 1 or y == height_ + 2 - 1) {
                newGrid[y][x] = 0;
            } else {
                newGrid[y][x] = grid_[y - 1][x - 1];
            }
        }
    }

    for (int y = 0; y < height_ ; ++y) {
        delete grid_[y];
        delete Grid[y];
    }
    delete[] grid_;
    delete[] Grid;

    height_ += 2, width_ += 2;

    grid_ = newGrid;

    Grid = new int * [height_];
    for (int y = 0; y < height_; ++y) {
        Grid[y] = new int[width_];
        for (int x = 0; x < width_; ++x) {
            Grid[y][x] = grid_[y][x];
        }
    }
}

void Sandpile::Scatter() {
    Image *image = new Image(GetWidth(), GetHeight());
    bool flag = true;
    int **newGrid = new int *[height_];
    for (int y = 0; y < height_; ++y) {
        newGrid[y] = new int[width_];
        for (int x = 0; x < width_; ++x) {
            newGrid[y][x] = grid_[y][x];
        }
    }
    int count = 0;
    while (flag and count < maxIter_) {
        flag = false;
        for (int y = 0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
                if (grid_[y][x] >= 4) {
                    flag = true;

                    if (x == 0 or y == 0 or x == width_ - 1 or y == height_ - 1) {
                        x++, y++;
                        Expend(newGrid);
                        delete image;
                        image = new Image(width_, height_);
                        image->Update(grid_);
                    }
                    newGrid[y][x] -= 4;
                    newGrid[y][x + 1] += 1;
                    newGrid[y][x - 1] += 1;
                    newGrid[y - 1][x] += 1;
                    newGrid[y + 1][x] += 1;
                }
            }
        }
        for (int y = 0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
                grid_[y][x] = newGrid[y][x];
                if (count % freq_ == 0) {
                    image->SetColor(x, y, newGrid[y][x]);
                }
            }
        }
        if (count % freq_ == 0) {
            std::string path = path_ + std::to_string(count) + ".bmp";
            image->Export(path);
        }
        count++;
    }
}

void Sandpile::SetPath(char *path) {
    path_ = path;
}

char* Sandpile::GetPath() {
    return path_;
}
