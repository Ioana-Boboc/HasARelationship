#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class ExceptieExistentaDenumire {
private:
	string mesaj;
public:
	ExceptieExistentaDenumire(string mesaj) : mesaj(mesaj) {}
	string getMesaj() { return this->mesaj; }
};
struct Data {
	int zi, luna, an;
};
class Ingredient {
private:
	char* denumire;
	float cantitate;
	string unitDeMasura;
	Data dataExpirarii;
public:
	Ingredient() {
		this->denumire = nullptr;
		this->cantitate = 0;
		this->unitDeMasura = "N/A";
		this->dataExpirarii.an = 0;
		this->dataExpirarii.luna = 0;
		this->dataExpirarii.zi = 0;
	}
	Ingredient(const char* denumire, float cantitate, string unitDeMasura, Data dataExpirarii) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		this->cantitate = cantitate;
		this->unitDeMasura = unitDeMasura;
		this->dataExpirarii = dataExpirarii;
	}
	Ingredient(const char* denumire, float cantitate) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else this->denumire = nullptr;
		this->cantitate = cantitate;
		this->unitDeMasura = "N/A";
		this->dataExpirarii.an = 0;
		this->dataExpirarii.luna = 0;
		this->dataExpirarii.zi = 0;
	}
	const char* getDenumire() {
		return this->denumire;
	}
	void setDenumire(const char* denumire) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else this->denumire = nullptr;
	}
	float getCantitate() {
		return this->cantitate;
	}
	void setCantitate(float cantitate) {
		if (cantitate > 0)
			this->cantitate = cantitate;
	}
	string getUnitDeMasura() {
		return this->unitDeMasura;
	}
	void setUnitDeMasura(string unitDeMasura) {
		if (unitDeMasura.length() > 2)
			this->unitDeMasura = unitDeMasura;
	}
	Data getDataExpirarii() {
		return this->dataExpirarii;
	}
	void setDataExpirarii(Data dataExpirarii) {
		if (dataExpirarii.an > 0)
			this->dataExpirarii.an = dataExpirarii.an;
		if (dataExpirarii.luna > 0)
			this->dataExpirarii.luna = dataExpirarii.luna;
		if (dataExpirarii.zi > 0)
			this->dataExpirarii.zi = dataExpirarii.zi;
	}
	Ingredient(const Ingredient& i) {
		if (i.denumire != nullptr) {
			this->denumire = new char[strlen(i.denumire) + 1];
			strcpy(this->denumire, i.denumire);
		}
		else this->denumire = nullptr;
		this->cantitate = i.cantitate;
		this->unitDeMasura = i.unitDeMasura;
		this->dataExpirarii = i.dataExpirarii;
	}
	Ingredient& operator=(const Ingredient& i) {
		if (this != &i) {
			delete[] this->denumire;
			this->denumire = nullptr;

			if (i.denumire != nullptr) {
				this->denumire = new char[strlen(i.denumire) + 1];
				strcpy(this->denumire, i.denumire);
			}
			else this->denumire = nullptr;
			this->cantitate = i.cantitate;
			this->unitDeMasura = i.unitDeMasura;
			this->dataExpirarii = i.dataExpirarii;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Ingredient& i) {
		out << "\n~~~~~~~~~~~~afisare ingredient~~~~~~~~~~~~";
		if (i.denumire != nullptr)
			out << "\nDenumire: " << i.denumire;
		else out << "-";
		out << "\nCantitate: " << i.cantitate;
		out << "\nUnitate de masura: " << i.unitDeMasura;
		out << "\nData expirarii (zi.luna.an): " << i.dataExpirarii.zi << "." << i.dataExpirarii.luna << "." << i.dataExpirarii.an;
		out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		return out;
	}
	friend istream& operator>>(istream& in, Ingredient& i) {
		delete[] i.denumire;
		i.denumire = nullptr;

		cout << "\n____Citire ingredient____";
		cout << "\nIntroduceti denumire: ";
		string buffer;
		in >> buffer;
		i.denumire = new char[buffer.size() + 1];
		strcpy(i.denumire, buffer.data());
		cout << "Introduceti cantitate: ";
		in >> i.cantitate;
		cout << "Introduceti unitate de masura: ";
		in >> i.unitDeMasura;
		cout << "Introduceti ziua expirarii: ";
		in >> i.dataExpirarii.zi;
		cout << "Introduceti luna expirarii: ";
		in >> i.dataExpirarii.luna;
		cout << "Introduceti anul expirarii: ";
		in >> i.dataExpirarii.an;
		cout << "\n__________________________";
		return in;

	}
	Ingredient& operator-(float cantDeRedus) {
		if (cantDeRedus > 0)
			if (this->cantitate - cantDeRedus > 0) {
				this->cantitate -= cantDeRedus;
			}
		return *this;
	}
	bool expirat() {
		// verific daca un produs este expirat la data de 25 decembrie 2023
		if (this->dataExpirarii.an < 2023)
			return 1;
		else if (this->dataExpirarii.an == 2023 && this->dataExpirarii.luna < 12)
			return 1;
		else if (this->dataExpirarii.an == 2023 && this->dataExpirarii.luna == 12 && this->dataExpirarii.zi < 25)
			return 1;
		return 0;
	}
	void adaugaCantitate(float q) {
		if (q > 0)
			this->cantitate += q;
	}
	// preincrementare ++
	Ingredient& operator++() {
		this->cantitate++;
		return *this;
	}
	// postincrementare ++
	Ingredient operator++(int) {
		Ingredient copie = *this;
		this->cantitate++;
		return copie;
	}
	~Ingredient() {
		delete[] this->denumire;
		this->denumire = nullptr;
	}
	friend class Preparat;
	friend class Stoc;
};

class Preparat {
private:
	const int id;
	string denumire;
	int nrIngrediente;
	Ingredient** listaIngrediente;
	float pret;
public:
	Preparat() :id(id) {
		this->denumire = "N/A";
		this->nrIngrediente = 0;
		this->listaIngrediente = nullptr;
		this->pret = 0;
	}
	Preparat(int id, string denumire, int nrIngrediente, Ingredient** listaIngrediente, float pret) :id(id) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		if (nrIngrediente > 0 && listaIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = new Ingredient(*listaIngrediente[i]);
		}
		else {
			this->nrIngrediente = 0;
			this->listaIngrediente = nullptr;
		}
		this->pret = pret;
	}
	Preparat(int id, string denumire) :id(id) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		this->nrIngrediente = 0;
		this->listaIngrediente = nullptr;
		this->pret = 0;
	}
	int getId() {
		return this->id;
	}
	string getDenumire() {
		return this->denumire;
	}
	void setDenumire(string denumire) {
		if (denumire.length() > 3)
			this->denumire = denumire;
	}
	float getPret() {
		return this->pret;
	}
	void setPret(float pret) {
		if (pret > 2.5)
			this->pret = pret;
	}
	void setListaIngrediente(int nrIngrediente, Ingredient** listaIngrediente) {
		for (int i = 0; i < this->nrIngrediente; i++) {
			delete this->listaIngrediente[i];
			this->listaIngrediente[i] = nullptr;
		}
		delete[] this->listaIngrediente;
		this->listaIngrediente = nullptr;

		if (nrIngrediente > 0 && listaIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = new Ingredient(*listaIngrediente[i]);
		}
	}
	Preparat(const Preparat& p) :id(p.id) {
		if (p.denumire.length() > 0)
			this->denumire = p.denumire;
		if (p.nrIngrediente > 0 && p.listaIngrediente != nullptr) {
			this->nrIngrediente = p.nrIngrediente;
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = new Ingredient(*p.listaIngrediente[i]);
		}
		else {
			this->nrIngrediente = 0;
			this->listaIngrediente = nullptr;
		}
		this->pret = p.pret;
	}
	Preparat& operator=(const Preparat& p) {
		if (this != &p) {
			for (int i = 0; i < this->nrIngrediente; i++) {
				delete this->listaIngrediente[i];
				this->listaIngrediente[i] = nullptr;
			}
			delete[] this->listaIngrediente;
			this->listaIngrediente = nullptr;

			if (p.denumire.length() > 0)
				this->denumire = p.denumire;
			if (p.nrIngrediente > 0 && p.listaIngrediente != nullptr) {
				this->nrIngrediente = p.nrIngrediente;
				this->listaIngrediente = new Ingredient * [this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++)
					this->listaIngrediente[i] = new Ingredient(*p.listaIngrediente[i]);
			}
			else {
				this->nrIngrediente = 0;
				this->listaIngrediente = nullptr;
			}
			this->pret = p.pret;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Preparat& p) {
		out << "\n~~~~~~~~~~~~afisare preparat~~~~~~~~~~~~";
		out << "\nId: " << p.id;
		out << "\nDenumire: " << p.denumire;
		out << "\nNumar ingrediente: " << p.nrIngrediente;
		if (p.nrIngrediente > 0) {
			out << "\nLista ingredintelor: ";
			for (int i = 0; i < p.nrIngrediente; i++)
				out << *p.listaIngrediente[i];
		}
		else {
			out << "\nLista ingredientelor: " << "-";
		}
		out << "\nPret: " << p.pret;
		out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		return out;
	}
	friend istream& operator>>(istream& in, Preparat& p) {
		for (int i = 0; i < p.nrIngrediente; i++) {
			delete p.listaIngrediente[i];
			p.listaIngrediente[i] = nullptr;
		}
		delete[] p.listaIngrediente;
		p.listaIngrediente = nullptr;

		cout << "\n____Citire preparat____";
		cout << "\nIntroduceti denumire: ";
		in >> p.denumire;
		cout << "Introduceti numar ingrediente: ";
		in >> p.nrIngrediente;
		if (p.nrIngrediente > 0) {
			p.listaIngrediente = new Ingredient * [p.nrIngrediente];
			cout << "Introduceti lista ingrediente: ";
			for (int i = 0; i < p.nrIngrediente; i++) {
				p.listaIngrediente[i] = new Ingredient();
				in >> *p.listaIngrediente[i];
			}
		}
		else {
			p.listaIngrediente = nullptr;
		}
		cout << "\nIntroduceti pret: ";
		in >> p.pret;
		cout << "\n______________________";
		return in;
	}
	void modificaPret(float pretNou) {
		if (pretNou > 0)
			this->pret = pretNou;
	}
	void adaugaIngredient(Ingredient& i, float pretInPlus) {
		Ingredient** copieListaIngr = new Ingredient * [this->nrIngrediente + 1];
		for (int i = 0; i < this->nrIngrediente; i++) {
			copieListaIngr[i] = new Ingredient(*this->listaIngrediente[i]);
		}
		copieListaIngr[this->nrIngrediente] = new Ingredient(i);
		delete[] this->listaIngrediente;
		this->nrIngrediente++;
		this->listaIngrediente = copieListaIngr;
		this->pret += pretInPlus;
	}
	bool operator<(const Preparat& p) {
		if (this->pret != 0 && p.pret != 0)
			if (this->pret < p.pret)
				return true;
			else return false;
		else throw ExceptieExistentaDenumire("nu poate fi facuta aceasta comparatie!");
	}
	explicit operator float() {
		return this->pret;
	}
	~Preparat() {
		for (int i = 0; i < this->nrIngrediente; i++) {
			delete this->listaIngrediente[i];
			this->listaIngrediente[i] = nullptr;
		}
		delete[] this->listaIngrediente;
		this->listaIngrediente = nullptr;
	}
	friend class Meniu;
	friend class Comanda;
};

class Stoc {
private:
	int nrIngrediente;
	Ingredient** listaIngrediente;
public:
	Stoc(int nrIngrediente, Ingredient** listaIngrediente) {
		if (nrIngrediente > 0 && listaIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = new Ingredient(*listaIngrediente[i]);
		}
		else {
			this->nrIngrediente = 0;
			this->listaIngrediente = nullptr;
		}
	}
	Stoc() {
		this->nrIngrediente = 0;
		this->listaIngrediente = nullptr;
	}
	void setListaIngrediente(int nrIngrediente, Ingredient** listaIngrediente) {
		for (int i = 0; i < this->nrIngrediente; i++) {
			delete this->listaIngrediente[i];
			this->listaIngrediente[i] = nullptr;
		}
		delete[] this->listaIngrediente;
		this->listaIngrediente = nullptr;

		if (this->nrIngrediente > 0 && this->listaIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = new Ingredient(*listaIngrediente[i]);
		}
	}
	Stoc(const Stoc& s) {
		if (s.nrIngrediente > 0 && s.listaIngrediente != nullptr) {
			this->nrIngrediente = s.nrIngrediente;
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = new Ingredient(*s.listaIngrediente[i]);
		}
		else {
			this->nrIngrediente = 0;
			this->listaIngrediente = nullptr;
		}
	}
	Stoc& operator=(const Stoc& s) {
		if (this != &s) {
			for (int i = 0; i < this->nrIngrediente; i++) {
				delete this->listaIngrediente[i];
				this->listaIngrediente[i] = nullptr;
			}
			delete[] this->listaIngrediente;
			this->listaIngrediente = nullptr;

			if (s.nrIngrediente > 0 && s.listaIngrediente != nullptr) {
				this->nrIngrediente = s.nrIngrediente;
				this->listaIngrediente = new Ingredient * [this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++)
					this->listaIngrediente[i] = new Ingredient(*s.listaIngrediente[i]);
			}
			else {
				this->nrIngrediente = 0;
				this->listaIngrediente = nullptr;
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Stoc& s) {
		out << "\n~~~~~~~~~~~~afisare stoc~~~~~~~~~~~~";
		out << "\nNumar ingrediente: " << s.nrIngrediente;
		if (s.nrIngrediente > 0) {
			out << "\nLista ingredintelor: ";
			for (int i = 0; i < s.nrIngrediente; i++)
				out << *s.listaIngrediente[i];
		}
		else {
			out << "\nLista ingredientelor: " << "-";
		}
		out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		return out;
	}
	friend istream& operator>>(istream& in, Stoc& s) {
		for (int i = 0; i < s.nrIngrediente; i++) {
			delete s.listaIngrediente[i];
			s.listaIngrediente[i] = nullptr;
		}
		delete[] s.listaIngrediente;
		s.listaIngrediente = nullptr;

		cout << "\n____Citire stoc____";
		cout << "\nIntroduceti numar ingrediente: ";
		in >> s.nrIngrediente;
		if (s.nrIngrediente > 0) {
			s.listaIngrediente = new Ingredient * [s.nrIngrediente];
			cout << "Introduceti lista ingrediente: ";
			for (int i = 0; i < s.nrIngrediente; i++) {
				s.listaIngrediente[i] = new Ingredient();
				in >> *s.listaIngrediente[i];
			}
		}
		else {
			s.listaIngrediente = nullptr;
		}
		cout << "\n___________________";
		return in;
	}
	bool existaIngrediente() {
		if (this->nrIngrediente > 0 && this->listaIngrediente != nullptr)
			return true;
		else return false;
	}
	void cateIngredienteInStoc() {
		cout << "\nIn stoc exista " << this->nrIngrediente << " ingrediente.";
	}
	~Stoc() {
		for (int i = 0; i < this->nrIngrediente; i++) {
			delete this->listaIngrediente[i];
			this->listaIngrediente[i] = nullptr;
		}
		delete[] this->listaIngrediente;
		this->listaIngrediente = nullptr;
	}
	friend class Comanda;
};

class Meniu {
private:
	int nrPreparate;
	Preparat** listaPreparate;
public:
	Meniu() {
		this->nrPreparate = 0;
		this->listaPreparate = nullptr;
	}
	Meniu(int nrPreparate, Preparat** listaPreparate) {
		if (nrPreparate > 0 && listaPreparate != nullptr) {
			this->nrPreparate = nrPreparate;
			this->listaPreparate = new Preparat * [this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->listaPreparate[i] = new Preparat(*listaPreparate[i]);
		}
		else {
			this->nrPreparate = 0;
			this->listaPreparate = nullptr;
		}
	}
	void setListaPreparate(int nrPreparate, Preparat** listaPreparate) {
		for (int i = 0; i < this->nrPreparate; i++) {
			delete this->listaPreparate[i];
			this->listaPreparate[i] = nullptr;
		}
		delete[] this->listaPreparate;
		this->listaPreparate = nullptr;

		if (nrPreparate > 0 && listaPreparate != nullptr) {
			this->nrPreparate = nrPreparate;
			this->listaPreparate = new Preparat * [this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->listaPreparate[i] = new Preparat(*listaPreparate[i]);
		}
	}
	Meniu(const Meniu& m) {
		if (m.nrPreparate > 0 && m.listaPreparate != nullptr) {
			this->nrPreparate = m.nrPreparate;
			this->listaPreparate = new Preparat * [this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->listaPreparate[i] = new Preparat(*m.listaPreparate[i]);
		}
		else {
			this->nrPreparate = 0;
			this->listaPreparate = nullptr;
		}
	}
	Meniu& operator=(const Meniu& m) {
		if (this != &m) {
			for (int i = 0; i < this->nrPreparate; i++) {
				delete this->listaPreparate[i];
				this->listaPreparate[i] = nullptr;
			}
			delete[] this->listaPreparate;
			this->listaPreparate = nullptr;

			if (m.nrPreparate > 0 && m.listaPreparate != nullptr) {
				this->nrPreparate = m.nrPreparate;
				this->listaPreparate = new Preparat * [this->nrPreparate];
				for (int i = 0; i < this->nrPreparate; i++)
					this->listaPreparate[i] = new Preparat(*m.listaPreparate[i]);
			}
			else {
				this->nrPreparate = 0;
				this->listaPreparate = nullptr;
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Meniu& m) {
		out << "\n~~~~~~~~~~~~afisare meniu~~~~~~~~~~~~";
		out << "\nNumar preparate: " << m.nrPreparate;
		if (m.nrPreparate > 0) {
			out << "\nLista preparatelor: ";
			for (int i = 0; i < m.nrPreparate; i++)
				out << *m.listaPreparate[i];
		}
		else {
			out << "\nLista preparatelor: " << "-";
		}
		out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		return out;
	}
	friend istream& operator>>(istream& in, Meniu& m) {
		for (int i = 0; i < m.nrPreparate; i++) {
			delete m.listaPreparate[i];
			m.listaPreparate[i] = nullptr;
		}
		delete[] m.listaPreparate;
		m.listaPreparate = nullptr;

		cout << "\n____Citire meniu____";
		cout << "\nIntroduceti numar preparate: ";
		in >> m.nrPreparate;
		if (m.nrPreparate > 0) {
			m.listaPreparate = new Preparat * [m.nrPreparate];
			cout << "Introduceti lista preparate: ";
			for (int i = 0; i < m.nrPreparate; i++) {
				m.listaPreparate[i] = new Preparat();
				in >> *m.listaPreparate[i];
			}
		}
		else {
			m.listaPreparate = nullptr;
		}
		cout << "\n____________________";
		return in;
	}
	int operator[](int pozitie) {
		if (pozitie >= 0 && pozitie <= this->nrPreparate)
			if (this->listaPreparate != nullptr)
				return this->listaPreparate[pozitie]->getId();
	}
	void afisareNrPreparate() {
		cout << "\nNr preparatelor din meniu este: " << this->nrPreparate;
	}
	void afisareaIdurilorPreparatelorDinMeniu() {
		if (this->nrPreparate != 0 && this->listaPreparate != nullptr) {
			cout << "\nId-urile preparatelor disponibile in meniu: ";
			for (int i = 0; i < this->nrPreparate; i++)
				cout << "\nAl " << i + 1 << "-lea preparat are Id - ul: " << this->listaPreparate[i]->getId();
		}
	}
	~Meniu() {

		for (int i = 0; i < this->nrPreparate; i++) {
			delete this->listaPreparate[i];
			this->listaPreparate[i] = nullptr;
		}
		delete[] this->listaPreparate;
		this->listaPreparate = nullptr;

	}
	friend class Comanda;
};

class Comanda {
private:
	const int id;
	Meniu m;
	int nrPreparate;
	int* listaPreparate;
	bool achitare;
	// 0- cash  1- card
public:
	Comanda(int id, Meniu m, int nrPreparate, int* listaPreparate, bool achitare) : id(id) {
		this->m = m;
		if (nrPreparate > 0 && listaPreparate != nullptr) {
			this->nrPreparate = nrPreparate;
			this->listaPreparate = new int[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->listaPreparate[i] = listaPreparate[i];
		}
		else {
			this->nrPreparate = 0;
			this->listaPreparate = nullptr;
		}
		this->achitare = achitare;
	}
	Comanda(int id, bool achitare) :id(id) {
		this->nrPreparate = 0;
		this->listaPreparate = nullptr;
		this->achitare = achitare;
	}
	int getId() {
		return this->id;
	}
	bool getAchitare() {
		return this->achitare;
	}
	void setAchitare(bool achitare) {
		if (achitare == 0 || achitare == 1)
			this->achitare = achitare;
	}
	void setPreparate(int nrPreparate, int* listaPreparate) {
		delete[] this->listaPreparate;
		this->listaPreparate = nullptr;

		if (nrPreparate > 0 && listaPreparate != nullptr) {
			this->nrPreparate = nrPreparate;
			this->listaPreparate = new int[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->listaPreparate[i] = listaPreparate[i];
		}
	}
	Comanda(const Comanda& c) :id(c.id) {
		this->m = c.m;
		if (c.nrPreparate > 0 && c.listaPreparate != nullptr) {
			this->nrPreparate = c.nrPreparate;
			this->listaPreparate = new int[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->listaPreparate[i] = c.listaPreparate[i];
		}
		else {
			this->nrPreparate = 0;
			this->listaPreparate = nullptr;
		}
		this->achitare = c.achitare;
	}
	Comanda& operator=(const Comanda& c) {
		if (this != &c) {
			delete[] this->listaPreparate;
			this->listaPreparate = nullptr;

			this->m = c.m;
			if (c.nrPreparate > 0 && c.listaPreparate != nullptr) {
				this->nrPreparate = c.nrPreparate;
				this->listaPreparate = new int[this->nrPreparate];
				for (int i = 0; i < this->nrPreparate; i++)
					this->listaPreparate[i] = c.listaPreparate[i];
			}
			else {
				this->nrPreparate = 0;
				this->listaPreparate = nullptr;
			}
			this->achitare = c.achitare;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Comanda& c) {
		out << "\n~~~~~~~~~~~~afisare comanda~~~~~~~~~~~~";
		out << "\nId comanda: " << c.id;
		out << "\nMeniul disponibil este: " << c.m;
		out << "\nNumar preparate comandate: " << c.nrPreparate;
		out << "\nId-urile lor sunt: ";
		if (c.nrPreparate > 0) {
			for (int i = 0; i < c.nrPreparate; i++)
				out << c.listaPreparate[i] << " ";
		}
		else out << "-";

		out << "\nAchitare (0-cash 1-card): " << c.achitare;
		out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		return out;
	}
	friend istream& operator>>(istream& in, Comanda& c) {
		delete[] c.listaPreparate;
		c.listaPreparate = nullptr;

		cout << "\n____Citire comanda____";
		/*cout << "\nIntroduceti meniu: ";
		in >> c.m;*/
		cout << "\nIntroduceti numar preparate comandate: ";
		in >> c.nrPreparate;
		cout << "Introduceti id-urile preparatelor: ";
		if (c.nrPreparate > 0) {
			c.listaPreparate = new int[c.nrPreparate];
			for (int i = 0; i < c.nrPreparate; i++) {
				cout << "\nAl " << i + 1 << "-lea preparat are id ul: ";
				in >> c.listaPreparate[i];
			}
		}
		else {
			c.nrPreparate = 0;
			c.listaPreparate = nullptr;
		}
		cout << "Introduceti modalitatea de achitare (0-cash 1-card): ";
		in >> c.achitare;
		return in;
	}
	/*float pretTotal() {
		float p = 0;
		if(this->nrPreparate!=0 && this->listaPreparate!=nullptr)
			for(int i=0;i<this->nrPreparate;i++)
				for (int j = 0; j < m.nrPreparate; i++) {
					if (this->listaPreparate[i] == m[j])
						p += m.listaPreparate[j]->getPret();
				}
		return p;
	}*/
	bool operator!() {
		return !this->achitare;
	}
	void afisareNrPreparateComandate() {
		cout << "\nNr preparatelor comandate este: " << this->nrPreparate;
	}
	void afisareModalitatePlata() {
		if (this->achitare == 0)
			cout << "\nComanda va fi achitata cash.";
		else cout << "\nComanda va fi achitata cu cardul.";
	}
	~Comanda() {
		delete[] this->listaPreparate;
		this->listaPreparate = nullptr;
	}
};

class Restaurant {
private:
	char* denumire;
	static int nrMinimSalariati;
public:
	Restaurant() {
		this->denumire = nullptr;
	}
	Restaurant(const char* denumire) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else this->denumire = nullptr;
	}
	const char* getDenumire() {
		return this->denumire;
	}
	void setDenumire(const char* denumire) {
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else this->denumire = nullptr;
	}
	int getNrMinimSalariati() {
		return Restaurant::nrMinimSalariati;
	}
	static void setNrMinimSalariati(int nrAng) {
		if (nrAng >= 1)
			Restaurant::nrMinimSalariati = nrAng;
	}
	Restaurant(const Restaurant& r) {
		if (r.denumire != nullptr) {
			this->denumire = new char[strlen(r.denumire) + 1];
			strcpy(this->denumire, r.denumire);
		}
		else this->denumire = nullptr;
	}
	Restaurant& operator=(const Restaurant& r) {
		if (this != &r) {
			delete[] this->denumire;
			this->denumire = nullptr;

			if (r.denumire != nullptr) {
				this->denumire = new char[strlen(r.denumire) + 1];
				strcpy(this->denumire, r.denumire);
			}
			else this->denumire = nullptr;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Restaurant& r) {
		out << "\n~~~~~~~~~~~~afisare restaurant~~~~~~~~~~~~";
		if (r.denumire != nullptr)
			out << "\nDenumire: " << r.denumire;
		else out << "\n-";
		out << "\nNumarul angajatilor: " << Restaurant::nrMinimSalariati;
		out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		return out;
	}
	friend istream& operator>>(istream& in, Restaurant& r) {
		delete[] r.denumire;
		r.denumire = nullptr;

		cout << "\n____Citire restaurant____";
		cout << "\nIntroduceti denumire: ";
		string buffer;
		in >> buffer;
		r.denumire = new char[buffer.size() + 1];
		strcpy(r.denumire, buffer.data());
		cout << "Introduceti nr angajati(>=1): ";
		int nr;
		in >> nr;
		Restaurant::setNrMinimSalariati(nr);
		return in;
	}
	bool operator==(const char* denumire) {
		if (this->denumire != nullptr && denumire != nullptr) {
			return strcmp(this->denumire, denumire) == 0;
		}
		return false;
	}
	void afisareNrSalariati() {
		cout << "\nNr salariati: " << Restaurant::getNrMinimSalariati();
	}
	void afisareDenumire() {
		cout << "\nDenumirea localului: " << this->denumire;
	}
	~Restaurant() {
		delete[] this->denumire;
		this->denumire = nullptr;
	}
};

int Restaurant::nrMinimSalariati = 1;
int main() {
	// supraincarcarea operatorului >> este comentata pentru rularea intregului program, ea poate fi decomentata pentru orice clasa din solutie
	Data dataExp = { 10,06,2024 };
	Data dataExp2 = { 30,12,2023 };

	cout << "\n-------------------VERIFICARI PT INGREDIENT-------------------";
	Ingredient i1("faina", 1000, "kg", dataExp);
	cout << i1;

	Ingredient i15("salata", 200);
	cout << i15;
	Ingredient i16 = i15;
	cout << i16;
	Ingredient i17("utdugv", 865);
	i17 = i1;
	cout << i17;
	cout << "\nnoul i17";
	// op -
	i17 = i17 - 15;
	cout << i17;
	cout << endl << i1.getDenumire() << " " << i1.getCantitate() << " " << i1.getUnitDeMasura();
	i17.setDenumire("piper");
	i17.setCantitate(10);
	i17.setUnitDeMasura("kg");
	cout << i17;
	/*cin >> i4;
	cout << i4;*/
	i1.adaugaCantitate(15);
	cout << "\nCantitatea din i1 este: " << i1.getCantitate();
	cout << "\nEste produsul " << i1.getDenumire() << " expirat? 1-da 0-nu: " << i1.expirat();

	Ingredient i2("ou", 500, "bucata", dataExp2);
	Ingredient i3("sare", 1000, "kg", dataExp);
	Ingredient i4("aluat", 100, "bucata", dataExp);
	Ingredient i5("sos", 15, "litru", dataExp);
	Ingredient i6("sunca", 5, "kg", dataExp2);
	Ingredient i7("mozzarella", 5, "kg", dataExp2);
	Ingredient i8("porumb", 10, "conserva", dataExp);
	Ingredient i9("ciuperci", 100, "bucata", dataExp);
	Ingredient i10("zahar", 1000, "kg", dataExp);
	Ingredient i11("apa", 10000, "litru", dataExp);
	Ingredient i12("suc", 300, "litru", dataExp);
	Ingredient i13("topping", 20, "kg", dataExp);
	Ingredient i14("lapte", 150, "litru", dataExp2);

	// op ++ ambele forme
	cout << endl << "Preincrementare i12: " << i12.operator++();
	cout << endl << "Postincrementare i12: " << i12.operator++(4);
	cout << i12;

	//cout << i2 << i3 << i4 << i5 << i6 << i7 << i8 << i9 << i10 << i11 << i12<<i13; 
	cout << "\n-------------------VERIFICARI PT PREPARAT-------------------";
	Ingredient* ingrediente[] = { &i1, &i2, &i14, &i3, &i10 };
	Preparat p1(20, "Clatite", 5, ingrediente, 16);
	cout << p1;
	cout << endl << p1.getId();
	Preparat p2(10, "Paine");
	//cout << p2;
	p2 = p1;
	cout << p2;
	Preparat p3(15, "Paine");
	//cin >> p3;
	cout << p3;
	p3.modificaPret(8);
	cout << p3;
	p2.adaugaIngredient(i13, 5);
	cout << p2;
	// op <
	try {
		if (p1 < p2)
			cout << "\nPrimul preparat este mai ieftin.";
		else cout << "\nAl doilea preparat este mai ieftin.";
	}
	catch (ExceptieExistentaDenumire ex) {
		cout << endl << ex.getMesaj();
	}
	Ingredient* ingrediente4[] = { &i4, &i5, &i6, &i7, &i8, &i9 };
	Preparat p4(10, "Pizza", 6, ingrediente4, 35);
	cout << p4;
	cout << endl << p4.getDenumire();
	float pretul = (float)p4;
	cout << "\nPizza are pretul: " << pretul;

	cout << "\n-------------------VERIFICARI PT STOC-------------------";
	Stoc s(5, ingrediente);
	cout << s;
	cout << "\nExista ingrediente in stoc? 0-nu 1-da: " << s.existaIngrediente();
	s.cateIngredienteInStoc();

	cout << "\n-------------------VERIFICARI PT MENIU-------------------";
	Preparat* preparate[] = { &p1,&p4 };
	Meniu m(2, preparate);
	cout << m;
	// op []
	cout << "\nId-ul primului preparat: " << m[0];
	m.afisareNrPreparate();
	m.afisareaIdurilorPreparatelorDinMeniu();

	cout << "\n-------------------VERIFICARI PT COMANDA-------------------";
	int prep1[] = { 20, 1 };
	// constructor cu toti param 
	Comanda c1(1, m, 2, prep1, 0);
	cout << c1;
	// op !
	cout << "\nClientii NU doresc sa achite (0-cash 1-card): " << !c1;
	//cout << "\nPRETUL TOTAL AL COMENZII ESTE: " << c1.pretTotal();
	// constructor cu 2 param 
	Comanda c2(2, 1);
	cout << c2;
	// op = 
	c2 = c1;
	cout << c2;
	// constructor de copiere 
	Comanda c3(c1);
	cout << c3;
	// op>> + op<<
	Comanda c4(4, 0);
	//cin >> c4;
	cout << c4;
	int prep2[] = { 10 };
	c2.setPreparate(1, prep2);
	c2.setAchitare(1);
	cout << c2;
	c1.afisareNrPreparateComandate();
	c1.afisareModalitatePlata();
	cout << "\n-------------------VERIFICARI PT RESTAURANT-------------------";
	Restaurant r1;
	r1.setNrMinimSalariati(20);
	cout << r1;
	Restaurant r2(r1);
	cout << r2;
	Restaurant r3("Mama");
	cout << endl << r3.getDenumire();
	Restaurant r4;
	cin >> r4;
	cout << r4;
	// op ==
	const char* numeRestaurant = "Mama";
	bool acelasiNume = (r4 == numeRestaurant);
	cout << "\nAu aceeasi denumire restaurantele r3 si r4? 0-nu 1-da: " << acelasiNume;
	r4.afisareDenumire();
	r4.afisareNrSalariati();
	return 0;
}