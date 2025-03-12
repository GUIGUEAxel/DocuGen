/*!
 * \file "Case.cpp"
 * \brief Définition de la classe CCase
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2015
 *
 * \details Cette classe représente une case du labyrinthe,
 *          incluant ses voisins et son état de visite.
 */

#include "Case.h"

 /*!
  * \brief Définit la position d'une case dans le labyrinthe
  * \param X Coordonnée X de la case
  * \param Y Coordonnée Y de la case
  */
void CCase::setPos(size_t X, size_t Y)
{
    m_PosX = X;
    m_PosY = Y;
}

/*!
 * \brief Définit le voisin du haut
 * \param pcase Pointeur vers la case voisine
 */
void CCase::setTopNeightBors(pCase pcase)
{
    if (!m_TopNeightBors)
    {
        m_TopNeightBors = pcase;
        pcase->setBottomNeightBors(shared_from_this());
    }
}

/*!
 * \brief Définit le voisin de droite
 * \param pcase Pointeur vers la case voisine
 */
void CCase::setRightNeightBors(pCase pcase)
{
    if (!m_RightNeightBors)
    {
        m_RightNeightBors = pcase;
        pcase->setLeftNeightBors(shared_from_this());
    }
}

/*!
 * \brief Définit le voisin du bas
 * \param pcase Pointeur vers la case voisine
 */
void CCase::setBottomNeightBors(pCase pcase)
{
    if (!m_BottomNeightBors)
    {
        m_BottomNeightBors = pcase;
        pcase->setTopNeightBors(shared_from_this());
    }
}

/*!
 * \brief Définit le voisin de gauche
 * \param pcase Pointeur vers la case voisine
 */
void CCase::setLeftNeightBors(pCase pcase)
{
    if (!m_LeftNeightBors)
    {
        m_LeftNeightBors = pcase;
        pcase->setRightNeightBors(shared_from_this());
    }
}

/*!
 * \brief Dessine une case dans le labyrinthe
 * \param sizeCase Taille d'une case à l'écran
 */
void CCase::drawCase(const LibGraph2::CSize& sizeCase)const
{
    LibGraph2::ILibGraph2* libgraph = LibGraph2::GetLibGraph2();
    libgraph->setPen(LibGraph2::MakeARGB(20, 0, 0, 0), 0.5f);

    if (m_Visited)
        libgraph->setSolidBrush(LibGraph2::MakeARGB(200, 255, 255, 0));
    if (m_WrongChoice)
        libgraph->setSolidBrush(LibGraph2::MakeARGB(200, 255, 0, 0));
    if (!m_Visited && !m_WrongChoice)
        libgraph->setSolidBrush(LibGraph2::MakeARGB(10, 0, 0, 0));

    libgraph->drawRectangle(LibGraph2::CRectangle(LibGraph2::CPoint(m_PosX * sizeCase.m_fWidth, m_PosY * sizeCase.m_fHeight), sizeCase));

    libgraph->setPen(LibGraph2::MakeARGB(255, 0, 0, 0), 2);

    if (getTopNeightBors() == nullptr)
        libgraph->drawLine(LibGraph2::CPoint(m_PosX * sizeCase.m_fWidth, m_PosY * sizeCase.m_fHeight),
            LibGraph2::CPoint(m_PosX * sizeCase.m_fWidth + sizeCase.m_fWidth, m_PosY * sizeCase.m_fHeight));

    if (getRightNeightBors() == nullptr)
        libgraph->drawLine(LibGraph2::CPoint(m_PosX * sizeCase.m_fWidth + sizeCase.m_fWidth, m_PosY * sizeCase.m_fHeight),
            LibGraph2::CPoint(m_PosX * sizeCase.m_fWidth + sizeCase.m_fWidth, m_PosY * sizeCase.m_fHeight + sizeCase.m_fHeight));

    if (getBottomNeightBors() == nullptr)
        libgraph->drawLine(LibGraph2::CPoint(m_PosX * sizeCase.m_fWidth, m_PosY * sizeCase.m_fHeight + sizeCase.m_fHeight),
            LibGraph2::CPoint(m_PosX * sizeCase.m_fWidth + sizeCase.m_fWidth, m_PosY * sizeCase.m_fHeight + sizeCase.m_fHeight));

    if (getLeftNeightBors() == nullptr)
        libgraph->drawLine(LibGraph2::CPoint(m_PosX * sizeCase.m_fWidth, m_PosY * sizeCase.m_fHeight),
            LibGraph2::CPoint(m_PosX * sizeCase.m_fWidth, m_PosY * sizeCase.m_fHeight + sizeCase.m_fHeight));
}
