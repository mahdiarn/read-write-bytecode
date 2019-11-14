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
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            img.setPixel(i,j,* new QColor(img.pixelColor(i,j).red() * 0.21,img.pixelColor(i,j).green() * 0.72,img.pixelColor(i,j).blue() * 0.07));
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
