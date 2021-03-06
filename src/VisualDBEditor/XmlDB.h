#ifndef XMLDB_H
#define XMLDB_H

#include <QtXml/QtXml>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTableView>

#include "AbstractDB.h"

class Table;
class Relation;

class XmlDB : public AbstractDB
{
public:
    XmlDB(const QString &fp);

    QMap<QString, uint> tableID;

    QString displayModeToString(DisplayMode mode);
    DisplayMode stringToDisplayMode(QString str);

    tuple<QVector<Table *>*, QVector<Relation *> *> fillTables() override;
    void save(QVector<Table* > *tables, QVector<Relation *> *relations) override;

private:
    QString filePath;
    QXmlStreamReader xmlReader;
    QXmlStreamWriter xmlWriter;

    void parseTable(QVector<Table *> *tables );
    tuple<QVector<Table *> *, QVector<Relation *> *> readXmlFile(const QString &);
};

#endif // XMLDB_H
