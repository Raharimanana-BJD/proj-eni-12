#include "ajoutvisiteur.h"
#include "ui_ajoutvisiteur.h"
#include"connection.h"
#include <QSqlQuery>
#include "qdebug.h"
#include "stylesheet.h"

ajoutvisiteur::ajoutvisiteur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutvisiteur)
{
    ui->setupUi(this);
    stylesheet style;
    ui->NomAjout->setStyleSheet(style.inputStyle);
    ui->AdresseAjout->setStyleSheet(style.inputStyle);
    ui->ProvAjout->setStyleSheet(style.inputStyle);

}

ajoutvisiteur::~ajoutvisiteur()
{
    delete ui;
}

void ajoutvisiteur::on_ComfAjout_clicked()
{
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    m_db.connOpen();

    nom = ui->NomAjout->text();
    adresse = ui->AdresseAjout->text();
    provenance = ui->ProvAjout->text();

    if(nom.isEmpty() || adresse.isEmpty() || provenance.isEmpty())
    {
        qDebug() << "Veuillez remplir tous les champs";
    }else
    {
        QSqlQuery requ;
        QString verifProd = "select count(*) from Visiteur where nom = :nom";
        requ.prepare(verifProd);
        requ.bindValue(":nom",nom);
        requ.exec();
        if(requ.next())
        {
            if(requ.value(0).toInt() > 0)
            {
                qDebug()<<"Le produit"+nom+" est déjà saisi";
            }
            else
            {

                QSqlQuery req;
                QString requete = "INSERT INTO Visiteur(nom,adresse,provenance) VALUES(:nom,:adresse,:provenance);";
                req.prepare(requete);
                req.bindValue(":nom",nom);
                req.bindValue(":adresse",adresse);
                req.bindValue(":provenance",provenance);
                req.exec();
                m_db.connClose();
                this->close();

            }

        }
    }

}


void ajoutvisiteur::on_AnnulAjout_clicked()
{
    this->close();
}

