#ifndef MODIFIERVISITEUR_H
#define MODIFIERVISITEUR_H

#include <QDialog>

namespace Ui {
class ModifierVisiteur;
}

class ModifierVisiteur : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierVisiteur(QWidget *parent = nullptr);
    QString Mod;
    QString NumModif(QString Numero);
    void GetMod(QString nom,QString adresse,QString provenance);
    QString nom;
    QString adresse;
    QString provenance;
    ~ModifierVisiteur();

private slots:
    void on_ComfMod_clicked();

    void on_AnnulAjout_2_clicked();

    void on_AnnulModifVisiteur_clicked();

private:
    Ui::ModifierVisiteur *ui;
};

#endif // MODIFIERVISITEUR_H
