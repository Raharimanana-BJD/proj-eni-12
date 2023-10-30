#ifndef MODIFSITE_H
#define MODIFSITE_H

#include <QDialog>

namespace Ui {
class modifSite;
}

class modifSite : public QDialog
{
    Q_OBJECT

public:
    explicit modifSite(QWidget *parent = nullptr);
    QString Mod;
    QString NumModifSite(QString Num);
    void GetMode(QString Nom,QString lieux,QString tarifeJournalier);
    QString Nom;
    QString lieux;
    QString tarifeJournalier;
    ~modifSite();

private slots:
    void on_ConfModSite_clicked();

private:
    Ui::modifSite *ui;
};

#endif // MODIFSITE_H
