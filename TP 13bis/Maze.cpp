/*!
 * \file "Maze.cpp"
 * \brief Définition de la classe CMaze
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2015
 *
 * \details Cette classe gère la structure du labyrinthe et sa résolution.
 */

#include "Maze.h"

 /*!
  * \brief Constructeur de la classe CMaze
  * \param maze Représentation du labyrinthe sous forme de chaîne de caractères
  * \param Width Largeur du labyrinthe
  * \param Height Hauteur du labyrinthe
  */
CMaze::CMaze(const std::string& maze, const size_t& Width, const size_t& Height)
	:m_Maze(Height)
{
	for (size_t j = 0; j < Height; j++)
	{
		m_Maze[j].resize(Width);
		for (size_t i = 0; i < Width; i++)
		{
			m_Maze[j][i] = std::make_shared<CCase>();
			m_Maze[j][i]->setPos(i, j);
		}
	}

	// Initialisation des connexions entre les cases du labyrinthe
	for (size_t j = 0; j < Height; j++)
		for (size_t i = 0; i < Width; i++)
		{
			if (j < Height - 1 && maze[(j * (Width * 2)) + (i * 2)] == ' ')
			{
				m_Maze[j][i]->setBottomNeightBors(m_Maze[j + 1][i]);
			}
			if (i < Width - 1 && maze[(j * (Width * 2)) + (i * 2 + 1)] == ' ')
			{
				m_Maze[j][i]->setRightNeightBors(m_Maze[j][i + 1]);
			}
		}
}

/*!
 * \brief Ajoute une étape dans la résolution du labyrinthe
 */
void CMaze::AddStep()
{
	CCase::pCase pCurCase = m_Path.back();
	CCase::pCase pCaseToAdd;
	bool next = true;

	if (m_Path.empty())
	{
		std::cout << "Il n'y a pas de chemin possible";
		return;
	}

	if (pCurCase == m_End)
		return;

	// Vérification des voisins pour avancer dans le labyrinthe
	if (pCurCase->getRightNeightBors() != nullptr && next && !pCurCase->getRightNeightBors()->getVisited())
	{
		pCaseToAdd = pCurCase->getRightNeightBors();
		next = false;
	}
	if (pCurCase->getTopNeightBors() != nullptr && next && !pCurCase->getTopNeightBors()->getVisited())
	{
		pCaseToAdd = pCurCase->getTopNeightBors();
		next = false;
	}
	if (pCurCase->getLeftNeightBors() != nullptr && next && !pCurCase->getLeftNeightBors()->getVisited())
	{
		pCaseToAdd = pCurCase->getLeftNeightBors();
		next = false;
	}
	if (pCurCase->getBottomNeightBors() != nullptr && next && !pCurCase->getBottomNeightBors()->getVisited())
	{
		pCaseToAdd = pCurCase->getBottomNeightBors();
		next = false;
	}

	if (!next)
	{
		pCaseToAdd->isVisited();
		m_Path.push_back(pCaseToAdd);
	}
	else
	{
		pCurCase->isWrongChoice();
		m_Path.pop_back();
	}
}

/*!
 * \brief Définit le point de départ du labyrinthe
 * \param start Pointeur vers la case de départ
 */
void CMaze::setStart(CCase::pCase& start)
{
	m_Start = start;
	start->isVisited();
	m_Path.push_back(start);
}

/*!
 * \brief Définit le point d'arrivée du labyrinthe
 * \param end Pointeur vers la case d'arrivée
 */
void CMaze::setEnd(CCase::pCase& end)
{
	m_End = end;
}
