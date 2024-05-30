#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <memory>
#include <exception>
#include <stdexcept>

using namespace std;

// Excepții
class Exceptie_sal: public exception {
private:
    string eroare;
public:
    Exceptie_sal(const char* mesaj) : eroare(mesaj) {}
    const char* what() const throw() {
        return eroare.c_str();
    }
};

class Exceptie_mancare: public exception {
private:
    string eroare;
public:
    Exceptie_mancare(const char* mesaj) : eroare(mesaj) {}
    const char* what() const throw() {
        return eroare.c_str();
    }
};

// Clasele pentru adăpostul de animale

class Adresa {
private:
    string strada;
    string codPostal;
    string oras;
public:
    static Adresa creeazaAdresa(string strada, string codPostal) {
        return Adresa("Bucuresti", strada, codPostal);
    }
    Adresa() : strada(""), codPostal(""), oras("") {}
    Adresa(string strada, string oras, string codPostal)
        : strada(strada), codPostal(codPostal), oras(oras) {}

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

// Pattern Factory Method pentru crearea animalelor
class Animal {
protected:
    string nume;
    string specie;
    double kgMancare;
public:
    double getKgMancare() const { return kgMancare; }

    Animal() : nume(""), specie(""), kgMancare(0.0) {}
    Animal(string nume, string specie, double kgMancare) : nume(nume), specie(specie), kgMancare(kgMancare) {}

    string getNume() const { return nume; }
    string getSpecie() const { return specie; }
    void setNume(string newNume) { nume = newNume; }
    void setSpecie(string newSpecie) { specie = newSpecie; }

    virtual void mananca() = 0;

    friend ostream& operator<<(ostream& out, const Animal& animal) {
        if (animal.getKgMancare() >= 0)
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
        cout << "Un caine ar trebui sa manance 2 kg de bobite pe luna!!!";
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

// Implementarea Factory Method pentru crearea animalelor
class AnimalFactory {
public:
    static unique_ptr<Animal> createAnimal(const string& type, const string& nume, const string& specie, double kgMancare) {
        if (type == "Caine")
            return unique_ptr<Caine>(new Caine(nume, specie, kgMancare));
        else if (type == "Pisica")
            return unique_ptr<Pisica>(new Pisica(nume, specie, kgMancare));
        else
            throw invalid_argument("Tip de animal necunoscut.");
    }
};

class Angajat {
protected:
    string nume;
    double salariu;

public:
    Angajat() : nume(""), salariu(0.0) {}
    Angajat(string nume, double salariu) : nume(nume), salariu(salariu) {}

    string getNume() const { return nume; }
    double getSalariu() const { return salariu; }
    void setNume(string newNume) { nume = newNume; }
    void setSalariu(double newSalariu) { salariu = newSalariu; }

    virtual void lucreaza() = 0;
    virtual string getTip() const = 0;  // Metodă virtuală pentru a returna tipul de angajat
    virtual string getRol() const = 0;  // Metodă virtuală pentru a returna rolul angajatului

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
    string getTip() const override {
        return "Veterinar";
    }
    string getRol() const override {
        return "Ingrijeste animalele";
    }
};

class Receptionist : public Angajat {
public:
    Receptionist() : Angajat() {}
    Receptionist(string nume, double salariu) : Angajat(nume, salariu) {}

    void lucreaza() override {
        cout << nume << " este receptionist si preia apelurile." << endl;
    }
    string getTip() const override {
        return "Receptionist";
    }
    string getRol() const override {
        return "Preia apelurile";
    }
};

// Clasă pentru reprezentarea cuștilor
class Cusca {
private:
    string id;
    int capacitate;
public:
    Cusca() : id(""), capacitate(0) {} // Constructor implicit adăugat
    Cusca(string id, int capacitate) : id(id), capacitate(capacitate) {}

    string getId() const { return id; }
    int getCapacitate() const { return capacitate; }

    friend ostream& operator<<(ostream& out, const Cusca& cusca) {
        out << "Cusca " << cusca.id << ": capacitate " << cusca.capacitate << " animale";
        return out;
    }
};

// Clasă pentru reprezentarea cantităților de mâncare
class Mancare {
private:
    string tip;
    double cantitate; // în kilograme
public:
    Mancare() : tip(""), cantitate(0.0) {} // Constructor implicit adăugat
    Mancare(string tip, double cantitate) : tip(tip), cantitate(cantitate) {}

    string getTip() const { return tip; }
    double getCantitate() const { return cantitate; }

    friend ostream& operator<<(ostream& out, const Mancare& mancare) {
        out << "Mancare " << mancare.tip << ": " << mancare.cantitate << " kg";
        return out;
    }
};

// Template pentru Inventar (Utilizare de Programare generică - Cerința de clasă șablon)
template <typename T>
class Inventar {
private:
    map<string, T> items; // Utilizarea unui container STL (map)
public:
    void adaugaItem(const string& nume, const T& item) {
        items[nume] = item;
    }

    T getItem(const string& nume) const {
        auto it = items.find(nume);
        if (it != items.end()) {
            return it->second;
        }
        throw invalid_argument("Itemul nu exista.");
    }

    friend ostream& operator<<(ostream& out, const Inventar& inventar) {
        for (const auto& item : inventar.items) {
            out << item.first << ": " << item.second << endl;
        }
        return out;
    }
};

// Funcție șablon pentru calculul hranei totale (Programare generică - funcție șablon)
template <typename T>
double calculeazaHranaTotala(const vector<unique_ptr<T>>& animale) {
    return accumulate(animale.begin(), animale.end(), 0.0, // Utilizare STL `accumulate`
        [](double suma, const unique_ptr<T>& animal) {
            return suma + animal->getKgMancare();
        });
}

// Singleton pentru clasa Adapost (Design pattern Singleton)
class Adapost {
private:
    string numeAdapost;
    Adresa adresa;
    vector<unique_ptr<Animal>> animale; // Utilizare STL `vector`
    vector<shared_ptr<Angajat>> angajati; // Utilizarea smart pointer `shared_ptr`

    // Constructor privat pentru Singleton
    Adapost() : numeAdapost(""), adresa(Adresa()) {}

public:
    Adapost(const Adapost&) = delete;
    Adapost& operator=(const Adapost&) = delete;

    static Adapost& getInstance() {
        static Adapost instance;
        return instance;
    }

    void adaugaAnimal(unique_ptr<Animal> animal) {
        animale.push_back(move(animal));
    }

    void adaugaAngajat(shared_ptr<Angajat> angajat) {
        angajati.push_back(move(angajat));
    }

    double salariuMediuAngajati() const {
        if (angajati.empty()) {
            throw Exceptie_sal("Nu avem angajati.");
        }
        double totalSalarii = accumulate(angajati.begin(), angajati.end(), 0.0, // Utilizare STL `accumulate`
            [](double suma, const shared_ptr<Angajat>& angajat) {
                return suma + angajat->getSalariu();
            });
        return totalSalarii / angajati.size();
    }

    void afisareInformatii() const {
        cout << "Nume adapost: " << numeAdapost << endl;
        cout << "Adresa: " << adresa << endl;
        cout << "Animale:" << endl;
        for (const auto& animal : animale) {
            cout << " - " << *animal << endl;
        }
        cout << "Angajati:" << endl;
        for (const auto& angajat : angajati) {
            cout << " - " << *angajat << " (" << angajat->getTip() << ", " << angajat->getRol() << ")" << endl;
        }
        cout << "Salariu mediu al angajatilor: " << salariuMediuAngajati() << endl;
    }

    void setNumeAdapost(const string& nume) {
        numeAdapost = nume;
    }

    void setAdresa(const Adresa& adr) {
        adresa = adr;
    }
};

int main() {
    // Initializare Adresa
    Adresa adresa("Strada Principala", "Bucuresti", "12345");

    // Singleton pentru Adapost
    Adapost& adapost = Adapost::getInstance();
    adapost.setNumeAdapost("Adapostul 1");
    adapost.setAdresa(adresa);

    // Utilizare Factory Method pentru crearea animalelor
    adapost.adaugaAnimal(AnimalFactory::createAnimal("Caine", "Max", "Caine", 2.5));
    adapost.adaugaAnimal(AnimalFactory::createAnimal("Pisica", "Zizi", "Pisica", 1.8));

    // Adăugare angajați folosind shared_ptr
    adapost.adaugaAngajat(make_shared<Veterinar>("Ionut", 2000.0));
    adapost.adaugaAngajat(make_shared<Receptionist>("Mihai", 3000.0));

    // Crearea inventarului de cuști și mâncare
    Inventar<Cusca> inventarCusti;
    inventarCusti.adaugaItem("C01", Cusca("C01", 2));
    inventarCusti.adaugaItem("C02", Cusca("C02", 3));

    Inventar<Mancare> inventarMancare;
    inventarMancare.adaugaItem("Hrana caini", Mancare("Hrana caini", 50.0));
    inventarMancare.adaugaItem("Hrana pisici", Mancare("Hrana pisici", 30.0));

    // Afisare informatii despre adapost
    try {
        adapost.afisareInformatii();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Afisare inventar cuști
    cout << "Inventar Cuști:" << endl;
    cout << inventarCusti << endl;

    // Afisare inventar mâncare
    cout << "Inventar Mâncare:" << endl;
    cout << inventarMancare << endl;

    // Calcul hrana totală
    vector<unique_ptr<Animal>> animale; // Utilizarea smart pointer `unique_ptr`
    animale.push_back(AnimalFactory::createAnimal("Caine", "Max", "Caine", 2.5));
    animale.push_back(AnimalFactory::createAnimal("Pisica", "Zizi", "Pisica", 1.8));
    cout << "Hrana totala: " << calculeazaHranaTotala(animale) << " kg" << endl;

    return 0;
}
