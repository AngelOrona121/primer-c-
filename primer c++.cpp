// primer c++.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <limits> // Para std::numeric_limits



using namespace std;

const int a = 4;



class RandomNumberGenerator {
private:
    int usedNumbers[6];
    int count;

public:
    RandomNumberGenerator() {
        // Inicializar el arreglo de números utilizados
        for (int i = 0; i < 6; ++i) {
            usedNumbers[i] = 0;
        }
        count = 0;

        // Inicializar la semilla del generador de números aleatorios
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    int generateRandomNumber() {
        if (count >= 6) {
            return -1; // Valor sentinela para indicar que ya no quedan números por generar
        }

        int randomNumber;
        do {
            randomNumber = std::rand() % 6 + 1;
        } while (usedNumbers[randomNumber - 1] == 1);

        usedNumbers[randomNumber - 1] = 1;
        count++;

        return randomNumber;
    }
};
class Methods 
{
    RandomNumberGenerator RandNum;

private:
    int MasterMind[11][4]{};
    int Fila[4] =
    {
        RandNum.generateRandomNumber(),
        RandNum.generateRandomNumber(),
        RandNum.generateRandomNumber(),
        RandNum.generateRandomNumber(),
    };


public:
    void IniciarTabla() 
    {
        for (size_t i = 0; i < a; i++)
        {
            MasterMind[0][i] = Fila[i];
        }
    }
    void Tabla() 
    {
        for (size_t i = 1; i < 10; i++)
        {
            for (size_t j = 0; j < a; j++)
            {
                if (MasterMind[i][j] != 0)
                {
                    cout << "|" << MasterMind[i][j] << "|";

                }
                else
                {
                    cout << "|" << '_' << "|";
                }
            }

            cout << "        ";

            for (size_t j = 0; j < a; j++)
            {

                char f = CFX(MasterMind[i][j],MasterMind[0][j], MasterMind[0]);

                cout << "|" << f << "|";
            }



            cout << "\n";
        }
    }

    char CFX(int M,int N, int Array[a])
    {
        if ( M == 0)
        {
            return '0';
        }
        else if (M == N)
        {
            return 'C';
        }
        else if (FRIO(Array, M))
        {
            return 'F';
        }
        else
        {
            return 'X';
        }
    }

    bool FRIO(int Array[a], int y)
    {
        bool r = false;

        for (size_t i = 0; i < a; i++)
        {
            if (y == Array[i])
            {
                r = true;
            }
        }

        return r;
    }

    bool CaptarIntento(string as)
    {
        if (as.length() != 4) {
            return false;
        }

        for (char c : as) {
            if (c < '1' || c > '6') {
                return false;
            }
        }

        return true;
    }

    void GuardarIntento(int Intento[], int t)
    {

        for (size_t i = 0; i < a; i++)
        {
            MasterMind[t][i] = Intento[i];
        }
    }


    bool Victoria(int p[a])
    {
        for (int i = 0; i < a; i++) {
            if (MasterMind[0][i] != p[i]) 
            {
                return false; // Encontramos elementos diferentes, no son iguales
            }
        }
        return true;
        
    }



};

int main() 
{
    const int maxAttempts = 10; // Número máximo de intentos
    int intentos = 1; // Contador de intentos
    bool victoria = false;

    Methods Game;

    Game.IniciarTabla();

    cout << "BIENVENIDO AL JUEGO DE MASTERMIND\n";

    cout << "------------------------------------------------------------------------\n";

    while (intentos <= maxAttempts && victoria != true)
    {
        Game.Tabla();

        try
        {
            int tr[a]{};
            string ou;
            cout << "Ingresar Intento (arreglo de enteros): ";
            cin >> ou;

            if (Game.CaptarIntento(ou))
            {
                for (size_t i = 0; i < a; i++)
                {
                    tr[i] = ou[i] - '0';
                }

                Game.GuardarIntento(tr, intentos);
                    if (Game.Victoria(tr))
                    {
                        cout << "HAS GANADO! | " << "CALIFICACION:" << 10 - intentos << "\n";
                        cout << "------------------------------------------------------------------------\n";

                        victoria = true;
                    }
                    intentos++;

            }


        }
        catch (exception) 
        {

            cout << "Intente de nuevo (Presione Enter)\n";

            continue;
        }


    }


    return 0;
}


