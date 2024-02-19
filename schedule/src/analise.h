#include "iostream"
#include "Student.h"

#ifndef PROJETO_1_ANALISE_H
#define PROJETO_1_ANALISE_H

using namespace std;

/**
 * @file
 * Esta função retorna um vetor que contém todos os estudantes de todas as UC's
 * Complexidade: O(n), onde n é a soma dos sizes das coleções envolvidas
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as suas respetivas turmas
 * @return
 */
vector<uc_students> consultar_ocupacao_uc(setStudents& s, listPairUcClass& p);


/**
 * Esta função imprime o número de estudantes de cada UC
 * Complexidade: O(n)
 * @param res Estudantes de cada UC
 */
void print_uc_ocupacao(vector<uc_students> res);

/**
* Esta função retorna um vetor que contém todas as turmas presentes na base de dados
        * Complexidade: O(n)
* @param s Conjunto de todos os estudantes
* @param p Lista de todas as UC's com as suas respetivas turmas
* @return
*/
vector<turmas> consultar_ocupacao_turmas(setStudents& s, listPairUcClass& p);

/**
 * Esta função imprime as ocupação de cada UC de cada turma
 * Complexidade: O(1)
 * @param t Vetor com todas as turmas
 */
void print_ocupacao_turmas(vector<turmas> t);

/**
 * Esta função ordena o vetor que contém os estudantes de cada UC por valor
 * Complexidade: O(n^3)
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as suas respetivas turmas
 * @param flag Ordem crescente se flag == true e decrescente se flag == false
 * @return
 */
vector<uc_students> sort_uc_by_value(setStudents s, listPairUcClass p, bool flag);


/**
 * Esta função constrói o horário de um aluno
 * Complexidade: O(n)
 * @param input ID do aluno
 * @param s Conjunto de todos os estudantes
 * @param c Lista das aulas do aluno
 */
void horario_aluno(std::string input, setStudents& s, listClasses& c){

    if(input.at(0) >= 48 && input.at(0) <= 57){
        auto it = s.setStudents.find(Student(input));
        if(it != s.setStudents.end()){
            it->print_horario(c);
        }
        else{
            cout << "\nAluno nao encontrado\n";
        }
    }
    else{

        auto it = find(s.setStudents.begin(), s.setStudents.end(), input);
        if(it != s.setStudents.end()){
            it->print_horario(c);
        }
        else{
            cout << "\nAluno nao encontrado\n";
        }
    }
}

/**
 * Esta função imprime os alunos de uma turma
 * Complexidade: O(n)
 * @param s Conjunto de todos os estudantes
 * @param uc UC-alvo
 * @param turma Turma-alvo
 */
void alunos_turma(setStudents& s, string uc, string turma){
    pairUcClasses p = {uc, turma};
    vector<Student> t = s.searchClass(p);

    if(t.size() == 0){
        cout << "Turma não encontrada\n";
    }
    else{
        auto it = t.begin();

        while (it != t.end()){
            it->print();
            it++;
            cout <<"\nNa UC " << uc << " e turma " << turma << " encontram-se " << t.size() <<" alunos\n";
        }

    }
}

/**
 * Esta função imprime os alunos de um curso
 * Complexidade: O(n)
 * @param s Conjunto de todos os estudantes
 * @param curso Curso-alvo
 */
void alunos_curso(setStudents& s, std::string curso) { //Alteração
    vector<Student> res = s.searchCourse(curso);

    if (res.empty()) {
        cout << "\nCurso nao encontrado\n";
    }
    else {
        auto it = res.begin();

        while (it != res.end()) {
            it->print();
            it++;
        }
        cout << "\nEstao inscritos " << res.size() << " alunos neste curso\n";
    }
}

/**
 * Esta função imprime os alunos de um ano
 * Complexidade: O(n)
 * @param s Conjunto de todos os estudantes
 * @param curso Curso-alvo
 */
void alunos_ano(setStudents& s, int ano){
    year res = s.searchYear(ano);
    if (res.v_s.size() == 0) {
        cout << "Ano não encontrado\n";
    }

    else {
        auto it = res.v_s.begin();

        while (it != res.v_s.end()) {
            it->print();
            it++;
            cout << "\nDo ano " << ano << " estão inscritos " << res.v_s.size() << " alunos\n";
        }
    }
}

/**
 * Esta função retorna o número de alunos inscrito em n ou mais UC's
 * Complexidade: O(n)
 * @param s Conjunto de todos os estudantes
 * @param n Número mínimo de UC's do estudante
 */
void alunos_inscritos_nUC(setStudents& s, int n){
    vector<Student> t = s.search_nUc(n);

    if(t.size() == 0){
        cout << "\nErro na operacao\n";
    }
    else{
        cout << "\nEstao inscritos " << t.size() << " alunos em pelo menos " << n << " UC's\n";
    }
}

/**
 * Esta função imprime a ocupação das turmas por UC
 * Complexidade: O(n)
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as respetivas turmas
 * @param flag Ordem crescente se flag == true e decrescente se flag == false
 */
void consultar_ocupacao_turmas_by_uc(setStudents& s, listPairUcClass& p, bool flag){
    vector<turmas> res = consultar_ocupacao_turmas(s, p);

    if(flag){
        print_ocupacao_turmas(res);
    }
    else{
        reverse(res.begin(), res.end());
        print_ocupacao_turmas(res);
    }
}

/**
 * Esta função compara 2 turmas através do seu número de alunos
 * Complexidade: O(1)
 * @param t_1 Turma 1
 * @param t_2 Turma 2
 * @return true se a t_1 tiver menos alunos
 ou a UC de t_1 vier primeiro na ordem alfabética ou a classe de t_1 vier primeiro na ordem alfabética. Senão, retorna false.
 */
bool compare_turmas_by_value(turmas t_1, turmas t_2){
    if(t_1.v_s.size() < t_2.v_s.size()){
        return true;
    }
    else if(t_1.v_s.size() == t_2.v_s.size()){
        if(t_1.turma.get_uc() < t_2.turma.get_uc()){
            return true;
        }
        else if(t_1.turma.get_uc() == t_2.turma.get_uc()){
            return t_1.turma.get_classe() < t_2.turma.get_classe();
        }
    }
    return false;
}

/**
 * Esta função imprime a ocupação das turmas ordenada pelo número de alunos de cada uma
 * Complexidade: O(n * log(n))
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as respetivas turmas
 * @param flag Ordem crescente se flag == true e decrescente se flag == false
 */
void consultar_ocupacao_turmas_by_value(setStudents& s, listPairUcClass& p, bool flag){
    vector<turmas> res = consultar_ocupacao_turmas(s, p);

    if(flag){
        sort(res.begin(), res.end(), compare_turmas_by_value);
        print_ocupacao_turmas(res);
    }
    else{
        sort(res.rbegin(), res.rend(), compare_turmas_by_value);
        print_ocupacao_turmas(res);
    }
}

/**
 * Esta função compara duas turmas pela sua ordem alfabética
 * Complexidade: O(1)
 * @param t_1 Turma 1
 * @param t_2 Turma 2
 * @return true se a UC de t_1 vier primeiro na ordem alfabética ou a classe de t_1 vier primeiro na ordem alfabética. Senão, retorna false.
 */
bool compare_turmas_by_turma(turmas t_1, turmas t_2){
    if(t_1.turma.get_classe() < t_2.turma.get_classe()){
        return true;
    }
    else if(t_1.turma.get_classe() == t_2.turma.get_classe()){
        if(t_1.turma.get_uc() < t_2.turma.get_uc()){
            return true;
        }
        else if(t_1.turma.get_uc() == t_2.turma.get_uc()){
            return t_1.v_s.size() < t_1.v_s.size();
        }
    }
    return false;
}

/**
 * Esta função imprime a ocupação das turmas ordenadas por ordem alfabética
 * Complexidade: O(n * log(n))
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as respetivas turmas
 * @param flag Ordem crescente se flag == true e decrescente se flag == false
 */
void consultar_ocupacao_turmas_by_turma(setStudents& s, listPairUcClass& p, bool flag){
    vector<turmas> res = consultar_ocupacao_turmas(s, p);

    if(flag){
        sort(res.begin(), res.end(), compare_turmas_by_turma);
        print_ocupacao_turmas(res);
    }
    else{
        sort(res.rbegin(), res.rend(), compare_turmas_by_turma);
        print_ocupacao_turmas(res);
    }
}

vector<turmas> consultar_ocupacao_turmas(setStudents& s, listPairUcClass& p){
    auto it_1 = p.list_of_pairs.begin();
    vector<Student> v;
    turmas t;
    vector<turmas> res;

    while(it_1 != p.list_of_pairs.end()){
        v = s.searchClass(*it_1);

        t.turma = pairUcClasses(it_1->get_uc(), it_1->get_classe());
        t.v_s = v;

        res.push_back(t);
        it_1 ++;
    }
    return res;
}

void print_ocupacao_turmas(vector<turmas> t){
    auto it = t.begin();

    while(it != t.end()){
        cout << "Na UC " << it->turma.get_uc() << " e Class " << it->turma.get_classe() << " tem a ocupacao de " << it->v_s.size() << " alunos\n";
        it++;

    }
}

/**
 * Esta função permite separar os estudantes por ano
 * @param s Conjunto de todos os estudantes
 * @return um vector<year> com os anos de curso (1 ao 3) e respetivos dados de cada um
 */
vector<year> ocupacao_ano(setStudents& s){
    vector<year> res;

    year ano = s.searchYear(1);
    res.push_back(ano);

    ano = s.searchYear(2);
    res.push_back(ano);

    ano = s.searchYear(3);
    res.push_back(ano);

    return res;
}

/**
 * Esta função ordena os anos
 * Ordem crescente se flag == true e decrescente se flag == false
 * Complexidade: O(n)
 * @param s Conjunto de todos os estudantes
 * @param flag Ordem crescente se flag == true e decrescente se flag == false
 */
void ocupacao_ano_value(setStudents& s, bool flag){
    vector<year> res = ocupacao_ano(s);

    if(flag){
        sort(res.begin(), res.end());

    }
    else{
        sort(res.rbegin(), res.rend());
    }

    auto it = res.begin();

    while (it != res.end()) {
        cout << "\nDo ano " << it->ano << " estão inscritos " << it->v_s.size() << " alunos\n";
        it++;
    }
}

/**
 * Esta função imprime quantos alunos estão inscritos em cada ano
 * Complexidade: O(n)
 * @param s Conjunto de todos os estudantes
 * @param flag Ordem crescente se flag == true e decrescente se flag == false
 */
void ocupacao_ano_by_ano(setStudents& s, bool flag){
    vector<year> res = ocupacao_ano(s);

    if(!flag){
        reverse(res.begin(), res.end());
    }

    auto it = res.begin();

    while (it != res.end()) {
        cout << "\nDo ano " << it->ano << " estão inscritos " << it->v_s.size() << " alunos\n";
        it++;
    }
}

/**
 * Esta função imprime as 3 UC's com maior ocupação
 * Complexidade: O(n^3)
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as respetivas turmas
 */
void consultar_ocupacao_uc_maior(setStudents& s, listPairUcClass& p){
    vector<uc_students> res = sort_uc_by_value(s, p, false);

    cout << "1º -> " << res.at(0).uc << " tem " << res.at(0).v_s.size() << " alunos\n";
    cout << "2º -> " << res.at(1).uc << " tem " << res.at(1).v_s.size() << " alunos\n";
    cout << "3º -> " << res.at(2).uc << " tem " << res.at(2).v_s.size() << " alunos\n";

}

vector<uc_students> consultar_ocupacao_uc(setStudents& s, listPairUcClass& p){
    list<classes_per_uc> t = p.list_class_per_uc();
    vector<pairUcClasses> v;
    vector<Student> v_st;
    uc_students uc_s;
    vector<uc_students> res;

    auto it = t.begin();
    bool flag = true;

    while(it != t.end()){
        v = it->convert();

        for(pairUcClasses pair : v){
            v_st = s.searchClass(pair);

            if(flag){
                uc_s.v_s = v_st;
                flag = false;
            }
            else{
                uc_s.insert_v_s(v_st);
            }
        }

        uc_s.uc = v.at(0).get_uc();
        res.push_back(uc_s);

        flag = true;
        it++;
    }

    return res;
}

/**
 * Esta função ordena o vetor que contém os estudantes de cada UC por valor
 * Complexidade: O(n^3)
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as suas respetivas turmas
 * @param flag Ordem crescente se flag == true e decrescente se flag == false
 * @return
 */
vector<uc_students> sort_uc_by_value(setStudents s, listPairUcClass p, bool flag){
    vector<uc_students> res = consultar_ocupacao_uc(s, p);
    if(flag){
        std::sort(res.begin(), res.end());
    }
    else{
        std::sort(res.rbegin(), res.rend());
    }
    return res;
}

/**
 * Esta função imprime o vetor retornado da fução sort_uc_by_value
 * Complexidade: O(n^3)
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as respetivas turmas
 * @param flag Ordem crescente se flag == true e decrescente se flag == false
 */
void uc_ocupacao_by_value(setStudents s, listPairUcClass p, bool flag){
    vector<uc_students> res = sort_uc_by_value(s, p, flag);
    print_uc_ocupacao(res);
}

/**
 * Esta função imprime quantos alunos estão inscritos em cada UC
 * Complexidade: O(n)
 * @param res Vetor de cada UC com os seus respetivos estudantes
 */
void print_uc_ocupacao(vector<uc_students> res){
    auto it = res.begin();

    while(it != res.end()){
        cout << "Na UC " << it->uc << " tem " << it->v_s.size() << " alunos\n";
        it++;
    }
}

/**
 * Esta função ordena o vetor que contém todos os estudantes de cada UC por valor
 * Ordem crescente se flag == true e decrescente se flag == false
 * Complexidade: O(n^3)
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as respetivas turmas
 * @param flag Ordem crescente se flag == true e decrescente se flag == false
 */
void uc_ocupacao_by_uc(setStudents s, listPairUcClass p, bool flag){
    vector<uc_students> res = consultar_ocupacao_uc(s, p);
    if(flag){
        print_uc_ocupacao(res);
    }
    else{
        reverse(res.begin(), res.end());
        print_uc_ocupacao(res);
    }
}

/**
 * Esta função acrescenta mais horários ao calendário sch (horários inputados, não do ficheiro)
 * Complexidade: O(n)
 * @param c Lista de aulas do novo horário
 * @param input pairUcClasses do novo horário
 * @return o vetor atualizado com novos horários
 */

//Overload
schedule criar_horario(listClasses c, pairUcClasses input){
    schedule res;
    timeLine t_l;

    t_l.p = input;

    auto it = find(c.list_of_classes.begin(), c.list_of_classes.end(), input);

    for(Horario h : it->vector_horario){
        t_l.h = Horario(h.getWeekday(), h.getStartHour(), h.getDuration(), h.getType());
        res.sch.push_back(t_l);
    }

    return res;
}

/**
 * Esta função retorna as turmas inseridas numa UC específica, uc
 * Complexidade: O(n)
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as respetivas turmas
 * @param uc UC-alvo
 * @return
 */
vector<turmas> consultar_ocupacao_uc_especifica(setStudents& s, listPairUcClass& p, string uc){
    list<classes_per_uc> t = p.list_class_per_uc();
    vector<pairUcClasses> v;
    vector<Student> v_st;
    vector<turmas> res;
    turmas turma;

    auto it_1 = find(t.begin(), t.end(), uc);
    v = it_1->convert();

    auto it_2 = v.begin();

    while (it_2 != v.end()){
        v_st = s.searchClass(*it_2);

        turma.turma = *it_2;
        turma.v_s = v_st;

        res.push_back(turma);

        it_2++;
    }

    return res;
}

/**
 * Esta função itera sobre o vetor resultante da funçáo consultar_ocupacao_uc_especifica()
 * Complexidade: O(n), em que n é o número de turmas do vetor v_turmas
 * @param s Conjunto de todos os estudantes
 * @param p Lista de todas as UC's com as respetivas turmas
 * @param uc UC-alvo
 * @return O número de alunos da turma com menos alunos
 */
int ocupacao_minima(setStudents& s, listPairUcClass& p, string uc){
    vector<turmas> v_turmas;
    v_turmas = consultar_ocupacao_uc_especifica(s, p, uc);

    int size;
    bool flag = true;

    auto it = v_turmas.begin();

    while(it != v_turmas.end()){
        if(flag){
            size = it->v_s.size();
            flag = false;
        }
        else{
            if(size > it->v_s.size()){
                size = it->v_s.size();
            }
        }
        it++;
    }

    return size;
}



#endif //PROJETO_1_ANALISE_H
