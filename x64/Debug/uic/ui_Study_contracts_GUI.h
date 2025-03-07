/********************************************************************************
** Form generated from reading UI file 'Study_contracts_GUI.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDY_CONTRACTS_GUI_H
#define UI_STUDY_CONTRACTS_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Study_contracts_GUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Study_contracts_GUIClass)
    {
        if (Study_contracts_GUIClass->objectName().isEmpty())
            Study_contracts_GUIClass->setObjectName("Study_contracts_GUIClass");
        Study_contracts_GUIClass->resize(600, 400);
        menuBar = new QMenuBar(Study_contracts_GUIClass);
        menuBar->setObjectName("menuBar");
        Study_contracts_GUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Study_contracts_GUIClass);
        mainToolBar->setObjectName("mainToolBar");
        Study_contracts_GUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Study_contracts_GUIClass);
        centralWidget->setObjectName("centralWidget");
        Study_contracts_GUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Study_contracts_GUIClass);
        statusBar->setObjectName("statusBar");
        Study_contracts_GUIClass->setStatusBar(statusBar);

        retranslateUi(Study_contracts_GUIClass);

        QMetaObject::connectSlotsByName(Study_contracts_GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *Study_contracts_GUIClass)
    {
        Study_contracts_GUIClass->setWindowTitle(QCoreApplication::translate("Study_contracts_GUIClass", "Study_contracts_GUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Study_contracts_GUIClass: public Ui_Study_contracts_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDY_CONTRACTS_GUI_H
