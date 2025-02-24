#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void uploadFile(); //Declare the slot function for uploading files.
    void openCamera();
    void encryptData();
    void updateFrame();
private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    QTimer *timer;

    QImage matToQImage(const cv::Mat& mat);
};
#endif // MAINWINDOW_H
