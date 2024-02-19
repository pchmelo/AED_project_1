#include "Student.h"
#include "pairUcClasses.h"
#include "Classes.h"
#include "terminal.h"


int main(){
    setStudents s;
    s.read_file();

    listClasses c;
    c.read_file();

    listPairUcClass p;
    p.read_file();

    queueTask q;
    q.read_file(s);

    stackUndo u;
    u.read_file(s);


    terminal_inicialize(s, c, p, q, u);

    atualizar_alunos(s);
    atualizar_tarefas(q);
    atualizar_historico(u);

    std::cout << "Operacao finalizada\n";
    return 0;
}


