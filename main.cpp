#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.resize(1280,720);
    m.show();
    /*
    int matriks[3][3];
    matriks[0][0] = -1;
    matriks[0][1] = -1;
    matriks[0][2] = -1;
    matriks[1][0] = -1;
    matriks[1][1] = 9;
    matriks[1][2] = -1;
    matriks[2][0] = -1;
    matriks[2][1] = -1;
    matriks[2][2] = -1;
    for (int i = 0; i < img.height(); i++) {
        for (int j = 0; j < img.width(); j++) {
            if (j != 0 && i != 0 && j != img.width() - 1 && i != img.height() - 1) {
                int temp[3][3];
                temp[0][0] = img.pixelIndex(i-1,j-1);
                temp[0][1] = img.pixelIndex(i-1,j);
                temp[0][2] = img.pixelIndex(i-1,j+1);
                temp[1][0] = img.pixelIndex(i,j-1);
                temp[1][1] = img.pixelIndex(i,j);
                temp[1][2] = img.pixelIndex(i,j+1);
                temp[2][0] = img.pixelIndex(i+1,j-1);
                temp[2][1] = img.pixelIndex(i+1,j);
                temp[2][2] = img.pixelIndex(i+1,j+1);

                int sum = 0;

                for (int y = 0; y < 3; y++) {
                    for (int x = 0; x < 3; x++) {
                        sum += (temp[y][x] * matriks[y][x]);
                    }
                }

                if (sum > 255) {
                    sum = 255;
                } else if (sum < 0) {
                    sum = 0;
                }

                img.setPixel(i,j,sum);
            }
        }
    }
    */

    /*
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            img.setPixelColor(i,j,* new QColor(img.pixelColor(i,j).red() * 0.21,img.pixelColor(i,j).green() * 0.72,img.pixelColor(i,j).blue() * 0.07));
        }
    }
    */

    /*
    QImage imgZoom;
    imgZoom.load("C:\\Users\\Arrw\\Desktop\\read-write-bytecode\\examples\\lena_gray.bmp");
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            img.setPixel(i,j,0);
        }
    }
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            img.setPixel(i*2,j*2,imgZoom.pixelIndex(i,j));
            img.setPixel(i*2,(j+1)*2,imgZoom.pixelIndex(i,j));
            img.setPixel((i+1)*2,j*2,imgZoom.pixelIndex(i,j));
            img.setPixel((i+1)*2,(j+1)*2,imgZoom.pixelIndex(i,j));
        }
    }
    */

    return a.exec();
}
