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

    Polynome polynome_a = dividende;//theta(polynome_a.degree)
    Polynome polynome_b = diviseur;
    Rationnel rationnel0[1] = {Rationnel(0)};//Theta(1)
    Polynome polynome0(std::vector<Rationnel>(rationnel0, rationnel0 + 1));//theta(1)
    int degreea = polynome_a.degre();//Theta(1)
    int degreeb = polynome_b.degre();//Theta(1)

    int i = 0;
    std::vector<Polynome> vec_result;
    while (degreea >= degreeb) {//teta(1)
        ///obtient coefficient polynomes.
        Rationnel coefficientA = polynome_a.coefficient(degreea);//teta(1)
        Rationnel coefficientB = polynome_b.coefficient(degreeb);//teta(1)
        if (coefficientB == Rationnel(0)) {//teta(1)
            coefficientB = 1;
        }
        Rationnel coefficientX = coefficientA / coefficientB;//teta(1)

        if (coefficientX == 0) {//teta(1)
            coefficientX = Rationnel(1);
        }
        ///Création du polynome multiplicateur.
        int degreeX = degreea - degreeb;//teta(1)
        //Construction d'un vecteur se fait en temps linéaire selon la soustraction des degrés des 2 polynomes
        //Toutefois la construction du vecteur est négligeable comparer au reste de l'algorithme.
        std::vector<Rationnel> vec_rationnels_x(degreeX + 1, Rationnel(0));//linear container size. teta(degreeX)
        vec_rationnels_x[degreeX] = coefficientX;
        Polynome polynome_x(vec_rationnels_x); //teta(1)
        std::cout << std::endl << polynome_x << std::endl;
        vec_result.push_back(polynome_x);// teta(1)
        ///création du polynome à sosutraire
        Polynome polynome_a_soustraire = polynome_x * polynome_b;//teta(degreeX^2)
        ///création polynome restant apprès soustraction
        Polynome quotientRestant = polynome_a - polynome_a_soustraire; //teta(degreea + degreePolyASoustraire)
        ///Remplace polynome_a par le nouveau. (si pas égale à 0)
        polynome_a = quotientRestant;
        reste = quotientRestant;
        ///update les degrés
        degreea = polynome_a.degre();//teta(1)
        degreeb = polynome_b.degre();//teta(1)
        i++;
    }
    std::cout << "valeur de i : " << i << std::endl;;
    for (int i = 0; i < vec_result.size(); i++) {//theta(vec_result.size())
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
        ///Pour une raison quelconque, le denominaeur recu en paramètre est = à 0 plus de 50 fois.
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
