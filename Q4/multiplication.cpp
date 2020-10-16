#include "grandentier.hpp"
#include <iostream>
#include <cmath>


GrandEntier calculateAxB(int n, GrandEntier m1, GrandEntier m2, GrandEntier m3) {
    ///Calcul opZ
    GrandEntier opZ = m3 - m1 - m2;//2*Theta(n+m)
    ///Application de la formule avec les valeurs trouvés
    ///Soit : [2^n * m1] + 2^(n/2) * [opZ] + [m2]
    int exposant1 = 2 * floor(n / 2);//theta(1)
    int exposant2 = floor(n / 2);//theta(1)
    ///  m1 = 2^n * m1
    m1.shiftBits(exposant1);//theta(n+shift)
    ///opZ =  2^(n/2) * opZ
    opZ.shiftBits(exposant2);//theta(n+shift)

    GrandEntier AxB = m1 + opZ + m2;//2*Theta(n+m)
    return AxB;
}

///Make sure vectors are both of the same size, by filling with some 0s.
void fillVectorsWithZeros(std::vector<bool> &A, std::vector<bool> &B) {
    int m = A.size();
    int n = B.size();
    if (m > n) { //A est plus grand, on augmente B
        int newSize = A.size() - B.size();
        B.insert(B.end(), newSize, 0);//theta(n)
        n = B.size();
    } else if (n > m) {//B est plus grand, on augmente A
        int newSize = B.size() - A.size();
        A.insert(A.end(), newSize, 0);//theta(n)
        m = A.size();
    }
}

int i = 0;

GrandEntier GrandEntier::operator*(const GrandEntier &grand_entier) const {
    std::vector<bool> A = this->m_bits;//theta(n)
    std::vector<bool> B = grand_entier.m_bits;//theta(n)
    fillVectorsWithZeros(A, B);//theta(n) worst, theta(1) best
    int n = A.size();

    if (n <= 1) {
        int valueA = 0, valueB = 0;
        if (n > 0) {
            valueA = A.at(0);
            valueB = B.at(0);
        }
        i++;
        std::cout << "i -> " << i << std::endl;
        return GrandEntier(valueA * valueB);//theta(1)
    }
    ///Init some variables...
    GrandEntier m1, m2, m3, additionA, additionB, opZ;
    int half_sizeA = floor(n / 2.0);//theta(1)
    int half_sizeB = floor(n / 2.0);//theta(1)
    ///Splits vector A in 2.
    std::vector<bool> a_Inf, a_Sup;
    a_Inf = std::vector<bool>(A.begin(), A.begin() + half_sizeA);//theta(n/2)
    a_Sup = std::vector<bool>(A.begin() + half_sizeA, A.end());//theta(n/2)

    GrandEntier ge_A, ge_a_inf, ge_a_sup;
    ge_a_inf = GrandEntier(a_Inf);//theta(n/2)
    ge_a_sup = GrandEntier(a_Sup);//theta(n/2)

    ///Splits vector B in 2.
    std::vector<bool> b_Inf, b_Sup;//theta(1)
    b_Inf = std::vector<bool>(B.begin(), B.begin() + half_sizeB);//theta(n/2)
    b_Sup = std::vector<bool>(B.begin() + half_sizeB, B.end());//theta(n/2)

    GrandEntier ge_B, ge_b_inf, ge_b_sup;
    ge_b_inf = GrandEntier(b_Inf);//theta(n/2)
    ge_b_sup = GrandEntier(b_Sup);//theta(n/2)

    ///Identification de m1, m2, m3
    m1 = ge_a_sup * ge_b_sup;//theta(1)
    m2 = ge_a_inf * ge_b_inf;//theta(1)
    additionA = ge_a_sup + ge_a_inf;//theta(n/2 + n/2) = theta(n)
    additionB = ge_b_sup + ge_b_inf;//theta(n/2 + n/2) = theta(n)
    m3 = additionA * additionB;//theta(1)

    ///calculate AxB with formula
    GrandEntier AxB = calculateAxB(n, m1, m2, m3);//4*theta(n+m)
    return AxB;
}


