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

    int max = std::max(m, n);
    if (max <= 1) {
        int valueA = 0, valueB = 0;
        if (m > 0) {
            valueA = A.at(0);
        }
        if (n > 0) {
            valueB = B.at(0);
        }
        return GrandEntier(valueA * valueB);;
    }
    ///Init some variables...
    GrandEntier m1, m2, m3, additionA, additionB, opZ;
    GrandEntier ge_1 = GrandEntier(1);
    std::size_t const half_sizeA = m / 2;
    std::size_t const half_sizeB = n / 2;
    ///halfs A
    std::vector<bool> a_Inf(A.begin(), A.begin() + half_sizeA);
    std::vector<bool> a_Sup(A.begin() + half_sizeA, A.end());
    GrandEntier ge_A = GrandEntier(A);
    GrandEntier ge_a_inf = GrandEntier(a_Inf);
    GrandEntier ge_a_sup = GrandEntier(a_Sup);

    ///halfs B
    std::vector<bool> b_Inf(B.begin(), B.begin() + half_sizeB);
    std::vector<bool> b_Sup(B.begin() + half_sizeB, B.end());
    GrandEntier ge_b = GrandEntier(B);
    GrandEntier ge_b_inf = GrandEntier(b_Inf);
    GrandEntier ge_b_sup = GrandEntier(b_Sup);

    std::cout << "GE_A : " << ge_A.toString() << std::endl;
    std::cout << "GE_A_MOINS : " << ge_a_inf.toString() << std::endl;
    std::cout << "GE_A_PLUS : " << ge_a_sup.toString() << std::endl;
    std::cout << "GE_B : " << ge_b.toString() << std::endl;
    std::cout << "GE_B_MOINS : " << ge_b_inf.toString() << std::endl;
    std::cout << "GE_B_PLUS : " << ge_b_sup.toString() << std::endl;
    std::cout << "================" << std::endl;


    ///IDentification opération à effectuer
    //[2^n * a_Sup * b_Sup] + 2^(n/2) * [(a_Sup * b_inf) + (a_Inf * b_Sup)] + [(a_Inf * b_inf)]
    //[2^n *      m1      ] + 2^(n/2) * [opZ]                             +       [m2]
    ///Découverte variable réduit # de multiplication (opZ)
    // [Opé_Z] = (a_Sup + a_Inf)*(b_Sup + b_Inf) - (a_Sup * b_Sup) - (a_Inf * b_Inf)
    //           (additionA)    * (additionB)    -      m1         -       m2
    //                         m3                -      m1         -       m2
    ///Identification de m1, m2, m3
    std::cout << "m1 : ============" << std::endl;
    m1 = ge_a_sup * ge_b_sup;
    std::cout << "m2 : ============" << std::endl;
    m2 = ge_a_inf * ge_b_inf;
    additionA = ge_a_sup + ge_a_inf;
    additionB = ge_b_sup + ge_b_inf;
    std::cout << "m3 : ============" << std::endl;
    m3 = additionA * additionB;
    ///Calcul opZ
    opZ = m3 - m1 - m2;

    ///Application de la formule avec les valeurs trouvés
    ///Soit : [2^n * m1] + 2^(n/2) * [m3] + [m2]
    ///Les multiplications binaire sont compté comme des opérations élémentaires.

    m1.shiftBits(floor(n));//  m1 = 2^n * m1
    opZ.shiftBits(floor(n / 2));//opZ =  2^(n/2) * opZ
//    std::cout << m1.toString() << std::endl;
//    std::cout << m2.toString() << std::endl;
//    std::cout << m3.toString() << std::endl;
    GrandEntier trueRes = m1 + opZ + m2;
    std::cout << "trueRes : " << trueRes.toString() << std::endl;
    return trueRes;
}
