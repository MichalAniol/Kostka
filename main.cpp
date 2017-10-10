#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;

// zmienne:
int szerokosc = 70, wysokosc = 30 ;              // proporce ekranu aby był kwadratowy : 81 do 41 = 1.97561
    string wiersz = "0123456789012345678901234567890123456789"
                    "012345678901234567890123456789" ;      // !!! string musi miec dlugosc "szerokosci" !!!
    char * adres_wiersza = &wiersz[0] ;
int ilosc_kostek = 3 ;

// funkcje:
void wyswietlacz (char * ekran) ;
void wyswietlacz2 (char * ekran) ;
void linia (int x1, int y1, int x2, int y2, char * pole) ;

/********************** M A I N *****************************/

int main()
{

    char pole[wysokosc][szerokosc];                                                //stworzenie pola
    char * pamiec_pola = &pole[0][0] ;
    for (int i = 0 ; i < (wysokosc * szerokosc) ; i++) *(pamiec_pola + i) = ' ' ;   //clear pole

    float kont_a = 45 * M_PI / 180 ,                                                //współżedne wyświetlania
          kont_b = 66 * M_PI / 180 ,
          kont_c = 23 * M_PI / 180 ,
          rada = M_PI / 180 ;

    float przesow_x = 0, przesow_y = -800, przesow_z = 0 ,
        zoom = 1, rzutnia = 50 ;

    int punkt_x[3][8], punkt_y[3][8] ;

    int kos_x[3][8], kos_y[3][8], kos_z[3][8] ;

    for (int i = 0 ; i < ilosc_kostek ; i++)                                                    //obiekt kostka - wierzcholki
    {
        int nr = 0 ;
        int x, y ;
        switch (i)
        {
            case 0 : x = 0 ; y = 0 ; break ;
            case 1 : x = 130 ; y = 130 ; break ;
            case 2 : x = -130 ; y = -130 ; break ;
        }
        kos_x[i][nr] =  50 + x ; kos_y[i][nr] =  50 + y ; kos_z[i][nr] =  50 ; nr++ ;
        kos_x[i][nr] = -50 + x ; kos_y[i][nr] =  50 + y ; kos_z[i][nr] =  50 ; nr++ ;
        kos_x[i][nr] = -50 + x ; kos_y[i][nr] = -50 + y ; kos_z[i][nr] =  50 ; nr++ ;
        kos_x[i][nr] =  50 + x ; kos_y[i][nr] = -50 + y ; kos_z[i][nr] =  50 ; nr++ ;
        kos_x[i][nr] =  50 + x ; kos_y[i][nr] =  50 + y ; kos_z[i][nr] = -50 ; nr++ ;
        kos_x[i][nr] = -50 + x ; kos_y[i][nr] =  50 + y ; kos_z[i][nr] = -50 ; nr++ ;
        kos_x[i][nr] = -50 + x ; kos_y[i][nr] = -50 + y ; kos_z[i][nr] = -50 ; nr++ ;
        kos_x[i][nr] =  50 + x ; kos_y[i][nr] = -50 + y ; kos_z[i][nr] = -50 ; nr++ ;
    }

    int licznik = 0 ;

    for ( ; ; )
    {

        kont_a += .64 * rada ; if (kont_a > M_PI * 2) kont_a -= M_PI * 2 ;      //ruch kostki
        kont_b += .321 * rada ; if (kont_b > M_PI * 2) kont_b -= M_PI * 2;
        kont_c += .18 * rada ; if (kont_c > M_PI * 2) kont_c -= M_PI * 2 ;
        zoom += sin( (licznik / 3) * rada) / 104  ;
        licznik++ ; if (licznik > 360 * 3) licznik = 0 ;

    for (int i = 0 ; i < ilosc_kostek ; i++)
    {
        for (int q = 0 ; q < 8 ; q++)
        {
        punkt_x[i][q] = (szerokosc / 2) + zoom * (-((cos(kont_c) * (cos(kont_b) * (kos_x[i][q]) - sin(kont_b) *
                     (sin(kont_a) * kos_y[i][q] + cos(kont_a) * kos_z[i][q])) - sin(kont_c) * (cos(kont_a) * kos_y[i][q] -
                     sin(kont_a) * kos_z[i][q])) + przesow_x) / ((sin(kont_c) * (cos(kont_b) * (kos_x[i][q]) -
                     sin(kont_b) * (sin(kont_a) * kos_y[i][q] + cos(kont_a) * kos_z[i][q])) + cos(kont_c) *
                     (cos(kont_a) * kos_y[i][q] - sin(kont_a) * kos_z[i][q])) + przesow_y) * rzutnia) * 1.97561 ;

        punkt_y[i][q] = (wysokosc / 2) - zoom * (-((sin(kont_b) * (kos_x[i][q]) + cos(kont_b) * (sin(kont_a) *
                     kos_y[i][q] + cos(kont_a) * kos_z[i][q])) + przesow_z) / ((sin(kont_c) * (cos(kont_b) *
                     (kos_x[i][q]) - sin(kont_b) * (sin(kont_a) * kos_y[i][q] + cos(kont_a) * kos_z[i][q])) +
                     cos(kont_c) * (cos(kont_a) * kos_y[i][q] - sin(kont_a) * kos_z[i][q])) + przesow_y) * rzutnia) ;

/***************************** WZOR NIESROCONY ************
            float x1, x2, x3, y1, y2, y3 , z1, z2, z3, x4, y4, z4,
            viz1, viz2 ;

        x1 = kos_x[i][q] ;     //obrot wokol osi X
        y1 = cos(kont_a) * kos_y[i][q] - sin(kont_a) * kos_z[i][q] ;
        z1 = sin(kont_a) * kos_y[i][q] + cos(kont_a) * kos_z[i][q] ;

        x2 = cos(kont_b) * x1 - sin(kont_b) * z1 ; //wokol Y
        y2 = y1 ;
        z2 = sin(kont_b) * x1 + cos(kont_b) * z1 ;

        x3 = cos(kont_c) * x2 - sin(kont_c) * y2 ; //wool Z
        y3 = sin(kont_c) * x2 + cos(kont_c) * y2 ;
        z3 = z2 ;

        x4 = x3 + przesow_x ;    //przesuniencie
        y4 = y3 + przesow_y ;
        z4 = z3 + przesow_z ;

        viz1 = -x4 / y4 * rzutnia ;     //rzutowanie
        viz2 = -z4 / y4 * rzutnia ;

        punkt_x[i][q] = (szerokosc / 2) + zoom * viz1 * 1.97561 ;   //punkty ekranu
        punkt_y[i][q] = (wysokosc / 2) - zoom * viz2 ;*/
        }
    }

    for (int i = 0 ; i < ilosc_kostek ; i++)
    {
        linia(punkt_x[i][0], punkt_y[i][0], punkt_x[i][1], punkt_y[i][1], pamiec_pola) ;        //kreslenie
        linia(punkt_x[i][1], punkt_y[i][1], punkt_x[i][2], punkt_y[i][2], pamiec_pola) ;        //kreslenie
        linia(punkt_x[i][2], punkt_y[i][2], punkt_x[i][3], punkt_y[i][3], pamiec_pola) ;        //kreslenie
        linia(punkt_x[i][3], punkt_y[i][3], punkt_x[i][0], punkt_y[i][0], pamiec_pola) ;        //kreslenie

        linia(punkt_x[i][0], punkt_y[i][0], punkt_x[i][4], punkt_y[i][4], pamiec_pola) ;        //kreslenie
        linia(punkt_x[i][4], punkt_y[i][4], punkt_x[i][5], punkt_y[i][5], pamiec_pola) ;        //kreslenie
        linia(punkt_x[i][5], punkt_y[i][5], punkt_x[i][6], punkt_y[i][6], pamiec_pola) ;        //kreslenie
        linia(punkt_x[i][6], punkt_y[i][6], punkt_x[i][7], punkt_y[i][7], pamiec_pola) ;        //kreslenie

        linia(punkt_x[i][7], punkt_y[i][7], punkt_x[i][4], punkt_y[i][4], pamiec_pola) ;        //kreslenie
        linia(punkt_x[i][1], punkt_y[i][1], punkt_x[i][5], punkt_y[i][5], pamiec_pola) ;        //kreslenie
        linia(punkt_x[i][2], punkt_y[i][2], punkt_x[i][6], punkt_y[i][6], pamiec_pola) ;        //kreslenie
        linia(punkt_x[i][3], punkt_y[i][3], punkt_x[i][7], punkt_y[i][7], pamiec_pola) ;        //kreslenie
    }

    wyswietlacz (pamiec_pola) ;

    for (int i = 0 ; i < (wysokosc * szerokosc) ; i++) *(pamiec_pola + i) = ' ' ;   //clear pole
    }

}

/***********************************************************/

void wyswietlacz (char * pole)
{
    char * adres_popmocniczy ;
    COORD c ; c.X = 0 ; c.Y = 0 ;                                            //powrót na gore ekranu
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c ) ;

    for (int i = 0 ; i < wysokosc ; i++)                                    //wypisanie ekranu
    {
        adres_popmocniczy = adres_wiersza ;
        for (int q = 0 ; q < szerokosc ; q++)
        {
            *adres_popmocniczy++ = *pole++ ;
        }
        cout << wiersz << endl ;
    }
}

/*********/

void linia (int x1, int y1, int x2, int y2, char * pole)
{

    float dlugosc_linii_x = x1 - x2 ;
    float dlugosc_linii_y = y1 - y2 ;
    float iloczyn_dlugosci = x1 * y2 - x2 * y1 ;
                                                        //czy linia przecina ekran
    if(x1 < 0 && x2 < 0 ) return ;
    if(x1 > szerokosc && x2 > szerokosc ) return ;
    if(y1 < 0 && y2 < 0 ) return ;
    if(y1 > wysokosc && y2 > wysokosc ) return ;
    if(x1 == x2 && y1 == y2) return ;

    if (x1 < 0) { y1 = iloczyn_dlugosci / dlugosc_linii_x ; x1 = 0 ; }  //z lewej
    if (x2 < 0) { y2 = iloczyn_dlugosci / dlugosc_linii_x ; x2 = 0 ; }

    if (x1 > szerokosc) { y1 = (szerokosc * dlugosc_linii_y + iloczyn_dlugosci) / dlugosc_linii_x ; x1 = szerokosc ; }  //z prawej
    if (x2 > szerokosc) { y2 = (szerokosc * dlugosc_linii_y + iloczyn_dlugosci) / dlugosc_linii_x ; x2 = szerokosc ; }

    if (y1 > wysokosc) { x1 = (wysokosc * dlugosc_linii_x - iloczyn_dlugosci) / dlugosc_linii_y ; y1 = wysokosc ; }  //z gory
    if (y2 > wysokosc) { x2 = (wysokosc * dlugosc_linii_x - iloczyn_dlugosci) / dlugosc_linii_y ; y2 = wysokosc ; }

    if (y1 < 0) { x1 = (-iloczyn_dlugosci) / dlugosc_linii_y ; y1 = 0 ; }  //z dolu
    if (y2 < 0) { x2 = (-iloczyn_dlugosci) / dlugosc_linii_y ; y2 = 0 ; }


    dlugosc_linii_x = x2 - x1 ;                                         //ponowne obliczenie dlugosci lini po obcieciu
    dlugosc_linii_y = y2 - y1 ;

    if (dlugosc_linii_x == 0) return ;
    if (dlugosc_linii_y == 0) return ;

    int krok, znak_x = 1, znak_y = 1 ;                                  //dlugosc lini w punktach

    if (dlugosc_linii_x < 0 ) { int pomocnicza = dlugosc_linii_x - (2 * dlugosc_linii_x) ; dlugosc_linii_x = pomocnicza ; znak_x = -1 ; }
    if (dlugosc_linii_y < 0 ) { int pomocnicza = dlugosc_linii_y - (2 * dlugosc_linii_y) ; dlugosc_linii_y = pomocnicza ; znak_y = -1 ; }
    (dlugosc_linii_x > dlugosc_linii_y) ? krok = dlugosc_linii_x : krok = dlugosc_linii_y ;

    if (krok)
    {
        if (krok < 0) { int pom = krok - (2 * krok) ; krok = pom ; }


        float krok_x = dlugosc_linii_x / krok ;                         //rysowanie linii
        float krok_y = dlugosc_linii_y / krok ;
        for (int i = 0 ; i < krok ; i++)
        {
            int x, y ;
            x = x1 + (i * krok_x * znak_x) ;
            y = y1 + (i * krok_y * znak_y) ;
            *(pole + x + (y * szerokosc)  ) = char(178) ;
        }
    }
}


