/*!
 * \file Case.h
 * \brief Déclaration de la classe CCase
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2015
 *
 * \details Cette classe représente une case du labyrinthe et gère ses connexions aux cases voisines.
 */

#pragma once
#include <LibGraph2.h>
#include <memory>

 /*!
  * \class CCase
  * \brief Représente une case du labyrinthe.
  *
  * Une case peut être connectée à ses voisins (haut, droite, bas, gauche) et stocke
  * son état (visitée ou mauvais choix). Elle permet également d'être affichée graphiquement.
  */
class CCase : public std::enable_shared_from_this<CCase>
{
public:
    /*!
     * \typedef pCase
     * \brief Alias pour un pointeur partagé vers une case.
     */
    using pCase = std::shared_ptr<CCase>;

private:
    size_t m_PosX; /*!< Position X de la case dans le labyrinthe */
    size_t m_PosY; /*!< Position Y de la case dans le labyrinthe */
    bool m_Visited = false; /*!< Indique si la case a été visitée */
    bool m_WrongChoice = false; /*!< Indique si la case fait partie d'un mauvais chemin */

    pCase m_TopNeightBors = nullptr; /*!< Pointeur vers la case voisine du haut */
    pCase m_RightNeightBors = nullptr; /*!< Pointeur vers la case voisine de droite */
    pCase m_BottomNeightBors = nullptr; /*!< Pointeur vers la case voisine du bas */
    pCase m_LeftNeightBors = nullptr; /*!< Pointeur vers la case voisine de gauche */

public:
    /*!
     * \brief Définit la position de la case.
     * \param X Coordonnée X.
     * \param Y Coordonnée Y.
     */
    void setPos(size_t X, size_t Y);

    /*!
     * \brief Récupère la position X de la case.
     * \return Coordonnée X.
     */
    size_t getPosX() { return m_PosX; }

    /*!
     * \brief Récupère la position Y de la case.
     * \return Coordonnée Y.
     */
    size_t getPosY() { return m_PosY; }

    /*!
     * \brief Marque la case comme visitée.
     */
    void isVisited() { m_Visited = true; }

    /*!
     * \brief Vérifie si la case a été visitée.
     * \return true si la case a été visitée, sinon false.
     */
    bool getVisited() const { return m_Visited; }

    /*!
     * \brief Marque la case comme un mauvais choix.
     */
    void isWrongChoice() { m_WrongChoice = true; }

    /*!
     * \brief Vérifie si la case fait partie d'un mauvais choix.
     * \return true si la case est un mauvais choix, sinon false.
     */
    bool getWrongChoice() const { return m_WrongChoice; }

    /*!
     * \brief Définit la case voisine du haut.
     * \param pcase Pointeur vers la case du haut.
     */
    void setTopNeightBors(pCase pcase);

    /*!
     * \brief Définit la case voisine de droite.
     * \param pcase Pointeur vers la case de droite.
     */
    void setRightNeightBors(pCase pcase);

    /*!
     * \brief Définit la case voisine du bas.
     * \param pcase Pointeur vers la case du bas.
     */
    void setBottomNeightBors(pCase pcase);

    /*!
     * \brief Définit la case voisine de gauche.
     * \param pcase Pointeur vers la case de gauche.
     */
    void setLeftNeightBors(pCase pcase);

    /*!
     * \brief Retourne la case voisine du haut.
     * \return Pointeur vers la case du haut.
     */
    pCase getTopNeightBors() const { return m_TopNeightBors; }

    /*!
     * \brief Retourne la case voisine de droite.
     * \return Pointeur vers la case de droite.
     */
    pCase getRightNeightBors() const { return m_RightNeightBors; }

    /*!
     * \brief Retourne la case voisine du bas.
     * \return Pointeur vers la case du bas.
     */
    pCase getBottomNeightBors() const { return m_BottomNeightBors; }

    /*!
     * \brief Retourne la case voisine de gauche.
     * \return Pointeur vers la case de gauche.
     */
    pCase getLeftNeightBors() const { return m_LeftNeightBors; }

    /*!
     * \brief Dessine la case sur l'interface graphique.
     * \param sizeCase Taille de la case en pixels.
     */
    void drawCase(const LibGraph2::CSize&) const;
};
