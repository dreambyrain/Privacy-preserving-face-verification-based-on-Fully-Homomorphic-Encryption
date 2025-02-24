/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *imageLabel;
    QPushButton *uploadButton;
    QPushButton *cameraButton;
    QPushButton *encryptButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        imageLabel = new QLabel(centralwidget);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setGeometry(QRect(240, 70, 301, 221));
        uploadButton = new QPushButton(centralwidget);
        uploadButton->setObjectName("uploadButton");
        uploadButton->setGeometry(QRect(40, 420, 151, 71));
        cameraButton = new QPushButton(centralwidget);
        cameraButton->setObjectName("cameraButton");
        cameraButton->setGeometry(QRect(290, 420, 151, 71));
        encryptButton = new QPushButton(centralwidget);
        encryptButton->setObjectName("encryptButton");
        encryptButton->setGeometry(QRect(570, 420, 151, 71));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        imageLabel->setText(QCoreApplication::translate("MainWindow", "imageLabel", nullptr));
        uploadButton->setText(QCoreApplication::translate("MainWindow", "uploadButton", nullptr));
        cameraButton->setText(QCoreApplication::translate("MainWindow", "cameraButton", nullptr));
        encryptButton->setText(QCoreApplication::translate("MainWindow", "encryptButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
