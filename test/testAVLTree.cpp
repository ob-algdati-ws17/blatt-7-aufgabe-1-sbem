/**
 * @authors Ehsan Moslehi, Sebastian Bauman
 */

#include "testAVLTree.h"
#include <memory>

using namespace std;

// empty tree

TEST(AVLTreeTest, Empty_Tree) {
    AVLTree t;
    EXPECT_EQ(nullptr, t.preorder());
    EXPECT_EQ(nullptr, t.inorder());
    EXPECT_EQ(nullptr, t.postorder());
}

// insert

TEST(AVLTreeTest, One_Node) {
    AVLTree t;
    t.insert(42);
//    EXPECT_TRUE(tree.search(42));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(42));
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(42));
}

TEST(AVLTreeTest, Two_Nodes) {
    AVLTree t;
    t.insert(42);
    t.insert(43);
//    EXPECT_TRUE(tree.search(42));
//    EXPECT_TRUE(tree.search(43));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(42, 43));
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42, 43));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(43, 42));
}

TEST(AVLTreeTest, Three_Nodes_Rotate_Right) {
    AVLTree t;
    t.insert(43);
    t.insert(42);
    t.insert(41);
//    EXPECT_TRUE(t.search(41));
//    EXPECT_TRUE(t.search(42));
//    EXPECT_TRUE(t.search(43));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(41, 42, 43));
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42, 41, 43));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(41, 43, 42));
}

TEST(AVLTreeTest, Three_Nodes_Rotate_Left) {
    AVLTree t;
    t.insert(41);
    t.insert(42);
    t.insert(43);
//    EXPECT_TRUE(t.search(41));
//    EXPECT_TRUE(t.search(42));
//    EXPECT_TRUE(t.search(43));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(41, 42, 43));
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42, 41, 43));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(41, 43, 42));
}

TEST(AVLTreeTest, Three_Nodes_Rotate_RightLeft) {
    AVLTree t;
    t.insert(41);
    t.insert(43);
    t.insert(42);
//    EXPECT_TRUE(t.search(41));
//    EXPECT_TRUE(t.search(42));
//    EXPECT_TRUE(t.search(43));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(41, 42, 43));
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42, 41, 43));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(41, 43, 42));
}

TEST(AVLTreeTest, Three_Nodes_Rotate_LeftRight) {
    AVLTree t;
    t.insert(43);
    t.insert(41);
    t.insert(42);
//    EXPECT_TRUE(t.search(41));
//    EXPECT_TRUE(t.search(42));
//    EXPECT_TRUE(t.search(43));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(41, 42, 43));
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42, 41, 43));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(41, 43, 42));
}


// remove

// insert nothing and remove from empty tree (case 1)
TEST(AVLTreeTest, Remove_EmptyTree) {
    AVLTree t;
    t.remove(43);
    EXPECT_EQ(nullptr, t.preorder());
    EXPECT_EQ(nullptr, t.inorder());
    EXPECT_EQ(nullptr, t.postorder());
}

// insert one node and remove this one node (case 2)
TEST(AVLTreeTest, Remove_RootWithoutChilds) {
    AVLTree t;
    t.insert(43);
    t.remove(43);
    EXPECT_EQ(nullptr, t.preorder());
    EXPECT_EQ(nullptr, t.inorder());
    EXPECT_EQ(nullptr, t.postorder());
}

// insert root and left and right child, remove root (case 3)
TEST(AVLTreeTest, Remove_RootWithChilds) {
    AVLTree t;
    t.insert(42);
    t.insert(41);
    t.insert(43);
    t.remove(42);
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(41, 43));
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(41, 43));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(43, 41));
}

// Remove Node that has no childs (case 4)

// Remove left node when right node has height 0 (case 4.1.1)
TEST(AVLTreeTest, Remove_NodeWithNoChilds_NodeIsLeftChild_RightChildHasHeightZero) {
    AVLTree t;
    t.insert(42);
    t.insert(41);
    t.remove(41);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(42));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(42));
}

// Remove left node when right node has height 1 (case 4.1.2)
TEST(AVLTreeTest, Remove_NodeWithNoChilds_NodeIsLeftChild_RightChildHasHeightOne) {
    AVLTree t;
    t.insert(42);
    t.insert(41);
    t.insert(43);
    t.remove(41);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42, 43));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(42, 43));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(43, 42));
}

// Remove left node when right node has children (case 4.1.3.1.1)
TEST(AVLTreeTest, Remove_LeftNodeWithNoChilds_RightChildHasChildren_RightChildHasBalZero_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(10);
    t.insert(60);
    t.insert(1);
    t.insert(15);
    t.insert(55);
    t.insert(65);
    t.insert(14);
    t.insert(16);
    t.remove(1);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50, 15, 10, 14, 16, 60, 55, 65));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10, 14, 15, 16, 50, 55, 60, 65));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(14, 10, 16, 15, 55, 65, 60, 50));
}

// Remove left node when right node has children (case 4.1.3.1.2)
TEST(AVLTreeTest, Remove_LeftNodeWithNoChilds_RightChildHasChildren_RightChildHasBalZero_ParentIsRight) {
    AVLTree t;
    t.insert(50);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(30);
    t.insert(55);
    t.insert(70);
    t.insert(65);
    t.insert(75);
    t.remove(55);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,20,10,30,70,60,65,75));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,20,30,50,60,65,70,75));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(10,30,20,65,60,75,70,50));
}

// Remove left node when right node has children (case 4.1.3.2.1)
TEST(AVLTreeTest, Remove_LeftNodeWithNoChilds_RightChildHasChildren_RightChildHasBalOne_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(10);
    t.insert(60);
    t.insert(1);
    t.insert(15);
    t.insert(55);
    t.insert(65);
    t.insert(16);
    t.remove(1);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,15,10,16,60,55,65));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,15,16,50,55,60,65));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(10,16,15,55,65,60,50));
}

// Remove left node when right node has children (case 4.1.3.2.2)
TEST(AVLTreeTest, Remove_LeftNodeWithNoChilds_RightChildHasChildren_RightChildHasBalOne_ParentIsRight) {
    AVLTree t;
    t.insert(50);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(30);
    t.insert(55);
    t.insert(70);
    t.insert(75);
    t.remove(55);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,20,10,30,70,60,75));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,20,30,50,60,70,75));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(10,30,20,60,75,70,50));
}

// Remove left node when right node has children (case 4.1.3.3.1)
TEST(AVLTreeTest, Remove_LeftNodeWithNoChilds_RightChildHasChildren_RightChildHasBalMinusOne_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(10);
    t.insert(60);
    t.insert(1);
    t.insert(15);
    t.insert(55);
    t.insert(65);
    t.insert(14);
    t.remove(1);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,14,10,15,60,55,65));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,14,15,50,55,60,65));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(10,15,14,55,65,60,50));
}

// Remove left node when right node has children (case 4.1.3.3.2)
TEST(AVLTreeTest, Remove_LeftNodeWithNoChilds_RightChildHasChildren_RightChildHasBalMinusOne_ParentIsRight) {
    AVLTree t;
    t.insert(50);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(30);
    t.insert(55);
    t.insert(70);
    t.insert(65);
    t.remove(55);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,20,10,30,65,60,70));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,20,30,50,60,65,70));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(10,30,20,60,70,65,50));
}

// Remove right node when left node has height 0 (case 4.2.1)
TEST(AVLTreeTest, Remove_NodeWithNoChilds_NodeIsRightChild_LeftChildHasHeightZero) {
    AVLTree t;
    t.insert(42);
    t.insert(43);
    t.remove(43);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(42));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(42));
}

// Remove right node when left node has height 1 (case 4.2.2)
TEST(AVLTreeTest, Remove_NodeWithNoChilds_NodeIsRightChild_LeftChildHasHeightOne) {
    AVLTree t;
    t.insert(42);
    t.insert(41);
    t.insert(43);
    t.remove(43);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(42, 41));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(41, 42));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(41, 42));
}

// Remove right node when left node has children (case 4.2.3.1.1)
TEST(AVLTreeTest, Remove_RightNodeWithNoChilds_LeftChildHasChildren_LeftChildHasBalZero_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(25);
    t.insert(55);
    t.insert(65);
    t.insert(5);
    t.insert(15);
    t.remove(25);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,10,5,20,15,60,55,65));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(5,10,15,20,50,55,60,65));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(5,15,20,10,55,65,60,50));
}

// Remove right node when left node has children (case 4.2.3.1.2)
TEST(AVLTreeTest, Remove_RightNodeWithNoChilds_LeftChildHasChildren_LeftChildHasBalZero_ParentIsRight) {
    AVLTree t;
    t.insert(50);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(30);
    t.insert(53);
    t.insert(65);
    t.insert(51);
    t.insert(54);
    t.remove(65);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,20,10,30,53,51,60,54));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,20,30,50,51,53,54,60));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(10,30,20,51,54,60,53,50));
}

// Remove right node when left node has children (case 4.2.3.2.1)
TEST(AVLTreeTest, Remove_RightNodeWithNoChilds_LeftChildHasChildren_LeftChildHasBalOne_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(25);
    t.insert(55);
    t.insert(65);
    t.insert(15);
    t.remove(25);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,15,10,20,60,55,65));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,15,20,50,55,60,65));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(10,20,15,55,65,60,50));
}

// Remove right node when left node has children (case 4.2.3.2.2)
TEST(AVLTreeTest, Remove_RightNodeWithNoChilds_LeftChildHasChildren_LeftChildHasBalOne_ParentIsRight) {
    AVLTree t;
    t.insert(50);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(30);
    t.insert(53);
    t.insert(65);
    t.insert(54);
    t.remove(65);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,20,10,30,54,53,60));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,20,30,50,53,54,60));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(10,30,20,53,60,54,50));
}

// Remove right node when left node has children (case 4.2.3.3.1)
TEST(AVLTreeTest, Remove_RightNodeWithNoChilds_LeftChildHasChildren_LeftChildHasBalMinusOne_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(25);
    t.insert(55);
    t.insert(65);
    t.insert(5);
    t.remove(25);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,10,5,20,60,55,65));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(5,10,20,50,55,60,65));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(5,20,10,55,65,60,50));
}

// Remove right node when left node has children (case 4.2.3.2.2)
TEST(AVLTreeTest, Remove_RightNodeWithNoChilds_LeftChildHasChildren_LeftChildHasBalMinusOne_ParentIsRight) {
    AVLTree t;
    t.insert(50);
    t.insert(20);
    t.insert(60);
    t.insert(10);
    t.insert(30);
    t.insert(53);
    t.insert(65);
    t.insert(51);
    t.remove(65);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,20,10,30,53,51,60));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,20,30,50,51,53,60));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(10,30,20,51,60,53,50));
}

// Remove left node which has left child (case 5.1.1)
TEST(AVLTreeTest, Remove_LeftNodeWithLeftChild_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(40);
    t.insert(70);
    t.insert(20);
    t.remove(40);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,20,70));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(20,50,70));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(20,70,50));
}

// Remove left node which has right child (case 5.1.2)
TEST(AVLTreeTest, Remove_LeftNodeWithRightChild_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(40);
    t.insert(70);
    t.insert(45);
    t.remove(40);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,45,70));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(45,50,70));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(45,70,50));
}

// Remove right node which has left child (case 5.2.1)
TEST(AVLTreeTest, Remove_RightNodeWithLeftChild_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(30);
    t.insert(70);
    t.insert(60);
    t.remove(70);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,30,60));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(30,50,60));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(30,60,50));
}

// Remove right node which has right child (case 5.2.2)
TEST(AVLTreeTest, Remove_RightNodeWithRightChild_ParentIsLeft) {
    AVLTree t;
    t.insert(50);
    t.insert(30);
    t.insert(70);
    t.insert(80);
    t.remove(70);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,30,80));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(30,50,80));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(30,80,50));
}

// Remove left node which has two children (case 6.1)
TEST(AVLTreeTest, Remove_LeftNodeWithTwoChildren) {
    AVLTree t;
    t.insert(50);
    t.insert(30);
    t.insert(70);
    t.insert(10);
    t.insert(40);
    t.remove(30);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,10,40,70));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(10,40,50,70));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(40,10,70,50));
}

// Remove right node which has two children (case 6.2)
TEST(AVLTreeTest, Remove_RightNodeWithTwoChildren) {
    AVLTree t;
    t.insert(50);
    t.insert(30);
    t.insert(70);
    t.insert(60);
    t.insert(80);
    t.remove(70);
    EXPECT_THAT(*t.preorder(), testing::ElementsAre(50,30,60,80));
    EXPECT_THAT(*t.inorder(), testing::ElementsAre(30,50,60,80));
    EXPECT_THAT(*t.postorder(), testing::ElementsAre(30,80,60,50));
}