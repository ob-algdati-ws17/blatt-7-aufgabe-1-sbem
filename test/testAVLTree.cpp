/**
 * @authors Ehsan Moslehi, Sebastian Bauman
 */

#include "testAVLTree.h"
#include <memory>

using namespace std;

// empty test case ready to receive some code
// We have to rewrite it!!!!!!!!!!!!!!!!!!!!!
TEST(AVLTreeTest, Name) {
    AVLTree b;
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}