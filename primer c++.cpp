// primer c++.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <random>

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
        srand(static_cast<unsigned int>(time(nullptr))); 

        // Esta línea inicializa la semilla del generador de números aleatorios.
        // La función 'time(nullptr)' devuelve el número de segundos transcurridos desde la "época" (un punto de referencia en el tiempo).

        /*time(nullptr): La función time(nullptr) devuelve el tiempo actual en segundos desde una fecha de referencia, 
        generalmente conocida como "epoch". Esto proporciona un valor que cambia con el tiempo y se utiliza a menudo para inicializar 
        generadores de números aleatorios.
        static_cast<unsigned int>: Esta parte del código convierte el resultado de time(nullptr) a un tipo de dato unsigned int, 
        que es un tipo entero sin signo. La conversión se realiza para asegurarse de 
        que el valor de tiempo sea adecuado para ser utilizado como semilla en la función srand.*/

    }

    int generateRandomNumber() {
        if (count >= 6) {
            return -1; // Valor sentinela para indicar que ya no quedan números por generar
        }

        int randomNumber;

        // Utilizar un bucle do-while para asegurarse de que el número generado sea único.
        do {
            // Generar un número aleatorio utilizando el operador de módulo (%) para limitar el rango a 1 a 6.
            randomNumber = rand() % 6 + 1;
        } while (usedNumbers[randomNumber - 1] == 1); // Repetir hasta que se encuentre un número no utilizado.

        // Marcar el número generado como utilizado para evitar repeticiones.
        usedNumbers[randomNumber - 1] = 1;

        // Incrementar el contador de números generados.
        count++;

        // Devolver el número aleatorio único generado.
        return randomNumber;
    }
};
class MasterMindGame 
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
    MasterMindGame() //Constructor
    {
        for (size_t i = 0; i < a; i++)
        {
            MasterMind[0][i] = Fila[i];
        }
    }
    void Tabla()  //Imprimir la tabla de intentos y frio/caliente
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

                char f = CFX(MasterMind[i][j],MasterMind[0][j], MasterMind[0]); //El metodo FrioCalienteX se encarga de mostrar eso.

                cout << "|" << f << "|";
            }



            cout << "\n";
        }
    }

    char CFX(int Entrada,int Valor_Buscado, int Array[a])
    {
        if ( Entrada == 0) //Slot vacio
        {
            return '0';
        }
        else if (Entrada == Valor_Buscado) //Frente a frente
        {
            return 'C';
        }
        else if (FRIO(Array, Entrada)) //Frio / esta en la fila
        {
            return 'F';
        }
        else
        {
            return 'X'; //MALO
        }
    }

    bool FRIO(int Array[a], int y) //REcorre la fila y verifica que el numero esta en el
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

    bool CaptarIntento(string Cadena_Intento) //Verifica que el intento es valido antes de introducirlo
    {
        if ((Cadena_Intento.length() != 4) || (Cadena_Intento.empty())) //Verifica si es de 4 elementos o esta vacio 
        {
            return false;
        }

        for (char c : Cadena_Intento) //Verifica si el intento esta del 1 al 6, en ascii. el char c : as funciona como un foreach
        { 
            if (c < '1' || c > '6') {
                return false;
            }
        }

        return true;
    }

    void GuardarIntento(int Intento[a], int t) //Se ejecuta luego de verificar el intento y se guarda en la tabla MAsterMind. El elemento t es la fila o intento realizado
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
                return false; // Encontramos que son diferentes, no son iguales
            }
        }
        return true;
        
    }

    void MostrarFilaOculta() 
    {
        for (size_t j = 0; j < a; j++) 
        {
            cout << MasterMind[0][j];
        }

        cout << '\n';
    }



};

int main() 
{
    const int maxAttempts = 10; // Número máximo de intentos
    int intentos = 1; // Contador de intentos
    bool victoria = false;

    MasterMindGame Game;

    while (intentos <= maxAttempts && victoria != true)
    {


        cout << "BIENVENIDO AL JUEGO DE MASTERMIND\n";

        cout << "------------------------------------------------------------------------\n";

        Game.Tabla();

        try
        {
            int Array_Try[a]{};
            string Entrada_Intento;
            cout << "------------------------------------------------------------------------\n";

            cout << "Ingresar Intento (4 Enteros sin espacio):";
            cin >> Entrada_Intento;

            if (Entrada_Intento == "secreto")
            {
                Game.MostrarFilaOculta(); cin >> Entrada_Intento;
            }

            if (Game.CaptarIntento(Entrada_Intento))
            {
                for (size_t i = 0; i < a; i++)
                {
                    Array_Try[i] = Entrada_Intento[i] - '0'; //Se introduce la cadena de entrada en un arreglo de enteros. 
                }

                Game.GuardarIntento(Array_Try, intentos);
                    if (Game.Victoria(Array_Try))
                    {

                        cout << "HAS GANADO! | " << "CALIFICACION:" << maxAttempts - intentos + 1 << "\n";
                        cout << "------------------------------------------------------------------------\n";

                        break;

                        victoria = true;
                    }
                    intentos++;

            }

            system("cls");



        }
        catch (exception) 
        {

            cout << "Intente de nuevo (Presione Enter)\n";

            continue;
        }


    }


    return 0;
}


