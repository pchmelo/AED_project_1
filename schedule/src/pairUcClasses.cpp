//
// Created by pchmelo on 11-10-2023.
//

#include "pairUcClasses.h"
#include "string"
#include "vector"
#include "fstream"
#include "sstream"
#include "algorithm"

pairUcClasses::pairUcClasses() {
    pUcClasse = std::make_pair("0","0");
}

pairUcClasses::pairUcClasses(std::string uc, std::string classe){
    pUcClasse.first = uc;
    pUcClasse.second = classe;
}

const std::string pairUcClasses::get_classe() const {
    return pUcClasse.second;
}

const std::string pairUcClasses::get_uc() const {
    return pUcClasse.first;
}

bool pairUcClasses::operator==(pairUcClasses p) {
    if (this->pUcClasse.first == p.pUcClasse.first && this->pUcClasse.second == p.pUcClasse.second) {
        return true;
    }
    return false;
}

void pairUcClasses::print() {
    std::cout << pUcClasse.first << "," << pUcClasse.second << '\n';
}

void listPairUcClass::read_file() {
    std::string input = "../schedule/src/dataSet/classes_per_uc.csv";
    std::ifstream MyReadFile(input);
    std::string line;
    pairUcClasses pucl;
    std::getline(MyReadFile, line);

    while (std::getline(MyReadFile, line)) {
        std::vector<std::string> values;
        std::stringstream ss(line);
        while (ss.good()) {
            std::string subtr;
            getline(ss, subtr, ',');
            values.push_back(subtr);
        }

        if (values[1][values[1].size() - 1] == '\r') {
            values[1].pop_back();
        }

        pucl = pairUcClasses(values[0], values[1]);
        list_of_pairs.push_back(pucl);
    }
}

bool operator == (std::pair<std::string, std::list<std::string>> t_1, std::string t_2) {
    return t_1.first == t_2;
}

std::list<classes_per_uc> listPairUcClass::list_class_per_uc() const {
    std::list<classes_per_uc> res;
    classes_per_uc p;

    auto it_1 = list_of_pairs.begin();

    while (it_1 != list_of_pairs.end()) {
        auto it_2 = std::find(res.begin(), res.end(), it_1->get_uc());

        if(it_2 != res.end()){
            p = *it_2;
            res.remove(*it_2);
            p.classes.push_back(it_1->get_classe());
            res.push_back(p);
        }
        else{
            p.uc = it_1->get_uc();
            p.classes.clear();
            p.classes.push_back(it_1->get_classe());
            res.push_back(p);
        }
        it_1 ++;
    }
    return res;
}
