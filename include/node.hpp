#pragma once
#include <iostream>
#include <vector>

class Node{

    private:

      std::pair<int,int> position;
      int                data;
      Node*              nodeParent;
      std::vector<Node*> nodeChilds;


      public:

      Node(std::pair<int,int> position, Node* nodeParent);
      int getData();
      std::pair<int,int> getPosition();
      void setPosition(std::pair<int,int> position);
      void setData(int data);

      void setChild(Node* newNode);
      std::vector<Node*> getChilds();

      Node* getParent();
      void printDescendents();
      void printDescendents_(Node* nodeAux);



};
