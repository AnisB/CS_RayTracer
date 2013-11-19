#include <render/renderer.h>


int main()
{
	Renderer theRenderer;
	if(theRenderer.Init())
		theRenderer.Run();
	return 0;
}
