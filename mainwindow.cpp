#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage img;

void MainWindow::on_pushButton_clicked()
{
    img.load("C:\\Users\\Arrw\\Desktop\\read-write-bytecode\\file lama\\examples\\lena_gray.bmp");
    onShowImg();
}

void MainWindow::on_pushButton_2_clicked()
{
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.pixelIndex(i,j) <= 127) {
                img.setPixel(i,j,0);
            } else {
                img.setPixel(i,j,255);
            }
        }
    }
    onShowImg();
}

void MainWindow::onShowImg()
{
    ui->gambar->setPixmap(QPixmap::fromImage(img));
    ui->gambar->show();
}

void MainWindow::on_plusBrightness_clicked()
{
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.pixelIndex(i,j) < 255) {
                img.setPixel(i,j,img.pixelIndex(i,j) + 1);
            }
        }
    }
    onShowImg();
}

void MainWindow::on_minusBrightness_clicked()
{
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.pixelIndex(i,j) > 0) {
                img.setPixel(i,j,img.pixelIndex(i,j) - 1);
            }
        }
    }
    onShowImg();
}

void MainWindow::on_flipX_clicked()
{
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width() / 2; i++) {
            int pos = img.width() - i - 1;
            int temp = img.pixelIndex(i,j);
            img.setPixel(i,j,img.pixelIndex(pos,j));
            img.setPixel(pos,j,temp);
        }
    }
    onShowImg();
}

void MainWindow::on_flipY_clicked()
{
    for (int j = 0; j < img.height() / 2; j++) {
        for (int i = 0; i < img.width(); i++) {
            int pos = img.height() - j - 1;
            int temp = img.pixelIndex(i,j);
            img.setPixel(i,j,img.pixelIndex(i,pos));
            img.setPixel(i,pos,temp);
        }
    }
    onShowImg();
}

void MainWindow::on_negative_clicked()
{
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            img.setPixel(i,j,255-img.pixelIndex(i,j));
        }
    }
    onShowImg();
}

void MainWindow::on_translate_clicked()
{
    QString xAxis = ui->translateX->text();
    QString yAxis = ui->translateY->text();
    int x = xAxis == NULL ? 0 : xAxis.toInt();
    int y = yAxis == NULL ? 0 : yAxis.toInt();

    if (x != 0) {
        for (int j = 0; j < img.height(); j++) {
            int tempx[img.width()];
            for (int i = 0; i < img.width(); i++) {
                if (i < x) {
                    tempx[i] = 0;
                } else {
                    tempx[i] = img.pixelIndex(i-x,j);
                }
            }
            for (int i = 0; i < img.width(); i++) {
                img.setPixel(i,j,tempx[i]);
            }
        }
    }

    if (y != 0) {
        for (int i = 0; i < img.width(); i++) {
            int tempy[img.height()];
            for (int j = 0; j < img.height(); j++) {
                if (j < y) {
                    tempy[j] = 0;
                } else {
                    tempy[j] = img.pixelIndex(i,j-y);
                }
            }
            for (int j = 0; j < img.height(); j++) {
                img.setPixel(i,j,tempy[j]);
            }
        }
    }

    onShowImg();
}

void MainWindow::on_sharpen_clicked()
{
    QImage imgTemp = img;
    int matriks[3][3];
    matriks[0][0] = 0;
    matriks[0][1] = -1;
    matriks[0][2] = 0;
    matriks[1][0] = -1;
    matriks[1][1] = 4;
    matriks[1][2] = -1;
    matriks[2][0] = 0;
    matriks[2][1] = -1;
    matriks[2][2] = 0;
    int temp[3][3];
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (j > 0 && i > 0 && i < img.width() - 1 && j < img.height() - 1) {
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

                imgTemp.setPixel(i,j,sum);
            }
        }
    }
    img = imgTemp;
    onShowImg();
}
