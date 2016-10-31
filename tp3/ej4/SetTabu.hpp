#include <set>
#include <queue>
#include <utility>

//usaria unordered_set si no fuera para la facu

typedef std::pair<int,int> Arista;


struct compArista
{
	bool operator() (const Arista &izq, const Arista &der)
	{
		//si der es izq invertido
		if(izq.first == der.second && izq.second == der.first)
			return false;
		return izq.first<der.first || (!(der.first<izq.first) && izq.second<der.second);
	}
};


class SetTabu
{
	public:
		SetTabu();
		~SetTabu();
		void push(Arista nueva);
		Arista pop();//podria omitir este retorno
		long long size();
		bool belongs(Arista buscada);
	
	private:
		std::queue<Arista> cola;
		std::set<Arista,compArista> conjunto;
};
