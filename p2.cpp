#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

class Alumno//Record
{	
private:
    char codigo[5];    
	char nombre[11];    
	char apellidos[20];	
    char carrera[20];

    char ciclo[2];
    char mensualidad[10];
    
    int NextDel = 0;
public:

    void setData(){
        cout<<"Codigo: ";
        readFromConsole(codigo,6);
        cout<<"Nombre: ";
        readFromConsole(nombre,12);
        cout<<"Apellidos: ";
        readFromConsole(apellidos,21);
        cout<<"Carrera: ";
        readFromConsole(carrera,21);
        cout<<"Ciclo: ";
        readFromConsole(ciclo,3);
        cout<<"Mensualidad: ";
        readFromConsole(mensualidad,11);
    }    
    void showData(){
        cout<<nombre<<" - "<<apellidos<<" - "<<carrera<<" - "<<ciclo<<" - "<<" - "<<mensualidad<<endl;
    }

    void setNextDel(int nextD){
        NextDel = nextD;
    }

    int getCiclo(){
        return int(ciclo);
    }

    float getMensualidad(){
        return stof(mensualidad);
    }

    int getNextDel(){
        return NextDel;
    }

    void readFromConsole(char buffer[], int size){
	    string temp;			
	    cin >> temp;
	    for(int i=0; i<size; i++)		
		    buffer[i] = (i < temp.size())? temp[i] : ' ';
	    buffer[size-1] = '\0';
	    cin.clear();
    }
};


class FixedRecordFile
{
private:
    string file_name;
    int head;
public:
    FixedRecordFile(string file_name){
        this->file_name = file_name;
        head = -1;
        ofstream file(this->file_name, ios::app | ios::binary);
        file.write((char*)&head,sizeof(int));        
    } 

    void writeRecord(Alumno record){ // ADD
        ofstream file(this->file_name, ios::app | ios::binary);
        if(!file.is_open()) throw ("No se pudo abrir el archivo");
        file.write((char*) &record, sizeof(Alumno)-sizeof(int));//guardar en formato binario
        char next = '0';
        file.write((char*)&next,sizeof(char));
        file << '\n';
        file << flush;
        file.close();
    }  

    void writeRecord(Alumno record, int pos){
        ofstream file(this->file_name, ios::app | ios::binary);
        if(!file.is_open()) throw ("No se pudo abrir el archivo");

        file.seekp(pos * sizeof(Alumno), ios::beg);//fixed length record
        file.write((char*) &record, sizeof(Alumno));
        file.close();
    } 

    vector<Alumno> scanAll(){ // LOAD
        ifstream file(this->file_name, ios::binary);
        if(!file.is_open()) throw ("No se pudo abrir el archivo");
        
        vector<Alumno> alumnos;
        Alumno record; 

        while(!file.eof()){
            record = Alumno();               
            file.read((char*) &record, sizeof(Alumno));
            alumnos.push_back(record);    
        }
        file.close();

        return alumnos;
    } 

    Alumno readRecord(int pos){ // READ RECORD
        ifstream file(this->file_name, ios::binary);
        if(!file.is_open()) throw ("No se pudo abrir el archivo");

        Alumno record;
        file.seekg(pos * sizeof(Alumno), ios::beg);//fixed length record
        file.read((char*) &record, sizeof(Alumno));
        file.close();
        return record;
    }

    int num_records(){ // SIZE
        ifstream file(this->file_name, ios::binary);
        if(!file.is_open()) throw ("No se pudo abrir el archivo");
        
        file.seekg(0, ios::end);//ubicar cursos al final del archivo
        long size = file.tellg();//cantidad de bytes del archivo        
        file.close();
        return size / sizeof(Alumno);
    }

    bool Delete(int pos){
        //OBTENER EL REGISTRO DEL DATO A ELIMINAR
        
        Alumno record = readRecord(pos);

        //SETEAMOS VALORES DEL NEXTDEAL

        if(record.getNextDel() == -1 || num_records()/pos==0) return false;

        if(head == -1){
            head = pos;
            record.setNextDel(-1);
        }else{
            int temp = head;
            head = pos;
            record.setNextDel(temp);
        }
        writeRecord(record,pos);
        return true;
    }
};

int main()
{
    FixedRecordFile* file = new FixedRecordFile("datos.txt");
    Alumno* record = new Alumno();
    record->setData();
    file->writeRecord(*record);
    return 0;
}