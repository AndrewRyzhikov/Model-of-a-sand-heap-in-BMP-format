#ifndef LAB3_SANDPILE_H
#define LAB3_SANDPILE_H

class Sandpile {
public:
    Sandpile();

    void CreatGrid();

    void SetPath(char* path);
    char* GetPath();

    void SetWidth(int width);
    int GetWidth();

    void SetHeight(int height);
    int GetHeight();

    void SetFreq(int freq);
    int GetFreq();

    void SetMaxIter(int max_iter);
    int GetMaxIter();

    void SetCell(int y, int x, int num);
    int GetCell(int y, int x);

    void Scatter();

    void Expend(int** &Grid);


private:
    int width_;
    int height_;
    int maxIter_;
    int freq_;
    char* path_;
    int** grid_;
};


#endif //LAB3_SANDPILE_H
