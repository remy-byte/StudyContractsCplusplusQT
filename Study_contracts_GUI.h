#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Study_contracts_GUI.h"

class Study_contracts_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Study_contracts_GUI(QWidget *parent = nullptr);
    ~Study_contracts_GUI();

private:
    Ui::Study_contracts_GUIClass ui;
};
