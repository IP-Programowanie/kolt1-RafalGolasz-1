#include "Wybor.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszcza� pomi�dzy #ifdef a #endif.
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

class W�a�ciciel
{

};

class Samoch�d
{
protected:
	char numerRej[50];
	int stanLicznika;
	dopuszczenie dop;
	W�a�ciciel* w�;
	static Samoch�d* instWzor;
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

	/*void setW�a�ciciel(W�a�ciciel* w)
	{
		this->w� = w;
	}

	W�a�ciciel* getW�a�ciciel()
	{
		return w�;
	}*/

	static void setInstancjaWzorcowa(Samoch�d* instancjaWz)
	{
		instWzor = instancjaWz;
	}

	Samoch�d(const char* numRej, int stanLicz, dopuszczenie d, W�a�ciciel* w)
	{
		strcpy_s(numerRej, numRej);
		setStanLicznika(stanLicz);
		dop = d;
		w� = w;
	}

	Samoch�d()
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
			throw invalid_argument("samoch�d nie jest dopuszczony do jazdy!");
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

	bool operator!=(const Samoch�d& a)
	{
		return (dop != a.dop || abs(stanLicznika - a.stanLicznika) > 20);
	}
};

Samoch�d* Samoch�d::instWzor = nullptr;

class Samoch�dElektryczny : public Samoch�d
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

	Samoch�dElektryczny(int stanBat, const char* numRej, int stanLicz, dopuszczenie d, W�a�ciciel* w)
		: Samoch�d(numRej, stanLicz, d, w)
	{
		setStanBaterii(stanBat);
	}

	double zasieg() override
	{
		if (getDopuszczenie() == dopuszczenie::niedopuszczony)
		{
			throw invalid_argument("samoch�d nie jest dopuszczony do jazdy!");
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
	W�a�ciciel* w1 = NULL;
	W�a�ciciel* w2 = NULL;

	Samoch�d s1("ADA3425", 1000, dopuszczenie::dopuszczony, w1);
	Samoch�d s4("OKI4747", 1030, dopuszczenie::dopuszczony, w2);
	Samoch�d s2("Essa224", 125, dopuszczenie::niedopuszczony, w1);

	Samoch�d::setInstancjaWzorcowa(&s2);


	Samoch�dElektryczny s3(75, "EOP1234", 500, dopuszczenie::dopuszczony, w2);

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
