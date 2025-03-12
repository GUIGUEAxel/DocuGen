/*!
 * \file Maze.h
 * \brief Déclaration de la classe CMaze
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2015
 *
 * \details Cette classe représente un labyrinthe et permet de le résoudre.
 */

#pragma once
#include "Case.h"
#include <vector>

 /*!
  * \typedef vec
  * \brief Alias pour un vecteur de pointeurs partagés vers des objets CCase.
  */
using vec = std::vector<CCase::pCase>;

/*!
 * \class CMaze
 * \brief Classe représentant un labyrinthe.
 *
 * Cette classe permet de stocker un labyrinthe sous forme de cases et propose
 * des méthodes pour définir le point de départ, le point d’arrivée et avancer
 * dans la résolution du labyrinthe.
 */
class CMaze
{
private:
    std::vector<vec> m_Maze; /*!< Grille du labyrinthe sous forme de cases */
    vec m_Path; /*!< Chemin suivi pour résoudre le labyrinthe */
    CCase::pCase m_Start; /*!< Pointeur vers la case de départ */
    CCase::pCase m_End; /*!< Pointeur vers la case d'arrivée */

public:
    /*!
     * \brief Constructeur de la classe CMaze.
     * \param maze Représentation du labyrinthe sous forme de chaîne de caractères.
     * \param Width Largeur du labyrinthe.
     * \param Height Hauteur du labyrinthe.
     */
    CMaze(const std::string& maze, const size_t& Width, const size_t& Height);

    /*!
     * \brief Définit la case de départ du labyrinthe.
     * \param start Pointeur vers la case de départ.
     */
    void setStart(CCase::pCase& start);

    /*!
     * \brief Définit la case d'arrivée du labyrinthe.
     * \param end Pointeur vers la case d'arrivée.
     */
    void setEnd(CCase::pCase& end);

    /*!
     * \brief Ajoute une étape dans la résolution du labyrinthe.
     */
    void AddStep();

    /*!
     * \brief Retourne la grille du labyrinthe.
     * \return Un vecteur 2D contenant les cases du labyrinthe.
     */
    std::vector<vec> getMaze() const { return m_Maze; }

    /*!
     * \brief Retourne le chemin suivi pour résoudre le labyrinthe.
     * \return Un vecteur contenant les cases du chemin.
     */
    vec getPath() const { return m_Path; }

    /*!
     * \brief Retourne la case de départ du labyrinthe.
     * \return Un pointeur vers la case de départ.
     */
    CCase::pCase getStart() const { return m_Start; }

    /*!
     * \brief Retourne la case d'arrivée du labyrinthe.
     * \return Un pointeur vers la case d'arrivée.
     */
    CCase::pCase getEnd() const { return m_End; }
};
