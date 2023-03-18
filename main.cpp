#include <iostream>
#include <string.h>
#include <stdlib.h>

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
        const int getId(){return this->id_angajat;}
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


    //Functionalitati

    //Prezice viitorul salariu al unui angajat
    //in functie de numarul lunilor lucrate
        float PrezicereSalariu(int Luni)
        {
            float sal=this->salariu;
            if (Luni>=12)
                sal+=1000*Luni/12;
            return sal;
        }


    //functie modificare
        void ModAngajat();

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
    this->CNP=NULL;
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
    if(obj.CNP != NULL){
        this->CNP = new int[6];
        for (int i=0; i<6;i++){
            this->CNP[i]=obj.CNP[i];
        }
    }else {this->CNP=NULL;};
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
            if (obj.CNP!=NULL)
                this->CNP[i]=obj.CNP[i];
            else{this->CNP[i]=0;}
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
    string cnpstring;
    in >> cnpstring;
    obj.CNP = new int[6];
    if (cnpstring.size()==6)
        for (int i=0; i<5;i++){
            obj.CNP[i]=cnpstring[i]-'0';
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
    if(obj.CNP!=NULL){ 
        out <<"CNP: ";
        for(int i=0;i<6;i++){
            out<<obj.CNP[i];
        }
        out <<endl;
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

//functie modificare
void Angajat::ModAngajat()
{
    char* n = new char[50];
    float sal;
    int luni;
    if (this->nume != NULL){
        delete [] this->nume;
    }
    cout << "Noul nume al angajatului: ";
    cin >> n;
    cout << "Noul salariu: ";
    cin >> sal;
    cout << "Luni lucrate: ";
    cin >> luni;
    cout << "CNP: ";
    this->nume= new char[strlen(n)+1];
    strcpy(this->nume, n);
    delete [] n;
    this->salariu=sal;
    this->LuniLucrate=luni;
    if (this->CNP != NULL){
        delete [] this->CNP;
    }
    this->CNP= new int[6];
    string cnpstring;
    cin >> cnpstring;
    if (cnpstring.size()==6)
        for (int i=0; i<6;i++){
            this->CNP[i]=cnpstring[i]-'0';
        }
}

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


    //functionalitati
        void ActualizeazaStoc(){
            if(this->Cantitate > 0){
                this->OnStock=true;
            }
            else{
                this->Cantitate=0;
                this->OnStock=false;
            }
        }

        void StergereCantitate(){
            if(this->Cantitate >= 1){
                this->Cantitate--;
                this->OnStock=true;
            }
            else{
                this->Cantitate=0;
                this->OnStock=false;
            }
        }


    //functie modificare
        void ModIngredient();


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
bool Ingredient::operator == (const Ingredient &i){return (this->Nume==i.Nume);}

//supraincarcarea operatorului >
bool Ingredient::operator > (const Ingredient &i){return this->Nume>i.Nume;}

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


class Client;

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
        const int getidProdus(){return this->idProdus;}
        static int getContorP(){return Produs::contorP;}
        char* getNumeProdus(){return this->NumeProdus;}
        int getNrIngrediente(){return this->NrIngrediente;}
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

        friend Client operator +(const Produs& p, const Client& c);

    //functionalitati

    //actualizeaza OnStock in functie de cantitatea si
    //atributul OnStock al fiecarui ingredient din produs
        void ActualizeazaStoc(){
            bool Stock=true;
            int cant=this->Ingrediente[0].getCantitate();
            for(int i=0; i<this->NrIngrediente;i++){
                if(!Ingrediente[i].getOnStock() || Ingrediente[i].getCantitate() < 1){
                    Stock=false;
                    break;
                }
                if (this->Ingrediente[i].getCantitate()<cant)
                    cant = this->Ingrediente[i].getCantitate();
            }
            if (Stock){
                this->OnStock=true;
                this->Cantitate=cant;
            }
            else {
                this->Cantitate=0;
                this->OnStock=false;
            }
        }

    //verifica daca se poate sterge o cantitate din produs
    //in caz afirmativ, se modifica actuala cantitate si cantitatile ingredientelor
    //din produs
    //in caz negativ, returneaza false
        bool StergereCantitate()
        {
            if (1 >= this->Cantitate){
                return false;
            }
            for (int i=0; i<this->NrIngrediente;i++){
                this->Ingrediente[i].setCantitate(Ingrediente[i].getCantitate()-1);
            }
            this->Cantitate--;
            this->ActualizeazaStoc();
            return true;
        }

    //metoda pentru stergerea unui ingredient dintr-un produs
        void StergeIngredient(Ingredient);

    //functie modificare
        void ModProdus();


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
    bool stoc = true;
    int cant = this->Ingrediente[0].getCantitate();
    for (int i =0; i<this->NrIngrediente;i++){
        if ((this->Ingrediente[i].getCantitate() < 1) || (this->Ingrediente[i].getOnStock() == false)){
            stoc=false;
            break;
        }
        if (this->Ingrediente[i].getCantitate()<cant)
            cant = this->Ingrediente[i].getCantitate();
    }
    if (stoc){
        this->OnStock=true;
        this->Cantitate=cant;
    }
    else {
        this->Cantitate=0;
        this->OnStock=false;
    }
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
    bool stoc = true;
    int cant = Ingrediente[0].getCantitate();
    for (int i =0; i<this->NrIngrediente;i++){
        if ((Ingrediente[i].getCantitate() < 1) || (Ingrediente[i].getOnStock() == false)){
            stoc=false;
            break;
        }
        if (Ingrediente[i].getCantitate()<cant)
            cant = Ingrediente[i].getCantitate();
    }
    if (stoc==true){
        this->OnStock=true;
        this->Cantitate=cant;
    }
    else {
        this->Cantitate=0;
        this->OnStock=false;
    }

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
    out<<"Pret: "<<obj.Pret<<endl;
    out<<"On Stock: "<<obj.OnStock<<endl;
    out<<"Cantitate: "<<obj.Cantitate<<endl<<endl;
    if(obj.NrIngrediente!=0){
        out<<"Ingrediente: "<<endl;
        for(int i=0; i<obj.NrIngrediente;i++){
            out<<obj.Ingrediente[i]<<endl;  
        }
    }else{out<<"Nu are ingrediente\n";}
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

//functie modificare
void Produs::ModProdus()
{
    char* nume=new char[50];
    double p;
    int c;
    if (this->NumeProdus!=NULL){
        delete[] this->NumeProdus;
    }
    cout << "Noul nume al ingredientului: ";
    cin >> nume;
    this->NumeProdus=new char[strlen(nume)+1];
    strcpy(this->NumeProdus,nume);
    cout << "Noul pret: ";
    cin >> p;
    cout << "Noua cantitate: ";
    cin >> c;
    if (c > 0)
        this->OnStock= true;
    this->Pret=p;
    this->Cantitate=c;
    delete[]nume;
}

//functie stergere Ingredient din produs
void Produs::StergeIngredient(Ingredient I)
{
    Ingredient* aux = new Ingredient[this->NrIngrediente-1];
    int index=0;
    for (int i=0; i<this->NrIngrediente; i++){
        if(this->Ingrediente[i]==I)
            continue;
        aux[index++]=this->Ingrediente[i];
    }
    this->NrIngrediente--;
    delete [] this->Ingrediente;
    this->Ingrediente = new Ingredient[NrIngrediente];
    for(int i=0; i<NrIngrediente;i++)
        this->Ingrediente[i]=aux[i];
    this->NrIngrediente--;
    delete [] aux;
}

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
        void setNrProduse(int NrProduse){this->NrProduse=NrProduse;}


    //getters
        string getNume(){return this->Nume;}
        int getNrMasa(){return this->NrMasa;}
        int getNrProduse(){return this->NrProduse;}


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

        friend Client operator +(const Client& c, const Produs& p);
        friend Client operator +(const Produs& p, const Client& c);
        friend Client operator -(const Client& c, const Produs& p);

    //functionalitati

    //calculeaza pretul total al comenzii
        double PretComanda();

    //afiseaza comanda
        void getComanda() {
            cout<<"Comanda:"<<endl;
            if(NrProduse==0){cout<<"Nu aveti niciun produs in comanda dumneavoastra\n";}
            else{
                for (int i=0; i< this->NrProduse; i++){
                    cout<<this->Comanda[i].getNumeProdus() << ": "<<Comanda[i].getPret() <<" lei"<<endl;
                }
                cout<<"\nPret total: "<<this->PretComanda()<<endl;
            }
        }



    //sterge produs din comanda
        void StergeProdus(Produs);

    //functie modificare client
        void ModClient();

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
        if (NrProduse > 0){
        this->Comanda = new Produs[this->NrProduse];
        for (int i=0; i<this->NrProduse;i++){
            this->Comanda[i]=obj.Comanda[i];
        }
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

//PretComanda
double Client::PretComanda(){
    double Pret=0;
    for(int i=0; i<this->NrProduse;i++){
        Pret+=this->Comanda[i].getPret();
    }
    return Pret;
}




//Sterge produs din comanda
void Client::StergeProdus(Produs P)
{
    Produs* aux;
    aux = this->Comanda;
    if (this->Comanda!= NULL){
        delete[] this->Comanda;
        this->Comanda=NULL;
    }
    this->Comanda = new Produs[NrProduse--];
    int index;
    for (int i=0; i<this->NrProduse; i++){
        if (aux[i]==P)
            continue;
        this->Comanda[index++]=aux[i];
    }
}


//functie modificare
void Client::ModClient()
{
    string n;
    int masa;
    cout << "Noul nume al clientului: ";
    cin >> n;
    cout << "Noul numar al mesei: ";
    cin >> masa;
    this->Nume=n;
    this->NrMasa=masa;
}

//destructor
Client::~Client(){
    if (this->Comanda != NULL){
        delete [] this->Comanda;
        this->Comanda = NULL;
    }
}


// operatorul + intre Client si Produs (pt a adauga un produs la comanda clientului)
Client operator +(const Client& c, const Produs& p)
{
    Client aux = c;
    if (aux.Comanda!=NULL){
        delete[] aux.Comanda;
    }
    aux.Comanda=new Produs[aux.NrProduse +1];
    for (int i = 0; i<aux.NrProduse; i++){
        aux.Comanda[i]=c.Comanda[i];
    }
    aux.Comanda[aux.NrProduse]=p;
    aux.NrProduse++;
    return aux;
}

Client operator +(const Produs& p, const Client& c)
{
    Client aux = c;
    if (aux.Comanda!=NULL){
        delete[] aux.Comanda;
    }
    aux.Comanda=new Produs[aux.NrProduse +1];
    for (int i = 0; i<aux.NrProduse; i++){
        aux.Comanda[i]=c.Comanda[i];
    }
    aux.Comanda[aux.NrProduse]=p;
    aux.NrProduse++;
    return aux;
}

Client operator -(const Client& c, const Produs& p)
{
    Client aux = c;
    int index=0;
    if (aux.Comanda!=NULL){
        delete[] aux.Comanda;
        aux.Comanda=NULL;
    }
    aux.NrProduse--;
    if (aux.NrProduse>0){
        aux.Comanda=new Produs[aux.NrProduse];
        for (int i=0; i<c.NrProduse; i++){
            if (c.Comanda[i]==p)
                continue;
            aux.Comanda[index]=c.Comanda[i];
            index++;
        }
    }
    return aux;
}

void StergeAngajat(Angajat* A, int& NrAn, int id)
    {
        Angajat* aux = new Angajat[NrAn-1];
        int idx=0;
        for(int i = 0; i< NrAn; i++){
            if (A[i].getId() != id){
                aux[idx++]=A[i];
            }
        }
        NrAn--;
        A = new Angajat[NrAn];
        for (int i=0; i<NrAn;i++){
            A[i]=aux[i];
        }
        delete [] aux;
    }

void StergeProdus(Produs* P, int& NrProd, int id)
    {
        Produs* aux = new Produs[NrProd-1];
        int idx=0;
        for(int i = 0; i< NrProd; i++){
            if (P[i].getidProdus() != id){
                aux[idx++]=P[i];
            }
        }
        NrProd--;
        P = new Produs[NrProd];
        for (int i=0; i<NrProd;i++){
            P[i]=aux[i];
        }
        delete [] aux;
    }

void StergeIngr(Ingredient* I, int& NrIngr, string nume)
    {
        Ingredient* aux = new Ingredient[NrIngr-1];
        int idx=0;
        for(int i = 0; i< NrIngr; i++){
            if (I[i].getNume() != nume){
                aux[idx++]=I[i];
            }
        }
        NrIngr--;
        for (int i=0; i<NrIngr;i++){
            I[i]=aux[i];
        }
        delete [] aux;
    }

void meniuprincipal()
{
    system("cls");
    cout << "Bine ai venit la Cafeneaua FMI!\n\n";
    cout << "Selecteaza tipul user-ului:\n\n";
    cout << "1. Client\n2. Angajat\n3. Admin\n0. Exit\n\n";
}

void meniuClient()
{
    system("cls");
    cout << "Buna ziua! Cu ce va putem ajuta?\n\n";
    cout << "1.Meniu\n0.Exit\n\n";
}

void meniuProduse(int nrProd, Produs* P, Client &User)
{
    system("cls");
    cout <<"Acesta este meniul. Puteti adauga la comanda dumneavoastra orice produs din meniu, in limita stocului.\n\n";
    for (int i=0; i<nrProd; i++)
    {
        cout <<P[i].getidProdus() <<". "<< P[i].getNumeProdus() <<" | "<<P[i].getCantitate()<<endl<<endl;
    }

    User.getComanda();
    cout<<"\nOptiuni:\n0. Exit\n1. Adauga la comanda\n2. Sterge din comanda\n3. Finalizare comanda\n";
}

void meniuAngajat()
{
    system("cls");
    cout << "Vezi informatii despre angajatul cu id-ul: ";
}

void meniuAdministrator()
{
    system("cls");
    cout << "Meniu administrator:\n\n0. Exit\n1. Angajati\n2. Produse\n3. Ingrediente\n";
}

int main()
{
    int* cnp1 = new int[6]{5,3,2,4,5,2};
    Angajat A1("Ana", 24, 2000, cnp1);
    Angajat A2("Bogdan", 36);
    Angajat A3("Cosmin");

    Angajat A[20]={A1,A2,A3};

    Ingredient D("Cafea", 1000, 'A', true, false);
    Ingredient E("Zahar", 200, 'B', true, false);
    Ingredient F("Lapte", 500, 'C', true, true);
    Ingredient G("Apa", 1000, 'A', true, true);


    // Ingredient* I1 = new Ingredient[3]{D,E,F};
    // Ingredient* I2 = new Ingredient[2]{D,E};
    // Ingredient* I3 = new Ingredient[2]{D,F};
    // Ingredient* I4 = new Ingredient[1]{G};

    Ingredient I1[3] = {D,E,F};
    Ingredient I2[2] = {D,E};
    Ingredient I3[2] = {D,F};
    Ingredient I4[1] = {G};

    Ingredient All_Ing[20] ={D,E,F,G};

    Ingredient* In[20]={I1,I2,I3,I4};

    Produs P1("Cappuccino", 3, I1, 10.0);
    Produs P2("Latte", 3, I1, 15.0);
    Produs P3("Apa", 1, I4, 5.0);
    Produs P4("Cafea cu zahar", 2, I2);
    Produs P5("Cafea cu lapte", 2, I3);

    Produs P[20]={P1,P2,P3,P4,P5};

    Client C1("Ionescu Ion");
    Client C2("Popescu Pop");

    Client C[20] = {C1,C2};

    int alegere;
    int nrAn=3, nrCli=2, nrProd=5, nrIngr=4, nrIn=4, nrComanda=0;
    Client User("User");

    do
    {
            meniuprincipal();
            cin >> alegere;
            int alegere1;
            switch(alegere)
            {
                case 0: //exit
                    break;
                case 1: //client
                        {
                        do{
                            meniuClient();
                            cin >> alegere1;
                            int alegere2;
                            if(alegere1==0){break;}//Exit
                            else if(alegere1==1){//Meniu Produse
                                do
                                {
                                    meniuProduse(nrProd, P, User);
                                    cin >> alegere2;
                                    if (alegere2==0){break;}
                                    else if(alegere2==1){
                                        //adauga produs
                                        int id, idx;
                                        bool gasit=false, posibil=false;
                                        cout << "\nId-ul produsului pe care doresti sa-l adaugi la comanda: ";
                                        cin >> id;
                                        for (int i = 0; i<nrProd;i++){
                                            if (P[i].getidProdus()==id){
                                                if(P[i].StergereCantitate()){                                                    
                                                    User = User+P[i];
                                                    idx=i;
                                                    posibil = true;
                                                }
                                                gasit=true;
                                            }
                                        }
                                        cout << "Produsul cu id-ul " << id;
                                        if(gasit){if (posibil){cout<<" a fost adaugat la comanda.\n";}
                                                else{cout <<" nu are cantitate destula pentru a putea fi adaugat la comanda. Incercati o cantitate mai mica.\n";}}
                                        else{cout <<" nu a fost gasit in meniu.\n";}
                                        nrComanda++;
                                        system("pause");
                                    }
                                    else if(alegere2==2){
                                        //sterge produs
                                        if (nrComanda!=0){
                                            cout << "Numele produsului pe care doresti sa-l stergi din comanda: ";
                                            string s;
                                            bool gasit=false;
                                            cin >> s;
                                            for(int i=0; i<nrComanda;i++){
                                                if (s==User[i].getNumeProdus()){
                                                    User = User-User[i];
                                                    gasit=true;
                                                    break;
                                                }
                                            }
                                            if(gasit){
                                                for (int i=0; i<nrProd;i++){
                                                    if(s==P[i].getNumeProdus())
                                                        P[i].setCantitate(P[i].getCantitate()+1);
                                                }
                                            }
                                            cout << "\n\nProdusul cu numele "<< s;
                                            if (gasit){cout << " a fost sters din comanda.\n";
                                            }else{cout << " nu exista in comanda.\n";}
                                            nrComanda--;
                                        }
                                        else{cout << "Nu puteti sterge un produs daca nu aveti niciunul in comanda.\n";}
                                        system("pause");
                                    }else if(alegere2==3){
                                        //finalizeaza comanda
                                        system("cls");
                                        User.getComanda();
                                        while (nrComanda>0){
                                            User=User-User[0];
                                            nrComanda--;
                                        }
                                        system("pause");
                                    }else{
                                        cout<<"Optiune inexistenta. Mai incercati o data.\n";
                                        system("pause");
                                    }
                                }while(alegere2);

                            }else {
                                cout<<"Optiune inexistenta. Mai incercati o data.\n";
                                system("pause");
                            }
                        }while(alegere1);
                        break;
                        }

                case 2: //Meniu Angajat
                        {
                        meniuAngajat();
                        int id_a;
                        bool gasitA=false;
                        cin >> id_a;
                        cout << endl;
                        for (int i=0; i<nrAn; i++){
                            if(id_a==A[i].getId()){
                                cout << A[i];
                                gasitA=true;
                                break;
                            }
                        }
                        if(gasitA==false){cout<<"Angajatul cu ID-ul "<< id_a <<" nu exista.\n";}
                        system("pause");
                        break;
                        }
                case 3: //Meniu administrator
                        {
                        int alegere3;
                        do{
                        meniuAdministrator();
                        cin >> alegere3;
                        if(alegere3==0){break;}
                        else if(alegere3==1){
                            int alegere4;
                            do{
                            system("cls");
                            cout << "Administrare angajati:\n\n";
                            for (int i=0; i<nrAn; i++){
                                cout<<A[i]<<endl;
                            }
                            cout << "\nOptiuni:\n0. Exit\n1. Adauga angajat\n2. Sterge angajat\n3. Modifica angajat\n";
                            cin >>alegere4;
                            if(alegere4==0){break;}
                            else if(alegere4==1){
                                Angajat aux;
                                cin >> aux;
                                A[nrAn++] = aux;
                            }else if(alegere4==2){
                                cout <<"\nIntrodu id-ul angajatului pe care vrei sa il stergi: ";
                                int id, idx=0;
                                cin >> id;
                                StergeAngajat(A,nrAn,id);
                            }else if(alegere4==3){
                                cout <<"\nIntrodu id-ul angajatului pe care vrei sa il modifici: ";
                                int id, idx=0;
                                cin >> id;
                                for (int i=0;i<nrAn;i++){
                                    if(id==A[i].getId()){
                                        A[i].ModAngajat();
                                    }
                                }
                            }
                            }while(alegere4);
                        }else if(alegere3==2){
                            int alegere4;
                            do
                            {
                            system("cls");
                            cout << "Administrare produse:\n\n";
                            for (int i=0; i<nrProd; i++){
                                cout<<P[i]<<endl<<endl;
                            }
                            cout << "\nOptiuni:\n0. Exit\n1. Adauga produs\n2. Sterge produs\n3. Modifica produs\n";
                            cin >>alegere4;
                            if(alegere4==0){break;}
                            else if(alegere4==1){
                                Produs aux;
                                cin >> aux;
                                P[nrProd] = aux;
                            }else if(alegere4==2){
                                cout <<"\nIntrodu id-ul produsului pe care vrei sa il stergi: ";
                                int id, idx=0;
                                cin >> id;
                                StergeProdus(P,nrProd,id);
                            }else if(alegere4==3){
                                cout <<"\nIntrodu id-ul produsului pe care vrei sa il modifici: ";
                                int id, idx=0;
                                cin >> id;
                                for (int i=0;i<nrProd;i++){
                                    if(id==P[i].getidProdus()){
                                        P[i].ModProdus();
                                    }
                                }
                            }else{cout<<"Optiune inexistenta. Mai incercati o data.\n";}
                            }while(alegere4);
                        }else if(alegere3==3){
                            int alegere4;
                            do
                            {
                            system("cls");
                            cout << "Administrare ingrediente:\n\n";
                            for (int i=0; i<nrIngr; i++){
                                cout<<All_Ing[i]<<endl;
                            }
                            cout << "\nOptiuni:\n0. Exit\n1. Adauga ingredient\n2. Sterge ingredient\n3. Modifica ingredient\n";
                            int alegere4;
                            cin >>alegere4;
                            if(alegere4==0){break;}
                            else if(alegere4==1){
                                Ingredient aux;
                                cin >> aux;
                                All_Ing[nrIngr++] = aux;
                            }else if(alegere4==2){
                                cout <<"\nIntrodu numele ingredientului pe care vrei sa il stergi: ";
                                string nume;
                                cin >> nume;
                                for (int i=0; i<nrProd; i++){
                                    for (int j=0; j<P[i].getNrIngrediente();j++){
                                        if (P[i][j].getNume() == nume) {
                                            P[i].StergeIngredient(P[i][j]);
                                            break;
                                        }
                                    }
                                }
                                StergeIngr(All_Ing,nrIngr,nume);
                            }else if(alegere4==3){
                                cout <<"\nIntrodu numele ingredientului pe care vrei sa il modifici: ";
                                string nume;
                                cin >> nume;
                                for (int i=0;i<nrAn;i++){
                                    if(nume==All_Ing[i].getNume()){
                                        All_Ing[i].ModIngredient();
                                    }
                                }
                            }else{cout<<"Optiune inexistenta. Mai incercati o data.\n";}
                            }while(alegere4);
                        }
                        }while(alegere3);
                        break;
                        } 
                default:
                        cout << "Optiune inexistenta. Mai incercati o data.\n";
                        system("pause");
                        break;
            }
    }while(alegere);



    return 0;
}
