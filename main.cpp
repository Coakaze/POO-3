#include <iostream>
#include <fstream>
using namespace std;

struct Pair
{
    int nr;
    int poz;
};

class Vector
{
    int *v;
    int n;
public:
    Vector(int nr, int n);
    Vector(int *v, int n);
    Vector(const Vector &vCopie);
    ~Vector();
    void actualizare(int nrNou, int nNou);
    int sum();
    Pair maxim();
    void sortare();
    Vector& operator = (const Vector &vCopie);
    int operator * (const Vector v2);
    friend ostream& operator << (ostream& out, Vector v2);
};

Vector::Vector(int nr, int n)
{
    v = new int[n];
    this->n = n;
    for(int i=0; i<n; i++)
        v[i] = nr;
}

Vector::Vector(int *v, int n)
{
    this->n = n;
    this->v = new int[n];
    for(int i=0; i<n; i++)
        this->v[i] = v[i];
}

Vector::Vector(const Vector &vCopie)
{
    n = vCopie.n;
    v = new int[n];
    for(int i=0; i<n; i++)
        v[i] = vCopie.v[i];
}

Vector::~Vector()
{
    n = 0;
    delete [] v;
}

void Vector::actualizare(int nrNou, int nNou)
{
    delete [] v;
    n = nNou;
    v = new int[n];
    for(int i=0; i<n; i++)
        v[i] = nrNou;
}

int Vector::sum()
{
    int sum = 0;
    for(int i=0; i<n; i++)
        sum += v[i];
    return sum;
}

Pair Vector::maxim()
{
    Pair maxim;
    maxim.nr = v[0];
    for(int i=0; i<n; i++)
        if(v[i] > maxim.nr)
        {
            maxim.nr = v[i];
            maxim.poz = i + 1;
        }
    return maxim;
}

void Vector::sortare()
{
    int aux;
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
}

Vector& Vector::operator = (const Vector &vCopie)
{
    if(this == &vCopie)
        return *this;
    delete [] v;
    n = vCopie.n;
    v = new int[n];
    for(int i=0; i<n; i++)
        v[i] = vCopie.v[i];
    return *this;
}

int Vector::operator * (const Vector v2)
{
    if(n != v2.n)
        return 0;
    int pScalar = 0;
    for(int i=0; i<n; i++)
        pScalar += v[i] * v2.v[i];
    return pScalar;
}

ostream& operator<<(ostream& out, Vector v2)
{
    for(int i=0; i<v2.n; i++)
        out<<v2.v[i]<<" ";
    return out;
}

int main()
{
    ifstream f("date.in");
    int *v, n;
    f>>n;
    v = new int[n];
    for(int i=0; i<n; i++)
        f>>v[i];
    Vector v1(2,10);                                                  ///constructor pentru initializarea cu un numar dat pe toate componentele
    Vector v2(v1);                                                    ///constructor de copiere
    Vector v3(v, n);                                                  ///constructor de initializare cu un vector citit
    v1 = v3;                                                          ///metoda-operator public de atribuire =
    cout<<"v1: "<<v1<<'\n';
    cout<<"v2: "<<v2<<'\n';
    cout<<"v3: "<<v3<<'\n';
    v1.actualizare(5, 8);                                             ///metoda pentru reactualizare
    cout<<"v1 dupa actualizare: "<<v1<<'\n';
    int suma_v3 = v3.sum();
    cout<<"suma elementelor din v3: "<<suma_v3<<'\n';                 ///metoda pentru calculul sumei
    int maxim = v3.maxim().nr;                                        ///metoda pentru calculul maximului si pozitiei
    int poz = v3.maxim().poz;
    cout<<"Maximul din v3: "<<maxim<<" pe pozitia: "<<poz<<'\n';
    v3.sortare();                                                     ///metdoda pentru sortare
    cout<<"Vectorul v3 sortat: "<<v3<<'\n';
    cout<<"v1 * v3: "<<v1 * v3<<'\n';
    cout<<"v1 * v2: "<<v1 * v2;
    return 0;
}
