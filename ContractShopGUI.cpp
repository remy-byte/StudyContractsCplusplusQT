#include "ContractShopGUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <algorithm>
#include <iostream>
#include <QMessageBox>
#include <QGroupBox>
#include <qinputdialog.h>
#include <qdir.h>
#include <QString>

void ShoppingGUI::setup_UI(QWidget* widget)
{


	widget->resize(1000, 500);

	auto mainVBoxLayout = new QVBoxLayout(widget);
	this->postsList = new QListWidget;

    auto HBoxLayout = new QHBoxLayout;
    HBoxLayout->addWidget(this->postsList);

    this->addButton = new QPushButton("Generate random contracts");
    auto formLayout = new QFormLayout;

    HBoxLayout->addLayout(formLayout);

    this->resetButton = new QPushButton("Reset");
    formLayout->addWidget(this->resetButton);

    this->numberofgenerations = new QLineEdit;
    formLayout->addRow(QString("Number of generations"), this->numberofgenerations);
    formLayout->addWidget(this->addButton);

    this->addtoShopButton = new QPushButton("Add");
    this->addLine = new QLineEdit;
    formLayout->addRow(QString("Add a subject: "), this->addLine);
    formLayout->addWidget(this->addtoShopButton);

    this->file = new QLineEdit;
    this->exportToFile = new QPushButton("Export");
    formLayout->addRow(QString("Export to file: "), this->file);
    formLayout->addWidget(this->exportToFile);


    mainVBoxLayout->addLayout(HBoxLayout);
    this->connect();


}


void ShoppingGUI::populateList(vector <Contract> contracts)
{

    vector <Contract> elements = contracts;
    this->postsList->clear();

    QStringList result;

    std::transform(elements.begin(), elements.end(), std::back_inserter(result)
        , [](const Contract& contract)
        {
            return QString::fromStdString(
                contract.get_Subject() + '-' + std::to_string(contract.get_Duration()) + '-' + contract.get_Type() + '-' + contract.get_Teacher_name());
        });

    this->postsList->addItems(result);
}

void ShoppingGUI::connect()
{
    this->service.addObserver(this);
    QObject::connect(this->addButton, &QPushButton::clicked,
        [this]()
        {
            int number_of_generations = this->numberofgenerations->text().toInt();
            service.random_fill(number_of_generations, service.get_All());
            this->populateList(service.getShoppingCart());
        });

    QObject::connect(this->addtoShopButton, &QPushButton::clicked,
        [this]()
        {

            string subject = this->addLine->text().toStdString();
            try {
                service.AddToCartService(subject);
                this->populateList(service.getShoppingCart());
            }
            catch(RepoContractException){
                QMessageBox::information(this, "Something went wrong!", "Nu exista!!!");
                return;
            }


        });

    QObject::connect(this->resetButton, &QPushButton::clicked,
        [this]()
        {

            service.clearCart();
            this->populateList(service.getShoppingCart());

        });


}

