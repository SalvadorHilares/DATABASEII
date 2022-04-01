#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Alumno{
    string Nombre;
    string Apellidos;
    string Carrera;
    float mensualidad = 0.00;

    void imprimir() {
        cout << "Nombre: " << Nombre << "\n";
        cout << "Apellidos: " << Apellidos << "\n";
        cout << "Carrera: " << Carrera << "\n";
        cout << "Mensualidad: " << mensualidad << "\n";
        cout << "\n";
    }

    void asignarValores(string nombre_, string apellidos_, string carrera_,float mensualidad_){
        //Se asignan los datos del alumno
        Nombre = nombre_;
        Apellidos = apellidos_;
        Carrera = carrera_;
        mensualidad = mensualidad_;
    }

};

class VariableRecord{
private:
    string fileName;

public:
    VariableRecord(string nombreArchivo){
        this->fileName = nombreArchivo;
    }

    vector<Alumno> load(){
        vector<Alumno> alumnos;
        int contador = 0;
        //Accediendo al archivo
        ifstream File;
        string registro;
        File.open(fileName, ios::in);
        //Obtenemos cada uno de los registros del archivo
        while (getline(File, registro)) {
            if (contador == 0)
                getline(File,registro);
            Alumno alumno = Alumno();
            //Se asigna cada parte del registro a su correspondiente atributo en alumno
            string space_delimiter = "|";
            vector<string> campos{};

            size_t pos = 0;
            while (((pos = registro.find(space_delimiter)) != string::npos)) {
                campos.push_back(registro.substr(0, pos));
                registro.erase(0, pos + 1);
            }

            alumno.Nombre = campos[0];
            alumno.Apellidos = campos[1];
            alumno.Carrera = campos[2];
            alumno.mensualidad = stof(registro.substr(0,pos));

            //Se añade el alumno al vector
            alumnos.push_back(alumno);
            contador++;
        }
        File.close();
        return alumnos;
    }

    void add(Alumno record){
        string registro;
        //Creamos el registro a agregar
        registro = record.Nombre + '|' + record.Apellidos + '|' + record.Carrera + '|' + to_string(record.mensualidad) + '\n';
        //Abrimos el archivo
        ofstream File;
        File.open(fileName, ofstream::app);
        //Agregamos el registro al archivo
        File<<registro;
        File.close();
    }

    Alumno readRecord(int pos){
        pos += 2;
        //Accedemos al archivo
        ifstream File;
        File.open(fileName);
        string registro;
        //Nos posicionamos en el registro deseado
        while(pos>0){
            getline(File,registro);
            pos--;
        }

        Alumno alumno;
        string space_delimiter = "|";
        vector<string> campos{};

        size_t posicion = 0;
        while (((posicion = registro.find(space_delimiter)) != string::npos)) {
            campos.push_back(registro.substr(0, posicion));
            registro.erase(0, posicion + 1);
        }

        alumno.Nombre = campos[0];
        alumno.Apellidos = campos[1];
        alumno.Carrera = campos[2];
        alumno.mensualidad = stof(registro.substr(0, posicion));

        File.close();
        return alumno;
    }
};

int main(){
    VariableRecord funcionPrincipal = VariableRecord("datos2.txt");

    cout << endl << "-------------------load-----------------" << endl;
    vector<Alumno> alumnos = funcionPrincipal.load();
    cout << "Imprimiendo los registros de los alumnos 1,2,3: " << endl << endl;
    alumnos[0].imprimir();
    alumnos[1].imprimir();
    alumnos[2].imprimir();


    cout << "-------------------add------------------" << endl;
    Alumno alumnoA = Alumno();
    string nombre, apellidos, carrera;
    float mensualidad;
    nombre = "Luis";
    apellidos = "Ango Rivera";
    carrera = "Bioingenieria";
    mensualidad = 2200.00;
    alumnoA.asignarValores(nombre, apellidos, carrera, mensualidad);
    funcionPrincipal.add(alumnoA);
    cout << "Alumno agregado con exito." << endl;


    cout << endl << "----------------readRecord--------------" << endl;
    cout << "Tomando como primer elemento el registro en la posicion 0..." << endl;
    cout << "Imprimiendo el registro del alumno en la posicion 1: " << endl;
    Alumno alumnoB;
    alumnoB = funcionPrincipal.readRecord(1);
    alumnoB.imprimir();

    return 0;
}