#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QtGui>
#include <Product.h>

class AddProduct : public QDialog
{
    Q_OBJECT

        public:
            AddProduct(QSqlDatabase db);

        protected slots:
            void createProduct();

        protected:
            QVBoxLayout *m_mainLayout;
            QFormLayout *m_addProductForm;
            QHBoxLayout *m_buttonsLayout;
            QLineEdit *m_productName, *m_productBarCode, *m_productPrice;
            QPushButton *m_validate, *m_abort;
            Product product;
};

#endif // ADDPRODUCT_H
