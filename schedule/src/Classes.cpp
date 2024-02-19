//
// Created by User on 24/10/2023.
//

#include "Classes.h"
#include "vector"
#include "fstream"
#include "sstream"

Horario::Horario() {
    this->duration = 0;
    this->start_hour = 0;
    this->type = "0";
    this->weekday = "0";
}

Horario::Horario(std::string weekday, float start_hour, float duration, std::string type) {
    this->duration = duration;
    this->start_hour = start_hour;
    this->type = type;
    this->weekday = weekday;
}

const std::string &Horario::getWeekday() const {
    return weekday;
}

float Horario::getStartHour() const {
    return start_hour;
}

const std::string &Horario::getType() const {
    return type;
}

float Horario::getDuration() const {
    return duration;
}

bool Horario::operator<(Horario horario) const {
       std::map<std::string, int> codex{
           {"Monday", 1},{"Tuesday", 2},
           {"Wednesday", 3},{"Thursday", 4},
           {"Friday", 5},{"Saturday", 6}
       };

       if(codex[this->weekday] < codex[horario.weekday]){
           return true;
       }
       else if(codex[this->weekday] == codex[horario.weekday]){
           if(this->start_hour < horario.start_hour){
               return true;
           }
       }
    return false;

}

void Horario::print() const {
    std::cout << "Dia da semana: " << this->weekday << "\n";
    std::cout << "Duracao: " << this->duration << "\n";
    std::cout << "Tipo da aula: " << this->type << "\n";
    std::cout << "Hora do comeco da aula: " << this->start_hour << "\n";
}

bool Horario::sobreposicao(Horario h) const {
    Horario h_1, h_2 = h;
    h_1.start_hour = this->start_hour;
    h_1.duration = this->duration;

    if(h_2.start_hour < h_1.start_hour){
        h_2 = h_1;
        h_1 = h;
    }

    float end_1 = h_1.start_hour + h_1.duration;

    if(h_2.start_hour < end_1){
        return true;
    }
    return false;
}

//--------------------------------Classes--------------------------------

Classes::Classes() {
    this->puc = pairUcClasses("", "");
    Horario h;
    this->vector_horario.push_back(h);
}

Classes::Classes(pairUcClasses puc, std::string weekday, float start_hour, float duration, std::string type) {
    this->puc = puc;
    Horario h = Horario(weekday, start_hour, duration, type);
    this->vector_horario.push_back(h);
}

const pairUcClasses &Classes::getPuc() const {
    return puc;
}

bool Classes::operator == (const Classes& cl) const{
    if ((this->puc.get_uc() == cl.puc.get_uc()) && (this->puc.get_classe() == cl.puc.get_classe())) {
        return true;
    }
    return false;
}

bool Classes::operator == (const pairUcClasses& pair) const{
    if ((this->puc.get_uc() == pair.get_uc()) && (this->puc.get_classe() == pair.get_classe())) {
        return true;
    }
    return false;
}

void Classes::print() {
    std::cout << puc.get_uc() << "," << puc.get_classe() << "\n";
    std::cout << "Horarios\n";

    for(Horario h: vector_horario){
        h.print();
    }
}


void Classes::insert_horario(std::string weekday, float start_hour, float duration, std::string type) {
    vector_horario.push_back(Horario(weekday, start_hour, duration, type));
}

void listClasses::read_file() {
    std::string input = "../schedule/src/dataSet/classes.csv";
    std::ifstream MyReadFile(input);
    std::string line;
    Classes cl;
    pairUcClasses p;
    std::getline(MyReadFile, line);



    while (std::getline(MyReadFile, line)) {
        std::vector<std::string> values;
        std::stringstream ss(line);

        while (ss.good()) {
            std::string substr;
            getline(ss, substr, ',');
            values.push_back(substr);
        }

        p = pairUcClasses(values[1], values[0]);

        auto it = std::find(list_of_classes.begin(), list_of_classes.end(), p);

        if(it != list_of_classes.end()){
            cl = *it;
            list_of_classes.remove(*it);

            if (values[5][values[5].size() - 1] == '\r') {
                values[5].pop_back();
            }

            cl.insert_horario(values[2], std::stof(values[3]), std::stof(values[4]), values[5]);
            list_of_classes.push_back(cl);

        }
        else{
            if (values[5][values[5].size() - 1] == '\r') {
                values[5].pop_back();
            }

            cl = Classes(pairUcClasses(values[1], values[0]), values[2], std::stof(values[3]), std::stof(values[4]), values[5]);
            list_of_classes.push_back(cl);
        }

    }
    auto it = std::find(list_of_classes.begin(), list_of_classes.end(), p);
    cl = *it;
    cl.vector_horario.push_back(cl.vector_horario.at(0));
    list_of_classes.remove(*it);
    list_of_classes.push_back(cl);
}
