#include "DBHandler.h"

DBHandler::DBHandler()
{

}

void DBHandler::openConnection(DBType t, QString url, QString dbName, QString userName, QString password, ConnectionFlags f)
{
    if(t == XML_FILE)
    {
        db = new XmlDB(url);
    }
    else qDebug() << "Error: openConnection() : DBHandler";

    emit connectionSuccess();
}

void DBHandler::fillTables(DisplayMode m, QVector<Table *> *tables)
{
    QVector<Table *> *t = db->fillTables(m, tables);
    emit fillTablesSuccess(t);
}

void DBHandler::setTables(QVector<Table*>* tbs)
{
    tables = tbs;
}

QVector<Table*>* DBHandler::getTables()
{
    return tables;
}


void DBHandler::setAccessMod(AccessMod am)
{
    accessMod = am;
}

AccessMod DBHandler::getAccessMod()
{
    return accessMod;
}

QVector< std::tuple<QString, QRect, QAbstractItemModel*> >* DBHandler::getTablesData()
{
    return tablesData;
}

void DBHandler::save()
{

}

void DBHandler::freeUnusedMemmory()
{

}


