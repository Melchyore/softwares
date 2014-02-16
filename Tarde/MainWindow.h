#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtGui>
#include <QLCDNumber>
#include "Product.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow (QWidget *parent = 0);
        void createAppearance ();
        void DataBaseFile ();
        QSqlDatabase openDataBase ();

    signals:

    protected slots:
        void addProductWindow();
        void viewStockWindow();
        void undo();
        void reset();
        void display(QString code);

    protected:
        QSqlDatabase db;
        QWidget *m_mainWidget;
        QMenu *m_file;
        QToolBar *m_toolBar;
        QAction *m_newProductAction, *m_displayProducts, *m_undoAction, *m_resetAction, *m_exitAction;
        QHBoxLayout *m_generalContainer;
        QVBoxLayout *m_container, *m_rightContainer;
        QLineEdit *m_barCode;
        QHash<QString, int> m_allPrices;
        QLabel *m_actualPrice, *m_totalPriceLabel, *m_response;
        QLCDNumber *m_actualPriceLCD, *m_totalPrice;
        double m_customerPrice, m_lastPrice;
        Product product;
};

#endif // MAINWINDOW_H
