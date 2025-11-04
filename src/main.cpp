   #include <iostream>
   #include <string>

   using namespace std;
   

    string getNome() {
        return nome;
    }   
    int getIdade() {
        return idade;
    }
    std::string getCpf() {
        return cpf;
    }
    };

    class treinador : public pessoa
    {
    string especialidade;
    void exibirDadosTreinador() {
        exibirDados();
        cout << "Especialidade: " << especialidade << endl;
    }
};

class aluno : public pessoa{
    int matricula;
    void exibirDadosAluno() {
        exibirDados();
        cout << "Matricula: " << matricula << endl; 
    }
};