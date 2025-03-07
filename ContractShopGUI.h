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
#include <qpainter.h>
#include <qpainterpath.h>


class ShoppingGUI : public QWidget, public Observer{

public:

	ShoppingGUI(ContractList& service) : service{ service } {
		this->setup_UI(this);
        this->populateList(this->service.getShoppingCart());
	}

    void update() override {
        vector <Contract> elemente = this->service.getShoppingCart();
        this->populateList(elemente);
    }

private:
	ContractList& service;
	void populateList(vector<Contract> elements);
	QListWidget* postsList;
	void setup_UI(QWidget* widget);

	QPushButton* addButton;
	QPushButton* resetButton;
	void connect();
    QLineEdit* numberofgenerations;
	QPushButton* addtoShopButton;
	QLineEdit* addLine;

	QPushButton* exportToFile;
	QLineEdit* file;
};

class PainterGUI :public QWidget, public Observer {
private:
    ContractList& serv;
public:
    PainterGUI(ContractList& serv) :serv{ serv } {
        this->serv.addObserver(this);
    }
    void update() override {
        repaint();
    }

    void paintEvent(QPaintEvent*) override {
        QPainter p{ this };
       
        int x = 10;
        for (const auto& prod : this->serv.getShoppingCart()) {
            QImage im = QImage("C:\\Users\\Remus\\Desktop\\cat.png");

            p.drawImage(x, 0, im.scaled(100, 600));
           // p.drawRect(x,0,30,50);
            x += 40;
            prod.get_Subject();
        }
    }

    ~PainterGUI() = default;
};