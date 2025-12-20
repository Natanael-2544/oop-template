# **Cerință proiect C++: Simulator Hotel**

Organizația **Q&V Hotels** dorește să implementeze un simulator pentru gestionarea unui hotel, folosind concepte OOP în C++.

Aplicația modelează **camerele hotelului** și **angajații**, precum și consumul de resurse (energie) în timpul unui ciclu de funcționare.

---

## **Camere**

Fiecare cameră are:
- un **ID unic** (generat automat)
- un **număr de nopți**
- un **preț pe noapte**
- opțiuni:
    - mic dejun
    - room service

### **Tipuri de camere**
- **Single**
- **Double**
- **Suite**

### **Reguli de preț**
- **Single**
    - preț bază: `100 / noapte`
- **Double**
    - preț bază: `125 / noapte`
    - opțional: vedere la mare → `+10 / noapte`
- **Suite**
    - preț bază: `150 / noapte`
    - opțional:
        - vedere la mare → `+10 / noapte`
        - minibar → `+5 / noapte`

### **Costuri suplimentare**
- mic dejun: `+20 / noapte`
- room service: `+5 / noapte`

Prețul total al unei camere este:



---

## **Angajați**

Fiecare angajat are:
- un **ID unic**
- **100 puncte energie** la început
- consum de energie în funcție de activitate

### **Tipuri de angajați**
- **Receptioner**
- **Menajer**
- **Manager**

### **Consum energie**
- **Receptioner**
    - check-in: `25 energie`
    - check-out: `25 energie`
- **Menajer**
    - curățenie / room service: `15 energie`
- **Manager**
    - check-in / check-out: `5 energie × număr camere ocupate`

Dacă energia unui angajat scade sub `0`, se afișează un mesaj de avertizare.

---

## **Scop**
Aplicația permite:

- Afișarea numărului de angajați pentru fiecare tip în parte
- Implementarea simulării și afișarea unui ciclu (sub orice formă)
- Crearea unei opțiuni ca între cicluri să poți selecta comenzi care sunt prioritare și ar trebui să fie terminate primele
- Optimizarea ciclului (se va prioritiza ca fiecare angajat să își facă rolul; vezi exemplu pentru varianta neoptimizată)
- Posibilitatea de a selecta strategia de alegere a comenzilor care sunt procesate (de exemplu FIFO, comanda cea mai „grea” prima, comanda cea mai ușoară prima)
- Rezervări
- Afisarea clientilor dupa pretul total in oridnea descrescatoare 
- Prioritizarea sa se faca dupa clientul cu cel mai mai pret
