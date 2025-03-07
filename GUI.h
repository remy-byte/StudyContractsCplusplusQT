#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qboxlayout.h>
#include <QPushButton>
#include <QLineEdit>
#include <QtWidgets/qformlayout.h>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <qwindow.h>
#include "contract_service.h"
#include <qtextedit.h>
#include "ContractShopGUI.h"
#include "MyListWidget.h"
#include "qcombobox.h"

class GUI : public QWidget{
  

private:
    Q_OBJECT

	ContractList& service;
	QListWidget* postsList;
    ShoppingGUI& shop;
	vector <Contract> elements;
    ShoppingGUI* shop_p;
    PainterGUI* painter;

    MyListModel* model1;
    QListView* listWisg = new QListView;

    QComboBox* comboBox;


    QLineEdit* subjectEdit;
    QLineEdit* durationEdit;
    QLineEdit* typeEdit;
    QLineEdit* teacherEdit;

    QPushButton* addButton;
    QPushButton* resetButton;
    QPushButton* sortbySubjectButton;
    QPushButton* sortbyDurationButton;
    QPushButton* sortbyteacherandTypeButton;
    QPushButton* updateButton;
    QPushButton* deleteButton;
    QLineEdit* filterEdit;
    QPushButton* openCartButton;


    QPushButton* filterDurationButton;
    QPushButton* filterTeacherButton;    

    QPushButton* aButton;


    void populateList(vector<Contract> elements);

    void connect();

    int selectedIndex();

    void setupUI(QWidget* widget);


    void addAuthors();

    vector <string> get_list_of_teachers();

    int count_teachers(string teacher);


public:
    GUI(ContractList& service, ShoppingGUI& shop) : service{ service }, shop{ shop } {
        this->setupUI(this);

    }


};

