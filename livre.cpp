#include "livre.h"
#include<QtDebug>
livre::livre()
{
     _titre="";
     _auteur="";
     _anne="";
     _contunu="";
     _person_louer="";
     _id;

}
void livre::setname(QString nametitre){_titre = nametitre;}
void livre::setauteur(QString auteurname){_auteur = auteurname;}
void livre::setcontenu(QString contenu){_contunu=contenu;}
void livre::setanne(QString date){_anne=date;}
void livre::set_id(QString id){_id=id;};
QString livre::getname() const{return _titre;} ;
QString livre::getauteur() const{return _auteur;};
QString livre::getanne() const{return _anne;}
QString livre::getcontunnu() const{return _contunu;}
QString livre::getrenter() {return _person_louer;}
void livre::set_renter(QString renter){
    _person_louer =renter;
}

bool livre::operator==(const livre &rhs) const {
    return (_titre==rhs.getname()&& _auteur==rhs.getauteur() && _contunu == rhs.getcontunnu()) ;

}

bool livre::operator!=(const livre &rhs) const {
    return !(_titre==rhs.getname()&& _auteur==rhs.getauteur() && _contunu == rhs.getcontunnu()) ;
}


