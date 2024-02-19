#include "algorithm"
#include "analise.h"
#include "manipular.h"

using namespace std;

void terminal_analise(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void analise_consultar_alunos(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void ambiente_teste(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void analise_horario_aluno(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void terminal_ocupacao_ano(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void terminal_ocupacao_uc(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void terminal_ocupacao_turma(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void terminal_manipular(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void terminal_adicionar_tarefa(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void terminal_ver_tarefas(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u, bool flag);
void terminal_processar_pedido(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);
void terminal_ver_historico(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u, bool flag);
void terminal_processar_undo(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u);


void terminal_inicialize(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    string input;

    cout << "----------------------Bem vindo----------------------\n\n";
    cout << "Pressione um numero indicado:\n";

    cout << "1 -> Análise da informacao\n";
    cout << "2 -> Manipulacao dos dados\n";
    cout << "3 -> Ambiente de teste\n";
    cout << "4 -> Exit\n";

    cin >> input;

    if(input == "1"){
        terminal_analise(s, c, p, q, u);
    }
    else if(input == "2"){
        terminal_manipular(s, c, p, q, u);
    }
    else if(input == "3"){
        ambiente_teste(s, c, p, q, u);
    }
    else if(input == "4"){
        int i = 0;
    }
    else{
        cout << "Input inválido\n";
        terminal_inicialize(s, c, p, q, u);
    }
}

void terminal_analise(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    string input;

    cout << "-----------------------Analise-----------------------\n\n";
    cout << "Pressione um numero indicado:\n";

    cout << "1 -> Procurar pelo horario de um aluno\n";
    cout << "2 -> Consultar os alunos de (...)\n";
    cout << "3 -> Consultar os alunos em n UC's\n";
    cout << "4 -> Consultar a ocupacao das turmas (...)\n";
    cout << "5 -> Consultar a ocupacao dos anos (...)\n";
    cout << "6 -> Consultar a ocupacao das UC's (...)\n";
    cout << "7 -> Voltar para tras\n";

    cin >> input;

    if(input == "1"){
        analise_horario_aluno(s, c, p, q, u);
    }

    else if (input == "2"){
        analise_consultar_alunos(s, c, p, q, u);

        cin >> input;
    }
    else if(input == "3"){
        cout << "Introduza o numero de cadeiras inscristas por aluno,\ne pressione 'e' para voltar para tras:\n";
        cin >> input;

        if(input == "e"){
            terminal_analise(s, c, p, q, u);
        }
        else{
            alunos_inscritos_nUC(s, std::stoi(input));
            cout << "\n------Operacao finalizada com sucesso------\n";
            terminal_analise(s, c, p, q, u);
        }

    }
    else if(input == "4"){
        terminal_ocupacao_turma(s, c, p, q, u);

    }
    else if(input == "5"){
        terminal_ocupacao_ano(s,c,p,q,u);
    }
    else if(input == "6"){
        terminal_ocupacao_uc(s, c, p, q, u);
    }

    else if(input == "7"){
        terminal_inicialize(s, c, p, q, u);
    }
    else{
        cout << "Input invalido\n";
        terminal_analise(s, c, p, q, u);
    }
}

void analise_horario_aluno(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    string input;

    cout << "\nIntroduza o iD ou o nome do Aluno,\ne pressione 'e' para voltar para tras:\n";

    cin >> input;
    cout << input;

    if(input == "e"){
        terminal_analise(s, c, p, q, u);
    }
    else {
        horario_aluno(input, s, c);
        cout << "\n--------Operacao finalizada com sucesso--------\n\n";
        terminal_analise(s, c, p, q, u);
    }

}

void analise_consultar_alunos(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    string input;

    cout << "\nConsultar os alunos de ...\n";
    cout << "1 -> uma turma\n";
    cout << "2 -> um curso\n";
    cout << "3 -> um ano\n";
    cout << "4 -> Voltar para tras\n";

    cin >> input;

    if(input == "1"){
        string input_2;
        cout << "Introduza a UC, pressione 'e' para voltar para tras\n";
        cin >> input;

        if(input == "e"){
            analise_consultar_alunos(s, c, p, q, u);
        }

        cout << "Introduza a turma, pressione 'e' para voltar para tras\n";
        cin >> input_2;

        if(input_2 == "e"){
            analise_consultar_alunos(s, c, p, q, u);
        }
        else{
            alunos_turma(s, input, input_2);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            analise_consultar_alunos(s, c, p, q, u);

        }
    }
    else if(input == "2"){
        cout << "Introduza o curso que deseja procurar,\ne pressione 'e' para voltar para trás\n";
        cin >> input;

        if (input == "e") {
            analise_consultar_alunos(s, c, p, q, u);
        }

        else {
            alunos_curso(s, input);
            cout << "\n------Operacao finalizada com sucesso------\n";
            terminal_analise(s, c, p, q, u);
        }
    }

    else if(input == "3"){
        cout << "Introduza o ano que deseja procurar,\ne pressione 'e' para voltar para tras\n";
        cin >> input;

        if(input == "e"){
            analise_consultar_alunos(s, c, p, q, u);
        }

        else{
            alunos_ano(s, stoi(input));
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s, c, p, q, u);

        }

    }
    else if(input == "4"){
        terminal_analise(s, c, p, q, u);
    }
    else{
        cout << "Input invalido\n";
        analise_consultar_alunos(s, c, p, q, u);
    }
}

void terminal_ocupacao_ano(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    std::string input;

    cout << "\nDeseja saber a ocupaçao dos anos por:\n";

    cout << "1 -> Por ano\n";
    cout << "2 -> Por valor\n";
    cout << "3 -> Voltar para tras\n";

    cin >> input;

    if(input == "1"){
        cout << "\nPor ordem:\n";

        cout << "1 -> Ordem ascendente\n";
        cout << "2 -> Ordem descendente\n";
        cout << "3 -> Voltar para trás\n";

        cin >> input;

        if(input == "1"){
            ocupacao_ano_by_ano(s, true);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s,c,p,q,u);

        }
        else if(input == "2"){
            ocupacao_ano_by_ano(s, false);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s,c,p,q,u);
        }
        else if(input == "3"){
            terminal_ocupacao_ano(s, c, p, q, u);
        }
        else{
            cout << "Input invalido\n";
            terminal_ocupacao_ano(s, c, p, q, u);
        }
    }
    else if(input == "2"){
        cout << "\nPor ordem:\n";

        cout << "1 -> Ordem ascendente\n";
        cout << "2 -> Ordem descendente\n";
        cout << "3 -> Voltar para trás\n";

        cin >> input;

        if(input == "1"){
            ocupacao_ano_value(s, true);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s,c,p,q,u);
        }
        else if(input == "2"){
            ocupacao_ano_value(s, false);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s,c,p,q,u);
        }
        else if(input == "3"){
            terminal_ocupacao_ano(s, c, p, q, u);
        }
        else{
            cout << "Input invalido\n";
            terminal_ocupacao_ano(s, c, p, q, u);
        }
    }
    else if(input == "3"){
        terminal_analise(s, c, p, q, u);
    }
    else{
        cout << "Input invalido\n";
        terminal_ocupacao_ano(s, c, p, q, u);
    }
}

void terminal_ocupacao_uc(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    std::string input;

    cout << "\nDeseja saber: \n";
    cout << "1 -> A ocupacao de todas UC's\n";
    cout << "2 -> As UC's com maior ocupacao\n";
    cout << "3 -> Voltar para tras\n";

    cin >> input;

    if(input == "1"){
        cout << "\nDeseja procurar por:\n";
        cout << "1 -> valor\n";
        cout << "2 -> UC\n";
        cout << "3 -> Voltar para tras\n";

        cin >> input;

        if(input == "1"){
            cout << "\nDeseja procurar por:\n";
            cout << "1 -> ordem ascendente\n";
            cout << "2 -> ordem descendente\n";
            cout << "3 -> Voltar para tras\n";

            cin >> input;

            if(input == "1"){
                cout << "\nOcupacao das UC's por valor e ordem ascendente:\n";
                uc_ocupacao_by_value(s, p, true);
                cout << "\n--------Operacao finalizada com sucesso--------\n\n";
                terminal_analise(s, c, p, q, u);
            }
            else if(input == "2"){
                cout << "\nOcupacao das UC's por valor e ordem descendente:\n";
                uc_ocupacao_by_value(s, p, false);
                cout << "\n--------Operacao finalizada com sucesso--------\n\n";
                terminal_analise(s, c, p, q, u);
            }
            else if(input == "3"){
                terminal_ocupacao_uc(s, c, p, q, u);
            }
            else{
                cout << "Input invalido\n";
                terminal_ocupacao_uc(s, c, p, q, u);
            }
        }
        else if(input == "2"){
            cout << "\nDeseja procurar por:\n";
            cout << "1 -> ordem ascendente\n";
            cout << "2 -> ordem descendente\n";
            cout << "3 -> Voltar para tras\n";

            cin >> input;

            if(input == "1"){
                cout << "\nOcupacao das UC's por UC e ordem ascendente:\n";
                uc_ocupacao_by_uc(s, p, true);
                cout << "\n--------Operacao finalizada com sucesso--------\n\n";
                terminal_analise(s, c, p, q, u);
            }
            else if(input == "2"){
                cout << "\nOcupacao das UC's por UC e ordem descendente:\n";
                uc_ocupacao_by_uc(s, p, false);
                cout << "\n--------Operacao finalizada com sucesso--------\n\n";
                terminal_analise(s, c, p, q, u);
            }
            else if(input == "3"){
                terminal_ocupacao_uc(s, c, p, q, u);
            }
            else{
                cout << "Input invalido\n";
                terminal_ocupacao_uc(s, c, p, q, u);
            }

        }
        else if(input == "3"){
            terminal_analise(s, c, p, q, u);
        }
        else{
            cout << "Input invalido\n";
            terminal_ocupacao_uc(s, c, p, q, u);
        }

    }
    else if(input == "2"){
        cout << "\nAs tres UC's com mais ocupacao sao:\n";
        consultar_ocupacao_uc_maior(s, p);
        cout << "\n--------Operacao finalizada com sucesso--------\n\n";
        terminal_analise(s, c, p, q, u);
    }

    else if(input == "3"){
        terminal_analise(s, c, p, q, u);
    }
    else{
        cout << "Input invalido\n";
        terminal_ocupacao_uc(s, c, p, q, u);
    }
}

void terminal_ocupacao_turma(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    std::string input;

    cout << "\nDeseja procurar por:\n";
    cout << "1 -> valor\n";
    cout << "2 -> UC\n";
    cout << "3 -> turma\n";
    cout << "4 -> Voltar para tras\n";

    cin >> input;

    if(input == "1"){
        cout << "\nDeseja procurar por:\n";
        cout << "1 -> ordem ascendente\n";
        cout << "2 -> ordem descendente\n";
        cout << "3 -> Voltar para tras\n";

        cin >> input;

        if(input == "1"){
            cout << "\nOcupacao das turmas por valor e ordem ascendente:\n";
            consultar_ocupacao_turmas_by_value(s, p, true);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s, c, p, q, u);

        }
        else if(input == "2"){
            cout << "\nOcupacao das turmas por valor e ordem descendente:\n";
            consultar_ocupacao_turmas_by_value(s, p, false);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s, c, p, q, u);

        }
        else if(input == "3"){
            terminal_ocupacao_uc(s, c, p, q, u);
        }
        else{
            cout << "Input invalido\n";
            terminal_ocupacao_uc(s, c, p, q, u);
        }
    }
    else if(input == "2"){
        cout << "\nDeseja procurar por:\n";
        cout << "1 -> ordem ascendente\n";
        cout << "2 -> ordem descendente\n";
        cout << "3 -> Voltar para tras\n";

        cin >> input;

        if(input == "1"){
            cout << "\nOcupacao das turmas por UC e ordem ascendente:\n";
            consultar_ocupacao_turmas_by_uc(s, p, true);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s, c, p, q, u);
        }
        else if(input == "2"){
            cout << "\nOcupacao das turmas por UC e ordem descendente:\n";
            consultar_ocupacao_turmas_by_uc(s, p, false);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s, c, p, q, u);
        }
        else if(input == "3"){
            terminal_ocupacao_uc(s, c, p, q, u);
        }
        else{
            cout << "Input invalido\n";
            terminal_ocupacao_uc(s, c, p, q, u);
        }
    }
    else if(input == "3"){
        cout << "\nDeseja procurar por:\n";
        cout << "1 -> ordem ascendente\n";
        cout << "2 -> ordem descendente\n";
        cout << "3 -> Voltar para tras\n";

        cin >> input;

        if(input == "1"){
            cout << "\nOcupacao das turmas por turma e ordem ascendente:\n";
            consultar_ocupacao_turmas_by_turma(s, p, true);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s, c, p, q, u);

        }
        else if(input == "2"){
            cout << "\nOcupacao das turmas por turma e ordem descendente:\n";
            consultar_ocupacao_turmas_by_turma(s, p, false);
            cout << "\n--------Operacao finalizada com sucesso--------\n\n";
            terminal_analise(s, c, p, q, u);

        }
        else if(input == "3"){
            terminal_ocupacao_uc(s, c, p, q, u);
        }
        else{
            cout << "Input invalido\n";
            terminal_ocupacao_uc(s, c, p, q, u);
        }
    }

    else if(input == "4"){
        terminal_analise(s, c, p, q, u);
    }
    else{
        cout << "Input invalido\n";
        terminal_ocupacao_turma(s, c, p, q, u);
    }
}

void terminal_manipular(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    string input;

    cout << "----------------------Menu de manipulacao----------------------\n\n";
    cout << "Selecione a opcao que deseja:\n";

    cout << "1 -> Adicionar tarefa\n";
    cout << "2 -> Ver tarefas pendentes\n";
    cout << "3 -> Processar tarefa\n";
    cout << "4 -> Ver historico de tarefas\n";
    cout << "5 -> Refazer uma tarefa\n";
    cout << "6 -> Exit\n";

    cin >> input;

    if(input == "1"){
        terminal_adicionar_tarefa(s, c, p, q, u);
        cout << "\nTarefa adicionada com sucesso\n";
        cout << "\n--------Operacao finalizada com sucesso--------\n\n";
        terminal_manipular(s, c, p, q, u);
    }
    else if(input == "2"){
        terminal_ver_tarefas(s,c,p,q,u, false);
        cout << "\n--------Operacao finalizada com sucesso--------\n\n";
        terminal_manipular(s,c,p,q, u);
    }
    else if(input == "3"){
        terminal_processar_pedido(s,c,p,q,u);
        cout << "\n--------Operacao finalizada com sucesso--------\n\n";
        terminal_manipular(s,c,p,q,u);
    }
    else if(input == "4"){
        terminal_ver_historico(s,c,p,q,u,false);
        cout << "\n--------Operacao finalizada com sucesso--------\n\n";
        terminal_manipular(s,c,p,q,u);
    }
    else if(input == "5"){
        terminal_processar_undo(s,c,p,q,u);
        cout << "\n--------Operacao finalizada com sucesso--------\n\n";
        terminal_manipular(s,c,p,q,u);
    }
    else if(input == "6"){
        terminal_inicialize(s,c,p,q,u);
    }
    else{
        cout << "Input inválido\n";
        terminal_manipular(s,c,p,q,u);
    }
}

void terminal_adicionar_tarefa(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    string input;

    cout << "Introduza o iD do aluno,\nselecione 'e' para voltar para tras:\n";

    cin >> input;

    if(input == "e"){
        terminal_manipular(s,c,p,q,u);
    }

    string iD = input;

    cout << "Selecione a opcao que deseja:\n";

    cout << "1 -> Adicionar uma UC\n";
    cout << "2 -> Remover uma UC\n";
    cout << "3 -> Trocar uma UC\n";
    cout << "4 -> Voltar para tras\n";

    cin >> input;

    if(input == "1") {
        int type = stoi(input);

        cout << "\nIntroduza a UC que deseja adicionar,\nselecione 'e' para voltar para tras:\n";
        cin >> input;

        if(input == "e"){
            terminal_manipular(s,c,p,q,u);
        }

        string uc = input;

        cout << "\nIntroduza a Classe que deseja adicionar,\nselecione 'e' para voltar para tras:\n";
        cin >> input;

        if(input == "e"){
            terminal_manipular(s,c,p,q,u);
        }

        string classe = input;

        Student student = Student(iD);
        auto it = s.setStudents.find(student);

        task tarefa = task(type, *it, pairUcClasses(uc, classe));

        q.insert_task(tarefa);

    }
    else if(input == "2"){
        int type = stoi(input);

        cout << "\nIntroduza a UC que deseja remover,\nselecione 'e' para voltar para tras:\n";
        cin >> input;

        if(input == "e"){
            terminal_manipular(s,c,p,q,u);
        }

        string uc = input;

        cout << "\nIntroduza a Classe que deseja remover,\nselecione 'e' para voltar para tras:\n";
        cin >> input;

        if(input == "e"){
            terminal_manipular(s,c,p,q,u);
        }

        string classe = input;

        Student student = Student(iD);
        auto it = s.setStudents.find(student);

        task tarefa = task(type, *it, pairUcClasses(uc, classe));

        q.insert_task(tarefa);

    }
    else if(input == "3"){
        int type = stoi(input);

        cout << "\nIntroduza a UC que deseja mudar de,\nselecione 'e' para voltar para tras:\n";
        cin >> input;

        if(input == "e"){
            terminal_manipular(s,c,p,q,u);
        }

        string uc_1 = input;

        cout << "\nIntroduza a Classe que deseja mudar de,\nselecione 'e' para voltar para tras:\n";
        cin >> input;

        if(input == "e"){
            terminal_manipular(s,c,p,q,u);
        }

        string classe_1 = input;

        cout << "\nIntroduza a UC que deseja mudar para,\nselecione 'e' para voltar para tras:\n";
        cin >> input;

        if(input == "e"){
            terminal_manipular(s,c,p,q,u);
        }

        string uc_2 = input;

        cout << "\nIntroduza a Classe que deseja mudar para,\nselecione 'e' para voltar para tras:\n";
        cin >> input;

        if(input == "e"){
            terminal_manipular(s,c,p,q,u);
        }

        string classe_2 = input;

        Student student = Student(iD);
        auto it = s.setStudents.find(student);

        task tarefa = task(type, *it, pairUcClasses(uc_1, classe_1), pairUcClasses(uc_2, classe_2));

        q.insert_task(tarefa);

    }

    else if(input == "4"){
        terminal_manipular(s,c,p,q,u);
    }
    else{
        cout << "Input inválido\n";
        terminal_adicionar_tarefa(s,c,p,q,u);
    }

}

void terminal_ver_tarefas(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u, bool flag){

    if(q.q_task.empty()){
        cout <<"\nNao existe nenhuma tarefa\n";
    }
    else{
        if(flag){
            cout << "\nA proxima tarefa a ser efetuada sera:\n";
        }
        else{
            cout << "\nIrao ser efetuadas as seguintes tarefas:\n";
        }
    }

    queueTask print;
    print.q_task = q.q_task;


    while(!print.q_task.empty()){

        cout << "\nID: " << print.q_task.front().get_student().get_idNum() << "\n";
        cout << "Nome: " << print.q_task.front().get_student().get_name() << "\n";

        if(print.q_task.front().get_type() == 1){
            cout << "Deseja adicionar a UC " << print.q_task.front().get_pair_1().get_uc() <<" com turma "<< print.q_task.front().get_pair_1().get_classe() <<"\n";
        }
        else if(print.q_task.front().get_type() == 2){
            cout << "Deseja remover a UC " << print.q_task.front().get_pair_1().get_uc() <<" com turma "<< print.q_task.front().get_pair_1().get_classe() <<"\n";
        } else{
            cout << "Deseja mudar a UC " << print.q_task.front().get_pair_1().get_uc() <<" com turma "<< print.q_task.front().get_pair_1().get_classe() <<"\n";
            cout << "Para a UC " << print.q_task.front().get_pair_2().get_uc() <<" com turma "<< print.q_task.front().get_pair_2().get_classe() <<"\n";
        }
        if(flag){
            break;
        }

        print.q_task.pop();
    }
}

void terminal_processar_pedido(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u) {

    if (q.q_task.empty()) {
        cout << "\nNao existem tarefas para ser realizadas\n";
        terminal_manipular(s,c,p,q,u);
    }
    else {

        string input;
        terminal_ver_tarefas(s, c, p, q, u, true);

        cout << "\nDeseja processar a tarefa:\n";

        cout << "1 - Sim\n";
        cout << "2 - Nao\n";

        cin >> input;

        if (input == "1") {
            task tarefa = q.q_task.front();

            if (tarefa.get_type() != 2) {
                int i = teste_tarefa(s, c, p, tarefa);

                if (i == 1) {
                    cout << "\nErro a processar processar a tarefa\n";
                    q.q_task.pop();
                    cout << "O aluno com iD " << tarefa.get_student().get_idNum()
                        << " ja atingiu o limite maximo de 7 UC's\n";
                    terminal_processar_pedido(s, c, p, q, u);

                } else if (i == 2) {
                    cout << "\nErro a processar processar a tarefa\n";
                    q.q_task.pop();
                    cout << "A UC " << tarefa.get_pair_1().get_uc() << " e turma " << tarefa.get_pair_1().get_classe()
                        << " atingiu o CAP de 30 alunos\n";
                    terminal_processar_pedido(s, c, p, q, u);

                } else if (i == 3) {
                    cout << "\nErro a processar processar a tarefa\n";
                    q.q_task.pop();
                    cout << "A UC " << tarefa.get_pair_2().get_uc() << " e turma " << tarefa.get_pair_2().get_classe()
                        << " atingiu o CAP de 30 alunos\n";
                    terminal_processar_pedido(s, c, p, q, u);

                } else if (i == 4) {
                    cout << "\nErro a processar processar a tarefa\n";
                    q.q_task.pop();
                    cout << "O aluno com iD " << tarefa.get_student().get_idNum() << " ja encontra-se inscrito na UC "
                        << tarefa.get_pair_1().get_uc() << "\n";
                    terminal_processar_pedido(s, c, p, q, u);

                } else if (i == 5) {
                    cout << "\nErro a processar processar a tarefa\n";
                    q.q_task.pop();
                    cout << "O aluno com iD " << tarefa.get_student().get_idNum() << " ja encontra-se inscrito na UC "
                        << tarefa.get_pair_2().get_uc() << "\n";
                    terminal_processar_pedido(s, c, p, q, u);

                } else if (i == 6) {
                    cout << "\nErro a processar processar a tarefa\n";
                    q.q_task.pop();
                    cout << "A UC " << tarefa.get_pair_1().get_uc() << " e turma " << tarefa.get_pair_1().get_classe()
                        << " irá sobrepor o horario do aluno com iD " << tarefa.get_student().get_idNum() << "\n";
                    terminal_processar_pedido(s, c, p, q, u);

                } else if (i == 7) {
                    cout << "\nErro a processar processar a tarefa\n";
                    q.q_task.pop();
                    cout << "A UC " << tarefa.get_pair_2().get_uc() << " e turma " << tarefa.get_pair_2().get_classe()
                        << " irá sobrepor o horario do aluno com iD " << tarefa.get_student().get_idNum() << "\n";
                    terminal_processar_pedido(s, c, p, q, u);

                } else if (i == 8) {
                    cout << "\nErro a processar processar a tarefa\n";
                    q.q_task.pop();
                    cout << "A inscricao na UC " << tarefa.get_pair_1().get_uc() << " e turma "
                         << tarefa.get_pair_1().get_classe() << " irá causar um desiquilibrio entre as turmas da cadeira\n";
                    terminal_processar_pedido(s, c, p, q, u);

                } else if (i == 9) {
                    cout << "\nErro a processar processar a tarefa\n";
                    q.q_task.pop();
                    cout << "A inscricao na UC " << tarefa.get_pair_2().get_uc() << " e turma "
                         << tarefa.get_pair_2().get_classe() << " irá causar um desiquilibrio entre as turmas da cadeira\n";
                    terminal_processar_pedido(s, c, p, q, u);

                } else {
                    cout << "\nA tarefa foi aceite com sucesso\n";

                    if (tarefa.get_type() == 1) {
                        processar_add(s, c, p, q, u, tarefa, true);
                        cout << "\nA tarefa realizada com sucesso\n";
                        terminal_processar_pedido(s, c, p, q, u);
                    } else {
                        processar_switch(s, c, p, q, u, tarefa, true);
                        cout << "\nA tarefa realizada com sucesso\n";
                        terminal_processar_pedido(s, c, p, q, u);
                    }

                }
            } else {
                cout << "\nA tarefa foi aceite com sucesso\n";
                processar_remove(s, c, p, q, u, tarefa, true);
                cout << "\nA tarefa realizada com sucesso\n";
                terminal_processar_pedido(s, c, p, q, u);
            }
        } else if (input == "2") {
            terminal_manipular(s, c, p, q, u);
        } else {
            cout << "Input inválido\n";
            terminal_processar_pedido(s, c, p, q, u);
        }
    }
}

void terminal_ver_historico(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u, bool flag){
    stackUndo new_queue;
    new_queue.stack_task = u.stack_task;

    if(u.stack_task.empty()){
        cout << "\nNao existe nenhuma tarefa no historico\n";
    }
    else{
        if(flag){
            cout << "\nA ultima alteracao foi:\n";
        }
        else{
            cout << "\nHistórico das alteracoes da mais recente para a mais antiga\n";
        }
    }

    while(!new_queue.stack_task.empty()){
        if(new_queue.stack_task.top().get_type() == 1){
            cout << "A UC " << new_queue.stack_task.top().get_pair_1().get_uc() << " e turma " <<
            new_queue.stack_task.top().get_pair_1().get_classe() << " foi removida ao aluno com iD "
            << new_queue.stack_task.top().get_student().get_idNum() << "\n";
        }
        else if(new_queue.stack_task.top().get_type() == 2){
            cout << "A UC " << new_queue.stack_task.top().get_pair_1().get_uc() << " e turma " <<
                 new_queue.stack_task.top().get_pair_1().get_classe() << " foi adicionada ao aluno com iD "
                 << new_queue.stack_task.top().get_student().get_idNum() << "\n";
        }
        else{
            cout << "A UC " << new_queue.stack_task.top().get_pair_2().get_uc() << " e turma " <<
                 new_queue.stack_task.top().get_pair_2().get_classe() << "\nfoi trocada com a UC "<<
                 new_queue.stack_task.top().get_pair_1().get_uc() << " e turma " << new_queue.stack_task.top().get_pair_1().get_classe()
                 << " ao aluno com iD "<< new_queue.stack_task.top().get_student().get_idNum() << "\n";
        }

        if(flag){
            break;
        }

        new_queue.stack_task.pop();
    }

}

void terminal_processar_undo(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){
    if(u.stack_task.empty()){
        cout << "\nNao existem nehuma tarfera no historico\n";
        terminal_manipular(s,c,p,q,u);
    }
    else{
        string input;
        terminal_ver_historico(s,c,p,q,u,true);

        cout << "\nDeseja refazer a tarefa:\n";
        cout <<"1 -> Sim\n";
        cout <<"2 -> Nao\n";

        cin >> input;

        if(input == "1"){
            task tarefa = u.stack_task.top();
            processar_undo(s,c,p,q,u,tarefa);

            cout << "\nA tarefa realizada com sucesso\n";
            terminal_processar_undo(s,c,p,q,u);

        }
        else if(input == "2"){
            terminal_manipular(s,c,p,q,u);
        }
        else{
            cout << "Input inválido\n";
            terminal_processar_pedido(s,c,p,q,u);
        }
    }
}

void ambiente_teste(setStudents& s, listClasses& c, listPairUcClass& p, queueTask& q, stackUndo& u){

    cout << "------------------Ambiente de Teste------------------\n\n";

    Student student_1 = Student("202025232");
    //Student student_2 = Student("202047842");

    pairUcClasses p_1 = pairUcClasses("L.EIC002", "1LEIC05");
    pairUcClasses p_2 = pairUcClasses("L.EIC002", "1LEIC07");

    auto it_1 = s.setStudents.find(student_1);
    //auto it_2 = s.setStudents.find(student_2);

    schedule sch_1 = it_1->criar_horario(c);
    //schedule sch_2 = it_2->criar_horario(c);

    task tarefa_1 = task(3, *it_1, p_1, p_2);

    int i = teste_tarefa(s,c,p,tarefa_1);


    auto it_3 = s.setStudents.find(student_1);

    cout << "Finish\n";
}