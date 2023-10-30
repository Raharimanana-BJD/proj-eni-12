#ifndef AJOUTVISITE_H
#define AJOUTVISITE_H

#include <QDialog>

namespace Ui {
class ajoutVisite;
}

class ajoutVisite : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutVisite(QWidget *parent = nullptr);
    QString recupID;
    QString ID;
    QString NumeroVisiteur;
    QString NumSite;
    QString NbrJour;
    QString DateVisite;
    ~ajoutVisite();

private slots:
    void on_comfAjoutVisite_clicked();

    void on_annulAjoutVisite_clicked();

    void on_NumVisiteur_activated(const QString &arg1);

    void on_NumVisiteur_activated(int index);

    void on_NumeroVisiteur_currentIndexChanged(int index);

private:
    Ui::ajoutVisite *ui;
};

#endif // AJOUTVISITE_H
