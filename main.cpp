#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
#define IMIE_NIEZDEFINIOWANE "##BRAK_PARTNERA"
#define LICZBA_WCIEC 0

struct Tdziecko;
struct Tpara
{
    string imie_pierwszej_osoby;
    string imie_drugiej_osoby;
    Tdziecko* dziecko;
};
struct Tdziecko
{
    Tdziecko* rodzenstwo;
    Tpara* para;
};

void dodaj_dziecko(Tpara* glowa, string* imie_rodzica, string* imie_dziecka);
Tpara* znajdz_pare_o_danym_imieniu(Tpara* para, string* imie_rodzica);
void nowa_para(Tdziecko*& dziecko, string* imie_dziecka);
void nowe_rodzenstwo(Tdziecko*& dziecko);
void drukuj_drzewo(Tpara* para, int liczba_wciec);
void nowy_malzonek(Tpara*& para, string* imie_rodzica, string* imie_malzonka);
void menu();
void zmien_imie(Tpara* para, string* stare_imie);
void drukuj_dzieci(Tpara* para, string* imie_pary);
void drukuj_wnuki(Tpara* para, string* imie_pary);

int main()
{
    Tpara* pierwsza_para = new Tpara;
    Tdziecko* dziecko;
    string pom1;
    string pom2;
    string* imie1;
    string* imie2;


    int x;
    cout << "Podaj imie pierwszej osoby w rodzinie(glowy rodziny):" << endl;
    cin >> pom1;
    imie1 = &pom1;
    if (pierwsza_para) {
        pierwsza_para->imie_pierwszej_osoby = pom1;
        pierwsza_para->imie_drugiej_osoby = IMIE_NIEZDEFINIOWANE;
        pierwsza_para->dziecko = NULL;
    }
    while (1) {
        menu();
        cin >> x;
        switch (x) {
        case 1: {
            cout << "Wpisz imie rodzica" << endl;
            cin >> pom1;
            cout << "Wpisz imie dziecka" << endl;
            cin >> pom2;
            imie1 = &pom1;
            imie2 = &pom2;
            dodaj_dziecko(pierwsza_para, imie1, imie2);
            break;
        }
        case 2: {
            cout << "Wpisz imie osoby wychodzacej za maz" << endl;
            cin >> pom1;
            cout << "Wpisz imie malzonka" << endl;
            cin >> pom2;
            imie1 = &pom1;
            imie2 = &pom2;
            nowy_malzonek(pierwsza_para, imie1, imie2);
            break;
        }
        case 3: {
            drukuj_drzewo(pierwsza_para, LICZBA_WCIEC);
            break;
        }
        case 4: {
            cout << "Podaj jedno z imion pary, w ktorej chcesz edytowac imie" << endl;
            cin >> pom1;
            imie1 = &pom1;
            zmien_imie(pierwsza_para, imie1);
            break;
        }
        case 5: {
            int h;
            cout << "Podaj jedno z imion pary, z ktorej chcesz wypisac dzieci lub wnuki" << endl;
            cin >> pom1;
            cout << "Wybierz 1 aby wypisac imiona dzieci, wybierz 2 aby wypisac imiona wnukow:" << endl;
            cin >> h;
            imie1 = &pom1;
            if (h == 1) drukuj_dzieci(pierwsza_para, imie1);
            if (h == 2) drukuj_wnuki(pierwsza_para, imie1);
            break;
        }
        }
    }
}
void dodaj_dziecko(Tpara* glowa, string* imie_rodzica, string* imie_dziecka)
{
    Tpara* szukany_wezel;
    szukany_wezel = znajdz_pare_o_danym_imieniu(glowa, imie_rodzica); //jakas tam para i chuj
    if (szukany_wezel) {
        Tdziecko* dziecko = szukany_wezel->dziecko;
        Tdziecko* pomocnicze_dziecko = dziecko;
        while (dziecko != NULL)
        {
            if (dziecko->para == NULL)
            {
                nowa_para(dziecko, imie_dziecka);
                return;
            }
            if (dziecko->rodzenstwo == NULL)
                pomocnicze_dziecko = dziecko;
            dziecko = dziecko->rodzenstwo;
        }
        if (pomocnicze_dziecko == NULL)
        {
            nowe_rodzenstwo(szukany_wezel->dziecko);
            nowa_para(szukany_wezel->dziecko, imie_dziecka);
        }
        else
        {
            nowe_rodzenstwo(pomocnicze_dziecko->rodzenstwo);
            nowa_para(pomocnicze_dziecko->rodzenstwo, imie_dziecka);
        }
    }
    else cout << "Nie ma osoby o takim imieniu" << endl;
}
void zmien_imie(Tpara* para, string* stare_imie) {
    Tpara* nowe_imie = new Tpara;
    int wybor;
    cout << "Chcesz zmienic imie pierwszej czy drugiej osoby?" << endl;
    cin >> wybor;
    cout << "Podaj nowe imie" << endl;
    cin >> nowe_imie->imie_pierwszej_osoby;
    nowe_imie->imie_drugiej_osoby = nowe_imie->imie_pierwszej_osoby;
    if (wybor == 1) {
        znajdz_pare_o_danym_imieniu(para, stare_imie)->imie_pierwszej_osoby = nowe_imie->imie_pierwszej_osoby;
    }
    if (wybor == 2) {
        znajdz_pare_o_danym_imieniu(para, stare_imie)->imie_drugiej_osoby = nowe_imie->imie_drugiej_osoby;
    }
}
void drukuj_drzewo(Tpara* para, int liczba_wciec) {
    Tdziecko* dziecko = para->dziecko;
    for (int i = 0; i < liczba_wciec; i++) {
        cout << "\t";
    }
    if (liczba_wciec != 0) {
        cout << "|" << endl;
    }
    for (int i = 0; i < liczba_wciec; i++) {
        cout << "\t";
    }
    if (liczba_wciec != 0) {
        cout << setw(4) << " --- ";
    }
    cout << para->imie_pierwszej_osoby << " + " << para->imie_drugiej_osoby << endl;
    while (dziecko != NULL)
    {
        drukuj_drzewo(dziecko->para, liczba_wciec + 1);
        dziecko = dziecko->rodzenstwo;
    }
}
void drukuj_dzieci(Tpara* para, string* imie_pary) {
    Tpara* tymczasowa_para;
    tymczasowa_para = znajdz_pare_o_danym_imieniu(para, imie_pary);
    Tdziecko* dziecko = new Tdziecko;
    dziecko = tymczasowa_para->dziecko;
    while (dziecko != NULL) {
        cout << dziecko->para->imie_pierwszej_osoby << endl;
        dziecko = dziecko->rodzenstwo;
    }
    cout << endl;

}
void drukuj_wnuki(Tpara* para, string* imie_pary) {
    Tpara* tymczasowa_para;
    tymczasowa_para = znajdz_pare_o_danym_imieniu(para, imie_pary);
    Tdziecko* dziecko = new Tdziecko;
    Tdziecko* wnuk = new Tdziecko;
    dziecko = tymczasowa_para->dziecko;
    while (dziecko != NULL) {
        wnuk = dziecko->para->dziecko;
        while (wnuk != NULL) {
            cout << wnuk->para->imie_pierwszej_osoby << endl;
            wnuk = wnuk->rodzenstwo;
        }
        dziecko = dziecko->rodzenstwo;
    }
    cout << endl;
}
Tpara* znajdz_pare_o_danym_imieniu(Tpara* para, string* imie_rodzica)
{
    Tdziecko* dziecko = para->dziecko;
    Tpara* tymczasowa_para;
    if ((para->imie_drugiej_osoby == *imie_rodzica) || (para->imie_pierwszej_osoby == *imie_rodzica))
        return para;
    while (dziecko != NULL)
    {
        tymczasowa_para = znajdz_pare_o_danym_imieniu(dziecko->para, imie_rodzica);
        if (tymczasowa_para != NULL)
            return tymczasowa_para;
        dziecko = dziecko->rodzenstwo;
    }
    return NULL;
}
void nowa_para(Tdziecko*& dziecko, string* imie_dziecka)
{
    dziecko->para = new Tpara;
    dziecko->para->imie_pierwszej_osoby = *imie_dziecka;
    dziecko->para->imie_drugiej_osoby = IMIE_NIEZDEFINIOWANE;
    dziecko->para->dziecko = NULL;
}
void nowe_rodzenstwo(Tdziecko*& dziecko)
{
    dziecko = new Tdziecko;
    dziecko->rodzenstwo = NULL;
}
void nowy_malzonek(Tpara*& para, string* imie_osoby_wychodzacej_za_maz, string* imie_malzonka) {
    Tpara* szukany_wezel;
    szukany_wezel = znajdz_pare_o_danym_imieniu(para, imie_osoby_wychodzacej_za_maz);
    if (szukany_wezel->imie_drugiej_osoby == IMIE_NIEZDEFINIOWANE)
    {
        szukany_wezel->imie_drugiej_osoby = *imie_malzonka;
    }
    else {
        cout << "Szukana osoba ma juz malzonka" << endl;
    }
}
void menu() {
    cout << "Jezeli chcesz dodac dziecko wpisz 1" << endl;
    cout << "Jezeli chcesz dodac malzonka wpisz 2" << endl;
    cout << "Jezeli chcesz pokazac cale drzewo wpisz 3" << endl;
    cout << "Jezeli chcesz zmienic imie wpisz 4" << endl;
    cout << "Jezeli chcesz wypisac dzieci lub wnuki wpisz 5" << endl;
}
