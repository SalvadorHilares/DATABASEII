#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Alumno {
    char codigo[5];
    char nombre[11];
    char apellidos[20];
    char carrera[15];
};

istream &operator>>(istream &stream, Alumno &p) {
    stream.read(p.codigo, 5);
    stream.read(p.nombre, 11);
    stream.read(p.apellidos, 20);
    stream.read(p.carrera, 15);
    stream.get(); // read \n
    stream.get(); // read \r
    return stream;
}

ostream &operator<<(ostream &stream, Alumno &p) {
    stream.write(p.codigo, 5);
    stream.write(p.nombre, 11);
    stream.write(p.apellidos, 20);
    stream.write(p.carrera, 15);
    stream << "\n";
    stream << flush;
    return stream;
}


Alumno initRecord() {
    // TODO: crear alumno desde teclado
    Alumno alumno;
    string codigo, nombre, apellido, carrera;
    cin >> codigo >> nombre>>apellido>>carrera;
    for (int i = 0; i < 5; i++) {
        if(i<codigo.size())
            alumno.codigo[i] = codigo[i];
        else
            alumno.codigo[i] = ' ';
    }
    for (int i = 0; i < 11; i++) {
        if(i<nombre.size())
            alumno.nombre[i] = nombre[i];
        else
            alumno.nombre[i] = ' ';
    }
    for (int i = 0; i < 20; i++) {
        if(i<apellido.size())
            alumno.apellidos[i] = apellido[i];
        else
            alumno.apellidos[i] = ' ';;
    }
    for (int i = 0; i < 15; i++) {
        if(i<carrera.size())
            alumno.carrera[i] = carrera[i];
        else
            alumno.carrera[i] = ' ';
    }
    return alumno;
}

class FixedRecord {
private:
    string name;

public:
    FixedRecord(string name) { this->name = name; }

    vector<Alumno> load() {
        ifstream archivo;
        archivo.open(this->name);

        vector<Alumno> alumnos;

        Alumno alumno;
        while (!archivo.eof()) {
            archivo >> alumno;
            alumnos.push_back(alumno);
        }
        archivo.close();
        return alumnos;
    }

    void add(Alumno record) {
        ofstream outfile;
        outfile.open(this->name, ios::app);
        outfile << record;
        outfile.close();
    }

    Alumno readRecord(int pos) {
        Alumno alumno;
        return alumno;
    }
};

void print(vector<Alumno> alumnos) {
    string codigoA = "", nombreA = "", apellidoA = "", carreraA = "", vacio = "";
    for (int i = 0; i < alumnos.size(); i++) {
        cout << "ALUMNO NUMERO " << i + 1 << endl;
        cout << "-------------------------\n\n";
        for (int j = 0; j < 5; j++) {
            codigoA = codigoA + alumnos[i].codigo[j];
        }
        for (int z = 0; z < 11; z++) {
            nombreA = nombreA + alumnos[i].nombre[z];
        }
        for (int k = 0; k < 20; k++) {
            apellidoA = apellidoA + alumnos[i].apellidos[k];
        }
        for (int x = 0; x < 15; x++) {
            carreraA = carreraA + alumnos[i].carrera[x];
        }
        cout << "Codigo: " << codigoA << endl;
        cout << "Nombre: " << nombreA << endl;
        cout << "Apellidos: " << apellidoA << endl;
        cout << "Carrera: " << carreraA << endl;

        cout << endl;
        codigoA = vacio;
        nombreA = vacio;
        apellidoA = vacio;
        carreraA = vacio;
    }
}

int main() {
    class FixedRecord record("datos1.txt");
    vector<Alumno> alumnos = record.load();
    print(alumnos);
    cout<<"ingrese un nuevo alumno:"<<endl;
    Alumno Record = initRecord();
    record.add(Record);
    alumnos = record.load();
    print(alumnos);
    return 0;
}