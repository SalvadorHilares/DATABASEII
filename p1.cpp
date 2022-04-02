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


void readFromConsole(char buffer[], int size){
	    string temp;			
	    cin >> temp;
	    for(int i=0; i<size; i++)		
		    buffer[i] = (i < temp.size())? temp[i] : ' ';
	    buffer[size-1] = '\0';
	    cin.clear();
    }


Alumno initRecord() {
    // TODO: crear alumno desde teclado
    Alumno alumno;
    string agregado;
    readFromConsole(alumno.codigo,6);
    readFromConsole(alumno.nombre,12);
    readFromConsole(alumno.apellidos,21);
    readFromConsole(alumno.carrera,16);
    return alumno;
  }



class FixedRecord {
private:
    string name;
    vector<Alumno> alumnos;
public:
  FixedRecord(string name) { this->name = name; }

  vector<Alumno> load() {
    ifstream archivo;
    archivo.open(this->name);

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
    alumnos.push_back(record);
  }

  Alumno readRecord(int pos) {
    return alumnos[pos];
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
  FixedRecord* record = new FixedRecord("datos1.txt");
  vector<Alumno> alumnos = record->load();
  print(alumnos);
  Alumno Record = initRecord();
  record->add(Record);
  print(alumnos);
  return 0;
}