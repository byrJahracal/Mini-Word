/********************************************************************************
** Form generated from reading UI file 'miniword.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIWORD_H
#define UI_MINIWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiniWord
{
public:
    QAction *action_newFile;
    QAction *action_openfile;
    QAction *action_savefile;
    QAction *action_quit;
    QAction *action_search;
    QAction *action_replace;
    QAction *action_save_as;
    QAction *action_addsize;
    QAction *action_cutsize;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MiniWord)
    {
        if (MiniWord->objectName().isEmpty())
            MiniWord->setObjectName(QStringLiteral("MiniWord"));
        MiniWord->resize(400, 300);
        action_newFile = new QAction(MiniWord);
        action_newFile->setObjectName(QStringLiteral("action_newFile"));
        action_openfile = new QAction(MiniWord);
        action_openfile->setObjectName(QStringLiteral("action_openfile"));
        action_savefile = new QAction(MiniWord);
        action_savefile->setObjectName(QStringLiteral("action_savefile"));
        action_quit = new QAction(MiniWord);
        action_quit->setObjectName(QStringLiteral("action_quit"));
        action_search = new QAction(MiniWord);
        action_search->setObjectName(QStringLiteral("action_search"));
        action_replace = new QAction(MiniWord);
        action_replace->setObjectName(QStringLiteral("action_replace"));
        action_save_as = new QAction(MiniWord);
        action_save_as->setObjectName(QStringLiteral("action_save_as"));
        action_addsize = new QAction(MiniWord);
        action_addsize->setObjectName(QStringLiteral("action_addsize"));
        action_cutsize = new QAction(MiniWord);
        action_cutsize->setObjectName(QStringLiteral("action_cutsize"));
        centralWidget = new QWidget(MiniWord);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MiniWord->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MiniWord);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MiniWord->setMenuBar(menuBar);
        statusBar = new QStatusBar(MiniWord);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MiniWord->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(action_newFile);
        menu->addAction(action_openfile);
        menu->addAction(action_save_as);
        menu->addAction(action_savefile);
        menu->addAction(action_quit);
        menu_2->addAction(action_search);
        menu_2->addAction(action_replace);
        menu_2->addAction(action_addsize);
        menu_2->addAction(action_cutsize);

        retranslateUi(MiniWord);

        QMetaObject::connectSlotsByName(MiniWord);
    } // setupUi

    void retranslateUi(QMainWindow *MiniWord)
    {
        MiniWord->setWindowTitle(QApplication::translate("MiniWord", "MiniWord", Q_NULLPTR));
        action_newFile->setText(QApplication::translate("MiniWord", "\346\226\260\345\273\272", Q_NULLPTR));
        action_newFile->setShortcut(QApplication::translate("MiniWord", "Ctrl+N", Q_NULLPTR));
        action_openfile->setText(QApplication::translate("MiniWord", "\346\211\223\345\274\200", Q_NULLPTR));
        action_openfile->setShortcut(QApplication::translate("MiniWord", "Ctrl+O", Q_NULLPTR));
        action_savefile->setText(QApplication::translate("MiniWord", "\344\277\235\345\255\230", Q_NULLPTR));
        action_savefile->setShortcut(QApplication::translate("MiniWord", "Ctrl+S", Q_NULLPTR));
        action_quit->setText(QApplication::translate("MiniWord", "\345\205\263\351\227\255", Q_NULLPTR));
        action_quit->setShortcut(QApplication::translate("MiniWord", "Ctrl+W", Q_NULLPTR));
        action_search->setText(QApplication::translate("MiniWord", "\346\237\245\346\211\276", Q_NULLPTR));
        action_search->setShortcut(QApplication::translate("MiniWord", "Ctrl+F", Q_NULLPTR));
        action_replace->setText(QApplication::translate("MiniWord", "\346\233\277\346\215\242", Q_NULLPTR));
        action_replace->setShortcut(QApplication::translate("MiniWord", "Ctrl+H", Q_NULLPTR));
        action_save_as->setText(QApplication::translate("MiniWord", "\345\217\246\345\255\230\344\270\272", Q_NULLPTR));
        action_addsize->setText(QApplication::translate("MiniWord", "\345\255\227\345\217\267\345\212\240\345\244\247", Q_NULLPTR));
        action_addsize->setShortcut(QApplication::translate("MiniWord", "Ctrl+K", Q_NULLPTR));
        action_cutsize->setText(QApplication::translate("MiniWord", "\345\255\227\345\217\267\345\207\217\345\260\217", Q_NULLPTR));
        action_cutsize->setShortcut(QApplication::translate("MiniWord", "Ctrl+L", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MiniWord", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MiniWord", "\347\274\226\350\276\221", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MiniWord: public Ui_MiniWord {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIWORD_H
