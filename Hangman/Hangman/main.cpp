#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<ctime>

void cargaPalabras(std::vector<std::string> &palabras);
int algoritmoSeleccion(int cantidadPalabras);
std::string ocultaPalabra(int cantidad, std::string caracter);
std::string metodoMiedo(std::string cortada, std::string palabra, std::string letra);
bool adivinado(std::string letra, std::vector<std::string> &letrasAsertadas);

int main() {

	std::vector<std::string> palabras; // Crea un vector vacio llamada palabras
	std::vector<std::string> letrasAsertadas;

	cargaPalabras(palabras); // Llena el vector con palabras

	int indice = algoritmoSeleccion(palabras.size());
	int intentos = 0;
	int intentosPosibles = 7;
	std::string palabraSecreta = palabras[indice];
	std::string palabraOculta = ocultaPalabra(palabraSecreta.length(), "_");

	while (palabraOculta != palabraSecreta && intentos < intentosPosibles) {
		std::string intentoLetra = "";
		std::cout << "La palabra correcta es = " << palabraSecreta << std::endl;
		std::cout << "Ha completado = " << palabraOculta << std::endl;
		std::cout << "Intentos restantes = " << intentosPosibles - intentos << std::endl;
		std::cout << "Digite una letra: ";
		std::cin >> intentoLetra;
		if (adivinado(intentoLetra, letrasAsertadas))
			std::cout << "Ya encontro la letra " << intentoLetra;
		else {
			letrasAsertadas.push_back(intentoLetra);
			if (!(palabraSecreta.rfind(intentoLetra) == intentoLetra.npos)) {
				palabraOculta = metodoMiedo(palabraOculta, palabraSecreta, intentoLetra);
				std::cout << "Buen intento!";
			}
			else {
				std::cout << "Mala suerte, incorrecto";
				intentos++;
			}
		}
		system("cls");
	}

	std::cin.get();
		
	return 0;
}

// Lectura de todas las palabras desde un archivo .txt
void cargaPalabras(std::vector<std::string> &palabras)
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

// Crea un flujo stringstream para almacenar todas la palabras
std::string ocultaPalabra(std::vector<std::string>& palabras)
{
	std::stringstream s;
	std::vector<std::string>::iterator iterPalabra;
	for (iterPalabra = palabras.begin(); iterPalabra != palabras.end(); ++iterPalabra)
		s << *iterPalabra << std::endl;
	return s.str();
}

// Algoritmo temporal no valido para generar un numero aleatorio
int algoritmoSeleccion(int cantidadPalabras)
{
	srand(static_cast<unsigned int>(time(nullptr)));  // Semilla para números pseudo-aleatorios
	return rand() % cantidadPalabras;
}

// Oculta la palabra con caracteres
std::string ocultaPalabra(int cantidad, std::string caracter)
{
	std::string oculta = "";
	for (int i = 0; i < cantidad; i++)
		oculta += caracter;
	return oculta;
}

// Imprime n veces un caracter escogido
std::string imprimeRepetida(int cantidad, std::string caracter)
{
	std::string linea = "";
	for (int i = 0; i < cantidad; i++)
		linea += caracter;
	return linea;
}

// Algoritmo para modificar la palabra con la letras asertadas 
std::string metodoMiedo(std::string cortada, std::string palabra, std::string letra)
{
	if (cortada.length() == 0)
		return "";
	else if (palabra.rfind(letra) == letra.npos)
		return cortada;
	else {
		int i = palabra.rfind(letra);
		return metodoMiedo(cortada.substr(0, i), palabra.substr(0, i), letra) + (letra + cortada.substr(i + 1, cortada.length()));
	}
}

// Revisa si una letra digitada ya fue asertada correctamente
bool adivinado(std::string letra, std::vector<std::string>& letrasAsertadas)
{
	std::vector<std::string>::iterator iterLetras;
	for (iterLetras = letrasAsertadas.begin(); iterLetras != letrasAsertadas.end(); ++iterLetras) {
		if (*iterLetras == letra)
			return true;
	}
	return false;
}

