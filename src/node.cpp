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
  std::cout << "I'm the node with PosX: " << position.first << " and PosY " <<  position.second;
  std::cout << " child being push has PosX: " << newNode -> getPosition().first << " PosY: " << newNode -> getPosition().second << " Data: " << newNode -> getData() << "\n";
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

  std::vector<Node*> nodeChilds_ = nodeChilds[3] -> getChilds();

  if (!nodeChilds_.empty()){
    for (int i = 0; i < nodeChilds_.size(); i++){
      std::cout << "Pos X: " << nodeChilds_[i] -> getPosition().first << " Pos Y: " << nodeChilds_[i] -> getPosition().second << " Data: " << nodeChilds_[i] -> getData() << "\n";
    }
  }else std::cout << "Empty childs" << "\n";


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
