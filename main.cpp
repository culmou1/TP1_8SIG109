#include <iostream>
#include <fstream>
#include "DossierProfesseur.h"
#include <string>
using namespace std;



void afficher (void);

DossierProfesseur::DossierProfesseur (string FP)
{
	ifstream entree; // Input file stream, pour lire le fichier
    tete = courant_prof = new Professeur; /* Construction de la chaine + emplacement de tete */

	entree.open (FP.c_str()); // entrer nom du fichier en mode lecture
	if (entree.fail ()) // Fichier qui n'ouvre pas
	{
		cerr << "Erreur d'ouverture"; // cerr pour message d'erreur
        entree.close(); // Fermeture du fichier
	}
	else // CREE TETE LISTE
	{
		while  (!entree.eof())
		{
            getline (entree, courant_prof->nom);
            getline (entree, courant_prof->prenom);
			courant_prof->listecours = new Cours;
			courant_cours = courant_prof->listecours;
			getline (entree, courant_cours->sigle);
			while (courant_cours->sigle != "&")
			{
				courant_cours->suivant = new Cours;
				courant_cours = courant_cours->suivant;
				getline (entree, courant_cours->sigle);
			}
			courant_cours->suivant = NULL;
            courant_prof->listetudiant = new Etudiant;
			courant_etu = courant_prof->listetudiant;
			getline (entree, courant_etu->nom);
			while (courant_etu->nom != "&")
			{
				courant_etu->apres = new Etudiant;
				courant_etu = courant_etu->apres;
				getline (entree, courant_etu->nom);
			}
        
			courant_etu->apres = NULL;
            if (!entree.eof()) {
            courant_prof->suivant = new Professeur;
            courant_prof=courant_prof->suivant;
            }
		}
		courant_prof->suivant =NULL;
	}
	entree.close();
	courant_prof = tete;
}

DossierProfesseur::~DossierProfesseur ( ) /* Destruction de notre classe. Mais avant nous devons libérer l'espace de la liste chaîné */
{
	courant_prof = tete;
	while (courant_prof != NULL) // Première boucle qui passe toute la structure PROF
	{
		courant_etu = courant_prof->listetudiant;
		while (courant_etu != NULL) /* Tant que la liste des étudiants n'est pas terminé */
		{
			courant_prof->listetudiant= courant_etu->apres;
			delete courant_etu; /* nous avons supprimer un élément de la chaine */
			courant_etu = courant_prof->listetudiant; /* on redonne la position a courant_etu pour supprimer la prochaine élément de la chaîne */
		}
		courant_cours = courant_prof->listecours; /* Pointe sur la prochaine struture Cours */
		while (courant_cours != NULL)
		{
			courant_prof->listecours= courant_cours->suivant;
			delete courant_cours; // Supprime un élément de la chaine de cours
			courant_cours = courant_prof->listecours; /* Redonne la position au prochaine élément à supprimer */
		}
		tete = courant_prof->suivant; /* La tete faut le prochaine élément à supprimer */
		delete courant_prof; // Supprime l'élément
		courant_prof = tete; /* courant_prof recois la position de tete pour le prochain élément à supprimer */
	}
}

void DossierProfesseur::supprimer (string nom, string prenom )
{
	Professeur *precedent; /* Pointeur precedent pour supprimer le nom du prof */
	precedent = NULL;
	courant_prof = tete;

	while (courant_prof != NULL && courant_prof->nom != nom && courant_prof->prenom != prenom)
	{
		precedent = courant_prof;
		courant_prof = courant_prof->suivant;
	}
	if (courant_prof->nom == nom && courant_prof->prenom == prenom)
	{
		if (precedent != NULL) // si precedent n'est pas la tete
			precedent->suivant = courant_prof->suivant;
		else // s'il l'est
			tete = tete->suivant;
		delete courant_prof;
	}
	else
	{
		cout << "Le professeur recherche n'existe pas." << endl;
	}
	courant_prof = tete;
    recopier("Text.TXT");
}

string DossierProfesseur::afficherleprofplusetudiant ( ) const
{
	int nb_etudiants, tampon;
	Professeur *profrecherche;
	string nomrecherche;

	profrecherche = courant_prof = tete; /* Pourquoi tete qui donne a courant_prof qui donne a profrechercher */
	courant_etu = courant_prof->listetudiant;

	for (nb_etudiants = 0; courant_etu->apres != NULL; nb_etudiants++) /* On conte le nombre d'étudiant tu premiers prof */
		{
			courant_etu = courant_etu->apres;
		}
	courant_prof = courant_prof->suivant;
	courant_etu = courant_prof->listetudiant;
	while (courant_prof != NULL) /* Parcours toute les profs tant qu'il n'arrive pas sur la fin  */
	{
		courant_etu = courant_prof->listetudiant;
		for (tampon = 0; courant_etu->apres != NULL; tampon++) /* conte les étudiants du prochais Prof */
		{
			courant_etu = courant_etu->apres;
		}
		if (tampon > nb_etudiants) /* Comparaison être le tampon (Prof suivant) et le nombre du premier Prof */
		{
			nb_etudiants = tampon;
			profrecherche = courant_prof;
		}
		courant_prof = courant_prof->suivant; /* On pointe sur le prochain élément */
		
	}
	nomrecherche = profrecherche->nom + " " + profrecherche->prenom; // Permet de retournée seulement un string
	courant_prof = tete;
	return nomrecherche; // Retourne le nom du prof qui à le plus d'étudiant
}

int DossierProfesseur::affichernbreprofpouruncours (string coursdonne) const
{
	int nbprofpourcours = 0;
	courant_prof = tete;
	
	while (courant_prof != NULL)
	{
		courant_cours = courant_prof->listecours;
		while (courant_cours != NULL)
		{
			if (coursdonne  == courant_cours->sigle) /* recois en parametre un nom de cours et le compare au nom du sigle */
				nbprofpourcours += 1; /* Incrémentation des cours si le if est respecté */
			courant_cours = courant_cours->suivant;
		}
		courant_prof = courant_prof->suivant;
	}
	if (nbprofpourcours == 0) /* Si aucun cour trouvé */
		return 0;
	else
		return nbprofpourcours;

}

string DossierProfesseur::affichercoursplusdemande ( ) const
{
	int nbre = 0, tampon=0;
	Cours *coursrecherche = NULL;

	courant_prof = tete;
	courant_cours = courant_prof->listecours;
	coursrecherche = courant_prof->listecours;
	nbre = affichernbreprofpouruncours (courant_cours->sigle); /* Fait appel à la fonction pour sortir un entier qui correspond au cours le plus enseigner au étudiant */
	
	while (courant_prof != NULL)
	{
		courant_cours = courant_prof->listecours;
		while (courant_cours != NULL)
		{
			tampon = affichernbreprofpouruncours (courant_cours->sigle);
			if (nbre < tampon) /* Je crois que nous donnons le même entier */
			{
				nbre = tampon; /* nbre reçois le tampons si nbre est plus petit que tambon */
				coursrecherche = courant_cours; /* donne le cours le plus demander */
			}
			courant_cours = courant_cours->suivant;
		}
		courant_prof = courant_prof->suivant;
	}
	if (nbre == 0) /* Si aucune enseignant n'enseigne ce cours */
		return "0";
	else
		return coursrecherche->sigle; /* Retourne le string qui à été demander le plus de fois par les prof */
}



void DossierProfesseur::recopier (string FP)
{
    ofstream ficEcriture(FP,ios::out); /* je n'es peut-être pas utilisé le bon mode */
    courant_prof = tete;
    while (ficEcriture.eof()) // Ouverture en monde écriture
    {
        ficEcriture << courant_prof->prenom; // Mets la valeur de courant_prof ->prenom
        ficEcriture << courant_prof->nom; // mets la valeur de courant_prof->Nom
        courant_cours=courant_prof->listecours;
        while (courant_cours->sigle != "&")
        {
            ficEcriture << courant_cours->sigle;
            courant_cours=courant_cours->suivant;
        }
        ficEcriture << "&";
        courant_etu=courant_prof->listetudiant;
        while (courant_etu->nom != "&")
        {
            ficEcriture << courant_etu->nom;
            courant_etu=courant_etu->apres;
        }
        ficEcriture << "&";
        
        ficEcriture.close();
    }
    
}


int main (void)
{
	string cours; int nbre;
    string desnom, desprenom;
    char choix;
	DossierProfesseur first ("/Users/Daehli/Desktop/8SIG109/8SIG109/en.lproj/FP.TXT"); // Déclaration du constructeur
    afficher ();// Affiche le fichier choisis
    cout << "Quelle est vôtre choix entre( '-','#','*','%','$',) ?" << endl;
    cin >> choix;
    
    
    switch (choix) {
        case '-':
            cout << "Quelle est le prenom et le nom du professeur à supprimer ?";
            cin >> desprenom >> desnom;
            first.supprimer(desnom, desprenom);
            break;
        case '#': first.afficherleprofplusetudiant( );
            break;
        case '*':first.affichercoursplusdemande ( );
            break;
        case'%': cout << "Quels court est enseigner par combien de prof ";
            cin >> cours;
            first.affichernbreprofpouruncours (cours);
            break;
        case '$':first.recopier ("FP.TXT");
            break;
        default:
            break;
    }


	cout << endl << "Quel cours cherchez vous? " ;
	cin >> cours;
	nbre = first.affichernbreprofpouruncours (cours);
	if (nbre== 0)
		cout << endl << "Pas de prof !";
	else 
		cout << endl << "Il y a " << nbre << " de profs pour le cours " << cours;

	cout << endl << "Le cours le plus demande est " << first.affichercoursplusdemande() << endl;
	cout << endl << "Le prof qui a le plus d'etudiants est " << first.afficherleprofplusetudiant() <<endl;

	system ("pause");
}

void afficher (void)
{
    cout << courant_prof->nom << "  " << courant_prof->prenom << endl;
	courant_cours = courant_prof->listecours;
	while (courant_cours != NULL)
	{
		cout << courant_cours->sigle << endl;
		courant_cours = courant_cours->suivant;
	}
	courant_etu = courant_prof->listetudiant;
	while (courant_etu != NULL)
	{
		cout << courant_etu->nom << endl;
		courant_etu = courant_etu->apres;
	}
	while (courant_prof!=NULL)
	{ 
		cout << "-------------------------------------------------------------------" << std::endl;
		cout << courant_prof->nom << "  " << courant_prof->prenom << endl;
		courant_cours = courant_prof->listecours;
		while (courant_cours->suivant != NULL)
		{
			cout << courant_cours->sigle << endl;
			courant_cours = courant_cours->suivant;
		}
		courant_etu = courant_prof->listetudiant;
		while (courant_etu->apres != NULL)
		{
			cout << courant_etu->nom << endl;
			courant_etu = courant_etu->apres;
		}
		courant_prof = courant_prof->suivant;
	}
}
