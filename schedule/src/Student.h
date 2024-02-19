//
// Created by pchmelo on 10-10-2023.
//

#include "vector"
#include "string"
#include "iostream"
#include "set"
#include "sstream"
#include "fstream"
#include "Classes.h"
#include "algorithm"


#ifndef PROJETO_1_STUDENT_H
#define PROJETO_1_STUDENT_H

struct year;


class Student{
    private:
        std::string name;
        std::string idNum;
        int ano;
        std::string curso;
        //pairUcClasses std_uc;
    public:
        std::vector<pairUcClasses> std_uc;

        //Constructors
        Student();
        Student(std::string idNum);
        Student(std::string idNum, std::string name, std::string uc, std::string classe, int ano, std::string curso);

        //Getters
        std::string get_name() const;
        std::string get_idNum() const;
        std::string getCurso() const;

        std::vector<pairUcClasses> get_pairUcClasses() const;

    /**
    * Esta função permite imprimir os dados acerca de um estudante
    * Complexidade: O(n)
    * @return
    */
        void print() const;

    /**
    * Esta função permite imprimir o nome de um estudante de forma personalizada
    * Complexidade: O(1)
    */
        void print_name() const;
        //pairUcClasses get_paiUcClasses();

    /**
    * Esta função permite inserir um novo par à coleção std_uc (UC's e turmas associadas a cada estudante)
    * Complexidade: O(1)
    * @param uc Nova UC do estudante
    * @param classe Nova turma do estudante
    * @param ano Novo ano do estudante
    */
        void insert_pair(std::string uc, std::string classe, int ano);

    /**
    * Este operador é usado pela coleção setStudents de forma a ordenar os estudantes.
    * Complexidade: O(1)
    * @param student Student de comparação
    * @return true se o ID do estudante atual for menor do que o id de student. Senão, retorna false.
    */
        bool operator < (const Student& student) const;
        //bool operator < (const std::string& id) const;

        //bool operator == (const Student& student) const;

    /**
    * Esta função permite comparar encontrar estudantes no conjunto apenas pesquisando pelo seu nome
    * Complexidade: O(1)
    * @param name Nome do estudante
    * @return true se os atributos name forem iguais. Senão, retorna false.
    */
        bool operator == (const std::string& name) const;

       // bool operator () (const std::string& id) const;

        //horario

    /**
    * Esta função permite criar um horário através da lista de aulas de um estudante
    * Complexidade: O(n * log(n))
    * @param c lista de aulas de base para o horário
    * @return o horário de um estudante.
    */
        schedule criar_horario(listClasses& c) const;

    /**
    * Esta função permite imprimir o horário de um estudante
    * @param c Aulas do horário
    * @return
    */
        void print_horario(listClasses& c) const;

    /**
    * Esta função verifica se um estudante pertence a uma certa turma
    * Complexidade: O(n)
    * @param turma Turma a que o estudante pode pertencer
    * @return true se o estudante pertencer à turma. Senão, retorna false.
    */
        bool student_pretence_class(pairUcClasses turma) const;

    /**
    * Esta função verifica se um estudante pertence a um certo ano
    * Complexidade: O(n)
    * @param ano Ano a que o estudante pode pertencer
    * @return true se o estudante pertencer ao ano. Senão, retorna false.
    */
        bool student_pertence_ano(int ano) const;

    /**
    * Esta função verifica se um estudante pertence a um certo curso
    * Complexidade: O(1)
    * @param curso Curso a que o estudante pode pertencer
    * @return true se o estudante pertencer ao curso. Senão, retorna false.
    */
        bool student_pertence_curso(std::string curso) const;

    /**
    * Esta função verifica se um estudantes está inscrito em pelo menos n UC's
    * Complexidade: O(1)
    * @param n Número mínimo de UC's de um estudante
    * @return true se um certo estudante estiver inscrito em n ou mais cadeiras.
    */
        bool student_nUc(int n) const;

};

class setStudents{
    public:
        std::set<Student> setStudents;

    /**
    * Esta função permite inserir um novo estudantes na coleção setStudents
    * Complexidade: O(1)
    * @param student Novo estudante a ser inserido
    * @return
    */
        void insert_student(Student student);

    /**
    * Esta função permite ler e retirar dados do ficheiro students_classes.csv
    * Complexidade: O(n * log(n))
    */
        void read_file();

    /**
    * Esta função procura estudantes por classe
    * Complexidade: O(n)
    * @param turma Turma a pesquisar
    * @return uma coleção com todos os estudantes que pertencem a uma certa turma.
    */
        std::vector<Student> searchClass(pairUcClasses turma) const;

    /**
    * Esta função procura estudantes por ano
    * Complexidade: O(n)
    * @param ano Ano a pesquisar
    * @return uma coleção com todos os estudantes que pertencem a um certo ano.
    */
        year searchYear(int ano) const;

    /**
    * Esta função procura estudantes por curso
    * Complexidade: O(n)
    * @param curso Curso a pesquisar
    * @return uma coleção com todos os estudantes que pertencem a um certo curso.
    */
        std::vector<Student> searchCourse(std::string curso) const;

    /**
    * Esta função procura estudantes por número de UC's inscritas
    * Complexidade: O(1)
    * @param n Número mínimo de UC's inscritas dos estudantes
    * @return uma coleção com todos os estudantes que estão inscritos em n ou mais cadeiras.
    */
        std::vector<Student> search_nUc(int n) const;
};

struct uc_students{
    std::string uc;
    std::vector<Student> v_s;

    /**
     * Este operador permite igualar dois objetos do tipo uc_students num contexto de procura
     * Complexidade: O(1)
     * @param t uc_students de comparação
     * @return true se a uc atual for igual à uc associada a t. Senão, retorna false.
     */
    bool operator == (uc_students t) const{
        return this->uc == t.uc;
    }

    /**
     * Este operador vai permitir ordenar os estudantes de uma UC por valor, de forma ascendente e descendente
     * Complexidade: O(1)
     * @param t uc_students de comparação
     * @return true se o número de estudantes na UC atual for menor do que os da uc_students t. Senão, retorna false.
     */
    bool operator < (uc_students t) const{
        return this->v_s.size() < t.v_s.size();
    }

    /**
     * Esta função permite acrescentar novos estudantes a uma certa UC
     * Complexidade: O(1)
     * @param t Novos estudantes de uma UC
     * @return
     */
    void insert_v_s(std::vector<Student> t) {
        v_s.insert(v_s.end(), t.begin(), t.end());
    }
};

struct year{
    int ano;
    std::vector<Student> v_s;

    /**
     * Esta função permite ordenar os anos de forma ascendente/descendente
     * Complexidade: O(1)
     */
    bool operator < (year y){
        return this->v_s.size() < y.v_s.size();
    }
};

struct turmas{
    pairUcClasses turma;
    std::vector<Student> v_s;

    /**
    * Este operador permite comparar dois objetos do tipo turmas para fins de procura
    * Complexidade: O(1)
    * @param t "turmas" de comparação
    * @return true se o pairUcClasses turma do objeto associado ao this for igual ao do parãmetro. Senão, retorna false.
    */
    bool operator == (turmas t) const{
        return this->turma.get_uc() == t.turma.get_uc() && this->turma.get_classe() == t.turma.get_classe();
    }

    /**
     * Esta função permite procurar os estudantes de uma turma colocando apenas a UC e a turma como inputs
     * Complexidade: O(1)
     * @param t pairUcClasses do qual queremos saber os estudantes
     * @return true se os pairUcClasses forem iguais. Senão, retorna false.
     */
    bool operator == (pairUcClasses t) const{
        return this->turma.get_uc() == t.get_uc() && this->turma.get_classe() == t.get_classe();
    }

    /**
     * Este operador vai permitir ordenar as turmas por valor, de forma ascendente e descendente
     * Complexidade: O(1)
     * @param t "turmas" de comparação
     * @return true se a turma atual tiver menos estudantes que a turma t. Senão, retorna false.
     */
    bool operator < (turmas t) const{
        return this->v_s.size() < t.v_s.size();
    }
};


#endif //PROJETO_1_STUDENT_H
