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
    Rationnel rationnel0[1] = {Rationnel(0)};
    Polynome polynome0(std::vector<Rationnel>(rationnel0, rationnel0 + 1)); //0
    int degreea = polynome_a.degre();
    int initdegreea = polynome_a.degre();
    int degreeb = polynome_b.degre();

    int i = 0;
    std::vector<Polynome> vec_result;
    while (degreea >= degreeb) {
        ///obitent coefficient polynomes.
        Rationnel coefficientA = polynome_a.coefficient(degreea);
        Rationnel coefficientB = polynome_b.coefficient(degreeb);
        if (coefficientB == Rationnel(0)) {
            coefficientB = 1;
        }
        Rationnel coefficientX = coefficientA / coefficientB;

        if (coefficientX == 0) {
            coefficientX = Rationnel(1);
        }
        ///Création du polynome multiplicateur.
        int degreeX = degreea - degreeb;
        std::vector<Rationnel> vec_rationnels_x(degreeX + 1, Rationnel(0));
        vec_rationnels_x[degreeX] = coefficientX;
        Polynome polynome_x(vec_rationnels_x);

        vec_result.push_back(polynome_x);
        ///création du polynome à sosutraire
        Polynome polynome_a_soustraire = polynome_x * polynome_b;
        ///création polynome restant apprès soustraction
        Polynome quotientRestant = polynome_a - polynome_a_soustraire;
        ///Remplace polynome_a par le nouveau. (si pas égale à 0)
        polynome_a = quotientRestant;
        reste = quotientRestant;
        ///update les degrés
        degreea = polynome_a.degre();
        degreeb = polynome_b.degre();
        i++;
    }
    std::cout << "valeur de initdegreea : " << initdegreea << std::endl;;
    std::cout << "valeur de i : " << i << std::endl;;
    for (int i = 0; i < vec_result.size(); i++) {
        quotient = quotient + vec_result.at(i);
    }


}


Polynome plus_grand_commun_diviseur(const Polynome &a, const Polynome &b) {
    assert(a >= b);
    assert(a.degre() > 0 || a.coefficient(0).numerateur() != 0);
    Polynome numerateur, denominateur, quotient, reste, pgcd;
    numerateur = a;
    denominateur = b;
    //Création de "zéro" et "un" en tant que polynome.
    Rationnel rationnel0[2] = {Rationnel(0), Rationnel(0)};
    Rationnel rationnel1[1] = {Rationnel(1)};
    Polynome polynome0(std::vector<Rationnel>(rationnel0, rationnel0 + 2)); //0
    Polynome polynome1(std::vector<Rationnel>(rationnel1, rationnel1 + 1)); //1
    bool repeat = true;
    while (repeat) {

        if (denominateur != polynome0) {
            division(numerateur, denominateur, quotient, reste);
        } else {
            quotient = polynome1;
            reste = polynome0;
        }
        if (reste.degre() < denominateur.degre() || reste == polynome0) {
            repeat = false;
            pgcd = quotient;
            if (reste != polynome0) {
                pgcd = polynome1;
            }
        }
        //effectue changement de variable.
        numerateur = denominateur;
        denominateur = reste;// le reste parfois est 0 mais je repeat quand même créant une division par 0.
    }
//    std::cout << "RESULTAT : Num/denom [" << a << "] / [" << b << "] = [" << quotient << "] avec reste = " << reste
//              << std::endl;
    return pgcd;
}
