#include "window.hpp"

using namespace genv;
using namespace std;

const int X=800;
const int Y=600;

int main()
{
	gout.open(X, Y);
	gout.set_title("Chess");
	gout.load_font("LiberationSans-Regular.ttf", 18);
	Window* window = new Window(X, Y);
	window->event_loop();
    
    return 0;
}
