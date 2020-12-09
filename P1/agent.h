#ifndef AGENT__
#define AGENT__

#include <string>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
struct punto{
        int x;
        int y;
    };
enum orientacion{
        Norte = 0,
        Este = 1,
        Sur = 2,
        Oeste = 3
    };


class Agent
{
public:
	Agent():bump_(false), dirty_(false), tiempo_transcurrido(0){
	miOrientacion=Norte;
	posicion.x=5;
	posicion.y=5;
	inicializarMatriz();
	accionAnterior = actIDLE;
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actSUCK,
	    actIDLE
	};

	void Perceive(const Environment &env);
	ActionType Think();
	void inicializarMatriz();
	void Mapea();
	ActionType Gira(char s);

	int GetTiempoTranscurrido(char ori); // Devuelve el número de veces que la aspiradora ha pasado por una casilla. Devuelve -1 si hay un muro.
	//param: e --> enfrente, i--> izquierda, d--> derecha.

	bool puedoAvanzar(char ori); //param: e --> enfrente, i--> izquierda, d--> derecha.

	int GetPosMasLongeba(); //Devuelve--> 0: la de la izquierda, 1: la de enfrente 2: la de la derecha 3:derecha o izquierda 4: cualquiera de las 3

	ActionType girarAMenosBarrida(); // Devuelve un giro en concreto de forma que queda enfrente de la casilla menos barrida:
	//la de la derecha o la de la izquierda. Si la menos barrida es la de enfrente devuelve avanzar

private:
	bool bump_, dirty_;
	int mundo_[10][10];
	orientacion miOrientacion;
    punto posicion;
    ActionType accionAnterior;
    int tiempo_transcurrido;
};

string ActionStr(Agent::ActionType);

#endif
