#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTableView>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Mainwindow; }
QT_END_NAMESPACE

class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = nullptr);
    QSqlQueryModel *model;
    QString numVisiteur;
    QString nom;
    QString adresse;
    QString provenance;
    QString Nom;
    QString lieux;
    QString tarifeJournalier;
    QString numSite;
    void affichVisiteur(QTableView *table);
    void affichSite(QTableView *table);
    void affichVisite(QTableView *table);
    QString NumeroVisiteur;
    QString NumSite;
    QString NbrJour;
    QString DateVisite;
    ~Mainwindow();

private slots:
    void on_AjoutSiteBtn_clicked();

    void on_ajoutVisteur_clicked();

    void on_visiteurTable_clicked(const QModelIndex &index);

    void on_modifVisteurBtn_clicked();

    void on_SupVisiteurBtn_clicked();

    void on_AjoutSite_clicked();

    void on_tableSite_clicked(const QModelIndex &index);

    void on_SuppSiteBtn_clicked();

    void on_ModifSiteBtn_clicked();

    void on_SuppSite_clicked();

    void on_Recherche_textChanged(const QString &arg1);

    void on_Recherche_cursorPositionChanged(int arg1, int arg2);

    void on_rechNomNum_textChanged(const QString &arg1);

    void on_AjoutVisite_clicked();

    void on_SupVisite_clicked();

    void on_tableVisite_clicked(const QModelIndex &index);

private:
    Ui::Mainwindow *ui;
};
#endif // MAINWINDOW_H
