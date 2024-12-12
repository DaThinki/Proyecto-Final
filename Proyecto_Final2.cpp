// Proyecto_Final2.cpp : Define el punto de entrada de la aplicación.
//


#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include "framework.h"
#include "Proyecto_Final2.h"
#include "resource.h"
#include <commctrl.h>
#include <commdlg.h>
#include <fstream>
#include <oleauto.h>
#include <wchar.h>
#include <locale.h>
#include <string>
#include <cwctype>
#include <windows.h>
#include <wchar.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <cwctype> 
#include <string.h>
#include <tchar.h>
#include <stdio.h> 
#include <sstream> 
#include <iomanip> 
#include <ctime>

using namespace std;
//////
//varaibles extra para la ejecucion
bool datosCorrectos = false;
double buscar_citas_de = 0;
double buscar_citas_al = 0;
int ID_SEARCH;

char ultimoUsuario[20];
char ultimaContrasena[20];
bool ultimoPuesto;
char file[MAX_PATH];

//---------------------------------------------Ids_Lista
//para que siempre se le asigne un id diferente a las cosas, gnerado automatico
struct Ids {
    Ids* anterior;
    int contadorProductos; 
    int contadorPedidos;
    int contadorUsuarios;
    Ids* siguiente;
};
Ids* ini_Ids;
Ids* fin_Ids;
Ids* aux_Ids;

//---------------------------------------------ADMIN_Lista
struct admin {
    admin* anterior;
    char usuarioAdmin[60];
    char adminPassword[60];
    admin* siguiente;
};
admin* ini_admin = nullptr;
admin* fin_admin = nullptr;
admin* aux_admin = nullptr;

//---------------------------------------------USUARIOS_ArbolBinario
struct usuarios {
    char correoElectronico[50];
    char password[30];
    char nombre[80];
    char apellidoPat[50];
    char apellidoMat[50];
    char rutaFoto[MAX_PATH];
    char genero[50];
    SYSTEMTIME fechaNac;
    int idUsuario;
    char nombreUsuario[255];
    usuarios* izquierda;
    usuarios* derecha;
}*raiz, * actualUsuarios;


//---------------------------------------------Ultimo Usuario_Lista
struct ultPas {//para el boton de ultimo que ingreso
    ultPas* anterior;
    char nombreUsuario[255];
    char password[30];
    ultPas* siguiente;
};

ultPas* ini_ult;
ultPas* aux_ult;
ultPas* fin_ult;

//---------------------------------------------PEDIDOS_Lista
struct pedidos {
    pedidos* anterior;
    int idPedido;                   
    int edadCliente;                
    char nacionalidadCliente[100];  
    int idProductoComprado;         
    int idCliente;                  
    bool pedidoEntregado;           
    char nombreCliente[50];         
    char apellidoPatCliente[50];    
    char apellidoMatCliente[50];    
    char metodoPago[17];            
    float precio;                   
    char origen[60];
    char destino[60];
    char nombreProducto[60];        
    char categoria[60];             // Categoría del producto (e.g., "Electrónica", "Ropa")
    int cantidadComprada;           // Cantidad de productos comprados
    pedidos* siguiente;
};
pedidos* ini_pedidos = nullptr;
pedidos* fin_pedidos = nullptr;
pedidos* aux_pedidos = nullptr;


//---------------------------------------------CLIENTES_Lista
struct clientes {
    char nombre[50];
    char key[50];//ocupamos este key de bsuqueda por si la persona tiene dos espacios en su nombre
    char apellidoMat[50];
    char apellidoPat[50];
    char nacionalidad[50];
    double fechaNacimiento;
    double telefono;
    char genero[50];
    SYSTEMTIME fechaNacPasajero;
    int numvuelo;
    char metodoPago[50];
    int idpasajeros;
    int edad;
    //REGISTRAR USUARIO FECHA Y HORA DE REGISTRO
    char usuarioQueRegistro[60];
    SYSTEMTIME fechaRegistro;


    clientes* siguiente;
    clientes* anterior;

};
clientes* ini_pasajeros = nullptr;
clientes* fin_pasajeros = nullptr;
clientes* aux_pasajeros = nullptr;
clientes* raiz_pasajeros = nullptr;


//---------------------------------------------PRODUCTOS_Lista
struct productos {
    int numvue;
    char origen[30];
    char destino[30];
    double fecha;
    double hora;
    char tipoav[30];
    float asientotal;
    float ejecutiva;
    int contadorAsientosEjecutiva;
    int contadorAsientosTurista;
    float turista;
    float precioejecutiva;
    float precioturista;
    float mayores;
    float menores;
    float diascan;
    int idvuelo;//id de busqeuda
    int cantBoletosVendidos;
    SYSTEMTIME fechaVuelo;
    SYSTEMTIME horaVuelo;
    bool vueloRealizado;// Para verificar si esta dado de alta el producto
    bool pasajerosRegistrados; // si tiene clientes registrados
    char usuarioQueRegistro[60];
    SYSTEMTIME fechaRegistro;

    productos* siguiente;
    productos* anterior;
};
productos* ini_vuelos = nullptr;
productos* fin_vuelos = nullptr;
productos* aux_vuelos = nullptr;








int x = 0;
#define ID_TIMER1 1000
#define MAX_LOADSTRING 100

productos* vueloEncontrado = nullptr; // Debido extrañas razones para dar vuelos de alta y baja en confimrar/cancelar vuelos funciona si la variable es global.

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];
HINSTANCE hinstGlobal;// nombre de clase de la ventana principal

int contadorVuelos = 0;
int contadorpasajeros = 0;
int contadorboletos = 0;
int contadorPedidos = 0;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    MostrarPorFecha(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    InicioSesion(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    VentanaAdmin(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    RegistroAdmin(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    RegistroUsuario(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Principal(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    RegistroPasajeros(HWND, UINT, WPARAM, LPARAM);//Hecho
LRESULT CALLBACK    RegistroVuelos(HWND, UINT, WPARAM, LPARAM);//Hecho 
LRESULT CALLBACK    CancelarConfirmarProductos(HWND, UINT, WPARAM, LPARAM);//Hecho
LRESULT CALLBACK    ReporteVuelos(HWND, UINT, WPARAM, LPARAM);//<--- Faltantes
LRESULT CALLBACK    Manifiesto(HWND, UINT, WPARAM, LPARAM);//<---Faltantes
LRESULT CALLBACK    CompraProductos(HWND, UINT, WPARAM, LPARAM);//<--- Faltantes
LRESULT CALLBACK    CancelarConfirmarPedido(HWND, UINT, WPARAM, LPARAM);//Hecho 
LRESULT CALLBACK    AdminIniciado(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//funciones de mia
bool menu(int, HWND);
productos* BinaryF(productos*, int);
productos* middleVuelos(productos*, productos*);
clientes* BusquedaBinariaNombre(clientes*, WCHAR*);
clientes* middle(clientes*, clientes*);
clientes* BinaryP(clientes*, int);
clientes* middlepas(clientes*, clientes*);


void ordenarPedidos(pedidos*&, bool (*comparar)(pedidos*, pedidos*));
bool compararPorCantidad(pedidos*, pedidos*);
bool compararPorCliente(pedidos*, pedidos*); 


int generarPase(clientes*);
//prototipos funciones de asael

//---------------------------------------------Ids_Lista
void agregarIds(Ids*);
void leerIds(char[]);
void escribirIds(char[]);
//---------------------------------------------ADMIN_Lista
void agregarAdmin(admin*);
void leeradmin(char[]);
void escribiradmin(char[]);
//---------------------------------------------USUARIOS_ArbolBinario
bool registroUsuario(usuarios**, usuarios*);
bool buscarUsuario(usuarios*, char*);
void recorrerPreorden(usuarios*, HWND);
void ListaUsuarios(usuarios*, HWND);
void escribirArchivoUsuario(char[], usuarios*);
void escribirNodoDirecto(ofstream&, usuarios*);
void leerArchivoUsuarios(char[]);
void leerNodoDirecto(ifstream&);
//---------------------------------------------Ultimo Usuario_Lista
void agregarUltPas(ultPas* nuevoUltPas);
void leerUltPas(char archivo[]);
void escribirUltPas(char archivo[]);
//---------------------------------------------BOLETOS_Lista
void agregarPedido(pedidos* nuevoPedido);
void leerPedidos(char archivo[]);
void escribirPedidos(char archivo[]);
void guardarPedidosEnArchivo(pedidos* cabeza, const string& nombreArchivo);
//---------------------------------------------CLIENTES_Lista
void agregarPasajero(clientes* nuevoPasajero);
void escribirPasajeros(char archivo[]);
void leerPasajeros(char archivo[]);
//---------------------------------------------PRODUCTOS_Lista
void agregarVuelo(productos* nuevoVuelo);
void leerVuelos(char archivo[]);
void escribirVuelos(char archivo[]);
void guardarListaEnArchivo(productos* cabeza, const std::string& nombreArchivo);
void eliminarVuelo(productos* vueloEliminar);
void MostrarDetallesVueloEnLista(productos* vuelo, HWND hWnd, int listaID);
//---------------------------------------------FUNCIONES DEL QUICKSORT

void swap(pedidos* a, pedidos* b);//void swap(boletos* a, boletos* b);
pedidos* partition(pedidos* low, pedidos* high);//boletos* partition(boletos* low, boletos* high);
void quickSort(pedidos* low, pedidos* high);//void quickSort(boletos* low, boletos* high);
pedidos* getLastNode(pedidos* node);//boletos* getLastNode(boletos* node);
void ordenarPedidosDescendenteQuicksort();//void ordenarBoletosDecendenteQuicksort();

//---------------------------------------------FUNCIONES DEL HEAPSORT
void heapify(pedidos arr[], int n, int i);//void heapify(boletos arr[], int n, int i);
void heapSort(pedidos arr[], int n);//void heapSort(boletos arr[], int n);

//---------------------------------------------EXTRA
void ActualizarListBox(HWND hWnd);
void GuardarListBoxEnArchivo(HWND hWndListBox, const char* nombreArchivo);



void ponerFotoyNombre(HWND);
productos* buscarVueloPorDestino(const char*);
productos* buscarVueloPorFechaYDestino(const string&, const char*, int idmandar);
productos* buscarPorId(int idmandar);
void escribirVuelos(char[]);
void leerVuelos(char[]);
void agregarVuelo(productos*);
double FileTimeToDouble(FILETIME ft);
void AddStringToListBox(HWND hWnd, int listBoxId, const std::string& text);

void escribirUserlast(const char*);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    // LEER ADMIN
    char admincarpeta[MAX_PATH] = "";
    char archivoadmin[] = "\\admin.dat";
    GetCurrentDirectory(MAX_PATH, admincarpeta);
    strcat_s(admincarpeta, sizeof(admincarpeta), archivoadmin);
    leeradmin(admincarpeta);

    // LEER USUARIOS
    char usuariosCarpeta[MAX_PATH] = "";
    char archivoUsuarios[] = "\\usuarios.dat";
    GetCurrentDirectory(MAX_PATH, usuariosCarpeta);
    strcat_s(usuariosCarpeta, sizeof(usuariosCarpeta), archivoUsuarios);
    leerArchivoUsuarios(usuariosCarpeta);

    // LEER ULTIMO USUARIO
    char lastUserCarpeta[MAX_PATH] = "";
    char archivoLastUser[] = "\\ultUsuario.dat";
    GetCurrentDirectory(MAX_PATH, lastUserCarpeta);
    strcat_s(lastUserCarpeta, sizeof(lastUserCarpeta), archivoLastUser);
    leerUltPas(lastUserCarpeta);


    // LEER VUELOS
    char vueloscarpeta[MAX_PATH] = "";
    char archivovuelo[] = "\\productos.dat";
    GetCurrentDirectory(MAX_PATH, vueloscarpeta);
    strcat_s(vueloscarpeta, sizeof(vueloscarpeta), archivovuelo);
    leerVuelos(vueloscarpeta);

    // LEER PEDIDOS
    char pedidosCarpeta[MAX_PATH] = "";
    char archivoPedidos[] = "\\pedidos.dat";
    GetCurrentDirectory(MAX_PATH, pedidosCarpeta);
    strcat_s(pedidosCarpeta, sizeof(pedidosCarpeta), archivoPedidos);
    leerPedidos(pedidosCarpeta);

    //LEER PASAJEROS
    char pasajerosCarpeta[MAX_PATH] = "";
    char archivoPasajeros[] = "\\clientes.dat";
    GetCurrentDirectory(MAX_PATH, pasajerosCarpeta);
    strcat_s(pasajerosCarpeta, sizeof(pasajerosCarpeta), archivoPasajeros);
    leerPasajeros(pasajerosCarpeta);

    //LEER IDS 
    char IdsCarpeta[MAX_PATH] = "";
    char archivoIds[] = "\\ids.dat";
    GetCurrentDirectory(MAX_PATH, IdsCarpeta);
    strcat_s(IdsCarpeta, sizeof(IdsCarpeta), archivoIds);
    leerIds(IdsCarpeta);
    if (ini_Ids == nullptr) {
        ini_Ids = new Ids; // Asignar memoria para el nodo
        ini_Ids->contadorProductos = 0;
        ini_Ids->contadorUsuarios = 0;
        ini_Ids->contadorPedidos = 0;
        ini_Ids->anterior = nullptr;
        ini_Ids->siguiente = nullptr;
        fin_Ids = ini_Ids; // Si es el único nodo, fin_Ids también apunta a él
    }
    else {
        contadorVuelos = ini_Ids->contadorProductos;
        contadorpasajeros = ini_Ids->contadorUsuarios;
        contadorPedidos = ini_Ids->contadorPedidos;
    }


    hinstGlobal = hInstance;
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDPROYECTOFINAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    if (!InitInstance(hInstance, nCmdShow)) { return FALSE; }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDPROYECTOFINAL));
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    escribirVuelos(vueloscarpeta);
    escribirArchivoUsuario(usuariosCarpeta, raiz);
    escribiradmin(admincarpeta);
    escribirPedidos(pedidosCarpeta);
    escribirPasajeros(pasajerosCarpeta);
    escribirUltPas(lastUserCarpeta);

    if (ini_Ids != nullptr) {
        ini_Ids->contadorProductos = contadorVuelos;
        ini_Ids->contadorUsuarios = contadorpasajeros;
        ini_Ids->contadorPedidos = contadorboletos;
        escribirIds(IdsCarpeta);
    }

    escribirIds(IdsCarpeta);


    return (int)msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = InicioSesion;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDPROYECTOFINAL));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_EDPROYECTOFINAL);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;
    HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(ID_InicioSesion), NULL, InicioSesion);
    if (!hWnd) { return FALSE; }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

//---------------------------------------------INICO CALLBACKS
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Agregar cualquier código de dibujo que use hDC aquí...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;


}
LRESULT CALLBACK MostrarPorFecha(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG: {



        SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("PEDIDOS:"));
        // Inicializar la lista de vuelos
        productos* actual = ini_vuelos;
        while (actual != nullptr) {
            //Te pasaste de lanzota lo pusiste  actual->fecha y esa ni tiene nada no manches, se supone que se usan actual->fechaVuelo es la que se usa en las fechas, no te pases.
            double fechaVuelo_double = 0;
            SystemTimeToVariantTime(&(actual->fechaVuelo), &fechaVuelo_double);


            if (fechaVuelo_double >= buscar_citas_de && fechaVuelo_double <= buscar_citas_al) {

                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("ID PEDIDOS:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->idvuelo).c_str()));
                int opc = SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("lugar de envio:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(actual->origen));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("Destino:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(actual->destino));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("Tipo de producto:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(actual->tipoav));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("Total de unidades:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, opc, (LPARAM)(to_string(actual->asientotal).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("Total de unidades con caja:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->ejecutiva).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("precio:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioejecutiva).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("Total de unidades sin caja:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->turista).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("precio:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioturista).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("# de unidades en reserva:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->menores).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("# de unidades en caja:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->mayores).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-Fecha y hora de registro:"));
                string fecha_a_mostrar =
                    to_string(actual->fechaRegistro.wDay) + '/' +
                    to_string(actual->fechaRegistro.wMonth) + '/' +
                    to_string(actual->fechaRegistro.wYear);
                string hora_a_mostrar =
                    to_string(actual->fechaRegistro.wHour) + ':' +
                    to_string(actual->fechaRegistro.wMinute);
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT((fecha_a_mostrar).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT((hora_a_mostrar).c_str()));
            }

            actual = actual->siguiente;
        }

    }break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case ID_GnerarArchivo: {

            guardarListaEnArchivo(ini_vuelos, "pedidosPorFecha.txt");

        }break;
        case ID_RegRan: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_ReporteVuelos), NULL, ReporteVuelos);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);

        }break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Agregar cualquier código de dibujo que use hDC aquí...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
LRESULT CALLBACK InicioSesion(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case ID_Salir: {
            int ventana = MessageBox(0, "Seguro que desea salir?", "Aviso", MB_YESNO | MB_ICONQUESTION);
            switch (ventana) {
            case IDYES:
                DestroyWindow(hWnd);
                break;
            }break;

        }break;
        case ID_Admin: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_VentanaAdmin), NULL, VentanaAdmin);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }   break;
        case ID_Ingresar: {
            char usuario[60];
            char password[60];
            GetDlgItemText(hWnd, ID_Usuario, usuario, 20);
            if (strlen(usuario) <= 0) {
                MessageBox(hWnd, "Favor de ingresar usuario", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            GetDlgItemText(hWnd, ID_Password, password, 20);
            if (strlen(password) <= 0) {
                MessageBox(hWnd, "Favor de ingresar contrasenia", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }


            //revisar que el usuario exista 


            if (buscarUsuario(raiz, usuario) == true)
            {
                if (strcmp(password, actualUsuarios->password) == 0) {

                    ultPas* nuevoUltPass = new ultPas;
                    strcpy_s(nuevoUltPass->nombreUsuario, actualUsuarios->nombreUsuario);
                    strcpy_s(nuevoUltPass->password, actualUsuarios->password);
                    agregarUltPas(nuevoUltPass);


                    HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
                    ShowWindow(ventana, SW_SHOW);
                    EndDialog(hWnd, 0);
                }
            }
            else
            {
                MessageBox(hWnd, "Usuario no existe", "AVISO", MB_OK | MB_ICONINFORMATION);
                break;
            }


        }break;
        case ID_UltReg: {
            if (ini_ult == nullptr) {
                MessageBox(hWnd, "Nadie se ha iniciado sesion", "Error", MB_OK | MB_ICONERROR);
                break;
            }
            else
            {
                SetDlgItemText(hWnd, ID_Usuario, ini_ult->nombreUsuario);
                SetDlgItemText(hWnd, ID_Password, ini_ult->password);
            }

        }break;
        case IDM_ABOUT: {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        }   break;
        case IDM_EXIT: {
            DestroyWindow(hWnd);
        }   break;
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
LRESULT CALLBACK VentanaAdmin(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ID_RegistroAdm: {
            bool yahayadmin = false;
            admin* actualadmin = ini_admin;
            while (actualadmin != nullptr)
            {
                yahayadmin = true; // Tan pronto como encontremos un admin, establecemos yahayadmin a true
                break; // Salimos del bucle ya que no necesitamos buscar más
                actualadmin = actualadmin->siguiente;
            }

            if (yahayadmin)
            {
                MessageBox(hWnd, "YA HAY UN ADMIN REGISTRADO", "ATENCION", MB_OK | MB_ICONERROR);
            }
            else
            {
                int window = MessageBox(hWnd, "El admin solo se puede registrar una vez, ¿continuar?", "Aviso", MB_YESNO | MB_ICONQUESTION);
                if (window == IDYES)
                {
                    HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_RegistroDeAdmin), hWnd, RegistroAdmin);
                    ShowWindow(ventana, SW_SHOW);
                    EndDialog(hWnd, 0);
                }
            }
        }break;
        case ID_Ingresar: {

            char textow[255];
            char textow2[255];

            GetDlgItemText(hWnd, ID_UsuarioAdm, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de ingresar su usuario", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            GetDlgItemText(hWnd, ID_PasswordAdm, textow2, 255);
            if (strlen(textow2) <= 0) {
                MessageBox(hWnd, "Favor de ingresar su contrasenia", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            admin* actual = ini_admin;
            while (actual != nullptr) {
                if (strcmp(actual->usuarioAdmin, textow) == 0 && strcmp(actual->adminPassword, textow2) == 0)
                {
                    datosCorrectos = true;
                    break;
                }
                actual = actual->siguiente;
            }

            if (datosCorrectos)
            {
                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_AdminSesion), hWnd, AdminIniciado);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
                datosCorrectos = false;
            }
            else
            {
                MessageBox(hWnd, "El usuario o la contrasenia no coinciden. Favor de verificar e ingresar los datos correctos", "Error", MB_OK | MB_ICONERROR);
            }



        }
                        break;
        case ID_RegAdm: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_InicioSesion), hWnd, InicioSesion);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }
                      break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
LRESULT CALLBACK RegistroAdmin(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ID_RegistroAdmin: {
            admin* nuevoadmin = new admin;

            char textow[255];
            GetDlgItemText(hWnd, IDC_EDIT1, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de ingresar usuario", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            strcpy_s(nuevoadmin->usuarioAdmin, sizeof(nuevoadmin->usuarioAdmin), textow);

            GetDlgItemText(hWnd, IDC_EDIT2, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de ingresar contrasenia", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            strcpy_s(nuevoadmin->adminPassword, sizeof(nuevoadmin->adminPassword), textow);

            // Agregar el nuevo admin a la lista
            agregarAdmin(nuevoadmin);

            MessageBox(hWnd, "Se registro al admin", "ATENCION", MB_OK | MB_ICONEXCLAMATION);

            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_VentanaAdmin), hWnd, VentanaAdmin);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }
                             break;
        case ID_Regreso: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_VentanaAdmin), hWnd, VentanaAdmin);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }
                       break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
        return 0;
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Agregar cualquier código de dibujo que use hDC aquí...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
LRESULT CALLBACK AdminIniciado(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG: {
        // Aquí deberías poner el código que necesitas ejecutar cuando se inicializa el diálogo
        admin* actual = ini_admin;
        while (actual != nullptr)
        {
            SetDlgItemText(hWnd, ID_NombreAdmin, actual->usuarioAdmin);
            actual = actual->siguiente;
        }
        return TRUE; // Devuelve TRUE para indicar que has procesado este mensaje
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case ID_CANCEL_REGI: {
            int window = MessageBox(hWnd, "Seguro desea cerrar sesion?", "Aviso", MB_YESNO | MB_ICONQUESTION);
            if (window == IDYES)
            {
                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_InicioSesion), NULL, InicioSesion);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }
        }
                           break;
        case ID_RegistrarUsuarios: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_RegistroUsuario), NULL, RegistroUsuario);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }
                                 break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Agregar cualquier código de dibujo que use hDC aquí...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
LRESULT CALLBACK RegistroUsuario(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case ID_RegistrarUsuario: {
            // Creo el nodo
            usuarios* nodonuevo = new usuarios;
            nodonuevo->izquierda = nullptr;
            nodonuevo->derecha = nullptr;
            char textow[255]; // variable para almacenar datos temporales

            // Obtener y validar el nombre
            GetDlgItemText(hWnd, ID_NombUs, nodonuevo->nombre, sizeof(nodonuevo->nombre));
            if (strlen(nodonuevo->nombre) <= 0) {
                MessageBox(hWnd, "Favor de ingresar el nombre", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }




            // Obtener y validar el apellido paterno
            GetDlgItemText(hWnd, ID_User3, nodonuevo->apellidoPat, sizeof(nodonuevo->apellidoPat));
            if (strlen(nodonuevo->apellidoPat) <= 0) {
                MessageBox(hWnd, "Favor de ingresar apellido paterno", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }



            // Obtener y validar el apellido materno
            GetDlgItemText(hWnd, ID_User2, nodonuevo->apellidoMat, sizeof(nodonuevo->apellidoMat));
            if (strlen(nodonuevo->apellidoMat) <= 0) {
                MessageBox(hWnd, "Favor de ingresar apellido materno", "ATENCION", MB_OK | MB_ICONERROR);

                break;
            }


            // Obtener y validar el correo electrónico
            GetDlgItemText(hWnd, ID_CorreoUs, nodonuevo->correoElectronico, sizeof(nodonuevo->correoElectronico));
            if (strlen(nodonuevo->correoElectronico) <= 0) {
                MessageBox(hWnd, "Favor de ingresar correo valido", "ATENCION", MB_OK | MB_ICONERROR);

                break;
            }


            // Obtener y validar la contraseña
            GetDlgItemText(hWnd, ID_PassUs, nodonuevo->password, sizeof(nodonuevo->password));
            if (strlen(nodonuevo->password) <= 0) {
                MessageBox(hWnd, "Favor de ingresar una contrasenia", "ATENCION", MB_OK | MB_ICONERROR);

                break;
            }


            // Obtener y validar el nombre de usuario
            GetDlgItemText(hWnd, ID_User, nodonuevo->nombreUsuario, sizeof(nodonuevo->nombreUsuario));
            if (strlen(nodonuevo->nombreUsuario) <= 0) {
                MessageBox(hWnd, "Favor de ingresar un nombre de usuario valido", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            //fecha actual
            SYSTEMTIME fecha_sistema = { 0 };
            GetLocalTime(&fecha_sistema);

            // Obtener la fecha de nacimiento
            SYSTEMTIME fechaNacimiento;
            DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), &fechaNacimiento);


            // Calcular la edad
            int edad = fecha_sistema.wYear - fechaNacimiento.wYear;
            if (fecha_sistema.wMonth < fechaNacimiento.wMonth ||
                (fecha_sistema.wMonth == fechaNacimiento.wMonth && fecha_sistema.wDay < fechaNacimiento.wDay)) {
                edad--;
            }

            // Validar si es mayor de 18 años
            if (edad < 18) {
                MessageBox(hWnd, "No se puede registrar no es mayor de 18", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            if (fechaNacimiento.wYear > fecha_sistema.wYear ||
                (fechaNacimiento.wYear == fecha_sistema.wYear && fechaNacimiento.wMonth > fecha_sistema.wMonth) ||
                (fechaNacimiento.wYear == fecha_sistema.wYear && fechaNacimiento.wMonth == fecha_sistema.wMonth && fechaNacimiento.wDay > fecha_sistema.wDay)) {
                MessageBox(hWnd, "No se puede registrar una fecha futura", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            nodonuevo->fechaNac = fechaNacimiento;


            // Obtener y validar el género
            if (IsDlgButtonChecked(hWnd, ID_Mascu) == BST_CHECKED) {
                strcpy_s(nodonuevo->genero, "Masculino");
            }
            else if (IsDlgButtonChecked(hWnd, ID_Femen) == BST_CHECKED) {
                strcpy_s(nodonuevo->genero, "Femenino");
            }
            else {
                MessageBox(hWnd, "Favor de seleccionar el genero", "ATENCIÓN", MB_OK | MB_ICONERROR);
                break;
            }




            strcpy_s(nodonuevo->rutaFoto, file);

            // Intentar registrar el usuario
            if (registroUsuario(&raiz, nodonuevo)) {
                MessageBox(0, "Usuario registrado", "AVISO", MB_OK | MB_ICONINFORMATION);
                // Abrir la ventana de sesión de admin
                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_AdminSesion), NULL, AdminIniciado);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }
            else {
                MessageBox(0, "El nombre de usuario ya esta registrado", "AVISO", MB_OK | MB_ICONERROR);
                delete nodonuevo; // Liberar memoria si el registro falla
            }


        } break;

        case ID_Navegar: {
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = "Todos\0*.*\0ImagenBMP\0*.bmp\0";
            ofn.lpstrFile = file;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(file);
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            ofn.nFilterIndex = 2;



            if (GetOpenFileName(&ofn) == TRUE) {
                HBITMAP bmp;

                bmp = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

                SendDlgItemMessage(hWnd, ID_FotoUsuario, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
            }
            else {
                MessageBox(hWnd, "Seleccione imagen de usuario", "AVISO", MB_OK | MB_ICONERROR);
            }
        } break;

        case ID_RegresoRegistro: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_AdminSesion), NULL, AdminIniciado);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        } break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
LRESULT CALLBACK Principal(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG: {

        HBITMAP imagen = (HBITMAP)LoadImage(hInst, actualUsuarios->rutaFoto, IMAGE_BITMAP, 100, 100, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
        SendMessage(GetDlgItem(hWnd, ID_FotoUserActual), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
        SetDlgItemText(hWnd, ID_NombUserActual, actualUsuarios->nombreUsuario);

    }break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd))
        {
            return FALSE;
        }
        switch (wmId)
        {
        case ID_CerrarSesion: {
            int window = MessageBox(hWnd, "Seguro desea cerrar sesion?", "Aviso", MB_YESNO | MB_ICONQUESTION);
            if (window == IDYES)
            {
                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_InicioSesion), NULL, InicioSesion);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }

        }break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        }
    }
    break;
    case WM_DESTROY: {
        PostQuitMessage(0);
    }break;

    }
    return 0;
}
bool menu(int opcion, HWND hWnd) {
    switch (opcion)
    {
    case ID_PASAJEROS_RESGISTRARPASAJEROS: {
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_RegistroPasajeros), NULL, RegistroPasajeros);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    case ID_VUELOS_REGSITROVUELOS: {
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_RegistroVuelos), NULL, RegistroVuelos);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    case ID_VUELOS_CANCELAR_CONFIRMAR: {
        if (ini_vuelos == nullptr) {
            MessageBox(hWnd, "Registra un pedido", "Error", MB_OK | MB_ICONERROR);
            break;
        }
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_CancelarVuelos), NULL, CancelarConfirmarProductos);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    case ID_VUELOS_REPORTEVEULOS: {
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_ReporteVuelos), NULL, ReporteVuelos);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    case ID_VUELOS_MANIFIESTO: {
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Manifiesto), NULL, Manifiesto);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    case ID_BOLETOS_COMPRARBOLETOS: {
        // Validación si no hay boletos o vuelos todavía
        if (ini_pasajeros == nullptr || ini_vuelos == nullptr) {
            MessageBox(hWnd, "Registre Clientes o Pedidos antes.", "Error", MB_OK | MB_ICONERROR);
            break;
        }
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_CompraBoletos), NULL, CompraProductos);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);


    }break;
    case ID_SalirTotal: {
        int ventana = MessageBox(0, "Seguro que desea salir?", "Aviso", MB_YESNO | MB_ICONQUESTION);
        switch (ventana) {
        case IDYES:
            DestroyWindow(hWnd);
            break;
        }break;
    }break;
    case ID_BOLETOS_CANCELAR_CONFIRMAR: {
        if (ini_pasajeros == nullptr) {
            MessageBox(hWnd, "Para eliminar pedidos debes comprarlos antes", "Error", MB_OK | MB_ICONERROR);
            break;
        }
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_CancelarConfirmarBoletos), NULL, CancelarConfirmarPedido);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    default: { return false; }

    }
    return true;
}
LRESULT CALLBACK RegistroPasajeros(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG: {
        HBITMAP imagen = (HBITMAP)LoadImage(hInst, actualUsuarios->rutaFoto, IMAGE_BITMAP, 100, 100, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
        SendMessage(GetDlgItem(hWnd, ID_FotoUserActual), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
        SetDlgItemText(hWnd, ID_NombUserActual, actualUsuarios->nombreUsuario);
    }break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId) {
        case ID_RegistroPasajero: {
            clientes* nuevoPasajero = new clientes;

            char textow[255];

            // Obtener y validar el nombre
            GetDlgItemText(hWnd, ID_NombPasajero, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de ingresar el nombre", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            for (int i = 0; i < strlen(textow); i++) {
                if (!iswalpha(textow[i])) {
                    MessageBox(hWnd, "El nombre solo debe contener letras", "ATENCION", MB_OK | MB_ICONERROR);
                    break;
                }
            }

            //Sacar la key pra busqueda
            char key[50];
            int j = 0;
            for (int i = 0; i < strlen(textow) && j < 49; i++) {
                if (textow[i] != ' ') {
                    key[j] = textow[i];
                    j++;
                }
            }
            key[j] = '\0'; // Añadir el carácter nulo al final

            strcpy_s(nuevoPasajero->nombre, textow);
            strcpy_s(nuevoPasajero->key, key);

            // Obtener y validar el apellido paterno
            GetDlgItemText(hWnd, ID_ApellidoPasajero, textow, 50);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de ingresar el apellido paterno", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            for (int i = 0; i < strlen(textow); i++) {
                if (!iswalpha(textow[i])) {
                    MessageBox(hWnd, "El apellido paterno solo debe contener letras", "ATENCION", MB_OK | MB_ICONERROR);
                    break;
                }
            }
            strcpy_s(nuevoPasajero->apellidoPat, textow);

            // Obtener y validar el apellido materno
            GetDlgItemText(hWnd, ID_ApellidoMatPasajero, textow, 50);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de ingresar el apellido materno", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            for (int i = 0; i < strlen(textow); i++) {
                if (!iswalpha(textow[i])) {
                    MessageBox(hWnd, "El apellido materno solo debe contener letras", "ATENCION", MB_OK | MB_ICONERROR);
                    break;
                }
            }
            strcpy_s(nuevoPasajero->apellidoMat, textow);

            //
            // Obtener y validar la nacionalidad
            GetDlgItemText(hWnd, ID_NacionalidadPasajero, textow, 50);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de ingresar la nacionalidad", "ATENCIÓN", MB_OK | MB_ICONERROR);
                break;
            }

            bool error = false;
            for (int i = 0; i < strlen(textow); i++) {
                if (!iswalpha(textow[i])) {
                    error = true;
                }
            }

            if (error)
            {
                MessageBox(hWnd, "La nacionalidad solo debe contener letras", "ATENCIÓN", MB_OK | MB_ICONERROR);
                break;
            }
            strcpy_s(nuevoPasajero->nacionalidad, textow);

            // Obtener y validar el teléfono
            GetDlgItemText(hWnd, ID_NumTelefono, textow, 50);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de ingresar el contacto", "ATENCIÓN", MB_OK | MB_ICONERROR);
                break;
            }
            if (strlen(textow) != 8 && strlen(textow) != 10 && strlen(textow) != 12) {
                MessageBox(hWnd, "El numero de contacto debe tener 8, 10 o 12 números", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            for (int i = 0; i < strlen(textow); i++) {
                if (!iswdigit(textow[i])) {
                    MessageBox(hWnd, "El numero de contacto solo debe contener números", "ATENCION", MB_OK | MB_ICONERROR);
                    break;
                }
            }
            nuevoPasajero->telefono = atol(textow);

            // Obtener y validar el género
            if (IsDlgButtonChecked(hWnd, ID_Mascu) == BST_CHECKED) {
                strcpy_s(nuevoPasajero->genero, "Masculino");
            }
            else if (IsDlgButtonChecked(hWnd, ID_Femen) == BST_CHECKED) {
                strcpy_s(nuevoPasajero->genero, "Femenino");
            }
            else {
                MessageBox(hWnd, "Favor de seleccionar el genero", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }


            //obtener la fecha

            //fecha actual
            SYSTEMTIME fecha_sistema = { 0 };
            GetLocalTime(&fecha_sistema);

            // Obtener la fecha de nacimiento del pasajero
            SYSTEMTIME fechaNacimientoPasajero;
            DateTime_GetSystemtime(GetDlgItem(hWnd, ID_NaciPsajero), &fechaNacimientoPasajero);

            // Calcular la diferencia en días entre las fechas
            FILETIME ft1, ft2;
            SystemTimeToFileTime(&fechaNacimientoPasajero, &ft1);
            SystemTimeToFileTime(&fecha_sistema, &ft2);

            ULARGE_INTEGER uli1, uli2;
            uli1.LowPart = ft1.dwLowDateTime;
            uli1.HighPart = ft1.dwHighDateTime;
            uli2.LowPart = ft2.dwLowDateTime;
            uli2.HighPart = ft2.dwHighDateTime;

            int diferenciaDias = static_cast<int>((uli2.QuadPart - uli1.QuadPart) / (10000 * 1000 * 60 * 60 * 24)); // 10000 (ticks en un milisegundo), 1000 (milisegundos en un segundo), 60 (segundos en un minuto), 60 (minutos en una hora), 24 (horas en un día)

            if (diferenciaDias < 7) {
                MessageBox(hWnd, "NO PUEDES REALIZAR COMPRAS CON ESA EDAD", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            if (fechaNacimientoPasajero.wYear > fecha_sistema.wYear ||
                (fechaNacimientoPasajero.wYear == fecha_sistema.wYear && fechaNacimientoPasajero.wMonth > fecha_sistema.wMonth) ||
                (fechaNacimientoPasajero.wYear == fecha_sistema.wYear && fechaNacimientoPasajero.wMonth == fecha_sistema.wMonth && fechaNacimientoPasajero.wDay > fecha_sistema.wDay)) {
                MessageBox(hWnd, "No se puede registrar una fecha futura", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            nuevoPasajero->fechaNacPasajero = fechaNacimientoPasajero;

            // Calcular la edad
            int edad = fecha_sistema.wYear - fechaNacimientoPasajero.wYear;
            if (fecha_sistema.wMonth < fechaNacimientoPasajero.wMonth ||
                (fecha_sistema.wMonth == fechaNacimientoPasajero.wMonth && fecha_sistema.wDay < fechaNacimientoPasajero.wDay)) {
                edad--;
            }

            nuevoPasajero->edad = edad;
            nuevoPasajero->fechaRegistro = fecha_sistema;
            strcpy_s(nuevoPasajero->usuarioQueRegistro, actualUsuarios->nombreUsuario);

            // Agregar el nuevo pasajero a la lista doblemente enlazada
            contadorpasajeros += 1;
            nuevoPasajero->idpasajeros = contadorpasajeros;
            agregarPasajero(nuevoPasajero);

            MessageBox(hWnd, "Cliente registrado con exito", "Registro", MB_OK);
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        } break;


        case ID_CancelPasajero: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        } break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    } break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Agregar cualquier código de dibujo que use hDC aquí...
        EndPaint(hWnd, &ps);
    } break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return 0;
}
LRESULT CALLBACK RegistroVuelos(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG: {

        HBITMAP imagen = (HBITMAP)LoadImage(hInst, actualUsuarios->rutaFoto, IMAGE_BITMAP, 100, 100, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
        SendMessage(GetDlgItem(hWnd, ID_FotoUserActual), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
        SetDlgItemText(hWnd, ID_NombUserActual, actualUsuarios->nombreUsuario);

        SendMessage(GetDlgItem(hWnd, ID_ComboOrigen), CB_INSERTSTRING, 0, (LPARAM)"Monterey");
        SendMessage(GetDlgItem(hWnd, ID_ComboOrigen), CB_INSERTSTRING, 0, (LPARAM)"Guadalajara");
        SendMessage(GetDlgItem(hWnd, ID_ComboOrigen), CB_INSERTSTRING, 0, (LPARAM)"CDMX");
        SendMessage(GetDlgItem(hWnd, ID_ComboOrigen), CB_INSERTSTRING, 0, (LPARAM)"Tijuana");
        SendMessage(GetDlgItem(hWnd, ID_ComboOrigen), CB_INSERTSTRING, 0, (LPARAM)"Houston");

        SendMessage(GetDlgItem(hWnd, ID_ComboDestino), CB_INSERTSTRING, 0, (LPARAM)"Monterey");
        SendMessage(GetDlgItem(hWnd, ID_ComboDestino), CB_INSERTSTRING, 0, (LPARAM)"Guadalajara");
        SendMessage(GetDlgItem(hWnd, ID_ComboDestino), CB_INSERTSTRING, 0, (LPARAM)"CDMX");
        SendMessage(GetDlgItem(hWnd, ID_ComboDestino), CB_INSERTSTRING, 0, (LPARAM)"Tijuana");
        SendMessage(GetDlgItem(hWnd, ID_ComboDestino), CB_INSERTSTRING, 0, (LPARAM)"Houston");

        SendMessage(GetDlgItem(hWnd, ID_TipoAvion), CB_INSERTSTRING, 0, (LPARAM)"Comida");
        SendMessage(GetDlgItem(hWnd, ID_TipoAvion), CB_INSERTSTRING, 0, (LPARAM)"Figuras");
        SendMessage(GetDlgItem(hWnd, ID_TipoAvion), CB_INSERTSTRING, 0, (LPARAM)"Muebles");
        SendMessage(GetDlgItem(hWnd, ID_TipoAvion), CB_INSERTSTRING, 0, (LPARAM)"Electrodomesticos");
        SendMessage(GetDlgItem(hWnd, ID_TipoAvion), CB_INSERTSTRING, 0, (LPARAM)"Productos de belleza");
        SYSTEMTIME fecha_y_hora_actuales;
        GetLocalTime(&fecha_y_hora_actuales);
        double fecha_y_hora_actual;
        SystemTimeToVariantTime(&fecha_y_hora_actuales, &fecha_y_hora_actual);
        SetTimer(hWnd, ID_HoraRegistro, 1000, NULL);
    }break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case IDC_V1:
        case IDC_V2:
        case IDC_V3:
        case IDC_V4:
        case IDC_V5:
            if (wmEvent == BN_CLICKED)
            {
                // Obtener el ID del radio button seleccionado
                int radioButtonID = LOWORD(wParam);

                switch (radioButtonID)
                {
                case IDC_V1:
                    SetDlgItemText(hWnd, ID_CantAsientos, "16");
                    break;
                case IDC_V2:
                    SetDlgItemText(hWnd, ID_CantAsientos, "14");
                    break;
                case IDC_V3:
                    SetDlgItemText(hWnd, ID_CantAsientos, "31");
                    break;
                case IDC_V4:
                    SetDlgItemText(hWnd, ID_CantAsientos, "27");
                    break;
                case IDC_V5:
                    SetDlgItemText(hWnd, ID_CantAsientos, "24");
                    break;
                default:
                    break;
                }
            }
            break;
        case ID_RegistrarVuelo: {

            productos* nuevoVuelo = new productos;
            char textow[255];

            GetDlgItemText(hWnd, ID_ComboOrigen, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de seleccionar el lugar de envioo", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            strcpy_s(nuevoVuelo->origen, textow);

            GetDlgItemText(hWnd, ID_ComboDestino, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de seleccionar un destinatario", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            strcpy_s(nuevoVuelo->destino, textow);



            // Obtener y validar el género
            char numas[255] = "";
            strcpy_s(numas, "160");

            // Obtener y validar el número de asientos según el tipo de avión
            if (IsDlgButtonChecked(hWnd, IDC_V1) == BST_CHECKED) {
                GetDlgItemText(hWnd, ID_CantAsientos, textow, 255);
                nuevoVuelo->asientotal = atof(textow);
                strcpy_s(nuevoVuelo->tipoav, "Comida");
            }
            else if (IsDlgButtonChecked(hWnd, IDC_V2) == BST_CHECKED) {
                GetDlgItemText(hWnd, ID_CantAsientos, textow, 255);
                nuevoVuelo->asientotal = atof(textow);
                strcpy_s(nuevoVuelo->tipoav, "Figuras");
            }
            else if (IsDlgButtonChecked(hWnd, IDC_V3) == BST_CHECKED) {
                GetDlgItemText(hWnd, ID_CantAsientos, textow, 255);
                nuevoVuelo->asientotal = atof(textow);
                strcpy_s(nuevoVuelo->tipoav, "Muebles");
            }
            else if (IsDlgButtonChecked(hWnd, IDC_V4) == BST_CHECKED) {
                GetDlgItemText(hWnd, ID_CantAsientos, textow, 255);
                nuevoVuelo->asientotal = atof(textow);
                strcpy_s(nuevoVuelo->tipoav, "Electrodomesticos");
            }
            else if (IsDlgButtonChecked(hWnd, IDC_V5) == BST_CHECKED) {
                GetDlgItemText(hWnd, ID_CantAsientos, textow, 255);
                nuevoVuelo->asientotal = atof(textow);
                strcpy_s(nuevoVuelo->tipoav, "Productos de belleza");
            }
            else {
                MessageBox(hWnd, "Favor de seleccionar tipo de producto", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }




            // Obtener y validar la cantidad de unidades con caja
            GetDlgItemText(hWnd, ID_AsientosEjecutiva, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner número de unidades con caja", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            nuevoVuelo->ejecutiva = atof(textow);

            // Obtener y validar la cantidad de unidades sin caja
            GetDlgItemText(hWnd, ID_AsientosTurista, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner numero de unidades sin caja", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            nuevoVuelo->turista = atof(textow);

            // Validar que la suma de ambas versiones equivalga al total de unidades
            if (nuevoVuelo->ejecutiva + nuevoVuelo->turista != nuevoVuelo->asientotal) {
                MessageBox(hWnd, "La suma de TODAS las unidades debe ser igual a la cantidad total de asientos", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            // Obtener y validar el precio con caja
            GetDlgItemText(hWnd, ID_PrecioEjecutiva, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner precio para unidades con caja", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            nuevoVuelo->precioejecutiva = atof(textow);

            // Obtener y validar el precio sin caja
            GetDlgItemText(hWnd, ID_PrecioTurista, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner precio para unidades sin caja", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            nuevoVuelo->precioturista = atof(textow);

            // Obtener y validar el porcentaje almacenado
            GetDlgItemText(hWnd, IDC_Percent10anios, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner porcentaje de pedidos reservados", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            nuevoVuelo->menores = atof(textow);
            if (nuevoVuelo->menores > 30) {
                MessageBox(hWnd, "El porcentaje de pedidos en reserva no debe ser mayor a 30%", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            // Obtener y validar el porcentaje en stock
            GetDlgItemText(hWnd, ID_Percent60anios, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner porcentaje de unidades disponibles", "ATENCIÓN", MB_OK | MB_ICONERROR);
                break;
            }
            nuevoVuelo->mayores = atof(textow);
            if (nuevoVuelo->mayores > 30) {
                MessageBox(hWnd, "El porcentaje de unidades disponibles no debe ser mayor a 30%", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            // Obtener y validar el límite de días para cancelación
            GetDlgItemText(hWnd, ID_LimCancel, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner limite de días para cancelacion", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            nuevoVuelo->diascan = atof(textow);


            //OBTNER LAS FECHA Y HORA DEL VUELO

            SYSTEMTIME fecha_obtenida = { 0 }, hora_obtenida = { 0 };
            SYSTEMTIME fecha_sistema = { 0 };
            GetLocalTime(&fecha_sistema);
            DateTime_GetSystemtime(GetDlgItem(hWnd, ID_FechaVuelo), &fecha_obtenida);

            nuevoVuelo->fechaRegistro = fecha_obtenida;
            strcpy_s(nuevoVuelo->usuarioQueRegistro, actualUsuarios->nombreUsuario);

            // Calcular la fecha máxima permitida (seis meses desde la fecha actual)
            SYSTEMTIME fecha_maxima = fecha_sistema;
            fecha_maxima.wMonth += 6;
            if (fecha_maxima.wMonth > 12) {
                fecha_maxima.wYear += fecha_maxima.wMonth / 12;
                fecha_maxima.wMonth = fecha_maxima.wMonth % 12;
                if (fecha_maxima.wMonth == 0) {
                    fecha_maxima.wMonth = 12;
                    fecha_maxima.wYear -= 1;
                }
            }


            // Verificar que la fecha de vuelo no sea en el mismo día
            if (fecha_obtenida.wYear == fecha_sistema.wYear &&
                fecha_obtenida.wMonth == fecha_sistema.wMonth &&
                fecha_obtenida.wDay == fecha_sistema.wDay) {
                MessageBox(hWnd, "No puede registrar un pedido en el mismo dia", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            // Verificar que la fecha de vuelo no sea en el pasado
            if (fecha_obtenida.wYear < fecha_sistema.wYear ||
                (fecha_obtenida.wYear == fecha_sistema.wYear && fecha_obtenida.wMonth < fecha_sistema.wMonth) ||
                (fecha_obtenida.wYear == fecha_sistema.wYear && fecha_obtenida.wMonth == fecha_sistema.wMonth && fecha_obtenida.wDay < fecha_sistema.wDay)) {
                MessageBox(hWnd, "No puede registrar en una fecha pasada", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            // Verificar que la fecha de vuelo no exceda los seis meses
            if (fecha_obtenida.wYear > fecha_maxima.wYear ||
                (fecha_obtenida.wYear == fecha_maxima.wYear && fecha_obtenida.wMonth > fecha_maxima.wMonth) ||
                (fecha_obtenida.wYear == fecha_maxima.wYear && fecha_obtenida.wMonth == fecha_maxima.wMonth && fecha_obtenida.wDay > fecha_maxima.wDay)) {
                MessageBox(hWnd, "No puede registrar un Pedidos tan lejano (max 6 meses)", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }


            DateTime_GetSystemtime(GetDlgItem(hWnd, ID_HoraVuelo), &hora_obtenida);
            if (fecha_obtenida.wYear == fecha_sistema.wYear && fecha_obtenida.wMonth == fecha_sistema.wMonth && fecha_obtenida.wDay == fecha_sistema.wDay) {
                if (hora_obtenida.wHour <= fecha_sistema.wHour) {
                    if (hora_obtenida.wMinute <= fecha_sistema.wMinute) {
                        MessageBox(hWnd, "No puede registrar en una hora que ya paso", "ATENCION", MB_OK | MB_ICONERROR);
                        break;
                    }
                }
            }



            nuevoVuelo->fechaVuelo = fecha_obtenida;
            nuevoVuelo->horaVuelo = hora_obtenida;



            contadorVuelos += 1;
            nuevoVuelo->idvuelo = contadorVuelos;
            nuevoVuelo->vueloRealizado = false;
            nuevoVuelo->pasajerosRegistrados = false;
            nuevoVuelo->cantBoletosVendidos = 0;
            nuevoVuelo->contadorAsientosEjecutiva = 0;
            nuevoVuelo->contadorAsientosTurista = 0;
            agregarVuelo(nuevoVuelo);


            MessageBox(hWnd, "Pedido registrado Existosamente", "ATENCION", MB_OK | MB_ICONINFORMATION);
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);

        }break;
        case ID_RegresoRegVuel: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        } break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Agregar cualquier código de dibujo que use hDC aquí...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}

LRESULT CALLBACK CancelarConfirmarProductos(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) //CancelarConfirmarVuelos
{
    // Buscar el vuelo por fecha y destino, deberia funcionar para todos los casos tratados en la funcion

    switch (message)
    {
    case WM_INITDIALOG: {
        // Vuelos Informacion
       // Inicializar la lista de vuelos
        SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("PEDIDOS:"));
        productos* actual = ini_vuelos;
        while (actual != nullptr) {

            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-ID PEDIDOS:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->idvuelo).c_str()));
            int opc = SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Pedidos con origen:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(actual->origen));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Destino:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(actual->destino));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Tipo Producto:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(actual->tipoav));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de unidades:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, opc, (LPARAM)(to_string(actual->asientotal).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de pedidos con caja:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->ejecutiva).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio con caja:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioejecutiva).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de pedidos sin caja:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->turista).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio sin caja:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioturista).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-numero de unidades con caja:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->menores).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-numero de unidades sin caja:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->mayores).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Registrado por:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT(actual->usuarioQueRegistro));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Fecha y hora de registro:"));
            string fecha_a_mostrar =
                to_string(actual->fechaRegistro.wDay) + '/' +
                to_string(actual->fechaRegistro.wMonth) + '/' +
                to_string(actual->fechaRegistro.wYear);
            string hora_a_mostrar =
                to_string(actual->fechaRegistro.wHour) + ':' +
                to_string(actual->fechaRegistro.wMinute);
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT((fecha_a_mostrar).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT((hora_a_mostrar).c_str()));
            actual = actual->siguiente;
        }
    }break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
            //Para el boton con la id que es IDC_BusquedaPasajero debremos utilizar los metodos de busqueda ya anteriormente escritos y lo cual deberia mostrarse en la ID_ConfirmarVuelo que es 
        case IDC_BusquedaPasajero:
        {
            if (HIWORD(wParam) == BN_CLICKED)
            {
                // Limpiar la lista antes de agregar nuevos elementos
                SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_RESETCONTENT, 0, 0);
                SendMessage(GetDlgItem(hWnd, ID_PasajerosVuelos), LB_RESETCONTENT, 0, 0);

                // Obtener la fecha del control Date-Time
                SYSTEMTIME fechaSeleccionada;
                DateTime_GetSystemtime(GetDlgItem(hWnd, ID_BusquedaFecha), &fechaSeleccionada);

                // Convertir la fecha seleccionada a string
                string fechaStr =
                    to_string(fechaSeleccionada.wDay) + '/' +
                    to_string(fechaSeleccionada.wMonth) + '/' +
                    to_string(fechaSeleccionada.wYear);
                //Obtener el ID del control Edit
                char idobtenido[100];
                int idabuscar = 0;
                GetDlgItemText(hWnd, IDC_ID, idobtenido, sizeof(idobtenido));
                // Verificar si el ID obtenido es un número positivo y no está vacío
                if (strlen(idobtenido) > 0) {

                    int id = atoi(idobtenido);
                    if (id > 0) {

                        idabuscar = id;
                    }
                    else {
                        MessageBox(hWnd, "El ID no puede ser un numero negativo.", "Error", MB_OK | MB_ICONERROR);
                    }
                }
                else {
                    MessageBox(hWnd, "Por favor, ingrese un ID.", "Error", MB_OK | MB_ICONERROR);
                }

                // Verificar si el vuelo existe
                bool find = false;
                productos* actualVuelo = ini_vuelos;
                while (actualVuelo != nullptr) {
                    if (actualVuelo->idvuelo == idabuscar) {
                        find = true;
                        break; // Salir del bucle una vez que se encuentre el vuelo
                    }
                    actualVuelo = actualVuelo->siguiente;
                }

                if (!find) {
                    MessageBox(hWnd, "El pedido especificado no existe", "ATENCION", MB_OK | MB_ICONERROR);
                    break; // Salir del switch en caso de que el vuelo no exista
                }




                // Obtener el destino del control Edit
                char destino[100];
                GetDlgItemText(hWnd, ID_BusquedaNombre, destino, sizeof(destino));

                if (!fechaStr.empty() && strcmp(destino, "") != 0) {
                    // Si se especificó una fecha y un destino, buscar por fecha y destino
                    vueloEncontrado = buscarVueloPorFechaYDestino(fechaStr, destino, idabuscar);
                }
                else if (strcmp(destino, "") != 0) {
                    // Si no se especificó una fecha pero sí un destino, buscar por destino solo
                    vueloEncontrado = buscarVueloPorDestino(destino);
                }
                else if (!fechaStr.empty()) {
                    // Si no se especificó un destino pero sí una fecha, mostrar un mensaje de error
                    MessageBox(hWnd, "Por favor, especifique un destino.", "Informacion", MB_OK | MB_ICONINFORMATION);
                    return 0;
                }
                else {
                    // Si no se especificó ni destino ni fecha, mostrar un mensaje de error
                    MessageBox(hWnd, "Por favor, especifique un destino y/o una fecha.", "Informacion", MB_OK | MB_ICONINFORMATION);
                    return 0;
                }

                if (vueloEncontrado != nullptr && vueloEncontrado->vueloRealizado == false && find && vueloEncontrado->idvuelo == idabuscar)
                {
                    // Agregar los detalles del vuelo encontrado a la lista
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("PEDIDO ENCONTRADO:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-ID PEDIDO:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(vueloEncontrado->idvuelo).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-Lugar de envio:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(vueloEncontrado->origen));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-Destino:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(vueloEncontrado->destino));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-Tipo Pedido:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(vueloEncontrado->tipoav));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de ventas:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(vueloEncontrado->asientotal).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de ventas con caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(vueloEncontrado->ejecutiva).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio Con caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(vueloEncontrado->precioejecutiva).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de ventas sin caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(vueloEncontrado->turista).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio Sin caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(vueloEncontrado->precioturista).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-numero de unidades con caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(vueloEncontrado->menores).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-numero de unidades sin caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(vueloEncontrado->mayores).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-Registrado por:"));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)(vueloEncontrado->usuarioQueRegistro));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("-Fecha y hora de registro:"));

                    string fecha_a_mostrar =
                        to_string(vueloEncontrado->fechaRegistro.wDay) + '/' +
                        to_string(vueloEncontrado->fechaRegistro.wMonth) + '/' +
                        to_string(vueloEncontrado->fechaRegistro.wYear);
                    string hora_a_mostrar =
                        to_string(vueloEncontrado->fechaRegistro.wHour) + ':' +
                        to_string(vueloEncontrado->fechaRegistro.wMinute);
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT((fecha_a_mostrar).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT((hora_a_mostrar).c_str()));

                    // Activar o desactivar el botón de cancelar vuelo según si se encontró un vuelo o no
                    EnableWindow(GetDlgItem(hWnd, ID_CANCEL), vueloEncontrado != nullptr);

                    // Mostrar el numero de TotalDePasajeros
                    stringstream ss;
                    ss << fixed << setprecision(0) << vueloEncontrado->cantBoletosVendidos;
                    string totalPasajerosStr = ss.str();
                    SetDlgItemText(hWnd, ID_TotalDePasajeros, totalPasajerosStr.c_str());

                    //ERA MOSTRAR BOLETOS CON CORRELACION XD
                    // Inicializamos los pasajeros para ver si se muestran
                    bool nohaypasajeros = false;
                    // Mostrar pedidos asociados al producto encontrado 
                    pedidos* auxiliar = ini_pedidos;
                    bool pedidosEncontrados = false;
                    SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Pedidos del producto:"));
                    while (auxiliar != nullptr)
                    {
                        if (auxiliar->idProductoComprado == vueloEncontrado->idvuelo/*auxiliar->idProductoComprado == productoEncontrado->idProducto*/)
                        {
                            pedidosEncontrados = true;
                            // Rellenar ListBox con detalles de pedidos
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("ID del Pedido:"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(to_string(auxiliar->idPedido).c_str()));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("ID del Producto:"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(to_string(auxiliar->idProductoComprado).c_str()));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Comprado por:"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(auxiliar->nombreCliente));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(auxiliar->apellidoPatCliente));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(auxiliar->apellidoMatCliente));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Nombre del Producto:"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(auxiliar->nombreProducto));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Categoría:"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(auxiliar->categoria));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Precio:"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(to_string(auxiliar->precio).c_str()));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Cantidad Comprada:"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(to_string(auxiliar->cantidadComprada).c_str()));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Método de Pago:"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(auxiliar->metodoPago));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Pedido Entregado:"));
                            SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(auxiliar->pedidoEntregado ? TEXT("Sí") : TEXT("No")));
                        }
                        auxiliar = auxiliar->siguiente;
                    }
                    if (!pedidosEncontrados) {
                        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("No hay pedidos registrados para este vuelo."));
                    }

                    if (nohaypasajeros == true)
                    {
                        MessageBox(hWnd, "No hay productos vendidos para este vuelo.", "Informacion", MB_OK | MB_ICONINFORMATION);
                    }



                }

            }
            else
            {
                // Si no se encuentra ningún vuelo, mostrar un mensaje
                MessageBox(hWnd, "No se encontro ningun pedido con el destino y/o fecha especificados o Confirmado.", "Informacion", MB_OK | MB_ICONINFORMATION);
                SetDlgItemText(hWnd, ID_TotalDePasajeros, "");
            }




        } break;

        case ID_CANCEL: {
            // Verificar si se encontró un vuelo para cancelar
            if (vueloEncontrado != nullptr) {
                // Mostrar un mensaje de confirmación
                int respuesta = MessageBox(hWnd, "Estas seguro de que deseas cancelar este pedido", "Confirmar cancelacion", MB_YESNO | MB_ICONQUESTION);
                if (respuesta == IDYES) {
                    // Eliminar el vuelo encontrado
                    eliminarVuelo(vueloEncontrado);
                    // Mostrar un mensaje de confirmación
                    MessageBox(hWnd, "El pedido ha sido cancelado.", "Informacion", MB_OK | MB_ICONINFORMATION);
                    // Limpiar la lista de vuelos
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_RESETCONTENT, 0, 0);
                }
            }
            else {
                MessageBox(hWnd, "No se ha encontrado ningun pedido para cancelar.", "Informacion", MB_OK | MB_ICONINFORMATION);
            }
        } break;


        case ID_CONFRIMVUELO: {
            // Verificar si se encontró un vuelo para confirmar


            // && vueloEncontrado->pasajerosRegistrados == true
            //COSA QUE QUITE

            if (vueloEncontrado != nullptr) {
                // Mostrar un mensaje de confirmación
                int respuesta = MessageBox(hWnd, "Estas seguro de que deseas confirmar", "Confirmar vuelo", MB_YESNO | MB_ICONQUESTION);
                if (respuesta == IDYES) {
                    // Aquí guardarías el vuelo o realizarías alguna acción adicional según tus requisitos
                    vueloEncontrado->vueloRealizado = true;
                    // Mostrar un mensaje de confirmación
                    MessageBox(hWnd, "El Pedido ha sido confirmado.", "Informacion", MB_OK | MB_ICONINFORMATION);
                    SendMessage(GetDlgItem(hWnd, ID_ConfirmarVuelo), LB_RESETCONTENT, 0, 0);
                }
            }
            else {
                MessageBox(hWnd, "No se ha encontrado ningun pedido por confirmar o.", "Informacion", MB_OK | MB_ICONINFORMATION);
            }
        } break;

        case ID_RegresoCancelar: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);

        }break;
        }
    }break;
    case WM_CLOSE:
    {
        int ventana = MessageBox(0, "Seguro que desea salir?", "Aviso", MB_YESNO | MB_ICONQUESTION);
        switch (ventana)
        {
        case IDYES:
            DestroyWindow(hWnd);
            break;
        }break;
    }break;
    case WM_DESTROY: {
        PostQuitMessage(0);
    }break;

    }
    return 0;
}
LRESULT CALLBACK ReporteVuelos(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case ID_BOTONBUSQEUDA: {
            if (HIWORD(wParam) == BN_CLICKED) {
                // Obtener las fechas seleccionadas por el usuario
                SYSTEMTIME desde, al;
                DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), &desde);
                DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_DATETIMEPICKER2), &al);

                // Convertir las fechas seleccionadas a formato de doble precisión
                double fecha_del, fecha_al;
                SystemTimeToVariantTime(&desde, &fecha_del);
                SystemTimeToVariantTime(&al, &fecha_al);

                // Almacenar las fechas seleccionadas
                buscar_citas_de = fecha_del;
                buscar_citas_al = fecha_al;

                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_MOSTRARPOR), NULL, MostrarPorFecha);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }
        }break;

        case ID_RegresoManifiesto: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);

        } break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Agregar cualquier código de dibujo que use hDC aquí...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
LRESULT CALLBACK Manifiesto(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG: {

        // Inicializar la lista de Pedidos
        SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("Pedidos:"));
        productos* actual = ini_vuelos;
        while (actual != nullptr) {
            // Verificar si el pedido está realizado
            if (actual->vueloRealizado) {
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-ID PEDIDO:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->idvuelo).c_str()));
                int opc = SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-Lugar de envio:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(actual->origen));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-Destino:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(actual->destino));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-Tipo Pedido:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(actual->tipoav));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-Unidades Disponibles:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, opc, (LPARAM)(to_string(actual->asientotal).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-Unidades con caja:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->ejecutiva).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio con caja:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioejecutiva).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-Unidades sin caja:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->turista).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio sin caja:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioturista).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-numero de clientes con caja:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->menores).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-numero de clientes sin caja:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->mayores).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-Registrado por:"));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT(actual->usuarioQueRegistro));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT("-Fecha y hora de registro:"));
                string fecha_a_mostrar =
                    to_string(actual->fechaRegistro.wDay) + '/' +
                    to_string(actual->fechaRegistro.wMonth) + '/' +
                    to_string(actual->fechaRegistro.wYear);
                string hora_a_mostrar =
                    to_string(actual->fechaRegistro.wHour) + ':' +
                    to_string(actual->fechaRegistro.wMinute);
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT((fecha_a_mostrar).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_VuelosRealizados), LB_ADDSTRING, 0, (LPARAM)TEXT((hora_a_mostrar).c_str()));
            }
            actual = actual->siguiente;
        }

    }break;

    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {



        case ID_RegresoManifiesto: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);



        }break;

        case ID_SELECC: {
            // Limpiar la lista antes de agregar nuevos elementos
            SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_RESETCONTENT, 0, 0);
            //Obtener el ID del control Edit
            char idobtenido[100];
            int idabuscar = 0;
            GetDlgItemText(hWnd, IDC_EDITN, idobtenido, sizeof(idobtenido));
            // Verificar si el ID obtenido es un número positivo y no está vacío
            if (strlen(idobtenido) > 0) {

                int id = atoi(idobtenido);
                if (id > 0) {

                    idabuscar = id;
                    ID_SEARCH = id;
                }
                else {
                    MessageBox(hWnd, "El ID no puede ser un número negativo.", "Error", MB_OK | MB_ICONERROR);
                }
            }
            else {
                MessageBox(hWnd, "Por favor, ingrese un ID.", "Error", MB_OK | MB_ICONERROR);
            }

            // Verificar si el vuelo existe y si ya fue realizado
            bool find = false;
            productos* actualVuelo = ini_vuelos;
            while (actualVuelo != nullptr) {
                if (actualVuelo->idvuelo == idabuscar && actualVuelo->vueloRealizado) {
                    find = true;
                    break; // Salir del bucle una vez que se encuentre el vuelo
                }
                actualVuelo = actualVuelo->siguiente;
            }

            if (!find) {
                MessageBox(hWnd, "El pedido especificado no existe", "ATENCION", MB_OK | MB_ICONERROR);
                break; // Salir del switch en caso de que el vuelo no exista
            }

            vueloEncontrado = buscarPorId(idabuscar);

            // Mostrar pedidos asociados al vuelo encontrado
            pedidos* auxiliar = ini_pedidos; // Cambiado de boletos* a pedidos*
            bool pedidosEncontrados = false;

            SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Productos asociados al Pedido:"));

            while (auxiliar != nullptr) {
                if (auxiliar->idProductoComprado == vueloEncontrado->idvuelo && auxiliar->pedidoEntregado == true) { // Ajustado para idProductoComprado y pedidoEntregado
                    pedidosEncontrados = true;

                    // Rellenar ListBox con detalles del pedido
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Cliente:"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(auxiliar->nombreCliente));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(auxiliar->apellidoPatCliente));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(auxiliar->apellidoMatCliente));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Edad del Cliente:"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(auxiliar->edadCliente).c_str())); // Ajustado para edadCliente
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Nacionalidad del Cliente:"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(auxiliar->nacionalidadCliente)); // Ajustado para nacionalidadCliente
                }
                auxiliar = auxiliar->siguiente;
            }

            if (!pedidosEncontrados) {
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("No hay pedidos registrados para este vuelo o ninguno fue entregado."));
            }


        }break;


        case ID_OrdenarNombre: {
            HWND hWndListBox = GetDlgItem(hWnd, ID_PasajerosDelVuelo);
            int itemCount = SendMessage(hWndListBox, LB_GETCOUNT, 0, 0);
            if (itemCount == 0) {
                MessageBox(hWnd, "Espera a que haya algo en los listbox", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            int num_pedidos = 0;
            pedidos* temp = ini_pedidos;
            while (temp != nullptr) {
                num_pedidos++;
                temp = temp->siguiente;
            }

            pedidos* arr = new pedidos[num_pedidos];

            temp = ini_pedidos;
            int i = 0;
            while (temp != nullptr && i < num_pedidos) {
                arr[i] = *temp;
                temp = temp->siguiente;
                i++;
            }

            heapSort(arr, num_pedidos); // Llamada a HeapSort adaptada para pedidos

            // Mostrar pedidos asociados al producto encontrado

            SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_RESETCONTENT, 0, 0);
            SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Pedidos del producto:"));

            for (int i = 0; i < num_pedidos; i++) {
                // Agregar detalles del pedido a la lista en la interfaz de usuario
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Cliente:"));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(arr[i].nombreCliente));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(arr[i].apellidoPatCliente));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(arr[i].apellidoMatCliente));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Edad del Cliente:"));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(arr[i].edadCliente).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Nacionalidad del Cliente:"));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(arr[i].nacionalidadCliente));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Producto Comprado:"));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(arr[i].nombreProducto));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Cantidad Comprada:"));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(arr[i].cantidadComprada).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Precio Total:"));
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(arr[i].precio).c_str()));
            }

            delete[] arr; // Liberar memoria dinámica
        } break;


        case ID_OrdenarNumAsiento: {
            HWND hWndListBox = GetDlgItem(hWnd, ID_PasajerosDelVuelo);
            int itemCount = SendMessage(hWndListBox, LB_GETCOUNT, 0, 0);
            if (itemCount == 0) {
                MessageBox(hWnd, "Espera a que haya algo en los listbox", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_RESETCONTENT, 0, 0);
            //MIA AQUI ES DONDE VA LA LOGICA DE ORDENAR
            //O SEA ORDENAS Y SE VUELVE A A ABRIR LA VENTANA YA ORDENADO TODO

            ordenarPedidosDescendenteQuicksort(); //ordenarBoletosDecendenteQuicksort();
            //SE SUPONE YA SE ORDENO Y SE VOLVIO A ESCRIBIR

           // Mostrar pedidos asociados al producto encontrado
            pedidos* auxiliar = ini_pedidos;
            bool pedidosEncontrados = false;
            SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Clientes que realizaron el pedido:"));

            while (auxiliar != nullptr)
            {
                if (auxiliar->idProductoComprado == vueloEncontrado->idvuelo && auxiliar->pedidoEntregado == true/*auxiliar->idProductoComprado == productoEncontrado->idProducto && auxiliar->pedidoEntregado == true*/)
                {
                    pedidosEncontrados = true;
                    // Rellenar ListBox con detalles de pedidos
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Cliente:"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(auxiliar->nombreCliente));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(auxiliar->apellidoPatCliente));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(auxiliar->apellidoMatCliente));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Edad del Cliente:"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(auxiliar->edadCliente).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Nacionalidad del Cliente:"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(auxiliar->nacionalidadCliente));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Producto Comprado:"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(auxiliar->nombreProducto));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("Cantidad Comprada:"));
                    SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)(to_string(auxiliar->cantidadComprada).c_str()));
                }
                auxiliar = auxiliar->siguiente;
            }

            if (!pedidosEncontrados) {
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_ADDSTRING, 0, (LPARAM)TEXT("No hay pedidos registrados para este producto o nadie lo confirmo."));
            }


        }break;
 case ID_GnerarArchivo: {
            SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_RESETCONTENT, 0, 0); 
            // Inicializar la lista de vuelos
            SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("PEDIDOS:"));
            productos* actual = ini_vuelos;
            while (actual != nullptr) {
                // Verificar si el vuelo está realizado
                if (actual->vueloRealizado && actual->idvuelo == ID_SEARCH) {
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-ID PEDIDOS:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->idvuelo).c_str()));
                    int opc = SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-Lugar de envio:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(actual->origen));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-Destino:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(actual->destino));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-Tipo Producto:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(actual->tipoav));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de Pedidos:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, opc, (LPARAM)(to_string(actual->asientotal).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de pedidos con caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->ejecutiva).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio con caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioejecutiva).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de pedidos sin caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->turista).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio sin caja:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioturista).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-numero de Productos con caja disponibles:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->menores).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-numero de Productos sin caja disponibles:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->mayores).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-Registrado por:"));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT(actual->usuarioQueRegistro));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("-Fecha y hora de registro:"));
                    string fecha_a_mostrar =
                        to_string(actual->fechaRegistro.wDay) + '/' +
                        to_string(actual->fechaRegistro.wMonth) + '/' +
                        to_string(actual->fechaRegistro.wYear);
                    string hora_a_mostrar =
                        to_string(actual->fechaRegistro.wHour) + ':' +
                        to_string(actual->fechaRegistro.wMinute);
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT((fecha_a_mostrar).c_str()));
                    SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT((hora_a_mostrar).c_str()));
                }
                actual = actual->siguiente;
            }

           
            // Obtener el número de elementos en el ListBox de origen (ID_PasajerosDelVuelo)
            int itemCountPasajeros = SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_GETCOUNT, 0, 0);
           
            SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
            SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)TEXT("PASAJEROS:"));
            for (int i = 0; i < itemCountPasajeros; i++) {
               
                char buffer[256]; 
                SendMessage(GetDlgItem(hWnd, ID_PasajerosDelVuelo), LB_GETTEXT, i, (LPARAM)buffer);

                
                SendMessage(GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER), LB_ADDSTRING, 0, (LPARAM)buffer);
            }
        
        
        }break;

        case IDC_GEN_ARCH: {

            HWND hWndListBox = GetDlgItem(hWnd, ID_MANIFESTO_OF_MOTHER_MONSTER);
            //HWND hWndListBox = GetDlgItem(GetDesktopWindow(), ID_MANIFESTO_OF_MOTHER_MONSTER);
            const char* nombreArchivo = "Manifiesto.txt";

            GuardarListBoxEnArchivo(hWndListBox, nombreArchivo);

        
        }break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    }break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
LRESULT CALLBACK CompraProductos(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG: {

        // Se carga la lista, para los metodos de pago

        SendMessage(GetDlgItem(hWnd, ID_Clase), CB_INSERTSTRING, 0, (LPARAM)"C/CAJA");
        SendMessage(GetDlgItem(hWnd, ID_Clase), CB_INSERTSTRING, 0, (LPARAM)"S/CAJA");
        SendMessage(GetDlgItem(hWnd, ID_MetodoPago), CB_INSERTSTRING, 0, (LPARAM)"Efectivo");
        SendMessage(GetDlgItem(hWnd, ID_MetodoPago), CB_INSERTSTRING, 0, (LPARAM)"Tarjeta");
        SendMessage(GetDlgItem(hWnd, ID_MetodoPago), CB_INSERTSTRING, 0, (LPARAM)"Apple Pay");
        SendMessage(GetDlgItem(hWnd, ID_MetodoPago), CB_INSERTSTRING, 0, (LPARAM)"Mercado Pago");


        // Informacion de los clientes, estos datos seran de utlidad
        SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT("Pasajeros:"));
        clientes* actualpass = ini_pasajeros;
        while (actualpass != nullptr)
        {
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT("-Cliente con id:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)(to_string(actualpass->idpasajeros).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT("-Nombre:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT(actualpass->nombre));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT(actualpass->apellidoPat));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT(actualpass->apellidoMat));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT("-Registrado por:"));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT(actualpass->usuarioQueRegistro));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT("-Fecha y hora de registro:"));
            string fecha_a_mostrar =
                to_string(actualpass->fechaRegistro.wDay) + '/' +
                to_string(actualpass->fechaRegistro.wMonth) + '/' +
                to_string(actualpass->fechaRegistro.wYear);
            string hora_a_mostrar =
                to_string(actualpass->fechaRegistro.wHour) + ':' +
                to_string(actualpass->fechaRegistro.wMinute);
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT((fecha_a_mostrar).c_str()));
            SendMessage(GetDlgItem(hWnd, ID_ListaPasajeros), LB_ADDSTRING, 0, (LPARAM)TEXT((hora_a_mostrar).c_str()));
            actualpass = actualpass->siguiente;
        }



        // Vuelos Informacion
        // Inicializar la lista de vuelos
        SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("PEDIDOS:"));
        productos* actual = ini_vuelos;
        while (actual != nullptr) {
            // Verifica si el vuelo no ha sido realizado
            if (!actual->vueloRealizado) {
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-ID PEDIDO:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->idvuelo).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Lugar de recibo:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(actual->origen));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Destino:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(actual->destino));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Tipo Producto:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(actual->tipoav));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de unidades:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->asientotal).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de unidades CON CAJA disponibles:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->ejecutiva).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio empaquetados:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioejecutiva).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Total de unidades SIN CAJA disponibles:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->turista).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-precio sin caja:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->precioturista).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Pedidos empaquetados:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->menores).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Pedidos SIN empaquetar"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(to_string(actual->mayores).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Registrado por:"));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)(actual->usuarioQueRegistro));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT("-Fecha y hora de registro:"));
                string fecha_a_mostrar =
                    to_string(actual->fechaRegistro.wDay) + '/' +
                    to_string(actual->fechaRegistro.wMonth) + '/' +
                    to_string(actual->fechaRegistro.wYear);
                string hora_a_mostrar =
                    to_string(actual->fechaRegistro.wHour) + ':' +
                    to_string(actual->fechaRegistro.wMinute);
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT((fecha_a_mostrar).c_str()));
                SendMessage(GetDlgItem(hWnd, ID_ListaVuelos), LB_ADDSTRING, 0, (LPARAM)TEXT((hora_a_mostrar).c_str()));
            }
            actual = actual->siguiente;
        }


    } break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId) {
        case ID_ComprarBoleto: {
            pedidos* nuevopedido = new pedidos;//boletos* nuevoboleto = new boletos;

            char textow[255];
            int vueloaBuscar = 0;
            int pasajeroaBuscar = 0;


            // Obtener ID de vuelo deseado
            GetDlgItemText(hWnd, ID_edit_vuelo, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner id del producto deseado", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            vueloaBuscar = atoi(textow);

            //BUSQUEDA BINARIA:
            // Contar el número de vuelos
            int tamanoVuelos = 0;
            productos* actualVuelo = ini_vuelos;
            while (actualVuelo != nullptr) {
                tamanoVuelos++;
                actualVuelo = actualVuelo->siguiente;
            }

            // Crear un array de punteros a vuelos
            productos** arrayVuelos = new productos * [tamanoVuelos];

            // Convertir la lista enlazada a array
            actualVuelo = ini_vuelos;
            for (int i = 0; i < tamanoVuelos; i++) {
                arrayVuelos[i] = actualVuelo;
                actualVuelo = actualVuelo->siguiente;
            }

            // Buscar el vuelo usando búsqueda binaria
            bool vueloEncontrado = false;
            bool vueloYaConfirmado = false;
            int izquierda = 0;
            int derecha = tamanoVuelos - 1;
            while (izquierda <= derecha) {
                int medio = izquierda + (derecha - izquierda) / 2;
                if (arrayVuelos[medio]->idvuelo == vueloaBuscar) {
                    actualVuelo = arrayVuelos[medio];
                    vueloEncontrado = true;
                    if (actualVuelo->vueloRealizado == true) {
                        vueloYaConfirmado = true;
                    }
                    strcpy(nuevopedido->origen, actualVuelo->origen);
                    strcpy_s(nuevopedido->destino, actualVuelo->destino);
                    break;
                }
                if (arrayVuelos[medio]->idvuelo < vueloaBuscar) {
                    izquierda = medio + 1;
                }
                else {
                    derecha = medio - 1;
                }
            }

            // Liberar el array de vuelos después de su uso
            delete[] arrayVuelos;

            if (!vueloEncontrado) {
                MessageBox(hWnd, "El Pedido especificado no existe", "ATENCION", MB_OK | MB_ICONERROR);
                break; // Salir del switch en caso de que el vuelo no exista
            }

            if (vueloYaConfirmado == true) {
                MessageBox(hWnd, "El Pedido especificado ya se realizo y es imposible comprar mas Productos", "ATENCION", MB_OK | MB_ICONERROR);
                break; // Salir del switch en caso de que el vuelo no exista
            }


            nuevopedido->idProductoComprado = actualVuelo->idvuelo;

            // Obtener ID de usuario deseado
            GetDlgItemText(hWnd, ID_edit_usu, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner id de usuario que desea comprar", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            pasajeroaBuscar = atoi(textow);

            // Verificar si el pasajero existe
            bool pasajeroEncontrado = false;
            clientes* actualPasajero = ini_pasajeros;
            while (actualPasajero != nullptr) {
                if (actualPasajero->idpasajeros == pasajeroaBuscar) {
                    pasajeroEncontrado = true;
                    // Aquí podrías realizar las operaciones necesarias para completar la compra
                    break; // Salir del bucle una vez que se encuentre el pasajero
                }
                actualPasajero = actualPasajero->siguiente;
            }

            if (!pasajeroEncontrado) {
                MessageBox(hWnd, "El Cliente especificado no existe", "ATENCION", MB_OK | MB_ICONERROR);
                break; // Salir del switch en caso de que el pasajero no exista
            }
            else
            {
                nuevopedido->idCliente = actualPasajero->idpasajeros;
            }

            //Verificar que el pasajero no tenga ya un boleto para ese vuelo
            bool yaCuentaConBoleto = false;
            pedidos* actualBoleto = ini_pedidos;
            while (actualBoleto != nullptr)
            {
                if (actualBoleto->idProductoComprado == nuevopedido->idProductoComprado && actualBoleto->idCliente == actualPasajero->idpasajeros)
                {
                    yaCuentaConBoleto = true;
                    break;
                }
                actualBoleto = actualBoleto->siguiente;
            }

            if (yaCuentaConBoleto)
            {
                MessageBox(hWnd, "El Cliente ya cuenta con Producto de este tipo comprado ", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }


            //esto Es justo lo que voya  cambiar



            if (IsDlgButtonChecked(hWnd, ID_EJE) == BST_CHECKED) {

                if (actualVuelo->contadorAsientosEjecutiva >= actualVuelo->ejecutiva)
                {
                    MessageBox(hWnd, "Cantidad de Productos en con caja enteramente vendida", "ATENCION", MB_OK | MB_ICONERROR);
                    break;
                }


                actualVuelo->contadorAsientosEjecutiva += 1;
                nuevopedido->precio = actualVuelo->precioejecutiva;
                strcpy(nuevopedido->categoria, "Con caja");
            }
            else if (IsDlgButtonChecked(hWnd, ID_TURI) == BST_CHECKED) {

                if (actualVuelo->contadorAsientosTurista >= actualVuelo->turista)
                {
                    MessageBox(hWnd, "Cantidad de Productos sin caja enteramente vendida", "ATENCION", MB_OK | MB_ICONERROR);
                    break;
                }

                actualVuelo->contadorAsientosTurista += 1;
                GetDlgItemText(hWnd, ID_CantAsientos, textow, 255);
                nuevopedido->precio = actualVuelo->precioturista;
                strcpy(nuevopedido->categoria, "Sin caja");
            }
            else {
                MessageBox(hWnd, "Favor de seleccionar el tipo de producto", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            GetDlgItemText(hWnd, ID_MetodoPago, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Favor de poner metodo de pago", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            strcpy(nuevopedido->metodoPago, textow);

            contadorPedidos += 1; // Incrementar el contador de pedidos
            nuevopedido->idPedido = contadorPedidos;

            // Copiar detalles del cliente al pedido
            strcpy(nuevopedido->nombreCliente, actualPasajero->nombre);
            strcpy(nuevopedido->apellidoPatCliente, actualPasajero->apellidoPat);
            strcpy(nuevopedido->apellidoMatCliente, actualPasajero->apellidoMat);
            strcpy(nuevopedido->nacionalidadCliente, actualPasajero->nacionalidad);
            nuevopedido->edadCliente = actualPasajero->edad;



            agregarPedido(nuevopedido);

            MessageBox(hWnd, "Compra exitosa", "ATENCION", MB_OK | MB_ICONINFORMATION);
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);


        } break;
        case ID_RegresoCompraBoletos: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        } break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    } break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    } break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return 0;
}
LRESULT CALLBACK CancelarConfirmarPedido(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG: {
        ActualizarListBox(hWnd);
    } break;

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case ID_RegresoCancelar: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ID_Principal), NULL, Principal);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        } break;

        case ID_CANCEL: {
            // Obtener Producto
            char textow[255];
            int BoletoABuscar = 0;
            GetDlgItemText(hWnd, ID_A_ELIMINAR, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Ingresa un ID de Producto valido", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            BoletoABuscar = atoi(textow);

            bool boletoEncontrado = false;
            bool yaNoSePuedeConfirmar = false;
            pedidos* actualBol = ini_pedidos;

            // Verificar si la lista está vacía
            if (actualBol == nullptr) {
                MessageBox(hWnd, "No hay pedidos registrados.", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

            // Recorrer la lista para encontrar el pedido
            while (actualBol != nullptr) {
                if (actualBol->idPedido == BoletoABuscar) {
                    boletoEncontrado = true;

                    // Verificar si el vuelo ya fue realizado
                    productos* aux = ini_vuelos;
                    while (aux != nullptr) {
                        if (actualBol->idProductoComprado == aux->idvuelo && aux->vueloRealizado) {
                            yaNoSePuedeConfirmar = true;
                            break;
                        }
                        aux = aux->siguiente;
                    }
                    break; // Salir del bucle una vez que se encuentra el pedido
                }
                actualBol = actualBol->siguiente;
            }

            // Manejar los resultados
            if (boletoEncontrado) {
                if (yaNoSePuedeConfirmar) {
                    MessageBox(hWnd, "El Pedido ya se realizo y ya no se puede confirmar el producto", "ATENCION", MB_OK | MB_ICONERROR);
                }
                else if (actualBol != nullptr) { // Verificar que el puntero es válido antes de usarlo
                    actualBol->pedidoEntregado = true;
                    MessageBox(hWnd, "Producto confirmado, Pedido otorgado", "Atencion", MB_OK | MB_ICONINFORMATION);
                }
            }
            else {
                MessageBox(hWnd, "El producto especificado no existe", "ATENCION", MB_OK | MB_ICONERROR);
            }

        } break;

        case ID_CANCEL2: {
            char textow[255];
            int BoletoABuscar = 0;
            GetDlgItemText(hWnd, ID_A_ELIMINAR, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Ingresa el ID del Producto", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            BoletoABuscar = atoi(textow);

            bool boletoEncontrado = false;
            pedidos* actualBol = ini_pedidos;
            pedidos* anteriorBol = nullptr;
            while (actualBol != nullptr) {
                if (actualBol->idPedido == BoletoABuscar) {
                    boletoEncontrado = true;

                    bool SisepuedeCancelar = false;



                    int respuesta = MessageBox(hWnd, " Seguro que desea eliminar el producto? ", "Confirmacion", MB_YESNO | MB_ICONQUESTION);

                    if (respuesta == IDYES) {
                        if (actualBol->pedidoEntregado == true)
                        {
                            MessageBox(hWnd, "El paquete ya ha sido entregado, no puede eliminarse", "ATENCION", MB_OK | MB_ICONERROR);
                            break;
                        }
                        if (actualBol == ini_pedidos) {
                            ini_pedidos = actualBol->siguiente;
                        }
                        else {
                            anteriorBol->siguiente = actualBol->siguiente;
                        }
                        if (actualBol == fin_pedidos) {
                            fin_pedidos = anteriorBol;
                        }
                        delete actualBol;
                        MessageBox(hWnd, "Producto eliminado exitosamente", "Exito", MB_OK | MB_ICONINFORMATION);
                        ActualizarListBox(hWnd);  // Actualizar ListBox después de eliminar
                    }
                    break;
                }
                anteriorBol = actualBol;
                actualBol = actualBol->siguiente;
            }

            if (!boletoEncontrado) {
                MessageBox(hWnd, "El producto especificado no existe", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

        } break;

        case IDC_BUTTON1: {
            char textow[255];
            bool boletoEncontrado = false;
            int BoletoABuscar = 0;
            GetDlgItemText(hWnd, ID_A_ELIMINAR, textow, 255);
            if (strlen(textow) <= 0) {
                MessageBox(hWnd, "Ingresa un ID del Producto", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }
            BoletoABuscar = atoi(textow);
            pedidos* actualBol = ini_pedidos;

            while (actualBol != nullptr) {
                if (actualBol->idPedido == BoletoABuscar && actualBol->pedidoEntregado != 0) {
                    boletoEncontrado = true;
                    guardarPedidosEnArchivo(ini_pedidos, "GuardarProductos.txt");
                    break;
                }

                actualBol = actualBol->siguiente;
            }

            if (!boletoEncontrado) {
                MessageBox(hWnd, "El producto especificado no existe", "ATENCION", MB_OK | MB_ICONERROR);
                break;
            }

        } break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
    } break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Agregar cualquier código de dibujo que use hDC aquí...
        EndPaint(hWnd, &ps);
    } break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
//---------------------------------------------FIN CALLBACKS



//---------------------------------------------EXTRA

void ActualizarListBox(HWND hWnd) {
    // Limpiar ListBox
    SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_RESETCONTENT, 0, 0);

    // Rellenar ListBox
    SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Pedidos Existentes:"));
    pedidos* actualPedido = ini_pedidos;
    while (actualPedido != nullptr) {
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("ID del Pedido:"));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(to_string(actualPedido->idPedido).c_str()));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("ID del Producto Comprado:"));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(to_string(actualPedido->idProductoComprado).c_str()));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Comprado por:"));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(actualPedido->nombreCliente));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Categoría del Producto:"));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(actualPedido->categoria));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Cantidad Comprada:"));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(to_string(actualPedido->cantidadComprada).c_str()));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Precio Total:"));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(to_string(actualPedido->precio).c_str()));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)TEXT("Método de Pago:"));
        SendMessage(GetDlgItem(hWnd, IDC_cancconfbol), LB_ADDSTRING, 0, (LPARAM)(actualPedido->metodoPago));

        actualPedido = actualPedido->siguiente;
    }
}

//---------------------------------------------Ids_Lista
void agregarIds(Ids* nuevoId) {
    nuevoId->anterior = nullptr;
    nuevoId->siguiente = nullptr;
    if (ini_Ids != nullptr)
    {
        delete ini_Ids;
        ini_Ids = nullptr;
        fin_Ids = nullptr;
    }
    ini_Ids = nuevoId;
    fin_Ids = nuevoId;
}
void leerIds(char archivo[]) {
    ifstream leerIds(archivo, ios::binary);
    if (leerIds.is_open())
    {
        Ids* nuevoIds = new Ids;
        leerIds.read((char*)nuevoIds, sizeof(Ids));
        nuevoIds->anterior = nullptr;
        nuevoIds->siguiente = nullptr;
        while (!leerIds.eof())
        {
            agregarIds(nuevoIds);
            nuevoIds = new Ids;
            leerIds.read((char*)nuevoIds, sizeof(Ids));
            nuevoIds->anterior = nullptr;
            nuevoIds->siguiente = nullptr;
        }
    }
}
void escribirIds(char archivo[]) {
    ofstream escribirIds(archivo, ios::binary | ios::trunc);
    if (escribirIds.is_open())
    {
        aux_Ids = ini_Ids;
        while (aux_Ids != nullptr)
        {
            escribirIds.write(reinterpret_cast<char*>(aux_Ids), sizeof(Ids));
            aux_Ids = aux_Ids->siguiente;
        }
        escribirIds.close();
    }
}
//---------------------------------------------ADMIN_Lista
void agregarAdmin(admin* nuevoAdmin) {
    nuevoAdmin->siguiente = nullptr;
    nuevoAdmin->anterior = nullptr;
    if (ini_admin == nullptr) {
        ini_admin = nuevoAdmin;
        fin_admin = nuevoAdmin;
    }
    else {
        fin_admin->siguiente = nuevoAdmin;
        nuevoAdmin->anterior = fin_admin;
        fin_admin = nuevoAdmin;
    }
}
void leeradmin(char archivo[]) {
    ifstream archivoALeerAdmin(archivo, ios::binary);
    if (archivoALeerAdmin.is_open()) {
        admin* nuevo = new admin;
        archivoALeerAdmin.read((char*)nuevo, sizeof(admin));
        nuevo->anterior = nullptr;
        nuevo->siguiente = nullptr;
        while (!archivoALeerAdmin.eof()) {
            agregarAdmin(nuevo);
            nuevo = new admin;
            archivoALeerAdmin.read((char*)nuevo, sizeof(admin));
            nuevo->anterior = nullptr;
            nuevo->siguiente = nullptr;
        }
    }
}
void escribiradmin(char archivo[]) {
    ofstream archivoAEscribir;
    archivoAEscribir.open(archivo, ios::binary | ios::trunc);
    if (archivoAEscribir.is_open()) {
        aux_admin = ini_admin;
        while (aux_admin != nullptr) {
            archivoAEscribir.write(reinterpret_cast<char*>(aux_admin), sizeof(admin));
            aux_admin = aux_admin->siguiente;
        }
        archivoAEscribir.close();
    }
}
//---------------------------------------------USUARIOS_ArbolBinario
bool registroUsuario(usuarios** arbol, usuarios* nodo) {
    if (*arbol != nullptr) {
        int decisiondelado = strcmp(nodo->nombreUsuario, (*arbol)->nombreUsuario);
        if (decisiondelado < 0) {
            return registroUsuario(&((*arbol)->izquierda), nodo);
        }
        else if (decisiondelado > 0) {
            return registroUsuario(&((*arbol)->derecha), nodo);
        }
        else {
            return false; // Usuario ya existente
        }
    }
    else {
        nodo->izquierda = nullptr;
        nodo->derecha = nullptr;
        *arbol = nodo;
        return true;
    }
}
bool buscarUsuario(usuarios* leaf, char* nombreUsuario) {
    while (leaf)
    {
        int decisiondelado = strcmp(nombreUsuario, leaf->nombreUsuario);
        if (decisiondelado == 0) { actualUsuarios = leaf; return true; }
        else if (decisiondelado < 0) { leaf = leaf->izquierda; }
        else { leaf = leaf->derecha; }
    }
    return false;
}
void recorrerPreorden(usuarios* nodo, HWND listbox) {
    if (nodo != nullptr) {
        ListaUsuarios(nodo, listbox);
        recorrerPreorden(nodo->izquierda, listbox);
        recorrerPreorden(nodo->derecha, listbox);
    }
}
void ListaUsuarios(usuarios* nodo, HWND listbox) {
    SendMessage(listbox, LB_ADDSTRING, 0, (LPARAM)nodo->nombre);
}
void escribirArchivoUsuario(char archivo[], usuarios* arbol) {
    ofstream escribir;
    escribir.open(archivo, ios::binary | ios::trunc);
    if (escribir.is_open()) {
        escribirNodoDirecto(escribir, arbol);
        escribir.close();
        //cout << "Archivo guardado" << endl;
    }
    else {
        //cout << "Error al abrir " << endl;
    }
}
void escribirNodoDirecto(ofstream& archivo, usuarios* nodo) {
    if (nodo != nullptr) {
        archivo.write(reinterpret_cast<char*>(nodo), sizeof(usuarios));
        escribirNodoDirecto(archivo, nodo->izquierda);
        escribirNodoDirecto(archivo, nodo->derecha);
    }
}
void leerArchivoUsuarios(char archivo[]) {
    ifstream filepass(archivo, ios::binary);
    if (filepass.is_open()) {
        raiz = nullptr; // Reinicia el árbol
        leerNodoDirecto(filepass);
        filepass.close();
        cout << "Archivo leido" << endl;
    }
    else {
        cout << "Error al abrir el archivo para leer" << endl;
    }
}
void leerNodoDirecto(ifstream& archivo) {
    usuarios* nuevo = new usuarios;
    while (archivo.read(reinterpret_cast<char*>(nuevo), sizeof(usuarios))) {
        nuevo->izquierda = nullptr;
        nuevo->derecha = nullptr;
        registroUsuario(&raiz, nuevo);
        nuevo = new usuarios;
    }
    delete nuevo;
}
void escribirUserlast(const char* archivo) {
    ofstream escribir;
    escribir.open(archivo, ios::binary | ios::trunc);
    if (escribir.is_open()) {
        escribir.write(reinterpret_cast<char*>(&ultimoUsuario), sizeof(ultimoUsuario));
        escribir.write(reinterpret_cast<char*>(&ultimaContrasena), sizeof(ultimaContrasena));
        escribir.write(reinterpret_cast<char*>(&ultimoPuesto), sizeof(ultimoPuesto));
        escribir.close();
    }
}

//---------------------------------------------Ultimo Usuario_Lista
void agregarUltPas(ultPas* nuevoUltPas) {
    nuevoUltPas->anterior = nullptr;
    nuevoUltPas->siguiente = nullptr;

    // Si ya hay un nodo en la lista se elimina
    //tal vez haya formas mas optimas de hacer esto pero es la que se me ocurrio
    if (ini_ult != nullptr) {
        delete ini_ult;
        ini_ult = nullptr;
        fin_ult = nullptr;
    }
    // Agrega el nuevo nodo como el único en la lista
    ini_ult = nuevoUltPas;
    fin_ult = nuevoUltPas;
}
void leerUltPas(char archivo[]) {
    ifstream leerUltPas(archivo, ios::binary);
    if (leerUltPas.is_open())
    {
        ultPas* nuevo = new ultPas;
        leerUltPas.read((char*)nuevo, sizeof(ultPas));
        nuevo->anterior = nullptr;
        nuevo->siguiente = nullptr;
        while (!leerUltPas.eof())
        {
            agregarUltPas(nuevo);
            nuevo = new ultPas;
            leerUltPas.read((char*)nuevo, sizeof(ultPas));
            nuevo->anterior = nullptr;
            nuevo->siguiente = nullptr;
        }
    }
}
void escribirUltPas(char archivo[]) {
    ofstream escribirUltPass(archivo, ios::binary | ios::trunc);
    if (escribirUltPass.is_open()) {
        aux_ult = ini_ult;
        while (aux_ult != nullptr)
        {
            escribirUltPass.write(reinterpret_cast<char*>(aux_ult), sizeof(ultPas));
            aux_ult = aux_ult->siguiente;
        }
        escribirUltPass.close();
    }
}
//---------------------------------------------BOLETOS_Lista
void agregarPedido(pedidos* nuevoPedido) {
    nuevoPedido->siguiente = nullptr;
    nuevoPedido->anterior = nullptr;

    if (ini_pedidos == nullptr) {
        ini_pedidos = nuevoPedido;
        fin_pedidos = nuevoPedido;
    }
    else {
        fin_pedidos->siguiente = nuevoPedido;
        nuevoPedido->anterior = fin_pedidos;
        fin_pedidos = nuevoPedido;
    }
}

void leerPedidos(char archivo[]) {
    ifstream archivoALeerPedidos(archivo, ios::binary);
    if (archivoALeerPedidos.is_open()) {
        pedidos* nuevoPedido = new pedidos;
        archivoALeerPedidos.read((char*)nuevoPedido, sizeof(pedidos));
        nuevoPedido->anterior = nullptr;
        nuevoPedido->siguiente = nullptr;
        while (!archivoALeerPedidos.eof()) {
            agregarPedido(nuevoPedido);
            nuevoPedido = new pedidos;
            archivoALeerPedidos.read((char*)nuevoPedido, sizeof(pedidos));
            nuevoPedido->anterior = nullptr;
            nuevoPedido->siguiente = nullptr;
        }
    }
}
void escribirPedidos(char archivo[]) {
    ofstream archivoAEscribirPedidos(archivo, ios::binary | ios::trunc);
    if (archivoAEscribirPedidos.is_open()) {
        aux_pedidos = ini_pedidos;
        while (aux_pedidos != nullptr) {
            archivoAEscribirPedidos.write(reinterpret_cast<char*>(aux_pedidos), sizeof(pedidos));
            aux_pedidos = aux_pedidos->siguiente;
        }
        archivoAEscribirPedidos.close();
    }
}
void guardarPedidosEnArchivo(pedidos* cabeza, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        pedidos* actual = cabeza;

        while (actual != nullptr) {
            archivo << "ID Pedido: " << actual->idPedido << endl;
            archivo << "ID Cliente: " << actual->idCliente << endl;
            archivo << "Nombre Producto: " << actual->nombreProducto << endl;
            archivo << "Cantidad Comprada: " << actual->cantidadComprada << endl;
            archivo << "Metodo de Pago: " << actual->metodoPago << endl;
            archivo << "Precio Total: " << actual->precio << endl;
            archivo << "Categoría: " << actual->categoria << endl;
            archivo << "Pedido Entregado: " << actual->pedidoEntregado << endl;
            archivo << "Origen: " << actual->origen << endl;
            archivo << "Destino: " << actual->destino << endl;

            archivo << endl;

            actual = actual->siguiente;
        }
        archivo.close();
        MessageBox(NULL, "Guardando....", "Exito", MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, "Error al abrir el archivo.", "Error", MB_OK | MB_ICONERROR);
    }
}


//---------------------------------------------CLIENTES_Lista
void agregarPasajero(clientes* nuevoPasajero) {
    nuevoPasajero->anterior = nullptr;
    nuevoPasajero->siguiente = nullptr;
    if (ini_pasajeros == nullptr)
    {
        ini_pasajeros = nuevoPasajero;
        fin_pasajeros = nuevoPasajero;
    }
    else
    {
        fin_pasajeros->siguiente = nuevoPasajero;
        nuevoPasajero->anterior = fin_pasajeros;
        fin_pasajeros = nuevoPasajero;
    }
}
void leerPasajeros(char archivo[]) {
    ifstream archivoALeerPasajeros(archivo, ios::binary);
    if (archivoALeerPasajeros.is_open())
    {
        clientes* nuevoPasajero = new clientes;
        archivoALeerPasajeros.read((char*)nuevoPasajero, sizeof(clientes));
        nuevoPasajero->anterior = nullptr;
        nuevoPasajero->siguiente = nullptr;
        while (!archivoALeerPasajeros.eof())
        {
            agregarPasajero(nuevoPasajero);
            nuevoPasajero = new clientes;
            archivoALeerPasajeros.read((char*)nuevoPasajero, sizeof(clientes));
            nuevoPasajero->anterior = nullptr;
            nuevoPasajero->siguiente = nullptr;
        }
    }
}
void escribirPasajeros(char archivo[]) {
    ofstream archivoAEscribirPasajeros(archivo, ios::binary | ios::trunc);
    if (archivoAEscribirPasajeros.is_open())
    {
        aux_pasajeros = ini_pasajeros;
        while (aux_pasajeros != nullptr)
        {
            archivoAEscribirPasajeros.write(reinterpret_cast<char*>(aux_pasajeros), sizeof(clientes));
            aux_pasajeros = aux_pasajeros->siguiente;
        }
        archivoAEscribirPasajeros.close();
    }
}
//---------------------------------------------VUELOS_Lista
void agregarVuelo(productos* nuevoVuelo) {
    nuevoVuelo->siguiente = nullptr; // Asegurar que el nuevo nodo no tenga un siguiente nodo
    nuevoVuelo->anterior = nullptr;  // Asegurar que el nuevo nodo no tenga un nodo anterior

    if (ini_vuelos == nullptr) { // Si la lista está vacía
        ini_vuelos = nuevoVuelo;
        fin_vuelos = nuevoVuelo;
    }
    else { // Si la lista no está vacía
        fin_vuelos->siguiente = nuevoVuelo;
        nuevoVuelo->anterior = fin_vuelos;
        fin_vuelos = nuevoVuelo;
    }
}
void leerVuelos(char archivo[]) {
    ifstream archivoALeer(archivo, ios::binary);
    if (archivoALeer.is_open()) {

        productos* nuevo = new productos;
        archivoALeer.read((char*)nuevo, sizeof(productos));
        nuevo->anterior = nullptr;
        nuevo->siguiente = nullptr;
        while (!archivoALeer.eof())//mientras no se llegue al final del archivo
        {
            agregarVuelo(nuevo);//agregamos nuevo pasajero
            nuevo = new productos;//creando nuevos nodos
            archivoALeer.read((char*)nuevo, sizeof(productos));//seaparando memorias
            nuevo->anterior = nullptr;
            nuevo->siguiente = nullptr;//ajustando el archivo
        }

    }
}
void escribirVuelos(char archivo[]) {
    ofstream archivoAEscribir(archivo, ios::binary | ios::trunc);
    if (archivoAEscribir.is_open()) {
        aux_vuelos = ini_vuelos;
        while (aux_vuelos != nullptr) {
            archivoAEscribir.write(reinterpret_cast<char*>(aux_vuelos), sizeof(productos));
            aux_vuelos = aux_vuelos->siguiente;
        }
        archivoAEscribir.close();
    }
}
void guardarListaEnArchivo(productos* cabeza, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        productos* actual = cabeza;

        while (actual != nullptr) {

            double fechaVuelo_double = 0;
            double horaVuelo_double = 0;
            SystemTimeToVariantTime(&(actual->fechaVuelo), &fechaVuelo_double);
            SystemTimeToVariantTime(&(actual->horaVuelo), &horaVuelo_double);

            if (fechaVuelo_double >= buscar_citas_de && fechaVuelo_double <= buscar_citas_al) {
                archivo << "NumVuelo: " << actual->numvue << endl;
                archivo << "Origen: " << actual->origen << endl;
                archivo << "Destino: " << actual->destino << endl;
                archivo << "Fecha: " << fechaVuelo_double << endl;
                archivo << "Hora: " << horaVuelo_double << endl;
                archivo << "TipoPedido: " << actual->tipoav << endl;
                archivo << "PedidosTotales: " << actual->asientotal << endl;
                archivo << "Con caja: " << actual->ejecutiva << endl;
                archivo << "Sin caja: " << actual->turista << endl;
                archivo << "PrecioEmpaquetado: " << actual->precioejecutiva << endl;
                archivo << "PrecioSinPaquete: " << actual->precioturista << endl;
                archivo << "Empaquetado: " << actual->mayores << endl;
                archivo << "Sin empaquetar: " << actual->menores << endl;
                archivo << "DiasCancelados: " << actual->diascan << endl;
                archivo << endl;
            }


            actual = actual->siguiente;
        }
        archivo.close();
        MessageBox(NULL, "Lista guardada exitosamente en el archivo.", "Exito", MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, "Error al abrir el archivo.", "Error", MB_OK | MB_ICONERROR);
    }
}
void eliminarVuelo(productos* vueloEliminar) {
    if (vueloEliminar == nullptr) return;

    // Verificar si el vuelo a eliminar es el primero de la lista
    if (vueloEliminar == ini_vuelos) {
        ini_vuelos = ini_vuelos->siguiente;
        delete vueloEliminar;
        return;
    }

    // Buscar el vuelo anterior al vuelo a eliminar
    productos* anterior = ini_vuelos;
    while (anterior->siguiente != vueloEliminar) {
        anterior = anterior->siguiente;
    }

    // Enlazar el vuelo anterior con el siguiente del vuelo a eliminar
    anterior->siguiente = vueloEliminar->siguiente;
    delete vueloEliminar;
}
void MostrarDetallesVueloEnLista(productos* vuelo, HWND hWnd, int listaID) {
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("* * * * * * * * * * * * * * * * * * * * * * * * * * *"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("ID PEDIDO:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(to_string(vuelo->idvuelo).c_str()));
    int opc = SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("Pedido originado en:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(vuelo->origen));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("Destino:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(vuelo->destino));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("Tipo de producto:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(vuelo->tipoav));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("Total de pedidos:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, opc, (LPARAM)(to_string(vuelo->asientotal).c_str()));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("Total de pedidos con caja:")); //ejecutivo
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(to_string(vuelo->ejecutiva).c_str()));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("precio:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(to_string(vuelo->precioejecutiva).c_str()));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("Total de pedidos sin caja:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(to_string(vuelo->turista).c_str()));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("precio:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(to_string(vuelo->precioturista).c_str()));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("# de pedidos con caja:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(to_string(vuelo->menores).c_str()));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)TEXT("# de pedidos sin caja:"));
    SendMessage(GetDlgItem(hWnd, listaID), LB_ADDSTRING, 0, (LPARAM)(to_string(vuelo->mayores).c_str()));


}

bool esSoloNumeros(WCHAR* str) {
    setlocale(LC_ALL, "");  // Establece la localización al valor predeterminado del sistema
    for (int i = 0; str[i] != L'\0'; i++) {
        if (!iswdigit(str[i])) {
            return false;
        }
    }
    return true;
}
bool esSoloLetras(WCHAR* str) {
    setlocale(LC_ALL, "");  // Establece la localización al valor predeterminado del sistema
    for (int i = 0; str[i] != L'\0'; i++) {
        if (!iswalpha(str[i]) && str[i] != L' ') {
            return false;
        }
    }
    return true;
}
productos* buscarVueloPorDestino(const char* destino) {
    productos* vueloActual = ini_vuelos;
    while (vueloActual != NULL) {
        if (strcmp(vueloActual->destino, destino) == 0) {
            return vueloActual;
        }
        vueloActual = vueloActual->siguiente;
    }
    return NULL;
}

productos* buscarPorId(int idmandar) {
    productos* vueloActual = ini_vuelos;
    while (vueloActual != NULL) {
        // Convertir la fecha del vueloActual a string
        string fechaActual =
            to_string(vueloActual->fechaRegistro.wDay) + '/' +
            to_string(vueloActual->fechaRegistro.wMonth) + '/' +
            to_string(vueloActual->fechaRegistro.wYear);

        // Comparar fecha y destino Y ID
        if (vueloActual->idvuelo == idmandar) {
            return vueloActual;
        }
        vueloActual = vueloActual->siguiente;
    }
    return NULL;
}

productos* buscarVueloPorFechaYDestino(const string& fechaVuelo, const char* destino, int idmandar) {
    productos* vueloActual = ini_vuelos;
    while (vueloActual != NULL) {
        // Convertir la fecha del vueloActual a string
        string fechaActual =
            to_string(vueloActual->fechaRegistro.wDay) + '/' +
            to_string(vueloActual->fechaRegistro.wMonth) + '/' +
            to_string(vueloActual->fechaRegistro.wYear);

        // Comparar fecha y destino Y ID
        if (fechaActual == fechaVuelo && strcmp(vueloActual->destino, destino) == 0 && vueloActual->idvuelo == idmandar) {
            return vueloActual;
        }
        vueloActual = vueloActual->siguiente;
    }
    return NULL;
}
int generarNumeroVuelo(productos* nodoVue) {
    srand(time(NULL));
    int i = rand() % 99999 + 10000;
    if (!BinaryF(nodoVue, i)) {
        return i;
    }
    else {
        return generarNumeroVuelo(nodoVue);
    }

}
productos* BinaryF(productos* head, int value) {
    productos* start = head;
    productos* last = nullptr;

    do {
        productos* mid = middleVuelos(start, last);
        if (mid == nullptr)
            return nullptr;
        if (mid->numvue == value)
            return mid;
        else if (mid->numvue < value)
            start = mid->siguiente;
        else
            last = mid;
    } while (last == nullptr || last != start);

    return nullptr;
}
productos* middleVuelos(productos* start, productos* last) {
    if (start == nullptr)
        return nullptr;

    productos* slow = start;
    productos* fast = start->siguiente;

    while (fast != last && fast != nullptr) {
        fast = fast->siguiente;
        if (fast != last && fast != nullptr) {
            slow = slow->siguiente;
            fast = fast->siguiente;
        }
    }

    return slow;
}

clientes* middle(clientes* start, clientes* last) {
    if (start == nullptr)
        return nullptr;

    clientes* slow = start;
    clientes* fast = start->siguiente;

    while (fast != last && fast != nullptr) {
        fast = fast->siguiente;
        if (fast != last && fast != nullptr) {
            slow = slow->siguiente;
            fast = fast->siguiente;
        }
    }

    return slow;
}
int generarPase(clientes* nodoPas) {
    srand(time(NULL));
    int i = rand() % 99999 + 10000;
    if (!BinaryP(nodoPas, i)) {
        return i;
    }
    else {
        return generarPase(nodoPas);
    }
}
clientes* BinaryP(clientes* head, int value) {
    clientes* start = head;
    clientes* last = nullptr;

    do {
        clientes* mid = middlepas(start, last);
        if (mid == nullptr)
            return nullptr;
        if (mid->numvuelo == value)
            return mid;
        else if (mid->numvuelo < value)
            start = mid->siguiente;
        else
            last = mid;
    } while (last == nullptr || last != start);

    return nullptr;
}
clientes* middlepas(clientes* start, clientes* last) {
    if (start == nullptr)
        return nullptr;

    clientes* slow = start;
    clientes* fast = start->siguiente;

    while (fast != last && fast != nullptr) {
        fast = fast->siguiente;
        if (fast != last && fast != nullptr) {
            slow = slow->siguiente;
            fast = fast->siguiente;
        }
    }

    return slow;
}

void ordenarPedidos(pedidos*& head, bool (*comparar)(pedidos*, pedidos*)) {
    if (head == nullptr) return;

    pedidos* sorted = nullptr; // Lista ordenada

    // Utilizamos un método similar a la ordenación por inserción
    pedidos* current = head;
    while (current != nullptr) {
        pedidos* siguiente = current->siguiente;

        if (sorted == nullptr || comparar(current, sorted)) {
            current->siguiente = sorted;
            sorted = current;
        }
        else {
            pedidos* temp = sorted;
            while (temp->siguiente != nullptr && !comparar(current, temp->siguiente)) {
                temp = temp->siguiente;
            }
            current->siguiente = temp->siguiente;
            temp->siguiente = current;
        }
        current = siguiente;
    }

    head = sorted;
}


double FileTimeToDouble(FILETIME ft) {
    ULARGE_INTEGER ull;
    ull.LowPart = ft.dwLowDateTime;
    ull.HighPart = ft.dwHighDateTime;
    return static_cast<double>(ull.QuadPart) / (10000.0 * 1000.0 * 60.0 * 60.0 * 24.0) - 134774 * 24.0;
}
void AddStringToListBox(HWND hWnd, int listBoxId, const std::string& text) {
    int len;
    int slength = (int)text.length() + 1;
    len = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, text.c_str(), slength, buf, len);
    SendMessage(GetDlgItem(hWnd, listBoxId), LB_ADDSTRING, 0, (LPARAM)buf);
    delete[] buf;
}


//---------------------------------------------FUNCIONES DEL QUICKSORT
// Función para intercambiar dos nodos de la lista pedidos
void swap(pedidos* a, pedidos* b) {
    if (a == b) return;

    // Intercambiar todos los campos entre dos pedidos
    int temp_idPedido = a->idPedido;
    a->idPedido = b->idPedido;
    b->idPedido = temp_idPedido;

    int temp_edadCliente = a->edadCliente;
    a->edadCliente = b->edadCliente;
    b->edadCliente = temp_edadCliente;

    char temp_nacionalidadCliente[100];
    strcpy(temp_nacionalidadCliente, a->nacionalidadCliente);
    strcpy(a->nacionalidadCliente, b->nacionalidadCliente);
    strcpy(b->nacionalidadCliente, temp_nacionalidadCliente);

    int temp_idProductoComprado = a->idProductoComprado;
    a->idProductoComprado = b->idProductoComprado;
    b->idProductoComprado = temp_idProductoComprado;

    int temp_idCliente = a->idCliente;
    a->idCliente = b->idCliente;
    b->idCliente = temp_idCliente;

    bool temp_pedidoEntregado = a->pedidoEntregado;
    a->pedidoEntregado = b->pedidoEntregado;
    b->pedidoEntregado = temp_pedidoEntregado;

    char temp_nombreCliente[50];
    strcpy(temp_nombreCliente, a->nombreCliente);
    strcpy(a->nombreCliente, b->nombreCliente);
    strcpy(b->nombreCliente, temp_nombreCliente);

    char temp_apellidoPatCliente[50];
    strcpy(temp_apellidoPatCliente, a->apellidoPatCliente);
    strcpy(a->apellidoPatCliente, b->apellidoPatCliente);
    strcpy(b->apellidoPatCliente, temp_apellidoPatCliente);

    char temp_apellidoMatCliente[50];
    strcpy(temp_apellidoMatCliente, a->apellidoMatCliente);
    strcpy(a->apellidoMatCliente, b->apellidoMatCliente);
    strcpy(b->apellidoMatCliente, temp_apellidoMatCliente);

    char temp_metodoPago[17];
    strcpy(temp_metodoPago, a->metodoPago);
    strcpy(a->metodoPago, b->metodoPago);
    strcpy(b->metodoPago, temp_metodoPago);

    float temp_precio = a->precio;
    a->precio = b->precio;
    b->precio = temp_precio;

    char temp_origen[60];
    strcpy(temp_origen, a->origen);
    strcpy(a->origen, b->origen);
    strcpy(b->origen, temp_origen);

    char temp_destino[60];
    strcpy(temp_destino, a->destino);
    strcpy(a->destino, b->destino);
    strcpy(b->destino, temp_destino);


    char temp_nombreProducto[60];
    strcpy(temp_nombreProducto, a->nombreProducto);
    strcpy(a->nombreProducto, b->nombreProducto);
    strcpy(b->nombreProducto, temp_nombreProducto);

    char temp_categoria[60];
    strcpy(temp_categoria, a->categoria);
    strcpy(a->categoria, b->categoria);
    strcpy(b->categoria, temp_categoria);

    int temp_cantidadComprada = a->cantidadComprada;
    a->cantidadComprada = b->cantidadComprada;
    b->cantidadComprada = temp_cantidadComprada;
}
pedidos* partition(pedidos* low, pedidos* high) {
    float pivot = high->precio; // Usamos el precio como pivote para ordenar por monto total
    pedidos* i = low->anterior;

    for (pedidos* j = low; j != high; j = j->siguiente) {
        if (j->precio >= pivot) { // Orden descendente por precio
            i = (i == nullptr) ? low : i->siguiente;
            swap(i, j);
        }
    }
    i = (i == nullptr) ? low : i->siguiente;
    swap(i, high);
    return i;
}
// Función de Quicksort para ordenar la lista de pedidos
void quickSort(pedidos* low, pedidos* high) {
    if (high != nullptr && low != high && low != high->siguiente) {
        pedidos* p = partition(low, high);
        quickSort(low, p->anterior);
        quickSort(p->siguiente, high);
    }
}
// Obtener el último nodo de la lista de pedidos
pedidos* getLastNode(pedidos* node) {
    while (node != nullptr && node->siguiente != nullptr)
        node = node->siguiente;
    return node;
}
// Función para ordenar la lista de pedidos en orden descendente usando Quicksort
void ordenarPedidosDescendenteQuicksort() {
    pedidos* last = getLastNode(ini_pedidos);
    quickSort(ini_pedidos, last);
}


//---------------------------------------------FUNCIONES DEL HEAPSORT
void heapify(pedidos arr[], int n, int i) {
    int largest = i;  // Inicializar el nodo raíz como el más grande
    int left = 2 * i + 1;  // Hijo izquierdo en el árbol
    int right = 2 * i + 2; // Hijo derecho en el árbol

    // Comparación utilizando el nombre del cliente (orden alfabético)
    if (left < n && std::string(arr[left].nombreCliente) > std::string(arr[largest].nombreCliente))
        largest = left;

    if (right < n && std::string(arr[right].nombreCliente) > std::string(arr[largest].nombreCliente))
        largest = right;

    // Si el nodo raíz no es el más grande, realizar intercambio y continuar ajustando
    if (largest != i) {
        swap(&arr[i], &arr[largest]);  // Intercambia utilizando la función swap para pedidos
        heapify(arr, n, largest); // Llamada recursiva para ajustar el árbol
    }
}


void heapSort(pedidos arr[], int n) {
    // Construir el heap (reorganizar el array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extraer elementos uno por uno desde el heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]); // Mueve la raíz actual al final
        heapify(arr, i, 0); // Llamada para ajustar el árbol reducido
    }
}

void GuardarListBoxEnArchivo(HWND hWndListBox, const char* nombreArchivo) {
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        MessageBox(NULL, "No se pudo abrir", "Guardar", MB_OK | MB_ICONINFORMATION);
        return;
    }

    // Obtener el número de elementos en el ListBox
    int itemCount = SendMessage(hWndListBox, LB_GETCOUNT, 0, 0);

    // Iterar sobre los elementos y escribirlos en el archivo
    for (int i = 0; i < itemCount; ++i) {
        char buffer[256]; // Buffer para almacenar el texto del elemento
        SendMessage(hWndListBox, LB_GETTEXT, i, (LPARAM)buffer);
        archivo << buffer << endl;

    }

    archivo.close();

    // Mostrar MessageBox indicando que el archivo se ha guardado con éxito
    MessageBox(NULL, "Archivo guardado con Exito", "Guardar", MB_OK | MB_ICONINFORMATION);
}



bool compararPorCantidad(pedidos* a, pedidos* b) {
    return a->cantidadComprada > b->cantidadComprada; // Ordenar de mayor a menor cantidad comprada
}
bool compararPorCliente(pedidos* a, pedidos* b) {
    return strcmp(a->nombreCliente, b->nombreCliente) < 0; // Orden alfabético
}
