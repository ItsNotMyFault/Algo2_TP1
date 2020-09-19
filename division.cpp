#include "division.hpp"
#include <iostream>
#include <assert.h>

void division(const Polynome &dividende, // Le polynome qui est divise
              const Polynome &diviseur,  // Le polynome qui divise
              Polynome &quotient,       // Parametre de sortie: le resultat de la division
              Polynome &reste) {       // Parametre de sortie: le reste de la division
    assert(diviseur.degre() > 0 || diviseur.coefficient(0).numerateur() != 0); // Pas de division par zero

    std::cout << "DIVISION ICI ========== " << std::endl;
    std::cout << "  Entree Dividende: " << dividende << std::endl;
    std::cout << "  Entree Dividende: " << diviseur << std::endl;
    std::cout << "  Entree quotient: " << quotient << std::endl;
    std::cout << "  Entree reste: " << reste << std::endl;

    Rationnel coefficients_dividence[4] = {Rationnel(1), Rationnel(2), Rationnel(0), Rationnel(1)};
    Polynome dividendeTest(std::vector<Rationnel>(coefficients_dividence, coefficients_dividence + 4)); // x^3 + 2x + 1
    Polynome quotientTest(std::vector<Rationnel>(2, Rationnel(1))); // x + 1
    Polynome resss = dividendeTest * quotientTest;
    std::cout << "  resss: " << resss << std::endl;

    // INSEREZ VOTRE CODE ICI
}

Polynome plus_grand_commun_diviseur(const Polynome &a, const Polynome &b) {
    assert(a >= b);
    assert(a.degre() > 0 || a.coefficient(0).numerateur() != 0);

    // INSEREZ VOTRE CODE ICI
    return Polynome();
}
