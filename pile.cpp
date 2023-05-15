#include "pile.h"
#include <iostream>
#include <string>
using namespace std;

pile::pile() {
    this->head = nullptr;
    this->nb_operandes = 0;
}

void pile::empiler(int val) {
    if (this->vide()) {
        operande *o = new operande(val);
        this->head = o;
    } else {
        operande *o = new operande(val, this->head);
        this->head = o;
    }
    this->nb_operandes++;
}

int pile::depiler() {
    if (this->vide()) {
        cout << "La pile est vide, la valeur renvoyee est une valeur par defaut (-1)" << endl;
        return -1;
    } else {
        int val = this->head->valeur;
        operande *o = this->head;
        this->head = this->head->suivant;
        delete o;
        this->nb_operandes--;
        cout << "La valeur depilee est " << val << endl;
        return val;
    }
}

bool pile::vide() {
    if (this->head == nullptr) {
        return true;
    } else {
        return false;
    }
}

void pile::afficher() {
    if (this->vide()) {
        cout << "La pile est vide" << endl;
    } else {
        operande *o = this->head;
        while (o != nullptr) {
            cout << o->valeur << endl;
            o = o->suivant;
        }
    }
}

void pile::evaluer(string expression) {
    for (int i = 0; i < expression.length(); i++) {
        cout << expression[i] << endl;
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            int a = this->depiler();
            int b = this->depiler();
            if (expression[i] == '+') {
                this->empiler(a + b);
            } else if (expression[i] == '-') {
                this->empiler(a - b);
            } else if (expression[i] == '*') {
                this->empiler(a * b);
            } else if (expression[i] == '/') {
                this->empiler(a / b);
            }
        } else {
            this->empiler(stoi(string(1, expression[i])));
        }
    }
    cout << "Le resultat est " << this->depiler() << endl;
}
