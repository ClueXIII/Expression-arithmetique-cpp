#include "outputChain.h"
#include <iostream>
#include <string>
#include "pile.h"
using namespace std;

outputChain::outputChain() {
    this->head = nullptr;
    this->tail = nullptr;
    this->nb_caracteres = 0;
}

void outputChain::add(string op) { //ajoute un caractere à la chaine de sortie
    if (this->head == nullptr) {
        caractere *o = new caractere(op);
        this->head = o;
        this->tail = o;
        this->nb_caracteres++;
    } else {
        this->head->suivant = new caractere(op);
        this->nb_caracteres++;
        this->head = this->head->suivant;
    }
}

void outputChain::afficher() {
    caractere *o = this->tail;
    while (o != nullptr) {
        cout << o->valeur;
        o = o->suivant;
    }
    cout << endl;
}

int getpriority (char op) { //retourne la priorité d'un opérateur
    if (op == '('){
        return 0; //parenthèse ouvrante
    }else if (op == '+' || op == '-'){
        return 1; //addition, soustraction
    } else if (op == '*' || op == '/' || op == '%'){
        return 2; //multiplication, division, modulo
    } else if (op == '^'){
        return 3; //puissance (associativité à droite)
    }else if (op == ')') {
        return 4; //parenthèse fermante
    } else {
        return -1; //l'op donné est un operande
    }
}

void outputChain::InfToSuf(string expression) { //transforme une expression infixe en expression suffixée
    pile p;
    for (int i = 0; i < expression.length()+1;i++) {
        string op = "";
        if (getpriority(expression[i]) == -1) { //si expression[i] (que l'on passe en string) est un opérande ou est vide
            if (expression[i] == '\0') { // si l'entrée est vide
                while (!p.vide()) { // tant que la pile n'est pas vide
                    this->add(p.depiler()); // on ajoute les opérateurs de la pile à la chaine de sortie jusqu'à ce que la pile soit vide
                }
            } else { //si l'entrée n'est pas vide c'est un opérande
                op = expression[i];
                while (getpriority(expression[i+1]) ==-1 && expression[i+1] != '\0') { // tant que le caractére suivant est un opérande différant de vide = c'est un chiffre
                    op += expression[i+1]; // on concaténe les chiffres pour former le nombre final
                    i++;// on incrémente i pour passer au caractére suivant
                }
                this->add(op + " "); //on ajoute directement le chiffre/nombre à la chaine de sortie suivit d'un espace pour séparer les opérandes
            }
        } else if (!p.vide()){ //si la pile n'est pas vide et que c'est un opérateur
            if (getpriority(expression[i])  == 3) { // si expression[i] (que l'on passe en string) est un ^ soit le seul oprérateur (utilisé ici) avec une associativité à droite en cpp
                while (getpriority(expression[i])  < getpriority(
                        p.getHead()->valeur[0])) { // tant que l'opérateur au sommet de la pile est strictement plus prioritaire que celui de l'expression
                    this->add(p.depiler()); // on ajoute l'opérateur de la pile à la chaine de sortie
                }
                p.empiler(string(1, expression[i])); // on empile l'opérateur de l'expression
            }
            else if (getpriority(expression[i])  == 0) { // si expression[i] (que l'on passe en string) est une parenthèse ouvrante
                p.empiler(string(1, expression[i])); // on empile la parenthèse ouvrante directement
            } else if (getpriority(expression[i])  == 4) { // si expression[i] (que l'on passe en string) est une parenthèse fermante
                while (p.getHead()->valeur != "(") { // tant que l'opérateur au sommet de la pile n'est pas une parenthèse ouvrante
                    this->add(p.depiler()); // on ajoute l'opérateur de la pile à la chaine de sortie
                }
                p.depiler(); // on dépile ensuite la parenthèse ouvrante
            } else { // pour tout les autres opérateurs qui on une associativité de gauche a droite
                while (!p.vide() && getpriority(expression[i])  <= getpriority(p.getHead()->valeur[0])) {// tant que l'opérateur au sommet de la pile est strictement plus prioritaire que celui de l'expression
                    this->add(p.depiler()); // on ajoute l'opérateur de la pile à la chaine de sortie
                }
                p.empiler(string(1, expression[i])); // on empile l'opérateur de l'expression
            }
        } else { // si la pile est vide et que c'est un operateur
            p.empiler(string(1, expression[i])); // on empile l'opérateur de l'expression
        }
    }
    cout << "votre expression en format suffixee : ";
    this->afficher();
}
