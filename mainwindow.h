#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_sharpen_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
