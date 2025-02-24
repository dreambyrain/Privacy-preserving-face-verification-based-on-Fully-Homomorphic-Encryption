#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>



#include <QMetaObject>
#include <QtConcurrent>
#include <fstream>

// OpenCV 头文件
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/opencv.hpp>

// SEAL 头文件
#include "seal/seal.h"

// C++ 标准库头文件
#include <fstream>
#include <vector>
#include <string>

#include <QImage>
#include <QTimer>

using namespace seal;


// 其他代码……


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置 QLabel 自动缩放内容
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setAlignment(Qt::AlignCenter);

    connect(ui->uploadButton, &QPushButton::clicked, this, &MainWindow::uploadFile);
    connect(ui->cameraButton, &QPushButton::clicked, this, &MainWindow::openCamera);
    connect(ui->encryptButton, &QPushButton::clicked, this, &MainWindow::encryptData);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    openCamera();
    timer->start(30);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::uploadFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Choose Picture", "", "Images(*.png *.xpm *.jpg)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "No image selected!");
        return;
    }

    // 读取图片
    cv::Mat img = cv::imread(filePath.toStdString());
    if (img.empty()) {
        QMessageBox::warning(this, "Error", "Failed to load image!");
        return;
    }

    // 转换为灰度图
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    // 加载 Haar 级联分类器(按照自己的路径修改)
    cv::CascadeClassifier faceDetector("/usr/  /opencv4/haarcascades/haarcascade_frontalface_default.xml");
    if (faceDetector.empty()) {
        QMessageBox::warning(this, "Error", "Failed to load face detection model!");
        return;
    }

    std::vector<cv::Rect> faces;
    faceDetector.detectMultiScale(img, faces, 1.1, 5, 0, cv::Size(100, 100));

    if (faces.empty()) {
        QMessageBox::warning(this, "Error", "No face detected!");
        return;
    }

    // 创建 LBPH 人脸识别器
    cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer = cv::face::LBPHFaceRecognizer::create();
    std::vector<cv::Mat> images;
    std::vector<int> labels;

    for (size_t i = 0; i < faces.size(); i++) {
        cv::Mat faceROI = img(faces[i]);
        images.push_back(faceROI);
        labels.push_back(1);  // 默认 ID，后续可以扩展
    }

    // 训练人脸识别模型并保存
    recognizer->train(images, labels);
    recognizer->save("trainer.yml");

    QMessageBox::information(this, "Success", "Facial data has been saved!");
}


// 使用 QTimer 读取视频，而不是 while 循环
void MainWindow::openCamera()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Choose Video File", "", "Videos (*.mp4 *.avi *.mov)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "No video selected!");
        return;
    }

    cap.open(filePath.toStdString());
    if (!cap.isOpened()) {
        QMessageBox::warning(this, "Error", "Could not open video file.");
        return;
    }

    qDebug() << "Video file opened successfully! Starting timer...";
    timer->start(33);
}


void MainWindow::updateFrame()
{
    if (!cap.isOpened()) {
        qDebug() << "VideoCapture is not open!";
        timer->stop();
        return;
    }

    cv::Mat frame;
    if (cap.read(frame)) {
        qDebug() << "Frame read successfully!";

        // 检查帧的大小和内容
        qDebug() << "Frame size: " << frame.cols << "x" << frame.rows;

        // 调整大小以适应 QLabel
        cv::resize(frame, frame, cv::Size(ui->imageLabel->width(), ui->imageLabel->height()));

        // 转换格式
        QImage img = matToQImage(frame);
        if (!img.isNull()) {
            qDebug() << "QImage created successfully!";
            ui->imageLabel->setPixmap(QPixmap::fromImage(img));
            ui->imageLabel->repaint();
        } else {
            qDebug() << "QImage is null!";
        }
    } else {
        qDebug() << "No more frames, stopping timer.";
        timer->stop();
    }
}





// mat 转 QImage
QImage MainWindow::matToQImage(const cv::Mat &mat)
{
    if (mat.empty()) return QImage();

    cv::Mat rgb;
    if (mat.channels() == 3) {
        cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
        return QImage(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    } else if (mat.channels() == 1) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    }
    return QImage();
}

//使用 QtConcurrent 运行加密，防止 UI 卡死
void MainWindow::encryptData()
{
    QtConcurrent::run([this]() {
        QString filePath = "/home/   /Program/build/trainer.yml";//根据自己的路径修改
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMetaObject::invokeMethod(this, [this]() {
                QMessageBox::warning(this, "错误", "无法打开 trainer.yml 文件！");
            }, Qt::QueuedConnection);
            return;
        }

        QString content = file.readAll();
        file.close();
        std::string stdContent = content.toStdString();
        std::vector<uint64_t> inputData;
        for (char c : stdContent) {
            inputData.push_back(static_cast<uint64_t>(static_cast<unsigned char>(c)));
        }

        EncryptionParameters parms(scheme_type::bfv);
        size_t poly_modulus_degree = 8192;
        parms.set_poly_modulus_degree(poly_modulus_degree);
        parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
        parms.set_plain_modulus(PlainModulus::Batching(poly_modulus_degree, 20));

        SEALContext context(parms);
        KeyGenerator keygen(context);
        PublicKey public_key;
        keygen.create_public_key(public_key);
        SecretKey secret_key = keygen.secret_key();
        Encryptor encryptor(context, public_key);
        BatchEncoder encoder(context);

        size_t slot_count = encoder.slot_count();
        if (inputData.size() < slot_count) {
            inputData.resize(slot_count, 0);
        } else if (inputData.size() > slot_count) {
            inputData.resize(slot_count);
        }

        Plaintext plain;
        encoder.encode(inputData, plain);
        Ciphertext encrypted;
        encryptor.encrypt(plain, encrypted);

        QString outPath = "/home/  /Ciphertext/encrypted_trainer.bin"; //根据自己的路径修改
        std::ofstream outFile(outPath.toStdString(), std::ios::binary);
        if (!outFile.is_open()) {
            QMetaObject::invokeMethod(this, [this]() {
                QMessageBox::warning(this, "错误", "无法保存加密数据到文件！");
            }, Qt::QueuedConnection);
            return;
        }
        encrypted.save(outFile);
        outFile.close();

        QMetaObject::invokeMethod(this, [this, outPath]() {
            QMessageBox::information(this, "加密", "全同态加密已成功完成，结果保存在：" + outPath);
        }, Qt::QueuedConnection);
    });
}
