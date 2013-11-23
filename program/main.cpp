#include "render/renderer.h"


int main()
{
	Renderer& theRenderer = Renderer::Instance();
	if(theRenderer.Init())
		theRenderer.Run();
	return 0;
}
