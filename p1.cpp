#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Alumno{
    char codigo [5];
    char nombre [11];
    char apellidos [20];
    char carrera [15];
};

istream & operator >> (istream & stream, Alumno & p){	
	stream.read(p.codigo, 5);		
	stream.read(p.nombre, 11);		
	stream.read(p.apellidos, 20);		
	stream.read(p.carrera, 15);
  stream.get(); // read \n	
  stream.get(); // read \r
	return stream;
}

class FixedRecord{
    private:
        string name;
    public:
        FixedRecord(string name){
            this->name = name;
        }
        vector<Alumno> load(){
            //TODO: INGRESAR CODIGO
            ifstream archivo;
            archivo.open(name);
          
            vector<Alumno> alumnos;
            
            Alumno alumno;
            while(!archivo.eof()){
              archivo >> alumno;
              alumnos.push_back(alumno);
            }
            archivo.close();
            return alumnos;      
        }
        void add(Alumno record){

        }
        Alumno readRecord(int pos){
            Alumno alumno;
            return alumno;
        }
};

int main(){
    class FixedRecord record("datos1.txt");
    vector<Alumno> alumnos = record.load();
    string codigoA = "", nombreA = "", apellidoA = "", carreraA = "", vacio = "";
    for(int i=0; i<alumnos.size(); i++){
      cout<<"ALUMNO NUMERO "<<i+1<<endl;
      cout<<"-------------------------\n\n";
      for(int j=0; j<5; j++){
        codigoA = codigoA + alumnos[i].codigo[j];
      }
      for(int z=0; z<11; z++){
        nombreA = nombreA + alumnos[i].nombre[z];
      }
      for(int k=0; k<20; k++){
        apellidoA = apellidoA + alumnos[i].apellidos[k];
      }
      for(int x=0; x<15; x++){
        carreraA = carreraA + alumnos[i].carrera[x];
      }
      cout<<"Codigo: "<<codigoA<<endl;
      cout<<"Nombre: "<<nombreA<<endl;
      cout<<"Apellidos: "<<apellidoA<<endl;
      cout<<"Carrera: "<<carreraA<<endl;

      cout<<endl;
      codigoA = vacio;
      nombreA = vacio;
      apellidoA = vacio;
      carreraA = vacio;
    }
    return 0;
}