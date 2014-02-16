#ifndef VIEWSTOCK_H
#define VIEWSTOCK_H

#include <QWidget>
#include <QtGui>
#include <Product.h>

class ViewStock : public QDialog
{
    Q_OBJECT
        public:
            ViewStock(QSqlDatabase db);
            void addData();

        signals:

        protected slots:
            void getRowData(QModelIndex row);
            void deleteProduct();
            void modifyProductWindow();

        protected:
            QSqlDatabase m_dataBase;
            QVBoxLayout *m_mainLayout;
            QHBoxLayout *m_buttonsLayout;
            QPushButton *m_modify, *m_delete;
            QTableView *m_stockTable;
            QStandardItemModel *m_model;
            QStandardItem *m_id, *m_name, *m_code, *m_price;
            QString m_dataName, m_dataCode, m_dataPrice;
            int m_dataId;
            Product product;
};

#endif // VIEWSTOCK_H
