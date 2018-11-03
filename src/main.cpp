#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <set>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"
#include "car.hpp"
#include "cScreen.hpp"
#include "initialScreen.hpp"
#include "simulationScreen.hpp"


struct lex_compare{
  bool operator() (const Node* targetNode1, const Node* targetNode2) const{
    return targetNode1 < targetNode2;
  }
};



int main(){



Field testField(100,100,1);
testField.calculateOptimalRoute(std::make_pair(1,1), std::make_pair(0,99));


/*
std::list<Node*> listaDeNodos;
Node nodo1(std::make_pair(1,1),0,NULL);
Node nodo2(std::make_pair(2,2),0,NULL);
Node nodo3(std::make_pair(1,1),0,NULL);
Node nodo4(std::make_pair(2,2),0,NULL);
Node nodo5(std::make_pair(3,3),0,NULL);
Node nodo6(std::make_pair(3,3),0,NULL);
Node nodo7(std::make_pair(1,1),0,NULL);
listaDeNodos.push_back(&nodo1);
listaDeNodos.push_back(&nodo2);
listaDeNodos.push_back(&nodo3);
listaDeNodos.push_back(&nodo4);
listaDeNodos.push_back(&nodo5);
listaDeNodos.push_back(&nodo6);
listaDeNodos.push_back(&nodo7);


for (auto node: listaDeNodos)
    node -> printInfo();


    std::list<Node*>::iterator targetNode = listaDeNodos.begin();

    while (targetNode != listaDeNodos.end()){

    bool coincidences = true;
    while(coincidences){

      coincidences = false;
      std::list<Node*>::iterator it = targetNode;
      it++;


      while (it != listaDeNodos.end()){
        std::cout << "Iterating\n";
        std::cout << "It node = ";
        (*it) -> printInfo();
        std::cout << "Target node = ";
        (*targetNode) -> printInfo();

        if ( nodesAreEqual((*it),(*targetNode)) ){
             std::cout << "Erasing\n";
             listaDeNodos.erase(it);
             coincidences = true;
             break;
        }else it++;
      }

    }
      targetNode++;
  }*/

    /*
    bool coincidences = true;
    //TODO Cada vez que borre que pare.
    while (coincidences){

    coincidences = false;
    std::list<Node*>::iterator it_ = listaDeNodos.begin();
    std::list<Node*>::iterator it = it_;
    it++;

    while (it != listaDeNodos.end()){

      std::cout << "Iterating\n";
      std::cout << "It node = ";
      (*it) -> printInfo();
      std::cout << "It_ node = ";
      (*it_) -> printInfo();

      if ( nodesAreEqual((*it),(*it_)) ){
           std::cout << "Erasing\n";
           listaDeNodos.erase(it);
           coincidences = true;
           break;
      }else it++;
    }
  }*/
/*
std::set<Node*, lex_compare> miSet;
Node nodo1(std::make_pair(1,1), 1, NULL);
nodo1.setData(20);
Node nodo4(std::make_pair(1,1), 1, NULL);
nodo4.setData(4);
Node nodo2(std::make_pair(1,1), 1, NULL);
nodo2.setData(20);
Node nodo3(std::make_pair(1,1), 1, NULL);
nodo3.setData(10);

miSet.insert(miSet.end(), &nodo1);
miSet.insert(miSet.end(), &nodo2);
miSet.insert(miSet.end(), &nodo3);
miSet.insert(miSet.end(), &nodo4);

for (auto node: miSet)
     node -> printInfo();

*/

/*
int posX, posY;
std::cout << "Introduce field X-AXIS dimension: ";
std::cin >> posX;
std::cout << "Y-AXIS dimension: ";
std::cin >> posY;

posX *= 20;
posY *= 20;

ceil(posX);
ceil(posY);

setFieldDimension(posX, posY);


sf::RenderWindow window(sf::VideoMode(posX,posY), "Autonomous Car", sf::Style::Close);

std::vector<cScreen*> Screens;

simulationScreen screen01;
Screens.push_back(&screen01);

int screen = 0;

while (screen != -1){
  screen = Screens[screen] -> Run(window);
}*/



}
