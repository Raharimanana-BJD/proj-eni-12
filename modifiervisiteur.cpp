#include "modifiervisiteur.h"
#include "ui_modifiervisiteur.h"
#include <QString>
#include <QSqlQuery>
#include "connection.h"

ModifierVisiteur::ModifierVisiteur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierVisiteur)
{
    ui->setupUi(this);
}

ModifierVisiteur::~ModifierVisiteur()
{
    delete ui;
}
QString ModifierVisiteur::NumModif(QString Numero){
    return Numero;
}
void ModifierVisiteur::GetMod(QString nom, QString adresse, QString provenance){
    ui->NomMod->setText(nom);
    ui->AdresseMod->setText(adresse);
    ui->ProvMod->setText(provenance);
}

void ModifierVisiteur::on_ComfMod_clicked()
{
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    m_db.connOpen();

    nom = ui->NomMod->text();
    adresse = ui->AdresseMod->text();
    provenance = ui->ProvMod->text();

    if(nom.isEmpty() || adresse.isEmpty() || provenance.isEmpty())
    {
        qDebug() << "Veuillez remplir tous les champs";
    }
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
            QString requete = "UPDATE Visiteur SET nom = :nom, adresse = :adresse, provenance = :provenance WHERE NumeroVisiteur = :num;";
            req.prepare(requete);
            req.bindValue(":nom",nom);
            req.bindValue(":adresse",adresse);
            req.bindValue(":provenance",provenance);
            req.bindValue(":num",Mod );
            req.exec();
            m_db.connClose();
            this->close();

        }

    }
}




void ModifierVisiteur::on_AnnulModifVisiteur_clicked()
{
    this->close();

}

