#include "MainWindow.h"
#include "AddProduct.h"
#include "ViewStock.h"

MainWindow::MainWindow (QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Bendahma Supermarket");
    setWindowIcon(QIcon("pictures/app_icon.png"));
    showMaximized();

    m_mainWidget = new QWidget(this);
    setCentralWidget(m_mainWidget);

    m_generalContainer = new QHBoxLayout();
    m_container        = new QVBoxLayout();
    m_rightContainer   = new QVBoxLayout();

    createAppearance();
    db = openDataBase();
    DataBaseFile();

    QObject::connect(m_newProductAction, SIGNAL(triggered()), this, SLOT(addProductWindow()));
    QObject::connect(m_displayProducts, SIGNAL(triggered()), this, SLOT(viewStockWindow()));
    QObject::connect(m_undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    QObject::connect(m_resetAction, SIGNAL(triggered()), this, SLOT(reset()));
    QObject::connect(m_exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createAppearance ()
{
    m_newProductAction    = new QAction(tr("Nouveau produit", "Ajouter un produit."), this);
    m_newProductAction->setIcon(QIcon("pictures/add.png"));
    m_displayProducts     = new QAction(tr("Liste des produits", "Affiche la liste des produits."), this);
    m_displayProducts->setIcon(QIcon("pictures/products.png"));
    m_undoAction          = new QAction(tr("Annuler", "Annule l'ajout du produit au client."), this);
    m_undoAction->setIcon(QIcon("pictures/undo.png"));
    m_resetAction         = new QAction(tr("Nouveau client", "Produits achetés par un nouveau client."), this);
    m_resetAction->setIcon(QIcon("pictures/reset.png"));
    m_exitAction          = new QAction(tr("Fermer", "Fermer l'application."), this);

    m_file = menuBar()->addMenu(tr("&Fichier", "Gérez vos produits/quittez l'application."));
    m_file->addAction(m_newProductAction);
    m_file->addAction(m_displayProducts);
    m_file->addAction(m_undoAction);
    m_file->addAction(m_resetAction);
    m_file->addAction(m_exitAction);

    QString style;
    style +=  "QMenuBar {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,";
    style +=  "stop:0 lightgray, stop:1 darkgray);}";
    style +=  "QMenuBar::item {";
    style +=  "spacing: 20px; /* spacing between menu bar items */";
    style +=  "padding: 1px 5px;";
    style +=  "background: transparent;";
    style +=  "border-radius: 2px;";
    style +=  "}";
    style +=  "QMenuBar::item:selected { /* when selected using mouse or keyboard */";
    style +=  "background: #A8A8A8;";
    style +=  "}";
    style +=  "QMenuBar::item:pressed {";
    style +=  "background: #888888;";
    style +=  "}";

    menuBar()->setStyleSheet(style);

    m_toolBar = addToolBar(tr("Barre d'outils", "Afficher/Ne pas afficher la barre d'outils"));
    m_toolBar->setMovable(false);
    m_toolBar->addAction(m_newProductAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_displayProducts);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_undoAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_resetAction);
    m_toolBar->setStyleSheet("QToolBar{background: #8E8E8E; border: 5E5E5E;}");

    m_barCode = new QLineEdit(m_mainWidget);
    m_barCode->setFixedHeight(25);
    m_barCode->setFocus(Qt::OtherFocusReason);
    connect(m_barCode, SIGNAL(textChanged(QString)), this, SLOT(display(QString)));

    m_response        = new QLabel("", m_mainWidget);
    m_response->setStyleSheet("QLabel{color: white;}");
    m_actualPrice     = new QLabel("Prix du produit : ", m_mainWidget);
    m_actualPrice->setStyleSheet("QLabel{color: white;}");
    m_totalPriceLabel =  new QLabel("Prix total pour le client : ", m_mainWidget);
    m_totalPriceLabel->setStyleSheet("QLabel{color: white;}");

    m_actualPriceLCD = new QLCDNumber(m_mainWidget);
    m_actualPriceLCD->setSegmentStyle(QLCDNumber::Flat);
    m_actualPriceLCD->setDigitCount(15);
    m_actualPriceLCD->display(0);
    m_actualPriceLCD->setStyleSheet("QFrame{border: none; color: red;}");

    m_customerPrice = 0;
    m_totalPrice = new QLCDNumber(m_mainWidget);
    m_totalPrice->setSegmentStyle(QLCDNumber::Flat);
    m_totalPrice->setDigitCount(15);
    m_totalPrice->display(m_customerPrice);
    m_totalPrice->setStyleSheet("QFrame{border: none; color: red;}");

    m_container->addWidget(m_barCode);
    m_container->addWidget(m_response);
    m_container->addWidget(m_actualPrice);
    m_container->addWidget(m_actualPriceLCD);
    m_container->addWidget(m_totalPriceLabel);
    m_container->addWidget(m_totalPrice);
    m_container->addStretch(1);

    //m_rightContainer->addWidget(m_barCode);

    m_generalContainer->addLayout(m_container);
    m_generalContainer->addLayout(m_rightContainer);

    m_mainWidget->setLayout(m_generalContainer);
}

void MainWindow::DataBaseFile ()
{
    QFile dbFile(QCoreApplication::applicationDirPath() + "/db.sqlite");

    if (! dbFile.exists())
    {
        if (dbFile.open(QIODevice::WriteOnly)) {
            db.open();
            QSqlQuery query;
            query.exec("create table products "
                    "(id integer primary key, "
                    "product_name text, "
                    "product_bar_code text, "
                    "product_price integer)"
            );
        }
    }
}

QSqlDatabase MainWindow::openDataBase ()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/db.sqlite");

    return db;
}

void MainWindow::addProductWindow()
{
    AddProduct *addProduct = new AddProduct(db);
    addProduct->exec();
}

void MainWindow::viewStockWindow()
{
    ViewStock *viewStock = new ViewStock(db);
    viewStock->exec();
}

void MainWindow::undo()
{
    if (m_totalPrice->value() > 0)
    {
        m_allPrices.take("price");

        int sum = 0;
        for (int i = 0; i < m_allPrices.size(); ++i)
        {
            sum += m_allPrices.values("price").at(i);
        }

        m_customerPrice = sum;
        m_totalPrice->display(m_customerPrice);
        m_actualPriceLCD->display(m_allPrices.value("price"));
        m_barCode->setText("");
        m_response->setText("");
    }
}

void MainWindow::reset()
{
    m_customerPrice = 0;
    m_lastPrice = 0;
    m_totalPrice->display(0);
    m_actualPriceLCD->display(0);
    m_barCode->setText("");
    m_response->setText("");
}

void MainWindow::display(QString code)
{
    db.open();

    QMap<QString, QString> check = product.getProduct(code);

    if (check.contains("code") && check["code"] == code)
    {
        m_lastPrice = check["price"].toInt();
        m_barCode->setText("");
        m_actualPriceLCD->display(check["price"].toInt());
        m_response->setText("Le produit a bien été retrouvé.\n\nNom : " + check["name"]
            + "\n\nCode : " + check["code"] + "\n\n");
        m_customerPrice += m_lastPrice;
        m_totalPrice->display(m_customerPrice);

        m_allPrices.insertMulti("price", m_lastPrice);
    }
    else
    {
        m_actualPriceLCD->display(0);
        m_response->setText("Impossible de retrouver le produit avec ce code barre.");
    }
}
