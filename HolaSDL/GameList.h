/**
 * Lista de objetos con eliminaci�n eficiente.
 *
 * @file gameList.h
 * @author Rub�n Rubio
 * @date TPV1 2023
 */

#ifndef GAME_LIST_H
#define GAME_LIST_H

#include <cassert>
#include <vector>

 /**
  * Lista de objetos que guardan una referencia opaca a su posici�n en la lista
  * para borrarse eficientemente. Los m�todos de inserci�n de la lista fijan esa
  * referencia, para lo que la clase @c T debe proporcionar un m�todo
  * @c setListAnchor que reciba un objeto de tipo @c GameList::anchor.
  *
  * @tparam T Tipo de los objetos almacenados (sin puntero, aunque los objetos
  * se almacenan como punteros).
  * @tparam owns Si la lista es propietaria de los objetos y se encarga de liberarlos
  * cuando se eliminan.
  */
template<typename T, bool owns = false>
class GameList
{
	/// Nodo de la lista doblemente enlazada
	struct Node
	{
		Node* prev, * next;
		T* elem;     ///< Elemento
		bool active; ///< Si est� activo o ha sido eliminado

		Node(T* elem, Node* base)
			: elem(elem)
			, active(true)
		{
			linkAfter(base);
		}

		Node()
			: prev(this)
			, next(this)
			, elem(nullptr)
			, active(true)
		{
		}

		~Node()
		{
			// if constexpr es un if que se eval�a en tiempo de compilaci�n
			// (si la instancia de la plantilla es propietaria de sus objetos
			// el programa compilado incluir� la eliminaci�n de estos)
			if constexpr (owns) {
				delete elem;
			}
		}

		/// Desconecta el nodo de la lista
		void unlink()
		{
			prev->next = next;
			next->prev = prev;
		}

		/// Conecta el nodo tras el nodo dado
		void linkAfter(Node* node)
		{
			next = node->next;
			prev = node;
			node->next->prev = this;
			node->next = this;
		}
	};

	// La palabra clave mutable aplicada a un atributo indica que este se puede
	// modificar incluso en funciones constantes. En esta clase todos los
	// atributos son mutables porque la estructura interna de la lista se modifica
	// en las operaciones de lectura (i.e. con los iteradores), pero no as�
	// su contenido abstracto (es decir, desde que erase elimina un objeto este
	// deja de estar disponible, pero su eliminaci�n se realiza cuando no haya
	// ning�n iterador apuntando a la lista).

	/// Nodo fantasma que da acceso a la lista
	mutable Node ghostNode;
	/// Lista de elementos pendientes de ser eliminados definitivamente
	mutable std::vector<Node*> toBeRemoved;
	/// Numero de iteradores activos sobre la estructura
	mutable int numIterators;

	/// N�mero de elementos en la lista
	std::size_t elemCount;

	/// Elimina de la lista definitiva los objetos pendientes de ser eliminados
	void removePending() const
	{
		for (Node* anchor : toBeRemoved) {
			anchor->unlink();
			delete anchor;
		}
		toBeRemoved.clear();
	}

	Node* nextActive(Node* node) const
	{
		// Conf�a en que el nodo fantasma es activo
		while (!node->active)
			node = node->next;
		return node;
	}

	Node* prevActive(Node* node) const
	{
		// Conf�a en que el nodo fantasma es activo
		while (!node->active)
			node = node->prev;
		return node;
	}

public:
	/// La referencia que permite borrar elementos de la lista
	using anchor = Node*;

	/// Crea una lista inicialmente vac�a
	GameList()
		: numIterators(0)
		, elemCount(0)
	{
	}

	/// Destruye todos los objetos de la lista si era propietaria de ellos
	~GameList() { clear(); }

	/// N�mero de elementos en la lista
	std::size_t size() const { return elemCount; }

	/// �La lista es vac�a?
	bool empty() const { return elemCount == 0; }

	/// Impide copiar la lista (los objetos tienen referencias a ella)
	GameList(const GameList& other) = delete;

	/// A�ade un nuevo objeto al principio de la lista y fija su iterador
	void push_front(T* value)
	{
		// Comprobamos en depuraci�n que no se insertan valores nulos
		assert(value != nullptr);

		Node* node = new Node(value, &ghostNode);
		value->setListAnchor(node);
		++elemCount;
	}

	/// A�ade un nuevo objeto al final de la lista y fija su iterador
	void push_back(T* value)
	{
		// Comprobamos en depuraci�n que no se insertan valores nulos
		assert(value != nullptr);

		Node* node = new Node(value, ghostNode.prev);
		value->setListAnchor(node);
		++elemCount;
	}

	/// Vac�a la lista y destruye todos sus objetos si era propietaria de ellos
	void clear()
	{
		Node* node = ghostNode.next;

		// Elimina los nodos y la lista de borrados pendientes
		while (node != &ghostNode) {
			Node* current = node;
			node = node->next;
			delete current;
		}

		// Recupera el nodo fantasma
		ghostNode.prev = &ghostNode;
		ghostNode.next = &ghostNode;

		// El tama�o es cero
		elemCount = 0;

		toBeRemoved.clear();
	}

	/// Borra un elemento de la lista a partir de su iterador.
	void erase(anchor it)
	{
		// Si no hay iteraciones activas, borra el nodo directamente
		if (numIterators == 0) {
			it->unlink();
			delete it;
		}
		// Si hay iteraciones activas, lo marca como borrado y lo apunta
		else {
			it->active = false;
			toBeRemoved.push_back(it);
		}

		// Reduce el n�mero de elementos
		--elemCount;
	}

	/// Iterador sobre los objetos de la lista (clase base)
	class iterator
	{
		// El constructor ha de ser privado, pero no para GameList
		friend GameList;

		const GameList& list;
		Node* node;

		iterator(const GameList& list, Node* node)
			: list(list)
			, node(node)
		{
			++list.numIterators;
		}

	public:
		/// Los iteradores no se pueden mover
		iterator(iterator&& otro) = delete;

		// Los iteradores se pueden copiar
		iterator(const iterator& otro)
			: list(otro.list)
			, node(otro.node)
		{
			++list.numIterators;
		}

		~iterator()
		{
			// Si no hay ning�n iterador apuntando a la lista
			// aplica las eliminaciones pendientes
			if (--list.numIterators == 0)
				list.removePending();
		}

		/// Accede al elemento apuntado por el iterador
		T& operator*() const { return *node->elem; }

		// Define los operadores de comparaci�n de iteradores (<=> basta en C++20)
#ifdef __cpp_lib_three_way_comparison
		auto operator<=>(const iterator& other) { return node <=> other.node; }
#else
		bool operator==(const iterator& other) { return node == other.node; }
		bool operator!=(const iterator& other) { return node != other.node; }
#endif
	};

	class forward_iterator : public iterator
	{
	public:
		using iterator::iterator;

		/// Avanza el iterador
		iterator& operator++()
		{
			// Se salta los elementos que han sido eliminados
			this->node = this->list.nextActive(this->node->next);
			return *this;
		}
	};

	class backward_iterator : public iterator
	{
	public:
		using iterator::iterator;

		/// Avanza el iterador (en direcci�n inversa)
		iterator& operator++()
		{
			// Se salta los elementos que han sido eliminados
			this->node = this->list.prevActive(this->node->prev);
			return *this;
		}
	};

	/// Iterador al inicio de la lista
	auto begin() const { return forward_iterator(*this, nextActive(ghostNode.next)); }

	/// Iterador al final de la lista
	auto end() const { return forward_iterator(*this, &ghostNode); }

	/// Iterador al principio de la lista en sentido inverso
	auto rbegin() const { return backward_iterator(*this, prevActive(ghostNode.prev)); }

	/// Iterador al final de la lista en sentido inverso
	auto rend() const { return backward_iterator(*this, &ghostNode); }
};

#endif // GAME_LIST
