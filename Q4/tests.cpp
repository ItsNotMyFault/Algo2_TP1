#include "grandentier.hpp"

#include <assert.h>
#include <iostream>
#include <cmath>

bool
test(const std::string &nom_du_test, const GrandEntier &a, const GrandEntier &b, const GrandEntier &produit_attendu) {
    GrandEntier produit_obtenu = a * b;

    if (produit_obtenu == produit_attendu) {
        std::cout << "Le test " << nom_du_test << " a passe" << std::endl;
        std::cout << "+1 point" << std::endl;
        return true;
    } else {
        std::cout << "a = " << a.toString() << std::endl;
        std::cout << "b = " << b.toString() << std::endl;
        std::cout << "produit attendu = " << produit_attendu.toString() << std::endl;
        std::cout << "produit obtenu =  " << produit_obtenu.toString() << std::endl;
        std::cout << "Le test " << nom_du_test << " a echoue" << std::endl;
        std::cout << "+0 point" << std::endl;
        return false;
    }
}

bool multiplicationParZero() {
    return test("Multiplication par zero",
                GrandEntier(0),
                GrandEntier(42),
                GrandEntier(0));
}

bool multiplicationParUn() {
    return test("Multiplication par un",
                GrandEntier(1),
                GrandEntier(42),
                GrandEntier(42));
}

bool multiplicationSimple() {
    return test("Multiplication simple",
                GrandEntier(3),
                GrandEntier(5),
                GrandEntier(15));
}

bool multiplicationLongue(unsigned int n) {
    std::vector<bool> a(n, false);
    for (unsigned int i = 0; i < n; i += 6) {
        a[i] = true;
    }

    unsigned int m = ((n + 5) / 6) * 6;
    std::vector<bool> produit(m);
    for (unsigned int i = 0; i < m; i++) {
        produit[i] = (i & 1);
    }

    return test("Multiplication longue",
                a,
                GrandEntier(42),
                produit);
}

bool multiplicationVecteursDeUns(unsigned int n, unsigned int m) {
    assert(n > m);
    std::vector<bool> produit(n + m, true);
    produit[n] = false;
    for (unsigned int i = 1; i < m; i++)
        produit[i] = false;

    return test("Multiplication de vecteurs de uns",
                GrandEntier(std::vector<bool>(n, true)),
                GrandEntier(std::vector<bool>(m, true)),
                GrandEntier(produit));
}

#include "cmath"

int main(void) {
//    multiplicationParZero();
//    std::cout << "=========" << std::endl;
//    multiplicationParUn();
//    std::cout << "=========" << std::endl;
//    multiplicationSimple();
//    std::cout << "=========" << std::endl;
//    multiplicationLongue(100); // Pour deboguer, essayez avec la valeur 10 plutot que 100
//    std::cout << "=========" << std::endl;
//    multiplicationVecteursDeUns(200, 70); // Pour deboguer, essayez avec de plus petites valeurs
//    std::cout << "=========" << std::endl;


    test("ARRRRRRRRRRGH",
         GrandEntier(1),
         GrandEntier(6),
         GrandEntier(3));

//    double gg = (1.0/2.0);
//    double ceilResult = ceil(gg);
//    double floorResult = floor(gg);
//
//    double gg2 = (0.5);
//    double ceilResult2 = std::ceil(gg2);
//    double floorResult2 = std::floor(gg2);



//    GrandEntier ff = GrandEntier(6);
//    std::vector<bool> A = ff.m_bits;
//    int m = A.size();
//
//    GrandEntier m1, m2, m3, additionA, additionB, opZ;
//    int half_sizeA = floor(m / 2.0);
//    ///Splits vector A in 2.
//    std::vector<bool> a_Inf(A.begin(), A.begin() + half_sizeA);
//    std::vector<bool> a_Sup(A.begin() + half_sizeA, A.end());
//    GrandEntier ge_A, ge_a_inf, ge_a_sup;
//    ge_A = GrandEntier(A);
//    ge_a_inf = GrandEntier(a_Inf);
//    ge_a_sup = GrandEntier(a_Sup);
//    std::cout << "A x B : " << ge_A.toString() << std::endl;
//    std::cout << "GE_A_MOINS : " << ge_a_inf.toString() << std::endl;
//    std::cout << "GE_A_PLUS : " << ge_a_sup.toString() << std::endl;


    return 0;
}
