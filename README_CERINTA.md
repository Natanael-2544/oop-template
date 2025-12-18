# **Cerință proiect C++: Simulator Hotel**

Organizația **Q&V Hotels** dorește să își extindă domeniul de activitate deschizând un hotel. Pentru a eficientiza operațiunile, aceștia doresc să implementeze o aplicație.

Aplicația va permite gestionarea camerelor și rezervărilor clienților. Fiecare rezervare are un **identificator unic**, un client și o cameră selectată. Fiecare cameră are un **tip** (Single, Double, Suite), un **preț pe noapte** și un număr de nopți rezervate. Clienții au un nume și preferințe (ex: etaj, vedere la mare).

---

### **Valori implicite și reguli de preț**
- **Preț standard pe noapte pentru Single:** 100
- **Double:** 150% din prețul Single dacă are vedere la mare; altfel 120%
- **Suite:** 250% din prețul Single dacă are vedere la mare; altfel 200%
- **Room service:** 50/unitate/zi
- Dacă la final mizeria este mare, consumul de energie al menajerilor crește cu +20

---

### **Valori implicite și energie angajați**
- Toți angajații încep cu **100 puncte energie** la începutul fiecărui ciclu
- **Tipuri de angajați și energie consumată:**
    - **Receptioner:** 25 energie pentru check-in
    - **Menajer:** 25 energie pentru room service/curățenie
    - **Manager:** 5 energie per cameră ocupată

---

### **Simulator**
Simulatorul rulează pe baza unui **ciclu** cu următoarele etape:

1. **Check-in:** angajații ocupă camerele clienților
    - Fiecare angajat poate prelua un client pe ciclu
    - Managerul consumă 5 energie pentru fiecare cameră ocupată

2. **Servicii:** room service, curățenie
    - Angajații își consumă energia conform tipului și sarcinilor

3. **Check-out:** finalizare șederii și calcularea costului total
    - Cost total = preț cameră (calculat după tip și procente) + room service

---

### **Funcționalități**
- Afișarea numărului de angajați pentru fiecare tip
- Crearea și gestionarea camerelor și rezervărilor
- Simularea unui ciclu complet (check-in, servicii, check-out)
- Posibilitatea de a selecta rezervări **prioritare**
- Strategii de procesare a rezervărilor: FIFO, cea mai scumpă, cea mai ieftină  
