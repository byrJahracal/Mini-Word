/********************************************************************************
** Form generated from reading UI file 'replacewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPLACEWINDOW_H
#define UI_REPLACEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReplaceWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *search;
    QPushButton *replace;
    QPushButton *relpace_all;
    QPushButton *cancel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ReplaceWindow)
    {
        if (ReplaceWindow->objectName().isEmpty())
            ReplaceWindow->setObjectName(QStringLiteral("ReplaceWindow"));
        ReplaceWindow->resize(543, 234);
        centralwidget = new QWidget(ReplaceWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 60, 72, 15));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 110, 72, 15));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(140, 60, 231, 21));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(140, 110, 231, 21));
        search = new QPushButton(centralwidget);
        search->setObjectName(QStringLiteral("search"));
        search->setGeometry(QRect(410, 30, 93, 28));
        replace = new QPushButton(centralwidget);
        replace->setObjectName(QStringLiteral("replace"));
        replace->setGeometry(QRect(410, 70, 93, 28));
        relpace_all = new QPushButton(centralwidget);
        relpace_all->setObjectName(QStringLiteral("relpace_all"));
        relpace_all->setGeometry(QRect(410, 110, 93, 28));
        cancel = new QPushButton(centralwidget);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setGeometry(QRect(410, 150, 93, 28));
        ReplaceWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ReplaceWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 543, 26));
        ReplaceWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ReplaceWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ReplaceWindow->setStatusBar(statusbar);

        retranslateUi(ReplaceWindow);

        QMetaObject::connectSlotsByName(ReplaceWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ReplaceWindow)
    {
        ReplaceWindow->setWindowTitle(QApplication::translate("ReplaceWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("ReplaceWindow", "\346\237\245\346\211\276\345\206\205\345\256\271\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("ReplaceWindow", "\346\233\277\346\215\242\344\270\272\357\274\232", Q_NULLPTR));
        search->setText(QApplication::translate("ReplaceWindow", "\346\237\245\346\211\276\344\270\213\344\270\200\344\270\252", Q_NULLPTR));
        replace->setText(QApplication::translate("ReplaceWindow", "\346\233\277\346\215\242", Q_NULLPTR));
        relpace_all->setText(QApplication::translate("ReplaceWindow", "\346\233\277\346\215\242\345\205\250\351\203\250", Q_NULLPTR));
        cancel->setText(QApplication::translate("ReplaceWindow", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReplaceWindow: public Ui_ReplaceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLACEWINDOW_H
