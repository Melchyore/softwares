#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QMap>

class Product
{
    public:
        Product();
        bool addProduct (QString name, QString code, quint32 price);
        QMap<QString, QString> getProduct (QString code);
        bool updateProduct (int id, QString updates);
        bool deleteProduct (int id);
        int getProductsNumber();
        QHash<QString, QString> getAllProducts();

    protected:
        QString m_name, m_code;
        quint32 m_price, m_id;
};

#endif // PRODUCT_H
