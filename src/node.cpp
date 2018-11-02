#include "node.hpp"

Node::Node(std::pair<int,int> position, Node* nodeParent):
      position(position),
      nodeParent(nodeParent),
      nodeChilds()
      {}

std::pair<int,int> Node::getPosition(){
    return position;
}

int Node::getData(){
  return data;
}

void Node::setPosition(std::pair<int,int> position){
  this -> position = position;
}

void Node::setData(int data){
  this -> data = data;
}


void Node::setChild(Node* newNode){
  nodeChilds.push_back(newNode);
}

std::vector<Node*> Node::getChilds(){
  return nodeChilds;
}

Node* Node::getParent(){
  return nodeParent;
}


void Node::printDescendents(){

  Node* nodeAux = NULL;

  if (!nodeChilds.empty()){
    for (int i = 0; i < nodeChilds.size(); i++){
      std::cout << "Pos X: " << nodeChilds[i] -> getPosition().first << " Pos Y: " << nodeChilds[i] -> getPosition().second << " Data: " << nodeChilds[i] -> getData() << "\n";
    }
  }

  std::cout << "Pos X: " << nodeChilds[0] -> getPosition().first << " Pos Y: " << nodeChilds[0] -> getPosition().second << " Data: " << nodeChilds[0] -> getData() << "\n";



  //nodeAux = nodeChilds[0];

  /*
  if (nodeAux != NULL)
  printDescendents_(nodeAux);*/


}

void Node::printDescendents_(Node* nodeAux){

  while (nodeAux != NULL){
    for (int i = 0; i < nodeAux -> getChilds().size(); i++){
      printDescendents_(nodeAux -> getChilds()[i]);
    }
    std::cout << "X Pos: " << nodeAux -> getPosition().first << " Y Pos: " << nodeAux -> getPosition().second << " Data: " <<nodeAux -> getData() << "\n";
  }

}
