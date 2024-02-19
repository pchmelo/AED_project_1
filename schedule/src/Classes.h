//
// Created by Pedro Vieira on 24/10/2023.
//

#include "pairUcClasses.h"
#include "list"
#include "vector"
#include "algorithm"
#include "map"
#ifndef PROJETO_1_CLASSES_H
#define PROJETO_1_CLASSES_H

class Horario {
    private:
        std::string weekday, type;
        float duration, start_hour;

    public:

        //Constructors
        Horario();
        Horario(std::string weekday, float start_hour, float duration, std::string type);

        //Getters
        const std::string &getWeekday() const;
        const std::string &getType() const;
        float getStartHour() const;
        float getDuration() const;

        /**
        * Esta função imprime um objeto do tipo Classes
        * Complexidade: O(n)
        * @param
        * @return
        */
        void print() const;

    /**
    * Esta função verifica se dois horários estão sobrepostos
    * Complexidade: O(1)
    * @param h Horário de comparação
    * @return Retorna true se o horário h começar a meio do horário atual, senão retorna false.
    */
        bool sobreposicao(Horario h) const;

    /**
    * Este operador vai permitir ordenar um schedule por dias da semana e por horas de início
    * Complexidade: O(1)
    * @param horario Horário de comparação
    * @return Retorna true se o horário atual se referir a um dia semanal mais inicial
    ou se ambos se referirem ao mesmo dia, mas o atual começar mais cedo. Senão, retorna false.
    */
        bool operator<(Horario horario) const;
};

class Classes {
private:
    pairUcClasses puc;

public:
    std::vector<Horario> vector_horario;

    //Constructors
    Classes();
    Classes(pairUcClasses puc, std::string weekday, float start_hour, float duration, std::string type);

    //Getter
    const pairUcClasses &getPuc() const;

    /**
     * Este operador vai permitir encontrar um objeto da classe Classes na list_of_classes
     * Complexidade: O(1)
     * @param cl "Classes" de comparação
     * @return Retorna true se o atributo puc do objeto atual e o do parâmetro cl forem iguais
     */
    bool operator == (const Classes& cl) const;

    /**
     * Este operador permite chegar às aulas (teóricas e práticas) de uma certa UC
     * Complexidade: O(1)
     * @param pair pairUcClasses de comparação
     * @return true se os pairUcClasses (atual e cl) forem iguais. Senão, retorna false.
     */
    bool operator == (const pairUcClasses& pair) const;

    /**
     * Esta função permite inserir um horário na coleção schedule
     * Complexidade: O(1)
     * @param weekday Dia da semana
     * @param start_hour Hora de início da aula
     * @param duration Duração da aula
     * @param type Tipo de aula (T ou TP)
     * @return
     */
    void insert_horario(std::string weekday, float start_hour, float duration, std::string type);

    /**
     * Esta função permite imprimir um objeto da classe Classes
     * Complexidade: O(n)
     * @return
     */
    void print();
};

class listClasses{
    public:
        std::list<Classes> list_of_classes;

        /**
        * Esta função permite ler e retirar dados do ficheiro classes.csv
        * Complexidade: O(n * log(n))
        */
        void read_file();
};



struct timeLine {
    Horario h;
    pairUcClasses p;

    /**
     * Este operador compara dois objetos do tipo timeLine através do mesmo operador da classe Horário
     * Complexidade: O(1)
     * @param t timeLine de comparação
     * @return true se o horário atual for menor do que o horário associado à timeLine t. Senão retorna false.
     */
    bool operator <(timeLine t){
        return this->h < t.h;
    }

    /**
     * Este operador vai permitir encontrar o horário de uma certa UC
     * Complexidade: O(1)
     * @param uc uc para a qual queremos saber o horário
     * @return true se a uc atual for igual ao parâmetro uc. Senão, retorna false.
     */
    bool operator == (std::string uc){
        return this->p.get_uc() == uc;
    }

};

struct schedule{
    std::vector<timeLine> sch;

    /**
     * Esta função verifica se é possível acrescentar uma timeLine ao calendário sem que haja sobreposição
     * Complexidade: O(n)
     * @param h Possível timeLine a ser adicionada
     * @return true se a timeLine não sobrepor nenhuma das outras presentes na coleção sch. Senão, retorna false.
     */
    bool add_possible(timeLine h){
        if(h.h.getType() == "T"){
            return true;
        }

        auto it = sch.begin();

        while(it != sch.end()) {
            if (it->p.get_uc() != h.p.get_uc()) {
                if (it->h.getWeekday() == h.h.getWeekday()) {
                    if (it->h.sobreposicao(h.h)) {
                        return false;
                    }
                }
            }
            it++;
        }
        return true;
    }
};





#endif //PROJETO_1_CLASSES_H
