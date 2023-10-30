#ifndef AJOUTVISITEUR_H
#define AJOUTVISITEUR_H

#include <QDialog>

namespace Ui {
class ajoutvisiteur;
}

class ajoutvisiteur : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutvisiteur(QWidget *parent = nullptr);
    QString nom;
    QString adresse;
    QString provenance;

    ~ajoutvisiteur();

private slots:
    void on_ComfAjout_clicked();

    void on_AnnulAjout_clicked();

private:
    Ui::ajoutvisiteur *ui;
};

#endif // AJOUTVISITEUR_H
