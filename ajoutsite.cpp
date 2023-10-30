#include "ajoutsite.h"
#include "ui_ajoutsite.h"
#include"connection.h"
#include <QSqlQuery>
#include "qdebug.h"


ajoutSite::ajoutSite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutSite)
{
    ui->setupUi(this);
}

ajoutSite::~ajoutSite()
{
    delete ui;
}

void ajoutSite::on_ConfAjoutSite_clicked()
{
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    m_db.connOpen();
    Nom = ui->NomAjoutSite->text();
    lieux = ui->LieuxAjoutSite->text();
    tarifeJournalier = ui->TarifAjoutSite->text();

    if(Nom.isEmpty() || lieux.isEmpty() || tarifeJournalier.isEmpty())
    {
        qDebug() << "Veuillez remplir tous les champs";
    }else
    {
        QSqlQuery requ;
        QString verifProd = "select count(*) from Site where Nom = :Nom";
        requ.prepare(verifProd);
        requ.bindValue(":Nom",Nom);
        requ.exec();
        if(requ.next())
        {
            if(requ.value(0).toInt() > 0)
            {
                qDebug()<<"Le produit"+Nom+" est déjà saisi";
            }
            else
            {

                QSqlQuery req;
                QString requete = "INSERT INTO Site(Nom,lieux,tarifeJournalier) VALUES(:Nom,:lieux,:tarifeJournalier);";
                req.prepare(requete);
                req.bindValue(":Nom",Nom);
                req.bindValue(":lieux",lieux);
                req.bindValue(":tarifeJournalier",tarifeJournalier);
                req.exec();
                m_db.connClose();
                this->close();

            }

        }
    }

}


void ajoutSite::on_AnnulAjoutSite_clicked()
{
    this->close();
}

