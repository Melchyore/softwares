#include "ViewStock.h"
#include "ModifyProduct.h"

ViewStock::ViewStock(QSqlDatabase db)
{
    m_dataBase = db;
    setFixedSize(800, 500);
    m_dataBase.open();
    setWindowTitle("Aperçu du stock");
    setWindowIcon(QIcon("pictures/app_icon.png"));
    setWindowFlags(Qt::MacWindowToolBarButtonHint);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    m_modify = new QPushButton("Modifier");
    m_modify->setDisabled(true);
    m_delete = new QPushButton("Supprimer");
    m_delete->setDisabled(true);

    m_buttonsLayout  = new QHBoxLayout;
    m_buttonsLayout->addWidget(m_modify);
    m_buttonsLayout->addWidget(m_delete);
    m_buttonsLayout->setAlignment(Qt::AlignLeft);

    m_stockTable = new QTableView;
    m_stockTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_stockTable->setCornerButtonEnabled(false);
    m_stockTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_stockTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_model      = new QStandardItemModel(product.getProductsNumber(), 4, this);

    addData();

    m_stockTable->setModel(m_model);
    m_mainLayout->addLayout(m_buttonsLayout);
    m_mainLayout->addWidget(m_stockTable);

    this->setLayout(m_mainLayout);

    connect(m_stockTable, SIGNAL(clicked(QModelIndex)), this, SLOT(getRowData(QModelIndex)));
    connect(m_modify, SIGNAL(clicked()), this, SLOT(modifyProductWindow()));
    connect(m_delete, SIGNAL(clicked()), this, SLOT(deleteProduct()));
}

void ViewStock::getRowData(QModelIndex row)
{
    m_modify->setDisabled(false);
    m_delete->setDisabled(false);

    m_dataId    = row.sibling(m_stockTable->currentIndex().row(), 0).data().toInt();
    m_dataName  = row.sibling(m_stockTable->currentIndex().row(), 1).data().toString();
    m_dataCode  = row.sibling(m_stockTable->currentIndex().row(), 2).data().toString();
    m_dataPrice = row.sibling(m_stockTable->currentIndex().row(), 3).data().toString();
}

void ViewStock::addData()
{
    m_model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    m_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Code barre"));
    m_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));

    for (int i = 0; i < product.getProductsNumber(); ++i)
    {
        m_id    = new QStandardItem(product.getAllProducts().values("id").at(i));
        m_name  = new QStandardItem(product.getAllProducts().values("name").at(i));
        m_code  = new QStandardItem(product.getAllProducts().values("code").at(i));
        m_price = new QStandardItem(product.getAllProducts().values("price").at(i));

        m_model->setItem(i, 0, m_id);
        m_model->setItem(i, 1, m_name);
        m_model->setItem(i, 2, m_code);
        m_model->setItem(i, 3, m_price);
    }
}

void ViewStock::deleteProduct()
{
    bool remove = product.deleteProduct(m_dataId);

    if (remove)
    {
        QMessageBox::information(this, "Information", "Le produit a bien été supprimé.");
        m_model->removeRows(0, m_model->rowCount());
        addData();
    }
    else
    {
        QMessageBox::warning(this, "Erreur", "Le produit n'a pas pu être supprimé.");
    }
}

void ViewStock::modifyProductWindow()
{
    ModifyProduct *modify = new ModifyProduct(m_dataId, m_dataName, m_dataCode, m_dataPrice, &m_model, this);
    modify->exec();
}
