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

    virtual double calcPret() const =0;
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
    virtual void checkIn() = 0;
    virtual void checkOut() = 0;
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
    void checkIn() override {
        std::cout << "Receptioner " << idAngajat << " face check-in.\n";
        consumaEnergie(25);
    }
    void checkOut() override {
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
    void checkIn() override {
        std::cout << "Manager " << idAngajat << " supraveghează check-in.\n";
        consumaEnergie(25);
    }
    void checkOut() override {
        std::cout << "Manager " << idAngajat << " supraveghează check-out.\n";
        consumaEnergie(25);
    }
    void servicii() override{}
};
//----------------------------------------------------------------------------
//Camera factory si Angajat factoru

class CameraFactory {
public:
    static Camera* creeazaCamera (int tip, int nopti, bool micDejun, bool roomService, bool vedereMare=false, bool minibar=false) {
        switch (tip) {
            case 1: return new Single(nopti, micDejun, roomService);
            case 2: return new Double(nopti, micDejun, roomService, vedereMare);
            case 3: return new Suite(nopti, micDejun, roomService, vedereMare, minibar);
            default: throw std::invalid_argument("Tip camera invalid");
        }
    }
};

class AngajatFactory {
public:
    static Angajat* creeazaAngajat (int tip) {
        switch (tip) {
            case 1: return new Receptioner();
            case 2: return new Menajer();
            case 3: return new Manager();
            default: throw std::invalid_argument("Tip angajat invalid");
        }
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
        if (camere.empty()) {
            std::cout << "Nu exista rezervari.\n";
            return;
        }
        std::cout << "Rezervari hotel:\n";
        for (auto c: camere) {
            std::cout << *c;
        }
    }
};

void afisareOptiuniCamera(int &nopti, bool &micDejun, bool &roomService) {
    std::cout << "Nr nopti: ";
    std::cin >> nopti;
    std::cout << "Mic dejun (1/0)? ";
    std::cin >> micDejun;
    std::cout << "Room service (1/0)? ";
    std::cin >> roomService;
}

void meniu() {
    auto &hotel = Hotel::getInstance();
    int optiune;
    while (true) {
        std::cout << "\n1. Adauga Single\n2. Adauga Double\n3. Adauga Suite\n4. Afiseaza rezervari\n5. Afiseaza angajati\n0. Iesire\nOptiune: ";
        std::cin >> optiune;

        if (optiune==0){ break;}
        int nopti;
        bool micDejun, roomService, vedereMare, minibar;

        switch (optiune) {
            case 1:
                afisareOptiuniCamera(nopti, micDejun, roomService);
                hotel.adaugaCamera(CameraFactory::creeazaCamera(1, nopti, micDejun, roomService));
                break;
            case 2:
                afisareOptiuniCamera(nopti, micDejun, roomService);
                std::cout << "Vedere la mare (1/0)? "; std::cin >> vedereMare;
                hotel.adaugaCamera(CameraFactory::creeazaCamera(2, nopti, micDejun, roomService, vedereMare));
                break;
            case 3:
                afisareOptiuniCamera(nopti, micDejun, roomService);
                std::cout << "Vedere la mare (1/0)? "; std::cin >> vedereMare;
                std::cout << "Minibar (1/0)? "; std::cin >> minibar;
                hotel.adaugaCamera(CameraFactory::creeazaCamera(3, nopti, micDejun, roomService, vedereMare, minibar));
                break;
            case 4:
                hotel.afisareRezervari();
                break;
            case 5:
                hotel.afisareAngajati();
                break;
            default:
                std::cout << "Optiune invalida.\n";
        }
    }
}

int main() {
    auto& Hotel=Hotel::getInstance();
    Hotel.adaugaAngajat(AngajatFactory::creeazaAngajat(1)); // Receptioner
    Hotel.adaugaAngajat(AngajatFactory::creeazaAngajat(2)); // Menajer
    Hotel.adaugaAngajat(AngajatFactory::creeazaAngajat(3)); // Manager

    // Pornim meniul interactiv
    meniu();
    return 0;
}
