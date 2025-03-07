#pragma once
#include <QAbstractListModel>
#include <vector>
#include "contract_service.h"
#include <sstream>



class MyListModel : public QAbstractListModel {
    std::vector<Contract> contracts;
public:
    MyListModel(const std::vector<Contract> contracts) : contracts(contracts) {};
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        parent.row();
        return int(contracts.size());
    };
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole)
        {
            index.row();
        /*    std::stringstream stream;
            stream << contracts[index.row()].to_string();

            string string_stream = stream.str();
            */

           // return QString::fromStdString(contracts[index.row()].to_string());
        }
      /*  if (role == Qt::UserRole)
        {
            string user_data = contracts[index.row()].to_string();
            return QString::fromStdString(user_data);
        }
        */

        return QVariant{};
    };

};
