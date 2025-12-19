#include <iostream>
#include <vector>

class Camera {
    static int idGenerator;
    int id;
protected:
    int nrNopti;
    int pretNoapte;
    bool micDejun;
    double calcPretBaza() const {
        double pret = pretNoapte;
        if (micDejun) pret += 20;
        return pret * nrNopti;
    }
public:
    Camera(const int& nrNopti_, const int& pretNoapte_=100, bool micDejun_=false):
    id(++idGenerator), nrNopti(nrNopti_), pretNoapte(pretNoapte_), micDejun(micDejun_) {}
    int getId()const{ return id;}

    virtual double calcPret()=0;
    virtual void afisare(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Camera& c) {
        c.afisare(out);
        return out;
    }
    virtual ~ Camera();
};
int Camera::idGenerator = 0;

class Single: public Camera {
public:
    Single(const int& nrNopti_, bool micDejun_ = false)
        : Camera(nrNopti_, 100, micDejun_) {}

    void afisare(std::ostream& out) const override {
        out<<" Single: "<< getId()
             << " (NrNopti= " <<nrNopti
             << " MicDejun= " <<micDejun<< ")";
    }
    double calcPret() override {
        return calcPretBaza();}
};

class Double: public Camera {
    bool vedereMare;
    public:
    Double(const int& nrNopti_, bool micDejun_ = false, bool vedereMare_ = false)
        : Camera(nrNopti_, 100 * 1.25, micDejun_), vedereMare(vedereMare_) {}
    void afisare(std::ostream& out) const override {
        out<<" Double: "<< getId()
             << " (NrNopti= " <<nrNopti
             << " MicDejun= " <<micDejun
             <<" VedereMare= " <<vedereMare<< ")";
    }
    double calcPret() override {
        double pret = calcPretBaza();
        if (vedereMare) pret += 5 * nrNopti;
        return pret;
    }
};

class Suite: public Camera {
    bool vedereMare;
    bool minibar;
public:
    Suite(const int& nrNopti_, bool micDejun_ = false, bool vedereMare_ = false, bool minibar_ = false)
        : Camera(nrNopti_, 100 * 1.5, micDejun_), vedereMare(vedereMare_), minibar(minibar_) {}
    void afisare(std::ostream& out) const override {
        out<<" Suite: "<< getId()
             << " (NrNopti= " <<nrNopti
             << " MicDejun= " <<micDejun
             <<" VedereMare= " <<vedereMare
             <<" Minibar= " <<minibar<< ")";
    }
    double calcPret() override {
        double pret = calcPretBaza();
        if (vedereMare) pret += 10 * nrNopti;
        if (minibar) pret += 15 * nrNopti;
        return pret;
    }
};
int main() {

    return 0;
}
