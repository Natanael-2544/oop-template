#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string>

#include "Hotel.h"
#include "CameraFactory.h"
#include "AngajatFactory.h"
#include "Single.h"
#include "Double.h"
#include "Suite.h"
#include "Receptioner.h"
#include "Menajer.h"
#include "Manager.h"



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

    void executaCheck(bool isCheckIn, Camera *c) {
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
                        if (isCheckIn) r->checkIn(c);
                        else r->checkOut(c);
                        finalizat = true;
                        break;
                    } else {
                        // Receptioner fara energie -> adaugam unul nou
                        auto nou = AngajatFactory::creeazaAngajat(1);
                        hotel.adaugaAngajat(nou);
                        std::cout << "S-a adaugat un nou Receptioner.\n";

                        // Folosim imediat noul receptioner (cast la Receptioner*)
                        if (auto rNou = dynamic_cast<Receptioner*>(nou)) {
                            if (isCheckIn) rNou->checkIn(c);
                            else rNou->checkOut(c);
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
        std::vector<Camera*> camereSortate = hotel.getCamere();
        std::sort(camereSortate.begin(), camereSortate.end(),
                  [](Camera* a, Camera* b) { return a->calcPret() > b->calcPret(); });

        for (auto& c : camereSortate) {
            // CHECK-IN cu receptioner
            executaCheck(true, c);

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
        executaCheck(false, c);

        // --- Manager supravegheaza check-in / check-out ---
        for (auto ang : hotel.getAngajati()) {
            if (auto m = dynamic_cast<Manager*>(ang)) {
                if (m->getEnergie() >= m->getCostCheckIn()) {
                    m->checkIn(c);  // scade 5 energie
                }
                if (m->getEnergie() >= m->getCostCheckOut()) {
                    m->checkOut(c); // scade 5 energie
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
