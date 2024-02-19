//
// Created by pchmelo on 29-10-2023.
//

#include "queue"
#include "Student.h"
#include "pairUcClasses.h"
#include "Classes.h"
#include "stack"

#ifndef PROJETO_1_QUEUETASK_H
#define PROJETO_1_QUEUETASK_H


class task {
    private:
        int type;
        Student student;
        pairUcClasses mudanca_1;
        pairUcClasses mudanca_2;

    public:
        task();
        task(int type, Student student, pairUcClasses mudanca_1);
        task(int type, Student student, pairUcClasses mudanca_1, pairUcClasses mudanca_2);

        int get_type() const;
        Student get_student() const;
        pairUcClasses get_pair_1() const;
        pairUcClasses get_pair_2() const;

};

class queueTask{
    public:
        std::queue<task> q_task;

    /**
    * Esta função lê e retira dados do ficheiro tasks.txt
    * Complexidade: O(n), onde n é o número de linhas do ficheiro
    * @param s Conjunto de todos os estudantes
    */
        void read_file(setStudents s);

    /**
    * Esta função permite adicionar uma nova tarefa à fila q_task
    * Complexidade: O(1)
    * @param tarefa Tarefa a ser realizada
    */
        void insert_task(task tarefa);
};

class stackUndo{
public:
    std::stack<task> stack_task;

    /**
     * Esta função lê e retira os dados necessários do ficheiro tarefas_realizadas.txt
     * Complexidade: O(n), onde n é um número de linhas do ficheiro
     * @param s Conjunto de todos os estudantes
     */
    void read_file(setStudents s);

    /**
     * Esta função insere uma nova tarefa que foi concluída com sucesso
     * Complexidade: O(1)
     * @param tarefa Tarefa concluída
     */
    void insert_task(task tarefa);
};


#endif //PROJETO_1_QUEUETASK_H
