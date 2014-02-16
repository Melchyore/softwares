#include "AddProduct.h"

AddProduct::AddProduct(QSqlDatabase db)
{
    db.open();
    setFixedSize(400, 200);
    setWindowTitle("Ajouter un produit");
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

    m_productName    = new QLineEdit;
    m_productName->setFixedHeight(25);
    m_productBarCode = new QLineEdit;
    m_productBarCode->setFixedHeight(25);
    m_productPrice   = new QLineEdit;
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

    connect(m_validate, SIGNAL(clicked()), this, SLOT(createProduct()));
    connect(m_abort, SIGNAL(clicked()), this, SLOT(accept()));
}

void AddProduct::createProduct()
{
    QMap<QString, QString> check = product.getProduct(m_productBarCode->text());

    if (check.contains("code") && check["code"] == m_productBarCode->text())
    {
        QMessageBox::warning(this, "Erreur", "Le produit existe déjà.");
    }
    else
    {
        bool add = product.addProduct(m_productName->text(), m_productBarCode->text(),
            m_productPrice->text().toInt());

        if (add)
        {
            QMessageBox::information(this, "Information", "Le produit a bien été ajouté au stock !");
            m_productName->setText("");
            m_productBarCode->setText("");
            m_productPrice->setText("");
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Le produit n'a pas pu être ajouté.");
        }
    }
}
