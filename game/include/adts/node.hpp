/*
 * node.hpp
 *
 *  Created on: Sep 13, 2022
 *      Author: jsaavedr
 */

#ifndef GAME_INCLUDE_ADTS_NODE_HPP_
#define GAME_INCLUDE_ADTS_NODE_HPP_
#include "adts/cell2D.hpp"
namespace adts {

class Node {
private:
	Cell2D data;
	Node* ptrNext;
public:
	Node();
	Node(Cell2D _data, Node* next = nullptr);
	void setData(Cell2D _data);
	void setNext(Node* _next);
	Cell2D getData();
	Node* getNext();
	void print();
	virtual ~Node();
};

} /* namespace adts */

#endif /* GAME_INCLUDE_ADTS_NODE_HPP_ */
