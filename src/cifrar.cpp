/**
* @file	    cifrar.cpp
* @brief	Programa que cifra mensagens lidas a partir de um arquivo.
* @author   Valmir Correa (valmircsjr@gmail.com)
* @date	    08/2018
*/

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <string>
using std::string;
using std::stoi;

#include <cstring>

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <vector>
using std::vector;

#include <algorithm>
using std::find;

#include <cstdlib>
using std::atoi;

/**
* @brief    Faz a leitura do conteudo do arquivo
* @param    arq Nome do arquivo a ser lido
* @return   Mensagem lida do arquivo
*/
string leitura (string arq) {
    
    ifstream arquivo (arq);
    
    if (!arquivo) {
        cerr << "Erro ao ler o arquivo " << arq << "!" << endl;
        exit (1);
    }

    string msg;
    while (!arquivo.eof()) {
        string str_temp;
        getline(arquivo, str_temp);
        msg += str_temp;
    }

    if (msg == "") {
        cerr << "Não há mensagem para ser cifrada!" << endl;
        exit(1);
    }

    return msg;
}

/**
* @brief    Cifra a mensagem recebida
* @param    msg Mensagem a ser cifrada
* @param    data Data
* @return   Mensagem cifrada
*/
string cifrar (string msg, int *data) {
    
    string msg_digitos;
    int msg_tam = msg.size();
    unsigned int aux = 0;
    char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    // Percorro a mensagem, substituindo cada caractere por um numero da data
    // Quando chego ao final do vetor da data, zero o contador (aux), para que de inicie de novo.
    for (int ii = 0; ii < msg_tam; ii++) {
        if (msg[ii] != ' ') {
            int valor_soma = data[aux];
            cout << valor_soma;
            for (int pp = 0; pp <= 26; pp++) {
                if (msg[ii] == alfabeto[pp]) {
                    int pos_nova_letra = pp + valor_soma;
                    if (pos_nova_letra >= 26)  {
                        msg_digitos += alfabeto[pos_nova_letra-26];
                    } else {
                        msg_digitos += alfabeto[pos_nova_letra];
                    }
                }
            }
            aux++;
            if (aux >= 6) {
                aux = 0;
            }
        } else {
            msg_digitos += ' ';
            cout << " ";
        }
    }
    return msg_digitos;
}

/**
* @brief    Faz a escrita de uma mensagem em um arquivo
* @param    arq Nome do arquivo a ser aberto
*/
void escrita (string nome_arq, string msg) {
    
    ofstream arquivo (nome_arq);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo " << nome_arq << "!" << endl;
        exit (1);
    }

    arquivo << msg;
    arquivo.close();
}

/**
 * Função principal
*/
int main (int argc, char* argv[]) {

    // Verifica se os argumentos foram passados corretamente
    if (argc != 4) {
        cout << "--> Argumentos inválidos! Use o comando: ";
        cout << "'./cifrar data data/mensagem.txt data/mensagem.sec'" << endl;
        exit(1);
    }

    // Remover as barras da data
    string data;
    int aux_tam = 0;
    char * data_sem_barras;
    data_sem_barras = strtok (argv[1], "/");
    while (data_sem_barras != NULL) {
        data += data_sem_barras;
        data_sem_barras = strtok (NULL, "/");
        aux_tam += 2;
    }

    // Verifica se o formato da data é dd/mm/aa
    if (data.size() != 6) {
        cout << "--> Digite a data no formato 'dd/mm/aa'!" << endl;
        exit(1);
    }

    // Verifica se foram passados numeros na data
    for (int ii = 0; ii < (int) data.size(); ii++) {
        if (data[ii] < 48 || data[ii] > 57) {
            cout << "--> Passe a data em valor númerico!" << endl;
            exit(1);
        }
    }

    // Passando a data para um vetor de inteiros para facilitar a manipulação
    int *data_int = new int [aux_tam];
    for (int ii = 0; ii < aux_tam; ii++) {
        data_int[ii] = data[ii] - '0';
    }

    // Nomes dos arquivos
    string arquivo_txt = argv[2];
    string arquivo_sec = argv[3];

    // leitura da mensagem
    string msg_clara = leitura(arquivo_txt);
    
    // Deixando todas as letras minusculas
    transform(msg_clara.begin(), msg_clara.end(), msg_clara.begin(), tolower);

    // Data
    cout << "Data:               ";
    for (int ii = 0; ii < 6; ii++) {
        cout << data_int[ii];
    }

    // Mensagem clara
    cout << endl << "Mensagem Clara:     " << msg_clara << endl;

    // Mensagem numerica gerada dentro da função "cifrar"
    cout << "Mensagem Numerica:  ";

    // Mensagem cifrada
    string msg_cifrada = cifrar(msg_clara, data_int);
    cout << endl << "Mensagem Cifrada:   " << msg_cifrada << endl;

    // Escrita da mensagem no arquivo
    escrita(arquivo_sec, msg_cifrada);

    return 0;
}