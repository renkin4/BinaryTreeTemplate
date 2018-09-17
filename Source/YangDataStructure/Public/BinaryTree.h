#pragma once

/**
 * 
 */

/** This template represent a element type that tie to a Number for Easy Search using Binary Tree Data Structure*/
template <typename ElementType>
class TBinaryTree
{
public:
	class TBinaryTreeNode
	{
	public:
		friend class TBinaryTree;

		/** Default Constructor*/
		TBinaryTreeNode(const ElementType & InElement, int32 InValue)
			: ELement(InElement), LeftNode(nullptr), RightNode(nullptr), Value(InValue)
		{}

		// TODO left node Constructor
		// TOOD left and right Node Constructor

		/** Get Const value*/
		const ElementType & GetElement() const { return ELement; }

		/** Get default Value*/
		ElementType & GetElement() { return ELement; }

		TBinaryTreeNode * GetLeftNode() const { return LeftNode; }

		TBinaryTreeNode * GetRightNode() const { return RightNode; }

		int32 GetValue() const { return Value; }

	protected:
		ElementType			ELement;
		TBinaryTreeNode *	LeftNode;
		TBinaryTreeNode *	RightNode;
		int32				Value;

		//TODO depth of this node

		//TODO node operator == and !=

		//TODO node depth Operator
	};

	TBinaryTree() 
		:RootNode(nullptr)
	{}

	TBinaryTree(ElementType & Elem, int32 Val) 
	{
		InsertNode(Elem, Val);
	}

	~TBinaryTree() 
	{
		DestroyTree();
	}
	
	void InsertNode(ElementType & Elem, int32 Val) 
	{
		if (RootNode != nullptr) 
		{
			// Insert new Node From RootNode. It will search for a suitable spot for New guy
			InsertNode(Elem, Val, RootNode);
			return;
		}

		// if RootNode doesn't Exist create 1
		RootNode = new TBinaryTreeNode(Elem, Val);
	}

	/** Search For The node that is tie to the val */
	TBinaryTreeNode * SearchNode(int32 Val)
	{
		// Search From Root Node
		return SearchNode(Val, RootNode);
	}

	/** Searching Using Element Breaks the purpose of Binary Tree. PS Not usable yet*/
	TBinaryTreeNode * SearchNode(ElementType & Elem)
	{
		return nullptr;
	}

	/** Destroy the entire tree */
	void DestroyTree() 
	{
		DestroyTree(RootNode);
	}

	TBinaryTreeNode * GetRootNode() const { return RootNode; }

private:
	/** Will destroy anything that's below it as well */
	void DestroyTree(TBinaryTreeNode * Leaf) 
	{
		// If node have any Left or right node it will delete them as well
		if (Leaf != nullptr) 
		{
			DestroyTree(Leaf->LeftNode);
			DestroyTree(Leaf->RightNode);
			delete Leaf;
		}
	}

	/** Try insert Node according to the Current Node */
	void InsertNode(ElementType & Elem, int32 Val, TBinaryTreeNode * Leaf)
	{
		// If Val is lesser then The Current Node Val go left
		if (Val < Leaf->Value)
		{	
			// If Current Node left node is not Nullptr rerun this function until it is null on either side.
			if (Leaf->LeftNode != nullptr) 
			{
				InsertNode(Elem, Val, Leaf->LeftNode);
				return;
			}
			// else just add into the current Node left node
			else 
			{
				Leaf->LeftNode = new TBinaryTreeNode(Elem, Val);
			}
		}
		// if it's Bigger then current Node go right
		else
		{
			// Check if Right is empty if it is not Continue Inserting using this function
			if (Leaf->RightNode != nullptr) 
			{
				InsertNode(Elem, Val, Leaf->RightNode);
				return;
			}
			// else just add into the current Node right node
			else 
			{
				Leaf->RightNode = new TBinaryTreeNode(Elem, Val);
			}
		}
	}

	TBinaryTreeNode * SearchNode(int32 Val, TBinaryTreeNode* Leaf) 
	{
		if (Leaf != nullptr) 
		{
			// Check Current Leaf 
			if (Val == Leaf->Value) 
			{
				return Leaf;
			}

			// if not Current Leaf check should search from right or left
			if (Val < Leaf->Value)
				return SearchNode(Val, Leaf->LeftNode);
			else
				return SearchNode(Val, Leaf->RightNode);
		}

		return nullptr;
	}

	TBinaryTreeNode * RootNode;
};

