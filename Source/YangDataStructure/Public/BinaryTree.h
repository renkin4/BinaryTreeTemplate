#pragma once

/**
 * 
 */

/** 
 * This template represent a element type that tie to a Number for Easy Search using Binary Tree Data Structure
 * @ Element type is the type of class u wish to tie it to
 * @ Value form please enter. Integer or Float value as ValueForm
 */
template <typename ElementType, typename ValueForm>
class TBinaryTree
{
public:
	class TBinaryTreeNode
	{
	public:
		friend class TBinaryTree;

		/** Delete Default Constructor and set default to Next Constructor Declaration */
		TBinaryTreeNode() = delete;

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

		ValueForm GetValue() const { return Value; }

	protected:
		ElementType			ELement;
		TBinaryTreeNode *	LeftNode;
		TBinaryTreeNode *	RightNode;
		ValueForm			Value;

		//TODO depth of this node

		//TODO node operator == and !=

		//TODO node depth Operator

	};

	TBinaryTree() 
		:RootNode(nullptr)
	{}

	TBinaryTree(ElementType & Elem, ValueForm Val)
	{
		InsertNode(Elem, Val);
	}

	~TBinaryTree() 
	{
		DestroyTree();
	}
	
	TBinaryTreeNode* InsertNode(ElementType & Elem, ValueForm Val)
	{
		if (RootNode != nullptr) 
		{
			// Insert new Node From RootNode. It will search for a suitable spot for New guy
			return InsertNode(Elem, Val, RootNode);;
		}

		// if RootNode doesn't Exist create 1
		RootNode = new TBinaryTreeNode(Elem, Val);
		return RootNode;
	}

	/** Search For The node that is tie to the val */
	TBinaryTreeNode * SearchNode(ValueForm Val)
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

	// TODO sort the binary tree

	// TOOD remove 1 of the Branch in the Tree

	// TODO tree sort. Sort An Array that's everywhere and return the val back in Array form

	/** Convert Sorted TMap to Binary Trees*/
	TBinaryTreeNode * SortedArrayToBT(TMap<ValueForm, ElementType> MappedArray, int32 Start, int32 End)
	{
		// When It overlapped the mid points
		if (Start > End)
			return nullptr;

		int32 MidVal = (Start + End) / 2;
		ElementType & ElemType = *MappedArray.Find(MidVal);
		ValueForm InsertVal = *MappedArray.FindKey(ElemType);

		// The Current Node it's Pointing Towards
		TBinaryTreeNode * CurrentNode = InsertNode(ElemType, InsertVal);

		// Add Left node Recursively
		SortedArrayToBT(MappedArray, Start, MidVal - 1);

		// Add Right Node Recursively
		SortedArrayToBT(MappedArray, MidVal + 1, End);

		return CurrentNode;
	}

	TBinaryTreeNode * GetMinValNode() 
	{
		return GetMinValNode(RootNode);
	}

	TBinaryTreeNode * GetMaxValNode() 
	{
		return GetMaxValNode(RootNode);
	}

	TBinaryTreeNode * GetRootNode() const { return RootNode; }

	/** Static assert only allow float, int32 or uint32 as a ValueForm */
	static_assert(TAreTypesEqual<ValueForm, int32>::Value
		|| TAreTypesEqual<ValueForm, float>::Value
		|| TAreTypesEqual<ValueForm, uint32>::Value, 
		"TBinaryTree::ValueFrom expect Float, int32 or uint32 to be passed in.");

private:
	/** Will destroy anything that's below it as well. Recursive deletion */
	void DestroyTree(TBinaryTreeNode * Leaf) 
	{
		// If node have any Left or right node it will delete them as well
		if (Leaf != nullptr) 
		{
			DestroyTree(Leaf->LeftNode);
			DestroyTree(Leaf->RightNode);

			delete Leaf;
			Leaf = nullptr; // Remove Dangling Pointer even though it's not needed
		}
	}

	/** Try insert Node according to the Current Node */
	TBinaryTreeNode * InsertNode(ElementType & Elem, ValueForm Val, TBinaryTreeNode * Leaf)
	{
		// If Val is lesser then The Current Node Val go left
		if (Val < Leaf->Value)
		{	
			// If Current Node left node is not Nullptr rerun this function until it is null on either side.
			if (Leaf->LeftNode != nullptr) 
			{
				return InsertNode(Elem, Val, Leaf->LeftNode);
			}
			// else just add into the current Node left node
			else 
			{
				Leaf->LeftNode = new TBinaryTreeNode(Elem, Val); 
				return Leaf->LeftNode;
			}
		}
		// if it's Bigger then current Node go right
		else
		{
			// Check if Right is empty if it is not Continue Inserting using this function
			if (Leaf->RightNode != nullptr) 
			{
				return InsertNode(Elem, Val, Leaf->RightNode);
			}
			// else just add into the current Node right node
			else 
			{
				Leaf->RightNode = new TBinaryTreeNode(Elem, Val);
				return Leaf->RightNode;
			}
		}

		// Something is wrong
		return nullptr;
	}

	TBinaryTreeNode * SearchNode(ValueForm Val, TBinaryTreeNode* Leaf)
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

	/** Getting the minimum Val from Branch Assuming that Left is always lesser then right */
	TBinaryTreeNode * GetMinValNode(TBinaryTreeNode * NodeToSearchFrom)
	{
		TBinaryTreeNode * MinimumNode = NodeToSearchFrom;

		// Keep Going left until u can't go left anymore
		while (NodeToSearchFrom->LeftNode != nullptr)
		{
			MinimumNode = NodeToSearchFrom->LeftNode;
		}
	
		return MinimumNode;
	}

	/** Getting the maximum Val From branch Assuming that Right is always More then left*/
	TBinaryTreeNode * GetMaxValNode(TBinaryTreeNode * NodeToSearchFrom)
	{
		TBinaryTreeNode * MaximumNode = NodeToSearchFrom;

		// Keep Going left until u can't go Right anymore
		while (NodeToSearchFrom->RightNode != nullptr)
		{
			MaximumNode = NodeToSearchFrom->RightNode;
		}
	
		return MaximumNode;
	}

	TBinaryTreeNode * RootNode;
};

