//
// Created by pchmelo on 29-10-2023.
//
#include "task.h"

task::task() {
    this->type = 0;
    this->student = Student();
    this->mudanca_1 = pairUcClasses();
    this->mudanca_2 = pairUcClasses();
}

task::task(int type, Student student, pairUcClasses mudanca_1) {
    this->type = type;
    this->student = student;
    this->mudanca_1 = mudanca_1;
    this->mudanca_2 = pairUcClasses();
}

task::task(int type, Student student, pairUcClasses mudanca_1, pairUcClasses mudanca_2) {
    this->type = type;
    this->student = student;
    this->mudanca_1 = mudanca_1;
    this->mudanca_2 = mudanca_2;
}

int task::get_type() const {
    return this->type;
}

Student task::get_student() const {
    return  this->student;
}

pairUcClasses task::get_pair_1() const {
    return  this->mudanca_1;
}

pairUcClasses task::get_pair_2() const {
    return  this->mudanca_2;
}

//------------QueueTask--------------

void queueTask::read_file(setStudents s){
    std::string dir_file = "../schedule/src/dataSet/tasks.txt";
    std::ifstream MyReadFile(dir_file);
    Student student;
    pairUcClasses p_1, p_2;

    std::map<std::string, int> codex{
            {"add", 1},{"remove", 2},
            {"switch", 3}
    };

    bool flag_1 = true;
    std::string line;
    task t;

    std::vector<std::string> v;

    while (getline(MyReadFile, line)) {
        std::stringstream ss(line);

        if (flag_1) {
            flag_1 = false;
            continue;
        }

        while (ss.good()) {
            std::string subtr;
            getline(ss, subtr, ',');
            v.push_back(subtr);
        }
        student = Student(v[1]);

        auto it = s.setStudents.find(student);
        p_1 = pairUcClasses(v[2], v[3]);
        p_2 = pairUcClasses(v[4], v[5]);

        t = task(codex[v[0]], *it, p_1, p_2);
        q_task.push(t);

        v.clear();
    }
}

void queueTask::insert_task(task tarefa) {
    q_task.push(tarefa);

    std::map<int, std::string> codex{
            {1, "add"},{2, "remove"},
            {3, "switch"}
    };

    /*
    std::string dir_file = "/home/pchmelo/Desktop/AED/projeto_1/schedule/src/dataSet/tasks.txt";

    std::fstream fout;
    fout.open(dir_file, std::ios::out | std::ios::app);

    fout << codex[tarefa.get_type()] << "," << tarefa.get_student().get_idNum() << ","
    << tarefa.get_pair_1().get_uc() << "," << tarefa.get_pair_1().get_classe() << ","
    << tarefa.get_pair_2().get_uc() << "," << tarefa.get_pair_2().get_classe() << "\n";

    fout.close();
    */
}

void stackUndo::read_file(setStudents s) {
    std::string dir_file = "../schedule/src/dataSet/tarefas_realizadas.txt";
    std::ifstream MyReadFile(dir_file);
    Student student;
    pairUcClasses p_1, p_2;

    std::map<std::string, int> codex{
            {"add", 2},{"remove", 1},
            {"switch", 3}
    };

    bool flag_1 = true;
    std::string line;
    task t;

    std::vector<std::string> v;

    while (getline(MyReadFile, line)) {
        std::stringstream ss(line);

        if (flag_1) {
            flag_1 = false;
            continue;
        }

        while (ss.good()) {
            std::string subtr;
            getline(ss, subtr, ',');
            v.push_back(subtr);
        }
        student = Student(v[1]);

        auto it = s.setStudents.find(student);


        if(codex[v[0]] == 3){
            p_1 = pairUcClasses(v[4], v[5]);
            p_2 = pairUcClasses(v[2], v[3]);
        }
        else{
            p_1 = pairUcClasses(v[2], v[3]);
            p_2 = pairUcClasses(v[4], v[5]);
        }

        t = task(codex[v[0]], *it, p_1, p_2);
        stack_task.push(t);

        v.clear();
    }
}

void stackUndo::insert_task(task tarefa) {
    task new_task;

    if(tarefa.get_type() == 1){
        new_task = task(2, tarefa.get_student(), tarefa.get_pair_1());
    }
    else if(tarefa.get_type() == 2){
        new_task = task(1, tarefa.get_student(), tarefa.get_pair_1());
    }
    else{
        new_task = task(3, tarefa.get_student(), tarefa.get_pair_2(), tarefa.get_pair_1());
    }

    stack_task.push(new_task);

    /*
    std::map<int, std::string> codex{
            {1, "add"},{2, "remove"},
            {3, "switch"}
    };

    std::string dir_file = "/home/pchmelo/Desktop/AED/projeto_1/schedule/src/dataSet/tarefas_realizadas.txt";

    std::fstream fout;
    fout.open(dir_file, std::ios::out | std::ios::app);

    fout << codex[tarefa.get_type()] << "," << tarefa.get_student().get_idNum() << ","
         << tarefa.get_pair_1().get_uc() << "," << tarefa.get_pair_1().get_classe() << ","
         << tarefa.get_pair_2().get_uc() << "," << tarefa.get_pair_2().get_classe() << "\n";

    fout.close();
    */
}