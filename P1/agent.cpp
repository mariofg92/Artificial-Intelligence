#include "agent.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

// -----------------------------------------------------------
void Agent::inicializarMatriz(){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
                mundo_[i][j]=0;
        }
    }
}
void Agent::Mapea(){
    if(bump_){
        switch(miOrientacion){
        case 0: mundo_[(posicion.y+9)%10][posicion.x] = -1; // +9 = -1 mod 10
            break;
        case 1: mundo_[posicion.y][(posicion.x+1)%10] = -1;
            break;
        case 2: mundo_[(posicion.y+1)%10][posicion.x] = -1;
            break;
        case 3: mundo_[posicion.y][(posicion.x+9)%10] = -1;
            break;}
    }
    else{
        if (accionAnterior==actFORWARD && !bump_){
            switch(miOrientacion){
            case 0: posicion.y = (posicion.y+9)%10;
                break;
            case 1: posicion.x = (posicion.x+1)%10;
                break;
            case 2: posicion.y = (posicion.y+1)%10;
                break;
            case 3: posicion.x = (posicion.x+9)%10;
                break;
            }
        }
        mundo_[posicion.y][posicion.x] = tiempo_transcurrido;
    }
}

Agent::ActionType Agent::Gira(char s){
    if (s=='d'){
        switch(miOrientacion){
            case 0: miOrientacion = Este;
                break;
            case 1: miOrientacion = Sur;
                break;
            case 2: miOrientacion = Oeste;
                break;
            case 3: miOrientacion = Norte;
                break;
            }
        return actTURN_R;
    }else{
        if (s=='i'){
            switch(miOrientacion){
                case 0: miOrientacion = Oeste;
                    break;
                case 1: miOrientacion = Norte;
                    break;
                case 2: miOrientacion = Este;
                    break;
                case 3: miOrientacion = Sur;
                    break;
                }
            return actTURN_L;
        }else{
            cout << "Ha introducido una posición de giro incorrecta";
            return actIDLE;
        }
    }
}


int Agent::GetTiempoTranscurrido(char ori){
    int a_devolver = -3; //Si no introducimos el parámetro adecuado devolverá -3

    switch(miOrientacion){
    case 0:
        if(ori=='e')
            a_devolver = mundo_[(posicion.y+9)%10][posicion.x];
        if(ori=='i')
            a_devolver = mundo_[posicion.y][(posicion.x+9)%10];
        if(ori=='d')
            a_devolver = mundo_[posicion.y][(posicion.x+1)%10];
        break;

    case 1:
        if(ori=='e')
            a_devolver = mundo_[posicion.y][(posicion.x+1)%10];
        if(ori=='i')
            a_devolver = mundo_[(posicion.y+9)%10][posicion.x];
        if(ori=='d')
            a_devolver = mundo_[(posicion.y+1)%10][posicion.x];
        break;

    case 2:
        if(ori=='e')
            a_devolver = mundo_[(posicion.y+1)%10][posicion.x];
        if(ori=='i')
            a_devolver = mundo_[posicion.y][(posicion.x+1)%10];
        if(ori=='d')
            a_devolver = mundo_[posicion.y][(posicion.x+9)%10];
        break;

    case 3:
        if(ori=='e')
            a_devolver = mundo_[posicion.y][(posicion.x+9)%10];
        if(ori=='i')
            a_devolver = mundo_[(posicion.y+1)%10][posicion.x];
        if(ori=='d')
            a_devolver = mundo_[(posicion.y+9)%10][posicion.x];
        break;
    }

    return a_devolver;
}
bool Agent::puedoAvanzar(char ori){
    if (GetTiempoTranscurrido(ori) != -1)
        return true;
    else
        return false;
}

int Agent::GetPosMasLongeba(){
    int a_devolver = -6; //Valor a devolver en caso de error

    if (puedoAvanzar('i')){
        if(puedoAvanzar('d')){
            if(GetTiempoTranscurrido('i') < GetTiempoTranscurrido('d')){
                if(puedoAvanzar('e')){
                    if(GetTiempoTranscurrido('i') < GetTiempoTranscurrido('e')){
                        a_devolver = 0;
                    }else{
                            a_devolver = 1;
                    }
                }else{
                    a_devolver = 0;
                }
            }else{
                if (puedoAvanzar('e')){
                    if(GetTiempoTranscurrido('e') < GetTiempoTranscurrido('d')){
                        a_devolver = 1;
                    }else{
                        a_devolver = 2;
                    }
                }else{
                    a_devolver = 2;
                }
            }
        }else{
            if(puedoAvanzar('e')){
                if(GetTiempoTranscurrido('i') < GetTiempoTranscurrido('e')){
                    a_devolver = 0;
                }else{
                    a_devolver = 1;
                }
            }else{
                a_devolver = 0;
            }
        }
    }else{
        if(puedoAvanzar('d')){
            if(puedoAvanzar('e')){
                if(GetTiempoTranscurrido('d') < GetTiempoTranscurrido('e')){
                    a_devolver = 2;
                }else{
                    a_devolver = 1;
                }
            }else{
                a_devolver = 2;
            }
        }else{
            if(puedoAvanzar('e')){
                a_devolver = 1;
            }else{
                a_devolver = 5; //Sólo puede venir por donde ha venido
            }
        }
    }

    return a_devolver;
}

Agent::ActionType Agent::girarAMenosBarrida(){
    int caso = GetPosMasLongeba();

    switch(caso){
        case 0: return Gira('i');
            break;
        case 1: return actFORWARD;
            break;
        case 2: return Gira('d');
            break;
        case 5: return Gira('i');
            break;
        default: return Gira('i'); //Nunca debería entrar en este caso
            break;

    }
}

Agent::ActionType Agent::Think()
{

    Mapea();


    if (dirty_){
        accionAnterior = actSUCK;
    }else{
        if ((accionAnterior == actTURN_L || accionAnterior == actTURN_R) && puedoAvanzar('e')){
            accionAnterior = actFORWARD;
        }else{
            accionAnterior = girarAMenosBarrida();

        }
    }

    tiempo_transcurrido++;

	return accionAnterior;

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	bump_ = env.isJustBump();
	dirty_ = env.isCurrentPosDirty();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actSUCK: return "SUCK";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}



