// ATGA_primer-avance.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <iomanip>
#include <limits>
using namespace std;

struct Orden {
    int numeroTicket;
    string cliente;
    string plato;
    double precio;
    bool cancelada;
};

vector<Orden> ordenes;

int obtenerNumeroTicket() {
    int numeroTicket = 1;
    for (const Orden& orden : ordenes) {
        if (orden.numeroTicket >= numeroTicket) {
            numeroTicket = orden.numeroTicket + 1;
        }
    }
    return numeroTicket;
}

void altaOrden() {
    Orden nuevaOrden;
    nuevaOrden.numeroTicket = obtenerNumeroTicket();

    cout << "Cliente: ";
    cin.ignore();
    getline(cin, nuevaOrden.cliente);

    cout << "Plato: ";
    getline(cin, nuevaOrden.plato);

    cout << "Precio: ";
    cin >> nuevaOrden.precio;

    nuevaOrden.cancelada = false;

    ordenes.push_back(nuevaOrden);
    cout << "Orden creada exitosamente con el numero de ticket: " << nuevaOrden.numeroTicket << endl;
}

void modificarOrden() {
    int numeroTicket;
    cout << "Numero de ticket de la orden a modificar: ";
    cin >> numeroTicket;

    for (Orden& orden : ordenes) {
        if (orden.numeroTicket == numeroTicket) {
            cout << "Nuevo Cliente: ";
            cin.ignore();
            getline(cin, orden.cliente);

            cout << "Nuevo Plato: ";
            getline(cin, orden.plato);

            cout << "Nuevo Precio: ";
            cin >> orden.precio;

            cout << "Orden modificada exitosamente." << endl;
            return;
        }
    }

    cout << "Orden no encontrada." << endl;
}

void eliminarOrden() {
    int numeroTicket;
    cout << "Numero de ticket de la orden a eliminar: ";
    cin >> numeroTicket;

    for (Orden& orden : ordenes) {
        if (orden.numeroTicket == numeroTicket) {
            orden.cancelada = true;
            cout << "Orden cancelada exitosamente." << endl;
            return;
        }
    }

    cout << "Orden no encontrada." << endl;
}

void listarOrdenes(bool mostrarCanceladas) {
    cout << "Lista de Ordenes:" << endl;
    for (const Orden& orden : ordenes) {
        if (orden.cancelada && !mostrarCanceladas) continue;

        cout << "Numero de Ticket: " << orden.numeroTicket << endl;
        cout << "Cliente: " << orden.cliente << endl;
        cout << "Plato: " << orden.plato << endl;
        cout << "Precio: $" << fixed << setprecision(2) << orden.precio << endl;//solo pon el valor del precio si agregas el signo de pesos se buguea

        if (orden.cancelada) {
            cout << "Status: Cancelada" << endl;
        }
        else {
            cout << "Status: Vigente" << endl;
        }

        cout << "---------------------------" << endl;
    }
}

int main() {
    int opcion;

    do {
        cout << "Menu de Opciones:" << endl;
        cout << "1. Alta de Ordenes" << endl;
        cout << "2. Modificar Orden" << endl;
        cout << "3. Eliminar o Cancelar Orden" << endl;
        cout << "4. Lista de Ordenes (Vigentes)" << endl;
        cout << "5. Lista de Ordenes (Todos)" << endl;
        cout << "6. Limpiar pantalla" << endl;
        cout << "7. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: altaOrden(); break;
        case 2: modificarOrden(); break;
        case 3: eliminarOrden(); break;
        case 4: listarOrdenes(false); break;
        case 5: listarOrdenes(true); break;
        case 6:
            // Limpiar pantalla 
            cout << "\033[2J\033[1;1H";  
            break;
        case 7: cout << "Saliendo del programa." << endl; break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opcion != 7);

    return 0;
}
