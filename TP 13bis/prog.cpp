/*!
 * \file prog.cpp
 * \brief Programme principal de la gestion du labyrinthe.
 *
 * Ce fichier contient le point d'entrée principal du programme ainsi que
 * l'initialisation et l'affichage du labyrinthe à l'aide de la bibliothèque LibGraph2.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2015
 */

#include <Windows.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <LibGraph2.h>
#include "maze.h"
#include "Case.h"

#include <iostream>
using namespace std;
using namespace LibGraph2;

/*! \mainpage Documentation du Projet Labyrinthe
 *
 * Ce projet implémente un labyrinthe et son algorithme de résolution.
 * Il utilise la bibliothèque graphique LibGraph2 pour l'affichage.
 */

const CSize g_szCase{ 30, 30 }; //!< \brief Taille de l'affichage des cases

/*!
 * \brief Point d'entrée principal du programme.
 *
 * Initialise la bibliothèque graphique, crée le labyrinthe et gère les événements.
 *
 * \param hInstance Instance de l'application (non utilisé)
 * \param hPrevInstance Ancienne instance de l'application (non utilisé)
 * \param lpCmdLine Paramètres de la ligne de commande (non utilisé)
 * \param nCmdShow Indicateur d'affichage de la fenêtre (non utilisé)
 * \return Retourne 0 à la fin de l'exécution du programme.
 */
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // Récupération de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();

    // Nombre de cases dans le labyrinthe (définit la taille de la fenêtre)
    size_t nNbCasesX = 6;
    size_t nNbCasesY = 5;

    /*! \todo 1) Création des cases A, B, C et D et définition de leurs connexions */
    /* CCase::pCase A = std::make_shared<CCase>(), B = std::make_shared<CCase>(), C = std::make_shared<CCase>(), D = std::make_shared<CCase>();
     * A->setPos(0, 0);
     * A->setRightNeightBors(B);
     * B->setPos(1, 0);
     * B->setBottomNeightBors(D);
     * C->setPos(0, 1);
     * C->setRightNeightBors(D);
     * D->setPos(1, 1);
     */

     /*! \todo 4) Création de l'objet CMaze représentant le labyrinthe */
    const std::string strMaze = "_ _   _| | |"
        "  _| |     |"
        "  _ _ _| | |"
        " |_     _|_|"
        "_ _ _|_ _ _|";
    CMaze Maze = CMaze(strMaze, nNbCasesX, nNbCasesY);

    /*! \todo 5) Initialisation des cases de départ et d'arrivée */
    Maze.setStart(Maze.getMaze()[0][0]);
    Maze.setEnd(Maze.getMaze()[4][5]);

    // Affichage d'un message d'aide
    libgraph->guiMessageBox("Aide", "Appuyez sur la barre d'espace pour faire un pas dans l'algorithme de résolution", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnInformation);
    libgraph->show(CSize{ nNbCasesX * g_szCase.m_fWidth, nNbCasesY * g_szCase.m_fHeight });

    evt e;  // Événement LibGraph 2
    while (libgraph->waitForEvent(e)) // Boucle d'événements
    {
        switch (e.type)
        {
        case evt_type::evtRefresh:
            libgraph->beginPaint();
            {
                /*! \todo 6) Dessiner chaque case du labyrinthe */
                for (auto row : Maze.getMaze())
                    for (auto pCase : row)
                        pCase->drawCase(g_szCase);

                /*! \todo 8) Dessiner le chemin de résolution */
                auto path = Maze.getPath();
                libgraph->setPen(MakeARGB(255, 0, 255, 0), 2, pen_DashStyles::Solid);
                for (size_t i = 0; i < path.size() - 1; i++)
                {
                    CPoint premier(path[i]->getPosX() * g_szCase.m_fWidth + g_szCase.m_fWidth / 2,
                        path[i]->getPosY() * g_szCase.m_fHeight + g_szCase.m_fHeight / 2);
                    CPoint second(path[i + 1]->getPosX() * g_szCase.m_fWidth + g_szCase.m_fWidth / 2,
                        path[i + 1]->getPosY() * g_szCase.m_fHeight + g_szCase.m_fHeight / 2);
                    libgraph->drawLine(premier, second);
                }

                /*! \todo 9) Affichage des images de départ, arrivée et position actuelle */
                libgraph->drawBitmap("start.png", CPoint(Maze.getStart()->getPosX() * g_szCase.m_fWidth, Maze.getStart()->getPosY() * g_szCase.m_fHeight), 1.0 / 640.0 * 30.0);
                libgraph->drawBitmap("exit.png", CPoint(Maze.getEnd()->getPosX() * g_szCase.m_fWidth, Maze.getEnd()->getPosY() * g_szCase.m_fHeight), 1.0 / 640.0 * 30.0);
                auto pCurCase = Maze.getPath().back();
                libgraph->drawBitmap("me.png", CPoint(pCurCase->getPosX() * g_szCase.m_fWidth, pCurCase->getPosY() * g_szCase.m_fHeight), 1.0 / 114.0 * 30.0);
            }
            libgraph->endPaint();
            break;

        case evt_type::evtKeyDown:
            if (e.vkKeyCode == VK_SPACE)
            {
                /*! \todo 7) Effectuer une étape de l'algorithme de résolution */
                Maze.AddStep();
                libgraph->askForRefresh();
            }
            break;
        }
    }

    // Libération de l'objet principal de LibGraph 2
    ReleaseLibGraph2();
    return 0;
}
