#include <iostream>
#include <string.h>

using namespace std;

class Angajat {
    private:
        const int id_angajat;
        static int contorID;
        float salariu;
        char* nume;         
        int LuniLucrate;

    public:
        Angajat();
        Angajat(char* nume, float salariu, int LuniLucrate);
        Angajat(char* nume, int LuniLucrate);
        Angajat(char* nume);
        Angajat(const Angajat &obj);

        //setters
        void setSalariu(float salariu);
        void setNume(char* nume){this->nume=nume;};
        void setLuniLucrate(int LuniLucrate){this->LuniLucrate=LuniLucrate;}

        //getters
        static int getContorID(){return Angajat::contorID;}
        string getnume(){return this->nume;}
        float getSalariu(){return this->salariu;}
        int getLuniLucrate(){return this->LuniLucrate;}
        
        //supraincare operatori
        Angajat& operator =(const Angajat&);
        friend istream & operator >>(istream & in, Angajat & obj);
        friend ostream & operator <<(ostream & out, const Angajat & obj);
        char & operator [] (int) const;

        //deconstructor
        ~Angajat();

};

int Angajat::contorID=1;

//constructorul fara parametrii
Angajat::Angajat():id_angajat(contorID++)
{
    nume = new char[strlen("Anonim")+1];
    strcpy(nume,"Anonim");
    salariu = NULL;
    LuniLucrate = NULL;
}

//constructorul cu toti parametrii
Angajat::Angajat(char* nume, float salariu, int LuniLucrate):id_angajat(contorID++)
{
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->salariu=salariu;
    this->LuniLucrate = LuniLucrate;
}

//constructor cu 1 parametru
Angajat::Angajat(char* nume):id_angajat(contorID++)
{
    this->nume= new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->LuniLucrate=0;
    setSalariu(this->salariu);
}

//constructor cu 2 parametrii
Angajat::Angajat(char* nume, int LuniLucrate):id_angajat(contorID++)
{
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->LuniLucrate=LuniLucrate;
    setSalariu(this->salariu);
}

//constructorul de copiere
Angajat::Angajat(const Angajat &obj):id_angajat(contorID++)
{
    this->nume=new char[strlen(obj.nume)+1];
    strcpy(this->nume,obj.nume);
    this->salariu=obj.salariu;
    this->LuniLucrate=obj.LuniLucrate;
}


void Angajat::setSalariu(float salariu)
{
    if(LuniLucrate>=24)
        this->salariu=salariu+2000.0;
    else if(LuniLucrate>=12)
        this->salariu=salariu+1000.0;
    else
        this->salariu=salariu;
}


//supraincarcarea operatorului =
Angajat& Angajat::operator =(const Angajat &obj)
{
    if (this != &obj)
    {
        if (this->nume != NULL){
            delete [] this->nume;
            this->nume = NULL;
        }
        this->nume= new char[strlen(obj.nume)+1];
        strcpy(this->nume, obj.nume);
        this->salariu=obj.salariu;
        this->LuniLucrate=obj.LuniLucrate;
    }
    return *this;
}

//supraincarcarea operatorului >>
istream & operator >>(istream & in, Angajat & obj)
{
    cout << "Nume Angajat: ";
    char aux[20];
    in >> aux;
    if (obj.nume != NULL){
        delete [] obj.nume;
    }
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume,aux);
    cout << "Salariu: ";
    in >> obj.salariu;
    cout << "Luni Lucrate: ";
    in >> obj.LuniLucrate;
}

//supraincarcarea operatorului <<
ostream & operator <<(ostream & out, const Angajat & obj)
{
    out<<"Id Angajat: "<<obj.id_angajat<<endl;
    out<<"Nume: "<<obj.nume<<endl;
    out<<"Salariu: "<<obj.salariu<<endl;
    out<<"Luni lucrate: "<<obj.LuniLucrate<<endl;
    return out;
}


Angajat::~Angajat(){   //destructor
    if (this->nume != NULL){
        delete[] this-> nume;
        this->nume=NULL;
    }
}

// de supraincarcat [], ++, --, +,-, cast, <, ==

class Produs {
    
};

class Meniu {

};

class Client {

};


int main()
{  
    return 0;
}