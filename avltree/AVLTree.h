/**
 * @authors Ehsan Moslehi, Sebastian Bauman
 */

/* TODO: upin(), upout(), remove(), googletests,
 * öffentliches Interface mit Doxygen kommentiert und als GitHub-Page veröffentlicht,
 * README.md hat link auf GitHub-Page.
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
        signed char bal = 0;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *prev = nullptr;
        Node(const int);
        Node(const int, Node *);
        Node(const int, Node *, Node *, Node*);
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
     * pp ist Vorgaengerklnoten von p (parent of p)
     *
     * 1.) p ist linker Nachfolger von pp:
     * Fall 1.1 - bal(pp) war 1 und wird 0:
     *   + falls pp Wurzel eines Teilbaums und
     *   + bal(pp) durch upin(p) zu 0 wird, dann
     *   + kann sich nichts weiter mehr geaendert haben und
     *   + upin() kann beendet werden
     *
     * Fall 1.2 - bal(pp) war 0 und wird -1:
     *   + falls bal(pp) 0 war und durch upin(p) zu -1 wird
     *   + muss upin(pp) aufgerufen werden (-> rekursiver Aufruf)
     *
     * Fall 1.3 - bal(pp) war -1 und wuerde zu -2:
     *   + ERROR!! AVL-Bedingung wuerde verletzt werden
     *   + bal(pp) darf nicht zu -2 werden!
     *   + Fall 1.3.1 - bal(p) == -1:
     *     * Ausfuehren einer Rotation nach rechts
     *     * Anschließend sind bal(pp) und bal(p) == 0
     *     * fertig
     *   + Fall 1.3.2 - bal(p) == 1:
     *     * Ausfuehren einer Doppelrotation nach links-rechts
     *     * Anschließend ist bal(pp) == 0
     *     * fertig
     *
     * 2.) p ist rechter Nachfolger von pp:
     * Fall 2.1 -> Analog zu "p ist linker Nachfolger von pp"
     * Fall 2.2 -> Analog zu "p ist linker Nachfolger von pp"
     * Fall 2.3.1 -> Rotation nach links, ansonsten analog zu "p ist linker Nachfolger von pp"
     * Fall 2.3.2 -> Doppelrotation nach rechts-links, ansonsten analog zu "p ist linker Nachfolger von pp"
     */
    void upin(Node*);

    /*
     * -> upout(p) kann rekursiv längs des Suchpfades aufgerufen werden
     * -> adjustiert die Höhenbalancen jedes Knotens
     * -> führt ggf. Rotationen oder Doppelrotationen durch
     * -> wenn upout(p) aufgerufen wird gilt:
     *    - bal(p) == 0
     *    - Teilbaum mit Wurzel p ist in Höhe um 1 geschrumpft
     *    -> die Invariante (bal(p) = 0) muss VOR jedem Aufruf von upout(p) gelten!!!
     *
     * Fall 1: p ist linker Sohn seines Vaters pp
     *    Fall 1.1: bal(pp) == -1
     *    -> bal(pp) wird zu 0
     *    -> fertig
     *
     *    Fall 1.2: bal(pp) == 0
     *    -> bal(pp) wird zu 1
     *    -> fertig
     *
     *    Fall 1.3: bal(pp) == 1
     *    -> bal(pp) wird zu 2 => AVL-Bedingung verletzt!!!!
     *    -> q ist rechter Nachfolger von pp (also rechter Bruder von p). Fallunterscheidung nach bal(q):
     *       Fall 1.3.1: bal(q) == 0
     *         => rotateLeft(pp)
     *         -> fertig
     *       Fall 1.3.2: bal(q) == 1
     *         => rotateLeft(pp)
     *         => upout(neue Wurzel des Teilbaums nach Rotation)
     *         -> fertig
     *       Fall 1.3.3: bal(q) == -1
     *         => rotateRightLeft(pp)
     *         => upout(neue Wurzel des Teilbaums nach Doppel-Rotation)
     *         -> fertig
     *
     * Fall 2: p ist rechter Sohn seines Vaters pp
     *    Fall 2.1: bal(pp) == -1
     *    -> bal(pp) wird zu 0
     *    -> fertig
     *
     *    Fall 2.2: bal(pp) == 0
     *    -> bal(pp) wird zu 1
     *    -> fertig
     *
     *    Fall 2.3: bal(pp) == 1
     *    -> bal(pp) wird zu 2 => AVL-Bedingung verletzt!!!!
     *    -> q ist linker Nachfolger von pp (also linker Bruder von p). Fallunterscheidung nach bal(q):
     *       Fall 2.3.1: bal(q) == 0
     *         => rotateRight(pp)
     *         -> fertig
     *       Fall 2.3.2: bal(q) == 1
     *         => rotateRight(pp)
     *         => upout(neue Wurzel des Teilbaums nach Rotation)
     *         -> fertig
     *       Fall 2.3.3: bal(q) == -1
     *         => rotateLeftRight(pp)
     *         => upout(neue Wurzel des Teilbaums nach Doppel-Rotation)
     *         -> fertig
     */
    /*
     * \Brief Method adjusts the balances of nodes of an avl tree after a node was removed from the tree.
     *
     * This method is called, after a node of an avl tree has been removed. Its task is to adjust the
     * balances of nodes and to rotate a section tree in the right way if it is necessary. Before upout()
     * begins to work, the precondition, that the node given as a parameter must have
     * a balance value of 0, must be fulfilled.
     *
     * @param Node object of which the balance has to be adjusted
     */
    void upout(Node*);

    void insert(const int, Node*);

    /*
     * \Brief Method finds symmetric predecessor to a given Node object.
     *
     * This method iterates through an avl tree, finds and returns the found symmetric
     * predecessor to a Node object, which must be transferred to the method as a parameter.
     *
     * @param Node object as start for the iteration
     * @return the found symmetric predecessor as a Node object
     */
    Node *findSymPred(Node *);

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
     * 2.) Knoten p mit entsprechendem Schluessel gefunden:
     *     * Fall 1: beide Nachfolger von p sind Blaetter
     *       - ersetzen des Knotens durch ein Blatt (nullptr)
     *       - pp ist Vorgänger von p
     *       - der andere Teilbaum q von pp kann nur eine Höhe von 0, 1 oder 2 haben. Fallunterscheidung Höhe von q:
     *
     *         Fall 1.1: q hat Höhe 0:
     *         -> bal(p) war 1 und wird zu 0
     *         -> aufruf upout() auf Suchpfad zur Wurzel
     *         -> fertig
     *
     *         Fall 1.2: q hat Höhe von 1:
     *         -> bal(p) war 0 und wird zu -1 oder 1
     *         -> fertig
     *
     *         Fall 1.3: q hat Höhe von 2:
     *         -> bal(p) war -1 oder 1 und wird zu -2 oder 2
     *         => AVL-Kriterium verletzt!!!
     *            1.) Rotation oder Doppelrotation (wann welches?)
     *            2.) Falls neue bal(neue Wurzel nach Rotation) == 0, ist Höhe um 1 gesunken
     *            3.) Aufruf upout() auf Suchpfad zur Wurzel
     *         -> fertig
     *
     *     * Fall 2: Ein Nachfolger ist innerer Knoten und einer ist Blatt
     *       - falls p nur inneren Knoten q und ein Blatt als Nachfolger hat
     *         müssen beide Nachfolger von q Blätter sein (AVL-Kriterium)
     *       -> p->key = q->key und q wird durch Blatt ersetzt
     *       -> Aufruf upout(), da Höhe von Teilbaum von 2 auf 1 gesunken ist
     *
     *     * Fall 3: Beide Nachfolger sind innere Knoten
     *       -> Wie bei nat. Suchbäumen:
     *          - ersetzen des Schlüssels von p durch Schlüssel des sym. Vorgängers
     *          - entfernen des sym. Vorgängers
     *          -> entspricht entfernen eines Knotes gemäß Fall 2.1 oder 2.2
     */
    void remove(const int);

    vector<int> *preorder() const;
    vector<int> *inorder() const;
    vector<int> *postorder() const;

    friend ostream &operator<<(ostream &, const AVLTree &);

};

#endif //BLATT_7_AUFGABE_1_SBEM_AVLTREE_H
