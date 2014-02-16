#include "ModifyProduct.h"

ModifyProduct::ModifyProduct(int id, QString name, QString code, QString price, QStandardItemModel** model, ViewStock* const stock)
{
    setFixedSize(400, 200);
    setWindowTitle("Modifier un produit");
    setWindowIcon(QIcon("pictures/app_icon.png"));
    setWindowFlags(Qt::WindowCloseButtonHint);

    QPalette* palette = new QPalette();
    palette->setColor(QPalette::WindowText, Qt::white);
    QLinearGradient linearGradient(0, 0, 0, this->height());
    linearGradient.setColorAt(0, "#090808");
    linearGradient.setColorAt(1, "#242424");
    palette->setBrush(QPalette::Window, *(new QBrush(linearGradient)));

    this->setPalette(*palette);

    m_mainLayout     = new QVBoxLayout;
    m_addProductForm = new QFormLayout;
    m_buttonsLayout  = new QHBoxLayout;

    m_stock = stock;
    m_model = *model;
    m_id    = id;
    m_name  = name;
    m_code  = code;
    m_price = price;

    m_productName    = new QLineEdit;
    m_productName->setText(m_name);
    m_productName->setFixedHeight(25);
    m_productBarCode = new QLineEdit;
    m_productBarCode->setText(m_code);
    m_productBarCode->setFixedHeight(25);
    m_productPrice   = new QLineEdit;
    m_productPrice->setText(m_price);
    m_productPrice->setFixedHeight(25);
    m_validate       = new QPushButton("Valider");
    m_abort          = new QPushButton("Annuler");

    m_addProductForm->addRow("&Nom du produit : ", m_productName);
    m_addProductForm->addRow("&Code barre : ", m_productBarCode);
    m_addProductForm->addRow("&Prix : ", m_productPrice);

    m_buttonsLayout->addWidget(m_validate);
    m_buttonsLayout->addWidget(m_abort);
    m_buttonsLayout->setAlignment(Qt::AlignCenter);

    m_mainLayout->addLayout(m_addProductForm);
    m_mainLayout->addLayout(m_buttonsLayout);
    this->setLayout(m_mainLayout);

    connect(m_validate, SIGNAL(clicked()), this, SLOT(modify()));
    connect(m_abort, SIGNAL(clicked()), this, SLOT(accept()));
}

void ModifyProduct::modify()
{
    bool update = product.updateProduct(m_id, "product_name = \"" + m_productName->text()
        + "\", product_bar_code = \"" + m_productBarCode->text() + "\", product_price = "
        + m_productPrice->text());

    if (update)
    {
        QMessageBox::information(this, "Information", "Le produit a bien été modifié.");
        m_model->removeRows(0, m_model->rowCount());
        m_stock->addData();
    }
    else
    {
        QMessageBox::warning(this, "Erreur", "Le produit n'a pas pu être modifié.");
    }
}
