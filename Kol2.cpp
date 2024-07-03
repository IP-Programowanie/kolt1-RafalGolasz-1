#include "Wybor.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczaæ pomiêdzy #ifdef a #endif.
*/

#ifdef Kol_2
#include <iostream>
#include <iomanip>
#pragma warning(disable: 4996)

enum dopuszczenie
{
	dopuszczony,
	niedopuszczony
};

class W³aœciciel
{

};

class Samochód
{
protected:
	char numerRej[50];
	int stanLicznika;
	dopuszczenie dop;
	W³aœciciel* w³;
	static Samochód* instWzor;
public:
	/*void setNumerRej(const char* numerRej)
	{
		strcpy_s(this->numerRej, numerRej);
	}

	const char* getNumerRej()
	{
		return numerRej;
	}*/

	void setStanLicznika(int stanLicz)
	{
		if (stanLicz < 0)
		{
			throw invalid_argument("Stan licznika nie moze byc ujemny!");
		}
		else
		{
			this->stanLicznika = stanLicz;
		}
	}

	int getStanLicznika()
	{
		return stanLicznika;
	}

	/*void setDopuszczenie(dopuszczenie d)
	{
		this->dop = d;
	}*/

	dopuszczenie getDopuszczenie()
	{
		return dop;
	}

	/*void setW³aœciciel(W³aœciciel* w)
	{
		this->w³ = w;
	}

	W³aœciciel* getW³aœciciel()
	{
		return w³;
	}*/

	static void setInstancjaWzorcowa(Samochód* instancjaWz)
	{
		instWzor = instancjaWz;
	}

	Samochód(const char* numRej, int stanLicz, dopuszczenie d, W³aœciciel* w)
	{
		strcpy_s(numerRej, numRej);
		setStanLicznika(stanLicz);
		dop = d;
		w³ = w;
	}

	Samochód()
	{
		if (!instWzor)
		{
			throw runtime_error("Brak instancji wzorcowej!");
		}
		*this = *instWzor;
	}

	virtual double zasieg()
	{
		if (getDopuszczenie() == dopuszczenie::niedopuszczony)
		{
			throw invalid_argument("samochód nie jest dopuszczony do jazdy!");
		}
		else
		{
			return 800.0;
		}
	}

	double WartoscSamochodu()
	{
		double cena = 0;
		double WAR_POCZ = 1000.0;
		if (getDopuszczenie() == dopuszczenie::dopuszczony)
		{
			cena = (WAR_POCZ - 0.2 * getStanLicznika());
		}
		else
		{
			cena = (WAR_POCZ - 0.2 * getStanLicznika()) * 0.2;
		}
		if (cena < 400)
		{
			cena = 400;
		}
		return cena;
	}

	bool operator!=(const Samochód& a)
	{
		return (dop != a.dop || abs(stanLicznika - a.stanLicznika) > 20);
	}
};

Samochód* Samochód::instWzor = nullptr;

class SamochódElektryczny : public Samochód
{
private:
	int stanBaterii;
public:
	void setStanBaterii(int stanBat)
	{
		if (stanBat < 0)
		{
			throw invalid_argument("Stan baterii nie moze byc mniejszy od 0!");
		}
		else
		{
			this->stanBaterii = stanBat;
		}
	}

	int getStanBaterii()
	{
		return stanBaterii;
	}

	SamochódElektryczny(int stanBat, const char* numRej, int stanLicz, dopuszczenie d, W³aœciciel* w)
		: Samochód(numRej, stanLicz, d, w)
	{
		setStanBaterii(stanBat);
	}

	double zasieg() override
	{
		if (getDopuszczenie() == dopuszczenie::niedopuszczony)
		{
			throw invalid_argument("samochód nie jest dopuszczony do jazdy!");
		}
		else
		{
			return 2.5 * stanBaterii;
		}
	}

	double WartoscSamochoduElektrycznego()
	{
		return WartoscSamochodu() * 0.7;
	}
};


int main()
{
	W³aœciciel* w1 = NULL;
	W³aœciciel* w2 = NULL;

	Samochód s1("ADA3425", 1000, dopuszczenie::dopuszczony, w1);
	Samochód s4("OKI4747", 1030, dopuszczenie::dopuszczony, w2);
	Samochód s2("Essa224", 125, dopuszczenie::niedopuszczony, w1);

	Samochód::setInstancjaWzorcowa(&s2);


	SamochódElektryczny s3(75, "EOP1234", 500, dopuszczenie::dopuszczony, w2);

	cout << "Zasieg samochodu elektrycznego: " << s3.zasieg() << endl;

	if (s1 != s4)
	{
		cout << "nie sa takie same!" << endl;
	}
	else
	{
		cout << "sa takie same!" << endl;
	}

	cout << "wartosc auta s1: " << s1.WartoscSamochodu() << endl;
}

#endif
