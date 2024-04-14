#include <bitset>
#include <vector>
#include <iostream>

using namespace std;

void flip_bits(void* ptr, const size_t n, const vector<size_t>& pos)
{

    char* u = (char*)ptr;
    for (size_t i : pos)
    {
        if (i >= 8 * n) {
            cerr << "Oshibka: pozitsiya bita vne diapazona\n";
            return;
        }

        size_t bytei = i / 8;
        size_t biti = i % 8;
        u[bytei] ^= 1 << (7 - biti);
    }
}

int main()
{
    size_t nb;
    cout << "Vvedite kolichestvo bait: ";
    cin >> nb;

    char* memory = new char[nb];
    cout << "Vvedite " << nb << " baiti soderzhimovo v pamyati (any char): ";
    for (size_t i = 0; i < nb; ++i) {
        cin >> memory[i];
    }

    size_t np;
    cout << "Vvedite kolichestvo bitovykh pozitsiy dlya perevorota: ";
    cin >> np;

    vector<size_t> positions;
    cout << "Vvedite " << np << " bitoviye pozitsii (0-" << (8 * nb - 1) << "): ";
    for (size_t i = 0; i < np; ++i) {
        size_t pos;
        cin >> pos;
        positions.push_back(pos);
    }

    flip_bits(memory, nb, positions);

    cout << "Soderzhimoye pamyati posle perevorota vybrannykh bitov:\n";
    for (size_t i = 0; i < nb; ++i) {
        cout << memory[i] << " ";
    }
    cout << endl;

    delete[] memory;

    return 0;
}
