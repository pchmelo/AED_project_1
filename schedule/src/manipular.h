//
// Created by pchmelo on 29-10-2023.
//
#include "analise.h"
#include "task.h"

#ifndef PROJETO_1_MANIPULAR_H
#define PROJETO_1_MANIPULAR_H

using namespace std;

/**
 * @file
 * Esta função permite inserir um novo estudante no setStudents
 * Complexidade: O(n)
 * @param s Conjunto dos estudantes atual
 */
void atualizar_alunos(setStudents& s);

/**
 * Esta função testa se uma tarefa é passível de ser realizada
 * Complexidade: O(n)
 * @param s Conjunto de todos os estudantes
 * @param c Lista das aulas
 * @param p Lista das aulas de cada UC
 * @param tarefa Tarefa a ser avaliada
 * @return 0 se a tarefa poder ser realizada.
 1-9 retorna um erro específico que explica o motivo pelo qual a tarefa não pode ser realizada
 */
int teste_tarefa(setStudents s,listClasses c, listPairUcClass p, task tarefa){
    int cap = 30;
    int size_pos = 0;


    if(tarefa.get_student().std_uc.size() == 7){
        return 1;
    }

    std::vector<turmas> t = consultar_ocupacao_turmas(s,p);

    if(tarefa.get_type() != 3){
        auto t_1 = std::find(t.begin(), t.end(), tarefa.get_pair_1());

        if(t_1->v_s.size() >= cap){
            return 2;
        }
        size_pos = t_1->v_s.size() + 1;
    }
    else{
        auto t_2 = std::find(t.begin(), t.end(), tarefa.get_pair_2());

        if(t_2->v_s.size() >= cap){
            return 3;
        }
        size_pos = t_2->v_s.size() + 1;
    }

    schedule sl = tarefa.get_student().criar_horario(c);

    if(tarefa.get_type() != 3){
        auto it = find(sl.sch.begin(), sl.sch.end(), tarefa.get_pair_1().get_uc());
        if(it != sl.sch.end()){
            return 4;
        }
    }
    else{
        if(tarefa.get_pair_1().get_uc() != tarefa.get_pair_2().get_uc()){
            auto it = find(sl.sch.begin(), sl.sch.end(), tarefa.get_pair_2().get_uc());
            if(it != sl.sch.end()){
                return 5;
            }
        }
    }

    schedule new_sch;

    if(tarefa.get_type() != 3){
       new_sch = criar_horario(c, tarefa.get_pair_1());
       auto it = new_sch.sch.begin();

       while(it != new_sch.sch.end()){
           if(!sl.add_possible(*it)){
               return 6;
           }

           it++;
       }
    }
    else{
        new_sch = criar_horario(c, tarefa.get_pair_2());
        auto it = new_sch.sch.begin();

        while(it != new_sch.sch.end()){
            if(!sl.add_possible(*it)){
                return 7;
            }
            it++;
        }
    }

    if(tarefa.get_type() != 3){
        int min = ocupacao_minima(s, p, tarefa.get_pair_1().get_uc());
        if(size_pos - min >= 4){
            return 8;
        }
    }
    else{
        int min = ocupacao_minima(s, p, tarefa.get_pair_2().get_uc());
        if(size_pos - min >= 4){
            return 9;
        }
    }

    return 0;
}

/**
 * Esta função executa a tarefa "add"
 * Complexidade: O(log(n))
 * @param s Conjunto de todos os estudantes
 * @param c Lista das aulas
 * @param p Lista das aulas de cada UC
 * @param q Fila de tarefas
 * @param u Pilha de tarefas
 * @param t
 * @param flag
 */
void processar_add(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u, task t, bool flag){
    auto it = s.setStudents.find(t.get_student());

    Student student = *it;
    student.std_uc.push_back(t.get_pair_1());

    s.setStudents.erase(*it);
    s.setStudents.insert(student);

    if(flag){
        q.q_task.pop();
        u.insert_task(t);
    }

}

void processar_remove(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u, task t, bool flag){
    auto it_1 = s.setStudents.find(t.get_student());

    Student student = *it_1;
    auto it_2 = std::find(student.std_uc.begin(), student.std_uc.end(), t.get_pair_1());

    student.std_uc.erase(it_2);

    s.setStudents.erase(*it_1);
    s.setStudents.insert(student);

    if(flag){
        q.q_task.pop();
        u.insert_task(t);
    }
}

/**
 * Esta função coloca no ficheiro students_classes.csv o conjunto dos estudantes atualizado
 * Complexidade: O(n^2)
 * @param s Conjunto de todos os estudantes
 */
void atualizar_alunos(setStudents& s) {
    std::string dir_file = "../schedule/src/dataSet/students_classes.csv";
    ofstream fout(dir_file,std::ios::out | std::ios::trunc);

    fout << "StudentCode,StudentName,UcCode,ClassCode\r\n";

    auto it_1 = s.setStudents.begin();

    while(it_1 != s.setStudents.end()){
        auto it_2 = it_1->std_uc.begin();

        while (it_2 != it_1->std_uc.end()){
            fout << it_1->get_idNum() << "," << it_1->get_name() << "," << it_2->get_uc() << "," << it_2->get_classe() <<"\r\n";
            it_2++;
        }
        it_1++;
    }

    fout.close();
}


void processar_switch(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u, task t, bool flag){
    task tarefa_1 = task(t.get_type(), t.get_student(), t.get_pair_1());
    task tarefa_2 = task(t.get_type(), t.get_student(), t.get_pair_2());

    processar_remove(s,c,p,q,u,tarefa_1, false);
    processar_add(s,c,p,q,u,tarefa_2, false);

    if(flag){
        q.q_task.pop();
        u.insert_task(t);
    }

}

void processar_undo(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u, task t){
    if(t.get_type() == 1){
        processar_add(s,c,p,q,u,t,false);
    }
    else if(t.get_type() == 2){
        processar_remove(s,c,p,q,u,t,false);
    }
    else{
        processar_switch(s,c,p,q,u,t,false);
    }
    u.stack_task.pop();
}

/**
 * Esta função atualiza a fila de tarefas, removendo as já realizadas
 * Complexidade: O(n)
 * @param q Fila de tarefas
 */
void atualizar_tarefas(queueTask& q){
    task t;
    queueTask& t_q = q;

    std::map<int, std::string> codex{
            {1, "add"},{2, "remove"},
            {3, "switch"}
    };

    string dir_file = "../schedule/src/dataSet/tasks.txt";
    ofstream fout(dir_file,std::ios::out | std::ios::trunc);

    fout << "Type,StudentID,UcCode1,ClassCode1,UcCode2,ClassCode2\n";

    while(!t_q.q_task.empty()){

        fout << codex[t_q.q_task.front().get_type()] << "," << t_q.q_task.front().get_student().get_idNum() << ","
             << t_q.q_task.front().get_pair_1().get_uc() << "," << t_q.q_task.front().get_pair_1().get_classe() << ","
             << t_q.q_task.front().get_pair_2().get_uc() << "," << t_q.q_task.front().get_pair_2().get_classe() << "\n";

        t_q.q_task.pop();
    }

    fout.close();
}

/**
 * Esta função escreve no ficheiro tarefas_realizadas.txt as tarefas concluídas com sucesso
 * Complexidade: O(n)
 * @param u Pilha de tarefas
 */
void atualizar_historico(stackUndo& u){
    stackUndo t_s = u;
    task t;
    string dir_file = "../schedule/src/dataSet/tarefas_realizadas.txt";
    ofstream fout(dir_file,std::ios::out | std::ios::trunc);

    vector<task> v_t;

    std::map<int, std::string> codex{
            {2, "add"},{1, "remove"},
            {3, "switch"}
    };

    fout << "Type,StudentID,UcCode1,ClassCode1,UcCode2,ClassCode2\n";

    while(!t_s.stack_task.empty()){
        v_t.push_back(t_s.stack_task.top());
        t_s.stack_task.pop();
    }

    reverse(v_t.begin(),v_t.end());

    auto it = v_t.begin();

    while(it != v_t.end()){
        if(it->get_type() != 3){
            fout << codex[it->get_type()] << "," << it->get_student().get_idNum() << ","
                 << it->get_pair_1().get_uc() << "," << it->get_pair_1().get_classe() << ","
                 << it->get_pair_2().get_uc() << "," << it->get_pair_2().get_classe() << "\n";
        }
        else{
            fout << codex[it->get_type()] << "," << it->get_student().get_idNum() << ","
                 << it->get_pair_2().get_uc() << "," << it->get_pair_2().get_classe() << ","
                 << it->get_pair_1().get_uc() << "," << it->get_pair_1().get_classe() << "\n";
        }
        it++;
    }

    fout.close();
}



#endif //PROJETO_1_MANIPULAR_H
