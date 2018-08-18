#include"Hangman.h"

Hangman::Hangman() 
{
	cargarPalabras();
	intentosPosibles = 7;
	palabraSecreta = algoritmoSeleccion();
	palabraOculta = std::string(palabraSecreta.size(), '_');
}

Hangman::~Hangman()
{
}

void Hangman::empezar()
{
	int intentos = 0;
	while (!correcta() && intentos < intentosPosibles) {
		encabezado();
		char intentoLetra;
		// std::cout << "La palabra correcta es = " << palabraSecreta << std::endl;
		std::cout << "Ha completado = " << palabraOculta << std::endl;
		std::cout << "Intentos restantes = " << intentosPosibles - intentos << std::endl;
		std::cout << "Digite una letra: ";
		std::cin >> intentoLetra;
		if (adivinado(intentoLetra)) {
			std::cout << "Ya uso la letra " << intentoLetra << std::endl;
			system("pause");
		}
		else {
			letrasUsadas.push_back(intentoLetra);
			if (palabraSecreta.rfind(intentoLetra) != palabraSecreta.npos) { // Encuentra la ultima ocurrencia
				actualizarOculta(intentoLetra); // Actualiza la palabra oculta solamente si acierta
				std::cout << "Buen intento!\n";
				system("pause");
			}
			else {
				std::cout << "Mala suerte, incorrecto\n";
				intentos++; 
				system("pause");
			}
		}
		system("cls");
	}
	std::cout << "PALABRA SECRETA: " << palabraSecreta << std::endl;
	std::cout << ((correcta()) ? "Felicidades!" : "Suerte en la proxima") << std::endl;
	system("pause");
}

void Hangman::cargarPalabras()
{
	std::ifstream flujoEntrada;
	flujoEntrada.open("../palabras.txt", std::ios::in);
	std::string palabra;
	flujoEntrada >> palabra; // Lectura previa
	while (!flujoEntrada.eof()) {
		palabras.push_back(palabra); // Insercion de cada palabra dentro del vector
		flujoEntrada >> palabra;
	}
	flujoEntrada.close();
}

std::string Hangman::algoritmoSeleccion()
{
	std::string palabra; // Palabra que se va a adivinar

	// Extraer los segundos del computador
	time_t fecha = time(&fecha);
	struct tm calendario;
	localtime_s(&calendario, &fecha);
	int segundos = calendario.tm_sec;

	// Iteradores para manipular los datos 
	std::vector<std::string>::iterator iteInicio = palabras.begin();
	std::vector<std::string>::iterator iteFinal = palabras.end();
	int mitad = (iteFinal - iteInicio) / 2;
	std::vector<std::string>::iterator iteMitad = palabras.begin() + mitad;

	// Algoritmo para seleccionar una letra aleatoria
	size_t iteraciones = segundos;
	if (iteraciones > palabras.size()) // Cuidado si los segundos sobrepasan el tamanio del vector
		iteraciones = segundos % palabras.size(); // Unicamente da valores variados si hay menos de 60 palabras
	for (size_t i = 0; i < iteraciones; i++) {
		if (i % 2 == 0) {
			swap(*iteInicio, *iteMitad);
			++iteInicio;
		}
		else {
			--iteFinal; // Apunta al final, entonces hay que disminuirlo primero
			swap(*iteFinal, *iteMitad);
		}
	}

	// La idea es que lo datos de la mitad siempre cambien
	palabra = *iteMitad;

	return palabra;
}

void Hangman::actualizarOculta(char letra)
{
	std::string cortar = palabraSecreta;
	while (cortar.npos != cortar.rfind(letra)) {
		size_t i = cortar.rfind(letra);
		palabraOculta[i] = letra;
		cortar = cortar.substr(0, i);
	}
}

bool Hangman::adivinado(char letra)
{
	std::vector<char>::iterator iterChar;
	for (iterChar = letrasUsadas.begin(); iterChar != letrasUsadas.end(); ++iterChar) {
		if (*iterChar == letra)
			return true;
	}
	return false;
}

bool Hangman::correcta()
{
	return palabraOculta == palabraSecreta;
}

void Hangman::encabezado()
{
	std::cout << "+--------------------------------------------------------+\n";
	std::cout << "|" << std::setw(34) << ">>AHORCADO<<" << std::setw(24) << "|\n";
	std::cout << "+--------------------------------------------------------+\n";
}
