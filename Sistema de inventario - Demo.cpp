#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include<cstdlib>
#include<windows.h>
#include<string.h>
#include<fstream>
#include <ctime>
#include <time.h>
#include<cstring>

#define MAX 99999

using namespace std;





//-----------Estructuras-----------//
struct Producto{
	int codigo;
	char descripcion[MAX];
	char accionFarmacologica[MAX];
	char marca[MAX];
	char vencimiento[MAX];
	char presentacion[MAX];
	char laboratorio[MAX];
	int cantidad;
	float precio;
	float costo;
};

struct Usuario{
	char usuario[MAX];
	string contrasena;
	int rol;
};

string USUARIO, CONTRASENA, ROL; // captura los datos del usuario que inicia sesion
float TOTAL; // Monto de compra total
int c;  //conteo de las facturas
int contador;

COORD coord={0,0};
void fecha()
{
     struct tm *tiempo;
     int dia;
     int mes;
     int anio;

     time_t fecha_sistema;
     time(&fecha_sistema);
     tiempo=localtime(&fecha_sistema);

     anio=tiempo->tm_year + 1900;
     mes=tiempo->tm_mon + 1;
     dia=tiempo->tm_mday;
     cout << dia << "/" << mes << "/" << anio;


}
string Fecha()
{
    time_t t;
    struct tm *tm;
    char fecha[100];
    t=time(NULL);
    tm=localtime(&t);
    strftime(fecha, 100, "%d/%m/%y", tm);
    return  fecha;
}

string Hora()
{
	time_t t;
    struct tm *tm;
    char hora[100];

    t=time(NULL);
    tm=localtime(&t);
    strftime(hora, 100, "%I:%M:%S", tm);
    return  hora;
}

void mostrarUsuario()
{
	cout << "USUARIO: " << USUARIO << endl;
	cout << "ROL: " << ROL << endl;
}

void gotoxy(int x,int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


//-----Funcion Visualizar-----//


void visualizarMedicamentos()
{
	Producto producto;
	ifstream lectura;
	lectura.open("inventario.txt", ios::out | ios::in);

	if(lectura.is_open())
	{


	cout << "   ---------------------------------------------------------------------------"<<endl;
	cout <<"   "<<setw(10)<< "| Codigo |" << setw(20) <<"      Marca        |" << setw(20) << "    Proveedor    |" << setw(10)
	<< " Cantidad|" << setw(10) << "  Costo  |" << endl;
	cout << "   ----------------------------------------------------------------------------"<<endl;
	 lectura >> producto.codigo;
	 //recorriendo el archivo
	 while(!lectura.eof())
	 {
	 	lectura >> producto.marca >> producto.descripcion >> producto.accionFarmacologica >>
		producto.vencimiento >> producto.presentacion>> producto.laboratorio >> producto.cantidad
		>> producto.precio >> producto.costo;

		//Mostrando en pantalla los productos
			cout <<"   "<<setw(9)<< producto.codigo<<"|" << setw(19) << producto.marca<<"|"
			<< setw(19) << producto.laboratorio<<"|" << setw(9) << producto.cantidad<<"|" << setw(9)
			<< producto.costo<<"|" << endl;

		lectura >> producto.codigo;
	 }
	 cout << "------------------------------------------------------------------------------"<<endl;
	}else{
		cout << "No se pudo abrir el archivo especificado" << endl;
	}
}


//-----Funcion AGOTANDO-----//


void agotando()
{
	Producto producto;
	ifstream lectura;
	lectura.open("inventario.txt", ios::out | ios::in);
	mostrarUsuario();

	if(lectura.is_open())
	{


	cout << "   ---------------------------------------------------------------------------"<<endl;
	cout <<"   "<<setw(10)<< "| Codigo |" << setw(20) <<"      Marca        |" << setw(20) << "    Proveedor    |" << setw(10)
	<< " Cantidad|" << setw(10) << "  Costo  |" << endl;
	cout << "   ----------------------------------------------------------------------------"<<endl;
	 lectura >> producto.codigo;
	 //recorriendo el archivo
	 while(!lectura.eof())
	 {
	 	lectura >> producto.marca >> producto.descripcion >> producto.accionFarmacologica >>
		producto.vencimiento >> producto.presentacion>> producto.laboratorio >> producto.cantidad
		>> producto.precio >> producto.costo;

		//Mostrando en pantalla los productos
			if(producto.cantidad <= 30 )
			{
				cout <<"   "<<setw(9)<< producto.codigo<<"|" << setw(19) << producto.marca<<"|"
				<< setw(19) << producto.laboratorio<<"|" << setw(9) << producto.cantidad<<"|" << setw(9)
				<< producto.costo<<"|" << endl;
			}


		lectura >> producto.codigo;
	 }
	 cout << "------------------------------------------------------------------------------"<<endl;
	}else{
		cout << "No se pudo abrir el archivo especificado" << endl;
	}
	system("pause");
}


//-----Funcion ELIMINAR-----//


void eliminar()
{
	mostrarUsuario();
	Producto producto;
	ofstream aux;
    ifstream lectura;
    int i= 0;
    bool encontrado = false;
    int auxCodigo = 0;
    aux.open("auxiliar2.txt",ios::out);
    lectura.open("inventario.txt",ios::in);
    visualizarMedicamentos();
    if(aux.is_open() && lectura.is_open()){

        cout<<"Ingresa el codigo: ";
        cin>>auxCodigo;
        lectura >> producto.codigo;
	 while(!lectura.eof())
	 {
	 	lectura >> producto.marca >> producto.descripcion >> producto.accionFarmacologica >>
		producto.vencimiento >> producto.presentacion>> producto.laboratorio >> producto.cantidad
		>> producto.precio >> producto.costo;
	 	if(auxCodigo == producto.codigo){
                encontrado = true;
                cout << "Registro Eliminado!" << endl;
            }else{
                aux << producto.codigo << " " << producto.marca << " " << producto.descripcion << " "
			<< producto.accionFarmacologica << " " << producto.vencimiento << " "
			<< producto.presentacion << " " << producto.laboratorio << " "
			<< producto.cantidad << " " << producto.precio << " "  << producto.costo<< endl;
            }
		lectura>>producto.codigo;
	}
    if(encontrado==false){
        cout<<"¡No se encontro ningun registro con esa contraseña! "<<auxCodigo<<endl;
    }
    aux.close();
    lectura.close();
    remove("inventario.txt");
    rename("auxiliar2.txt","inventario.txt");
    }
    else{
            cout<<"No se pudo abrir el archivo o aun no ha sido creado"<<endl;

    }
    system("pause");
}
//------------------------------Ver Medicamentos-------------------------------//
void verMedicamentos()
{
	mostrarUsuario();
	Producto producto;
	ifstream lectura;
	lectura.open("inventario.txt", ios::out | ios::in);

		cout << "              <<<  Inventario-> Ver Productos  >>>          " << endl;
		//cout << "    ------------------------------------------------------------" << endl;
	visualizarMedicamentos();
	system("pause");
}


//-----Funcion BUSCAR-----//


void buscar()
{
	mostrarUsuario();
	Producto producto;
	ifstream lectura;
	int codigo,p;
	bool encontrado = false;
	lectura.open("inventario.txt", ios::out | ios::in);

    gotoxy(40,6);
	cout << "B U S C A R   P R O D U C T O"<<endl;
	if(lectura.is_open())
	{
		gotoxy(17,8);
        cout << "Buscar por codigo: ";
        cin >> codigo;
        lectura >> producto.codigo;

        while(!lectura.eof())
        {
            lectura >> producto.marca >> producto.descripcion >> producto.accionFarmacologica >>producto.vencimiento >> producto.presentacion>>
            producto.laboratorio >> producto.cantidad>> producto.precio >> producto.costo;

            if(codigo == producto.codigo)
            {
                encontrado = true;

                gotoxy(17,10);
                cout << "Marca: " << producto.marca << endl;
                gotoxy(17,11);
                cout << "Descripcion: " << producto.descripcion << endl;
                gotoxy(17,12);
                cout << "Accion: " << producto.accionFarmacologica << endl;
                gotoxy(17,13);
                cout << "Presentaci\xa2n: " << producto.presentacion << endl;
                gotoxy(17,14);
                cout << "Proveedor: " << producto.laboratorio << endl;
                gotoxy(17,15);
                cout << "Precio: " << producto.costo << endl;
            }
            lectura >> producto.codigo;
        }
        if(!encontrado)
        {

            cout << "Producto no encontrado!" << endl;
        }
    }
    else{
        cout << "No se pudo abrir el archivo especificado" << endl;
    }
        system("pause");

}

//-----Funcion AGREGAR-----//


void agregar()
{
	mostrarUsuario();
	Producto producto; //creando objeto de estructura
	ofstream escribir;
	ifstream consulta;
	bool repetido = false;
	int auxcodigo=0;
	consulta.open("inventario.txt", ios::in);
	escribir.open("inventario.txt", ios::out | ios::app); //Abriendo archivo

	if (escribir.is_open() && consulta.is_open() )
	{
			gotoxy(40, 9);
			cout << "A G R E G A R    P R O D U C T O";
			gotoxy(27,11);
			cout << "Codigo: ";
			cin >> auxcodigo;


		consulta >> producto.codigo;// lectura adelantada

		//verificando que no halla un registro con el codigo ingresado
		while(!consulta.eof())
		{
			consulta >> producto.marca >> producto.descripcion >> producto.accionFarmacologica >>
			producto.vencimiento >> producto.presentacion>> producto.laboratorio >> producto.cantidad
			>> producto.precio >> producto.costo;

			if(producto.codigo == auxcodigo)
			{

                gotoxy(17, 13);
				cout << "¡Ya existe un producto con el codigo! " << auxcodigo << endl;
				repetido = true;
				system("pause");

			}
			consulta >> producto.codigo;
		}
		if (repetido == false)
		{
			gotoxy(27,12);
			cout << "Marca del producto:  ";
			cin >> producto.marca;
			fflush(stdin);
			gotoxy(27,13);
			cout << "Descripcion: ";
			cin >> producto.descripcion;
			fflush(stdin);
			gotoxy(27,14);
			cout << "Accion: ";
			cin >> producto.accionFarmacologica;
			fflush(stdin);
			gotoxy(27,15);
			cout << "Fecha de vencimiento: ";
			cin >> producto.vencimiento;
			fflush(stdin);
			gotoxy(27,16);
			cout << "Presentacion: " ;
			cin >> producto.presentacion;
			fflush(stdin);
			gotoxy(27,17);
			cout << "Proveedor: ";
			cin >> producto.laboratorio;
			fflush(stdin);
			gotoxy(27,18);
			cout << "Cantidad: ";
			cin >> producto.cantidad;
			fflush(stdin);
			gotoxy(27,19);
			cout << "Precio: ";
			cin >> producto.precio;
			fflush(stdin);
			gotoxy(27,20);
			cout << "Costo: ";
			cin >> producto.costo;
			fflush(stdin);
			//Fin de entrada de datos
			escribir << auxcodigo << " " << producto.marca << " " << producto.descripcion << " "
			<< producto.accionFarmacologica << " " << producto.vencimiento << " "
			<< producto.presentacion << " " << producto.laboratorio << " "
			<< producto.cantidad << " " << producto.precio << " " << producto.costo<< endl;

			system("cls");

		}
	}
	else{

		cout << "Error, el archivo no se pudo abrir" << endl;
	}


	escribir.close();
	consulta.close();
	system("pause");
}
void inventario()
{
	SetConsoleTitle("Sistema de Gestion - Distribuidora X");

	//---------Inicializando los punteros--------//
	char op;
	do {
		mostrarUsuario();

		gotoxy(40,9);
		cout << "INVENTARIO                        " << endl;

		gotoxy(27,11);
		cout << "      [1]. Agregar Producto	                     " << endl;
		gotoxy(27,12);
		cout << "      [2]. Eliminar Producto        	           " << endl;
		gotoxy(27,13);
		cout << "      [3]. Buscar Producto Especifico	                   " << endl;
		gotoxy(27,14);
		cout << "      [4]. Ver Productos de la distribuidora                      " << endl;

	    gotoxy(27,15);
	    cout << "      [5]. Productos agotandose" << endl;
		gotoxy(27,16);
		cout << "      [0]. Regresar                                   " << endl;


		gotoxy(25,19);
		cout << "    Ingrese opcion: ";
		cin >> op;

		switch(op)
		{
			case '1':
				{
					system("cls");
					agregar();
					system("cls");
					break;
				}
			case '2':
				{
					system("cls");
				    eliminar();
				    system("cls");
					break;
				}
			case '3':
				{
					system("cls");
					buscar();
					system("cls");
					break;
				}
			case '4':
				{
					system("cls");
					verMedicamentos();
					system("cls");
					break;
				}
			case '5':
				{
					system("cls");
					agotando();
					system("cls");
					break;
				}
			case '0':
				{
					system("cls");
					break;
				}

			default:
				{
					system("cls");
					cout << "Error, opcion desconocida";
					Sleep(500);
					system("cls");
					break;
				}
		}

	system("cls");

	}while(op!= '0');

}
void salir()
{

	string mensaje = "T e c h n o l o g y - G";
	cout << endl;
	cout << endl;
	cout << "                ";
	for (int i = 0; i < mensaje.length(); i++)
	{
		cout << mensaje[i];
		Sleep(80);
	}
}

//----------------------------Creacion de usuario-------------------------//
void crearusuario()
{
	mostrarUsuario();
	Usuario usuario; //creando objeto de estructura
	ofstream escribir; // salida de datos
	ifstream consulta; // entrada de datos
	bool repetido = false;
	string auxuser;
	consulta.open("registroUsuario.txt", ios::in);
	escribir.open("registroUsuario.txt", ios::out | ios::app); //Abriendo archivo

	if (escribir.is_open() && consulta.is_open() )
	{

        gotoxy(40, 9);
        cout << "CREAR NUEVO USUARIO";
        gotoxy(25,11);
		cout << "Usuario: ";
		fflush(stdin);
		cin >> auxuser;


		consulta >> usuario.usuario;// lectura adelantada

		//verificando que no halla un registro con el codigo ingresado
		while(!consulta.eof())
		{
			consulta >> usuario.contrasena >> usuario.rol;

			if(usuario.usuario == auxuser)
			{
				cout << "Ya existe un usuario con el descripcion " << auxuser << endl;
				repetido = true;
				system("pause");

			}
			consulta >> usuario.usuario;
		}
		if (repetido == false)
		{
			gotoxy(22,12);
			cout << "Contrasena:  ";
			cin >> usuario.contrasena;
			fflush(stdin);
			gotoxy(27,13);
			cout << "Ingrese (0)Administrador || (1) Cajero: ";
			cin >> usuario.rol;
			gotoxy(27,14);
			escribir << auxuser << " " << usuario.contrasena << " " << usuario.rol << endl;

            string exito = "USUARIO CREADO CON EXITO! ";
            for(int i = 0 ; i <= exito.length(); i++)
            {
                cout << exito[i];
                Sleep(80);
            }
            cout << endl;
		}
	}
	else{
		cout << "Error, el archivo no se pudo abrir" << endl;
	}


	escribir.close();
	consulta.close();
	Sleep(600);
}


//-----Funcion VER USUARIOS-----//


void verusuarios(){

    Usuario usuario;
	ifstream lectura;
	mostrarUsuario();
	int rol;
	lectura.open("registroUsuario.txt", ios::out | ios::in);
	if(lectura.is_open())
	{
        cout << "   ---------------------------------------------------------------------------"<<endl;
        cout <<"   "<<setw(30)<< "| Usuario";
        cout<<setw(20) <<"| Contrasena";
        cout<<setw(16)<<"| Rol"<<endl;
        lectura >> usuario.usuario;
	//recorriendo el archivo

        while(!lectura.eof())
        {
            lectura >> usuario.contrasena >> rol;
            cout <<"   "<<setw(30)<< usuario.usuario<< setw(17) << usuario.contrasena<< setw(19)<<rol<<endl;
            lectura >> usuario.usuario;
         }
         //cout << "------------------------------------------------------------------------------"<<endl;
	}
	else{
		cout << "No se pudo abrir el archivo especificado" << endl;
	}
	cout << "------------------------------------------------------------------------------"<<endl;
    cout<<"* El identificador 0, corresponde al rol de ADMINISTRADOR"<<endl;
    cout<<"* El identificador 1, corresponde al rol de CAJERO"<<endl;
    cout << "------------------------------------------------------------------------------"<<endl;

    system("pause");
}


//-----Funcion Eliminar USUARIO-----//


void eliminarUsuario()
{
	mostrarUsuario();
	Usuario user;
	ofstream aux;
    ifstream lectura;
    bool encontrado = false;
    string usuario ="";
    aux.open("auxiliar3.txt",ios::out);
    lectura.open("registroUsuario.txt",ios::in);
    if(aux.is_open() && lectura.is_open()){
        gotoxy(65,1);
        cout<<"Ingresa el usuario a eliminar: ";
        cin>>usuario;
        lectura >> user.usuario;
         while(!lectura.eof())
         {
            lectura >> user.contrasena >> user.rol;
            if(usuario == user.usuario){
                    encontrado = true;
                    cout << "Usuario " << user.usuario <<" Eliminado!" << endl;
                    Sleep(500);
                }else{
                    aux << user.usuario << " " << user.contrasena << " " << user.rol << endl;
                }
                lectura>>user.usuario;

        }
        if(encontrado==false){
            cout<<"No se encontro ningun usuario con id "<<usuario<<endl;
        }
        aux.close();
        lectura.close();
        remove("registroUsuario.txt");
        rename("auxiliar3.txt","registroUsuario.txt");
    }
    else{
            cout<<"No se pudo abrir el Archivo o aun no ha sido Creado"<<endl;

    }
    system("pause");
}


//-----Funcion ADMINISTRAR-----//


void administrar()
{
	SetConsoleTitle("ADMINISTRAR");
	char op;
	do {
		mostrarUsuario();
		gotoxy(40,9);
		cout << "A D M I N I S T R A R     U S U A R I O                   " << endl;
		cout << endl<<endl;

		gotoxy(27,11);
		cout << "      [1] Crear nuevo usuario                           " << endl;
		gotoxy(27,12);
		cout << "      [2] Ver usuarios                                  " << endl;
		gotoxy(27,13);
		cout << "      [0] Regresar                                        " << endl;

		gotoxy(25,15);
		cout << "    Opcion: ";
		cin >> op;

		switch(op)
		{
			case '1':
				{
					system("cls");
					crearusuario();
					system("cls");
					break;
				}
			case '2':
				{
					system("cls");
                    verusuarios();
					system("cls");
					break;
				}
			case '0':
				{

                    salir();
					system("cls");
					break;
				}
			default:

				{
					system("cls");
					cout << "Error, opcion desconoidca."<< endl;
					Sleep(500);
                    system("cls");
					break;
				}
		}



	}while(op!= '0');

}

//-----Funcion MENU-----//


void menu()
{
	SetConsoleTitle("ADMINISTRAR");
	char op;
	do {
		mostrarUsuario();
		gotoxy(40,9);
		cout << "M E N U   P R I N C I P A L                     " << endl;
		cout << endl;
		gotoxy(25,11);
		cout << "      [1]. Administrar Usuarios                           " << endl;
		gotoxy(25,12);
		cout << "      [2]. Inventario                         	 " << endl;
		gotoxy(25,13);
		cout << "      [3]. Productos en agotamiento                " << endl;
		gotoxy(25,14);
		cout << "      [4]. Factura                                   " << endl;
		gotoxy(25,15);
		cout << "      [0]. Salir                                   " << endl;

		gotoxy(25,16);
		cout << "    Ingrese opcion: ";
		cin >> op;

		switch(op)
		{
			case '1':
				{
					system("cls");
					administrar();
					system("cls");
					break;
				}
			case '2':
				{
					system("cls");
					inventario();
					system("cls");
					break;
				}
			case '3':
				{
					system("cls");
					agotando();
					system("cls");
					break;
				}
		
				
			case 0:
				{

					salir();
					break;
				}
			default:
				{
					system("cls");
					cout << "Error, opcion desconocida" << endl;
					Sleep(500);
					system("cls");
					break;
				}
		}



	}while(op!= '0');

}


//-----Funcion AGREGAR FACTURA-----//


void agregarFactura()
{
	Producto producto;
	ofstream aux;
	ofstream count;
	ofstream factura;
	ifstream lectura;
	ifstream lectura2;
	string usuario, auxproducto;
	int auxcantidad;
	float precio;
	int cantidadFinal ;
	int cantidad;
	int codigo;
	char resp;
	bool salir = false;
	bool encontrado = false;
	TOTAL = 0;


	aux.open("auxiliar.txt", ios::out);
	lectura.open("inventario.txt", ios::in);
	factura.open("factura.txt", ios::out );
	lectura2.open("factura.txt", ios::in);
	count.open("conteo.txt");
	if(lectura.is_open() && aux.is_open() && factura.is_open())
	{
		do{
			system("cls");
			mostrarUsuario();
			encontrado = false;
			cout << "                            F A C T U R A R  " << endl;
			lectura2 >> auxproducto;
			visualizarMedicamentos();
			cout  << endl;
			cout << "Codigo: ";
			cin >> codigo;
			lectura >> producto.codigo;
			 while(!lectura.eof())
			 {
			 	lectura >> producto.marca >> producto.descripcion>> producto.accionFarmacologica >>
				producto.vencimiento >> producto.presentacion>> producto.laboratorio >> producto.cantidad
				>> producto.precio >> producto.costo;

				if(codigo == producto.codigo)
				{
					encontrado = true;
					cout << "--------------------------------------------------------------"<< endl;
					cout << "                        Detalle: \n " << endl;
					cout << "Codigo: " << producto.codigo << endl;
					cout << "Marca: " << producto.marca << endl;
					cout << "descripcion: " << producto.descripcion << endl;
					cout << "Accion: " << producto.accionFarmacologica << endl;
					cout << "Presentacion: " << producto.presentacion << endl;
					cout << "Distribuidora: " << producto.laboratorio << endl;
					cout << "Costo: " << producto.costo << endl;
					cout << "---------------------------------------------------------------"<<endl;

					cout << "Esta seguro que desea comprar este producto? (S/N)";
					cin >> resp;
					if (resp == 's' || resp == 'S')
					{
						cout << "Cantidad: "; cin >> cantidad;
						if( producto.cantidad > cantidad)
						{

								cantidadFinal = producto.cantidad - cantidad;
								aux<<producto.codigo<<" "<<producto.marca<<" "<<producto.descripcion<<" "<<producto.accionFarmacologica<<" "<<
								producto.vencimiento << " " << producto.presentacion << " " << producto.laboratorio << " " << cantidadFinal <<
								" " << producto.precio << " " << producto.costo <<endl;
               					 cout<<"Registro Modificado"<<endl;
								TOTAL += producto.costo * cantidad;

						}
						else{
							cout << "Solo quedan " << producto.cantidad << " en existencia" << endl;
						}
                        lectura2 >> producto.codigo;
                        while(!lectura2.eof())
                        {
                            lectura >> USUARIO  >> producto.marca >>  cantidad  >>  producto.costo;
                        }
                        factura  << contador << cantidad << " " <<producto.marca<< " "  << producto.costo  << " " << producto.costo * cantidad <<endl;

					}
					else{
						cout << producto.marca ;
						 printf(" no a%cadido a la factura",164);
						 aux<<producto.codigo<<" "<<producto.marca<<" "<<producto.descripcion<<" "<<producto.accionFarmacologica<<" "<<
								producto.vencimiento << " " << producto.presentacion << " " << producto.laboratorio << " " << producto.cantidad <<
								" " << producto.precio << " " << producto.costo <<endl;
					}
				}
				else{
					aux<<producto.codigo<<" "<<producto.marca<<" "<<producto.descripcion<<" "<<producto.accionFarmacologica<<" "<<
								producto.vencimiento << " " << producto.presentacion << " " << producto.laboratorio << " " << producto.cantidad <<
								" " << producto.precio << " " << producto.costo <<endl;

				}
				lectura >> producto.codigo;
            }

            if (encontrado == false)
            {
                cout << "Producto con el codigo " << codigo << "no encotrado." << endl;
            }
            printf("Desea a%cadir otro producto? (S/N)",164);
            cin >> resp;
            resp = tolower(resp);
            if(resp == 'n')
            {
                salir  = true;

            }
                aux.close();
                lectura.close();
                remove("inventario.txt");
                rename("auxiliar.txt","inventario.txt");
                aux.open("auxiliar.txt", ios::out);
                lectura.open("inventario.txt", ios::in);

		}while(!salir);

	}
	else{
		cout << "No se pudo abrir el archivo especificado" << endl;
	}
	aux.close();
    lectura.close();
	system("pause");
}

void facturarse()
{
	FILE *archivo;
	FILE *archivo2;
	FILE *leer2;
	char caracter[100];
	ofstream imprimir;
	ifstream leer;
	ifstream leertodo;
	ofstream reporte;
	ofstream conteo;
	ifstream leerconteo;

	string texto;
	string usuario, auxproducto;
	int auxcantidad;
	float precio;
	int cantidad;
	imprimir.open("factura.txt", ios::out);
	leer.open("factura.txt", ios::in);
	leertodo.open("factura.txt", ios::in);
	reporte.open("reporte.txt", ios::out | ios::app);
	conteo.open("conteo.txt", ios::out);
	leerconteo.open("conteo.txt", ios::in);
	archivo = fopen("factura.txt","r");
	archivo2 = fopen("reporte.txt", "r");
	leer2 = fopen("conteo.txt", "r");
	if (imprimir.is_open() && leer.is_open() && leertodo.is_open() && reporte.is_open() && conteo.is_open() && leerconteo.is_open())
	{
			leerconteo >> c;
	/*	cout << c;
		system("pause");*/
		imprimir << "\n                                   Cajero RAPIDO" <<endl;
		imprimir << "                           Lucas Cordoba 704  " <<endl;
		imprimir << "                         Tel.:000 000 000\n\n" << endl;
		imprimir << "   Recibo: " << c << endl;
		imprimir << "   Fecha: " << "          " <<Fecha()<< "  " << Hora()<<endl;

		imprimir << "   TOTAL."<<"$"<< TOTAL << endl;
		imprimir << "   Cajero:"<< USUARIO <<endl;
		imprimir << "\n\n";
		imprimir << "   " << endl;

		//Aqui seguimos
		while(!feof(archivo))
		{
			fgets(caracter, 100,  archivo);
			puts(caracter);
			reporte << caracter;
		}
		reporte << endl << endl << endl << endl;
		fclose(archivo);



	}
	c++;
    conteo << c;
	imprimir.close();
	leer.close();
	leertodo.close();
	reporte.close();
	conteo.close();
	leerconteo.close();

	system("pause");
}
void menufactura()
{
	SetConsoleTitle("F A C T U R A C I O N");
	mostrarUsuario();

	char op;
	do
	{
		gotoxy(40,9);
		cout << "F a c t u r a c i o n" << endl;
		gotoxy(27,11);
		cout << "[1] Agregar Venta" << endl;
		gotoxy(27,12);
		cout << "[2] Imprimir" << endl;
		gotoxy(27,13);
		cout <<"[0] Regresar"<<endl;

		gotoxy(25,16);
		cout << "Ingrese opcion: "; cin >> op;

		switch(op)
		{
			case '1':
				{
					system("cls");
					agregarFactura();
					system("cls");
					break;
				}
			case '2':
				{
					system("cls");
					facturarse();
					system("cls");
					break;
				}
			case '0':
				{
					system("cls");
					break;
				}
			default:
				{
					system("cls");
					cout << "Error, opcion desconocida" << endl;
					Sleep(500);
					system("cls");
					break;
				}
		}
	}while(op!='0');

}

void menuFacturacion()
{
	SetConsoleTitle("FACTURACION");

	//---------Inicializando los punteros--------
	char op;
	do {
		mostrarUsuario();
		cout << endl;
		gotoxy(25,9);
        printf("                  F A C T U R A C I %c N",227);

		cout << endl;

		gotoxy(25,10);
		cout << "      [1] Agregar Venta                           " << endl;
		gotoxy(25,11);
		cout << "      [2] Productos Agotados                        	 " << endl;
		gotoxy(25,12);
		cout << "      [0] Salir              " << endl;

		gotoxy(25,16);
		cout << "Ingrese opcion: ";
		cin >> op;

		switch(op)
		{
			case '1':
				{
					system("cls");
					menufactura();
					system("cls");
					break;
				}
			case '2':
				{
					system("cls");
					agotando();
					system("cls");
					break;
				}
			case '0':
				{

					salir();
					break;
				}
			default:
				{
					system("cls");
					cout << "Error, opcion desconocida" << endl;
                    Sleep(500);
                    system("cls");
					break;
				}
		}



	}while(op!= '0');

}

void login()
{
	SetConsoleTitle("LOGIN");
	ofstream salida;
	ifstream lectura;

	string usuario;
	string contrasena;
	string auxusuario;
	string auxcontrasena;
	int rol;
	int contador = 0;
	int i = 0;
	char ch;
    bool ingresar = false;
    salida.open("registroUsuario.txt", ios::out|ios::app); //abriendo registro.dat
    lectura.open("registroUsuario.txt", ios::in);//abriendo registro.dat en lectura
    if(salida.is_open() & lectura.is_open())//validando si el archivo fue abierto
    {
        do{
			system("cls");
			gotoxy(15, 6);
			gotoxy(35,9);
			cout << "-A C C E S O   A L   S I S T E M A-" << endl;
			gotoxy(45,10);
			cout<<"Technology G - Leandro Gimenez "<<endl;
			gotoxy(45,13);
			cout << "Usuario: ";
			gotoxy(42,15);
			cout << "Contraseña: ";
			gotoxy(55,13);
			cin >> usuario;
			gotoxy(55,15);
			ch = getch();
			while(ch != 13){
			contrasena.push_back(ch);
			cout << '*';
			ch = getch();
			}

			cout << endl;
		lectura >> auxusuario;
		while(!lectura.eof())
		{
			lectura >> auxcontrasena >> rol;
			if(usuario == auxusuario && contrasena == auxcontrasena )
			{
				ingresar = true;
				break;
			}
			lectura >> auxusuario;

		}
		if(ingresar == false){
			system("cls");

			gotoxy(28,10);
			cout << "Usuario y/o contraseña incorrecto" << endl;
			Sleep(1000);
			contador ++;
			contrasena.clear();
		}
		if(contador == 3)
		{
			system("cls");
            gotoxy(28,10);
			cout << "Ha agotado el numero de intentos" << endl;
			gotoxy(28,11);
			cout << "Espere    segundos para volver a intentar" ;
			for (i = 20 ; i > 0; i--)
			{
				gotoxy(35 ,11);
				cout << i ;
				Sleep(1000);
			}
			contador = 0;

		}
		lectura.clear();
		lectura.seekg(0);
		}

		while(ingresar == false);

		if (ingresar == true){
			USUARIO = usuario;
			CONTRASENA = contrasena;

			if(rol == 0){
				ROL = "ADMINISTRADOR";
			}else{
				ROL = "CAJERO";
			}
			system("cls");

			gotoxy(0,8);
			for(int i=0;i<120;i++){
                cout<<"*";
                Sleep(1);
			}
			system("cls");

			lectura >> auxusuario;
			if (rol == 0)
			{
				menu();
			}
			else if(rol == 1)
			{
                menuFacturacion();
			}

		}
	 }
	 else{
	 	cout << "Error el archivo no se puedo cargar" << endl;
	 }
}


int main()
{
	system("COLOR B");
	SetConsoleTitle("Technology G");
	gotoxy(45,13);
    string introduccion = "T e c h n o l o g y G";
    for(int i = 0 ; i <= introduccion.length(); i++)
    {
        cout << introduccion[i];
        Sleep(100);
    }
	login();
	return 0;
	system("pause");
}
