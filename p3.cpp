#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>

using namespace std;

//Escribe
void writeString(fstream& stream, string str) {
    long unsigned int length = str.size();
    stream.write(str.c_str(), length);
}

//Lee
string readString(fstream& stream) {
    string result = "";
    char word;

    while(stream.read((char*)& word, sizeof(char)) && word != '|' && word != '\n') {
        result += word;
    }

    result += '\0';
    return result;
}

//Struct Alumno
struct Alumno
{
    string Nombre;
    string Apellidos;
    string Carrera;
    float mensualidad;

    Alumno() = default;

    Alumno(string Nombre, string Apellidos, string Carrera, float mensualidad)
    {
        this->Nombre = Nombre;
        this->Apellidos = Apellidos;
        this->Carrera = Carrera;
        this->mensualidad = mensualidad;    
    }

    //Escribe
    void write(fstream& stream)
    {
        char separador = '|';

        stream.write((char*)& mensualidad, sizeof(mensualidad));
        stream.write((char*)& separador, sizeof(char));

        writeString(stream, Nombre);
        stream.write((char*)& separador, sizeof(char));
        writeString(stream, Apellidos);
        stream.write((char*)& separador, sizeof(char));
        writeString(stream, Carrera);

        separador = '\n';
        stream.write((char*)& separador, sizeof(char));

    }
    //Cuando se lee
    bool read(fstream& stream) 
    {
        char separador;
        stream.read((char*)& mensualidad, sizeof(float));
        stream.read((char*)& separador, sizeof(char));

        if(stream.fail()) 
        {
            return false;
        }

        Nombre = readString(stream);
        Apellidos = readString(stream);
        Carrera = readString(stream);

        return true;
    }
    //Imprime
    void print() 
    {
        cout << "Nombre: " << Nombre << endl;
        cout << "Apellidos: " << Apellidos << endl;
        cout << "Carrera: " << Carrera << endl;
        cout << "Mensualidad: " << mensualidad << endl;
    }
};

class VariableRecord
{
    string nombreArchivo;
    string nombreIndice;
public:
    VariableRecord(string nombreArchivo)
    {
        //Guarda con .txt
        this->nombreArchivo =nombreArchivo +".txt";
        this->nombreIndice = nombreArchivo + "_index.txt";
        //Cierra
        ofstream(this->nombreArchivo);
        ofstream(this->nombreIndice);
    }
    //Leer todo los registros del archivo
    vector<Alumno> load()
    {
        vector<Alumno> alumnosArchivos;
        fstream archivos;

        archivos.open(this->nombreArchivo, ios::binary | ios::in);

        Alumno alumno;
        if(archivos.is_open())
        {
            while(alumno.read(archivos))
            {
                alumnosArchivos.push_back(alumno);
            }
            archivos.close();
        } else
        {
            cout  << "No se puede abrir el archivo" << endl;
        }
        return alumnosArchivos;
    }

    void add(Alumno record)
    {
        fstream archivos;
        fstream archivosIndex;
        archivos.open(this->nombreArchivo, ios::binary | ios::in | ios::out);
        if(archivos.is_open())
        {
            archivos.seekg(0, ios::end);
            long unsigned int length = archivos.tellg();
            record.write(archivos);
            archivos.close();
            archivosIndex.open(this->nombreIndice, ios::binary | ios::in | ios::out);
            if(archivosIndex.is_open())
            {
                archivosIndex.seekg(0, ios::end);
                archivosIndex.write((char*)& length, sizeof(length));
                archivosIndex.close();
            } else
            {
                cout << "No se puede abrir el archivo" << this->nombreIndice << endl;
            }
        }else 
        {
            cout << "No se puede abrir el archivo" << this->nombreArchivo << endl;
        }
    }

    Alumno readRecord(int pos)
    {
        Alumno alumno;
        fstream archivos;
        fstream archivosIndex;

        archivosIndex.open(this->nombreIndice, ios::binary | ios::in);

        if(archivosIndex.is_open())
        {
            archivosIndex.seekg((pos -1) * sizeof(long unsigned int));
            long unsigned int posicion;
            archivosIndex.read((char*)& posicion, sizeof(posicion));
            archivosIndex.close();

            archivos.open(this->nombreArchivo, ios::binary | ios::in);
            if(archivos.is_open())
            {
                archivos.seekg(posicion);
                char separador;
                archivos.read((char*)& alumno.mensualidad, sizeof(float));
                archivos.read((char*)& separador, sizeof(char));

                alumno.Nombre = readString(archivos);
                alumno.Apellidos = readString(archivos);
                alumno.Carrera = readString(archivos);
            } else
            {
                cout << "No se puede abrir el archivo" << endl;
            }
        } else 
        {
            cout << "No se puede abrir el archivo" << endl;
        }
        return alumno;
    }
};

int main(int argc, char const *argv[])
{
    VariableRecord test("test");
    Alumno alumno1("Jean Paul", "Melendez Cabezas", "CS", 523.2);
    Alumno alumno2("Carlos", "Merma Silva", "Administracion", 654.3);

    test.add(alumno1);
    test.add(alumno2);

    auto x1 = test.readRecord(1);
    x1.print();
    auto x2 = test.readRecord(2);
    x2.print();

    auto total = test.load();
    for(auto t: total)
    {
        t.print();
        cout << endl;
    }
    return 0;
}
