#include "3dRenderer.h" 

int main()
{
	olcEngine3D demo;
	if (demo.ConstructConsole(256, 240, 1, 1))
		demo.Start();
    return 0;
}
