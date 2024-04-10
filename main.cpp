#include <iostream>
#include "Graph.h"
#include "Book.h"
using namespace std;

int menu(){
    int option;
    cout << "\n\n- - - - - - - - - - - - - - - - M E N U - - - - - - - - - - - - - - - - - -"<<endl;
    cout<< "[1]. Ingresar libro." << endl;
    cout<< "[2]. Buscar nodo." << endl;
    cout<< "[3]. Establecer relacion." << endl;
    cout<< "[4]. Eliminar libro." << endl;
    cout<< "[5]. Libros existentes." << endl;
    cout<< "[6]. DFS Path." << endl;
    cout<< "[7]. BFS Path." << endl;
    cout<< "[8]  Prim Algorithm" << endl;
    cout<< "[9]  Dijktra Algorithm" << endl;
    cout<< "[10]  Datos prueba" << endl;
    cout<< "[0]. Salir." ;
    cout<< "\nDigite una opcion: " ;
    cin>>option;
    return option;
}

Book *createBook();
void readRelation(Graph *graph);
string readForDFS(Graph *graph);
string readForBFS(Graph *graph);
void readForPrim(Graph *graph);
string readForDijkstra(Graph *graph);
void dataTest(Graph *graph);

int main() {
    Graph *graph = new Graph();
    int choice;

    while((choice=menu())!=0){
        switch (choice) {
            case 1:
                cout << "\n- - - - - - - - - - I N G R E S A R  U N  L I B R O - - - - - - - - - - " << endl;
                Book *toAdd;
                toAdd = createBook();
                if(toAdd != NULL){
                    graph->addEdge(toAdd);
                    cout << "Libro agregado correctamente!" << endl;
                } else {
                    cout << "Ocurrio un error!" << endl;
                }
                break;
            case 2:
                break;
            case 3:
                cout << "\n- - - - - - - - - - I N S E R T A R   R E L A C I O N E S - - - - - - - - - - " << endl;
                try{
                    readRelation(graph);
                    cout << "\nRelacion establecida exitosamente";
                } catch (domain_error &e) {
                    cout << "\nNO HAY TALES ELEMENTOS";
                }
                break;
            case 4:
                break;
            case 5:
                cout << "\n- - - - - - - - - - M O S T R A R  L I B R O S - - - - - - - - - - " << endl;
                if(!graph->getBooks().isEmpty()){
                    cout << *graph;
                }
                else{
                    cout<<"NO HAY LIBROS INGRESADOS";
                }

                break;
            case 6:
                cout << "\n- - - - - - - - D F S  P A T H - - - - - - - - - -" << endl;
                cout << readForDFS(graph);
                break;
            case 7:
                cout << "\n- - - - - - - - B F S  P A T H - - - - - - - - - -" << endl;
                cout << readForBFS(graph);
                break;

            case 8:
                cout << "\n- - - - - - - P R I M  A L G O R I T H M - - - - - - - - "<< endl;
                readForPrim(graph);
                break;
            case 9:
                cout << "\n- - - - - - - D I J K S T R A  A L G O R I T H M - - - - - - - - "<< endl;
                cout << readForDijkstra(graph);
                break;
            case 10:
                cout << "\n Data charged\n" << endl;
                dataTest(graph);
            default:
                break;
        }
    }
}

Book *createBook(){
    string nombre, descripcion, dia, mes, anio;
    cout << "Autor: GABRIEL GARCIA MARQUEZ. " << endl;
    cout << "Obra: ";
    cin.ignore();
    getline(cin,nombre);
    cout << "Descripcion: ";
    cin.ignore();
    getline(cin,descripcion);
    cout <<" - Fecha - " << endl;
    cout <<"Dia: ";
    cin >> dia;
    cout <<"Mes: ";
    cin >> mes;
    cout <<"Anio: ";
    cin >> anio;

    try{
        StringOp validator;
        validator.validateNumber(dia);
        validator.validateNumber(mes);
        validator.validateNumber(anio);

        Book *toAdd = new Book(nombre,descripcion,dia,mes,anio);
        return toAdd;

    } catch(invalid_argument &e){
        cout << "Ingrese una fecha correcta!" << endl;
        return NULL;
    }
}

void readRelation(Graph *graph){
    string book1, book2;
    int cost;

    if(!graph->getBooks().isEmpty()){
        cout << "\nDigite el nombre del primer libro: ";
        cin.ignore();
        getline(cin,book1);
        cout << "\nDigite el nombre del segundo libro: ";
        getline(cin,book2);
        cout << "\nDigite el peso de la relacion: ";
        cin >> cost;
        graph->relate(book1,book2,cost);
    }
    else{
        cout << "\nNO HAY LIBROS EN LOS CUALES SE ESTABLEZCA UNA RELACIÓN";
    }

}

string readForDFS(Graph *graph) {
    string book;
    cout << "ingrese le libro inicial: ";
    cin.ignore();
    getline(cin, book);
    return graph->dfs(book);

}

string readForBFS(Graph *graph) {
    string book;
    cout << "ingrese le libro inicial: ";
    cin.ignore();
    getline(cin, book);
    return graph->bfs(book);

}

void readForPrim(Graph *graph){
    string initialBook;
    cout << "Ingrese el libro de inicio: ";
    cin.ignore();
    getline(cin, initialBook);
    cout << "El grafo de costo minimo es: " << endl;
    cout << *(graph->prim(initialBook));
}

string readForDijkstra(Graph *graph){
    string initialBook, destinationBook;
    cout << "Ingrese el libro inicial: ";
    cin.ignore();
    getline(cin, initialBook);
    cout << "Ingrese el libro destino: ";
    getline(cin,destinationBook);
    return graph->dijkstraShortestPath(initialBook, destinationBook);
}

void dataTest(Graph *graph){
    graph->addEdge(new Book("A","1","1/1/1"));
    graph->addEdge(new Book("B","1","1/1/1"));
    graph->addEdge(new Book("C","1","1/1/1"));
    graph->addEdge(new Book("D","1","1/1/1"));
    graph->addEdge(new Book("E","1","1/1/1"));
    graph->addEdge(new Book("F","1","1/1/1"));

    graph->relate("A","B",2);
    graph->relate("A","D",8);
    graph->relate("B","A",2);
    graph->relate("B","E",6);
    graph->relate("B","D",5);
    graph->relate("D","A",8);
    graph->relate("D","B",5);
    graph->relate("D","E",3);
    graph->relate("D","F",2);
    graph->relate("E","B",6);
    graph->relate("E","D",3);
    graph->relate("E","F",1);
    graph->relate("E","C",9);
    graph->relate("F","D",2);
    graph->relate("F","E",1);
    graph->relate("F","C",3);
    graph->relate("C","E",9);
    graph->relate("C","F",3);

}