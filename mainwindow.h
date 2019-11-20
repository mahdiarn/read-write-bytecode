#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void onShowImg();

    void on_plusBrightness_clicked();

    void on_minusBrightness_clicked();

    void on_flipX_clicked();

    void on_flipY_clicked();

    void on_negative_clicked();

    void on_translate_clicked();

    void filterImg(vector<vector<int>> matriks);

    void on_sharpen_clicked();

    void on_grayscale_clicked();

    void on_smoothen_clicked();

    void on_rotate_clicked();

    void on_notBtn_clicked();

    void on_saveBtn_clicked();

    void on_zoomBtn_clicked();

    void on_zoomOutBtn_clicked();

    void zoomIn();

    void zoomOut();

    void translate(int x, int y);

    void slice();

    void on_recognize_clicked();

    void on_showEdge_clicked();

    void smear();

    void on_smear_clicked();

    vector<int> bwCount();

    void negative();

    void smearBlack();

    void noiseReductionY();

    void dilate();

    void sharpen();

    void edgeDetect();

    void cll();

    bool searchPt(vector<vector<int>> li, int x, int y);

    int searchY(vector<vector<int>> li);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
