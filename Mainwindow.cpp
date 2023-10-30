#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "ajoutvisiteur.h"
#include"connection.h"
#include "qdebug.h"
#include <QSqlQuery>
#include "modifiervisiteur.h"
#include "ajoutsite.h"
#include "modifsite.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <qsqlerror.h>
#include "ajoutvisite.h"

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    affichVisiteur(ui->visiteurTable);
       affichSite(ui->tableSite);
       affichVisite(ui->tableVisite);
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::affichVisiteur(QTableView *table){
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    m_db.connOpen();
    model = new QSqlQueryModel();
    model->setQuery(" SELECT * FROM Visiteur");
    model->setHeaderData(0,Qt::Horizontal,tr("numero"));
    model->setHeaderData(1,Qt::Horizontal,tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,tr("adresse"));
    model->setHeaderData(3,Qt::Horizontal,tr("provenance"));
    ui->modifVisteurBtn->setDisabled(true);
    ui->SupVisiteurBtn->setDisabled(true);
    table->setModel(model);


}

void Mainwindow::affichSite(QTableView *table){
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    m_db.connOpen();
    model = new QSqlQueryModel();
    model->setQuery(" SELECT * FROM Site");
    model->setHeaderData(0,Qt::Horizontal,tr("Numero"));
    model->setHeaderData(1,Qt::Horizontal,tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,tr("Lieux"));
    model->setHeaderData(3,Qt::Horizontal,tr("Tarife Journalier"));
    ui->ModifSiteBtn->setDisabled(true);
    ui->SuppSite->setDisabled(true);
    table->setModel(model);


}

void Mainwindow::affichVisite(QTableView *table){
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    m_db.connOpen();
    model = new QSqlQueryModel();
    model->setQuery(" SELECT * FROM Visite");
    model->setHeaderData(0,Qt::Horizontal,tr("NumeroVisite"));
    model->setHeaderData(1,Qt::Horizontal,tr("NumSite"));
    model->setHeaderData(2,Qt::Horizontal,tr("NbrJour"));
    model->setHeaderData(3,Qt::Horizontal,tr("DateVisite"));
    ui->ModifVisite->setDisabled(true);
    ui->SupVisite->setDisabled(true);
    table->setModel(model);


}
void Mainwindow::on_visiteurTable_clicked(const QModelIndex &index)
{
    int rowSelected = index.row();
    numVisiteur = ui->visiteurTable->model()->data(ui->visiteurTable->model()->index(rowSelected,0)).toString();
    nom = ui->visiteurTable->model()->data(ui->visiteurTable->model()->index(rowSelected,1)).toString();
    adresse = ui->visiteurTable->model()->data(ui->visiteurTable->model()->index(rowSelected,2)).toString();
    provenance = ui->visiteurTable->model()->data(ui->visiteurTable->model()->index(rowSelected,3)).toString();
    ui->modifVisteurBtn->setDisabled(false);
    ui->SupVisiteurBtn->setDisabled(false);
    qDebug()<< numVisiteur+" "+nom+" "+" "+adresse+" "+provenance;

}


void Mainwindow::on_ajoutVisteur_clicked()
{
    ajoutvisiteur *a= new ajoutvisiteur();
    a->setModal(true);
    a->exec();
affichVisiteur(ui->visiteurTable);
}


void Mainwindow::on_SupVisiteurBtn_clicked()
{

    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    m_db.connOpen();
    QSqlQuery req;
    QString requette ="Delete from visiteur where NumeroVisiteur= :num ";
    req.prepare(requette);
    req.bindValue(":num",numVisiteur);
    req.exec();
    affichVisiteur(ui->visiteurTable);


}


void Mainwindow::on_modifVisteurBtn_clicked()
{
    ModifierVisiteur *Mo = new ModifierVisiteur();
    Mo->Mod = Mo->NumModif(this->numVisiteur);
    Mo->GetMod(this->nom,this->adresse,this->provenance);
    Mo->setModal(true);
    Mo->exec();
    affichVisiteur(ui->visiteurTable);
}
void Mainwindow::on_AjoutSite_clicked()
{
    ajoutSite *Aj = new ajoutSite();
    Aj->setModal(true);
    Aj->exec();
    affichSite(ui->tableSite);
}


void Mainwindow::on_tableSite_clicked(const QModelIndex &index)
{
    int rowSelected = index.row();
    numSite = ui->tableSite->model()->data(ui->tableSite->model()->index(rowSelected, 0)).toString();
    Nom = ui->tableSite->model()->data(ui->tableSite->model()->index(rowSelected, 1)).toString();
    lieux = ui->tableSite->model()->data(ui->tableSite->model()->index(rowSelected, 2)).toString();
    tarifeJournalier = ui->tableSite->model()->data(ui->tableSite->model()->index(rowSelected, 3)).toString();
    ui->ModifSiteBtn->setDisabled(false);
    ui->SuppSite->setDisabled(false);
    qDebug() << numSite + " " + Nom + " " + lieux + " " + tarifeJournalier;
}




void Mainwindow::on_ModifSiteBtn_clicked()
{
    // Créer une instance de la classe modifSite
    modifSite *mod = new modifSite();

    // Appeler la fonction NumModifSite avec numSite et stocker le résultat dans la variable Mod
    mod->Mod = mod->NumModifSite(this->numSite);

    // Passer les valeurs de Nom, lieux et tarifeJournalier à la classe modifSite
    mod->GetMode(this->Nom, this->lieux, this->tarifeJournalier);

    // Définir le dialogue mod comme modal et l'exécuter
    mod->setModal(true);
    mod->exec();

    // Mettre à jour la table ui->tableSite (assurez-vous que affichSite fonctionne correctement)
    affichSite(ui->tableSite);

    // Libérer la mémoire de l'objet mod
    delete mod;
}



void Mainwindow::on_SuppSite_clicked()
{
    Connection m_db;
    if (!m_db.connOpen())
    {
        qDebug() << "Failed to open database";
    }
    m_db.connOpen();
    QSqlQuery req;
    QString requette ="Delete from Site where NumeSite= :num ";
    req.prepare(requette);
    req.bindValue(":num",numSite);
    req.exec();
    affichSite(ui->tableSite);

}





void Mainwindow::on_Recherche_textChanged(const QString &arg1)
     {
    qDebug() << arg1;

    Connection m_db;
    if (!m_db.connOpen()) {
        qDebug() << "Failed to open database";
        return; // Quitter la fonction si la connexion à la base de données a échoué.
    }

    // Utilisez des guillemets simples autour des noms de colonnes et évitez les variables non déclarées.
    QSqlQuery requ;
    requ.exec("SELECT count(*) FROM visiteur WHERE nom LIKE '%" + arg1 + "%' OR NumeroVisiteur LIKE '%" + arg1 + "%'");

    if (requ.next()) {
        if (requ.value(0).toInt() == 0) {
           QMessageBox::warning(this, "Visiteur introuvable", "Le visiteur que vous avez saisi n'existe pas ou a déjà été supprimé.");

            // Créez un modèle vide pour l'en-tête
            QStandardItemModel *headerModel = new QStandardItemModel(0, 3); // 3 colonnes pour votre cas
            headerModel->setHorizontalHeaderLabels(QStringList() << "Nom" << "Adresse" << "Provenance");

            // Attribuez le modèle d'en-tête à votre QTableView
            ui->visiteurTable->setModel(headerModel);

            ui->modifVisteurBtn->setDisabled(true);
            ui->SupVisiteurBtn->setDisabled(true);
        } else {
            // Le code pour afficher les résultats de la recherche (comme vous l'avez déjà fait)

            model = new QSqlQueryModel();
            model->setQuery("SELECT * FROM visiteur WHERE nom LIKE '%" + arg1 + "%' OR NumeroVisiteur LIKE '%" + arg1 + "%'");
            model->setHeaderData(0, Qt::Horizontal, tr("Nom"));
            model->setHeaderData(1, Qt::Horizontal, tr("Adresse"));
            model->setHeaderData(2, Qt::Horizontal, tr("Provenance"));
            ui->visiteurTable->setStyleSheet("QHeaderView::section {background-color:#76D2D1}");
            ui->visiteurTable->setModel(model);

            ui->modifVisteurBtn->setDisabled(true);
            ui->SupVisiteurBtn->setDisabled(true);
        }
    }
}

void Mainwindow::on_rechNomNum_textChanged(const QString &arg1)
{
        qDebug() << arg1;

        Connection m_db;
        if (!m_db.connOpen())
        {
            qDebug() << "Failed to open database";
            return;
        }

        // Recherche dans la table "Visiteur"
        QSqlQuery requVisiteur;
        requVisiteur.exec("SELECT count(*) FROM Visiteur WHERE nom LIKE '%" + arg1 + "%' OR NumeroVisiteur LIKE '%" + arg1 + "%'");

        if (requVisiteur.next())
        {
            if (requVisiteur.value(0).toInt() == 0)
            {
                QMessageBox::warning(this, "Visiteur introuvable", "Le visiteur que vous avez saisi n'existe pas ou a déjà été supprimé.");

                QStandardItemModel *headerModel = new QStandardItemModel(0, 3);
                headerModel->setHorizontalHeaderLabels(QStringList() << "Nom" << "Adresse" << "Provenance");
                ui->visiteurTable->setModel(headerModel);
                ui->modifVisteurBtn->setDisabled(true);
                ui->SupVisiteurBtn->setDisabled(true);
            }
            else
            {
                model = new QSqlQueryModel();
                model->setQuery("SELECT * FROM Visiteur WHERE nom LIKE '%" + arg1 + "%' OR NumeroVisiteur LIKE '%" + arg1 + "%'");
                model->setHeaderData(0, Qt::Horizontal, tr("Nom"));
                model->setHeaderData(1, Qt::Horizontal, tr("Adresse"));
                model->setHeaderData(2, Qt::Horizontal, tr("Provenance"));
                ui->visiteurTable->setStyleSheet("QHeaderView::section {background-color:#76D2D1}");
                ui->visiteurTable->setModel(model);

                ui->modifVisteurBtn->setDisabled(true);
                ui->SupVisiteurBtn->setDisabled(true);
            }
        }

        // Recherche dans la table "Site"
        QSqlQuery requSite;
        requSite.exec("SELECT count(*) FROM Site WHERE Nom LIKE '%" + arg1 + "%' OR NumeSite LIKE '%" + arg1 + "%'");

        if (requSite.next())
        {
            if (requSite.value(0).toInt() == 0)
            {
                QMessageBox::warning(this, "Site introuvable", "Le site que vous avez saisi n'existe pas ou a déjà été supprimé.");

                QStandardItemModel *headerModel = new QStandardItemModel(0, 3); // 3 colonnes pour votre cas
                headerModel->setHorizontalHeaderLabels(QStringList() << "Nom" << "Lieux" << "Tarife Journalier");

                ui->tableSite->setModel(headerModel);

                ui->ModifSiteBtn->setDisabled(true);
                ui->SuppSite->setDisabled(true);
            }
            else
            {
                model = new QSqlQueryModel();
                model->setQuery("SELECT * FROM Site WHERE Nom LIKE '%" + arg1 + "%' OR NumeSite LIKE '%" + arg1 + "%'");
                model->setHeaderData(0, Qt::Horizontal, tr("Nom"));
                model->setHeaderData(1, Qt::Horizontal, tr("Lieux"));
                model->setHeaderData(2, Qt::Horizontal, tr("Tarife Journalier"));
                ui->tableSite->setStyleSheet("QHeaderView::section {background-color:#76D2D1}");
                ui->tableSite->setModel(model);

                ui->ModifSiteBtn->setDisabled(true);
                ui->SuppSite->setDisabled(true);
            }
        }
}


void Mainwindow::on_AjoutVisite_clicked()
{
    ajoutVisite *visite= new ajoutVisite();
    visite->setModal(true);
    visite->exec();
    affichVisite(ui->tableVisite);
}





void Mainwindow::on_tableVisite_clicked(const QModelIndex &index)
{
    int rowSelected = index.row();
    NumeroVisiteur = ui->tableVisite->model()->data(ui->tableVisite->model()->index(rowSelected, 0)).toString();
    NumSite = ui->tableVisite->model()->data(ui->tableVisite->model()->index(rowSelected, 1)).toString();
    NbrJour = ui->tableVisite->model()->data(ui->tableVisite->model()->index(rowSelected, 2)).toString();
    DateVisite = ui->tableVisite->model()->data(ui->tableVisite->model()->index(rowSelected, 3)).toString();
    ui->ModifVisite->setDisabled(false);
    ui->SupVisite->setDisabled(false);
    qDebug() << NumeroVisiteur + " " + NumSite + " " + NbrJour + " " + DateVisite;
}


