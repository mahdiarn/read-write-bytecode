#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OperasiGradien.h"
#include "OperasiLaplace.h"
#include <QDebug>
#include <QFileDialog>
#include <vector>
#include <math.h>

using namespace std;

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

const double pi = 3.14159265358979323846;

vector<vector<vector<int>>> listPoint;

void MainWindow::on_pushButton_clicked()
{
//    img.load("C:\\Users\\Arrw\\Desktop\\read-write-bytecode\\file lama\\examples\\mobil-3.bmp");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "C:/",
                                                        tr("Images (*.png *.xpm *.jpg)"));
    qDebug() << fileName;
    img.load(fileName);
    onShowImg();
}

void MainWindow::on_pushButton_2_clicked()
{
    slice();
    onShowImg();
}

void MainWindow::slice() {
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.format() == QImage::Format_Indexed8) {
                if (img.pixelIndex(i,j) <= 127) {
                    img.setPixel(i,j,0);
                } else {
                    img.setPixel(i,j,255);
                }
            } else {
                if ((img.pixelColor(i,j).red() * 0.299) + (img.pixelColor(i,j).green() * 0.587) + (img.pixelColor(i,j).blue() * 0.144) <= 127) {
                    img.setPixel(i,j,qRgb(0,0,0));
                } else {
                    img.setPixel(i,j,qRgb(255,255,255));
                }
            }
        }
    }
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
            if (img.format() != QImage::Format_Indexed8) {
                int r = img.pixelColor(i,j).red() + 1 < 255 ? img.pixelColor(i,j).red() + 1 : 255;
                int g = img.pixelColor(i,j).green() + 1 < 255 ? img.pixelColor(i,j).green() + 1 : 255;
                int b = img.pixelColor(i,j).blue() + 1 < 255 ? img.pixelColor(i,j).blue() + 1 : 255;
                img.setPixel(i,j,qRgb(r,g,b));
            } else {
                if (img.pixelIndex(i,j) < 255) {
                    img.setPixel(i,j,img.pixelIndex(i,j) + 1);
                }
            }
        }
    }
    onShowImg();
}

void MainWindow::on_minusBrightness_clicked()
{
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.format() != QImage::Format_Indexed8) {
                int r = img.pixelColor(i,j).red() - 1 > 0 ? img.pixelColor(i,j).red() - 1 : 0;
                int g = img.pixelColor(i,j).green() - 1 > 0? img.pixelColor(i,j).green() - 1 : 0;
                int b = img.pixelColor(i,j).blue() - 1 > 0? img.pixelColor(i,j).blue() - 1 : 0;
                img.setPixel(i,j,qRgb(r,g,b));
            } else {
                if (img.pixelIndex(i,j) > 0) {
                    img.setPixel(i,j,img.pixelIndex(i,j) - 1);
                }
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
            if (img.format() == QImage::Format_Indexed8) {
                int temp = img.pixelIndex(i,j);
                img.setPixel(i,j,img.pixelIndex(pos,j));
                img.setPixel(pos,j,temp);
            } else {
                int r = img.pixelColor(i,j).red();
                int g = img.pixelColor(i,j).green();
                int b = img.pixelColor(i,j).blue();
                int temp = qRgb(r,g,b);
                r = img.pixelColor(pos,j).red();
                g = img.pixelColor(pos,j).green();
                b = img.pixelColor(pos,j).blue();
                int newTemp = qRgb(r,g,b);
                img.setPixel(i,j,newTemp);
                img.setPixel(pos,j,temp);
            }
        }
    }
    onShowImg();
}

void MainWindow::on_flipY_clicked()
{
    for (int j = 0; j < img.height() / 2; j++) {
        for (int i = 0; i < img.width(); i++) {
            int pos = img.height() - j - 1;
            if (img.format() == QImage::Format_Indexed8) {
                int temp = img.pixelIndex(i,j);
                img.setPixel(i,j,img.pixelIndex(i,pos));
                img.setPixel(i,pos,temp);
            } else {
                int r = img.pixelColor(i,j).red();
                int g = img.pixelColor(i,j).green();
                int b = img.pixelColor(i,j).blue();
                int temp = qRgb(r,g,b);
                r = img.pixelColor(i,pos).red();
                g = img.pixelColor(i,pos).green();
                b = img.pixelColor(i,pos).blue();
                int newTemp = qRgb(r,g,b);
                img.setPixel(i,j,newTemp);
                img.setPixel(i,pos,temp);
            }
        }
    }
    onShowImg();
}

void MainWindow::on_negative_clicked()
{
    negative();
    onShowImg();
}

void MainWindow::negative() {
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.format() == QImage::Format_Indexed8) {
                img.setPixel(i,j,255-img.pixelIndex(i,j));
            } else {
                int r = 255-img.pixelColor(i,j).red();
                int g = 255-img.pixelColor(i,j).green();
                int b = 255-img.pixelColor(i,j).blue();
                img.setPixel(i,j,qRgb(r,g,b));
            }
        }
    }
}

void MainWindow::on_translate_clicked()
{
    QString xAxis = ui->translateX->text();
    QString yAxis = ui->translateY->text();
    int x = xAxis == NULL ? 0 : xAxis.toInt();
    int y = yAxis == NULL ? 0 : yAxis.toInt();

    translate(x,y);

    onShowImg();
}

void MainWindow::translate(int x, int y) {
    if (x >= 0) {
        for (int j = 0; j < img.height(); j++) {
            if (img.format() == QImage::Format_Indexed8) {
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
            } else {
                int tempxr[img.width()];
                int tempxg[img.width()];
                int tempxb[img.width()];
                for (int i = 0; i < img.width(); i++) {
                    if (i < x) {
                        tempxr[i] = 0;
                        tempxg[i] = 0;
                        tempxb[i] = 0;
                    } else {
                        tempxr[i] = img.pixelColor(i-x,j).red();
                        tempxg[i] = img.pixelColor(i-x,j).green();
                        tempxb[i] = img.pixelColor(i-x,j).blue();
                    }
                }
                for (int i = 0; i < img.width(); i++) {
                    img.setPixel(i,j,qRgb(tempxr[i],tempxg[i],tempxb[i]));
                }
            }
        }
    } else {
        x = img.width() - (x * -1);
        for (int j = 0; j < img.height(); j++) {
            if (img.format() == QImage::Format_Indexed8) {
                int tempx[img.width()];
                for (int i = 0; i < img.width(); i++) {
                    if (x < i) {
                        tempx[i] = 0;
                    } else {
                        tempx[i] = img.pixelIndex((img.width()-x-1)+i,j);
                    }
                }
                for (int i = 0; i < img.width(); i++) {
                    img.setPixel(i,j,tempx[i]);
                }
            } else {
                int tempxr[img.width()];
                int tempxg[img.width()];
                int tempxb[img.width()];
                for (int i = 0; i < img.width(); i++) {
                    if (x < i) {
                        tempxr[i] = 0;
                        tempxg[i] = 0;
                        tempxb[i] = 0;
                    } else {
                        tempxr[i] = img.pixelColor((img.width()-x-1)+i,j).red();
                        tempxg[i] = img.pixelColor((img.width()-x-1)+i,j).green();
                        tempxb[i] = img.pixelColor((img.width()-x-1)+i,j).blue();
                    }
                }
                for (int i = 0; i < img.width(); i++) {
                    img.setPixel(i,j,qRgb(tempxr[i],tempxg[i],tempxb[i]));
                }
            }
        }
    }

    if (y >= 0) {
        for (int i = 0; i < img.width(); i++) {
            if (img.format() == QImage::Format_Indexed8) {
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
            } else {
                int tempyr[img.height()];
                int tempyg[img.height()];
                int tempyb[img.height()];
                for (int j = 0; j < img.height(); j++) {
                    if (j < y) {
                        tempyr[j] = 0;
                        tempyg[j] = 0;
                        tempyb[j] = 0;
                    } else {
                        tempyr[j] = img.pixelColor(i,j-y).red();
                        tempyg[j] = img.pixelColor(i,j-y).green();
                        tempyb[j] = img.pixelColor(i,j-y).blue();
                    }
                }
                for (int j = 0; j < img.height(); j++) {
                    img.setPixel(i,j,qRgb(tempyr[j],tempyg[j],tempyb[j]));
                }
            }
        }
    } else {
        y = img.height() - (y * -1);
        for (int i = 0; i < img.width(); i++) {
            if (img.format() == QImage::Format_Indexed8) {
                int tempy[img.height()];
                for (int j = 0; j < img.height(); j++) {
                    if (y < j) {
                        tempy[j] = 0;
                    } else {
                        tempy[j] = img.pixelIndex(i,(img.height()-y-1)+j);
                    }
                }
                for (int j = 0; j < img.height(); j++) {
                    img.setPixel(i,j,tempy[j]);
                }
            } else {
                int tempyr[img.height()];
                int tempyg[img.height()];
                int tempyb[img.height()];
                for (int j = 0; j < img.height(); j++) {
                    if (y < j) {
                        tempyr[j] = 0;
                        tempyg[j] = 0;
                        tempyb[j] = 0;
                    } else {
                        tempyr[j] = img.pixelColor(i,(img.height()-y-1)+j).red();
                        tempyg[j] = img.pixelColor(i,(img.height()-y-1)+j).green();
                        tempyb[j] = img.pixelColor(i,(img.height()-y-1)+j).blue();
                    }
                }
                for (int j = 0; j < img.height(); j++) {
                    img.setPixel(i,j,qRgb(tempyr[j],tempyg[j],tempyb[j]));
                }
            }
        }
    }
}

void MainWindow::filterImg(vector<vector<int>> matriks) {
    QImage imgTemp = img;
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (j > 0 && i > 0 && i < img.width() - 1 && j < img.height() - 1) {
                if (img.format() == QImage::Format_Indexed8) {
                    vector<vector<int>> temp{ {img.pixelIndex(i-1,j-1),img.pixelIndex(i-1,j),img.pixelIndex(i-1,j+1)},
                                              {img.pixelIndex(i,j-1),img.pixelIndex(i,j),img.pixelIndex(i,j+1)},
                                              {img.pixelIndex(i+1,j-1),img.pixelIndex(i+1,j),img.pixelIndex(i+1,j+1)} };

                    int sum = 0;

                    for (int y = 0; y < 3; y++) {
                        for (int x = 0; x < 3; x++) {
                            sum += (temp.at(y).at(x) * matriks.at(y).at(x));
                        }
                    }

                    if (sum > 255) {
                        sum = 255;
                    } else if (sum < 0) {
                        sum = 0;
                    }

                    imgTemp.setPixel(i,j,sum);
                } else {
                    int tempr[3][3];
                    int tempg[3][3];
                    int tempb[3][3];

                    tempr[0][0] = img.pixelColor(i-1,j-1).red();
                    tempr[0][1] = img.pixelColor(i-1,j).red();
                    tempr[0][2] = img.pixelColor(i-1,j+1).red();
                    tempr[1][0] = img.pixelColor(i,j-1).red();
                    tempr[1][1] = img.pixelColor(i,j).red();
                    tempr[1][2] = img.pixelColor(i,j+1).red();
                    tempr[2][0] = img.pixelColor(i+1,j-1).red();
                    tempr[2][1] = img.pixelColor(i+1,j).red();
                    tempr[2][2] = img.pixelColor(i+1,j+1).red();

                    tempg[0][0] = img.pixelColor(i-1,j-1).green();
                    tempg[0][1] = img.pixelColor(i-1,j).green();
                    tempg[0][2] = img.pixelColor(i-1,j+1).green();
                    tempg[1][0] = img.pixelColor(i,j-1).green();
                    tempg[1][1] = img.pixelColor(i,j).green();
                    tempg[1][2] = img.pixelColor(i,j+1).green();
                    tempg[2][0] = img.pixelColor(i+1,j-1).green();
                    tempg[2][1] = img.pixelColor(i+1,j).green();
                    tempg[2][2] = img.pixelColor(i+1,j+1).green();

                    tempb[0][0] = img.pixelColor(i-1,j-1).blue();
                    tempb[0][1] = img.pixelColor(i-1,j).blue();
                    tempb[0][2] = img.pixelColor(i-1,j+1).blue();
                    tempb[1][0] = img.pixelColor(i,j-1).blue();
                    tempb[1][1] = img.pixelColor(i,j).blue();
                    tempb[1][2] = img.pixelColor(i,j+1).blue();
                    tempb[2][0] = img.pixelColor(i+1,j-1).blue();
                    tempb[2][1] = img.pixelColor(i+1,j).blue();
                    tempb[2][2] = img.pixelColor(i+1,j+1).blue();

                    int sumr = 0;
                    int sumg = 0;
                    int sumb = 0;

                    for (int y = 0; y < 3; y++) {
                        for (int x = 0; x < 3; x++) {
                            sumr += (tempr[y][x] * matriks.at(y).at(x));
                            sumg += (tempg[y][x] * matriks.at(y).at(x));
                            sumb += (tempb[y][x] * matriks.at(y).at(x));
                        }
                    }

                    if (sumr > 255) {
                        sumr = 255;
                    } else if (sumr < 0) {
                        sumr = 0;
                    }

                    if (sumg > 255) {
                        sumg = 255;
                    } else if (sumg < 0) {
                        sumg = 0;
                    }

                    if (sumb > 255) {
                        sumb = 255;
                    } else if (sumb < 0) {
                        sumb = 0;
                    }

                    imgTemp.setPixel(i,j,qRgb(sumr,sumg,sumb));
                }
            }
        }
    }
    img = imgTemp;
}

void MainWindow::on_sharpen_clicked()
{
    vector<vector<int>> matriks{ {0,-1,0},
                                 {-1,5,-1},
                                 {0,-1,0} };
    filterImg(matriks);
    onShowImg();
}

void MainWindow::on_grayscale_clicked()
{

    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.pixelColor(i,j).red() != img.pixelColor(i,j).green() && img.pixelColor(i,j).red() != img.pixelColor(i,j).blue() && img.pixelColor(i,j).blue() != img.pixelColor(i,j).green()){
                int gray = (img.pixelColor(i,j).red() * 0.299) + (img.pixelColor(i,j).green() * 0.587) + (img.pixelColor(i,j).blue() * 0.144);
                img.setPixel(i,j,qRgb(gray,gray,gray));
            }
        }
    }
    onShowImg();
}

void MainWindow::on_smoothen_clicked()
{
    vector<vector<int>> matriks{ {0,1,0},
                                 {1,-1,1},
                                 {0,1,0} };
    filterImg(matriks);
    onShowImg();
}

void MainWindow::on_rotate_clicked()
{
    QString degText = ui->rotateDeg->text();
    int deg = degText == NULL ? 0 : degText.toInt();

    QImage imgTemp = img;
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            imgTemp.setPixel(i,j,0);
        }
    }

    if (deg % 90 != 0) {
        int newX,newY;
        for (int j = 0; j < img.height(); j++) {
            for (int i = 0; i < img.width(); i++) {
                newX = (i*cos(deg*pi/180)) - (j*sin(deg*pi/180));
                newY = (i*sin(deg*pi/180)) + (j*cos(deg*pi/180));
                if (img.format() == QImage::Format_Indexed8) {
                    if (newX >= 0 && newY >= 0 && newX < img.width() && newY < img.height()) {
                        imgTemp.setPixel(newX,newY,img.pixelIndex(i,j));
                    }
                } else {
                    if (newX >= 0 && newY >= 0 && newX < img.width() && newY < img.height()) {
                        int r = img.pixelColor(i,j).red();
                        int g = img.pixelColor(i,j).green();
                        int b = img.pixelColor(i,j).blue();
                        imgTemp.setPixel(newX,newY,qRgb(r,g,b));
                    }
                }
            }
        }
    } else {
        int k;
        for (int x = 0; x < deg / 90; x++) {
            for (int i = 0; i < img.width(); i++) {
                k = img.height() - 1;
                for (int j = 0; j < img.height(); j++) {
                    if (img.format() == QImage::Format_Indexed8) {
                        imgTemp.setPixel(k,i,img.pixelIndex(i,j));
                    } else {
                        int r = img.pixelColor(i,j).red();
                        int g = img.pixelColor(i,j).green();
                        int b = img.pixelColor(i,j).blue();
                        imgTemp.setPixel(k,i,qRgb(r,g,b));
                    }
                    k--;
                }
            }
            img = imgTemp;
        }
    }
    img = imgTemp;
    onShowImg();
}

void MainWindow::on_notBtn_clicked()
{
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.format() == QImage::Format_Indexed8) {
                img.setPixel(i,j,255-img.pixelIndex(i,j));
            } else {
                int r = 255-img.pixelColor(i,j).red();
                int g = 255-img.pixelColor(i,j).green();
                int b = 255-img.pixelColor(i,j).blue();
                img.setPixel(i,j,qRgb(r,g,b));
            }
        }
    }
    onShowImg();
}

void MainWindow::on_saveBtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("Images (*.bmp)"));
    img.save(fileName,"BMP");
}

void MainWindow::on_zoomBtn_clicked()
{
    zoomIn();
    onShowImg();
}

void MainWindow::on_zoomOutBtn_clicked()
{
    zoomOut();
    onShowImg();
}

void MainWindow::zoomIn() {
    QImage imgZoom = img;
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.format() == QImage::Format_Indexed8) {
                if ((i*2)+1 < img.width() && (j*2)+1 < img.height()) {
                    imgZoom.setPixel(i*2,j*2,img.pixelIndex(i,j));
                    imgZoom.setPixel(i*2,(j*2)+1,img.pixelIndex(i,j));
                    imgZoom.setPixel((i*2)+1,j*2,img.pixelIndex(i,j));
                    imgZoom.setPixel((i*2)+1,(j*2)+1,img.pixelIndex(i,j));
                }
            } else {
                if ((i*2)+1 < img.width() && (j*2)+1 < img.height()) {
                    int r = img.pixelColor(i,j).red();
                    int g = img.pixelColor(i,j).green();
                    int b = img.pixelColor(i,j).blue();
                    imgZoom.setPixel(i*2,j*2,qRgb(r,g,b));
                    imgZoom.setPixel(i*2,(j*2)+1,qRgb(r,g,b));
                    imgZoom.setPixel((i*2)+1,j*2,qRgb(r,g,b));
                    imgZoom.setPixel((i*2)+1,(j*2)+1,qRgb(r,g,b));
                }
            }
        }
    }
    img = imgZoom;
}

void MainWindow::zoomOut()
{
    QImage imgZoom = img;
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (img.format() == QImage::Format_Indexed8) {
                if ((i*2)+1 < img.width() && (j*2)+1 < img.height()) {
                    imgZoom.setPixel(i,j,img.pixelIndex(i*2,j*2));
                } else {
                    imgZoom.setPixel(i,j,0);
                }
            } else {
                if ((i*2)+1 < img.width() && (j*2)+1 < img.height()) {
                    int r = img.pixelColor(i*2,j*2).red();
                    int g = img.pixelColor(i*2,j*2).green();
                    int b = img.pixelColor(i*2,j*2).blue();
                    imgZoom.setPixel(i,j,qRgb(r,g,b));
                } else {
                    imgZoom.setPixel(i,j,qRgb(0,0,0));
                }
            }
        }
    }
    img = imgZoom;
}

void MainWindow::on_recognize_clicked()
{
    translate(-img.width()/5,-img.height()/4);
    zoomIn();
    sharpen();
    slice();
    vector<int> bw = bwCount();
    if (bw.at(0) > bw.at(1)) {
        negative();
    }
    translate(-img.width()/10,0);
    translate(img.width()/5,0);
    translate(-img.width()/10,0);
    //smear();
    edgeDetect();
    translate(0,-img.height()/3);
    translate(0,img.height()/2);
    translate(0,-img.height()/2);
    translate(-img.width()/10,0);
    translate(0,-img.height()/10);
    //smearBlack();
    //noiseReductionY();
    /*
    vector<vector<int>> pts;
    int count = 0;
    for (int j = 0; j < img.height(); j++) {
        for (int i = img.width()/5; i < img.width()-(img.width()/5); i++) {
            if (img.pixelColor(i,j).red() == 255) {
                pts.push_back({i,j});
            }
        }
    }
    translate(-img.width()/5,searchY(pts));
    */
    onShowImg();
}

int MainWindow::searchY(vector<vector<int>> li) {
    int idx = 0;
    for (int i = 1; i < li.size(); i++) {
        if (li.at(i).at(0) < li.at(idx).at(0)) {
            idx = i;
        }
    }
    return li.at(idx).at(1);
}

void MainWindow::on_showEdge_clicked()
{
    vector<vector<int>> matriks{ {1,1,1},
                                 {1,-8,1},
                                 {1,1,1} };
    filterImg(matriks);
    onShowImg();
}

void MainWindow::smear(){
    int count;
    if (img.format() == QImage::Format_Indexed8) {
        for (int j = 0; j < img.height(); j++) {
            count = 0;
            for (int i = 0; i < img.width(); i++) {
                if (img.pixelIndex(i,j) == 0) {
                    count++;
                }
            }
            if (count < (img.width()/5)+100 || count > (img.width()/5)+250) {
                for (int i = 0; i < img.width(); i++) {
                    img.setPixel(i,j,255);
                }
            }
        }
    } else {
        for (int j = 0; j < img.height(); j++) {
            count = 0;
            for (int i = 0; i < img.width(); i++) {
                if (img.pixelColor(i,j).red() == 0) {
                    count++;
                }
            }
            if (count < (img.width()/5)+100 || count > (img.width()/5)+250) {
                for (int i = 0; i < img.width(); i++) {
                    img.setPixel(i,j,qRgb(255,255,255));
                }
            }
        }
    }
}

void MainWindow::smearBlack(){
    int count;
    if (img.format() == QImage::Format_Indexed8) {
        for (int j = 0; j < img.height(); j++) {
            count = 0;
            for (int i = 0; i < img.width(); i++) {
                if (img.pixelIndex(i,j) == 255) {
                    count++;
                }
            }
            if (count < 150 || count > 270) {
                for (int i = 0; i < img.width(); i++) {
                    img.setPixel(i,j,0);
                }
            }
        }
    } else {
        for (int j = 0; j < img.height(); j++) {
            count = 0;
            for (int i = 0; i < img.width(); i++) {
                if (img.pixelColor(i,j).red() == 255) {
                    count++;
                }
            }
            if (count < 10 || count > 100) {
                for (int i = 0; i < img.width(); i++) {
                    img.setPixel(i,j,qRgb(0,0,0));
                }
            }
        }
    }
}

void MainWindow::noiseReductionY() {
    if (img.format() == QImage::Format_Indexed8) {
        for (int j = 0; j < img.height(); j++) {
            for (int i = 0; i < img.width(); i++) {
                if (i <= img.width()/6 || i >= img.width() - (img.width()/6)) {
                    if (img.pixelIndex(i,j) == 255) {
                        img.setPixel(i,j,0);
                    }
                }
            }
        }
    } else {
        for (int j = 0; j < img.height(); j++) {
            for (int i = 0; i < img.width(); i++) {
                if (i <= img.width()/6 || i >= img.width() - (img.width()/6)) {
                    if (img.pixelColor(i,j).red() == 255) {
                        img.setPixel(i,j,qRgb(0,0,0));
                    }
                }
            }
        }
    }
}

void MainWindow::on_smear_clicked()
{
    /*vector<int> bw = bwCount();
    if (bw.at(0) > bw.at(1)) {
        smearBlack();
    } else {
        smear();
    }*/
    dilate();
    onShowImg();
}

void MainWindow::dilate() {
    vector<vector<int>> matriks{ {1,1,1},
                                 {1,1,1},
                                 {1,1,1} };
    filterImg(matriks);
}

void MainWindow::sharpen() {
    vector<vector<int>> matriks{ {1,1,1},
                                 {1,-6,1},
                                 {1,1,1} };
    filterImg(matriks);
}

void MainWindow::edgeDetect() {
    vector<vector<int>> matriks{ {1,1,1},
                                 {1,-8,1},
                                 {1,1,1} };
    filterImg(matriks);
}

void MainWindow::cll() {
    vector<vector<int>> listPt;
    for (int j = 0; j < img.height(); j++) {
        for (int i = 0; i < img.width(); i++) {
            if (!searchPt(listPt,i,j)) {

            }
        }
    }
}

bool MainWindow::searchPt(vector<vector<int>> li, int x, int y) {
    for (int i = 0; i < li.size(); i++) {
        if (li.at(i).at(0) == x && li.at(i).at(1) == y) {
            return true;
        }
    }
    return false;
}

vector<int> MainWindow::bwCount() {
    vector<int> res = {0,0};

    if (img.format() == QImage::Format_Indexed8) {
        for (int j = 0; j < img.height(); j++) {
            for (int i = 0; i < img.width(); i++) {
                if (img.pixelIndex(i,j) == 0) {
                    res.at(0)++;
                } else {
                    res.at(1)++;
                }
            }
        }
    } else {
        for (int j = 0; j < img.height(); j++) {
            for (int i = 0; i < img.width(); i++) {
                if (img.pixelColor(i,j).red() == 0) {
                    res.at(0)++;
                } else {
                    res.at(1)++;
                }
            }
        }
    }

    return res;
}
