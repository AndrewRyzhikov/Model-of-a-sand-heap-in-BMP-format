#include <iostream>
#include <fstream>
#include "Sandpile.h"
#include "cstring"

void AddGrains(char* filename, Sandpile* sandpile) {
    sandpile->CreatGrid();
    std::ifstream file;
    file.open(filename);
    int x, y, num;
    while(file >> x >> y >> num) {
        x--;
        y--;
        sandpile->SetCell(y, x, num);
    }
    file.close();
}


void Parse(int count, char* arguments[], Sandpile* sandpile) {
    char* filename;
    for (int i = 1; i < count; ++i) {
        if (strcmp("-l", arguments[i]) == 0 or strcmp("--length", arguments[i]) == 0) {
            sandpile->SetWidth(atoi(arguments[++i]));
        }
        if (strcmp("-w", arguments[i]) == 0 or strcmp("--width", arguments[i]) == 0) {
            sandpile->SetHeight(atoi(arguments[++i]));
            i++;
        }
        if (strcmp("-m", arguments[i]) == 0 or strcmp("--max-iter", arguments[i]) == 0) {
            sandpile->SetMaxIter(atoi(arguments[++i]));
            i++;
        }
        if (strcmp("-f", arguments[i]) == 0 or strcmp("--freq", arguments[i]) == 0) {
            sandpile->SetFreq(atoi(arguments[++i]));
            i++;
        }
        if (strcmp("-o", arguments[i]) == 0 or strcmp("--output", arguments[i]) == 0) {
            sandpile->SetPath(arguments[++i]);
        }
        if (strcmp("-i", arguments[i]) == 0 or strcmp("--input", arguments[i]) == 0) {
            filename = arguments[++i];
        }
    }
    AddGrains(filename, sandpile);
}

int main(int argc, char* argv[]) {
    Sandpile* sandpile = new Sandpile;
    Parse(argc, argv, sandpile);
    sandpile->Scatter();
}