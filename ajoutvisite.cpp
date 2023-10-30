#include "ajoutvisite.h"
#include "ui_ajoutvisite.h"
#include"connection.h"
#include <QSqlQuery>
#include "qdebug.h"
#include <QComboBox>

ajoutVisite::ajoutVisite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutVisite)
{
    ui->setupUi(this);
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    else if (m_db.connOpen()) {
        QSqlQuery query;
        query.prepare("SELECT * FROM visite");
        if(query.exec()){
            QString NumVisiteur = query.value(0).toString();
            QString NomProduit = query.value(1).toString();
  /*        Visite visite(NumVisiteur,NomProduit);
            recupID = visite.getId();
            ui->NumeroVisiteur->addItem(visite.toString());
   */     }

    }

}


ajoutVisite::~ajoutVisite()
{
    delete ui;
}

void ajoutVisite::on_comfAjoutVisite_clicked()
{
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    m_db.connOpen();
   // NumeroVisiteur = ui->NumVisiteur;
    //NumSite = ui->NumSite;
    NbrJour = ui->Nbr->text();
    DateVisite = ui->dateAjout->text();

    if(NumeroVisiteur.isEmpty() || NumSite.isEmpty() || NbrJour.isEmpty() || DateVisite.isEmpty())
    {
        qDebug() << "Veuillez remplir tous les champs";
    }else
    {
        QSqlQuery requ;
        QString verifProd = "select count(*) from Visite where NumeroVisiteur = :NumeroVisiteur";
        requ.prepare(verifProd);
        requ.bindValue(":NumeroVisiteur",NumeroVisiteur);
        requ.exec();
        if(requ.next())
        {
            if(requ.value(0).toInt() > 0)
            {
                qDebug()<<"Le produit"+NumeroVisiteur+" est déjà saisi";
            }
            else
            {

                QSqlQuery req;
                QString requete = "INSERT INTO Visite(NumeroVisiteur,NumSite,NbrJour,DateVisite) VALUES(:NumeroVisiteur,:NumSite,:NbrJour,:DateVisite);";
                req.prepare(requete);
                req.bindValue(":NumeroVisiteur",NumeroVisiteur);
                req.bindValue(":NumSite",NumSite);
                req.bindValue(":NbrJour",NbrJour);
                req.bindValue(":DateVisite",DateVisite);
                req.exec();
                m_db.connClose();
                this->close();

            }

        }
    }
}


void ajoutVisite::on_annulAjoutVisite_clicked()
{
    this->close();
}


void ajoutVisite::on_NumVisiteur_activated(int index)
{
    QString itemText = ui->NumeroVisiteur->currentText();
    QStringList parts = itemText.split("-");
    if(parts.size() == 2){
        recupID = parts[0];
        QString nomVisiteur = parts[1];
        int id = ui->NumeroVisiteur->itemData(index).toInt();
        qDebug() << "ID:" << id;
        qDebug() << "NumeroVisiteur:" << recupID;
        qDebug() << "NumeroVisiteur:" << NumeroVisiteur;
    }
}


void ajoutVisite::on_NumeroVisiteur_currentIndexChanged(int index)
{

}
