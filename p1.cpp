#include <iostream>
#include <vector>
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
            vector<Alumno> alumnos;
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
    return 0;
}
