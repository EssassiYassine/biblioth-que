    #ifndef LIVRE_H
    #define LIVRE_H
    #include <qstring.h>


    class livre
    {
    public:

        livre();
        void setname(QString name);
        void setauteur(QString auteurname);
        void setanne(QString date);
        void setcontenu(QString contenu);
        void set_renter(QString person);
        void set_id(QString id );
        QString get_id() const;
        QString getname() const;
        QString getauteur() const;
        QString getanne() const;
        QString getcontunnu() const;
        QString getrenter() ;
        bool operator==(const livre &other) const;
        bool operator!=(const livre &other) const;

    private:
        QString _titre, _auteur, _anne, _contunu,_person_louer,_id;


    };

    #endif // LIVRE_H
