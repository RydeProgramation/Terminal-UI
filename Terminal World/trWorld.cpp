#include "trWorld.h"

using namespace UITools;
using namespace UIToolsCore;
using namespace std;

// INI default

trWorld::trWorld() : Actors(new std::unordered_map<std::string, trActor*>())
{

}

// INI deep copy

trWorld::trWorld(const trWorld& other) : Actors(new std::unordered_map<std::string, trActor*>(*other.Actors))
{

}

// Copy

trWorld& trWorld::operator=(const trWorld& other)
{
	if (this == &other) { return *this; }

	if (Actors == nullptr) {
		Actors = new std::unordered_map<std::string, trActor*>(*other.Actors);
	} else {
		*Actors = *other.Actors;
	}

	return *this;
}

/// ACTORS MANG ///

bool trWorld::CreateActor(trActor* WIDG)
{
	// std::lock_guard<std::mutex> lock(*Mutex); // des fois abort()

	if (Actors->find(WIDG->GetName().GetDataActual()) == Actors->end())
	{
		(*Actors)[WIDG->GetName().GetDataActual()] = WIDG;
		WIDG->Init();
	}

	else
	{
		MessageBox(
			NULL,                           // Pas de fenêtre parente
			L"Widget already created",      // Message
			L"Erreur",                      // Titre de la boîte
			MB_ICONERROR | MB_OK            // Icône d'erreur + bouton OK
		);
		return false;
	}

	return true;
}

bool trWorld::DestroyActor(trActor* WIDG)
{
	WIDG->SetDestroy(true);

	return true;
}

bool trWorld::DestroyActor(const string& name) // VERIF SI BUG
{
	// Ne pas mettre de mutex ici

	if ((*Actors)[name])
	{
		return DestroyActor((*Actors)[name]);
	}

	MessageBox(
		NULL,
		L"Widget Not found for destroying",
		L"Erreur",
		MB_ICONERROR | MB_OK
	);

	return false;
}

bool trWorld::Destroy()
{
	for (auto it = Actors->begin(); it != Actors->end(); )
	{
		if (it->second->GetDestroy().GetDataActual())
		{
			delete it->second;        // supprime l'objet pointé
			it = Actors->erase(it);   // efface et récupère l'itérateur valide suivant
			ForceRefresh = true;
		}
		else
		{
			++it;
		}
	}

	return true; // Retourne true si tous les widgets ont été détruits avec succès
}

const trActor& trWorld::GetActor(const string& Name) const
{
	auto it = Actors->find(Name);

	if (it != Actors->end())
	{
		return *(it->second);
	}

	else
	{
		MessageBox(
			NULL,
			L"Widget Not found",
			L"Warning",
			MB_ICONERROR | MB_OK
		);

		return trActor::EmptyActor; // Retourne un actor vide
	}
}

const std::unordered_map<std::string, trActor*>& trWorld::GetActors() const
{
	return *Actors; // Retourne un pointeur vers la map contenant tous les widgets
}

// Protected 

trActor* trWorld::GetPtrActor(const std::string& Name) const
{
	auto it = Actors->find(Name);

	if (it != Actors->end())
	{
		return (it->second);
	}

	else
	{
		MessageBox(
			NULL,
			L"Widget Not found",
			L"Warning",
			MB_ICONERROR | MB_OK
		);

		return nullptr; // Retourne le widget vide
	}
}

void trWorld::UpdateActors()
{
	for (auto& widg : *Actors)
	{
		widg.second->APPLY(GetConsoleSize(BorderWidth));
	}
}

// DESTRUCTEUR

trWorld::~trWorld()
{
	delete Actors;
}