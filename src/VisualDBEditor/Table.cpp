#include "Table.h"

Table::Table(){}

Table::~Table()
{
    if (fieldsModel != nullptr)
        delete fieldsModel;

    if (objectsModel != nullptr)
        delete objectsModel;
}

QString Table::getName()
{
    return name;
}

QStandardItemModel *Table::getFieldsModel()
{
    return fieldsModel;
}

QStandardItemModel *Table::getObjectsModel()
{
    return objectsModel;
}

void Table::setName(const QString &name)
{
    this->name = name;
}

void Table::setFieldsModel(QStandardItemModel *im)
{
    fieldsModel = im;
}

void Table::setObjectsModel(QStandardItemModel *im)
{
    objectsModel = im;
}

void Table::setCoord(int x, int y, DisplayMode mode)
{
    coordX[mode] = x;
    coordY[mode] = y;
}

void Table::resize(int w, int h, DisplayMode mode)
{
    tableWidth[mode] = w;
    tableHeight[mode] = h;
}

int Table::getCoordX(DisplayMode mode)
{
    return coordX[mode];
}

int Table::getCoordY(DisplayMode mode)
{
    return coordY[mode];
}

int Table::getWidth(DisplayMode mode)
{
    return tableWidth[mode];
}

int Table::getHeight(DisplayMode mode)
{
    return tableHeight[mode];
}

QRect Table::getGeometry(DisplayMode mode)
{
   return QRect(coordX[mode], coordY[mode],
                tableWidth[mode], tableHeight[mode]);
}

void Table::setCoordX(int x, DisplayMode mode)
{
    coordX[mode] = x;
}

void Table::setCoordY(int y, DisplayMode mode)
{
    coordY[mode] = y;
}

void Table::setWidth(int w, DisplayMode mode)
{
    tableWidth[mode] = w;
}

void Table::setHeight(int h, DisplayMode mode)
{
    tableHeight[mode] = h;
}

void Table::setGeometry(const QRect &rect, DisplayMode mode)
{
    coordX[mode] = rect.x();
    coordY[mode] = rect.y();
    tableWidth[mode] = rect.width();
    tableHeight[mode] = rect.height();
}
