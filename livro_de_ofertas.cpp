#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

struct Oferta {
    int posicao;
    double valor;
    int quantidade;
};

vector<Oferta> ofertas;

bool verificarRepeticao(int posicao) {
    for (const Oferta& oferta : ofertas) {
        if (oferta.posicao == posicao) {
            return true;
        }
    }
    return false;
}

void inserir(int posicao, double valor, int quantidade) {
    if (verificarRepeticao(posicao)) {
        cout << "Ação repetida. Não será inserida novamente." << endl;
        return; 
    }

    Oferta novaOferta = { posicao, valor, quantidade };
    ofertas.push_back(novaOferta);
}

void modificar(int posicao, double novoValor, int novaQuantidade) {
    for (auto& oferta : ofertas) {
        if (oferta.posicao == posicao) {
            oferta.valor = novoValor;
            oferta.quantidade = novaQuantidade;
            return;
        }
    }
    cout << "Oferta com posição " << posicao << " não encontrada." << endl;
}

void deletar(int posicao) {
    auto it = ofertas.begin();
    while (it != ofertas.end()) {
        if (it->posicao == posicao) {
            it = ofertas.erase(it);
        } else {
            ++it;
        }
    }
}

void imprimirOfertas() {
    for (const Oferta& oferta : ofertas) {
        cout << oferta.posicao << "," << oferta.valor << "," << oferta.quantidade << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <número de notificações> <notificações...>" << endl;
        return 1;
    }

    int numNotificacoes;
    try {
        numNotificacoes = stoi(argv[1]);
    } catch (const invalid_argument& e) {
        cerr << "Número de notificações inválido." << endl;
        return 1;
    }

    for (int i = 2; i < argc; ++i) {
        stringstream ss(argv[i]);
        string token;
        vector<string> parametros;

        while (getline(ss, token, ',')) {
            parametros.push_back(token);
        }

        if (parametros.size() != 4) {
            cerr << "Formato de notificação inválido: " << argv[i] << endl;
            continue;
        }

        int posicao = stoi(parametros[0]);
        int acao = stoi(parametros[1]);
        double valor = stod(parametros[2]);
        int quantidade = stoi(parametros[3]);

        switch (acao) {
            case 0:
                inserir(posicao, valor, quantidade);
                break;
            case 1:
                modificar(posicao, valor, quantidade);
                break;
            case 2:
                deletar(posicao);
                break;
            default:
                cerr << "Ação inválida: " << acao << endl;
                break;
        }
    }

    imprimirOfertas();

    return 0;
}
