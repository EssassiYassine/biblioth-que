#ifndef BIBLIO_H
#define BIBLIO_H
#include "livre.h"
#include <QList>


class biblio
{
public:
    biblio();

    void addlivre(livre livre) const ;
    void replacelivre(livre livre,int new_livre_id) const;
    void removelivre(int id);
    QList<livre> getlistlivres() const;
    void changebibname(QString newname) const;
    const QString getname() const;
    bool operator==(const biblio &other) const;
    bool operator!=(const biblio &other) const;
private:
    mutable  QString _bibname;
    int _lastid;
    mutable QList<livre> _livres;
};

#endif // BIBLIO_H
