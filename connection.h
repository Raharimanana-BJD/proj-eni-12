#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QSqlDatabase>
#include "qdebug.h"

class Connection{
public:

    QSqlDatabase mydb;

    void connClose() {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen() {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C://Users//Bray//Desktop//GestionSite//DB.db");
        if (!mydb.open()) {
            qDebug() << "Échec d'ouverture de la base de données" << mydb.databaseName();
            return false;
        } else {
            qDebug() << "Connexion réussie à la base de données" << mydb.databaseName();
            return true;
        }
    }
};

#endif // CONNECTION_H
