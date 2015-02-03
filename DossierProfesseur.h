#ifndef DEF_PROF
#define DEF_PROF

#include <iostream>
#include <string>

struct Cours
{
	std::string sigle;
	Cours *suivant;
};
Cours *courant_cours;

struct Etudiant
{
	std::string nom;
	Etudiant *apres;
};
Etudiant *courant_etu;

struct Professeur
{
	std::string nom;
	std::string prenom;
	Cours *listecours;
	Etudiant *listetudiant;
	Professeur *suivant;
};
Professeur *courant_prof;

class DossierProfesseur
{
  private:
	Professeur *tete; // dÈbut de la liste chaÓnÈe

  public:
	DossierProfesseur (std::string FP); // Construit de la structure de la liste chaÓnÈe en mÈmoire ‡ partir du fichier FP
	~DossierProfesseur ( );											 // DÈtruit de la liste chaÓnÈe existant en mÈmoire.
	void supprimer (std::string nom, std::string prenom );		 // supprime de la liste chaÓnÈe un professeur donnÈ
	std::string afficherleprofplusetudiant ( ) const;				 // affiche le nom du professeur ayant le plus díÈtudiants
	std::string affichercoursplusdemande ( ) const;				 // affiche le cours le plus demandÈ de la liste
	int affichernbreprofpouruncours (std::string coursdonne) const; // affiche le nombre de professeurs pour le
																	 // cours coursdonne recopie la liste chaÓnÈe
	void recopier (std::string FP); // dans le fichier FP
};

#endif
