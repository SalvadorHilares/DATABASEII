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

istream & operator>> (istream & stream, Alumno & record){
    stream.read(record.codigo, 5);
    stream.read(record.nombre, 11);
    stream.read(record.apellidos, 20);
    stream.read(record.carrera, 15);
    stream.get(); //read \n
    stream.get();
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

            ifstream archivo;
            archivo.open(name, ios::in | ios::app);

            vector<Alumno> alumnos;
            Alumno alumno;
            
            while(archivo){
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
    cout<<alumnos.size()<<endl;
    return 0;
}