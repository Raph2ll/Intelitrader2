#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Oferta {
    string posicao;
    double valor;
    int quantidade;
};

vector<Oferta> ofertas;

bool verificarRepeticao(const string& posicao) {
    for (const Oferta& oferta : ofertas) {
        if (oferta.posicao == posicao) {
            return true;
        }
    }
    return false;
}

void inserir(string posicao) {
    if (verificarRepeticao(posicao)) {
        cout << "Ação repetida. Não será inserida novamente." << endl;
        return; 
    }

    Oferta novaOferta;
    novaOferta.posicao = posicao;

    cout << "Digite o valor da sua oferta. [0.0]" << endl;

    while (true) {
        try {
            string userInput;
            getline(cin, userInput);
            novaOferta.valor = stod(userInput);
            if (novaOferta.valor < 0.0) {
                cout << "Digite um valor maior que: 0.0" << endl;
            } else {
                break;
            }
        } catch (const invalid_argument& e) {
            cerr << "Erro de conversão: \nDigite um valor válido." << endl;
        }
    }

    cout << "Digite a quantidade da oferta. [0]" << endl;

    while (true) {
        try {
            string userInput;
            getline(cin, userInput);
            novaOferta.quantidade = stoi(userInput);
            if (novaOferta.quantidade < 0) {
                cout << "Digite um valor maior que: 0" << endl;
            } else {
                break;
            }
        } catch (const invalid_argument& e) {
            cerr << "Erro de conversão: \nDigite um valor válido." << endl;
        }
    }
    cout << posicao << "," << 0 << "," << novaOferta.valor << "," << novaOferta.quantidade << endl;
    ofertas.push_back(novaOferta);
}
void modificar(const string& posicao) {
    double novoValor;
    int novaQuantidade;

    if(!verificarRepeticao(posicao)) {
        cout << "Oferta com posição " << posicao << " não encontrada." << endl;
    return;
    }

    cout << "Digite o valor da sua oferta. [0.0]" << endl;

    while (true) {
        try {
            string userInput;
            getline(cin, userInput);
            novoValor = stod(userInput);
            if (novoValor < 0) {
                cout << "Digite um valor maior que: 0" << endl;
            } else {
                break;
            }
        } catch (const invalid_argument& e) {
            cerr << "Erro de conversão: \nDigite um valor válido." << endl;
        }
    }

    cout << "Digite a quantidade da oferta. [0]" << endl;

    while (true) {
        try {
            string userInput;
            getline(cin, userInput);
            novaQuantidade = stoi(userInput);
            if (novaQuantidade < 0) {
                cout << "Digite um valor maior que: 0" << endl;
            } else {
                break;
            }
        } catch (const invalid_argument& e) {
            cerr << "Erro de conversão: \nDigite um valor válido." << endl;
        }
    }

    for (auto it = ofertas.begin(); it != ofertas.end(); ++it) {
        if (it->posicao == posicao) {
            it->valor = novoValor;
            it->quantidade = novaQuantidade;
                cout << "Oferta com posição " << posicao << " modificada com sucesso." << endl;
                cout << posicao << "," << 1 << "," << novoValor << "," << novaQuantidade << endl;
            return;
        }
    }


}
void deletar(string posicao) {
    if (!verificarRepeticao(posicao)) {
        cout << "Oferta não encontrada." << endl;
        return; 
    }
    for (auto it = ofertas.begin(); it != ofertas.end();) {
        if (it->posicao == posicao) {
            it = ofertas.erase(it); // Após a remoção, `it` é automaticamente ajustado
            cout << "Oferta com ação " << posicao << " deletada com sucesso." << endl;
            cout << posicao << "," << 2 << "," << it->valor << "," << it->quantidade << endl;
        } else {
            ++it;
        }
    }

    if (ofertas.empty()) {
        cout << "Lista de ofertas vazia." << endl;
    }
}

void imprimirOfertas() {
    if (ofertas.empty()) {
        cout << "Lista de ofertas vazia." << endl;
        return;
    }

    cout << "Lista de ofertas:" << endl;
    for (const Oferta& oferta : ofertas) {
        cout << oferta.posicao << "," << oferta.valor << "," << oferta.quantidade << endl;
    }
}

int main() {
    cout << "Bem-vindo ao livro de ofertas." << endl;
    
    while (true) {
        int numero = 0;
        string ret = "";
        string userInput = "";

        while (true) {
            cout << "Insira o número da oferta:" << endl;

            try {
                getline(cin, userInput);
                numero = stoi(userInput);

                if (numero < 0) {
                    cout << "Digite um valor maior que 0." << endl;
                } else {
                    ret += to_string(numero);
                    break;
                }
            } catch (const invalid_argument& e) {
                cerr << "Erro de conversão: \nDigite um valor válido." << endl;
            }
        }

        while (true) {
            cout << "Selecione uma das opções abaixo:\n"
                 << "0: Inserir\n"
                 << "1: Modificar\n"
                 << "2: Deletar\n"
                 << "3: Ofertas\n" << endl;

            getline(cin, userInput);
            // cout << "Você digitou: " << userInput << "\n" << endl;

            if (userInput == "0") {
                inserir(ret);
                break;
            } else if (userInput == "1") {
                modificar(ret);
                break;
            } else if (userInput == "2") {
                deletar(ret);
                break;
            } else if (userInput == "3") {
                imprimirOfertas();
                break;
            } else {
                cout << "Digite um valor válido entre [0, 1, 2, 3]." << endl;
            }
        }
    }

    return 0;
}