// pureba 12.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <chrono>
#include <ctime>  // Necesario para usar time_t y tm
#include <fstream>  // Necesario para trabajar con archivos
using namespace std;

struct Orden {
    int numeroTicket;
    string nombreRestaurante;
    string vendedor;
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

string obtenerFechaActual() {
    time_t now;
    time(&now);

    struct tm localtm;
    localtime_s(&localtm, &now);

    int day = localtm.tm_mday;
    int month = 1 + localtm.tm_mon;
    int year = 1900 + localtm.tm_year;

    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}


void imprimirTicket(const Orden& orden) {
    cout << " Nombre del restaurante: " << orden.nombreRestaurante << " joey pida lo que quiera " << endl;
    cout << " Numero de ticket: " << orden.numeroTicket << " " << endl;
    cout << " Nombre del vendedor: " << orden.vendedor << " " << endl;
    cout << " Fecha: " << obtenerFechaActual() << " " << endl;
    cout << " Lista de los articulos: " << orden.plato << " " << endl;
    cout << " Precio de los articulos: $" << fixed << setprecision(2) << orden.precio << " " << endl;
    cout << " Numero total de articulos: 1 " << endl;
    cout << " Precio unitario del total de los articulos: $" << fixed << setprecision(2) << orden.precio << " " << endl;
    cout << " Promocion: hoy no fio mañana si " << endl;
    cout << " Propina: $" << fixed << setprecision(2) << (0.1 * orden.precio) << " " << endl;
    cout << " Impuesto: $" << fixed << setprecision(2) << (0.16 * orden.precio) << " " << endl;
    cout << " Total : $" << fixed << setprecision(2) << (1.26 * orden.precio) << " " << endl;
}

void imprimirMenu() {
    cout << "Menu de Platos:" << endl;
    cout << "1. Pizza - $100" << endl;
    cout << "2. Hamburguesa - $200" << endl;
    cout << "3. Tacos - $80" << endl;
    cout << "4. Nachos - $50" << endl;
}

void altaOrden() {
    Orden nuevaOrden;
    nuevaOrden.numeroTicket = obtenerNumeroTicket();

    nuevaOrden.vendedor = "Steaf";

    cout << "Cliente: ";
    getline(cin, nuevaOrden.cliente);

    // Imprimir el menú y obtener la selección del usuario
    imprimirMenu();
    int seleccion;
    cout << "Seleccione un plato (1-4): ";
    cin >> seleccion;

    // Asignar el plato y precio correspondiente
    switch (seleccion) {
    case 1:
        nuevaOrden.plato = "Pizza";
        nuevaOrden.precio = 100;
        break;
    case 2:
        nuevaOrden.plato = "Hamburguesa";
        nuevaOrden.precio = 200;
        break;
    case 3:
        nuevaOrden.plato = "Tacos";
        nuevaOrden.precio = 80;
        break;
    case 4:
        nuevaOrden.plato = "Nachos";
        nuevaOrden.precio = 50;
        break;
    default:
        cout << "Selección no válida. Orden cancelada." << endl;
        return;
    }

    nuevaOrden.cancelada = false;

    ordenes.push_back(nuevaOrden);
    cout << "Orden creada exitosamente con el numero de ticket: " << nuevaOrden.numeroTicket << endl;

    // Imprimir el ticket
    cout << "------ Ticket ------" << endl;
    imprimirTicket(nuevaOrden);
    cout << "---------------------" << endl;
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

void guardarOrdenesEnArchivo(const string& nombreRestaurante, const string& fecha) {
    ofstream archivo; // clase ifstream para leer archivos
    string nombrearchivo;

    nombrearchivo = "JoeyPidaloquequiera";

    archivo.open(nombrearchivo.c_str(), ios::out);

    if (archivo.fail()) {
        cout << "ERROR NO SE PUDO CREAR EL ARCHIVO";
        exit(1);
    }

    archivo << "Numero de Ticket: \t";
    archivo << "Cliente: \t";
    archivo << "Plato: \t";
    archivo << "Precio: $ \t";
    archivo << "Status: \t";
    archivo << "--------------------------- \n";

    for (const Orden& orden : ordenes) {
        archivo << orden.numeroTicket << "\t\t";
        archivo << orden.cliente << "\t\t";
        archivo << orden.plato << "\t\t";
        archivo << fixed << setprecision(2) << orden.precio << "\t\t";

        if (orden.cancelada) {
            archivo << "Cancelada \t\t";
        }
        else {
            archivo << "Vigente \t\t";
        }

        archivo << "\n";
    }

    archivo.close();
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

    // Al salir del programa, guardar la información de las órdenes en un archivo
    string nombreRestaurante = "joey pida lo que quiera";
    string fecha = obtenerFechaActual();
    guardarOrdenesEnArchivo(nombreRestaurante, fecha);

    return 0;
}