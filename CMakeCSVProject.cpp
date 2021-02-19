#include "CMakeCSVProject.h"

using namespace std;
void csv_read_row(std::string& line, int num);
void map_parse();
void csv_line_parse(csv_line &csvLine, int num);
string csv_cell_parser(string cell, int num);
void printMap(map<int, csv_line> Map);


map <int, csv_line> map_csv, map_result;

int main(int argc, char* argv[])
{
    string input;
    setlocale(LC_ALL, "Russian");

    if (argc > 1)
    {
        input = argv[1];}
    else
    {
        cout << "Не задан .csv файл!\n";
	cin.get();
	return 0;
    }

    ifstream  data(input);
    if (data.fail()) return (cout << "Ошибка файла!" << endl) && 0;

    std::string line; int num_line = 0;
    while (getline(data, line))
    {
        if (num_line > 0)
            csv_read_row(line, num_line);
        num_line++;
    }
    data.close();
    printMap(map_csv);

    map_parse();
    printMap(map_result);

    cin.get();
return 0;
}

// вывод таблицы в консоль
void printMap(map<int, csv_line> Map) {
    int setw_val = 12;

    std::cout << setw(setw_val) << "\tA" << setw(setw_val) << "B" << setw(setw_val) << "Cell" << "\n";
    for (auto elem : Map)
    {
        std::cout << setw(5) << elem.first << setw(setw_val)
            << elem.second.A << setw(setw_val) << elem.second.B << setw(setw_val) << elem.second.Cell << "\n";
    }
    std::cout << "\n\n";
}

// заполнение начальными значениями ячеек
void csv_read_row(std::string& line, int key) {
    std::vector<std::string> cells = split(line, ",");
    csv_line csvLine = { cells[1], cells[2], cells[3]};

    map_csv.insert(pair<int, csv_line>(std::stoi(cells[0]), csvLine));
    map_result.insert(pair<int, csv_line>(std::stoi(cells[0]), csvLine));
}

// разбор ячеек в результирующей
void map_parse() {
    for (auto elem : map_result)
    {
        csv_line_parse(elem.second, elem.first);
    }
}

// обновление значений в результирующей
void csv_line_parse(csv_line& csvLine, int key) {
    csvLine.A = csv_cell_parser(csvLine.getCols()[0], key);
    csvLine.B = csv_cell_parser(csvLine.getCols()[1], key);
    csvLine.Cell = csv_cell_parser(csvLine.getCols()[2], key);

    map_result.at(key) = csvLine;
}

// рекурсивное вычисление
string getValFromMap(int key, char* cell) {
    if (map_result.find(key) != map_result.end())
    {
        string val = map_result.at(key).getByCell(cell);
        if (isDigit(val))
            return val;
        else {
            return csv_cell_parser(val, key);
        }
    }
    else
        return "N/a";
}

// вычисление значений
string csv_cell_parser(string cell, int key) {
    if (!isDigit(cell))
    {
        if (cell.at(0) == '=') {
            // лист с оперендами
            list<char*> lst;

            char* tab2 = new char[cell.length() + 1];
            strcpy(tab2, cell.c_str());

            char* pch = strtok(tab2, "=-+*/");
            while (pch != NULL)
            {
                lst.push_back(pch);
                pch = strtok(NULL, "=-+*/");
            }

            string new_cell = cell;
            for (const char* cell_num : lst) {
                char* cellRef = strdup(cell_num);
                char* cell_l, * cell_n;

                // вычеслить номер и букву указанной ячейки
                getLetterAndNum(cell_num, cell_l, cell_n);
                //int num = atoi(numchar);

                // получить значение из вычесленной ячейуи
                string val = getValFromMap(atoi(cell_n), cell_l);
                if (val == "N/a")
                    return "N/a";
                string cll; cll.assign(cellRef, strlen(cellRef));

                new_cell.replace(new_cell.find(cll), cll.size(), val);
            }
            new_cell = std::regex_replace(new_cell, std::regex("\\="), "");

            // вычисление арифметической операции
            Expression exp = Expression(); 
            int solve = 0;
            try {
                exp.setExpression(new_cell);
                exp.parse();
                solve = exp.solve();
            }
            catch (exception ex) {

            }
            return std::to_string(solve);;
        }
        else // если нет '='
            return "N/a";
    }
    else // если число
        return cell;
}
