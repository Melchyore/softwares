#include "Product.h"

Product::Product() {}

bool Product::addProduct (QString name, QString code, quint32 price)
{
    m_name = name;
    m_code = code;
    m_price = price;

    QSqlQuery datas;
    datas.prepare("INSERT INTO products VALUES(NULL, :name, :code, :price)");
    datas.bindValue(":name", m_name);
    datas.bindValue(":code", m_code);
    datas.bindValue(":price", m_price);

    if (datas.exec())
    {
        return true;
    }
    else
    {
        return false;
    }
}

QMap<QString, QString> Product::getProduct (QString code)
{
    m_code = code;

    QSqlQuery datas;
    datas.prepare("SELECT * FROM products WHERE product_bar_code = :code");
    datas.bindValue(":code", m_code);
    datas.exec();

    if (datas.next())
    {
        QMap<QString, QString> productInfos;
        productInfos.insert("id", datas.value(0).toString());
        productInfos.insert("name", datas.value(1).toString());
        productInfos.insert("code", datas.value(2).toString());
        productInfos.insert("price", datas.value(3).toString());

        return productInfos;
    }
    else
    {
        QMap<QString, QString> errors;
        errors.insert("error", "The product does not exist.");

        return errors;
    }
}

bool Product::updateProduct (int id, QString updates)
{
    m_id = id;

    QSqlQuery check, update;
    check.prepare("SELECT count(*) FROM products WHERE id = :id");
    check.bindValue(":id", m_id);
    check.exec();

    if (check.next())
    {
        if (check.value(0).toInt() == 1)
        {
            update.prepare("UPDATE products SET " + updates + " WHERE id = :id");
            update.bindValue(":id", m_id);
            update.exec();

            qDebug() << m_id << updates;

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Product::deleteProduct (int id)
{
    m_id = id;

    QSqlQuery check, remove;
    check.prepare("SELECT count(*) FROM products WHERE id = :id");
    check.bindValue(":id", m_id);
    check.exec();

    if (check.next())
    {
        if (check.value(0).toInt() == 1)
        {
            remove.prepare("DELETE FROM products WHERE id = :id");
            remove.bindValue(":id", m_id);
            remove.exec();

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int Product::getProductsNumber()
{
    QSqlQuery products;
    products.prepare("SELECT count(*) FROM products");
    products.exec();

    if (products.next())
    {
        return products.value(0).toInt();
    }
}

QHash<QString, QString> Product::getAllProducts()
{
    QSqlQuery datas;
    datas.prepare("SELECT * FROM products ORDER BY id ASC");
    datas.exec();

    QHash<QString, QString> productsInfos;

    while (datas.next())
    {
        productsInfos.insertMulti("id", datas.value(0).toString());
        productsInfos.insertMulti("name", datas.value(1).toString());
        productsInfos.insertMulti("code", datas.value(2).toString());
        productsInfos.insertMulti("price", datas.value(3).toString());
    }

    return productsInfos;
}
