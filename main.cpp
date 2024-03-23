#include <iostream>
#include <vector>

using namespace std;

/// Clasele pentru adăpostul de animale

class Adresa {
private:
    string strada;
    string oras;
    string codPostal;

public:
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
private:
    string nume;
    string specie;

public:
    Animal() : nume(""), specie("") {}
    Animal(string nume, string specie) : nume(nume), specie(specie) {}

    /// Getteri și setteri
    string getNume() const { return nume; }
    string getSpecie() const { return specie; }
    void setNume(string newNume) { nume = newNume; }
    void setSpecie(string newSpecie) { specie = newSpecie; }

    friend ostream& operator<<(ostream& out, const Animal& animal) {
        out << "Animal: " << animal.nume << " (" << animal.specie << ")";
        return out;
    }
};

class Angajat {
private:
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

    friend ostream& operator<<(ostream& out, const Angajat& angajat) {
        out << "Angajat: " << angajat.nume << ", Salariu: " << angajat.salariu;
        return out;
    }
};

class Adapost {
private:
    string numeAdapost;
    Adresa adresa;
    vector<Animal> animale;
    vector<Angajat> angajati;

public:
    Adapost() : numeAdapost(""), adresa(Adresa()), animale(vector<Animal>()), angajati(vector<Angajat>()) {}
    Adapost(string numeAdapost, Adresa adresa, vector<Animal> animale, vector<Angajat> angajati)
        : numeAdapost(numeAdapost), adresa(adresa), animale(animale), angajati(angajati) {}

    double salariuMediuAngajati() const {
        if (angajati.empty()) return 0.0;
        double totalSalarii = 0.0;
        for (const auto& angajat : angajati) {
            totalSalarii += angajat.getSalariu();
        }
        return totalSalarii / angajati.size();
    }

    // Afiseaza informatiile despre adapost
    void afisareInformatii() const {
        cout << "Nume adapost: " << numeAdapost << endl;
        cout << "Adresa: " << adresa << endl;
        cout << "Animale:" << endl;
        for (const auto& animal : animale) {
            cout << " - " << animal << endl;
        }
        cout << "Angajati:" << endl;
        for (const auto& angajat : angajati) {
            cout << " - " << angajat << endl;
        }
        cout << "Salariu mediu al angajatilor: " << salariuMediuAngajati() << endl;
    }

    friend ostream& operator<<(ostream& out, const Adapost& adapost) {
        out << "Nume adapost: " << adapost.numeAdapost << endl;
        out << "Adresa: " << adapost.adresa << endl;
        out << "Animale:" << endl;
        for (const auto& animal : adapost.animale) {
            out << " - " << animal << endl;
        }
        out << "Angajati:" << endl;
        for (const auto& angajat : adapost.angajati) {
            out << " - " << angajat << endl;
        }
        out << "Salariu mediu al angajatilor: " << adapost.salariuMediuAngajati() << endl;
        return out;
    }
};

int main() {
    // Initializare Adresa
    Adresa adresa("Strada Principala", "Orasul Mic", "12345");

    // Initializare vector de animale
    vector<Animal> animale;
    animale.push_back(Animal("Max", "Caine"));
    animale.push_back(Animal("Mittens", "Catel"));

    // Initializare vector de angajati
    vector<Angajat> angajati;
    angajati.push_back(Angajat("John Doe", 2000.0));

    // Initializare adapost
    Adapost adapost("Adapostul Meu", adresa, animale, angajati);

    // Afisare informatii despre adapost
    cout << adapost;

    return 0;
}
