#include <iostream>
#include <bitset>
#include <string>

template <int size> 
class Booth
{
private:
	std::bitset <size> A, M, Q;
	bool binary_convert(int in_num, std::bitset <size> &binary)
	{
		std::string temp_str;
		bool negative{ false };
		int temp_num{ in_num };

		if (in_num < 0)
		{
			in_num = in_num * -1;
			negative = true;
		}
			

		do
		{
			temp_num = in_num % 2;
			in_num = in_num / 2;
			temp_str += static_cast<char> (temp_num + 48);
		} while (in_num > 0);

		if (temp_str.length() <= size)
		{
			for (int index = 0; index < temp_str.length(); index++)
			{
				binary[index] = static_cast<int> (temp_str[index] - 48);
			}

			if (negative)
				binary = two_complement(binary);
			return true;
		}
		else
		{
			std::cout << "La longitud de la palabra de bits, es mucha para la capacidad actual , ingrese una nueva.\n";
			return false;
		}
	}
	void move_right(std::bitset <size>& in1, std::bitset <size>& in2, int &in_q_1)
	{
		int temp{ in1[0] };
		for (int index = 0; index < size - 1; index++)
			in1[index] = in1[index + 1];
		for (int index = 0; index < size - 1; index++)
		{
			if(index == 0)
				in_q_1 = in2[0];
			in2[index] = in2[index + 1];
		}	
		in2[size - 1] = temp;
		
	}
	std::bitset <size> two_complement(std::bitset <size> original)
	{
		std::bitset <size> temp, temp_adder;
		temp_adder[0] = 1;
		for (int index = 0; index < size; index++)
			temp[index] = original[index] ^ 1;
		
		return adder(temp, temp_adder);
	}
	std::bitset <size> adder(std::bitset<size> in1, std::bitset<size> in2)
	{
		int carry{ 0 };
		std::bitset <size> temp, carry_test;
		for (int index = 0; index < size; index++)
		{
			temp[index] = (in1[index] ^ in2[index]) ^ carry;
			carry = (in1[index] & (in2[index] | carry)) | (in2[index] & carry);
		}
		return temp;
	}
	std::bitset <2 * size> algorithm()
	{
		std::bitset <2 * size> temp;
		int q{Q[0]}, q_1{0};
		std::cout << "Base: " << A << " - " << Q << " - " << q << q_1 << "\n";
		for (int index = 0; index < size; index++)
		{
			if ((q == 0) && (q_1 == 1))
				A = adder(A, M);
			else if ((q == 1) && (q_1 == 0))
				A = adder(A, two_complement(M));
			move_right(A, Q, q_1);
			q = Q[0];

			std::cout << index << " - " << A << " - " << Q << "   -   " << q << q_1 << "\n";
		}

		for (int index = 0; index < size; index++)
		{
			temp[index + size] = A[index];
			temp[index] = Q[index];
		}
		return temp;
	}
public:
	Booth() :
		A(), M(), Q()
	{}

	void print()
	{
		std::cout << "-------------------------\n";
		std::cout << "A: " << A << "\n";
		std::cout << "M: " << M << "\n";
		std::cout << "Q: " << Q << "\n";
	}
	void menu()
	{
		int input{ -1 };
		char input_char{ '\0'};
		bool active{ true };
		do
		{
			std::cout << "Ingrese el primer factor: ";
			std::cin >> input;
			if (!binary_convert(input, M))
				continue;
			std::cout << "Ingrese el segundo factor: ";
			std::cin >> input;
			if (!binary_convert(input, Q))
				continue;
			
			print();
			std::cout << "Multiplicacion: " << algorithm() << "\n";

			std::cout << "Desea continuar? 0(no), cualquier otra cosa(si): ";
			std::cin >> input_char;
			switch (input_char)
			{
			case '0':
				active = false;
				break;
			default:
				A.reset();
				M.reset();
				Q.reset();
				break;
			}
		} while (active);
	}
};

int main()
{
	Booth<8> test;
	test.menu();
}