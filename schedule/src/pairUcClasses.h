//
// Created by pchmelo on 11-10-2023.
//
#include "string"
#include "utility"
#include "iostream"
#include "list"
#include "vector"
#ifndef PROJETO_1_PAIRUCCLASSES_H
#define PROJETO_1_PAIRUCCLASSES_H


class pairUcClasses {
private:
    std::pair<std::string, std::string> pUcClasse;

public:

    //Constructors
    pairUcClasses();
    pairUcClasses(std::string uc, std::string classe);

    //Getters
    const std::string get_uc() const;
    const std::string get_classe() const;

    /**
     * Este operador vai permitir encontrar um objeto da classe pairUcClasses na coleção list_of_pairs
     * Complexidade: O(1)
     * @param p pairUcClasses de comparação
     * @return true se a uc e a classe forem iguais no pair associado ao this e ao do parâmetro.
     */
    bool operator==(pairUcClasses p);

    /**
     * Esta função permite imprimir um objeto da classe pairUcClasses
     * Complexidade: O(1)
     */
    void print();

};

struct classes_per_uc{
    std::string uc;
    std::list<std::string> classes;

    /**
     * Este operador vai evitar repetição de UC'S ja encontradas aquando da leitura do ficheiro classes_per_uc
     * Complexidade: O(1)
     * @param t String temporária que representa as UC's
     * @return true se a uc atual for igual ao parâmetro. Senão retorna false.
     */
    bool operator == (std::string t) const{
        return this->uc == t;
    }

    /**
     * Este operador vai permitir encontrar um elemento da coleção list_class_per_uc
     * Complexidade: O(1)
     * @param t classes_per_uc de comparação
     * @return true se a uc atual for igual à uc associada ao parâmetro t. Senão retorna false.
     */
    bool operator == (classes_per_uc t) const{
        return this->uc == t.uc;
    }

    /**
     * Esta função permite recolher os dados obtidos através da leitura do ficheiro classes_per_uc
     * Complexidade: O(n)
     * @return Um vetor<pairUcClasses> com os dados do ficheiro
     */
    std::vector<pairUcClasses> convert() const{
        std::vector<pairUcClasses> res;
        pairUcClasses p;

        for(std::string cl : this->classes){
            res.push_back(pairUcClasses(this->uc, cl));
        }
        return res;
    }
};

class listPairUcClass{
    public:
        std::list<pairUcClasses> list_of_pairs;

        /**
        * Esta função vai ler o ficheiro classes_per_uc e retirar os devidos dados
        * Complexidade: O(n), onde n é o número de linhas do ficheiro
        * @return
        */
        void read_file();
        std::list<classes_per_uc> list_class_per_uc() const;

};




#endif //PROJETO_1_PAIRUCCLASSES_H
