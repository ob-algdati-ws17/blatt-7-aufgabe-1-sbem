/**
 * @authors Ehsan Moslehi, Sebastian Bauman
 */

#include "testAVLTree.h"
#include <memory>

using namespace std;

// empty tree

/*TEST(AVLTreeTest, Empty_Tree) {
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
}*/


// remove

// insert nothing and remove from empty tree
TEST(AVLTreeTest, Remove_EmptyTree) {
    AVLTree t;
    t.remove(43);
    EXPECT_EQ(nullptr, t.preorder());
    EXPECT_EQ(nullptr, t.inorder());
    EXPECT_EQ(nullptr, t.postorder());
}

// insert one node and remove this one node
TEST(AVLTreeTest, Remove_RootWithoutChilds) {
    AVLTree t;
    t.insert(43);
    t.remove(43);
    EXPECT_EQ(nullptr, t.preorder());
    EXPECT_EQ(nullptr, t.inorder());
    EXPECT_EQ(nullptr, t.postorder());
}

// insert two nodes and remove one node
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