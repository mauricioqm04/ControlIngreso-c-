#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <ctime>
#include <time.h>
using namespace std;

struct Nodo{
	string placa;
	string tecno;
	string soat;
	string movimiento;
	string hora;
	string minuto;
	string segundo;
	string fecha;
	Nodo *siguiente;
};

struct tope{
	char dato;
};

//prototipos de funciones
void menu();
void menuinformes();
void insertarLista (Nodo *&, string, string, string, string, string, string, string, string);
void MostrarLista (Nodo *);
void BuscarLista (Nodo *);
void guardar(Nodo *&);
void cargar(Nodo *&);
void modificarNodo(Nodo *);
void eliminar(Nodo *&);
string tiempoH();
string tiempoM();
string tiempoS();
string tiempof();
string validarPlaca(string);
string validarFecha(string);
bool listaVacia(Nodo *);
bool valor();

//funciones de informes
void cantIngreso();
void cantSalida();
void entraSale();
void horaComunI();
void horaComunS();


Nodo *lista=NULL;
string placa, tecno, soat, mov, hora, minuto, segundo, fecha; 
ofstream archivo;

int main(){
	cout<<"\t------¡¡¡BIENVENIDO!!!------\n\n";	
	cargar(lista);	//cargar la lista si tiene datos 
	menu();
	return 0;
}
//funcion del menu principal
void menu(){
	int op;
	do{
			cout<<"------MENU-------\n";
			cout<<"1. Ingreso.\n";
			cout<<"2. Mostrar.\n";
			cout<<"3. Buscar.'\n";
			cout<<"4. Modificar.\n";
			cout<<"5. Eliminar. \n";
			cout<<"6. Informes. \n";		
			cout<<"7. Salir.\n";
			cout<<"Opcion: ";
			cin>>op;
		
		switch(op){
			case 1: cout<<"Ingrese la placa: ";
					cin>>placa;
					placa=validarPlaca(placa);	//a la placa le asigno lo que me deveuelve la funcion
					cout<<"Tecnomecanica: "<<endl;
					cout<<"1. Vigente "<<endl;
					cout<<"2. No vigente "<<endl;				
					if(valor()==true){
						tecno="Vigente";
					}
					else{
						tecno="No_vigente";
					}
					cout<<"Soat: "<<endl;
					cout<<"1. Vigente "<<endl;
					cout<<"2. No vigente "<<endl;					
					if(valor()==true){
						soat="Vigente";
					}
					else{
						soat="No_vigente";
					}
					cout<<"Tipo de movimiento: "<<endl;
					cout<<"1. Entra"<<endl;
					cout<<"2. Sale "<<endl;
					if(valor()==true){
						mov="Entrada";
					}
					else{
						mov="Salida";
					}
					hora=tiempoH();		//La hora los miutos y los segundos se guardan por separado
					minuto=tiempoM();	
					segundo=tiempoS();					
					fecha=tiempof();
					insertarLista(lista, placa, tecno, soat, mov, hora, minuto, segundo, fecha);
					cout<<"\tIngreso exitoso. "<<endl;
					system("pause");
					break;
					
			case 2: MostrarLista (lista);
					system("pause");
					break;
			
			case 3: if(listaVacia(lista)){
						cout<<"La lista se encuentra vacia. "<<endl;					
					}
					else{
						BuscarLista(lista);						
					}
					system("pause");
					break;
					
			case 4:	if(listaVacia(lista)){
						cout<<"La lista se encuentra vacia. "<<endl;					
					}
					else{
						modificarNodo(lista);						
					}
					system("pause");
					break;
			
			case 5: if(listaVacia(lista)){
						cout<<"La lista se encuentra vacia. "<<endl;					
					}
					else{
						eliminar(lista);						
					}
					system("pause");
					break;
			
			case 6: if(listaVacia(lista)){
						cout<<"La lista se encuentra vacia, no se puede ingresar a los informes. "<<endl;					
					}
					else{
						system("cls");
						menuinformes();
					}
					system("pause");						
					break;
					
			case 7: guardar(lista);	//se debe elimianr la lista 
					cout<<"La informacion se guardo con exito.\n";
					system("pause");
					break;
					
			default: cout<<"Opcion no valida. "<<endl;
					system("pause");
		}
		system("cls");
	}while(op!=7);
	
}

//insertar nodo a la lista
void insertarLista (Nodo *&lista, string pla, string tm, string seguro, string mv, string hor, string min, string seg, string fech){
	Nodo *nuevo_nodo = new Nodo ();
	nuevo_nodo->placa = pla;		//se asignan los valores al nodo
	nuevo_nodo->tecno = tm;
	nuevo_nodo->soat = seguro;
	nuevo_nodo->movimiento=mv;
	nuevo_nodo->hora=hor;
	nuevo_nodo->minuto=min;
	nuevo_nodo->segundo=seg;
	nuevo_nodo->fecha=fech;
	nuevo_nodo->siguiente=NULL;
  
	Nodo *aux;
	
	if (lista == NULL){    
		lista = nuevo_nodo;	
	}    
	else{    
		aux=lista;
	while(aux->siguiente!=NULL){
		aux=aux->siguiente;
	}
	aux->siguiente=nuevo_nodo;
	}   
}

//funcion para validar formato de la placa
string validarPlaca(string placa){
	bool tamanio=true;
    bool valeL=true;
    bool valeN=true;
    
    do{
        if(placa.length()!=6){
            tamanio=false;	//la placa debe tener 3 digitos y 3 caracteres
        }else{
            tamanio=true;
        }
        for(int i=0; i<3; i++){	//se deben recorrer los primeros 3 caracteres y validar que sean letras
            if((int)(placa[i]) < 65|| (int)(placa[i]) > 90){
                valeL=false;
                break;
            }else{valeL=true;}
        }
        if(valeL==false){
        	for(int i=0; i<3; i++){	//esto para validar que se puedan ingresar mayus y minusculas
            	if((int)(placa[i]) < 97 || (int)(placa[i]) > 122){
                	valeL=false;
                	break;
            }else{valeL=true;}
        	}	
		}
        
        for(int i=3;i<6;i++){	//se validan los campos del 3 al 5 para comprobar que sean digitos
            if((int)(placa[i]) < 48 || (int)(placa[i]) > 57){
                valeN=false;
                break;
            }else{valeN=true;}
        }
        
        if(tamanio==false || valeL==false || valeN==false){	
            cout<<"Placa no valida, recuerde ingresar una placa con formato (ABC123): ";cin>>placa;
        }
        
    }while(tamanio==false || valeL==false || valeN==false);	//mientras alguna bandera sea false se pide la placa
    for(int i=0;i<3;i++){
        placa[i]=toupper(placa[i]);	//convertir a mayusculas las placas ingresadas
    }
    return placa;
}

//funcion para validar la fecha
string validarFecha(string fecha){
	bool tamanio=true;
    bool valeA=true;
    bool valeM=true;
    bool valeD=true;
    bool valeG=true;
    
    do{
        if(fecha.length()!=10){
            tamanio=false;
        }else{
            tamanio=true;
        }
        for(int i=0; i<4; i++){
            if((int)(fecha[i]) < 48|| (int)(fecha[i]) > 57){
                valeA=false;
                break;
            }else{valeA=true;}
        }
        
        if((int)(fecha[5]) < 48 || (int)(fecha[5]) > 57){
            valeM=false;
        }else{valeM=true;}
        if((int)(fecha[6]) < 48 || (int)(fecha[6]) > 57){
            valeM=false;
        }else{valeM=true;}
        
        if((int)(fecha[8]) < 48 || (int)(fecha[8]) > 57){
            valeD=false;
        }else{valeD=true;}
        if((int)(fecha[9]) < 48 || (int)(fecha[9]) > 57){
            valeD=false;
        }else{valeD=true;}
        
        if((int)(fecha[4]) != 45 || (int)(fecha[7]) != 45){
            valeG=false;
        }else{valeG=true;}
        
        
        if(tamanio==false || valeA==false || valeM==false || valeD==false || valeG==false){
            cout<<"Fecha no valida, el formato debe ser (ano-mes-dia): ";cin>>fecha;
        }
        
    }while(tamanio==false || valeA==false || valeM==false || valeD==false || valeG==false);
    return fecha;
}

//funcion para mostrar los elementos de la lista
void MostrarLista (Nodo * lista){
  Nodo *actual = new Nodo ();
  actual = lista;
  
  if(listaVacia(lista)){
  	cout<<"\nLa lista se encuentra vacia. "<<endl;
  }
  
  while (actual != NULL){    
      cout <<"\nPlaca:		" <<actual->placa;
      cout <<"\nTecno: 		" <<actual->tecno;
      cout <<"\nSoat : 		" <<actual->soat;
      cout <<"\nMovim:		" <<actual->movimiento;
      cout <<"\nHora :		" <<actual->hora<<":"<<actual->minuto<<":"<<actual->segundo;
      cout <<"\nFecha: 		" <<actual->fecha;
      cout <<"\n";
      actual = actual->siguiente;
  }  
}

//funcion para imprimir la hora
string tiempoH(){
	// Tiempo actual
  	time_t t = time(NULL);
  	struct tm tiempoLocal = *localtime(&t);
  	// El lugar en donde se pondrá la fecha y hora formateadas
  	char fechaHora[70];
  	// El formato. Mira más en https://en.cppreference.com/w/c/chrono/strftime
  	char *formato = "%H";
  	// Intentar formatear https://parzibyte.me/blog/2019/07/31/c-obtener-formatear-fecha-actual/
  	int bytesEscritos = strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);       	
  return fechaHora;
}

//funcion para imprimir minutos
string tiempoM(){
	// Tiempo actual
  	time_t t = time(NULL);
  	struct tm tiempoLocal = *localtime(&t);
  	// El lugar en donde se pondrá la fecha y hora formateadas
  	char fechaHora[70];
  	// El formato. Mira más en https://en.cppreference.com/w/c/chrono/strftime
  	char *formato = "%M";
  	// Intentar formatear https://parzibyte.me/blog/2019/07/31/c-obtener-formatear-fecha-actual/
  	int bytesEscritos =
      strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);  	
  return fechaHora;
}

//funcion para imprimir segundos
string tiempoS(){
	// Tiempo actual
  	time_t t = time(NULL);
  	struct tm tiempoLocal = *localtime(&t);
  	// El lugar en donde se pondrá la fecha y hora formateadas
  	char fechaHora[70];
  	// El formato. Mira más en https://en.cppreference.com/w/c/chrono/strftime
  	char *formato = "%S";
  	// Intentar formatear https://parzibyte.me/blog/2019/07/31/c-obtener-formatear-fecha-actual/
  	int bytesEscritos =
      strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);  	
  return fechaHora;
}

//funcion para imprimir la fecha
string tiempof(){
	// Tiempo actual
  	time_t t = time(NULL);
  	struct tm tiempoLocal = *localtime(&t);
  	// El lugar en donde se pondrá la fecha y hora formateadas
  	char fechaHora[70];
  	// El formato. Mira más en https://en.cppreference.com/w/c/chrono/strftime
  	char *formato = "%Y-%m-%d";
  	// Intentar formatear https://parzibyte.me/blog/2019/07/31/c-obtener-formatear-fecha-actual/
  	int bytesEscritos =
      strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);  	
  return fechaHora;
}

//funcion para buscar un elemento en la lista
void BuscarLista (Nodo *lista){	
	bool band = false;
	Nodo *actual = new Nodo ();
	actual = lista;
		
	cout<<"Ingrese la placa que desea rastrear: ";
	cin>>placa;
	placa=validarPlaca(placa);
	
	int i=0;
	while (actual != NULL){    
    	if (actual->placa == placa){  //si actual es igual al elemento que estamos buscando entonces entre al condicional y cambie bandera a true
			band = true;
			i++;
			cout<<"\n\tMovimiento "<<i<<": ";	//variable i para contar mostrar los movimientos con un identificador
	    	cout <<"\nTipo de movimiento:		" <<actual->movimiento;
			if(actual->movimiento=="Entrada"){
				cout<<"\nHora de entrada: 		"<<actual->hora<<":"<<actual->minuto<<":"<<actual->segundo;
				cout <<"\nFecha de entrada : 		" <<actual->fecha;
			}
			else{
				cout<<"\nHora de salida: 		"<<actual->hora<<":"<<actual->minuto<<":"<<actual->segundo;
				cout <<"\nFecha de salida: 		" <<actual->fecha;
			}
			cout<<"\nTecnomecanica: 			"<<actual->tecno;
			cout<<"\nSoat:				"<<actual->soat;
			cout<<"\n";    
		}
    	actual = actual->siguiente;
    }
    
	//si bandera ha cambiado a true entonces el elemento se encontro
  	if (band == false){				    
      cout << "\nEl vehiculo con placa "<< placa <<" No tiene movimientos. "<<endl;	
    }  	
}

//funcion para modificar un nodo
void modificarNodo(Nodo *lista){
	Nodo *actual=new Nodo();
	int opci, op;	//variable para controlar la opcion del menu
	char sino;	//variable para decidir si cambiar mas datos
	bool band = false;		
	actual=lista;
		
	cout<<"Ingrese la placa del vehiculo: ";
	cin>>placa;
	placa=validarPlaca(placa);
	int i=0;
	while(actual!=NULL){
		if (actual->placa == placa){  //si actual es igual al elemento que estamos buscando entonces entre al condicional y cambie bandera a true
			band = true;
			i++;
			cout<<"\n\tMovimiento "<<i<<": ";
    		cout <<"\nTipo de movimiento:		" <<actual->movimiento;
			if(actual->movimiento=="Entrada"){
				cout<<"\nHora de entrada: 		"<<actual->hora<<":"<<actual->minuto<<":"<<actual->segundo;
				cout <<"\nFecha de entrada : 		" <<actual->fecha;
			}
			else{
				cout<<"\nHora de salida: 		"<<actual->hora<<":"<<actual->minuto<<":"<<actual->segundo;
				cout <<"\nFecha de salida: 		" <<actual->fecha;				
			}	
			cout<<"\nTecnomecanica: 			"<<actual->tecno;
			cout<<"\nSoat:				"<<actual->soat;	
			cout<<"\n";    
		}
    	actual = actual->siguiente;
	}
	//si bandera ha cambiado a true entonces el elemento se encontro
  	if (band == true){
  		actual=lista;
		cout<<"\nElija el movimiento que quiere modificar: ";	//se elije dentro de la cantidad de movimientos 	
		cin>>op;												//que quedaron contados dentro de la variable i
		if(op<=0||op>i){
			while(op<=0||op>i){
				cout<<"Escoja una opcion entre 0 y "<<i<<": ";
				cin>>op;	
			}			
		}
		int j=0;	//variable que cumple la misma funcion que la i
		while(actual!=NULL){
			if(actual->placa==placa){
				j++;
				if(j==op){		//op es el movimiento elegido para modificar y cuando sea igual al identificador entra
					cout<<"\n\tMovimiento "<<j<<": ";
					cout <<"\nPlaca:		" <<actual->placa;
				    cout <<"\nTecno: 		" <<actual->tecno;
				    cout <<"\nSoat : 		" <<actual->soat;
				    cout <<"\nMovim:		" <<actual->movimiento;
				    cout <<"\nHora :		" <<actual->hora<<":"<<actual->minuto<<":"<<actual->segundo;
				    cout <<"\nFecha: 		" <<actual->fecha;
				    cout <<"\n";
					
					do{
						cout<<"\nQue datos desea modificar? ";
						cout<<"\n1. Estado Tecno. ";			
						cout<<"\n2. Estado Soat. ";
						cout<<"\n3. Tipo movimiento. ";
						cout<<"\n4. Cancelar. ";
						cout<<"\nOpcion: ";
						cin>>opci;
						
						switch(opci){
							case 1: cout<<"Ingrese el nuevo Estado de la tecno: \n";
									cout<<"1. Vigente "<<endl;
									cout<<"2. No vigente "<<endl;				
									if(valor()==true){
										actual->tecno="Vigente";
									}
									else{
										actual->tecno="No_vigente";
									}	
									cout<<"\nDesea cambiar otro campo? (s/n): ";	//se pregunta si se quiere modiciar mas datos
									cin>>sino;
									break;
									
							case 2: cout<<"Ingrese el nuevo Estado del Soat: \n";									
									cout<<"1. Vigente "<<endl;
									cout<<"2. No vigente "<<endl;					
									if(valor()==true){
										actual->soat="Vigente";
									}
									else{
										actual->soat="No_vigente";
									}
									cout<<"\nDesea cambiar otro campo? (s/n): ";
									cin>>sino;
									break;
							
							case 3: cout<<"Ingrese el nuevo tipo de movimiento: \n";									
									cout<<"1. Entra  "<<endl;
									cout<<"2. Sale "<<endl;					
									if(valor()==true){
										actual->movimiento="Entrada";
									}
									else{
										actual->movimiento="Salida";
									}
									cout<<"\nDesea cambiar otro campo? (s/n): ";
									cin>>sino;
									break;
									
							case 4:	sino='n';
									break;
									
							default: cout<<"\nOpcion no valida. "<<endl;
									 system("pause");
									break;		
						}
						
					}while(sino=='s'||sino=='S');				
				}
			}
			actual=actual->siguiente;
		}
	}
	else{	//si la bandera al inicio de la funcion es igual a false es porque el vehiculo no se encontro
		cout << "\nEl vehiculo con placa "<< placa <<" No tiene movimientos. "<<endl;		
	}
}

//funcion para eliminar un vehiculo de la lista 
void eliminar(Nodo *&lista){
	char sn;
	bool band=false;
	int op;		
	Nodo *aux_borrar;
    Nodo *anterior=NULL;
    aux_borrar = lista;
	
	cout<<"Ingrese la placa del vehiculo: ";
	cin>>placa;
	placa=validarPlaca(placa);
	int i=0;
	while(aux_borrar!=NULL){
		if (aux_borrar->placa == placa){  //si actual es igual al elemento que estamos buscando entonces entre al condicional y cambie bandera a true
			band = true;
			i++;			
			cout<<"\n\tMovimiento "<<i<<": ";
    		cout <<"\nTipo de movimiento:		" <<aux_borrar->movimiento;
			if(aux_borrar->movimiento=="Entrada"){
				cout<<"\nHora de entrada: 		"<<aux_borrar->hora<<":"<<aux_borrar->minuto<<":"<<aux_borrar->segundo;
				cout <<"\nFecha de entrada : 		" <<aux_borrar->fecha;
			}
			else{
				cout<<"\nHora de salida: 		"<<aux_borrar->hora<<":"<<aux_borrar->minuto<<":"<<aux_borrar->segundo;
				cout <<"\nFecha de salida: 		" <<aux_borrar->fecha;
			}
			cout<<"\nTecnomecanica: 			"<<aux_borrar->tecno;
			cout<<"\nSoat:				"<<aux_borrar->soat;			
			cout<<"\n";			    
		}
    	aux_borrar = aux_borrar->siguiente;
	} 
	if(band == true){
		aux_borrar=lista;
		cout<<"\nElija el movimiento que quiere eliminar: ";
		cin>>op;
		if(op<=0||op>i){
			while(op<=0||op>i){
				cout<<"Escoja una opcion entre 0 y "<<i<<": ";
				cin>>op;	
			}			
		}
		int j=0;
		while(aux_borrar!=NULL){			
			if(aux_borrar->placa==placa){
				j++;
				if(op==j){
					if(anterior==NULL){	//si anterior es igual a null es porque se elimina el primero de la lista
						cout<<"\n\tSeguro que desea eliminar este registro? (s/n): ";
						cin>>sn;
						if((sn=='s')||(sn=='S')){
							lista=lista->siguiente;
							delete aux_borrar;
							cout<<"\nEste registro ha eliminado. "<<endl;
						}
						else{
							cout<<"\nEl registro no se ha eliminado. "<<endl;	
						}						
					}
					else{
						cout<<"\n\tSeguro que desea eliminar este registro? (s/n): ";
						cin>>sn;
						if((sn=='s')||(sn=='S')){
							anterior->siguiente=aux_borrar->siguiente;
							delete aux_borrar;
							cout<<"\nEste registro ha eliminado. "<<endl;
						}
						else{
							cout<<"\nEste registro no se ha eliminado. "<<endl;
						}
						
					}
				}							
			}
			anterior=aux_borrar;
			aux_borrar=aux_borrar->siguiente;
		}	
	}
	else{
		cout << "\nEl vehiculo con placa "<< placa <<" No tiene movimientos. "<<endl;	
	}
}

//funcion para guardar la informacion en el archivo
void guardar(Nodo *&lista){	 
	Nodo *actual = new Nodo();
	actual = lista;
	
	archivo.open("auxcontrolIngreso.txt", ios::app); //comando para crear el archivo, o agregar contenido
	
	//si hay un fallo al abrir el archivo 
	if(archivo.fail()){
		cout<<"\tNo se pudo crear el archivo";
		exit(1);
	}
	
	while(actual != NULL){		//mientras que actual sea diferente de null para recorrer la lista
		archivo<<actual->placa<<" "<<actual->tecno<<" "<<actual->soat<<" "<<actual->movimiento
		<<" "<<actual->hora<<" "<<actual->minuto<<" "<<actual->segundo<<" "<<actual->fecha<<endl;		
        actual=actual->siguiente;
	}	
	archivo.close();
		remove("controlIngreso.txt");
		rename("auxcontrolIngreso.txt", "controlIngreso.txt");		
}


//funcion para cargar la informacion en la lista 
void cargar(Nodo *&lista){
	ifstream archivo;
	archivo.open("controlIngreso.txt", ios::in);		//este comando abre los archivos en modo lectura
	
	archivo>>placa;									//se lee el primer campo del fichero que sabemos que es cedula
	
	if(archivo.fail()){									//si el archivo no existe o no tiene datos muestra un mensaje
		cout<<"\tNo hay informacion para cargar. \n";		
	}	
	else{										//sino entonces muestre los datos que hay ingresados	
		while(!archivo.eof()){
			archivo>>tecno>>soat>>mov>>hora>>minuto>>segundo>>fecha;	//guardamos los datos en estas variables
			insertarLista(lista, placa, tecno, soat, mov, hora, minuto, segundo, fecha);			
			archivo>>placa;	//siempre se debe leer la cedula al final del ciclo para volver a entrar 
		}
		cout<<"\tSe cargo la informacion con exito. \n";
	}	
	archivo.close();
	//remove("controlIngreso.txt");	
}


//funcion que devuelve un bool
bool valor(){
	int opcion;
	cout<<"Opcion: ";
	cin>>opcion;
	if(opcion != 1 && opcion != 2){
		while(opcion != 1 && opcion != 2){
			cout<<"Ingrese una opcion valida: ";
			cin>>opcion;
		}
	}
	if(opcion==1){
		return true;
	}
	else if(opcion == 2){
		return false;
	}	
}

//funcion para verificar si la lista esta vacia 
bool listaVacia(Nodo *lista){
	return(lista==NULL)? true:false;
}

//menu de informes
void menuinformes(){
	int op;
	do{
		cout<<"\n-----------------MENU DE INFORMES-----------\n";
		cout<<"1. Cantidad de vehiculos que ingresan al municipio. \n";
		cout<<"2. Cantidad de vehiculos que salen del municipio. \n";
		cout<<"3. Horas de entrada y salida de un vehiculo en un dia. \n";
		cout<<"4. Hora con mayor entrada y salida de vehiculos.\n";
		cout<<"5. Volver al menu principal. \n";
		cout<<"Opcion: ";
		cin>>op;
		
		switch(op){
			case 1: cantIngreso();
					break;
			case 2: cantSalida();
					break;
			case 3: entraSale();
					break;
			case 4: horaComunI();
					horaComunS();
					break;
			
			case 5: break;		
			
			default: cout<<"Opcion no valida. "<<endl;
					system("pause");
		}
		system("cls");
	}while(op!=5);
}

//funcion que cuenta los vehiculos que ingresan 
void cantIngreso(){
	Nodo *aux=new Nodo();
	Nodo *aux1=new Nodo();
	aux=lista;
	aux1=lista->siguiente;
	int cant=0, total=0;	
		
	while(aux!=NULL){
		if(aux->movimiento=="Entrada"){	
			cant++;	//contador por dias
			total++;//contador total
		}
		if(aux->siguiente==NULL){	//si es el ultimo nodo imprime y se sale del ciclo 
			cout<<"El dia "<<aux->fecha<<" ingresaron: "<<cant<<" vehiculos.\n\n";
			cout<<"Ingresaron en Total 		"<<total<<endl;
			break;
		}
		else if(aux->fecha!=aux1->fecha){	//cuando la fecha del proximo nodo es diferente se imprime 			
			cout<<"El dia "<<aux->fecha<<" ingresaron: "<<cant<<" vehiculos.\n\n";
			cant=0;	//se reinicia el contador por dias
		}		
		aux1=aux1->siguiente;
		aux=aux->siguiente;
	}
	system("pause");
}

//funcion que cuenta los vehiculos que salen
void cantSalida(){
	Nodo *aux=new Nodo();
	Nodo *aux1=new Nodo();
	aux=lista;
	aux1=lista->siguiente;
	int cant=0, total=0;		
	
	while(aux!=NULL){
		if(aux->movimiento=="Salida"){
			cant++;
			total++;
		}
		if(aux->siguiente==NULL){
			cout<<"El dia "<<aux->fecha<<" Salieron: "<<cant<<" vehiculos.\n\n";
			cout<<"Salieron en Total 	"<<total<<" vehiculos. \n"<<endl;
			break;
		}
		else if(aux->fecha!=aux1->fecha){
			cout<<"El dia "<<aux->fecha<<" Salieron: "<<cant<<" vehiculos.\n\n";
			cant=0;
		}		
		aux1=aux1->siguiente;
		aux=aux->siguiente;
	}
	system("pause");
}

//funcion hora de entrada y salida de los vehiculos
void entraSale(){
	bool band = false;
	Nodo *actual = new Nodo ();
	actual = lista;
		
	cout<<"Ingrese la placa que desea rastrear: ";
	cin>>placa;
	placa=validarPlaca(placa);
	cout<<"Ingrese la fecha (ano-mes-dia): ";
	cin>>fecha;
	fecha=validarFecha(fecha);
	int i=0;
	while (actual != NULL){    
    	if (actual->placa == placa && actual->fecha==fecha){  //si actual es igual al elemento que estamos buscando entonces entre al condicional y cambie bandera a true
			band = true;
			i++;
			cout<<"\n\tMovimiento "<<i<<": ";
	    	cout <<"\nTipo de movimiento:		" <<actual->movimiento;
			if(actual->movimiento=="Entrada"){
				cout<<"\nEl vehiculo ingreso a las: : 	"<<actual->hora<<":"<<actual->minuto<<":"<<actual->segundo;				
			}
			else{
				cout<<"\nEl vehiculo salio a las: 	"<<actual->hora<<":"<<actual->minuto<<":"<<actual->segundo;				
			}			
			cout<<"\n";    
		}
    	actual = actual->siguiente;
    }    
	//si bandera ha cambiado a true entonces el elemento se encontro
  	if (band == false){				    
      cout << "\nEl vehiculo con placa "<< placa <<" No tiene movimientos. "<<endl;	
    }  	
    system("pause");
}

//hora con mayor entrada vehiculos
void horaComunI(){	
	Nodo *actual=lista;
	int V[12];
	
	for(int i=1; i<=13; i++){
		V[i]=0;
	}
	
	while(actual != NULL){
		if(actual->movimiento=="Entrada"){
			if(actual->hora=="00" || actual->hora=="01"){
				V[1]=V[1]+1;
			}
			else if(actual->hora=="02"||actual->hora=="03"){
				V[2]=V[2]+1;
			}
			else if(actual->hora=="04"||actual->hora=="05"){
				V[3]=V[3]+1;
			}
			else if(actual->hora=="06"||actual->hora=="07"){
				V[4]=V[4]+1;
			}
			else if(actual->hora=="08"||actual->hora=="09"){
				V[5]=V[5]+1;
			}
			else if(actual->hora=="10"||actual->hora=="11"){
				V[6]=V[6]+1;
			}
			else if(actual->hora=="12"||actual->hora=="13"){
				V[7]=V[7]+1;
			}
			else if(actual->hora=="14"||actual->hora=="15"){
				V[8]=V[8]+1;
			}
			else if(actual->hora=="16"||actual->hora=="17"){
				V[9]=V[9]+1;
			}
			else if(actual->hora=="18"||actual->hora=="19"){
				V[10]=V[10]+1;
			}
			else if(actual->hora=="20"||actual->hora=="21"){
				V[11]=V[11]+1;
			}
			else if(actual->hora=="22"||actual->hora=="23"){  
				V[12]=V[12]+1;
			}
		}
		actual=actual->siguiente;
	}
	
	int mayor=V[0];
	int horaMayor=0;
	for(int i=1; i<=13; i++){
		if(V[i]>mayor){
			mayor=V[i];
			horaMayor=i;
		}
	}
	//cout<<"hora que mas se repite "<<mayor<<endl;
	//cout<<"posicion del vector con la hora que mas se repite "<<horaMayor<<endl;
	
	switch(horaMayor){
		case 1: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 00:00 y las 2:00";
				break;
		case 2: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 2:00 y las 4:00";
				break;
		case 3: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 4:00 y las 6:00";
				break;
		case 4: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 6:00 y las 8:00";
				break;
		case 5: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 8:00 y las 10:00";
				break;
		case 6: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 10:00 y las 12:00";
				break;
		case 7: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 12:00 y las 14:00";
				break;
		case 8: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 14:00 y las 16:00";
				break;
		case 9: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 16:00 y las 18:00";
				break;
		case 10: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 18:00 y las 20:00";
				break;
		case 11: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 20:00 y las 22:00";
				break;
		case 12: cout<<"\nLas horas con mayor ingreso de vehiculos son entre las 22:00 y las 00:00";
				break;
		case 0: cout<<"\nNo hay ingreso de vehiculos. ";
				break;
		default: cout<<"\nbasura.";
	}
	cout<<"\n";

}

//hora con mas salidas de vehiculos
void horaComunS(){
	Nodo *actual=lista;
	int V[12];
	for(int i=1; i<=13; i++){
		V[i]=0;
	}
	
	while(actual != NULL){
		if(actual->movimiento=="Salida"){
			if(actual->hora=="00" || actual->hora=="01"){
				V[1]=V[1]+1;
			}
			else if(actual->hora=="02"||actual->hora=="03"){
				V[2]=V[2]+1;
			}
			else if(actual->hora=="04"||actual->hora=="05"){
				V[3]=V[3]+1;
			}
			else if(actual->hora=="06"||actual->hora=="07"){
				V[4]=V[4]+1;
			}
			else if(actual->hora=="08"||actual->hora=="09"){
				V[5]=V[5]+1;
			}
			else if(actual->hora=="10"||actual->hora=="11"){
				V[6]=V[6]+1;
			}
			else if(actual->hora=="12"||actual->hora=="13"){
				V[7]=V[7]+1;
			}
			else if(actual->hora=="14"||actual->hora=="15"){
				V[8]=V[8]+1;
			}
			else if(actual->hora=="16"||actual->hora=="17"){
				V[9]=V[9]+1;
			}
			else if(actual->hora=="18"||actual->hora=="19"){
				V[10]=V[10]+1;
			}
			else if(actual->hora=="20"||actual->hora=="21"){
				V[11]=V[11]+1;
			}
			else if(actual->hora=="22"||actual->hora=="23"){  
				V[12]=V[12]+1;
			}
		}
		actual=actual->siguiente;
	}
	
	int mayor=V[0];
	int horaMayor=0;
	for(int i=0; i<=12; i++){
		if(V[i]>mayor){
			mayor=V[i];
			horaMayor=i;
		}
	}
	//cout<<"hora que mas se repite "<<mayor<<endl;
	//cout<<"posicion del vector con la hora mas repetida "<<horaMayor<<endl;
	
	switch(horaMayor){
		case 1: cout<<"\nLas horas con mayor salida de vehiculos son entre las 00:00 y las 2:00";
				break;
		case 2: cout<<"\nLas horas con mayor salida de vehiculos son entre las 2:00 y las 4:00";
				break;
		case 3: cout<<"\nLas horas con mayor salida de vehiculos son entre las 4:00 y las 6:00";
				break;
		case 4: cout<<"\nLas horas con mayor salida de vehiculos son entre las 6:00 y las 8:00";
				break;
		case 5: cout<<"\nLas horas con mayor salida de vehiculos son entre las 8:00 y las 10:00";
				break;
		case 6: cout<<"\nLas horas con mayor salida de vehiculos son entre las 10:00 y las 12:00";
				break;
		case 7: cout<<"\nLas horas con mayor salida de vehiculos son entre las 12:00 y las 14:00";
				break;
		case 8: cout<<"\nLas horas con mayor salida de vehiculos son entre las 14:00 y las 16:00";
				break;
		case 9: cout<<"\nLas horas con mayor salida de vehiculos son entre las 16:00 y las 18:00";
				break;
		case 10: cout<<"\nLas horas con mayor salida de vehiculos son entre las 18:00 y las 20:00";
				break;
		case 11: cout<<"\nLas horas con mayor salida de vehiculos son entre las 20:00 y las 22:00";
				break;
		case 12: cout<<"\nLas horas con mayor salida de vehiculos son entre las 22:00 y las 00:00";
				break;
		case 0: cout<<"\nNo hay salida de vehiculos. ";
				break;
		default: cout<<"\nInfo basura. ";
				break;
	}
	cout<<"\n\n";	
	system("pause");	
}


