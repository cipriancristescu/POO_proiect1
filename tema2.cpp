#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;
class Exceptie_sal: public exception{
private:
    string eroare;
public:
    Exceptie_sal(const char* mesaj): eroare(mesaj){}
    const char* what() const throw()
    {
        return eroare.c_str();
    }
};

class Exceptie_mancare: public exception{
private:
    string eroare;
public:
    Exceptie_mancare(const char* mesaj): eroare(mesaj){}
    const char* what() const throw()
    {
        return eroare.c_str();
    }
};
/// Clasele pentru adăpostul de animale

class Adresa {
private:
    string strada;
    string codPostal;
    string oras;
///    inline static const string oras_std = "Bucuresti";

public:
    static Adresa creeazaAdresa(string strada, string codPostal) {
        return Adresa("Bucuresti", strada, codPostal);
    }
    Adresa() : strada(""), oras(""), codPostal("") {}
    Adresa(string strada, string oras, string codPostal)
        : strada(strada), oras(oras), codPostal(codPostal) {}

    /// Getteri și setteri
    string getStrada() const { return strada; }
    string getOras() const { return oras; }
    string getCodPostal() const { return codPostal; }
    void setStrada(string newStrada) { strada = newStrada; }
    void setOras(string newOras) { oras = newOras; }
    void setCodPostal(string newCodPostal) { codPostal = newCodPostal; }

    friend ostream& operator<<(ostream& out, const Adresa& adresa) {
        out << "Adresa: " << adresa.strada << ", " << adresa.oras << ", " << adresa.codPostal;
        return out;
    }
};

class Animal {
protected:
    string nume;
    string specie;
    double kgMancare; // noua variabilă membru
    double getKgMancare() const { return kgMancare; } // noua metodă


public:
    Animal() : nume(""), specie(""), kgMancare(0.0) {}
    Animal(string nume, string specie, double kgMancare) : nume(nume), specie(specie), kgMancare(kgMancare) {}

    /// Getteri și setteri
    string getNume() const { return nume; }
    string getSpecie() const { return specie; }
    void setNume(string newNume) { nume = newNume; }
    void setSpecie(string newSpecie) { specie = newSpecie; }

    virtual void mananca() = 0; // metoda pur virtuală

    friend ostream& operator<<(ostream& out, const Animal& animal) {
        if(animal.getKgMancare()>=0)
            out << "Animal: " << animal.getNume() << " (" << animal.getSpecie() << "), Mananca: " << animal.getKgMancare() << " kg";
        else throw Exceptie_mancare("Animalul trebuie sa manance");
        return out;
    }
};

class Caine : public Animal {
public:
    Caine() : Animal() {}
    Caine(string nume, string specie, double kgMancare) : Animal(nume, specie, kgMancare) {}

    void mananca() override {
        cout << nume << " mananca hrana pentru caini." << endl;
    }
    static void recomandatKg() {
        cout << "Un caine ar trebui sa manance 2 kd de bobite pe luna!!!";
    }
};

class Pisica : public Animal {
public:
    Pisica() : Animal() {}
    Pisica(string nume, string specie, double kgMancare) : Animal(nume, specie, kgMancare) {}

    void mananca() override {
        cout << nume << " mananca hrana pentru pisici." << endl;
    }
};

class Angajat {
protected:
    string nume;
    double salariu;

public:
    Angajat() : nume(""), salariu(0.0) {}
    Angajat(string nume, double salariu) : nume(nume), salariu(salariu) {}

    /// Getteri și setteri
    string getNume() const { return nume; }
    double getSalariu() const { return salariu; }
    void setNume(string newNume) { nume = newNume; }
    void setSalariu(double newSalariu) { salariu = newSalariu; }

    virtual void lucreaza() = 0; // metoda pur virtuală

    friend ostream& operator<<(ostream& out, const Angajat& angajat) {
        out << "Angajat: " << angajat.nume << ", Salariu: " << angajat.salariu;
        return out;
    }
};

class Veterinar : public Angajat {
public:
    Veterinar() : Angajat() {}
    Veterinar(string nume, double salariu) : Angajat(nume, salariu) {}

    void lucreaza() override {
        cout << nume << " este veterinar si ingrijeste animalele." << endl;
    }
};

class Receptionist : public Angajat {
public:
    Receptionist() : Angajat() {}
    Receptionist(string nume, double salariu) : Angajat(nume, salariu) {}

    void lucreaza() override {
        cout << nume << " este receptionist si preia apelurile." << endl;
    }
};

class Adapost {
private:
    string numeAdapost;
    Adresa adresa;
    vector<Animal*> animale; /// Folosim pointeri către animale pentru polimorfism
    vector<Angajat*> angajati; /// Folosim pointeri către angajați pentru polimorfism

public:
    Adapost() : numeAdapost(""), adresa(Adresa()), animale(vector<Animal*>()), angajati(vector<Angajat*>()) {}
    Adapost(string numeAdapost, Adresa adresa, vector<Animal*> animale, vector<Angajat*> angajati)
        : numeAdapost(numeAdapost), adresa(adresa), animale(animale), angajati(angajati) {}

    double salariuMediuAngajati() const {
        if (angajati.empty())
        {
            throw Exceptie_sal("Nu avem angajati.");
        }
        double totalSalarii = 0.0;
        for (const auto& angajat : angajati) {
            totalSalarii += angajat->getSalariu();
        }
        return totalSalarii / angajati.size();
    }

    // Afiseaza informatiile despre adapost
    void afisareInformatii() const {
        cout << "Nume adapost: " << numeAdapost << endl;
        cout << "Adresa: " << adresa << endl;
        cout << "Animale:" << endl;
        for (const auto& animal : animale) {
            cout << " - " << *animal << endl;
        }
        cout << "Angajati:" << endl;
        for (const auto& angajat : angajati) {
            cout << " - " << *angajat << endl;
        }
        cout << "Salariu mediu al angajatilor: " << salariuMediuAngajati() << endl;
    }
};

int main() {
    // Initializare Adresa
    Adresa adresa("Strada Principala", "Bucuresti", "12345");
    //Adresa adresa_provizorie = Adresa.creeazaAdresa("Strada Secundara", "54321");

    // Initializare vector de animale
    vector<Animal*> animale;

    //Caine.recomandatKg();

    animale.push_back(new Caine("Max", "Caine", 2.5)); // Caine
    animale.push_back(new Pisica("Zizi", "Pisica", 1.8)); // Pisica

    // Initializare vector de angajati
    vector<Angajat*> angajati;
    angajati.push_back(new Veterinar("Ionut ", 2000.0)); // Veterinar
    angajati.push_back(new Receptionist("Mihai", 3000.0)); // Receptionist

    // Initializare adapost
    Adapost adapost("Adapostul 1", adresa, animale, angajati);

    // Afisare informatii despre adapost
    try{
        adapost.afisareInformatii();
    } catch(exception e) {
        cout<<e.what();
    }
    // Eliberare memorie pentru animale
    for (auto& animal : animale) {
        delete animal;
    }

    // Eliberare memorie pentru angajati
    for (auto& angajat : angajati) {
        delete angajat;
    }

    return 0;
}
