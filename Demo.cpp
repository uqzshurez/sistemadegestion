#include <iostream>
#include <string>

using namespace std;

// Definición de la estructura para los productos
struct Producto {
    int num_proveedor;
    string desc_proveedor;
    float precio;
};

int main() {
    int num_productos;

    cout << "Ingrese la cantidad de productos a ingresar: ";
    cin >> num_productos;

    // Creación del arreglo de productos
    Producto productos[num_productos];

    // Ingreso de datos de los productos
    for (int i = 0; i < num_productos; i++) {
        cout << "Producto " << i+1 << ":" << endl;
        cout << "Número de proveedor: ";
        cin >> productos[i].num_proveedor;
        cout << "Descripción del proveedor: ";
        cin >> productos[i].desc_proveedor;
        cout << "Precio: ";
        cin >> productos[i].precio;
    }

    // Mostrar en pantalla los datos de los productos ingresados
    cout << endl << "Productos ingresados:" << endl;
    for (int i = 0; i < num_productos; i++) {
        cout << "Producto " << i+1 << ":" << endl;
        cout << "Número de proveedor: " << productos[i].num_proveedor << endl;
        cout << "Descripción del proveedor: " << productos[i].desc_proveedor << endl;
        cout << "Precio: " << productos[i].precio << endl << endl;
    }

    return 0;
}
