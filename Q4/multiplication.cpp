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
    double m = A.size();
    double n = B.size();

    double max = std::max(m, n);
    if (max <= 1) {
        int valueA = 0, valueB = 0;
        if (m > 0) {
            valueA = A.at(0);
        }
        if (n > 0) {
            valueB = B.at(0);
        }
        return GrandEntier(valueA * valueB);
    }
    ///Init some variables...
    GrandEntier m1, m2, m3, additionA, additionB, opZ;
    int half_sizeA = floor(m / 2.0);
    int half_sizeB = floor(n / 2.0);
    ///Splits vector A in 2.
    std::vector<bool> a_Inf, a_Sup;
    a_Inf = std::vector<bool>(A.begin(), A.begin() + half_sizeA);
    a_Sup = std::vector<bool>(A.begin() + half_sizeA, A.end());

    GrandEntier ge_A, ge_a_inf, ge_a_sup;
    ge_A = GrandEntier(A);
    ge_a_inf = GrandEntier(a_Inf);
    ge_a_sup = GrandEntier(a_Sup);
    if(m == 1){
        ge_a_sup = GrandEntier(0);
        ge_a_inf = GrandEntier(1);
    }


    ///Splits vector B in 2.
    std::vector<bool> b_Inf, b_Sup;
    b_Inf = std::vector<bool>(B.begin(), B.begin() + half_sizeB);
    b_Sup = std::vector<bool>(B.begin() + half_sizeB, B.end());

    GrandEntier ge_b, ge_b_inf, ge_b_sup;
    ge_b = GrandEntier(B);
    ge_b_inf = GrandEntier(b_Inf);
    ge_b_sup = GrandEntier(b_Sup);
    if(n == 1){
        ge_b_sup = GrandEntier(0);
        ge_b_inf = GrandEntier(1);
    }
//    if(m == 1){
//        ge_b_inf = GrandEntier(0);
//        ge_b_sup = GrandEntier(b_Inf);
//    }

    std::cout << "A x B : " << ge_A.toString() << " X " << ge_b.toString() << std::endl;
    std::cout << "GE_A_MOINS : " << ge_a_inf.toString() << std::endl;
    std::cout << "GE_A_PLUS : " << ge_a_sup.toString() << std::endl;
    std::cout << "GE_B_MOINS : " << ge_b_inf.toString() << std::endl;
    std::cout << "GE_B_PLUS : " << ge_b_sup.toString() << std::endl;
    std::cout << "================" << std::endl;


    ///IDentification opération à effectuer
    //[2^n * a_Sup * b_Sup] + 2^(n/2) * [(a_Sup * b_inf) + (a_Inf * b_Sup)] + [(a_Inf * b_inf)]
    //[2^n *      m1      ] + 2^(n/2) * [opZ]                             +       [m2]
    ///Découverte variable réduit # de multiplication (opZ)
    // [opZ] = (a_Sup + a_Inf)*(b_Sup + b_Inf) - (a_Sup * b_Sup) - (a_Inf * b_Inf)
    //           (additionA)    * (additionB)    -      m1         -       m2
    //                         m3                -      m1         -       m2
    ///Identification de m1, m2, m3

    m1 = ge_a_sup * ge_b_sup;
    m2 = ge_a_inf * ge_b_inf;
    additionA = ge_a_sup + ge_a_inf;
    additionB = ge_b_sup + ge_b_inf;
    m3 = additionA * additionB;
    ///Calcul opZ
    opZ = m3 - m1 - m2;

    ///Application de la formule avec les valeurs trouvés
    ///Soit : [2^n * m1] + 2^(n/2) * [m3] + [m2]
    ///Les multiplications binaire sont compté comme des opérations élémentaires.
    int exposant1 = 2 * floor(max / 2);
    int exposant2 = floor(max / 2);
    m1.shiftBits(exposant1);//  m1 = 2^n * m1
    opZ.shiftBits(exposant2);//opZ =  2^(n/2) * opZ
    std::cout << "m1 : " << m1.toString() << std::endl;
    std::cout << "m2 : " << m2.toString() << std::endl;
    std::cout << "m3 : " << m3.toString() << std::endl;
    std::cout << "opz : " << opZ.toString() << std::endl;
    GrandEntier AxB = m1 + opZ + m2;
    std::cout << "AxB : " << AxB.toString() << std::endl;
    return AxB;
}
