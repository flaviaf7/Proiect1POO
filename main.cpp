#include <iostream>
#include <string.h>

using namespace std;

class Angajat {

    //atribute
        const int id_angajat;
        static int contorID; 
        char* nume;
        int LuniLucrate;
        float salariu;
        int* CNP;

    public:

    //constructori
        Angajat();
        Angajat(char* nume, int LuniLucrate, float salariu, int* CNP);
        Angajat(char* nume, int LuniLucrate);
        Angajat(char* nume);
        Angajat(const Angajat &obj); 
    
    /*
    constructorul de copiere
    se pune const pentru a proteja datele din obiectul de copiat
    se pune & pentru a putea accesa direct adresa obiectului de copiat
    astfel incat sa nu folosim memorie suplimentara daca cream alt obiect
    */

    //setters
        void setNume(char* nume){strcpy(this->nume, nume);};
        void setLuniLucrate(int LuniLucrate){this->LuniLucrate=LuniLucrate;}
        void setSalariu(float salariu){this->salariu=salariu;};
        void setCNP(int *CNP);
        

    //getters
        static int getContorID(){return Angajat::contorID;}
        char* getnume(){return this->nume;}
        float getSalariu(){return this->salariu;}
        int getLuniLucrate(){return this->LuniLucrate;}
        int* getCNP(){return this->CNP;}


    //supraincarcare operatori
        Angajat& operator =(const Angajat&);
        friend istream & operator >>(istream & in, Angajat & obj);
        friend ostream & operator <<(ostream & out, const Angajat & obj);
        char operator [] (int);
        Angajat& operator ++();
        Angajat operator ++(int);
        Angajat operator +(const Angajat &);
        Angajat operator +(int);
        Angajat operator -(int);
        operator float();
        bool operator == (const Angajat &a);
        bool operator > (const Angajat &a);

    //destructor
        ~Angajat();
};

//initializarea atributului static
int Angajat::contorID=1000;

//constructorul fara parametrii
Angajat::Angajat():id_angajat(contorID++)
{
    nume = new char[strlen("Anonim")+1];
    strcpy(nume,"Anonim");
    salariu = 0;
    LuniLucrate = 0;
}

//constructor cu 1 parametru
Angajat::Angajat(char* nume):id_angajat(contorID++)
{
    this->nume= new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->LuniLucrate=0;
    setSalariu(this->salariu);
    this->CNP = NULL;
}

//constructor cu 2 parametrii
Angajat::Angajat(char* nume, int LuniLucrate):id_angajat(contorID++)
{
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->LuniLucrate=LuniLucrate;
    setSalariu(this->salariu);
    this->CNP = NULL;
}

//constructorul cu toti parametrii
Angajat::Angajat(char* nume, int LuniLucrate, float Salariu, int* CNP):id_angajat(contorID++)
{
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->salariu=Salariu;
    this->LuniLucrate = LuniLucrate;
    this->CNP = new int[6];
    for (int i=0; i<6;i++){
        this->CNP[i]=CNP[i];
    }
}

//constructorul de copiere
Angajat::Angajat(const Angajat &obj):id_angajat(contorID++)
{
    this->nume=new char[strlen(obj.nume)+1];
    strcpy(this->nume,obj.nume);
    this->salariu=obj.salariu;
    this->LuniLucrate=obj.LuniLucrate;
    this->CNP = new int[6];
    for (int i=0; i<6;i++){
        this->CNP[i]=obj.CNP[i];
    }
}

//setter int*
void Angajat::setCNP(int* CNP)
{
    if (this->CNP != NULL){
        delete [] this->CNP;
        this->CNP=NULL;
    }
    this->CNP=new int[6];
    for (int i=0;i<6;i++){
        this->CNP[i]=CNP[i];
    }
}

//supraincarcarea operatorului =
Angajat& Angajat::operator =(const Angajat &obj)
{
    if (this != &obj)
    {
        if (this->nume != NULL){
            delete[] this->nume;
            this->nume = NULL;
        }

        this->nume= new char[strlen(obj.nume)+1];
        strcpy(this->nume, obj.nume);

        this->salariu=obj.salariu;
        this->LuniLucrate=obj.LuniLucrate;

        if (this->CNP != NULL){
            delete[] this->CNP;
            this->CNP=NULL;
        }

        this->CNP = new int[6];
        for (int i=0; i<6;i++){
            this->CNP[i]=obj.CNP[i];
        }
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
    cout << "CNP: ";
    if (obj.CNP != NULL){
        delete [] obj.CNP;
    }
    obj.CNP = new int[6];
    for (int i=0; i<6;i++){
        in >> obj.CNP[i];
    }
    return in;
}

//supraincarcarea operatorului <<
ostream & operator <<(ostream & out, const Angajat & obj)
{
    out<<"Id Angajat: "<<obj.id_angajat<<endl;
    out<<"Nume: "<<obj.nume<<endl;
    out<<"Salariu: "<<obj.salariu<<endl;
    out<<"Luni lucrate: "<<obj.LuniLucrate<<endl;
    out<<"CNP: ";
    for(int i=0;i<6;i++){
        out<<obj.CNP[i];
    }
    out<<endl;
    return out;
}

//supraincarcarea operatorului []
char Angajat::operator [] (int a)
{
    if(this->nume == NULL)
        throw runtime_error("Nume nu are caractere");
    if(a<0 || a>strlen(this->nume))
        throw runtime_error("Index invalid");
    else
        return this->nume[a];
}

//supraincarcarea operatorului ++ (Prima forma)
Angajat& Angajat::operator ++()
{
    this->LuniLucrate++;
    return *this;
}

//supraincarcarea operatorului ++ (A doua forma)
Angajat Angajat::operator ++(int)
{
    Angajat aux(*this);
    this->LuniLucrate++;
    return aux;
}

//supraincarcarea operatorului +
Angajat Angajat::operator +(const Angajat &)
{
    Angajat aux(*this);
    aux.LuniLucrate = this->LuniLucrate+aux.LuniLucrate;
    aux.salariu = this->salariu+aux.salariu;
    return aux;
}

//supraincarcarea operatorului +
Angajat Angajat::operator +(int a)
{
    Angajat aux(*this);
    aux.LuniLucrate=this->LuniLucrate+a;
    return aux;
}

//supraincarcarea operatorului -
Angajat Angajat::operator -(int a)
{
    Angajat aux(*this);
    aux.LuniLucrate=this->LuniLucrate-a;
    return aux;
}

//supraincarcarea operatorului cast pt float
Angajat::operator float(){return this->salariu;}

//supraincarcarea operatorului ==
bool Angajat::operator == (const Angajat &a){return strcmp(this->nume,a.nume)==0;}

//supraincarcarea operatorului >
bool Angajat::operator > (const Angajat &a){return strcmp(this->nume,a.nume)>0;}

        
//destructor
Angajat::~Angajat()
{
    if (this->nume != NULL){
        delete[] this-> nume;
        this->nume=NULL;
    }
    if (this->CNP != NULL){
        delete[] this->CNP;
        this->CNP=NULL;
    }
}


class Ingredient {
    private:

    //atribute
        string Nume;
        int Cantitate;
        char Categorie;
        bool OnStock;
        bool Organic;

    public:

    //constructori
        Ingredient();
        Ingredient(string Nume, int Cantitate, char Categorie, bool OnStock, bool Organic); 
        Ingredient(string Nume, int Cantitate, char Categorie); 
        Ingredient(string Nume, int Cantitate); 
        Ingredient(const Ingredient &obj);
        

    //setters
        void setNume(string Nume){this->Nume=Nume;}
        void setOnStock(bool OnStock){this->OnStock=OnStock;}
        void setCantitate(int Cantitate){this->Cantitate=Cantitate;}
        void setOrganic(bool Organic){this->Organic=Organic;}
        void setCategorie(char Categorie){this->Categorie=Categorie;}


    //getters
        string getNume(){return this->Nume;}
        bool getOnStock(){return this->OnStock;}
        int getCantitate(){return this->Cantitate;}
        bool getOrganic(){return this->Organic;}
        char getCategorie(){return this->Categorie;}


    //supraincarcare operatori
        Ingredient & operator =(const Ingredient &obj);
        friend istream & operator >>(istream & in, Ingredient & obj);
        friend ostream & operator <<(ostream & out, const Ingredient & obj);
        Ingredient& operator ++();
        Ingredient operator ++(int);
        Ingredient operator +(const Ingredient &);
        Ingredient operator +(int);
        Ingredient operator -(int);
        operator string();
        bool operator == (const Ingredient &I);
        bool operator > (const Ingredient &I);

    //metode CRUD (CreateReadUpdateDelete)
        void AfisareIngredient();
        void ModIngredient();
        void StergeIngredient();


    //destructor
        ~Ingredient(){};
};

//constructor fara parametrii
Ingredient::Ingredient(){
    Nume = "Ingredient";
    Cantitate = 0;
    Categorie = '-';
    OnStock = false;
    Organic = false;
}

//constructor cu 2 parametrii
Ingredient::Ingredient(string Nume, int Cantitate)
{
    this->Nume=Nume;
    this->Cantitate=Cantitate;
    if(this->Cantitate > 0)
        this->OnStock=true;
    else
        this->OnStock=false;
    this->Organic=false;
    this->Categorie='-';
}

//constructor cu 3 parametrii
Ingredient::Ingredient(string Nume, int Cantitate, char Categorie)
{
    this->Nume=Nume;
    this->Cantitate=Cantitate;
    if(Cantitate > 0)
        this->OnStock=true;
    else
        this->OnStock=false;
    this->Organic=false;
    this->Categorie=Categorie;
}

//constructor cu toti parametrii
Ingredient::Ingredient(string Nume, int Cantitate, char Categorie, bool OnStock, bool Organic){
    this->Nume=Nume;
    this->Cantitate=Cantitate;
    this->OnStock=OnStock;
    this->Organic=Organic;
    this->Categorie=Categorie;
}

//constructor de copiere
Ingredient::Ingredient(const Ingredient &obj)
{
    this->Nume=obj.Nume;
    this->Cantitate=obj.Cantitate;
    this->OnStock=obj.OnStock;
    this->Organic=obj.Organic;
    this->Categorie=obj.Categorie;
}

//overload la operatorul =
Ingredient &Ingredient::operator=(const Ingredient &obj){
    if(this != &obj){
        this->Nume=obj.Nume;
        this->Cantitate=obj.Cantitate;
        this->OnStock=obj.OnStock;
        this->Organic=obj.Organic;
        this->Categorie=obj.Categorie;
    }
    return *this;
}

//overload la operatorul >>
istream & operator >>(istream & in, Ingredient & obj)
{
    cout << "Nume Ingredient: ";
    in >> obj.Nume;
    cout << "Categorie: ";
    in >> obj.Categorie;
    cout << "Cantitate: ";
    in >> obj.Cantitate;
    cout << "On Stock[0/1]: ";
    in >> obj.OnStock;
    cout << "Organic[0/1]: ";
    in >> obj.Organic;

    return in;
}

//overload la operatorul <<
ostream & operator <<(ostream & out, const Ingredient & obj)
{
    out<<"Nume Ingredient: "<<obj.Nume<<endl;
    out<<"Categorie: "<<obj.Categorie<<endl;
    out<<"Cantitate: "<<obj.Cantitate<<endl;
    out<<"On Stock: "<<obj.OnStock<<endl;
    out<<"Organic: "<<obj.Organic<<endl;
    return out;
}

//supraincarcarea operatorului ++ (Prima forma)
Ingredient& Ingredient::operator ++()
{
    this->Cantitate++;
    if(this->Cantitate > 0)
        this->OnStock=true;
    return *this;
}

//supraincarcarea operatorului ++ (A doua forma)
Ingredient Ingredient::operator ++(int)
{
    Ingredient aux(*this);
    this->Cantitate++;
    if(this->Cantitate > 0)
        this->OnStock=true;
    return aux;
}

//supraincarcarea operatorului +
Ingredient Ingredient::operator +(const Ingredient &)
{
    Ingredient aux(*this);
    aux.Cantitate = this->Cantitate+aux.Cantitate;
    aux.OnStock = this->OnStock || aux.OnStock;
    return aux;
}

//supraincarcarea operatorului +
Ingredient Ingredient::operator +(int a)
{
    Ingredient aux(*this);
    if (this->Cantitate+a >= 0)
        aux.Cantitate=this->Cantitate+a;
    else
        aux.Cantitate=0;
        this->OnStock=false;
    if(this->Cantitate > 0)
        this->OnStock=true;
    return aux;
}

//supraincarcarea operatorului -
Ingredient Ingredient::operator -(int a)
{
    Ingredient aux(*this);
    if (this->Cantitate-a >= 0)
        aux.Cantitate=this->Cantitate-a;
    else
        aux.Cantitate=0;
        this->OnStock=false;
    if(this->Cantitate > 0)
        this->OnStock=true;
    return aux;
}

//supraincarcarea operatorului cast pt string
Ingredient::operator string(){return this->Nume;}

//supraincarcarea operatorului ==
bool Ingredient::operator == (const Ingredient &i){return this->Nume==i.Nume;}

//supraincarcarea operatorului >
bool Ingredient::operator > (const Ingredient &i){return this->Nume>i.Nume;}

//functie afisare
void Ingredient::AfisareIngredient()
{
    cout << this->Nume << " | ";
    cout << this->Categorie << " | ";
    cout << "Cantitate: " << this->Cantitate << " | ";
    if (this->OnStock == false)
        cout << "Nu este in stoc" << " | ";
    else
        cout << "Este in stoc" << " | ";
    if (this->Organic == false)
        cout << "Nu este organic" << endl;
    else
        cout << "Este organic" << endl;
}

//functie modificare
void Ingredient::ModIngredient(){
    string nume;
    bool stoc = false;
    int cnt;
    bool org;
    char cat;
    cout << "Noul nume al ingredientului: ";
    cin >> nume;
    cout << "Noua categorie: ";
    cin >> cat;
    cout << "Noua cantitate: ";
    cin >> cnt;
    if (cnt > 0)
        stoc = true;
    cout << "Organic [0/1]: ";
    cin >> org;
    this->Nume=nume;
    this->Cantitate=cnt;
    this->OnStock=stoc;
    this->Organic=org;
    this->Categorie=cat;
}

//functie stergere
void Ingredient::StergeIngredient(){
    this->~Ingredient();
}


class Produs {
    private:

    //atribute
        const int idProdus;
        static int contorP;
        char* NumeProdus;
        int NrIngrediente;
        Ingredient* Ingrediente;
        double Pret;
        int Cantitate;
        bool OnStock;

    public:

    //constructori
        Produs();
        Produs(char* NumeProdus, int NrIngrediente, Ingredient* Ingrediente, double Pret, int Cantitate);
        Produs(char* NumeProdus, int NrIngrediente, Ingredient* Ingrediente, double Pret);
        Produs(char* NumeProdus, int NrIngrediente, Ingredient* Ingrediente);
        Produs(const Produs &obj);


    //setters
        void setNumeProdus(char* NumeProdus);
        void setPret(double Pret){this->Pret=Pret;};
        void setOnStock(bool OnStock){this->OnStock=OnStock;}
        void setCantitate(int Cantitate){this->Cantitate=Cantitate;}


    //getters
        static int getContorP(){return Produs::contorP;}
        char* getNumeProdus(){return this->NumeProdus;}
        double getPret(){return this->Pret;}
        int getCantitate(){return this->Cantitate;}
        bool getOnStock(){return this->OnStock;}


    //supraincarcare operatori
        Produs & operator =(const Produs &obj);
        friend istream & operator >>(istream & in, Produs & obj);
        friend ostream & operator <<(ostream & out, const Produs & obj);
        Ingredient operator [] (int);
        Produs& operator ++();
        Produs operator ++(int);
        Produs operator +(const Produs &);
        Produs operator +(int);
        Produs operator -(int);
        operator bool();
        bool operator == (const Produs &p);
        bool operator > (const Produs &p);

    //destructor
        ~Produs();
};

int Produs::contorP=1000;

//constructor fara parametrii
Produs::Produs():idProdus(contorP++)
{
    NumeProdus = new char[strlen("Produs")+1];
    strcpy(NumeProdus,"Produs");
    Pret = 0;
    OnStock = false;
    Cantitate = 0;
    NrIngrediente =0;
    Ingrediente = NULL;
}

//constructor cu totii parametrii
Produs::Produs(char* NumeProdus, int NrIngrediente, Ingredient* Ingrediente, double Pret, int Cantitate):idProdus(contorP++)
{
    this->NumeProdus = new char[strlen(NumeProdus)+1];
    strcpy(this->NumeProdus,NumeProdus);
    this->NrIngrediente=NrIngrediente;
    this->Ingrediente = new Ingredient[NrIngrediente];
    for (int i=0; i<this->NrIngrediente; i++){
        this->Ingrediente[i]=Ingrediente[i];
    }
    this->Pret = Pret;
    this->Cantitate = Cantitate;
    if(this->Cantitate > 0)
        this->OnStock=true;
    else
        this->OnStock=false;

}

//constructor cu 4 parametrii
Produs::Produs(char* NumeProdus, int NrIngrediente, Ingredient* Ingrediente, double Pret):idProdus(contorP++)
{
    this->NumeProdus = new char[strlen(NumeProdus)+1];
    strcpy(this->NumeProdus,NumeProdus);
    this->NrIngrediente=NrIngrediente;
    this->Ingrediente = new Ingredient[NrIngrediente];
    for (int i=0; i<this->NrIngrediente; i++){
        this->Ingrediente[i]=Ingrediente[i];
    }
    this->Pret = Pret;
    this->Cantitate = 0;
    this->OnStock=false;

}

//constructor cu 3 parametrii
Produs::Produs(char* NumeProdus, int NrIngrediente, Ingredient* Ingrediente):idProdus(contorP++)
{
    this->NumeProdus = new char[strlen(NumeProdus)+1];
    strcpy(this->NumeProdus,NumeProdus);
    this->NrIngrediente=NrIngrediente;
    this->Ingrediente = new Ingredient[NrIngrediente];
    for (int i=0; i<this->NrIngrediente; i++){
        this->Ingrediente[i]=Ingrediente[i];
    }
    this->Pret = 0;
    this->Cantitate = 0;
    this->OnStock=false;

}

//constructor de copiere
Produs::Produs(const Produs &obj):idProdus(contorP++)
{
    this->NumeProdus=new char[strlen(obj.NumeProdus)+1];
    strcpy(this->NumeProdus,obj.NumeProdus);
    this->NrIngrediente=obj.NrIngrediente;
    this->Ingrediente=new Ingredient[NrIngrediente];
    for(int i=0;i<NrIngrediente;i++){
        this->Ingrediente[i]=obj.Ingrediente[i];
    }
    this->Pret=obj.Pret;
    this->OnStock=obj.OnStock;
    this->Cantitate=obj.Cantitate;
}

//setter char*
void Produs::setNumeProdus(char* NumeProdus)
{
    if (this->NumeProdus != NULL){
        delete [] this->NumeProdus;
        this->NumeProdus=NULL;
    }
    this->NumeProdus= new char[strlen(NumeProdus)+1];
    strcpy(this->NumeProdus, NumeProdus);
};

//overload la operatorul =
Produs &Produs::operator=(const Produs &obj){
    if(this != &obj)
    {
        if (this->NumeProdus != NULL){
            delete[] this->NumeProdus;
            this->NumeProdus=NULL;
        }

        this->NumeProdus= new char[strlen(obj.NumeProdus)+1];
        strcpy(this->NumeProdus, obj.NumeProdus);

        if (this->Ingrediente != NULL){
            delete[] this->Ingrediente;
            this->Ingrediente=NULL;
        }

        this->NrIngrediente=obj.NrIngrediente;
        this->Ingrediente = new Ingredient[obj.NrIngrediente];
        for (int i=0; i<obj.NrIngrediente; i++){
            this->Ingrediente[i]=obj.Ingrediente[i];
        }
        this->Pret=obj.Pret;
        this->Cantitate=obj.Cantitate;
        this->OnStock=obj.OnStock;
        
    }
    return *this;
}

//overload la operatorul >>
istream & operator >>(istream & in, Produs & obj)
{
    cout << "Nume Produs: ";
    char aux[20];
    in >> aux;
    if (obj.NumeProdus != NULL){
        delete [] obj.NumeProdus;
    }
    obj.NumeProdus = new char[strlen(aux)+1];
    strcpy(obj.NumeProdus,aux);
    cout << "Numar Ingrediente: ";
    in >> obj.NrIngrediente;
    if (obj.Ingrediente != NULL){
        delete [] obj.Ingrediente;
    }
    obj.Ingrediente = new Ingredient[obj.NrIngrediente];
    for (int i=0; i<obj.NrIngrediente;i++){
        cout << "Ingredientul " << i+1 << ":";
        in >> obj.Ingrediente[i];
    }
    cout << "Pret: ";
    in >> obj.Pret;
    cout << "Cantitate: ";
    in >> obj.Cantitate;
    if(obj.Cantitate > 0)
        obj.OnStock=true;
    else
        obj.OnStock=false;
    
    return in;
}

//overload la operatorul <<
ostream & operator <<(ostream & out, const Produs & obj)
{
    out<<"Id Produs: "<<obj.idProdus<<endl;
    out<<"Nume Produs: "<<obj.NumeProdus<<endl;
    out<<"Ingrediente: "<<endl;
    for(int i=0; i<obj.NrIngrediente-1;i++){
        out<<obj.Ingrediente[i]<<endl;
    }
    out<<"Pret: "<<obj.Pret<<endl;
    out<<"On Stock: "<<obj.OnStock<<endl;
    out<<"Cantitate: "<<obj.Cantitate<<endl;
    return out;
}

//supraincarcarea operatorului []
Ingredient Produs::operator [] (int a)
{
    if(this->Ingrediente == NULL)
        throw runtime_error("Produsul nu are ingrediente");
    if(a<0 || a>this->NrIngrediente)
        throw runtime_error("Index invalid");
    else
        return this->Ingrediente[a];
}

//supraincarcarea operatorului ++ (Prima forma)
Produs& Produs::operator ++()
{
    this->Cantitate++;
    if(this->Cantitate > 0)
        this->OnStock=true;
    return *this;
}

//supraincarcarea operatorului ++ (A doua forma)
Produs Produs::operator ++(int)
{
    Produs aux(*this);
    this->Cantitate++;
    if(this->Cantitate > 0)
        this->OnStock=true;
    return aux;
}

//supraincarcarea operatorului +
Produs Produs::operator +(const Produs &)
{
    Produs aux(*this);
    aux.Cantitate = this->Cantitate+aux.Cantitate;
    aux.OnStock = this->OnStock || aux.OnStock;
    return aux;
}

//supraincarcarea operatorului +
Produs Produs::operator +(int a)
{
    Produs aux(*this);
    if (this->Cantitate+a >= 0)
        aux.Cantitate=this->Cantitate+a;
    else
        aux.Cantitate=0;
        this->OnStock=false;
    if(this->Cantitate > 0)
        this->OnStock=true;
    return aux;
}

//supraincarcarea operatorului -
Produs Produs::operator -(int a)
{
    Produs aux(*this);
    if (this->Cantitate-a >= 0)
        aux.Cantitate=this->Cantitate-a;
    else
        aux.Cantitate=0;
        this->OnStock=false;
    if(this->Cantitate > 0)
        this->OnStock=true;
    return aux;
}

//supraincarcarea operatorului cast pt bool
Produs::operator bool(){return this->OnStock;}

//supraincarcarea operatorului ==
bool Produs::operator == (const Produs &p){return strcmp(this->NumeProdus,p.NumeProdus)==0;}

//supraincarcarea operatorului >
bool Produs::operator > (const Produs &p){return strcmp(this->NumeProdus,p.NumeProdus)>0;}

//destructor
Produs::~Produs(){
    if (this->NumeProdus != NULL){
        delete [] this->NumeProdus;
        this->NumeProdus = NULL;
    }
    if (this->Ingrediente != NULL){
        delete [] this->Ingrediente;
        this->Ingrediente=NULL;
    }
}


class Client{
    private:

    //atribute
        string Nume;
        int NrProduse;
        Produs* Comanda;
        int NrMasa;

    public:

    //constructori
        Client();
        Client(string Nume, int NrProduse, Produs* Comanda, int NrMasa);
        Client(string Nume, int NrProduse, Produs* Comanda);
        Client(string Nume);
        Client(const Client &obj);


    //setters
        void setNume(string Nume){this->Nume=Nume;}
        void setMasa(int NrMasa){this->NrMasa=NrMasa;}


    //getters
        string getNume(){return this->Nume;}
        int getNrMasa(){return this->NrMasa;}
        int getNrProduse(){return this->NrProduse;}
        Produs* getComanda() const {return this->Comanda;};


    //supraincarcare operatori
        Client& operator =(const Client&);
        friend istream & operator >>(istream & in, Client & obj);
        friend ostream & operator <<(ostream & out, const Client & obj);
        Produs operator [] (int);
        Client& operator ++();
        Client operator ++(int);
        Client operator +(const Client &);
        Client operator +(int);
        Client operator -(int);
        operator int();
        bool operator == (const Client &c);
        bool operator > (const Client &c);

    //destructor
        ~Client();
        
};

//constructor fara parametrii
Client::Client()
{
    Nume = "Anonim";
    NrProduse = 0;
    NrMasa = 0;
    Comanda = NULL;
}

//constructor cu 1 parametru
Client::Client(string Nume)
{
    this->Nume = Nume;
    this->NrProduse= 0;
    this->Comanda = NULL;
    this->NrMasa = 0;
}

//constructor cu 3 parametrii
Client::Client(string Nume, int NrProduse, Produs* Comanda)
{
    this->Nume = Nume;
    this->NrProduse= NrProduse;
    this->Comanda = new Produs[NrProduse];
    for (int i=0; i<this->NrProduse; i++){
        this->Comanda[i]=Comanda[i];
    }
    this->NrMasa = 0;
}

//constructor cu toti parametrii
Client::Client(string Nume, int NrProduse, Produs* Comanda, int NrMasa)
{
    this->Nume = Nume;
    this->NrProduse= NrProduse;
    this->Comanda = new Produs[NrProduse];
    for (int i=0; i<this->NrProduse; i++){
        this->Comanda[i]=Comanda[i];
    }
    this->NrMasa = NrMasa;
}

//constructor de copiere
Client::Client(const Client &obj)
{
    this->Nume=obj.Nume;
    this->NrProduse=obj.NrProduse;
    this->Comanda=new Produs[NrProduse];
    for (int i = 0;i<NrProduse;i++){
        this->Comanda[i]=obj.Comanda[i];
    }
    this->NrMasa=obj.NrMasa;
}

//supraincarcarea operatorului =
Client& Client::operator =(const Client &obj)
{
    if (this != &obj)
    {
        this->Nume=obj.Nume;
        this->NrProduse=obj.NrProduse;
        this->NrMasa=obj.NrMasa;

        if (this->Comanda != NULL){
            delete[] this->Comanda;
            this->Comanda=NULL;
        }

        this->Comanda = new Produs[NrProduse];
        for (int i=0; i<NrProduse;i++){
            this->Comanda[i]=obj.Comanda[i];
        }
    }
    return *this;
}

//overload la operatorul >>
istream & operator >>(istream & in, Client & obj)
{
    cout << "Nume Client: ";
    in >> obj.Nume;
    cout << "Numar Produse din comanda: ";
    in >> obj.NrProduse;
    if (obj.Comanda != NULL){
        delete [] obj.Comanda;
    }
    obj.Comanda = new Produs[obj.NrProduse];
    for (int i=0; i<obj.NrProduse;i++){
        cout << "Produsul " << i+1 << ":";
        in >> obj.Comanda[i];
    }
    cout << "Numarul mesei: ";
    in >> obj.NrMasa;
    return in;
}

//overload la operatorul <<
ostream & operator <<(ostream & out, const Client & obj)
{
    out<<"Nume Client: "<<obj.Nume<<endl;
    out<<"Produse din comanda: "<<endl;
    for(int i=0; i<obj.NrProduse-1;i++){
        out<<obj.Comanda[i]<<endl;
    }
    out<<"Numarul mesei: "<<obj.NrMasa<<endl;
    return out;
}

//supraincarcarea operatorului []
Produs Client::operator [] (int a)
{
    if(this->Comanda == NULL)
        throw runtime_error("Comanda nu are produse");
    if(a<0 || a>this->NrProduse)
        throw runtime_error("Index invalid");
    else
        return this->Comanda[a];
}

//supraincarcarea operatorului ++ (Prima forma)
Client& Client::operator ++()
{
    this->NrMasa++;
    return *this;
}

//supraincarcarea operatorului ++ (A doua forma)
Client Client::operator ++(int)
{
    Client aux(*this);
    this->NrMasa++;
    return aux;
}

//supraincarcarea operatorului +
Client Client::operator +(const Client &)
{
    Client aux(*this);
    aux.Nume = this->Nume+" "+aux.Nume;
    return aux;
}

//supraincarcarea operatorului +
Client Client::operator +(int a)
{
    Client aux(*this);
    if (this->NrMasa+a >= 0)
        aux.NrMasa=this->NrMasa+a;
    else
        aux.NrMasa=0;
    return aux;
}

//supraincarcarea operatorului -
Client Client::operator -(int a)
{
    Client aux(*this);
    if (this->NrMasa-a >= 0)
        aux.NrMasa=this->NrMasa-a;
    else
        aux.NrMasa=0;
    return aux;
}

//supraincarcarea operatorului cast pt int
Client::operator int(){return this->NrMasa;}

//supraincarcarea operatorului ==
bool Client::operator == (const Client &c){return this->Nume==c.Nume;}

//supraincarcarea operatorului >
bool Client::operator > (const Client &c){return this->NrMasa>c.NrMasa;}

//destructor
Client::~Client(){
    if (this->Comanda != NULL){
        delete [] this->Comanda;
        this->Comanda = NULL;
    }
}

int main()
{
    return 0;
}