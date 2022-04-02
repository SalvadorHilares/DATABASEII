#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <utility>
#include <iostream>
#include <cassert>

using namespace std;

struct Matricula {
    string _codigo{};
    int _ciclo{};
    float _mensualidad{};
    string _observaciones{};

    Matricula() = default;

    Matricula(string codigo, int ciclo, float mensualidad, string observaciones) : _codigo(move(codigo)),
                                                                                             _ciclo(ciclo),
                                                                                             _mensualidad(mensualidad),
                                                                                             _observaciones(
                                                                                                     move(
                                                                                                             observaciones)) {}
};

struct MetaDataMatricula {
    int _pos{};
    int _size{};
};

class VariableRecordBin {
    string _filename{};
    string _metafilename{};

public:
    VariableRecordBin(string filename);

    vector<Matricula> load();

    void add(Matricula record);

    Matricula readRecord(int pos);
};

VariableRecordBin::VariableRecordBin(string filename) : _filename(move(filename)) {
    size_t indexDot = _filename.find_last_of(".");
    _metafilename = _filename.substr(0, indexDot) + ".meta.bin";

    ofstream metafile(_metafilename, ios::binary);
    metafile.close();

    ofstream file(_filename, ios::binary);
    file.close();
}

vector<Matricula> VariableRecordBin::load() {
    ifstream metafile(_metafilename, ios::binary | ios::ate);
    int size = metafile.tellg(), nRecords = size / sizeof(MetaDataMatricula);
    metafile.seekg(0, ios::beg);
    vector<MetaDataMatricula> metaRecord(nRecords);
    for (int i = 0; i < nRecords; ++i)
        metafile.read(reinterpret_cast<char *>(&metaRecord[i]), sizeof(MetaDataMatricula));
    metafile.close();

    ifstream file(_filename, ios::binary);
    vector<Matricula> result(nRecords);
    for (int i = 0; i < nRecords; ++i) {
        file.seekg(metaRecord[i]._pos, ios::beg);
        file.read(reinterpret_cast<char *>(&result[i]), metaRecord[i]._size);
    }
    file.close();

    return result;
}

void VariableRecordBin::add(Matricula record) {
    ofstream file(_filename, ios::binary | ios::ate);
    int pos = file.tellp();
    file.write(reinterpret_cast<char *>(&record), sizeof(record));
    file.close();

    ofstream metafile(_metafilename, ios::binary | ios::app);
    MetaDataMatricula metaDataMatricula = {pos, (int) sizeof(record)};
    metafile.write(reinterpret_cast<char *> (&metaDataMatricula), sizeof(metaDataMatricula));
    metafile.close();
}

Matricula VariableRecordBin::readRecord(int pos) {
    ifstream metafile(_metafilename, ios::binary);
    metafile.seekg(pos * sizeof(MetaDataMatricula), ios::beg);
    MetaDataMatricula metadata{};
    metafile.read(reinterpret_cast<char *>(&metadata), sizeof(metadata));
    metafile.close();

    ifstream file(_filename, ios::binary);
    file.seekg(metadata._pos, ios::beg);
    Matricula matricula{};
    file.read(reinterpret_cast<char *>(&matricula), metadata._size);
    file.close();

    return matricula;
}

int main() {

    cout << "=== P4 ===\n";

    VariableRecordBin vrb01("datos2.txt");

    Matricula matricula01("000", 3, 100.2, "No pago");
    vrb01.add(matricula01);

    auto record = vrb01.readRecord(0);

    assert(record._observaciones == matricula01._observaciones);

    cout << "Todo se ejecuto correctamente\n";
    return 0;
}
