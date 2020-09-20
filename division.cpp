#include "division.hpp"

#include <assert.h>

void division(const Polynome &dividende, // Le polynome qui est divise
              const Polynome &diviseur,  // Le polynome qui divise
              Polynome &quotient,       // Parametre de sortie: le resultat de la division
              Polynome &reste) {       // Parametre de sortie: le reste de la division
    assert(diviseur.degre() > 0 || diviseur.coefficient(0).numerateur() != 0); // Pas de division par zero
    // (x^3 + 2x + 1) / (x + 1) = x^2 - x + 3 reste -2
    //FIN DU VECTEUR : début équation (full gauche) => x^3
    //DÉBUT DU VECTEUR : fin équation (full droite) => 1
    Polynome polynome_a = dividende;
    Polynome polynome_b = diviseur;

    std::cout << "polynome_a: " << polynome_a << std::endl;
    std::cout << "polynome_b: " << polynome_b << std::endl;

    int degreea = polynome_a.degre();
    int degreeb = polynome_b.degre();
    std::vector<Polynome> vec_result;
    while (degreea >= degreeb) {
        //obitent coefficient polynomes.
        Rationnel coefficientA = polynome_a.coefficient(degreea);
        Rationnel coefficientB = polynome_b.coefficient(degreeb);

//        double coefficientA_abs = std::abs(coefficientA.reel());
//        double coefficientB_abs = std::abs(coefficientB.reel());
        Rationnel coefficientX = coefficientA - coefficientA;
        if (coefficientX == 0) {
            coefficientX = Rationnel(1);
        }
        std::cout << "coefficientA: " << coefficientA << std::endl;
        std::cout << "coefficientB: " << coefficientB << std::endl;
        std::cout << "coefficientX: " << coefficientX << std::endl;
        //Création du polynome multiplicateur.
        int degreeX = degreea - degreeb;
        std::vector<Rationnel> vec_rationnels_x(degreeX + 1, Rationnel(0));
        vec_rationnels_x[degreeX] = coefficientX;
        Polynome polynome_x(vec_rationnels_x);

        vec_result.push_back(polynome_x);
        std::cout << "polynome_x: " << polynome_x << std::endl;
        ///création du polynome à sosutraire
        Polynome polynome_a_soustraire = polynome_x * polynome_b;

        std::cout << "polynome_a_soustraire: " << polynome_a_soustraire << std::endl;
        ///création polynome restant apprès soustraction
        Polynome quotientRestant = polynome_a - polynome_a_soustraire;
        std::cout << "quotientRestant: " << quotientRestant << std::endl;
        ///Remplace polynome_a par le nouveau.
        std::cout << "======================: " << std::endl;
        polynome_a = quotientRestant;
        reste = quotientRestant;
        //update les degrees...
        degreea = polynome_a.degre();
        degreeb = polynome_b.degre();

    }

    for (int i = 0; i < vec_result.size(); i++) {
        quotient = quotient + vec_result.at(i);
    }
    // INSEREZ VOTRE CODE ICI
}


Polynome plus_grand_commun_diviseur(const Polynome &a, const Polynome &b) {
    assert(a >= b);
    assert(a.degre() > 0 || a.coefficient(0).numerateur() != 0);

    // INSEREZ VOTRE CODE ICI
    return Polynome();
}
