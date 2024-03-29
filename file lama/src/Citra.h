#include <iostream>
#include <string>
#include <vector>

class Citra {
    private:
        std::vector<std::vector<std::vector<unsigned char>>> kanal;
        unsigned long long height, width;
        unsigned int maxValue;
        unsigned int bmpBitCount;
        std::vector<std::vector<unsigned int>> histogram;
    public:
        Citra();
        void loadFile(std::vector<unsigned char> byteFile, int fileType);
        void printCitra();
        void printKanal(int pos);
        void inverse();
        void generateHistogram();
        void printHistogram();
        void minImg(Citra);
        void plusImg(Citra);
        void andImg(Citra);
        void orImg(Citra);
        void brigthen(unsigned char nilai);
        void darken(unsigned char nilai);
        void calibrateBrightness(unsigned char nilai);
        void normalizeBrightness(unsigned char nilai);
        void flipX();
        void flipY();
        void translate(unsigned char x, unsigned char y);
        void notOperation();
        void convolution(unsigned char matriks[3][3]);
        void sharpen(unsigned char options);
        void rgbToGrayscale();
        void grayscaleToBinary();
        void zoomIn(int scaleX, int scaleY);
        void zoomOut(int scaleX, int scaleY);
        unsigned long long getWidth();
        unsigned long long getHeight();
        unsigned int getMaxValue();
        unsigned int getKanalSize();
        unsigned int getHistogramSize();
};