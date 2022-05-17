#include <iostream>
#include <fstream>
#include <string>

struct action {
	bool final_condition;
	bool change;
	bool move_left;
	bool move_right;
	int next_condition;
	action() {
		final_condition = 1;
	}
};
struct condition {
	int number_of_condition;
	action one;
	action zero;
};

class TuringMachine {
	condition* conditions;
	int lenght_tape;
	bool* tape;
	unsigned long long number_of_takt;
	int quantity_of_condition;
	char** plenty_of_condition;
	int out_position;
	bool error;
	bool aplicate;
public:
	int table(char* str, int str_len, char** array, int len_array) {
		if (len_array == 0)
			return 0;
		for (int i = 0; i < len_array; ++i) {
			bool flag_equal = 1;
			for (int j = 0; j < strlen(str); ++j) {
				if (array[i][j] != str[j])
					flag_equal = 0;
			}
			if (flag_equal)
				return i + 1;
		}
		return 0;
	}
	int table(const std::string str, char** array, int len_array) {
		if (len_array == 0)
			return 0;
		for (int i = 0; i < len_array; ++i) {
			bool flag_equal = 1;
			for (int j = 0; j < str.length(); ++j) {
				if (array[i][j] != str[j])
					flag_equal = 0;
			}
			if (flag_equal)
				return i + 1;
		}
		return 0;
	}
	TuringMachine(const char* input_file, const char* condition_file) {
		std::ifstream infile(input_file);
		int i = 0;
		infile >> lenght_tape;
		infile >> number_of_takt;
		char tape_mal_char[100];
		infile >> tape_mal_char;
		bool* tape_mal_bool = new bool[strlen(tape_mal_char)];
		for (int i = 0; i < strlen(tape_mal_char); ++i)
			tape_mal_bool[i] = (int)tape_mal_char[i] - 48;
		lenght_tape *= strlen(tape_mal_char);
		tape = new bool[lenght_tape];
		for (int i = 0; i < lenght_tape; ++i) {
			tape[i] = tape_mal_bool[i % strlen(tape_mal_char)];
			std::cout << tape[i];
		}
		std::cout << std::endl;
		infile.close();

		std::ifstream infile2(condition_file);
		plenty_of_condition = new char* [20];
		for (int i = 0; i < 20; ++i)
			plenty_of_condition[i] = new char[10];
		int index_conditions = 0;
		char bin1[10], tek_sost_tranzit[10], next_sost_tranzit[10];
		while (!infile2.eof()) {
			infile2 >> tek_sost_tranzit;
			char *tek_sost = tek_sost_tranzit;
			infile2 >> bin1;
			infile2 >> bin1;
			infile2 >> next_sost_tranzit;
			char* next_sost = next_sost_tranzit;
			infile2 >> bin1;
			infile2 >> bin1;
			if (table(tek_sost, plenty_of_condition, index_conditions)==0) {
				for(int i = 0; i < strlen(tek_sost);++i)
					plenty_of_condition[index_conditions][i] = tek_sost[i];
				++index_conditions;
			}
			if (table(next_sost, plenty_of_condition, index_conditions)==0) {
				for (int i = 0; i < strlen(next_sost); ++i)
					plenty_of_condition[index_conditions][i] = next_sost[i];
				++index_conditions;
			}
		}
		quantity_of_condition = index_conditions;
		infile2.close();

		std::ifstream infile3(condition_file);
		conditions = new condition[quantity_of_condition];
		char tek_sost[7], tek_znak[3], bin2[7], next_sost[7], next_znachenie[3], move[3];
		while (!infile3.eof()) {
			infile3 >> tek_sost;
			if (error == 0) {
				if (tek_sost[0] != 'q')
					error = 1;
				for (int i = 1; i < strlen(tek_sost); ++i) {
					if ((tek_sost[i] > '9') || (tek_sost[i] < '0')) {
						error = 1;
						break;
					}
				}
			}
			infile3 >> tek_znak;
			if ((tek_znak[0] != '0')&&(tek_znak[0] != '1'))
				error = 1;
			infile3 >> bin2;
			infile3 >> next_sost;
			if (error == 0) {
				if (next_sost[0] != 'q')
					error = 1;
				for (int i = 1; i < strlen(next_sost); ++i) {
					if ((next_sost[i] > '9') || (next_sost[i] < '0')) {
						error = 1;
						break;
					}
				}
			}
			infile3 >> next_znachenie;
			if ((next_znachenie[0] != '0') && (next_znachenie[0] != '1'))
				error = 1;
			infile3 >> move;
			if ((move[0] != 'R') && (move[0] != 'L') && (move[0] != 'N'))
				error = 1;
			int index = table(tek_sost, plenty_of_condition, quantity_of_condition)-1;
			conditions[index].number_of_condition = index;
			if (tek_znak[0] == '1') {
				conditions[index].one.final_condition = 0;
				conditions[index].one.next_condition = table(next_sost, plenty_of_condition, quantity_of_condition)-1;
				conditions[index].one.change = (int)next_znachenie[0] - 48;
				if (move[0] == 'L') {
					conditions[index].one.move_right = 0;
					conditions[index].one.move_left = 1;
				}
				else if (move[0] == 'R') {
					conditions[index].one.move_right = 1;
					conditions[index].one.move_left = 0;
				}
				else if (move[0] == 'N') {
					conditions[index].one.move_right = 0;
					conditions[index].one.move_left = 0;
				}
				std::cout << conditions[index].number_of_condition << ' ' << 1 << " -> " << conditions[index].one.next_condition << ' ' << conditions[index].one.change << ' ' << conditions[index].one.move_left << conditions[index].one.move_right << std::endl;
			}
			else if (tek_znak[0] == '0') {
				conditions[index].zero.final_condition = 0;
				conditions[index].zero.next_condition = table(next_sost, plenty_of_condition, quantity_of_condition)-1;
				conditions[index].zero.change = (int)next_znachenie[0] - 48;
				if (move[0] == 'L') {
					conditions[index].zero.move_left = 1;
					conditions[index].zero.move_right = 0;
				}
				else if (move[0] == 'R') {
					conditions[index].zero.move_left = 0;
					conditions[index].zero.move_right = 1;
				}
				else if (move[0] == 'N') {
					conditions[index].zero.move_right = 0;
					conditions[index].zero.move_left = 0;
				}
				std::cout << conditions[index].number_of_condition << ' ' << 0 << " -> " << conditions[index].zero.next_condition << ' ' << conditions[index].zero.change << ' ' << conditions[index].zero.move_left << conditions[index].zero.move_right << std::endl;
			}
		}
		infile3.close();

		std::ifstream infile4(input_file);
		char ch;
		while ((ch = infile4.get()) != EOF) {
			if ((ch > '9') || (ch < '0')) {
				error = 1;
				break;
			}
		}
		infile4.close();


	}
	TuringMachine(const TuringMachine& machine) {
		lenght_tape = machine.lenght_tape;
		tape = new bool[lenght_tape];
		for (int i = 0; i < lenght_tape; ++i)
			tape[i] = machine.tape[i];
		number_of_takt = machine.number_of_takt;
		quantity_of_condition = machine.quantity_of_condition;

		plenty_of_condition = new char* [quantity_of_condition];
		for (int i = 0; i < quantity_of_condition; ++i) {
			plenty_of_condition[i] = new char[strlen(machine.plenty_of_condition[i])];
		}
		for (int i = 0; i < quantity_of_condition; ++i) {
			for (int j = 0; j < strlen(machine.plenty_of_condition[i]); ++j)
				plenty_of_condition[i][j] = machine.plenty_of_condition[i][j];
		}
		conditions = new condition[machine.quantity_of_condition];
		for (int i = 0; i < quantity_of_condition; ++i) {
			conditions[i].number_of_condition = machine.conditions[i].number_of_condition;

			conditions[i].one.change = machine.conditions[i].one.change;
			conditions[i].one.final_condition = machine.conditions[i].one.final_condition;
			conditions[i].one.move_left = machine.conditions[i].one.move_left;
			conditions[i].one.move_right = machine.conditions[i].one.move_right;
			conditions[i].one.next_condition = machine.conditions[i].one.next_condition;

			conditions[i].zero.change = machine.conditions[i].zero.change;
			conditions[i].zero.final_condition = machine.conditions[i].zero.final_condition;
			conditions[i].zero.move_left = machine.conditions[i].zero.move_left;
			conditions[i].zero.move_right = machine.conditions[i].zero.move_right;
			conditions[i].zero.next_condition = machine.conditions[i].zero.next_condition;
		}
		error = machine.error;
		aplicate = machine.aplicate;
	}
	TuringMachine& operator=(TuringMachine& right) {
		if (conditions != nullptr)
			delete[] conditions;
		if (tape != nullptr)
			delete[] tape;
		for (int i = 0; i < quantity_of_condition; ++i)
			if (plenty_of_condition[i] != nullptr)
				delete[] plenty_of_condition[i];
		if (plenty_of_condition != nullptr)
			delete[] plenty_of_condition;

		lenght_tape = right.lenght_tape;
		bool* tape = new bool[lenght_tape];
		for (int i = 0; i < lenght_tape; ++i)
			tape[i] = right.tape[i];
		number_of_takt = right.number_of_takt;
		quantity_of_condition = right.quantity_of_condition;

		plenty_of_condition = new char* [quantity_of_condition];
		for (int i = 0; i < quantity_of_condition; ++i)
			plenty_of_condition[i] = new char[strlen(right.plenty_of_condition[i])];

		for (int i = 0; i < quantity_of_condition; ++i) {
			for (int j = 0; j < strlen(plenty_of_condition[i]); ++j)
				plenty_of_condition[i][j] = right.plenty_of_condition[i][j];
		}

		conditions = new condition[quantity_of_condition];
		for (int i = 0; i < quantity_of_condition; ++i) {
			conditions[i].number_of_condition = right.conditions[i].number_of_condition;

			conditions[i].one.change = right.conditions[i].one.change;
			conditions[i].one.final_condition = right.conditions[i].one.final_condition;
			conditions[i].one.move_left = right.conditions[i].one.move_left;
			conditions[i].one.move_right = right.conditions[i].one.move_right;
			conditions[i].one.move_right = right.conditions[i].one.next_condition;

			conditions[i].zero.change = right.conditions[i].zero.change;
			conditions[i].zero.final_condition = right.conditions[i].zero.final_condition;
			conditions[i].zero.move_left = right.conditions[i].zero.move_left;
			conditions[i].zero.move_right = right.conditions[i].zero.move_right;
			conditions[i].zero.move_right = right.conditions[i].zero.next_condition;
		}
	}
	std::string calc(std::string const& init, int maxsteps) {
		int tek_sost = table(init, plenty_of_condition, quantity_of_condition)-1, tek_pos = lenght_tape-1, quantity_of_takt = 0;
		while (quantity_of_takt+1 <= maxsteps) {
			if (quantity_of_takt > maxsteps) {
				aplicate = 1;
				break;
			}
			if (tape[tek_pos] == 0) {
				if (conditions[tek_sost].zero.final_condition) {
					out_position = tek_pos;
					break;
				}
				tape[tek_pos] = conditions[tek_sost].zero.change;
				if ((conditions[tek_sost].zero.move_left == 1) && (conditions[tek_sost].zero.move_right == 0)) {
					if (tek_pos == 0)
						tek_pos = lenght_tape - 1;
					else
						--tek_pos;
				}
				else if ((conditions[tek_sost].zero.move_left == 0) && (conditions[tek_sost].zero.move_right == 1))
					++tek_pos;
				tek_sost = conditions[tek_sost].zero.next_condition;
				++quantity_of_takt;
			}
			else if (tape[tek_pos] == 1) {
				if (conditions[tek_sost].one.final_condition) {
					out_position = tek_pos;
					break;
				}
				tape[tek_pos] = conditions[tek_sost].one.change;
				if ((conditions[tek_sost].one.move_left == 1) && (conditions[tek_sost].one.move_right == 0)) {
					if (tek_pos == 0)
						tek_pos = lenght_tape - 1;
					else
						--tek_pos;
				}
				else if ((conditions[tek_sost].one.move_left == 0) && (conditions[tek_sost].one.move_right == 1))
					++tek_pos;
				tek_sost = conditions[tek_sost].one.next_condition;
				++quantity_of_takt;
			}
		}
		std::string result(lenght_tape, '0');
		for (int i = 0; i < lenght_tape; ++i)
			result[i] = (char)(tape[i] + 48);
		return result;
	}
	~TuringMachine() {
		if (conditions != nullptr)
			delete[] conditions;
		if (tape != nullptr)
			delete[] tape;
		for (int i = 0; i < quantity_of_condition; ++i)
			if (plenty_of_condition[i] != nullptr)
				delete[] plenty_of_condition[i];
		if (plenty_of_condition != nullptr)
			delete[] plenty_of_condition;
	}
	const char* Get_First_condition() {
		return this->plenty_of_condition[0];
	}
	int Get_number_of_takt() {
		return this->number_of_takt;
	}
	int Get_length_tape() { return lenght_tape;}
	int Get_out_position() { return out_position;}
	bool Get_aplicate() { return aplicate;}
	bool Get_error() { return error; }
};

int main(int argc, char* argv[]) {
	TuringMachine m(argv[1], argv[2]), m1 = m;
	std::string result = new char[m1.Get_length_tape()];
	std::ofstream outfile(argv[3]);
	if (m1.Get_error() == 1)
		outfile << "Error";
	else {
		result = m1.calc(m1.Get_First_condition(), m1.Get_number_of_takt());
		if (m1.Get_aplicate() == 1)
			outfile << "Not applicable";
		else {
			for (int i = m1.Get_out_position(); i < m1.Get_length_tape(); ++i)
				outfile << result[i];
		}
	}
	outfile.close();
}