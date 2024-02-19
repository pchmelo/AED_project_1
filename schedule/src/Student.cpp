//
// Created by pchmelo on 10-10-2023.
//

#include "Student.h"

Student::Student() {
    this->name = "0";
    this->idNum = "0";
    this->ano = 0;
    this->curso = "0";
    std_uc.push_back(pairUcClasses("0", "0"));
}

Student::Student(std::string idNum) {
    this->name = "0";
    this->idNum = idNum;
    this->ano = 0;
    this->curso = "0";
    std_uc.push_back(pairUcClasses("0", "0"));
}

Student::Student(std::string idNum, std::string name, std::string uc, std::string classe, int ano, std::string curso){
    this->name = name;
    this->idNum = idNum;
    this->ano = ano;
    this->curso = curso;
    //this->std_uc = pairUcClasses(uc, classe);
    std_uc.push_back(pairUcClasses(uc, classe));
}


std::string Student::get_name() const{
    return name;
}

std::string Student::get_idNum() const{
    return idNum;
}

std::vector<pairUcClasses> Student::get_pairUcClasses() const{
    return std_uc;
}

std::string Student::getCurso() const {
    return curso;
}

void Student::print() const{

    std::cout <<"\niD: " << idNum << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Ano: " << ano << "\n\n";
    std::cout << "Curso: " << curso << "\n\n";

    std::cout << "Cadeiras inscritas:\n";

    for(pairUcClasses uc : std_uc){
        std::cout << uc.get_uc() << ", " << uc.get_classe() << "\n";
    }
}

void Student::print_name() const {
    std::cout <<"\niD: " << idNum << "\n";
    std::cout << "Name: " << name << "\n";
}

void Student::insert_pair(std::string uc, std::string classe, int ano) {
    if(ano > this->ano){
        this->ano = ano;
    }

    std_uc.push_back(pairUcClasses(uc,classe));
}

/*
pairUcClasses Student::get_paiUcClasses() {
    return std_uc;
}
*/

bool Student::operator < (const Student& student) const{
    return this->idNum < student.get_idNum();
}

/*
bool Student::operator<(const std::string& id) const {
    return this->idNum < id;
}
*/
/*
bool Student::operator == (const Student &student) const {
    return this->idNum == student.get_idNum();
}
*/

bool Student::operator == (const std::string &name) const {
    return this->name == name;
}

/*
bool Student::operator()(const std::string &id) const {
    return this->idNum == id;
}
*/

//setStudents métodos

void setStudents::insert_student(Student student) {
    setStudents.insert(student);
}

void setStudents::read_file() {

    std::string dir_file = "../schedule/src/dataSet/students_classes.csv";
    Student s;
    int ano;
    std::string curso;
    std::ifstream MyReadFile(dir_file);
    std::string line;
    std::vector<std::string> t;
    std::pair<std::string, std::string> t_1;
    bool flag_1 = true, flag_2 = true;


    while (getline(MyReadFile, line)) {
        std::stringstream ss(line);

        if (flag_1) {
            flag_1 = false;
            continue;
        }

        while (ss.good()) {
            std::string subtr;
            getline(ss, subtr, ',');
            t.push_back(subtr);
        }

        if (flag_2) {
            ano = t[3].at(0) - 48;
            std::string tt = t[3].substr(1, t[3].size());

            for (char &c: tt) {
                if (c >= '0' && c <= '9') {
                    break;
                }
                curso.push_back(c);
            }
            tt.clear();


            if (t[3][t[3].size() - 1] == '\r') {
                t[3].pop_back();
            }


            s = Student(t[0], t[1], t[2], t[3], ano, curso);

            curso.clear();
            flag_2 = false;
            t.clear();
            continue;

        } else {
            if (s.get_idNum() == t[0]) {
                ano = t[3].at(0) - 48;

                if (t[3][t[3].size() - 1] == '\r') {
                    t[3].pop_back();
                }

                s.insert_pair(t[2], t[3], ano);

                t.clear();
                continue;
            } else {
                auto it = setStudents.find(Student(t[0]));

                if (it == setStudents.end()) {
                    insert_student(s);

                    ano = t[3].at(0) - 48;

                    std::string tt = t[3].substr(1, t[3].size());

                    for (char &c: tt) {
                        if (c >= '0' && c <= '9') {
                            break;
                        }
                        curso.push_back(c);
                    }
                    tt.clear();

                    if (t[3][t[3].size() - 1] == '\r') {
                        t[3].pop_back();
                    }

                    s = Student(t[0], t[1], t[2], t[3], ano, curso);

                    curso.clear();
                    t.clear();
                    continue;
                } else {
                    Student student;
                    student = *it;

                    ano = t[3].at(0) - 48;

                    if (t[3][t[3].size() - 1] == '\r') {
                        t[3].pop_back();
                    }

                    student.insert_pair(t[2], t[3], ano);

                    setStudents.erase(*it);
                    setStudents.insert(student);

                    t.clear();
                    continue;
                }


            }

        }
    }

    insert_student(s);

}

schedule Student::criar_horario(listClasses& c) const{
    schedule res;
    Classes c_t;
    timeLine t;

    for(pairUcClasses p : this->std_uc){
        auto it = std::find(c.list_of_classes.begin(), c.list_of_classes.end(), p);
        c_t = *it;

        for(Horario h : c_t.vector_horario){
            t.h = h;
            t.p = c_t.getPuc();
            res.sch.push_back(t);
        }
    }

    std::sort(res.sch.begin(), res.sch.end());
    return res;
}

void Student::print_horario(listClasses& c) const{
    schedule h_t = this->criar_horario(c);
    Student::print_name();

    std::cout << "----------Horário----------" << std::endl;

    for(timeLine horario : h_t.sch){
        std::cout << "Cadeira: " << horario.p.get_uc() << "\n";
        std::cout << "Turma: " << horario.p.get_classe() << "\n";
        horario.h.print();
        std::cout << "\n";
    }
}

bool Student::student_pretence_class(pairUcClasses turma) const {
    auto it = std_uc.begin();

    while(it != std_uc.end()){
        if(turma == *it){
            return true;
        }
        it++;
    }
    return false;
}

bool Student::student_pertence_ano(int ano) const {
    return this->ano == ano;
}

std::vector<Student> setStudents::searchClass(pairUcClasses turma) const {
    auto it = setStudents.begin();
    std::vector<Student> res;

    while(it != setStudents.end()){
        if(it->student_pretence_class(turma)){
            res.push_back(*it);
        }
        it++;
    }
    return res;
}

year setStudents::searchYear(int ano) const {
    auto it = setStudents.begin();
    year res;
    res.ano = ano;

    while (it != setStudents.end()) {
        if (it->student_pertence_ano(ano)) {
            res.v_s.push_back(*it);
        }
        it++;
    }
    return res;
}

bool Student::student_pertence_curso(std::string curso) const { //Alteração
    return this->curso == curso;
}

std::vector<Student> setStudents::searchCourse(std::string curso) const {
    auto it = setStudents.begin();
    std::vector<Student> res;
    while (it != setStudents.end()) {
        if (it->student_pertence_curso(curso)) {
            res.push_back(*it);
        }
        it++;
    }
    return res;
}


bool Student::student_nUc(int n) const {
    return std_uc.size() >= n;
}

std::vector<Student> setStudents::search_nUc(int n) const {
    auto it = setStudents.begin();
    std::vector<Student> res;

    while(it != setStudents.end()){
        if(it->student_nUc(n)){
            res.push_back(*it);
        }
        it++;
    }
    return res;
}