#include "biblio.h"

biblio::biblio()
{

     _bibname = "new biblio";
     _livres;

}

void biblio::replacelivre(livre livre, int new_livre_id) const{_livres[new_livre_id]=livre;}
 void biblio::addlivre (livre new_livre) const{
    _livres.append(new_livre);
}
 bool biblio::operator==(const biblio &rhs) const {
     return (_bibname==rhs.getname()&& _livres==rhs.getlistlivres() );

 }

 bool biblio::operator!=(const biblio &rhs) const {
     return !(_bibname==rhs.getname()&& _livres==rhs.getlistlivres() );
 }

QList<livre> biblio::getlistlivres() const{return _livres;}
void biblio::removelivre(int id){_livres.removeAt(id);}
const QString biblio::getname() const{return _bibname;}
void biblio::changebibname(QString newname) const {
    _bibname = newname;
}

