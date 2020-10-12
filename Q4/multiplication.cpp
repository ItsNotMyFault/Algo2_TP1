#include "grandentier.hpp"
#include <iostream>
#include <cmath>

GrandEntier GrandEntier::operator*(const GrandEntier &grand_entier) const {
    // Inserez votre code ici
    //x & 1 = 0, then its even number
    //x & 1 = 1, then its odd number
    //x >> 1 = x/2 (floor)
    //les 2 tableaux sont passés automatiquement en param par l'opérateur "*".
    std::vector<bool> A = this->m_bits;
    std::vector<bool> B = grand_entier.m_bits;
    int m = A.size();
    int n = B.size();

    std::size_t const half_sizeA = m / 2;
    std::size_t const half_sizeB = n / 2;
    //halfs A
    std::vector<bool> half_A_inferieur(A.begin(), A.begin() + half_sizeA);
    std::vector<bool> half_A_superieur(A.begin() + half_sizeA, A.end());
    //halfs B
    std::vector<bool> halfB_inferieur(B.begin(), B.begin() + half_sizeB);
    std::vector<bool> half_B_superieur(B.begin() + half_sizeB, B.end());


    int resA = 0;
    int resB = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (A.at(i)) {
            resA += pow(2, i);
        }
    }
    for (int i = m - 1; i >= 0; i--) {
        if (B.at(i)) {
//            resB += 2 ^ i;
            resB += pow(2, i);
        }
    }
    //jdois finir avec la formation de 2 Grandentier et
    //les multiplier ensemble afin de faire un nouvel appel récursif.
    int ress = resA * resB;;
    return GrandEntier((int) ress);
}
