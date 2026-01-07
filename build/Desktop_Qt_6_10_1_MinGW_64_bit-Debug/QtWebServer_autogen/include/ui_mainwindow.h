/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *centralwidget_2;
    QVBoxLayout *verticalLayout_7;
    QFormLayout *formLayout_4;
    QLabel *portLabel;
    QLineEdit *portEdit_4;
    QLineEdit *rootEdit_4;
    QPushButton *startBtn_4;
    QLabel *rootLabel;
    QLabel *recvLabel_4;
    QLabel *sendLabel_4;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(339, 191);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget_2 = new QWidget(centralwidget);
        centralwidget_2->setObjectName("centralwidget_2");
        centralwidget_2->setGeometry(QRect(60, 20, 221, 111));
        verticalLayout_7 = new QVBoxLayout(centralwidget_2);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName("formLayout_4");
        portLabel = new QLabel(centralwidget_2);
        portLabel->setObjectName("portLabel");

        formLayout_4->setWidget(0, QFormLayout::ItemRole::LabelRole, portLabel);

        portEdit_4 = new QLineEdit(centralwidget_2);
        portEdit_4->setObjectName("portEdit_4");

        formLayout_4->setWidget(0, QFormLayout::ItemRole::FieldRole, portEdit_4);

        rootEdit_4 = new QLineEdit(centralwidget_2);
        rootEdit_4->setObjectName("rootEdit_4");

        formLayout_4->setWidget(1, QFormLayout::ItemRole::FieldRole, rootEdit_4);

        startBtn_4 = new QPushButton(centralwidget_2);
        startBtn_4->setObjectName("startBtn_4");

        formLayout_4->setWidget(2, QFormLayout::ItemRole::SpanningRole, startBtn_4);

        rootLabel = new QLabel(centralwidget_2);
        rootLabel->setObjectName("rootLabel");

        formLayout_4->setWidget(1, QFormLayout::ItemRole::LabelRole, rootLabel);


        verticalLayout_7->addLayout(formLayout_4);

        recvLabel_4 = new QLabel(centralwidget_2);
        recvLabel_4->setObjectName("recvLabel_4");

        verticalLayout_7->addWidget(recvLabel_4);

        sendLabel_4 = new QLabel(centralwidget_2);
        sendLabel_4->setObjectName("sendLabel_4");

        verticalLayout_7->addWidget(sendLabel_4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 339, 17));
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
        portLabel->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243:", nullptr));
        startBtn_4->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\346\234\215\345\212\241\345\231\250", nullptr));
        rootLabel->setText(QCoreApplication::translate("MainWindow", "\346\240\271\347\233\256\345\275\225:", nullptr));
        recvLabel_4->setText(QCoreApplication::translate("MainWindow", "\345\267\262\346\216\245\346\224\266: 0 \345\255\227\350\212\202", nullptr));
        sendLabel_4->setText(QCoreApplication::translate("MainWindow", "\345\267\262\345\217\221\351\200\201: 0 \345\255\227\350\212\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
