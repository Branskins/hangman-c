#ifndef HANGMAN_H
#define HANGMAN_H

#include<vector>
#include<string>
#include<fstream>
#include<ctime>
#include<iostream>
#include<algorithm>

class Hangman {
private:
	std::vector<std::string> palabras;
	std::vector<char> letrasUsadas;
	int intentosPosibles;
	std::string palabraSecreta;
	std::string palabraOculta;
public:
	Hangman();
	~Hangman();
	void empezar();
	void cargarPalabras();
	std::string algoritmoSeleccion();
	// Modifica la palabra oculta
	void actualizarOculta(char letra);
	// Revisa si una letra digitada ya fue utilizada
	bool adivinado(char letra);
	// Revisa si la palabra oculta es igual a la palabra secreta
	bool correcta();
};
#endif // !HANGMAN_H

