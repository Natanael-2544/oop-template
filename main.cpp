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
                std::cout<<"Angajatul "<<idAngajat<<" a ramas fara energie!";
            }
        }
    public:
        Angajat(const int& energie_=100):
            idAngajat(++idGen), energie(energie_) {}
        int getEnergie()const {return energie;}
        void scadeEnergie(int cost) { consumaEnergie(cost); }
        int getIdAngajat()const {return idAngajat;}
        void resetEnergie() { energie = 100; }
        virtual void servicii()=0;
        virtual ~Angajat()=default;
    };
    int Angajat::idGen=0;

class Receptioner: public Angajat, public CheckInOut {
public:
    Receptioner(): Angajat(){}
    int getCostCheckIn() const { return 20; }
    int getCostCheckOut() const { return 20; }
    void checkIn() override {
        std::cout << "Receptioner " << idAngajat << " face check-in.\n";
        consumaEnergie(getCostCheckIn());
    }
    void checkOut() override {
        std::cout << "Receptioner " << idAngajat << " face check-out.\n";
        consumaEnergie(getCostCheckOut());
    }
    void servicii() override {
        // Receptioner nu face room service
    }
};

class Menajer : public Angajat {
public:
    Menajer() : Angajat() {}
    int getCostServicii() const { return 15; }
    void servicii() override {
        std::cout << "Menajer " << idAngajat << " efectueaza room service/curațenie.\n";
        consumaEnergie(getCostServicii());
    }
};

class Manager : public Angajat, public CheckInOut {
public:
    Manager() : Angajat() {}
    int getCostCheckIn() const { return 5; }
    int getCostCheckOut() const { return 5; }
    void checkIn() override {
        std::cout << "Manager " << idAngajat << " supravegheaza check-in.\n";
        consumaEnergie(getCostCheckIn());
    }
    void checkOut() override {
        std::cout << "Manager " << idAngajat << " supravegheaza check-out.\n";
        consumaEnergie(getCostCheckOut());
    }
    void servicii() override{}
};
    //----------------------------------------------------------------------------
    //Camera factory si Angajat factory

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
    Hotel()=default;
protected:
    std::vector<Camera*> camere;
    std::vector<Angajat*> angajati;
public:
    Hotel(const Hotel&)=delete;
    Hotel& operator=(const Hotel&)=delete;
    static Hotel& getInstance() {
        static Hotel h;
        return h;
    }
    void afisareAngajatiDetaliat();
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
    void afisareCamereDescrescator() {
        if (camere.empty()) {
            std::cout << "Nu exista rezervari.\n";
            return;
        }
        std::vector<Camera*> copie=camere;
        std::sort(copie.begin(), copie.end(), [](Camera* a, Camera* b) {
            return a->calcPret()>b->calcPret();});
        std::cout<<"Camere ordonate descrescator dupa pret:\n";
        for (auto c : copie) {std::cout << *c;}
    }
    std::vector<Angajat*>& getAngajati() { return angajati; }
    std::vector<Camera*>& getCamere() { return camere; }
};

    void afisareOptiuniCamera(int &nopti, bool &micDejun, bool &roomService) {
        std::cout << "Nr nopti: ";
        std::cin >> nopti;
        std::cout << "Mic dejun (1/0)? ";
        std::cin >> micDejun;
        std::cout << "Room service (1/0)? ";
        std::cin >> roomService;
    }

    void Hotel::afisareAngajatiDetaliat() {
        std::cout << "angajati = [";

        for (size_t i = 0; i < angajati.size(); i++) {
            Angajat* a = angajati[i];

            if (dynamic_cast<Receptioner*>(a)) std::cout << "Receptioner";
            else if (dynamic_cast<Menajer*>(a)) std::cout << "Menajer";
            else if (dynamic_cast<Manager*>(a)) std::cout << "Manager";

            std::cout << "(" << a->getEnergie() << ")";

            if (i != angajati.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]\n";
    }

    void meniu() {
        auto &hotel = Hotel::getInstance();
        int optiune;
        while (true) {
            std:: cout<<"Bine ati venit la hotelul nostru! Aveti mai jos ofertele noastre. Cu ce va putem ajuta?";
            std::cout << "\n1. Adauga Single\n2. Adauga Double\n3. Adauga Suite\n4. Afiseaza rezervari\n5. Afiseaza angajati\n6. Afiseaza camere descrescator dupa pret\n0. Iesire\nOptiune: ";
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
                case 6:
                    hotel.afisareCamereDescrescator();
                    break;
                default:
                    std::cout << "Optiune invalida.\n";
            }
        }
    }

    void executaCheck(bool isCheckIn) {
        auto& hotel = Hotel::getInstance();
        bool finalizat = false;
        while (!finalizat) {
            for (auto ang : hotel.getAngajati()) {
                if (auto r = dynamic_cast<Receptioner*>(ang)) {
                    int cost;
                    if (isCheckIn) {
                        cost = r->getCostCheckIn();
                    } else {
                        cost = r->getCostCheckOut();
                    }
                    if (r->getEnergie() >= cost) {
                        if (isCheckIn) r->checkIn();
                        else r->checkOut();
                        finalizat = true;
                        break;
                    } else {
                        // Receptioner fara energie -> adaugam unul nou
                        auto nou = AngajatFactory::creeazaAngajat(1);
                        hotel.adaugaAngajat(nou);
                        std::cout << "S-a adaugat un nou Receptioner.\n";

                        // Folosim imediat noul receptioner (cast la Receptioner*)
                        if (auto rNou = dynamic_cast<Receptioner*>(nou)) {
                            if (isCheckIn) rNou->checkIn();
                            else rNou->checkOut();
                        }
                        finalizat = true;
                        break;
                    }
                }
            }
        }
    }

    void ruleazaZi() {
    auto& hotel = Hotel::getInstance();
    std::cout << "== START ==\n";

    for (auto& c : hotel.getCamere()) {

        // --- CHECK-IN cu receptioner ---
        executaCheck(true);

        // --- ROOM SERVICE cu menajer ---
        if (c->hasRoomService()) {
            bool serviciuFinalizat = false;
            while (!serviciuFinalizat) {
                for (auto ang : hotel.getAngajati()) {
                    if (auto m = dynamic_cast<Menajer*>(ang)) {
                        int cost = m->getCostServicii();
                        if (m->getEnergie() >= cost) {
                            m->servicii();
                            serviciuFinalizat = true;
                            break;
                        } else {
                            auto nou = AngajatFactory::creeazaAngajat(2);
                            hotel.adaugaAngajat(nou);
                            std::cout << "S-a adaugat un nou Menajer.\n";
                            if (auto mNou = dynamic_cast<Menajer*>(nou)) {
                                if (mNou->getEnergie() >= mNou->getCostServicii()) {
                                    mNou->servicii();
                                    serviciuFinalizat = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        // --- CHECK-OUT cu receptioner ---
        executaCheck(false);

        // --- Manager supravegheaza check-in / check-out ---
        for (auto ang : hotel.getAngajati()) {
            if (auto m = dynamic_cast<Manager*>(ang)) {
                if (m->getEnergie() >= m->getCostCheckIn()) {
                    m->checkIn();  // scade 5 energie
                }
                if (m->getEnergie() >= m->getCostCheckOut()) {
                    m->checkOut(); // scade 5 energie
                }
            }
        }

        hotel.afisareAngajatiDetaliat();
        std::cout << "== END ==\n";
    }
}

    int main() {
        auto& Hotel=Hotel::getInstance();
        Hotel.adaugaAngajat(AngajatFactory::creeazaAngajat(1)); // Receptioner
        Hotel.adaugaAngajat(AngajatFactory::creeazaAngajat(2)); // Menajer
        Hotel.adaugaAngajat(AngajatFactory::creeazaAngajat(3)); // Manager

        meniu();
        ruleazaZi(); // afisare vector angajati si comenzi
        return 0;
    }
