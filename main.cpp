#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string>

//Clasa Camera: Single, Double, Suite
class Camera {
    static int idGenerator;
protected:
    int id;
    int nrNopti;
    int pretNoapte;
    bool micDejun;
    bool roomService;
    double calcPretBaza() const {
        double pret = pretNoapte;
        if (micDejun) {pret += 20;}
        if (roomService) {pret += 5;}
        return pret * nrNopti;
    }
public:
    Camera(const int& nrNopti_, const int& pretNoapte_=100, bool micDejun_=false, bool roomService_=false):
    id(++idGenerator), nrNopti(nrNopti_), pretNoapte(pretNoapte_), micDejun(micDejun_), roomService(roomService_) {}
    int getId()const{ return id;}

    virtual double calcPret()=0;
    virtual void afisare(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Camera& c) {
        c.afisare(out);
        return out;
    }
    bool hasRoomService() const { return roomService; }
    int getNopti() const { return nrNopti; }
    virtual ~ Camera()=default;
};
int Camera::idGenerator = 0;

class Single: public Camera {
public:
    Single(const int& nrNopti_, bool micDejun_ = false, bool roomService_=false):
         Camera(nrNopti_, 100, micDejun_, roomService_) {}

    double calcPret() const {
        return calcPretBaza();
    }
    void afisare(std::ostream& out) const override {
        out<< "Single ID:" << id << " Nopti:" << nrNopti
                  << " MicDejun:" << micDejun << " RoomService:" << roomService
                  << " Pret:" << calcPret() << "\n";
    }
};

class Double: public Camera {
    bool vedereMare;
    public:
    Double(const int& nrNopti_,  bool micDejun_ = false, bool roomService_=false, bool vedereMare_ = false)
        : Camera(nrNopti_, 100 * 1.25, micDejun_, roomService_), vedereMare(vedereMare_) {}

    double calcPret() const {
        double pret = calcPretBaza();
        if (vedereMare) pret += 5 * nrNopti;
        return pret;
    }
    void afisare(std::ostream& out) const override {
        out<< "Double ID:" << id << " Nopti:" << nrNopti
                  << " MicDejun:" << micDejun << " RoomService:" << roomService
                  << " VedereMare:" << vedereMare
                  << " Pret:" << calcPret() << "\n";
    }
};

class Suite: public Camera {
    bool vedereMare;
    bool minibar;
public:
    Suite(const int& nrNopti_, bool micDejun_ = false, bool roomService_=false, bool vedereMare_ = false, bool minibar_ = false)
        : Camera(nrNopti_, 100 * 1.5, micDejun_, roomService_), vedereMare(vedereMare_), minibar(minibar_) {}

    double calcPret() const {
        double pret = calcPretBaza();
        if (vedereMare) pret += 10 * nrNopti;
        if (minibar) pret += 5 * nrNopti;
        return pret;
    }
    void afisare(std::ostream& out) const override {
        out<< "Suite ID:" << id << " Nopti:" << nrNopti
                  << " MicDejun:" << micDejun << " RoomService:" << roomService
                  << " VedereMare:" << vedereMare << " Minibar:" << minibar
                  << " Pret:" << calcPret() << "\n";
    }
};
//----------------------------------------------------------------------------
//Clasa Angajat

class CheckInOut {
public:
    virtual void checkIn(int camareOcupate) = 0;
    virtual void checkOut(int camareOcupate) = 0;
    virtual ~CheckInOut() {}
};

class Angajat {
    static int idGen;
protected:
    int idAngajat;
    int energie;
    void consumaEnergie(int cost) {
        energie -= cost;
        if (energie < 0) {
            std::cout<<"Angajatul "<<idAngajat<<" a rămas fără energie!";
        }
    }
public:
    Angajat(const int& energie_=100):
        idAngajat(++idGen), energie(energie_) {}
    int getEnergie()const {return energie;}
    int getIdAngajat()const {return idAngajat;}
    void resetEnergie() { energie = 100; }
    virtual void servicii()=0;
    virtual ~Angajat()=default;
};
int Angajat::idGen=0;

class Receptioner: public Angajat, public CheckInOut {
public:
    Receptioner(): Angajat(){}
    void checkIn(int camereOcupate) override {
        std::cout << "Receptioner " << idAngajat << " face check-in.\n";
        consumaEnergie(25);
    }
    void checkOut(int camereOcupate) override {
        std::cout << "Receptioner " << idAngajat << " face check-out.\n";
        consumaEnergie(25);
    }
    void servicii() override {
        // Receptioner nu face room service
    }
};

class Menajer : public Angajat {
public:
    Menajer() : Angajat() {}
    void servicii() override {
        std::cout << "Menajer " << idAngajat << " efectuează room service/curățenie.\n";
        consumaEnergie(15);
    }
};

class Manager : public Angajat, public CheckInOut {
public:
    Manager() : Angajat() {}
    void checkIn(int camereOcupate) override {
        std::cout << "Manager " << idAngajat << " supraveghează check-in.\n";
        consumaEnergie(5 * camereOcupate);
    }
    void checkOut( int camereOcupate ) override {
        std::cout << "Manager " << idAngajat << " supraveghează check-out.\n";
        consumaEnergie(5 * camereOcupate);
    }
};

//----------------------------------------------------------------------------
class Hotel {
    std::vector<Camera*> camere;
    std::vector<Angajat*> angajati;
    Hotel()=default;
public:
    Hotel(const Hotel&)=delete;
    Hotel& operator=(const Hotel&)=delete;
    static Hotel& getInstance() {
        static Hotel h;
        return h;
    }

    void adaugaCamera(Camera *c) {
        camere.push_back(c);
    }
    void adaugaAngajat(Angajat* a) {
        angajati.push_back(a);
    }
    void afisareAngajati() {
        int recep=0, menajer=0, manager=0;
        for (auto a: angajati) {
            if (dynamic_cast<Receptioner*>(a)){ recep++;}
            if (dynamic_cast<Menajer*>(a)){ menajer++;}
            if (dynamic_cast<Manager*>(a)){ manager++;}
        }
        std::cout << "Receptioneri:" << recep << " Menajeri:" << menajer << " Manageri:" << manager << "\n";
    }

    void afisareRezervari() {

    }
};

int afisare() {
    int x;
    std::cout << "1.Adauga Single"<<" ";
    std::cout<<"2.Adauga Double"<<" ";
    std::cout<<"3.Adauga Suite"<<" ";
    std::cout << "4.Upgrade element ";
    std::cout << "5.Afiseaza camere ";
    std::cout << "\nOptiune: ";
    std::cin >> x;
    return x;
}

void loop() {
    int optiune;
    while (true) {
        //afisareaMeniu();
        std::cin >> optiune;
        switch (optiune) {
            //case 1:
            //etc.
        }
    }
}
int main() {
    auto& x=Hotel::getInstance();
    return 0;
}
