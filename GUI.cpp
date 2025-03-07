#include "GUI.h"
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

int GUI::count_teachers(string teacher)
{
    int count = 0;
    vector<Contract> contracte = this->service.get_All();

    for (const auto& contract : contracte)
    {

        if (contract.get_Teacher_name() == teacher)
        {

            count++;

        }


    }

    return count;
}

vector <string> GUI::get_list_of_teachers()
{

    vector<string> teachers;
    vector<Contract> contracte = this->service.get_All();

    for (const auto& contract : contracte)
    {
        const string prof = contract.get_Teacher_name();
        auto found = std::find(teachers.begin(),teachers.end(), contract.get_Teacher_name());
        if (found == teachers.end())
        {
            teachers.push_back(prof);

        }


    }

    return teachers;


}


void GUI::setupUI(QWidget* widget)
{


	widget->resize(500, 500);

	auto mainVBoxLayout = new QVBoxLayout(widget);

   


	this->postsList = new QListWidget;


    this->filterDurationButton = new QPushButton("Filter by duration");
    this->filterTeacherButton = new QPushButton("Filter by teacher");
    mainVBoxLayout->addWidget(this->filterDurationButton);
    mainVBoxLayout->addWidget(this->filterTeacherButton);
    mainVBoxLayout->addWidget(this->postsList);

	this->populateList(this->service.get_All());

    mainVBoxLayout->addWidget(this->postsList);
    mainVBoxLayout->addWidget(this->listWisg);

    auto VLayout = new QVBoxLayout();

    vector<Contract> list = this->service.get_All();

    vector <string> teachers = GUI::get_list_of_teachers();
  /*  for (const auto& teacher : teachers)
    {
        QString teacher_r = QString::fromStdString(teacher);
        this->aButton = new QPushButton(teacher_r);
        VLayout->addWidget(this->aButton);
        int count = GUI::count_teachers(teacher);



        QObject::connect(this->aButton, &QPushButton::clicked,
            [this, count]() {

                QString count_Q = QString::fromStdString(to_string(count));
                QMessageBox::information(this, "Something went wrong!", count_Q);
`

            });

    }
    */


    auto hLayout = new QHBoxLayout;
    auto formLayout = new QFormLayout;
    auto sort_layout = new QHBoxLayout;

    this->subjectEdit = new QLineEdit;
    this->durationEdit = new QLineEdit;
    this->typeEdit = new QLineEdit;
    this->teacherEdit = new QLineEdit;

    this->subjectEdit->setFixedHeight(36);
    this->durationEdit->setFixedHeight(36);

    this->typeEdit->setFixedWidth(256);
    this->teacherEdit->setFixedWidth(256);

    this->openCartButton = new QPushButton("Open cart");



    formLayout->addRow(QString("Subject"), this->subjectEdit);
    formLayout->addRow(QString("Duration"), this->durationEdit);
    formLayout->addRow(QString("Type"), this->typeEdit);
    formLayout->addRow(QString("Teacher name"), this->teacherEdit);

    hLayout->addLayout(formLayout);

    this->resetButton = new QPushButton("Reset");


    this->sortbySubjectButton = new QPushButton("Sort by subject");
    this->sortbySubjectButton->setFixedWidth(256);

    this->sortbyDurationButton = new QPushButton("Sort by duration");
    this->sortbyDurationButton->setFixedWidth(256);

    this->sortbyteacherandTypeButton = new QPushButton("Sort by teacher and type");
    this->sortbyteacherandTypeButton->setFixedWidth(256);

    mainVBoxLayout->addWidget(this->openCartButton);

    this->addButton = new QPushButton("Add");
    this->updateButton = new QPushButton("Update");
    this->deleteButton = new QPushButton("Delete");
    hLayout->addWidget(this->addButton);
    hLayout->addWidget(this->updateButton);
    hLayout->addWidget(this->deleteButton);
    hLayout->addWidget(this->resetButton);
    sort_layout->addWidget(this->sortbySubjectButton);
    sort_layout->addWidget(this->sortbyDurationButton);
    sort_layout->addWidget(this->sortbyteacherandTypeButton);

    mainVBoxLayout->addLayout(VLayout);
    mainVBoxLayout->addLayout(hLayout);
    mainVBoxLayout->addLayout(sort_layout);
    this->connect();

}

void GUI::populateList(vector <Contract> contracts)
{

    this->model1 = new MyListModel(this->service.get_All());
    this->listWisg->setModel(model1);

    this->elements = contracts;
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

void GUI::connect()
{

    QObject::connect(this->postsList, &QListWidget::itemSelectionChanged,
        [this]() {
            int index = this->selectedIndex();
            auto element = this->elements.at(index);
            this->subjectEdit->setText(QString::fromStdString(element.get_Subject()));
            this->durationEdit->setText(QString::fromStdString(std::to_string(element.get_Duration())));
            this->typeEdit->setText(QString::fromStdString(element.get_Type()));
            this->teacherEdit->setText(QString::fromStdString(element.get_Teacher_name()));

        });


    QObject::connect(this->addButton, &QPushButton::clicked,
        [this]() {
            auto subject = this->subjectEdit->text().toStdString();
            auto duration = 0;
            duration = this->durationEdit->text().toInt();
            auto type = this->typeEdit->text().toStdString();
            auto teacher_name = this->teacherEdit->text().toStdString();


            if (subject.empty() || type.empty() || teacher_name.empty())
            {
                QMessageBox::information(this, "Something went wrong!", "Date invalide!!!");
                return;
            }

            try {
                this->service.addContractService(subject, duration, type, teacher_name);
            }
            catch (RepoContractException)
            {
                
                QMessageBox::information(this, "Something went wrong!","Produs existent!");
                return;
            }
            catch (ValidateException)
            {
                QMessageBox::information(this, "Something went wrong!","Date invalide!");
            }
            this->populateList(service.get_All());


        });


    QObject::connect(this->updateButton, &QPushButton::clicked,
        [this]() {
            auto subject = this->subjectEdit->text().toStdString();
            auto duration = 0;
            duration = this->durationEdit->text().toInt();
            auto type = this->typeEdit->text().toStdString();
            auto teacher_name = this->teacherEdit->text().toStdString();



            if (subject.empty() || type.empty() || teacher_name.empty())
            {
                QMessageBox::information(this, "Something went wrong!", "Date invalide!!!");
                return;
            }

            try {
                this->service.modifyContractService(subject, duration, type, teacher_name);
            }
            catch (RepoContractException)
            {

                QMessageBox::information(this, "Something went wrong!", "Produs inexistent!");
                return;
            }
            catch (ValidateException)
            {
                QMessageBox::information(this, "Something went wrong!", "Date invalide!");
            }
            this->populateList(service.get_All());



        });

    QObject::connect(this->deleteButton, &QPushButton::clicked,
        [this]() {

            int index = this->selectedIndex();

            try {

                this->service.deleteContractService(index);
            }
            catch (RepoContractException)
            {

                QMessageBox::information(this, "Something went wrong!", "Produs inexistent!");
                return;
            }
            catch (ValidateException)
            {
                QMessageBox::information(this, "Something went wrong!", "Date invalide!");
            }
            this->populateList(service.get_All());


        });

    QObject::connect(this->filterDurationButton, &QPushButton::clicked,
        [this]()
        {
            QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
            tr("Duration:"), QLineEdit::Normal);

        if (text=="")
        {
        QMessageBox::information(this, "Something went wrong!", "Date invalide!!!");
        return;
        }
            
            
            try{
                vector <Contract> filtrered_elements = this->service.filter_by_duration(text.toInt());

                if (filtrered_elements.size() == 0)
                {
                    QMessageBox::information(this, "Something went wrong!", "Nu exista obiecte de filrtat!");
                    return;
                }
                this->populateList(filtrered_elements);

            }
            catch (RepoContractException)
            {
                QMessageBox::information(this, "Something went wrong!", "Produs inexistent!");
                this->populateList(service.get_All());
                return;
            }


        });


    QObject::connect(this->filterTeacherButton, &QPushButton::clicked,
        [this]()
        {
            QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
            tr("Teacher name:"), QLineEdit::Normal);

    if (text == "")
    {
        QMessageBox::information(this, "Something went wrong!", "Date invalide!!!");
        return;
    }


    try {
        vector <Contract> filtrered_elements = this->service.filter_by_teacher_name(text.toStdString());

        if (filtrered_elements.size() == 0)
        {
            QMessageBox::information(this, "Something went wrong!", "Nu exista obiecte de filrtat!");
            return;
        }
        this->populateList(filtrered_elements);

    }
    catch (RepoContractException)
    {
        QMessageBox::information(this, "Something went wrong!", "Produs inexistent!");
        this->populateList(service.get_All());
        return;
    }


        });


    QObject::connect(this->resetButton, &QPushButton::clicked,
        [this]() {


            this->populateList(service.get_All());


        });



    QObject::connect(this->sortbySubjectButton, &QPushButton::clicked,
        [this]() {

            this->populateList(service.sort_by_subject());
        

        });
    
    QObject::connect(this->sortbyDurationButton, &QPushButton::clicked,
        [this]() {

            this->populateList(service.sort_by_duration());


        });


    QObject::connect(this->sortbyteacherandTypeButton, &QPushButton::clicked,
        [this]()
        {

            this->populateList(service.sort_by_teacher_and_type());


        });

    QObject::connect(this->openCartButton, &QPushButton::clicked,
        [this]() {

            painter = new PainterGUI(this->service);
            shop_p = new ShoppingGUI(this->service);
            shop_p->show();
            painter->show();
                
        });

}

int GUI::selectedIndex()
{
    auto index = this->postsList->selectionModel()->currentIndex();
    return index.row();
}