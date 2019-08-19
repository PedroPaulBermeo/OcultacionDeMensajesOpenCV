
#include <cstdlib>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

//Se incluye el paquete para poder usar una lista
#include <list>	
#include <cmath>

using namespace std;
using namespace cv;

int main(int argc, char* args[]) {

	Mat image = imread("Imagen-1.png");
	Mat gris;
	Mat gris2;
	Mat gris3;
	Mat image4;

	bool conversion = true;
	list <int> binario;
	int residuo = 0;

	cvtColor(image, gris, COLOR_BGR2GRAY);
	Mat image3;
	gris.copyTo(image3);

	//Vec3b bgrPixel = foo.at<Vec3b>(i, j);

	imshow("i1", image);
	
	//DECLARO LOS VALORES EN BINARIO PARA CADA LETRA DE LA PALABRA HOLA

	//H => 37 => 00100101
	//O => 38 => 00100110
	//L => 39 => 00100111
	//A => 40 => 00101000

	list<int>h({0,0,1,0,0,1,0,1});
	//h.reverse();
	list <int> o({0,0,1,0,0,1,1,0});
	//o.reverse();
	list <int> l({0,0,1,0,0,1,1,1});
	//l.reverse();
	list <int> a({0,0,1,0,1,0,0,0});
	//a.reverse();

	int pixel = 0;
	int* histo = new int[256];
	for (int i = 0; i < 256; i++)
		histo[i] = 0;

	int letras = 0;
	int contadorPosLetras = 0;
	int numeroPosicion = 0;

	int numero = 0;
	int temporal = 0;
	int contador = 0;
	
	for (int i = 0; i < gris.rows; i++) {
		for (int j = 0; j < gris.cols; j++) {
			binario.clear();
			pixel = (int)gris.at<uchar>(i, j);
			//cout << pixel << endl;
			histo[pixel]++;
		
			if (letras < 4) {
				while (pixel > 0) {
					residuo = pixel % 2;
					pixel = (int)pixel / 2;
					binario.push_front((residuo));
				}


				binario.pop_back();

				if(letras == 0){
					list<int>::iterator num = next(h.begin(), contadorPosLetras);
					binario.push_back(*num);
				}
				if (letras == 1) {
					list<int>::iterator num = next(o.begin(), contadorPosLetras);
					binario.push_back(*num);
				}
				if (letras == 2) {
					list<int>::iterator num = next(l.begin(), contadorPosLetras);
					binario.push_back(*num);

				}
				if (letras == 3) {
					list<int>::iterator num = next(a.begin(), contadorPosLetras);
					binario.push_back(*num);

				}
				contadorPosLetras++;
				if(contadorPosLetras > 7){
					letras++;
					contadorPosLetras = 0;
				}
			
				contador = 0;
				numero = 0;
				binario.reverse();
				for (list<int>::iterator it = binario.begin(); it != binario.end(); ++it) {
					//cout << ' ' << *it;	
					temporal = (*it) * pow(2, contador);
					numero += temporal;
					contador++;
				}
				cout << "Va a grabar" << numero << endl;
				image3.at<uchar>(i, j) =  numero;
			}
		}
	}
	cout << "pixel"<<pixel << endl;
	cout << "entero"<<numero << endl;
	cout << pixel << endl;
	for (auto v : binario) {
		cout << v << "\n";
	}
	binario.reverse();
	for (auto v : binario) {
		cout <<"reversa"<< v << "\n";
	}


	imshow("gris", gris);
	imshow("gris2", image3);
	imwrite("mensaje.png", image3);
	int cf = 0;
	cout << "gtis" << endl;
	for (int i = 0; i < gris.rows; i++) {
		for (int j = 0; j < gris.cols; j++) {
			//binario.clear();
			if(cf<33){
			pixel = (int)gris.at<uchar>(i, j);
			cout << pixel << endl;
			cf++;
			}
		}
	}
	cf = 0;
	cout << "mensaje" << endl;
	for (int i = 0; i < image3.rows; i++) {
		for (int j = 0; j < image3.cols; j++) {
			//binario.clear();
			if(cf<33){
			pixel = (int)image3.at<uchar>(i, j);
			cout << pixel << endl;
			cf++;
			}
		}
	}


	//Obtengo el mensaje

	list <int> caracterMensaje;
	list <int> caracteresMensaje;

	for (int i = 0; i < image3.rows; i++) {
		for (int j = 0; j < image3.cols; j++) {
			caracterMensaje.clear();
			pixel = (int)image3.at<uchar>(i, j);
			//cout << pixel << endl;
			while (pixel > 0) {
				residuo = pixel % 2;
				pixel = (int)pixel / 2;
				caracterMensaje.push_front((residuo));
			}
			/*
			for (list<int>::iterator it = caracterMensaje.begin(); it != caracterMensaje.end(); ++it) {
				cout << "convirtio" << endl;
				cout << *it << endl;
			}
			cout << " extrajo para mandar al ultimo " << caracterMensaje.back() << endl;*/
			caracteresMensaje.push_back(caracterMensaje.back());
			
		}
	}

	caracterMensaje.clear();

	list <String> palabra;

	contador = 0;
	
	for (list<int>::iterator it = caracteresMensaje.begin(); it != caracteresMensaje.end(); ++it) {
		
	
		if(caracterMensaje.size() <8){
			//cout << " extrajo modificada " << *it << endl;
			caracterMensaje.push_back(*it);
		}
		else {
			/*if(contador <5){
			cout << "Va a comparar" << endl;

			for (list<int>::iterator it = caracterMensaje.begin(); it != caracterMensaje.end(); ++it) {
				cout << ' ' << *it;

			}
			}*/
			if (caracterMensaje == a) {
				palabra.push_back("A");
			}
			else if (caracterMensaje == h) {
				palabra.push_back("H");
			}
			else if (caracterMensaje == l) {
				palabra.push_back("L");
			}
			else if (caracterMensaje == o) {
				palabra.push_back("O");
			}
			caracterMensaje.clear();
			caracterMensaje.push_back(*it);
			contador++;
		}
		
	}
	cout << "Palabra Encontrada" << endl;
	//cout << "Palabra Encontrada 2" << palabra.back();
	
	for (list<String>::iterator it = palabra.begin(); it != palabra.end(); ++it) {
		cout << ' ' << *it;	

	}

	/*int mayor = 0;
		int indice = 0;
		for (int i = 0; i < 256; i++) {
			if (mayor < int(histo[i])) {
				indice = i;
				mayor = int(histo[i]);
			}
			cout << histo[i] << "|";
		}
		cout << endl;
		cout << "mayor" << mayor << "|";
		cout << "indice" << indice << "|";
		cout << endl;*/
		//imshow("Imagen4", image4);
		/*
		cout << image2.rows << endl;
		cout << image2.cols << endl;
		cout << image3.rows << endl;
		cout << image3.cols << endl;
		cvtColor(image3, gris3, COLOR_BGR2GRAY);

		cvtColor(image2, gris2, COLOR_BGR2GRAY);

		imshow("corta 1", gris3);
		imshow("corta 2", gris2);
		image4 =gris3-gris2;

		imshow("cortado2", image4);
		*/

	waitKey(0);
	return 0;
}

void encriptar(void) /* Función donde se ejecuta la lógica del programa */
{
	printf("Hola Mundo\n"); /* imprime la cadena */
	return; /* sale de la función */


}

void desencriptar(void) /* Función donde se ejecuta la lógica del programa */
{
	printf("Hola Mundo\n"); /* imprime la cadena */
	return; /* sale de la función */
}