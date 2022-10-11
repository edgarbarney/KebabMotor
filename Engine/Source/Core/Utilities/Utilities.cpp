// FranticDreamer 2022
// Utilities

#include <iomanip>
#include <sstream>

#include "Utilities.hpp"

namespace KebabMotor::Utilities
{
	namespace Strings
	{ 
		std::string AddLeadingZeroes(int value, int digits)
		{
			std::ostringstream ss;
			ss << std::setw(digits) << std::setfill('0') << value;
			return ss.str();
		}
	}
	
	namespace Maths
	{
		template <class T>
		ENG_DLLEXP T RandomIntInRange(T max, T min)
		{
			std::random_device rd;
			std::default_random_engine gen(rd()); // seed
			std::uniform_int_distribution<T> range(min, max);
			return range(gen);
		}
		template short				ENG_DLLEXP RandomIntInRange <short>(short max, short min);
		template int				ENG_DLLEXP RandomIntInRange <int>(int max, int min);
		template unsigned int		ENG_DLLEXP RandomIntInRange <unsigned int>(unsigned int max, unsigned int min);
		template long				ENG_DLLEXP RandomIntInRange <long>(long max, long min);
		template unsigned long		ENG_DLLEXP RandomIntInRange <unsigned long>(unsigned long max, unsigned long min);
		template long long			ENG_DLLEXP RandomIntInRange <long long>(long long max, long long min);
		template unsigned long long	ENG_DLLEXP RandomIntInRange <unsigned long long>(unsigned long long max, unsigned long long min);
		template unsigned short		ENG_DLLEXP RandomIntInRange <unsigned short>(unsigned short max, unsigned short min);

		template <class T>
		ENG_DLLEXP T RandomFloatInRange(T max, T min)
		{
			std::random_device rd;
			std::default_random_engine gen(rd()); // seed
			std::uniform_real_distribution<T> range(min, max);
			return range(gen);
		}
		template float				ENG_DLLEXP RandomFloatInRange <float>(float max, float min);
		template double				ENG_DLLEXP RandomFloatInRange <double>(double max, double min);
		template long double		ENG_DLLEXP RandomFloatInRange <long double>(long double max, long double min);

		template <class T>
		ENG_DLLEXP T Factorial(T num)
		{
			T fact = 1;

			for (num; num >= 2; num--)
			{
				fact = fact * num;
			}

			return fact;
		}
		template short				ENG_DLLEXP Factorial <short>(short num);
		template int				ENG_DLLEXP Factorial <int>(int num);
		template unsigned int		ENG_DLLEXP Factorial <unsigned int>(unsigned int num);
		template long				ENG_DLLEXP Factorial <long>(long num);
		template unsigned long		ENG_DLLEXP Factorial <unsigned long>(unsigned long num);
		template long long			ENG_DLLEXP Factorial <long long>(long long num);
		template unsigned long long	ENG_DLLEXP Factorial <unsigned long long>(unsigned long long num);
		template unsigned short		ENG_DLLEXP Factorial <unsigned short>(unsigned short num);
	};
}