#include "trKeyBoardManagement.h"

using namespace std;

// INI
trKeyBoardManagement::trKeyBoardManagement() : Start_(false), BTNS(new std::unordered_map<int, trBTN_Key>()), ActiveKeysBufferWrite(new std::vector<trPair<int, bool>>()), ActiveKeysBufferRead(new std::vector<trPair<int, bool>>()), MutexKB(new std::mutex())
{
	
}

// INI deep copy
trKeyBoardManagement::trKeyBoardManagement(const trKeyBoardManagement& other) : Start_(other.Start_), BTNS(new std::unordered_map<int, trBTN_Key>(*other.BTNS)), ActiveKeysBufferWrite(new std::vector<trPair<int, bool>>(*other.ActiveKeysBufferWrite)), ActiveKeysBufferRead(new std::vector<trPair<int, bool>>(*other.ActiveKeysBufferRead)), MutexKB(new std::mutex())
{
	// A voir si ça crée pas de Prblm
	delete other.MutexKB; // On ne copie pas le mutex, on crée un nouveau mutex pour éviter les conflits d'accès
}

// copy
trKeyBoardManagement& trKeyBoardManagement::operator=(const trKeyBoardManagement& other)
{
	if (this == &other) { return *this; }

	Start_ = other.Start_;
	BTNS = new std::unordered_map<int, trBTN_Key>(*other.BTNS);
	ActiveKeysBufferWrite = new std::vector<trPair<int, bool>>(*other.ActiveKeysBufferWrite);
	ActiveKeysBufferRead = new std::vector<trPair<int, bool>>(*other.ActiveKeysBufferRead);
	MutexKB = new std::mutex();

	// A voir si ça crée pas de Prblm
	delete other.MutexKB; // On ne copie pas le mutex, on crée un nouveau mutex pour éviter les conflits d'accès

	return *this;
}

// FNC
bool trKeyBoardManagement::CreateBTN(const trBTN_Key& Btn)
{
	(*BTNS)[Btn.GetKey()] = Btn;

	return true;
}

// SET
void trKeyBoardManagement::SetActionBtnKey(int Key, void (*Action)()) 
{
	(*BTNS)[Key].SetAction(Action);
}

// GET
const std::unordered_map<int, trBTN_Key>& trKeyBoardManagement::GetBTNS() const
{
	return *BTNS;
}

const int trKeyBoardManagement::GetLastKeyState(const std::vector<trPair<int, bool>>& actkeys, int Key)
{
	for (auto it = actkeys.rbegin(); it != actkeys.rend(); ++it)
	{
		if (*it->first == Key)
		{
			return *it->second;
		}
	}

	return -1; // Non trouvé, donc pas de dernière action pour cette touche
}

// UPDATE
void trKeyBoardManagement::Update() 
{
	{ // Pour éviter que le mutex reste verrouillé trop longtemps, on utilise un bloc pour le verrouiller temporairement
		lock_guard<std::mutex> guard(*MutexKB); 
		std::swap(ActiveKeysBufferWrite, ActiveKeysBufferRead); 
	}

	// On vide le buffer
	for (auto& it : *ActiveKeysBufferRead)
	{
		(*BTNS)[*it.first].Update(*it.second);
	}

	// Traiter les boutons
	for (auto& it : *BTNS)
	{
		if (it.second.GetActionState())
		{
			it.second.DoAction();
		}
	}

	ActiveKeysBufferRead->clear(); 
}

// START
void trKeyBoardManagement::Start() 
{
	if (!Start_) 
	{
		Start_ = true;
		Loop(); // ici la loop est lancée, JUSTE pour garder en mémoire les touches du clavier
	}
}

// LOOP
void trKeyBoardManagement::Loop() 
{
	std::unordered_map<int, bool> LocalKeyState;

	while (true) 
	{
		std::vector<trPair<int, bool>> LocalBuffer; // On crée un vecteur local pour stocker les touches pressées ou relâchées

		for (auto& it : *BTNS) 
		{
			bool kState = (GetAsyncKeyState(it.first) & 0x8000);

			if (kState && GetLastKeyState(LocalBuffer, it.first) == -1 && !LocalKeyState[it.first])
			{
				LocalBuffer.push_back(trPair<int, bool>(it.first, true));
			}
			else if (!kState && GetLastKeyState(LocalBuffer, it.first) == -1 && LocalKeyState[it.first])
			{
				LocalBuffer.push_back(trPair<int, bool>(it.first, false));
			}
			else if (kState && GetLastKeyState(LocalBuffer, it.first) == 0) 
			{
				LocalBuffer.push_back(trPair<int, bool>(it.first, true));
			}
			else if (!kState && GetLastKeyState(LocalBuffer, it.first) == 1)
			{
				LocalBuffer.push_back(trPair<int, bool>(it.first, false)); 
			}

			LocalKeyState[it.first] = kState;
		}

		if (!LocalBuffer.empty()) 
		{
			lock_guard<std::mutex> guard(*MutexKB); // On verrouille le mutex pour éviter les conflits d'accès
			ActiveKeysBufferWrite->insert(ActiveKeysBufferWrite->end(), LocalBuffer.begin(), LocalBuffer.end()); // On ajoute le vecteur local au buffer principal
		}
	}
}

trKeyBoardManagement::~trKeyBoardManagement()
{
	delete BTNS;
}