#ifndef AJOUTSITE_H
#define AJOUTSITE_H

#include <QDialog>

namespace Ui {
class ajoutSite;
}

class ajoutSite : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutSite(QWidget *parent = nullptr);
    QString Nom;
    QString lieux;
    QString tarifeJournalier;
    ~ajoutSite();

private slots:
    void on_ConfAjoutSite_clicked();

    void on_AnnulAjoutSite_clicked();

private:
    Ui::ajoutSite *ui;
};

#endif // AJOUTSITE_H
