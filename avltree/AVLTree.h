/**
 * @authors Ehsan Moslehi, Sebastian Bauman
 */

#ifndef BLATT_7_AUFGABE_1_SBEM_AVLTREE_H
#define BLATT_7_AUFGABE_1_SBEM_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

class AVLTree {

private:
    struct Node {
        const int key;  // Vorgabe: nur ints als Schluessel
        // Balancefaktor für einen Knoten. Wird aktualisiert bei Aenderungen an Baumstruktur. bal e [-1,1].
        // Hoehe rechter Teilbaum - Hoehe linker Teilbaum.
        int bal;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(const int);
        Node(const int, Node *, Node*);
        ~Node();
        bool search(const int) const;
        vector<int> *preorder() const;  // Hauptreihenfolge (© Prof. Dr. Oliver Braun)
        vector<int> *inorder() const;   // Symmetrische Reihenfolge (© Prof. Dr. Oliver Braun)
        vector<int> *postorder() const; // Nebenreihenfolge (© Prof. Dr. Oliver Braun)
    };

    Node *root = nullptr;

    // ---------------------------------------------------------------------------------------

    /*
     * Die folgenden Methoden sind nur definiert. Es fehlen noch eventuelle Parameter, die
     * uebergeben werden muessen. Alle unten aufgefuehrten Methoden sind nicht schon in der
     * Aufgabe BinTree (Blatt 6) umgesetzt worden und deshalb neu.
     */

    // Hier die vier rotate-Methoden, die die Hoehendifferenz ausgleichen sollen

    /*
     * \brief Method rotates a tree or a section tree one step to the left.
     *
     * This method rotates a whole tree or just a section of a tree by one step to the left. In other
     * words this method performs a single rotation to the left. As the only parameter this method
     * needs a pointer to the root node of the tree it should rotate.
     *
     * @param n a Node argument
     * @return the new root node of the rotated tree
     */
    Node *rotateLeft(Node *n);

    /*
     * \brief Method rotates a tree or a section tree one step to the right.
     *
     * This method rotates a whole tree or just a section of a tree by one step to the right. In other
     * words this method performs a single rotation to the right. As the only parameter this method
     * needs a pointer to the root node of the tree it should rotate.
     *
     * @param n a Node argument
     * @return the new root node of the rotated tree
     */
    Node *rotateRight(Node *n);

    /*
     * \brief Method double rotates a tree or a section tree to the left and then to the right.
     *
     * This method rotates a whole tree or just a section of a tree by two steps: the first one to
     * the left and the second one to the right. In other words this method performs a double rotation
     * left-right. As the only parameter this method needs a pointer to the root node of the tree it
     * should rotate.
     *
     * @param n a Node argument
     * @return the new root node of the rotated tree
     */
    Node *rotateLeftRight(Node *n);

    /*
     * \brief Method double rotates a tree or a section tree to the right and then to the left.
     *
     * This method rotates a whole tree or just a section of a tree by two steps: the first one to
     * the right and the second one to the left. In other words this method performs a double rotation
     * right-left. As the only parameter this method needs a pointer to the root node of the tree it
     * should rotate.
     *
     * @param n a Node argument
     * @return the new root node of the rotated tree
     */
    Node *rotateRightLeft(Node *n);

    /*
     * Methode upin(p) laeuft den Pfad von Knoten p zurueck zu Wurzel und passt Balance-Faktor bal an.
     * upin(p) wird rekursiv aufgerufen und bricht ab, wenn p die Wurzel ist!
     *
     * yp ist Vorgaengerklnoten von p
     *
     * 1.) p ist linker Nachfolger von yp:
     * Fall 1.1 - bal(yp) war 1 und wird 0:
     *   + falls yp Wurzel eines Teilbaums und
     *   + bal(yp) durch upin(p) zu 0 wird, dann
     *   + kann sich nichts weiter mehr geaendert haben und
     *   + upin() kann beendet werden
     *
     * Fall 1.2 - bal(yp) war 0 und wird -1:
     *   + falls bal(yp) 0 war und durch upin(p) zu -1 wird
     *   + muss upin(yp) aufgerufen werden (-> rekursiver Aufruf)
     *
     * Fall 1.3 - bal(yp) war -1 und wuerde zu -2:
     *   + ERROR!! AVL-Bedingung wuerde verletzt werden
     *   + bal(yp) darf nicht zu -2 werden!
     *   + Fall 1.3.1 - bal(p) == -1:
     *     * Ausfuehren einer Rotation nach rechts
     *     * Anschließend sind bal(yp) und bal(p) == 0
     *     * fertig
     *   + Fall 1.3.2 - bal(p) == 1:
     *     * Ausfuehren einer Doppelrotation nach links-rechts
     *     * Anschließend ist bal(yp) == 0
     *     * fertig
     *
     * 2.) p ist rechter Nachfolger von yp:
     * Fall 2.1 -> Analog zu "p ist linker Nachfolger von yp"
     * Fall 2.2 -> Analog zu "p ist linker Nachfolger von yp"
     * Fall 2.3.1 -> Rotation nach links, ansonsten analog zu "p ist linker Nachfolger von yp"
     * Fall 2.3.2 -> Doppelrotation nach rechts-links, ansonsten analog zu "p ist linker Nachfolger von yp"
     */
    void upin(Node*);

    //
    void upout(const int);

    void insert(const int, Node*);

    // ---------------------------------------------------------------------------------------


public:

    ~AVLTree();

    // Funktioniert exakt, wie in natuerlichem Baum -> Siehe BinTree
    bool search(const int) const;

    /*
     * Funktioniert wie in BinTree
     * ABER: Pruefung, ob AVL-Bedingung noch gilt! (Ueberpruefe bal auf Pfad von Einfuegestelle bis zur Wurzel)
     * Ist AVL-Bedingung nicht erfuellt: Rotation oder Doppelrotation
     *
     * - Einfuegen in leeren Baum: -> wie BinTree, nichts besonderes
     * - Einfuegen von x mit Vorgaenger:
     *   * Fall 1:
     *     + bal(p) = 1 (-> rechter Ast von p ist um 1 hoeher als linker Ast)
     *     + wird nun x auf linkem Ast von p eingefuegt, so wird bal(p) == 0
     *   * Fall 2:
     *     + bal(p) = -1 (-> linker Ast von p ist um 1 hoeher als rechter Ast)
     *     + wird nun x auf rechtem Ast von p eingefuegt, so wird bal(p) == 0
     *   * Fall 3:
     *     + bal(p) = 0 (-> linker und rechter Ast von p sind gleich hoch)
     *     + wird x am linken Ast von p eingefuegt, so wird bal(p) == -1, sonst 1
     *     + Immer: Aufruf von upin(p)
     *
     * Wenn sich bal von p geaendert hat, haben sich eventuell auch andere bal auf dem Pfad von p zur Wurzel
     * geaendert. Daher muss upin(p) aufgerufen werden, das von p auf Pfad bis zur Wurzel laeuft und bal
     * anpasst.
     */
    void insert(const int);
    /*
     * 1.) Suche nach Knoten p mit entsprechendem Schluessel
     *     => Knoten p nicht gefunden -> fertig
     * 2.) Knoten p mit entsprechenden Schluessel gefunden:
     *     * Fall 2.1: beide Nachfolger sind Blaetter
     *     * Fall 2.2: Ein Nachfolger ist innerer Knoten und einer ist Blatt
     *     * Fall 2.3: Beide Nachfolger sind innere Knoten
     */
    void remove(const int);

    vector<int> *preorder() const;
    vector<int> *inorder() const;
    vector<int> *postorder() const;

    friend ostream &operator<<(ostream &, const AVLTree &);

};

#endif //BLATT_7_AUFGABE_1_SBEM_AVLTREE_H
