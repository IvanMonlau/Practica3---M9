#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <time.h>
#include <cstdlib>
#include <vector>

using namespace std;

vector<string> nombres; // Variable global para almacenar los nombres

int main() {
    srand(time(NULL));
    int N;
    cout << "Ingrese la cantidad de procesos a crear: ";
    cin >> N;

    // Llenar el vector de nombres
    for (int i = 0; i < N; ++i) {
        string nombre;
        cout << "Ingrese el nombre " << i + 1 << ": ";
        cin >> nombre;
        nombres.push_back(nombre);
    }

    // Crear los procesos hijos
    pid_t pid;
    for (int i = 0; i < N; ++i) {
        pid = fork();
        if (pid < 0) {
            cerr << "Error al crear el proceso hijo" << endl;
            return 1;
        } else if (pid == 0) {
            // Proceso hijo
            srand(getpid()); // Inicializar la semilla con el PID
            vector<string> nombres_local = nombres; // Copiar el vector

            // Seleccionar un índice aleatorio dentro del rango de los nombres originales
            int indice = rand() % nombres.size(); 

            cout << "Proceso " << i + 1 << ": " << nombres_local[indice] << " fue seleccionado." << endl;
            exit(0);
        }
    }

    // Proceso padre
    for (int i = 0; i < N; ++i) {
        wait(NULL);
    }

    return 0;
}