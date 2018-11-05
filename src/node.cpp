  #include "node.hpp"

  Node::Node(std::pair<int,int> position, int actualWeight, Node* nodeParent):
        position(position),
        nodeParent(nodeParent),
        data(0),
        weight(actualWeight),
        nodeChilds()
        {
          nodeChilds.reserve(4);
        }

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
  //  std::cout << "I'm the node with PosX: " << position.first << " and PosY " <<  position.second << " and Weight " << weight;
  //  std::cout << " child being push has PosX: " << newNode -> getPosition().first << " PosY: " << newNode -> getPosition().second << " Data: " << newNode -> getData() << "\n";
    nodeChilds.push_back(newNode);
  }

  std::vector<Node*> Node::getChilds(){
    return nodeChilds;
  }

  Node* Node::getParent(){
    return nodeParent;
  }

  std::vector<Node*> Node::getRoute(){

    std::vector<Node*> wayBack;
    Node* nodeAux = nodeParent;

    std::cout << "I'm the node with PosX: " << position.first << " and PosY " <<  position.second << "\n";
    while (nodeAux != NULL){
      std::cout << "X Pos: " << nodeAux -> getPosition().first << " Y Pos: " << nodeAux -> getPosition().second << " Data: " <<nodeAux -> getData() << "\n";
      wayBack.push_back(nodeAux);
      nodeAux = nodeAux -> getParent();
    }

    return wayBack;

  }


  void Node::printDescendents(){

    Node* nodeAux = NULL;

    if (!nodeChilds.empty())
      for (int i = 0; i < nodeChilds.size(); i++){
          printDescendents_(nodeChilds[i]);
      }

  }

  void Node::printDescendents_(Node* nodeAux){

    if (nodeAux != NULL){
      for (int i = 0; i < nodeAux -> getChilds().size(); i++){
        printDescendents_(nodeAux -> getChilds()[i]);
      }
      std::cout << "X Pos: " << nodeAux -> getPosition().first << " Y Pos: " << nodeAux -> getPosition().second << " Data: " <<nodeAux -> getData();
      std::cout << " My Parent is: (" << nodeAux -> getParent() -> getPosition().first << " , "  << nodeAux -> getParent() -> getPosition().second << ") \n";
    }

  }

  int Node::getWeight(){
      return weight;
  }

  void Node::setWeight(int weight){
      this -> weight = weight;
  }

  void Node::printInfo(){

    std::cout << "I'm the node with position ( " << position.first << " , " << position.second << "), data: " << data << " and weight: " << weight << "\n";

  }


  bool Node::operator==(const Node& targetNode){

    if (position.first != targetNode.position.first){
        return false;
    }else if (position.first != targetNode.position.first){
        return false;
    }else if (data != targetNode.data){
        return false;
    }else if (weight != targetNode.weight){
        return false;
    }else return true;


  }
