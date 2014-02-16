#ifndef MODIFYPRODUCT_H
#define MODIFYPRODUCT_H

#include <QWidget>
#include <QtGui>
#include <Product.h>
#include "ViewStock.h"

class ModifyProduct : public QDialog
{
    Q_OBJECT
        public:
            ModifyProduct(int id, QString name, QString code, QString price, QStandardItemModel** model, ViewStock* const stock);

        protected slots:
            void modify();

        protected:
            QStandardItemModel *m_model;
            ViewStock *m_stock;
            QVBoxLayout *m_mainLayout;
            QFormLayout *m_addProductForm;
            QHBoxLayout *m_buttonsLayout;
            QLineEdit *m_productName, *m_productBarCode, *m_productPrice;
            QPushButton *m_validate, *m_abort;
            QString m_name, m_code, m_price;
            int m_id;
            Product product;
};

#endif // MODIFYPRODUCT_H
