#include "render/renderer.h"


int main(int argc, char ** argv)
{
	if(argc<2)
	{
		std::cout<<"Pas assez d'arguments"<<std::endl;
		return -1;
	}
	Renderer& theRenderer = Renderer::Instance();
	if(theRenderer.Init(argv[1], argv[2]!=NULL))
		theRenderer.Run();
	return 0;
}
