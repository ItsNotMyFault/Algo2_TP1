#include "grandentier.hpp"
#include <iostream>
#include <cmath>

GrandEntier GrandEntier::operator*(const GrandEntier &grand_entier) const {
    std::vector<bool> A = this->m_bits;
    std::vector<bool> B = grand_entier.m_bits;
    double m = A.size();
    double n = B.size();
    if (m > n) { //A est plus grand, on augmente B
        int newSize = A.size() - B.size();
        B.insert(B.end(), newSize, 0);
        n = B.size();
    }else if(n > m){//B est plus grand, on augmente A
        int newSize = B.size() - A.size();
        A.insert(A.end(), newSize, 0);
        m = A.size();
    }

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

    ///

    GrandEntier ge_A, ge_a_inf, ge_a_sup;
    ge_A = GrandEntier(A);
    ge_a_inf = GrandEntier(a_Inf);
    ge_a_sup = GrandEntier(a_Sup);

    ///Splits vector B in 2.
    std::vector<bool> b_Inf, b_Sup;
    b_Inf = std::vector<bool>(B.begin(), B.begin() + half_sizeB);
    b_Sup = std::vector<bool>(B.begin() + half_sizeB, B.end());

    GrandEntier ge_B, ge_b_inf, ge_b_sup;
    ge_B = GrandEntier(B);
    ge_b_inf = GrandEntier(b_Inf);
    ge_b_sup = GrandEntier(b_Sup);

    std::cout << "A x B : " << ge_A.toString() << " X " << ge_B.toString() << std::endl;
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
    ///Soit : [2^n * m1] + 2^(n/2) * [opZ] + [m2]
    int exposant1 = 2 * floor(m / 2);
    int exposant2 = floor(n / 2);
    m1.shiftBits(exposant1);//  m1 = 2^n * m1
    opZ.shiftBits(exposant2);//opZ =  2^(n/2) * opZ
    GrandEntier AxB = m1 + opZ + m2;

    std::cout << "m1 : " << m1.toString() << std::endl;
    std::cout << "m2 : " << m2.toString() << std::endl;
    std::cout << "m3 : " << m3.toString() << std::endl;
    std::cout << "opz : " << opZ.toString() << std::endl;
    std::cout << "AxB : " << AxB.toString() << std::endl;
    return AxB;
}
