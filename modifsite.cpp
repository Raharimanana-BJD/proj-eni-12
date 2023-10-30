#include "modifsite.h"
#include "ui_modifsite.h"
#include <QString>
#include <QSqlQuery>
#include "connection.h"
modifSite::modifSite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifSite)
{
    ui->setupUi(this);
}

modifSite::~modifSite()
{
    delete ui;
}
QString modifSite::NumModifSite(QString Num){
    return Num;
}
void modifSite::GetMode(QString Nom, QString lieux, QString tarifeJournalier){
    ui->NomModtSite->setText(Nom);
    ui->LieuxModSite->setText(lieux);
    ui->TarifModSite->setText(tarifeJournalier);
}
void modifSite::on_ConfModSite_clicked()
{
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
        return;  // Quitte la fonction si la connexion à la base de données échoue
    }

    // Pas besoin d'appeler m_db.connOpen() à nouveau

    // Récupérer les valeurs des champs de l'interface utilisateur
     Nom = ui->NomModtSite->text();
    lieux = ui->LieuxModSite->text();
    tarifeJournalier = ui->TarifModSite->text();

    if (Nom.isEmpty() || lieux.isEmpty() || tarifeJournalier.isEmpty())
    {
        qDebug() << "Veuillez remplir tous les champs";
        m_db.connClose();  // Ferme la connexion à la base de données avant de quitter la fonction
        return;
    }

    QSqlQuery requ;
    QString verifProd = "SELECT COUNT(*) FROM Site WHERE Nom = :Nom";
    requ.prepare(verifProd);
    requ.bindValue(":Nom", Nom);
    requ.exec();

    if (requ.next())
    {
        if (requ.value(0).toInt() > 0)
        {
            qDebug() << "Le produit " << Nom << " est déjà saisi";
        }
        else
        {
            QSqlQuery req;
            QString requete = "UPDATE Site SET Nom = :nom, lieux = :lieux, tarifeJournalier = :tarif WHERE NumeSite = :num;";
            req.prepare(requete);
            req.bindValue(":nom", Nom);
            req.bindValue(":lieux", lieux);
            req.bindValue(":tarif", tarifeJournalier);
            req.bindValue(":num", Mod);
            req.exec();
            m_db.connClose();  // Ferme la connexion à la base de données
            this->close();
        }
    }
    else
    {
        qDebug() << "Erreur lors de la vérification du produit existant";
    }

    m_db.connClose();  // Ferme la connexion à la base de données après utilisation
}


