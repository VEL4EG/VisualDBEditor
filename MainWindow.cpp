#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QFile>

#include "DBHandler.h"
#include "TableView.h"
#include "Controller.h"

MainWindow::MainWindow(DBHandler *h, Controller *c):
    ui(new Ui::MainWindow),
    dbHandler(h),
    controller(c),
    tableViews(nullptr),
    tablesScene(new QWidget),
    scrollArea(new QScrollArea)
{
    ui->setupUi(this);

    setWindowTitle(QString("VisualDBEditor"));

    createActions();
    createMenu();

    scrollArea->setWidget(tablesScene);
    setCentralWidget(scrollArea);
}

MainWindow::~MainWindow()
{
    freeResources();

    delete ui;
}

void MainWindow::slot_fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(
                                this,
                                QString::fromUtf8("Open file..."),
                                QDir::currentPath(),
                                "XML file(*.xml)");
}

void MainWindow::slot_fileSaveAs()
{
    QString filePath = QFileDialog::getSaveFileName(
                                    this, "Save Xml", ".", "Xml files (*.xml)");
}


void MainWindow::slot_fileSave()
{
    controller->saveTables();
}

void MainWindow::createActions()
{

    fileOpen = new QAction(tr("&Open"), this);
    connect(fileOpen, SIGNAL(triggered()), this, SLOT(slot_fileOpen()));

    fileSave = new QAction(tr("&Save"), this);
    connect(fileSave, SIGNAL(triggered()), this, SLOT(slot_fileSave()));

    fileSaveAs = new QAction(tr("&Save As..."), this);
    connect(fileSaveAs, SIGNAL(triggered()), this, SLOT(slot_fileSaveAs()));

    fileExit = new QAction(tr("&Exit"), this);
    connect(fileExit, SIGNAL(triggered()), this, SLOT(close()));

    showClassesAct = new QAction(tr("&Classes"), this);
    showClassesAct->setCheckable(true);
    connect(showClassesAct, SIGNAL(triggered()), this, SLOT(showClasses()));

    showFieldsAct = new QAction(tr("&Fields"), this);
    showFieldsAct->setCheckable(true);
    connect(showFieldsAct, SIGNAL(triggered()), this, SLOT(showFields()));

    showObjectsAct = new QAction(tr("&Objects"), this);
    showObjectsAct->setCheckable(true);
    connect(showObjectsAct, SIGNAL(triggered()), this, SLOT(showObjects()));

    displayModeGroup = new QActionGroup(this);
    displayModeGroup->addAction(showClassesAct);
    displayModeGroup->addAction(showFieldsAct);
    displayModeGroup->addAction(showObjectsAct);
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(fileOpen);
    fileMenu->addAction(fileSave);
    fileMenu->addAction(fileSave);
    fileMenu->addSeparator();
    fileMenu->addAction(fileExit);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(showClassesAct);
    viewMenu->addAction(showFieldsAct);
    viewMenu->addAction(showObjectsAct);
}

void MainWindow::showTables(AccessMode accesMod, DisplayMode displayMode)
{
    freeResources();

    int tablesCount = dbHandler->getTablesCount();
    tableViews = new QVector<TableView*>(tablesCount);

    for (int i = 0; i < tablesCount; i++)
    {
        TableView *tv = new TableView(tablesScene);

        tv->setID(i);
        tv->setTableName(dbHandler->getTableName(i));
        tv->setAccesMod(accesMod);
        tv->show();

        connect(tv, SIGNAL(xChanged(uint,int)),
                this, SLOT(tableXChanged(uint,int)));

        connect(tv, SIGNAL(yChanged(uint,int)),
                this, SLOT(tableYChanged(uint,int)));

        connect(tv, SIGNAL(widthChanged(uint,int)),
                this, SLOT(tableWidthChanged(uint,int)));

        connect(tv, SIGNAL(heightChanged(uint,int)),
                this, SLOT(tableHeightChanged(uint,int)));

        connect(tv, SIGNAL(tableNameChanged(uint,QString)),
                this, SLOT(tableNameChanged(uint,QString)));

        (*tableViews)[i] = tv;
    }

    setDisplayMode(displayMode);
}

void MainWindow::setDisplayMode(DisplayMode mode)
{
    displayMode = mode;
    int tablesCount = tableViews->size();

    TableView::setEmitSignals(false);

    switch (mode)
    {
        case CLASSES:
        {
            showClassesAct->setChecked(true);

            for (int i = 0; i < tablesCount; i++)
                tableViews->at(i)->setModel(nullptr);

            break;
        }

        case FIELDS:
        {
            showFieldsAct->setChecked(true);

            for (int i = 0; i < tablesCount; i++)
                tableViews->at(i)->setModel(dbHandler->getTableFieldsModel(i));

            break;
        }

        case OBJECTS:
        {
            showObjectsAct->setChecked(true);

            for (int i = 0; i < tablesCount; i++)
                tableViews->at(i)->setModel(dbHandler->getTableObjectsModel(i));

            break;
        }
    }

    for (int i = 0; i < tablesCount; i++)
        tableViews->at(i)->setGeometry(dbHandler->getTableGeometry(i, mode));

    TableView::setEmitSignals(true);

    tablesScene->adjustSize();
}

void MainWindow::tableXChanged(uint tableID, int x)
{
    tablesScene->adjustSize();

    dbHandler->setTableX(tableID, x, displayMode);
}

void MainWindow::tableYChanged(uint tableID, int y)
{
    tablesScene->adjustSize();

    dbHandler->setTableY(tableID, y, displayMode);
}

void MainWindow::tableWidthChanged(uint tableID, int width)
{
    tablesScene->adjustSize();

    dbHandler->setTableWidth(tableID, width, displayMode);
}

void MainWindow::tableHeightChanged(uint tableID, int height)
{
    tablesScene->adjustSize();

    dbHandler->setTableHeight(tableID, height, displayMode);
}

void MainWindow::tableNameChanged(uint tableID, const QString &name)
{
    tablesScene->adjustSize();

    dbHandler->setTableName(tableID, name);
}

void MainWindow::freeResources()
{
    if (tableViews == nullptr)
        return;

    foreach (TableView *view, *tableViews)
        delete view;

    delete tableViews;
    tableViews = nullptr;
}
